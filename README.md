# 💡 Smart IoT-Based Health Monitoring System

An intelligent, real-time health monitoring solution powered by **ESP32**, seamlessly integrated with **biometric sensors** and **Firebase**. Designed with a mobile-first mindset, this project enables remote health tracking via a **custom-built Android application**.

![IoT System Image](https://raw.githubusercontent.com/Ilmaa2003/Smart-IoT-Based-Health-Monitoring-System/main/Images/01.jpg)

![IoT System Image](https://raw.githubusercontent.com/Ilmaa2003/Smart-IoT-Based-Health-Monitoring-System/main/Images/02.jpg)

![IoT System Image](https://raw.githubusercontent.com/Ilmaa2003/Smart-IoT-Based-Health-Monitoring-System/main/Images/03.jpg)

---

## 🧠 Project Summary

This IoT solution continuously captures and uploads health parameters using onboard sensors and displays the data in real time via an Android app. It aims to assist patients, caregivers, and medical professionals with **remote health monitoring**.

### 🩺 Monitored Metrics:

* ❤️ Heart Rate (BPM)
* 🫁 SpO₂ Level (Oxygen Saturation)
* 🌡️ Body Temperature
* 💦 Humidity Levels
* 🤧 Cough Events (via detection logic)
* 🌫️ Air Quality *(planned)*

---

## 🔍 Highlights

* ESP32-based sensor platform with Wi-Fi capability
* Firebase Realtime Database connectivity
* Live health metric display on Android device
* Modular design to support future sensors
* Emergency alert feature (in pipeline)

---

## ⚙️ Required Tools & Software

### Microcontroller:

* **ESP32** (Wi-Fi-enabled)

### Development Environments:

* Arduino IDE
* Android Studio
* Firebase Console

### Arduino Libraries:

```plaintext
WiFi.h
Firebase_ESP_Client.h
FirebaseJson.h
MAX30105.h
spo2_algorithm.h
heartRate.h
Adafruit_AHTX0.h
```

### Android SDK Dependencies:

* Firebase Realtime Database SDK
* Material UI Components

---

## 🚀 Setting Up the System

### 1. Arduino IDE Setup

* Install Arduino IDE: [Official Link](https://www.arduino.cc/en/software)
* Add ESP32 board URL in **Preferences**:

  ```
  https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
  ```
* Install the **ESP32 Board** via Boards Manager
* Use Library Manager to install required libraries

---

### 2. Firebase Configuration

1. Go to [Firebase Console](https://console.firebase.google.com/)
2. Create a new project
3. Enable **Realtime Database**
4. Get your:

   * Web API Key
   * Database URL
5. Set testing rules:

   ```json
   {
     "rules": {
       ".read": true,
       ".write": true
     }
   }
   ```

---

### 3. Uploading Code to ESP32

* Open the `.ino` file in Arduino IDE
* Update with your credentials:

  ```cpp
  #define WIFI_SSID "YourNetwork"
  #define WIFI_PASSWORD "YourPassword"
  #define API_KEY "YourFirebaseAPIKey"
  #define DATABASE_URL "https://your-database.firebaseio.com/"
  ```
* Select the correct ESP32 board
* Upload the code

---

## 📱 Android App Overview

A lightweight mobile app that retrieves real-time data from Firebase and presents it through a clean, modern UI. Designed for easy accessibility by patients and caretakers.

### App Features:

* Continuous syncing from Firebase
* Display of real-time metrics
* Supports low network latency
* Alert system (planned)
* Supports all Android versions with internet access

---

### Firebase App Integration

1. Add an Android app to your Firebase project
2. Download and place `google-services.json` inside:

   ```
   /app/google-services.json
   ```
3. Realtime Database rules (for testing):

   ```json
   {
     "rules": {
       ".read": true,
       ".write": true
     }
   }
   ```

### Sample Data Structure:

```json
{
  "HeartRate": 82,
  "SpO2": 97,
  "Temperature": 36.8,
  "Humidity": 57,
  "CoughDetected": "No"
}
```

---

## 📚 External Libraries & Dependencies

| Name                 | Description                          | Link                                                                  |
| -------------------- | ------------------------------------ | --------------------------------------------------------------------- |
| Arduino IDE          | IDE for programming ESP32            | [GitHub](https://github.com/arduino/Arduino)                          |
| ESP32 Core           | ESP32 support package for Arduino    | [GitHub](https://github.com/espressif/arduino-esp32)                  |
| Firebase ESP Client  | Firebase integration for ESP32       | [GitHub](https://github.com/mobizt/Firebase-ESP-Client)               |
| MAX30105 Library     | Pulse and SpO2 sensor interface      | [GitHub](https://github.com/sparkfun/SparkFun_MAX3010_Sensor_Library) |
| Adafruit AHTX0       | Temp & Humidity sensor driver        | [GitHub](https://github.com/adafruit/Adafruit_AHTX0)                  |
| Firebase Android SDK | Realtime DB SDK for Android          | [GitHub](https://github.com/firebase/firebase-android-sdk)            |
| Android Studio       | Official IDE for Android development | [Source](https://android.googlesource.com/platform/tools/studio/)     |

---

## 📈 Roadmap

* [ ] Air Quality Monitoring via MQ sensors
* [ ] Real-time notifications via FCM
* [ ] Data visualization using charts
* [ ] Medical history tracking

