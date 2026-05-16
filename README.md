# 🏦 Bank Security System

An AI-powered smart security system for banks and restricted areas using embedded systems, machine learning, IoT, cloud services, and real-time mobile monitoring.
---

## 📸 System Overview

The Bank Smart Security System is designed to automate security monitoring in restricted areas such as bank rooms, storage areas, and sensitive access zones.

The system combines:

- A Raspberry Pi Linux-based unit for camera processing, face recognition, server communication, and cloud integration.
- PIC16F877A microcontroller-based units for low-level sensor reading, voltage monitoring, relay control, buzzer control, LED indication, and lock control.
- A Flutter mobile application for real-time alerts, door control, voltage visualization, and event review.
- Supabase for database, storage, and real-time streams.
- Firebase Cloud Messaging for push notifications.

The system detects unauthorized access, after-hours motion intrusion, and power-fault conditions, then sends real-time alerts to the manager through the mobile application.

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
## Main Features

- Face recognition access control
- Authorized and unauthorized person classification
- PIR motion detection
- Voltage and power-fault monitoring
- Relay-controlled solenoid lock
- Buzzer and LED alarm indicators
- Raspberry Pi camera evidence capture
- Supabase cloud database integration
- Supabase storage for alert images
- Firebase Cloud Messaging notifications
- Real-time mobile alert streaming
- Remote door lock/unlock control
- Live voltage monitoring and visualization
- Alert status tracking: `new` and `reviewed`

---

##  Final System Architecture

```text
Camera / Sensors
      |
      v
Raspberry Pi Unit + PIC16F877A Unit
      |
      v
Face Recognition + Sensor Processing
      |
      v
Security Decision Logic
      |
      v
Supabase Database + Supabase Storage
      |
      v
Firebase Cloud Messaging
      |
      v
Flutter Mobile Application
      |
      v
Manager Action:
- View alert
- Review alert
- Lock door
- Unlock door
- Ignore alert
```

---



### 4.1 Linux-Based Unit

- Raspberry Pi
- Camera module
- Python runtime
- OpenCV
- ONNX face recognition models
- Network connection
- HTTP server interface for lock and alert actions

### 4.2 Microcontroller-Based Unit

- PIC16F877A microcontroller
- PIR motion sensor
- Voltage sensor module
- 2-channel relay module
- Solenoid lock
- Buzzer
- LEDs
- Logic level converter
- External power supply
- Backup battery switching circuit

---

## 5. Repository Structure

```text
Bank-Security-System/
│
├── README.md
│
├── mobile_app/
│   ├── lib/
│   │   ├── main.dart
│   │   ├── firebase_options.dart
│   │   ├── splash_screen.dart
│   │   ├── alerts_page.dart
│   │   ├── alert_details_page.dart
│   │   ├── notification_service.dart
│   │   └── voltage_sensor_tab.dart
│   ├── assets/
│   │   └── images/
│   │       └── logo.png
│   └── pubspec.yaml
│
├── raspberry_pi/
│   ├── main.py
│   ├── requirements.txt
│   ├── models/
│   │   ├── yunet.onnx
│   │   └── w600k_mbf.onnx
│   └── config.example.env
│
├── hardware/
│   ├── pic_firmware/
│   │   ├── main.c
│   │   └── project_files/
│   ├── schematics/
│   └── pcb/
│
├── notebooks/
│   └── model_finetuning_and_results.ipynb
│
└── docs/
    ├── diagrams/
    ├── screenshots/
    ├── test_results/
    └── references/
```

---


## 🧩 Components
### 4.1 Linux-Based Unit

- Raspberry Pi
- Camera module
- Python runtime
- OpenCV
- ONNX face recognition models
- Network connection
- HTTP server interface for lock and alert actions

### 4.2 Microcontroller-Based Unit

