# 🏦 Bank Security System

A real-time embedded security system for a bank vault door, built on Raspberry Pi 4 + PIC16F877A with face recognition, motion detection, power monitoring, and a mobile app for remote control.

---

## 📸 System Overview

```
Camera → Face Detection → ArcFace Embedding → SVC Classifier
                                                      ↓
                                              Known? → Log access
                                              Unknown? → Alert App → User decides action
                                                                          ↓
                                                              HTTP request to Pi → Alarm / Lock
```

```
PIR Sensor → PIC16F877A → Close door + Light room → Signal Pi → Capture image → Alert App
Voltage Sensor → PIC16F877A → Power stats → Pi → Alert App (notification + historical data)
```

---

## 🧩 Components

### 1. Raspberry Pi 4 (`pi/mergeall3.py`)
The brain of the system. Runs 3 parallel threads:

| Thread | Job |
|--------|-----|
| `camera_loop` | Captures frames continuously via Picamera2 |
| `detection_loop` | Runs face detection + recognition every N frames |
| `gpio_loop` | Monitors PIR signal and power outage signal from PIC |

**Flask API** (port 5000) receives commands from the mobile app:

| Endpoint | Action |
|----------|--------|
| `GET /alert_action` | Trigger alarm for 2 seconds |
| `GET /lock_on` | Lock the vault door |
| `GET /lock_off` | Unlock the vault door |

---

### 2. PIC16F877A (Embedded Controller)
Handles low-level hardware directly:

| Input | Action |
|-------|--------|
| PIR sensor (RB1) | Closes door (RD3), turns on lights (RD0, RD1), signals Pi |
| Voltage sensor (RA0/ADC) | Reads power level continuously, sends to Pi |
| Power below threshold | Sends alert signal to Pi, Pi forwards to app |
| No motion + no power issue | All outputs cleared |

**Communication with Raspberry Pi:**
The PIC continuously sends data to the Raspberry Pi over UART. This includes the live ADC voltage reading so the Pi can forward power statistics to the app in real time, and trigger signals when specific conditions are met (motion detected after hours, power below threshold). The Pi reads these signals and decides whether to capture an image, send an alert to the database, or trigger the alarm and lock.

---

### 3. ML Model — Face Recognition SVC

🤗 **Model on HuggingFace:** [Hagar633/face-recognition-svc](https://huggingface.co/Hagar633/face-recognition-svc)

**Pipeline:**
```
Camera Frame → YuNet (yunet.onnx) → Crop Face → ArcFace (w600k_mbf.onnx) → 512-dim embedding → SVC classifier → Name or UNKNOWN
```

| File | Description |
|------|-------------|
| `classifier.pkl` | Trained SVC model (scikit-learn, saved with joblib) |
| `yunet.onnx` | YuNet face detector |
| `w600k_mbf.onnx` | ArcFace embedding network |
| `det_500m.onnx` | Additional detection model |
| `mobilefacenet.onnx` | Lightweight face model |

Download all model files from HuggingFace and place them in `pi/models/` before running.

**How to use the classifier standalone:**
```python
import joblib, numpy as np

clf = joblib.load("models/classifier.pkl")
# Pass a 512-dim normalized ArcFace embedding
prediction = clf.predict(embedding.reshape(1, -1))
```

Confidence threshold: `0.70` — predictions below this are treated as `UNKNOWN`.

---

### 4. Mobile App
- Receives push notifications when unknown person detected, PIR triggered, or power outage
- User can confirm or ignore alerts
- Sends HTTP requests to Pi Flask API to control lock and alarm
- Displays power statistics over time from Supabase

---

### 5. Supabase (Backend Database)
All alerts and door states are stored in Supabase:

| Table | Data |
|-------|------|
| `alerts` | Unknown person detections, PIR triggers, power outages |
| `door_state` | Lock/unlock history |
| `people` | Person ID → name mapping for face recognition |

Alert images are uploaded to Supabase Storage (`alerts` bucket).

---

## 🗂️ Project Structure

```
Bank-Security-System/
├── README.md
├── pi/
│   ├── mergeall3.py        # Main Pi application
│   ├── Dockerfile          # Docker image definition
│   ├── requirements.txt    # Python dependencies
│   └── run.sh              # Docker run script
├── hardware/               # PIC16F877A firmware
├── ml_model/               # Training scripts
└── mobile_app/             # Mobile app code
```

---

## 🐳 Docker Setup

### Docker Hub
```bash
sudo docker pull hagar633/bank_sys:latest
```

### Build locally
```bash
cd pi/
sudo docker build -t bank_sys .
```

### Run
```bash
sudo ./pi/run.sh
```

The `run.sh` script mounts the Pi's system libraries and Python venv into the container so all hardware dependencies (picamera2, libcamera, GPIO, cv2) work without needing to be installed inside Docker:

```bash
sudo docker run --privileged --network host \
  -v /dev:/dev \
  -v /run/udev:/run/udev:ro \
  -v /usr:/usr:ro \
  -v /lib:/lib:ro \
  -v /home/pi/venv2:/home/pi/venv2:ro \
  -v /home/pi/bank_sys:/app \
  -e PYTHONPATH=/home/pi/venv2/lib/python3.13/site-packages \
  -e LIBCAMERA_IPA_MODULE_PATH=/usr/lib/arm-linux-gnueabihf/libcamera \
  -e SUPABASE_URL="your_supabase_url" \
  -e SUPABASE_KEY="your_supabase_key" \
  --entrypoint /usr/bin/python3.13 \
  bank_sys /app/mergeall3.py
```

---

## ⚙️ GPIO Pin Map (Raspberry Pi 4)

| Pin (BCM) | Role |
|-----------|------|
| GPIO 23 | PIR sensor input |
| GPIO 24 | Power outage signal input (from PIC) |
| GPIO 18 | Alarm output |
| GPIO 27 | Door lock output |

---

## 📦 Dependencies

### Python (via venv on Pi)
- `opencv-python` — face detection and embedding
- `numpy` — numerical operations
- `scikit-learn` / `joblib` — SVC classifier
- `picamera2` — camera interface
- `RPi.GPIO` — GPIO control
- `flask` — HTTP API
- `supabase` — cloud database

### System
- `libcamera` — camera stack
- Raspberry Pi OS (Bookworm, 64-bit)
- PIC16F877A with custom firmware

---

## 🚀 Push to Docker Hub

```bash
sudo docker login
sudo docker tag bank_sys hagar633/bank_sys:latest
sudo docker push hagar633/bank_sys:latest
```

---

## 🔗 Links

- 🐳 Docker Hub: [hagar633/bank_sys](https://hub.docker.com/r/hagar633/bank_sys)
- 🤗 HuggingFace Model: [Hagar633/face-recognition-svc](https://huggingface.co/Hagar633/face-recognition-svc)
- 💻 GitHub: [yaramahmoudd11/Bank-Security-System](https://github.com/yaramahmoudd11/Bank-Security-System)

---

