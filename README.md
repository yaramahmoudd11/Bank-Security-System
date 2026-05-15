Bank Smart Security System

An AI-powered smart security system for banks and restricted areas using embedded systems, machine learning, IoT, and real-time mobile monitoring.

Project Overview

This project combines a PIC16F877A microcontroller, Raspberry Pi, camera-based face recognition, sensors, relay-controlled locking, cloud services, and a mobile application to detect unauthorized access and send real-time alerts.

The system is designed to improve security automation by detecting abnormal events, controlling a solenoid lock, and notifying the user through a mobile app.

Main Features

* Face recognition access control
* Unauthorized-person detection
* PIR motion detection
* Voltage and power-fault monitoring
* Relay-controlled solenoid lock
* Buzzer and LED alarm outputs
* Mobile application alerts
* Cloud database integration
* Live data streaming
* Remote lock/unlock control

System Architecture

Sensors / Camera
      ↓
PIC16F877A + Raspberry Pi
      ↓
Machine Learning Processing
      ↓
Cloud Database
      ↓
Mobile Application
      ↓
Security Actions

Hardware Components

* PIC16F877A microcontroller
* Raspberry Pi
* Camera module
* PIR motion sensor
* Voltage sensor module
* 2-channel relay module
* Solenoid lock
* Logic level converter
* Buzzer
* LEDs
* Power supply connections

Repository Structure

Bank-Security-System/
│
├── mobile_app/        # Flutter mobile application
├── raspberry_pi/      # Raspberry Pi scripts
├── hardware/          # PIC firmware and hardware files
├── ml_model/          # Face recognition / embedding system
├── docs/
│   ├── diagrams/      # System architecture and input/output diagrams
│   ├── schematics/    # KiCad schematic and PCB files
│   └── references/    # Literature review papers
│
└── README.md

Machine Learning Feature

The system uses camera input for face recognition.

Basic pipeline:

Capture image
Detect face
Generate face embedding
Compare with stored database
Classify person as authorized or unauthorized
Trigger the suitable security action

Embedded System Logic

The PIC16F877A handles low-level control.

RA0/AN0 → Voltage sensor input
RB1     → Digital input condition
RB2     → Digital input condition
RD0     → Output control signal
RD1     → Alarm/status output
RD2     → Low-voltage warning output
RD3     → Security/motion-related output
RD4     → Lock/unlock-related output

Safety-Critical Scenarios

Unauthorized Access

If an unauthorized face is detected, the system keeps the door locked, activates alarm indicators, captures evidence, and sends an alert to the mobile app.

PIR Motion Detection

If motion is detected in a restricted area, the system activates the alarm, captures an image, uploads the event, and notifies the user.

Power Fault Detection

If the voltage drops below the threshold, the system activates a warning output and sends a power-fault alert.

Remote Door Locking and Unlocking

The user can lock or unlock the door from the mobile application. The command is sent to the system and the lock state is updated in the cloud database.

Software Stack

Embedded Side

* Embedded C
* PIC16F877A
* MikroC / XC8

Raspberry Pi Side

* Python
* OpenCV
* ONNX model inference
* Face embedding system

Mobile Application

* Flutter
* Supabase
* Firebase Cloud Messaging

Documentation

Project documentation is available inside:

docs/

It includes:

* System architecture diagram
* Input/output diagram
* Electrical schematic
* PCB-related files
* Reference papers

Demo Scenarios

* Authorized user access
* Unauthorized user detection
* Motion intrusion detection
* Power outage detection
* Remote door lock/unlock
* Live data streaming to mobile app

References

Reference papers used for the literature review are included in:

docs/references/

Authors

* Yara Mahmoud
* Filopater Emad
* Hagar Alsherbiny

License

This project is developed for educational and academic purposes.