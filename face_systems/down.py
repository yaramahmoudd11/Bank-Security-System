import os
import requests
import zipfile

MODELS_DIR = "models"
os.makedirs(MODELS_DIR, exist_ok=True)

def download_file(url, out_path):
    print(f"[DOWNLOAD] {url}")
    r = requests.get(url, stream=True)
    r.raise_for_status()

    with open(out_path, "wb") as f:
        for chunk in r.iter_content(chunk_size=1024 * 1024):
            if chunk:
                f.write(chunk)

    print(f"[OK] Saved to {out_path}")


def unzip(zip_path, extract_to):
    print(f"[UNZIP] {zip_path}")
    with zipfile.ZipFile(zip_path, 'r') as z:
        z.extractall(extract_to)
    print("[OK] Extracted")


# =========================
# 1. YuNet
# =========================
yunet_url = "https://github.com/opencv/opencv_zoo/raw/main/models/face_detection_yunet/face_detection_yunet_2023mar.onnx"

download_file(yunet_url, f"{MODELS_DIR}/yunet.onnx")


# =========================
# 2. InsightFace buffalo_sc
# =========================
buffalo_url = "https://github.com/deepinsight/insightface/releases/download/v0.7/buffalo_sc.zip"

zip_path = f"{MODELS_DIR}/buffalo_sc.zip"
download_file(buffalo_url, zip_path)

unzip(zip_path, MODELS_DIR)

os.remove(zip_path)


print("\n[DONE] All models downloaded")