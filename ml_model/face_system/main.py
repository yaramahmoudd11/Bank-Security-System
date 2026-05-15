"""

"""

import os
import sys
import mimetypes
from pathlib import Path
from datetime import datetime, timezone

import cv2
import numpy as np
import onnxruntime as ort
from supabase import create_client

# ── CONFIG ───────────────────────────────────────────────────────────────────
MODELS_DIR = "models"
YUNET_MODEL = os.path.join(MODELS_DIR, "yunet.onnx")

# down.py may unzip buffalo_sc either directly into models/ or inside models/buffalo_sc/
EMBED_MODEL_CANDIDATES = [
    os.path.join(MODELS_DIR, "w600k_mbf.onnx"),
    os.path.join(MODELS_DIR, "buffalo_sc", "w600k_mbf.onnx"),
]

SUPABASE_URL = os.getenv("SUPABASE_URL", "https://dtrmjuyfclfelfrqxezh.supabase.co")
SUPABASE_KEY = os.getenv("SUPABASE_KEY", "sb_secret_U24nWBwYZ-gadHJIGj9kUQ_MDDEg_By")

BUCKET_NAME = "faces"
PEOPLE_TABLE = "people"
SAMPLES_TABLE = "face_samples"

DEFAULT_ROLE = "manager"
DEFAULT_AUTHORIZED = True
DETECT_SIZE = (320, 240)
SCORE_THRESHOLD = 0.75
NMS_THRESHOLD = 0.30
VALID_EXTENSIONS = {".jpg", ".jpeg", ".png", ".bmp", ".webp"}

# ── PATH / MODEL HELPERS ─────────────────────────────────────────────────────
def fail(message: str):
    print(f"[ERROR] {message}")
    sys.exit(1)


def find_embed_model() -> str:
    for candidate in EMBED_MODEL_CANDIDATES:
        if os.path.isfile(candidate):
            return candidate

    for root, _, files in os.walk(MODELS_DIR):
        for file in files:
            if file == "w600k_mbf.onnx":
                return os.path.join(root, file)

    fail("Embedding model w600k_mbf.onnx not found. Run: python down.py")


def require_models():
    if not os.path.isfile(YUNET_MODEL):
        fail("YuNet model not found. Run: python down.py")
    return find_embed_model()


def is_image_file(path: str) -> bool:
    return Path(path).suffix.lower() in VALID_EXTENSIONS


def collect_images_from_folder(folder_path: str) -> list[str]:
    folder = Path(folder_path)
    if not folder.is_dir():
        fail(f"Folder does not exist: {folder_path}")

    images = [str(p) for p in sorted(folder.iterdir()) if p.is_file() and is_image_file(str(p))]
    return images


def safe_storage_name(text: str) -> str:
    cleaned = "".join(c if c.isalnum() or c in ("-", "_") else "_" for c in text.strip())
    return cleaned or "person"


def get_content_type(file_path: str) -> str:
    content_type, _ = mimetypes.guess_type(file_path)
    return content_type or "application/octet-stream"


# ── LOAD MODELS ──────────────────────────────────────────────────────────────
def load_detector_and_session():
    embed_model = require_models()

    print("[MODEL] Loading YuNet + ONNX embedding model...")

    if not hasattr(cv2, "FaceDetectorYN"):
        fail("cv2.FaceDetectorYN is missing. Try: python -m pip install opencv-contrib-python")

    detector = cv2.FaceDetectorYN.create(
        YUNET_MODEL,
        "",
        DETECT_SIZE,
        score_threshold=SCORE_THRESHOLD,
        nms_threshold=NMS_THRESHOLD,
    )

    session = ort.InferenceSession(embed_model, providers=["CPUExecutionProvider"])
    input_name = session.get_inputs()[0].name
    output_name = session.get_outputs()[0].name

    print(f"[MODEL] OK: detector={YUNET_MODEL}, embedder={embed_model}")
    return detector, session, input_name, output_name


DETECTOR, SESSION, IN_NAME, OUT_NAME = load_detector_and_session()

