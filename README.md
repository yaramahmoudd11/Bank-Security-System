# 🏦 Bank Smart Security System

An AI-powered smart security system for banks and restricted areas using embedded systems, machine learning, IoT, cloud services, Docker deployment, and real-time mobile monitoring.

---

## 📸 Project Overview

The **Bank Smart Security System** is designed to automate security monitoring in restricted areas such as bank rooms, storage areas, locker rooms, and sensitive access zones.

The system combines:

* A **Raspberry Pi Linux-based unit** for camera processing, face recognition, server communication, GPIO handling, Docker deployment, and cloud integration.
* A **PIC16F877A microcontroller-based unit** for low-level sensor reading, voltage monitoring, relay control, buzzer control, LED indication, and lock control.
* A **Flutter mobile application** for real-time alerts, door control, voltage visualization, outage statistics, and event review.
* **Supabase** for database, storage, and real-time streams.
* **Firebase Cloud Messaging** for push notifications.
* **HuggingFace** for hosting the trained face-recognition classifier/model files.
* **Docker Hub** for Raspberry Pi deployment.

The system detects unauthorized access, after-hours motion intrusion, and power-fault conditions, then sends real-time alerts to the manager through the mobile application.

---

## 🧠 High-Level System Flow

### Face Recognition Flow

```text
Camera → Face Detection → ArcFace Embedding → SVC Classifier
                                                      |
                                                      v
                                              Known? → Log access
                                              Unknown? → Alert App → User decides action
                                                                          |
                                                                          v
                                                              HTTP request to Pi → Alarm / Lock
```

### Sensor and Power Monitoring Flow

```text
PIR Sensor → PIC16F877A → Close door + Light room → Signal Pi → Capture image → Alert App
Voltage Sensor → PIC16F877A → Power statistics → Raspberry Pi → Alert App
```

---

## ✅ Main Features

* Face recognition access control
* Authorized and unauthorized person classification
* PIR motion detection
* Voltage and power-fault monitoring
* Relay-controlled solenoid lock
* Buzzer and LED alarm indicators
* Raspberry Pi camera evidence capture
* Supabase cloud database integration
* Supabase storage for alert images
* Firebase Cloud Messaging notifications
* Real-time mobile alert streaming
* Remote door lock/unlock control
* Live voltage monitoring and visualization
* Power stability percentage
* Outage rate percentage
* Average voltage display
* Backup battery activity indication
* Alert status tracking: `new` and `reviewed`
* Docker deployment on Raspberry Pi
* HuggingFace-hosted face-recognition model files

---

## 🏗️ Final System Architecture

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

## 🧩 Hardware Components

### Raspberry Pi / Linux-Based Unit

* Raspberry Pi 4
* Camera module
* Python runtime
* OpenCV
* ONNX face recognition models
* Network connection
* GPIO pins for PIR, power outage signal, alarm, and door lock
* Flask HTTP server interface for lock and alert actions
* Docker runtime for containerized deployment

### PIC16F877A Microcontroller Unit

* PIC16F877A microcontroller
* PIR motion sensor
* Voltage sensor module
* 2-channel relay module
* Solenoid lock
* Buzzer
* LEDs
* Logic level converter
* External power supply
* Backup battery switching circuit

---
## 🗂️ Repository Structure

```text
Bank-Security-System/
│
├── README.md
│
├── demo/
│   ├── demo_video_link.txt
│   └── .gitkeep
│
├── docs/
│   ├── diagrams/
│   ├── references/
│   └── schematics/
│
├── face_systems/
│   ├── main.py
│   ├── down.py
│   └── models/
│
├── hardware/
│   ├── pcb/
│   ├── pic_microcontroller/
│   └── wiring_diagrams/
│
├── mobile_app/
│   └── bank_alert_app/
│       ├── lib/
│       ├── android/
│       ├── ios/
│       ├── assets/images/
│       ├── supabase/
│       ├── test/
│       ├── web/
│       ├── windows/
│       ├── linux/
│       ├── macos/
│       ├── pubspec.yaml
│       └── pubspec.lock
│
└── pi/
    ├── Dockerfile
    ├── requirements.txt
    └── run.sh
```