- PIC16F877A microcontroller
- PIR motion sensor
- Voltage sensor module
- 2-channel relay module
- Solenoid lock
- Buzzer
- LEDs
- Logic level converter
- External power supply
- Backup battery switching circuit

---


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

**Communication with Raspberry Pi:**
The PIC continuously sends data to the Raspberry Pi over UART. This includes the live ADC voltage reading so the Pi can forward power statistics to the app in real time, and trigger signals when specific conditions are met (motion detected after hours, power below threshold). The Pi reads these signals and decides whether to capture an image, send an alert to the database, or trigger the alarm and lock.

---


## 5.🗂️ Repository Structure

```text
Bank-Security-System/
│
├── README.md
│
├── mobile_app/
│   ├── lib/
│   │   ├── main.dart
│   │   ├── firebase_options.dart
│   │   ├── splash_screen.dart
│   │   ├── alerts_page.dart
│   │   ├── alert_details_page.dart
│   │   ├── notification_service.dart
│   │   └── voltage_sensor_tab.dart
│   ├── assets/
│   │   └── images/
│   │       └── logo.png
│   └── pubspec.yaml
│
├── raspberry_pi/
│   ├── main.py
│   ├── requirements.txt
│   ├── models/
│   │   ├── yunet.onnx
│   │   └── w600k_mbf.onnx
│   └── config.example.env
│
├── hardware/
│   ├── pic_firmware/
│   │   ├── main.c
│   │   └── project_files/
│   ├── schematics/
│   └── pcb/
│
├── notebooks/
│   └── model_finetuning_and_results.ipynb
│
└── docs/
    ├── diagrams/
    ├── screenshots/
    ├── test_results/
    └── references/
```

---

## 6. Software Installation and Replicability Steps

This section explains how to reproduce the software setup for each unit in the system.

---

## 6.1 Raspberry Pi / Linux-Based Unit Setup

The Raspberry Pi unit is responsible for image capture, face recognition, communication with the cloud database, and receiving lock/unlock actions from the mobile application.

### 6.1.1 Required Software

- Raspberry Pi OS or any Linux-based OS
- Python 3.9 or newer
- pip
- OpenCV
- NumPy
- ONNX Runtime
- Supabase Python client
- Flask or FastAPI for local HTTP endpoints

### 6.1.2 Installation Steps

Update the system:

```bash
sudo apt update
sudo apt upgrade -y
```

Install Python and required system packages:

```bash
sudo apt install python3 python3-pip python3-venv git -y
sudo apt install libgl1 libglib2.0-0 -y
```

Clone the project repository:

```bash
git clone https://github.com/your-username/Bank-Security-System.git
cd Bank-Security-System/raspberry_pi
```

Create and activate a virtual environment:

```bash
python3 -m venv venv
source venv/bin/activate
```

Install Python dependencies:

```bash
pip install -r requirements.txt
```

Example `requirements.txt`:

```text
opencv-python
numpy
onnxruntime
supabase
python-dotenv
flask
requests
```

Create a local environment file:

```bash
cp config.example.env .env
```

Edit `.env` and add the required project keys:

```text
SUPABASE_URL=your_supabase_project_url
SUPABASE_ANON_KEY=your_supabase_anon_key
ALERT_BUCKET=alerts
```


### 6.1.3 Model Files

Place the ONNX model files inside:

```text
raspberry_pi/models/
```

Expected files:

```text
yunet.onnx
w600k_mbf.onnx
```

The face recognition pipeline uses:

1. Camera frame capture
2. Face detection
3. Face embedding extraction
4. Comparison with stored embeddings
5. Classification as authorized or unauthorized
6. Alert upload to Supabase if needed

### 6.1.4 Running the Raspberry Pi Unit

Run the main Raspberry Pi script:

```bash
python main.py
```

If a local server is used for mobile door commands, the following endpoints should be active:

```text
http://<raspberry-pi-ip>:5000/lock_on
http://<raspberry-pi-ip>:5000/lock_off
http://<raspberry-pi-ip>:5000/alert_action
```