# ── SUPABASE ─────────────────────────────────────────────────────────────────
if not SUPABASE_KEY or SUPABASE_KEY == "PASTE_YOUR_SUPABASE_KEY_HERE":
    fail(
        "SUPABASE_KEY is not set. In PowerShell run:\n"
        "  $env:SUPABASE_KEY=\"your_key_here\"\n"
        "or paste it locally in the SUPABASE_KEY line before running."
    )

supabase = create_client(SUPABASE_URL, SUPABASE_KEY)
print("[DB] Connected\n")

# ── CORE: DETECTION + EMBEDDING ──────────────────────────────────────────────
def detect_face(img_bgr):
    h, w = img_bgr.shape[:2]
    small = cv2.resize(img_bgr, DETECT_SIZE)
    DETECTOR.setInputSize(DETECT_SIZE)

    _, faces = DETECTOR.detect(small)
    if faces is None or len(faces) == 0:
        return None

    # YuNet output: [x, y, w, h, landmarks..., score]
    best = max(faces, key=lambda f: f[-1])

    sx = w / DETECT_SIZE[0]
    sy = h / DETECT_SIZE[1]

    x = int(best[0] * sx)
    y = int(best[1] * sy)
    fw = int(best[2] * sx)
    fh = int(best[3] * sy)

    pad = int(0.20 * max(fw, fh))
    x1 = max(0, x - pad)
    y1 = max(0, y - pad)
    x2 = min(w, x + fw + pad)
    y2 = min(h, y + fh + pad)

    crop = img_bgr[y1:y2, x1:x2]
    return crop if crop.size > 0 else None


def get_embedding(face_bgr) -> np.ndarray:
    img = cv2.resize(face_bgr, (112, 112))
    img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB).astype(np.float32)
    img = (img - 127.5) / 128.0
    img = np.transpose(img, (2, 0, 1))[np.newaxis]

    out = SESSION.run([OUT_NAME], {IN_NAME: img})[0][0]
    out = out.astype(np.float32)
    return out / (np.linalg.norm(out) + 1e-8)


# ── DB HELPERS ────────────────────────────────────────────────────────────────
def get_person(person_id: int):
    result = supabase.table(PEOPLE_TABLE).select("id, name, role, authorized").eq("id", int(person_id)).limit(1).execute()
    return result.data[0] if result.data else None

def add_person(name: str, role: str = DEFAULT_ROLE, authorized: bool = True) -> int:
    """
    Add person if not exists.
    If the name already exists, reuse the existing ID instead of crashing.
    """
    name = name.strip()

    existing = (
        supabase.table("people")
        .select("id, name, role, authorized")
        .eq("name", name)
        .limit(1)
        .execute()
    )

    if existing.data:
        person_id = existing.data[0]["id"]
        print(f"[DB] Person already exists: id={person_id} name={name}")

        supabase.table("people").update({
            "role": role,
            "authorized": authorized
        }).eq("id", int(person_id)).execute()

        return int(person_id)

    result = supabase.table("people").insert({
        "name": name,
        "role": role,
        "authorized": authorized,
        "embedding": [0.0] * 512
    }).execute()

    new_id = result.data[0]["id"]
    print(f"[DB] Added person: id={new_id} name={name} role={role}")
    return int(new_id)
def update_person_embedding(person_id: int, embedding: np.ndarray):
    supabase.table(PEOPLE_TABLE).update({
        "embedding": embedding.tolist()
    }).eq("id", int(person_id)).execute()


def upload_image(file_path: str, storage_path: str) -> str:
    with open(file_path, "rb") as f:
        file_bytes = f.read()

    supabase.storage.from_(BUCKET_NAME).upload(
        path=storage_path,
        file=file_bytes,
        file_options={
            "content-type": get_content_type(file_path),
            "upsert": "true",
        },
    )
    return storage_path