---

## 🧠 Raspberry Pi 4 Unit

The Raspberry Pi acts as the main intelligent processing unit. It handles camera capture, face recognition, GPIO interaction, mobile app commands, Supabase communication, and alert generation.

### Main Tasks

| Task           | Description                                                         |
| -------------- | ------------------------------------------------------------------- |
| Camera loop    | Captures frames continuously using the Pi camera                    |
| Detection loop | Runs face detection and face recognition                            |
| GPIO loop      | Monitors PIR signal and power outage signal from the PIC            |
| Cloud update   | Uploads alerts, images, voltage data, and system states to Supabase |
| HTTP server    | Receives lock/unlock/alarm commands from the mobile app             |

### Flask API Endpoints

| Endpoint            | Action                         |
| ------------------- | ------------------------------ |
| `GET /alert_action` | Trigger alarm for a short time |
| `GET /lock_on`      | Lock the vault/security door   |
| `GET /lock_off`     | Unlock the vault/security door |

---

## ⚙️ GPIO Pin Map — Raspberry Pi 4

| Pin (BCM) | Role                               |
| --------- | ---------------------------------- |
| GPIO 23   | PIR sensor input                   |
| GPIO 24   | Power outage signal input from PIC |
| GPIO 18   | Alarm output                       |
| GPIO 27   | Door lock output                   |

---

## 🔌 PIC16F877A Microcontroller Unit

The PIC16F877A unit handles low-level embedded control. It reads analog and digital inputs, controls relays, activates alarm outputs, monitors voltage, and controls lock-related outputs.

### PIC Pin Mapping

| PIC Pin   | Function                                             |
| --------- | ---------------------------------------------------- |
| RA0 / AN0 | Voltage sensor analog input                          |
| RB1       | PIR motion sensor input / digital security condition |
| RB2       | Additional digital input condition                   |
| RC6 / TX  | UART transmit to Raspberry Pi                        |
| RC7 / RX  | UART receive from Raspberry Pi                       |
| RD0       | Relay / solenoid lock control                        |
| RD1       | Alarm or status output                               |
| RD2       | Low-voltage warning output                           |
| RD3       | Security or motion-related output                    |
| RD4       | Lock/unlock-related output                           |


---

## 🧱 PIC Driver-Based Firmware Structure

The PIC firmware is planned to be organized using a driver-based structure for readability and easier debugging.


## 🧪 Embedded Control Logic

### Voltage Monitoring

The voltage sensor is connected to `RA0/AN0`.

If the measured voltage drops below the selected threshold:

* The low-voltage warning output is activated.
* Backup battery indication can be enabled.
* A power-fault condition is triggered.
* The mobile application displays the outage state through cloud updates.

### PIR Motion Detection

If PIR motion is detected in a restricted area:

* The alarm output is activated.
* The Raspberry Pi captures image evidence.
* An intrusion alert is uploaded to Supabase.
* The mobile application receives a real-time notification.

### Lock Control

The solenoid lock is controlled through a relay.

The lock state can be changed by:

* Local embedded logic
* Raspberry Pi decision logic
* Mobile application remote command

---

## 🤖 Machine Learning Pipeline

The system uses camera-based face recognition to detect whether a person is authorized or unauthorized.

### Pipeline

```text
Camera Frame
      |
      v
YuNet Face Detector
      |
      v
Crop Face
      |
      v
ArcFace Embedding Model
      |
      v
512-D Embedding
      |
      v
SVC Classifier
      |
      v
Name / UNKNOWN
```

### Model on HuggingFace