These endpoints are used by the mobile application to control the lock and trigger safety actions.

---

## 6.2 Microcontroller-Based Unit Setup

The PIC16F877A unit handles low-level embedded control. It reads digital and analog inputs, controls relays, activates alarm outputs, and sends/receives signals from the Raspberry Pi.

### 6.2.1 Required Software

Use one of the following:

- MikroC PRO for PIC
- MPLAB X IDE with XC8 compiler

### 6.2.2 Required Hardware Connections

| PIC Pin | Function |
|---|---|
| RA0 / AN0 | Voltage sensor analog input |
| RB1 | PIR motion sensor input |
| RB2 | Additional digital condition input |
| RD0 | Relay / solenoid lock control |
| RD1 | Alarm or status output |
| RD2 | Low-voltage warning output |
| RD3 | Security or motion-related output |
| RD4 | Lock/unlock-related output |
| RC6 / TX | UART transmit |
| RC7 / RX | UART receive |

### 6.2.3 Firmware Replication Steps

Open the firmware project:

```text
hardware/pic_firmware/
```

Compile the firmware using MikroC or XC8.

For MikroC:

1. Open MikroC PRO for PIC.
2. Create or open the PIC16F877A project.
3. Add `main.c`.
4. Select the correct oscillator frequency.
5. Build the project.
6. Generate the HEX file.

For MPLAB X with XC8:

1. Open MPLAB X.
2. Create a new standalone project.
3. Select device: `PIC16F877A`.
4. Select compiler: `XC8`.
5. Add the firmware source files.
6. Build the project.
7. Generate the HEX file.

### 6.2.4 Programming the PIC

Use a PIC programmer such as PICkit.

Steps:

1. Connect the PIC programmer to the PIC16F877A.
2. Load the generated `.hex` file.
3. Program the microcontroller.
4. Power the circuit.
5. Test each input and output.

### 6.2.5 Embedded Control Logic

The microcontroller performs the following actions:

#### Voltage Monitoring

The voltage sensor is connected to RA0 / AN0.

If the measured voltage drops below the selected threshold, the system:

- Activates the warning output.
- Enables backup battery indication.
- Sends or triggers a power-fault condition.
- Allows the cloud/mobile side to display the outage state.

#### PIR Motion Detection

If PIR motion is detected in a restricted area:

- The alarm output is activated.
- The Raspberry Pi can capture evidence.
- An intrusion alert is uploaded to Supabase.
- The mobile application receives a real-time alert.

#### Lock Control

The solenoid lock is controlled through a relay.

The lock state can be changed by:

- Local embedded logic
- Raspberry Pi decision logic
- Mobile application remote command

---

## 6.3 Mobile Application Setup

The mobile application is built using Flutter. It displays alerts, shows alert details, receives notifications, and allows the manager to control the door.

### 6.3.1 Required Software

- Flutter SDK
- Android Studio or VS Code
- Android Emulator or Android phone
- Firebase project
- Supabase project

### 6.3.2 Installation Steps

Go to the mobile application folder:

```bash
cd Bank-Security-System/mobile_app
```

Install dependencies:

```bash
flutter pub get
```

Clean previous builds if needed:

```bash
flutter clean
flutter pub get
```

Run the app:

```bash
flutter run
```

### 6.3.3 Firebase Setup

The project uses Firebase Cloud Messaging for notifications.

The file:

```text
lib/firebase_options.dart
```

is generated using FlutterFire CLI.

To regenerate it:

```bash
dart pub global activate flutterfire_cli
flutterfire configure
```

### 6.3.4 Supabase Setup

The app connects to Supabase using:

- Supabase project URL
- Supabase anon key
- `alerts` table
- `door_state` table
- `device_tokens` table
- `voltage sensor` table
- `alerts` storage bucket

Recommended tables:

#### alerts