def sample_exists(person_id: int, image_path: str) -> bool:
    result = (
        supabase.table(SAMPLES_TABLE)
        .select("id")
        .eq("person_id", int(person_id))
        .eq("image_path", image_path)
        .limit(1)
        .execute()
    )
    return bool(result.data)


def save_sample(person_id: int, image_path: str, embedding: np.ndarray):
    if sample_exists(person_id, image_path):
        print(f"  [INFO] Sample already exists in DB: {image_path}")
        return

    supabase.table(SAMPLES_TABLE).insert({
        "person_id": int(person_id),
        "image_path": image_path,
        "embedding": embedding.tolist(),
        "created_at": datetime.now(timezone.utc).isoformat(),
    }).execute()


# ── ENROLMENT FUNCTIONS ──────────────────────────────────────────────────────
def enrol_from_files(person_id: int, image_paths: list[str]):
    person = get_person(person_id)
    if person is None:
        fail(f"No person found with id={person_id}. Run: python face3.py add <name>")

    if not image_paths:
        fail("No image paths provided.")

    embeddings_collected = []
    saved = 0
    person_name = safe_storage_name(person["name"])

    print(f"[INFO] Enrolling samples for id={person_id}, name={person['name']}")

    for path in image_paths:
        if not is_image_file(path):
            print(f"  [SKIP] Not an image file: {path}")
            continue

        img = cv2.imread(path)
        if img is None:
            print(f"  [SKIP] Cannot open: {path}")
            continue

        crop = detect_face(img)
        if crop is None:
            print(f"  [SKIP] No face found in: {path}")
            continue

        emb = get_embedding(crop)

        storage_path = f"person_{person_id}_{person_name}/{Path(path).name}"
        try:
            uploaded_path = upload_image(path, storage_path)
        except Exception as e:
            print(f"  [WARN] Upload failed for {path}: {e}")
            uploaded_path = path

        save_sample(person_id, uploaded_path, emb)
        embeddings_collected.append(emb)
        saved += 1
        print(f"  [OK] Saved sample: {path}")

    if embeddings_collected:
        avg = np.mean(np.stack(embeddings_collected), axis=0)
        avg = avg / (np.linalg.norm(avg) + 1e-8)
        update_person_embedding(person_id, avg)
        print("  [DB] Updated average embedding in people table")

    print(f"\n[DONE] {saved}/{len(image_paths)} valid samples saved for person_id={person_id}")


def enrol_from_folder(person_id: int, folder_path: str):
    images = collect_images_from_folder(folder_path)
    if not images:
        fail(f"No image files found inside folder: {folder_path}")

    print(f"[INFO] Found {len(images)} images in folder: {folder_path}")
    enrol_from_files(person_id, images)


def bulk_enrol(root_folder: str, role: str = DEFAULT_ROLE):
    root = Path(root_folder)
    if not root.is_dir():
        fail(f"Root folder does not exist: {root_folder}")

    subfolders = [p for p in sorted(root.iterdir()) if p.is_dir()]
    if not subfolders:
        fail(
            "Bulk mode needs subfolders, one per person. Example:\n"
            "  people_photos/hagar/1.jpg\n"
            "  people_photos/mayar/1.jpg"
        )

    for folder in subfolders:
        images = collect_images_from_folder(str(folder))
        if not images:
            print(f"[SKIP] No images in: {folder}")
            continue

        name = folder.name.strip()
        print(f"\n========== {name} ==========")
        person_id = add_person(name, role=role)
        enrol_from_files(person_id, images)


# ── LIST / CHECK / DELETE ────────────────────────────────────────────────────
def list_persons():
    people = supabase.table(PEOPLE_TABLE).select("id, name, role, authorized").execute().data or []
    if not people:
        print("[DB] No persons in people table yet.")
        return

    samples = supabase.table(SAMPLES_TABLE).select("person_id").execute().data or []
    counts = {}
    for sample in samples:
        pid = sample["person_id"]
        counts[pid] = counts.get(pid, 0) + 1

    print(f"{'ID':<6} {'Name':<22} {'Role':<12} {'Auth':<7} {'Samples'}")
    print("-" * 62)
    for person in sorted(people, key=lambda x: x["id"]):
        sample_count = counts.get(person["id"], 0)
        print(
            f"{person['id']:<6} {person['name']:<22} {person['role']:<12} "
            f"{str(person['authorized']):<7} {sample_count}"
        )