🤗 **HuggingFace Model:** [Hagar633/face-recognition-svc](https://huggingface.co/Hagar633/face-recognition-svc)

### Model Files

| File                 | Description                          |
| -------------------- | ------------------------------------ |
| `classifier.pkl`     | Trained SVC model saved using joblib |
| `yunet.onnx`         | YuNet face detector                  |
| `w600k_mbf.onnx`     | ArcFace embedding model              |
| `det_500m.onnx`      | Additional detection model           |
| `mobilefacenet.onnx` | Lightweight face model               |

Download all model files from HuggingFace and place them in the models folder before running.

Recommended model folder:

```text
face_systems/models/
```

### Standalone Classifier Example

```python
import joblib

clf = joblib.load("models/classifier.pkl")
prediction = clf.predict(embedding.reshape(1, -1))
```

Confidence threshold:

```text
0.70
```

Predictions below this threshold are treated as `UNKNOWN`.

---

## 🐳 Docker Setup

### Docker Hub Image

```bash
sudo docker pull hagar633/bank_sys2:latest
```

### Build Locally

```bash
cd raspberry_pi/
sudo docker build -t bank_sys .
```

### Run on Raspberry Pi

```bash
sudo ./run.sh
```

The `run.sh` script mounts Raspberry Pi system libraries and Python virtual environment into the container so hardware dependencies such as `picamera2`, `libcamera`, `GPIO`, and `cv2` can work correctly.

Example run command:

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

### Push to Docker Hub

```bash
sudo docker login
sudo docker tag bank_sys hagar633/bank_sys2:latest
sudo docker push hagar633/bank_sys2:latest
```

---

## 📦 Dependencies

### Python Dependencies

* `opencv-python` — face detection and embedding preprocessing
* `numpy` — numerical operations
* `scikit-learn` / `joblib` — SVC classifier
* `picamera2` — Raspberry Pi camera interface
* `RPi.GPIO` — GPIO control
* `flask` — HTTP API
* `supabase` — cloud database client
* `requests` — HTTP requests
* `python-dotenv` — environment variables

### System Dependencies

* `libcamera`
* Raspberry Pi OS Bookworm 64-bit
* PIC16F877A with custom firmware
* Docker Engine

---

## 📱 Mobile Application Setup

The mobile application is built using Flutter. It displays alerts, receives notifications, shows voltage statistics, and allows the manager to control the door.

### Required Software

* Flutter SDK
* Android Studio or VS Code
* Android Emulator or Android phone
* Firebase project
* Supabase project

### Installation Steps

Go to the mobile app folder:

```bash
cd Bank-Security-System/mobile_app/bank_alert_app
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

---

## ☁️ Supabase Setup

The app connects to Supabase using:

* Supabase project URL
* Supabase anon key
* `alerts` table
* `door_state` table
* `device_tokens` table
* `voltage sensor` table
* `alerts` storage bucket

### Suggested Tables

#### alerts

| Column     | Type      | Description                       |
| ---------- | --------- | --------------------------------- |
| id         | int8      | Alert ID                          |
| category   | text      | `access`, `intrusion`, or `power` |
| message    | text      | Alert message                     |
| image_path | text      | Stored image path                 |
| source_id  | text      | Source unit                       |
| location   | text      | Alert location                    |
| status     | text      | `new` or `reviewed`               |
| created_at | timestamp | Alert creation time               |
| extra_data | jsonb     | Additional event information      |

#### door_state

| Column      | Type      | Description                  |
| ----------- | --------- | ---------------------------- |
| id          | int8      | Fixed row ID, usually 1      |
| is_locked   | bool      | Current lock state           |
| updated_at  | timestamp | Last update time             |
| updated_by  | text      | Source of update             |
| last_reason | text      | Reason for last state change |

#### device_tokens

| Column     | Type      | Description       |
| ---------- | --------- | ----------------- |
| token      | text      | FCM device token  |
| platform   | text      | Device platform   |
| updated_at | timestamp | Last token update |

#### voltage sensor

| Column         | Type      | Description                        |
| -------------- | --------- | ---------------------------------- |
| id             | int8      | Reading ID                         |
| voltage        | float8    | Measured voltage                   |
| adc_value      | int4      | ADC reading                        |
| status         | text      | `NORMAL`, `LOW`, or `POWER_OUTAGE` |
| battery_active | bool      | Backup battery state               |
| created_at     | timestamp | Reading time                       |

---

## 📓 Required Notebook

The final codebase includes:

```text
notebooks/model_finetuning_and_results.ipynb
```

The notebook should document:

* Dataset overview
* Number of enrolled persons
* Number of images per person
* Image preprocessing steps
* Face detection and embedding generation
* Model details
* Recognition threshold
* Similarity score distribution
* Accuracy or evaluation results
* Voltage readings visualization
* Alert category distribution
* Door action statistics
* Inference time analysis
* Power or response-time analysis if measured

---

## ✅ Final Implementation Results

### Access Control

When an unauthorized face is detected:

* The system classifies the person as unauthorized.
* The door remains locked.
* An alert is inserted into the Supabase `alerts` table.
* The captured image is uploaded to Supabase Storage.
* The mobile application displays the alert in the Access tab.
* The manager receives a notification.

### Intrusion Detection

When PIR motion is detected:

* The system triggers an intrusion event.
* Alarm indicators are activated.
* The Raspberry Pi captures image evidence.
* An intrusion alert is sent to the mobile application.
* The manager can review the event and control the door.

### Power Monitoring

When the voltage drops below the defined threshold:

* The PIC detects a low-voltage or outage condition.
* The backup battery indicator is activated.
* A power alert is uploaded to the cloud.
* The mobile app displays the event in the Power tab.
* Live voltage readings are shown in the Voltage tab.

### Mobile Application

The Flutter application provides:

* Splash screen
* Real-time alert list
* Alert details page
* Access alerts tab
* Intrusion alerts tab
* Power alerts tab
* Voltage monitoring tab
* Alert status update
* Door lock/unlock control
* FCM notification support
* Voltage chart
* Power stability percentage
* Outage rate percentage
* Average voltage display
* Battery backup status

---

## 🎬 Demo Scenarios

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

## 🚀 Running the Full System

### Step 1: Configure Supabase and Firebase

Make sure the following are configured:

* Supabase database tables
* Supabase storage bucket
* Supabase real-time enabled tables
* Firebase Cloud Messaging project
* Flutter Firebase options

### Step 2: Program the PIC

Upload the compiled HEX file to the PIC16F877A.

### Step 3: Start the Raspberry Pi Unit

```bash
cd Bank-Security-System
source venv/bin/activate
python face_systems/main.py
```

### Step 4: Run the Mobile App

```bash
cd mobile_app/bank_alert_app
flutter clean
flutter pub get
flutter run
```

### Step 5: Test the Scenarios

Test the following:

* Face recognition
* Unauthorized access alert
* PIR intrusion alert
* Voltage drop alert
* Door lock command
* Door unlock command
* Notification reception
* Live voltage visualization

---

## 🔐 Security Notes

* Do not publish real Supabase keys, Firebase keys, service account files, or private credentials in a public repository.
* Use `.env` files for local secrets.
* Add secret files to `.gitignore`.
* Use Supabase Row Level Security policies.
* Restrict write access to sensitive tables.
* Validate commands received by the Raspberry Pi before controlling the lock.

Recommended `.gitignore` entries:

```text
.env
*.env
serviceAccountKey.json
firebase-service-account.json
*firebase-adminsdk*.json
google-services.json
GoogleService-Info.plist
node_modules/
__pycache__/
venv/
build/
.dart_tool/
*.log
```

---

## 📚 Documentation

Project documentation is stored in:

```text
docs/
```

It includes:

* System architecture diagram
* Input/output diagram
* Electrical schematic
* PCB documentation
* Reference papers
* Screenshots
* Test results

---

## 🔗 Links

* 🐳 Docker Hub: [hagar633/bank_sys](https://hub.docker.com/r/hagar633/bank_sys2)
* 🤗 HuggingFace Model: [Hagar633/face-recognition-svc](https://huggingface.co/Hagar633/face-recognition-svc)
* 💻 GitHub: [yaramahmoudd11/Bank-Security-System](https://github.com/yaramahmoudd11/Bank-Security-System)

---

## 👥 Authors

* Yara Mahmoud
* Filopater Emad
* Hagar Alsherbiny

---

## 📄 License

This project is developed for educational and academic purposes.