| Column | Type | Description |
|---|---|---|
| id | int8 | Alert ID |
| category | text | `access`, `intrusion`, or `power` |
| message | text | Alert message |
| image_path | text | Stored image path |
| source_id | text | Source unit |
| location | text | Alert location |
| status | text | `new` or `reviewed` |
| created_at | timestamp | Alert creation time |

#### door_state

| Column | Type | Description |
|---|---|---|
| id | int8 | Fixed row ID, usually 1 |
| is_locked | bool | Current lock state |
| updated_at | timestamp | Last update time |
| updated_by | text | Source of update |
| last_reason | text | Reason for last state change |

#### device_tokens

| Column | Type | Description |
|---|---|---|
| token | text | FCM device token |
| platform | text | Device platform |
| updated_at | timestamp | Last token update |

#### voltage sensor

| Column | Type | Description |
|---|---|---|
| id | int8 | Reading ID |
| voltage | float8 | Measured voltage |
| adc_value | int4 | ADC reading |
| status | text | `NORMAL`, `LOW`, or `POWER_OUTAGE` |
| battery_active | bool | Backup battery state |
| created_at | timestamp | Reading time |

---

## 7. Machine Learning Pipeline

The system uses camera-based face recognition to detect whether a person is authorized or unauthorized.

### 7.1 ML Pipeline Steps

```text
Capture image
      |
      v
Detect face
      |
      v
Extract face embedding
      |
      v
Compare with stored embeddings
      |
      v
Classify person
      |
      v
Trigger access decision
```

### 7.2 ML Model Information

### 3. ML Model —🤗 **Model on HuggingFace:** [Hagar633/face-recognition-svc](https://huggingface.co/Hagar633/face-recognition-svc)

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



| Item | Description |
|---|---|
| Face detector | YuNet ONNX model |
| Embedding model | ONNX face embedding model |
| Input data | Face images captured from camera or dataset |
| Output | Authorized / Unauthorized classification |
| Deployment device | Raspberry Pi / Linux-based unit |
| Inference framework | ONNX Runtime |
| Main libraries | OpenCV, NumPy, ONNX Runtime |

---

## 8. Required Notebook

The final codebase includes the notebook:

```text
notebooks/model_finetuning_and_results.ipynb
```

This notebook documents the data, model, fine-tuning or calibration process, evaluation results, statistics, and visualizations.

### 8.1 Notebook Contents

The notebook should include the following sections:

#### 1. Dataset Overview

- Number of enrolled persons
- Number of images per person
- Total number of images
- Image dimensions
- Example images
- Class distribution

#### 2. Preprocessing

- Face detection
- Cropping
- Resizing
- Normalization
- Embedding generation

#### 3. Model Details

- Face detection model type
- Face embedding model type
- Model file size
- Input shape
- Output embedding size
- Similarity metric
- Threshold used for recognition

#### 4. Fine-Tuning / Calibration Results

If full fine-tuning was performed, include:

- Training accuracy
- Validation accuracy
- Loss curves
- Hyperparameters
- Batch size
- Learning rate
- Number of epochs

If embedding-based recognition was used without full model fine-tuning, include:

- Enrollment results
- Similarity score distribution
- Selected recognition threshold
- False accept cases
- False reject cases
- Recognition accuracy on test images

#### 6. Final ML Evaluation Summary

Example table:

| Metric | Value |
|---|---|
| Total images | To be filled |
| Embedding model size | To be filled |
| Average inference time | To be filled |
| Recognition threshold | To be filled |
| Test accuracy | To be filled |
| False accept rate | To be filled |
| False reject rate | To be filled |

---

## 9. Final Implementation Results

The implemented system successfully integrates the embedded unit, Raspberry Pi unit, cloud database, notification service, and mobile application.

### 9.1 Access Control Result

When an unauthorized face is detected:

- The system classifies the person as unauthorized.
- The door remains locked.
- An alert is inserted into the Supabase `alerts` table.
- The captured image is uploaded to Supabase Storage.
- The mobile application displays the alert in the Access tab.
- The manager receives a notification.

### 9.2 Intrusion Detection Result

When PIR motion is detected after hours:

- The system triggers an intrusion event.
- Alarm indicators are activated.
- The Raspberry Pi captures image evidence.
- An intrusion alert is sent to the mobile application.
- The manager can review the event and control the door.

### 9.3 Power Monitoring Result

When the voltage drops below the defined threshold:

- The PIC detects a low-voltage or outage condition.
- The backup battery indicator is activated.
- A power alert is uploaded to the cloud.
- The mobile app displays the event in the Power tab.
- Live voltage readings are shown in the Voltage tab.

### 9.4 Remote Door Control Result

The mobile application allows the manager to:

- View current door state.
- Lock the door.
- Unlock the door.
- Send a lock command to the Raspberry Pi.
- Update the lock state in Supabase.

The Raspberry Pi receives door commands using HTTP endpoints:

```text
/lock_on
/lock_off
/alert_action
```

### 9.5 Mobile Application Result

The Flutter application provides:

- Splash screen
- Real-time alert list
- Alert details page
- Access alerts tab
- Intrusion alerts tab
- Power alerts tab
- Voltage monitoring tab
- Alert status update
- Door lock/unlock control
- FCM notification support
- Voltage chart
- Power stability percentage
- Outage rate percentage
- Average voltage display
- Battery backup status

---

## 10. Demo Scenarios

The following demo scenarios are supported:

1. Authorized user access
2. Unauthorized user detection
3. Motion intrusion detection
4. Power outage detection
5. Remote door lock
6. Remote door unlock
7. Real-time voltage monitoring
8. Mobile notification reception
9. Alert review and status update

---

## 11. Running the Full System

To run the complete system:

### Step 1: Start Supabase and Firebase Services

Make sure the following are configured:

- Supabase database tables
- Supabase storage bucket
- Supabase real-time enabled tables
- Firebase Cloud Messaging project
- Flutter Firebase options

### Step 2: Program the PIC

Upload the compiled HEX file to the PIC16F877A.

### Step 3: Start the Raspberry Pi Unit

```bash
cd raspberry_pi
source venv/bin/activate
python main.py
```

### Step 4: Run the Mobile App

```bash
cd mobile_app
flutter clean
flutter pub get
flutter run
```


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

### Step 5: Test the Scenarios

Test the following:

- Face recognition
- Unauthorized access alert
- PIR intrusion alert
- Voltage drop alert
- Door lock command
- Door unlock command
- Notification reception
- Live voltage visualization

---

## 12. Security Notes

- Do not publish real Supabase keys, Firebase keys, service account files, or private credentials in a public repository.
- Use `.env` files for local secrets.
- Add secret files to `.gitignore`.
- Use Supabase Row Level Security policies.
- Restrict write access to sensitive tables.
- Validate commands received by the Raspberry Pi before controlling the lock.

Recommended `.gitignore` entries:

```text
.env
*.env
serviceAccountKey.json
google-services.json
GoogleService-Info.plist
__pycache__/
venv/
build/
.dart_tool/
```

---

## 13. References

Reference papers, diagrams, and implementation notes are stored in:

```text
docs/references/
docs/diagrams/
docs/test_results/
```

---


## 🔗 Links

- 🐳 Docker Hub: [hagar633/bank_sys](https://hub.docker.com/r/hagar633/bank_sys)
- 🤗 HuggingFace Model: [Hagar633/face-recognition-svc](https://huggingface.co/Hagar633/face-recognition-svc)
- 💻 GitHub: [yaramahmoudd11/Bank-Security-System](https://github.com/yaramahmoudd11/Bank-Security-System)

---

## 14. Authors

- Yara Mahmoud
- Filopater Emad
- Hagar Alsherbiny