def check_db():
    print("── people table ──")
    people = supabase.table(PEOPLE_TABLE).select("*").limit(2).execute().data or []
    for row in people:
        emb_len = len(row["embedding"]) if row.get("embedding") else 0
        print(
            f"  id={row.get('id')}  name={row.get('name')}  role={row.get('role')}  "
            f"authorized={row.get('authorized')}  embedding_len={emb_len}"
        )

    print("\n── face_samples table ──")
    samples = supabase.table(SAMPLES_TABLE).select("*").limit(2).execute().data or []
    for row in samples:
        emb_len = len(row["embedding"]) if row.get("embedding") else 0
        print(
            f"  id={row.get('id')}  person_id={row.get('person_id')}  "
            f"image_path={row.get('image_path')}  embedding_len={emb_len}"
        )


def delete_person(person_id: int):
    supabase.table(SAMPLES_TABLE).delete().eq("person_id", int(person_id)).execute()
    supabase.table(PEOPLE_TABLE).delete().eq("id", int(person_id)).execute()
    print(f"[DB] Deleted person_id={person_id} from people + face_samples")


# ── CLI ──────────────────────────────────────────────────────────────────────
def print_help():
    print("""
Commands:
  python face3.py list
  python face3.py check
  python face3.py add <name> [role]
  python face3.py files <person_id> img1.jpg img2.jpg ...
  python face3.py folder <person_id> <folder_path>
  python face3.py bulk <root_folder> [role]
  python face3.py delete <person_id>

For one person with a folder of images:
  python face3.py add hagar
  python face3.py folder 3 hagar_photos

For many people using subfolders:
  people_photos/
    hagar/
      1.jpg
      2.jpg
    mayar/
      1.jpg
      2.jpg

  python face3.py bulk people_photos
""")


def main():
    if len(sys.argv) < 2:
        print_help()
        return

    cmd = sys.argv[1].lower()

    if cmd == "list":
        list_persons()

    elif cmd == "check":
        check_db()

    elif cmd == "add":
        if len(sys.argv) < 3:
            print("Usage: python face3.py add <name> [role]")
            sys.exit(1)
        name = sys.argv[2]
        role = sys.argv[3] if len(sys.argv) >= 4 else DEFAULT_ROLE
        new_id = add_person(name, role=role)
        print(
            "\nNow add face photos using one of these:\n"
            f"  python face3.py folder {new_id} folder_name\n"
            f"  python face3.py files {new_id} photo1.jpg photo2.jpg"
        )

    elif cmd == "files":
        if len(sys.argv) < 4:
            print("Usage: python face3.py files <person_id> img1.jpg img2.jpg ...")
            sys.exit(1)
        enrol_from_files(int(sys.argv[2]), sys.argv[3:])

    elif cmd == "folder":
        if len(sys.argv) < 4:
            print("Usage: python face3.py folder <person_id> <folder_path>")
            print("Example: python face3.py folder 3 hagar_photos")
            sys.exit(1)
        enrol_from_folder(int(sys.argv[2]), sys.argv[3])

    elif cmd == "bulk":
        if len(sys.argv) < 3:
            print("Usage: python face3.py bulk <root_folder> [role]")
            print("Example: python face3.py bulk people_photos")
            sys.exit(1)
        role = sys.argv[3] if len(sys.argv) >= 4 else DEFAULT_ROLE
        bulk_enrol(sys.argv[2], role=role)

    elif cmd == "delete":
        if len(sys.argv) < 3:
            print("Usage: python face3.py delete <person_id>")
            sys.exit(1)
        delete_person(int(sys.argv[2]))

    else:
        print(f"Unknown command: {cmd}")
        print_help()


if __name__ == "__main__":
    main()
