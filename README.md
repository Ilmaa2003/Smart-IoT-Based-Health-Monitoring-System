#  Smart IoT Health Monitoring System

A real-time IoT-based health monitoring system built with **ESP32**, **MAX30105 Pulse Sensor**, **Adafruit AHTX0 Sensor**, **Firebase Realtime Database**, and a custom-built **Android mobile app** for real-time data visualization.

![IoT Image](https://raw.githubusercontent.com/AmjadAzward/IoT-Coursework-HNDSE24.2F-Group-03/main/Images/01.jpg)

![IoT Image 2](https://raw.githubusercontent.com/AmjadAzward/IoT-Coursework-HNDSE24.2F-Group-03/main/Images/02.jpg)

![IoT Image 3](https://raw.githubusercontent.com/AmjadAzward/IoT-Coursework-HNDSE24.2F-Group-03/main/Images/03.jpg)

![IoT Image 4](https://raw.githubusercontent.com/AmjadAzward/IoT-Coursework-HNDSE24.2F-Group-03/main/Images/04.jpg)

![IoT Image 5](https://raw.githubusercontent.com/AmjadAzward/IoT-Coursework-HNDSE24.2F-Group-03/main/Images/05.jpg)

##  About the Project

This project monitors key health parameters such as:
- Heart Rate (BPM)
- Blood Oxygen (SpO₂)
- Body Temperature
- Humidity
- Cough Detection (via algorithm)
- Air Quality
  
The data is transmitted from ESP32 to Firebase in real time and displayed on a dedicated Android app, making it ideal for remote health tracking.

---

##  Features

-  Real-time sensor data logging from ESP32
-  Firebase Realtime Database integration
-  Custom Android mobile app to display health vitals
-  Alert system for abnormal readings (upcoming)
-  Easily extendable for other health sensors or platforms


---

##  Software Requirements

- Arduino IDE
- Android Studio
- Firebase Console
- Required Libraries for Arduino:
  - `WiFi.h`
  - `Firebase_ESP_Client.h`
  - `FirebaseJson.h`
  - `MAX30105.h`
  - `spo2_algorithm.h`
  - `heartRate.h`
  - `Adafruit_AHTX0.h`
- Android App dependencies:
  - Firebase Realtime Database SDK

---

##  Arduino IDE Installation

1. Download Arduino IDE: [https://www.arduino.cc/en/software](https://www.arduino.cc/en/software)
2. Add ESP32 board URL in Preferences:
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json

markdown
Copy
Edit
3. Install ESP32 Board from Boards Manager.
4. Install required libraries via **Library Manager**.

---

##  Firebase Setup

1. Create a Firebase project from [Firebase Console](https://console.firebase.google.com/)
2. Enable **Realtime Database**
3. Copy:
- **Web API Key**
- **Database URL**
4. Update rules for testing:
  
{
  "rules": {
    ".read": true,
    ".write": true
  }
}

Use the API key and URL in both Arduino code and Android app.

🧪 Installation


Open the .ino file in Arduino IDE.

Replace your credentials:

#define WIFI_SSID "YourSSID"
#define WIFI_PASSWORD "YourPassword"
#define API_KEY "YourFirebaseWebAPIKey"
#define DATABASE_URL "https://your-project-id.firebaseio.com/"
Select ESP32 board and upload the code.


---

##  About the App

This mobile app displays live health parameters collected from IoT sensors connected to an ESP32 and pushed to Firebase. It's designed for patients, doctors, or caretakers to remotely monitor:

-  Heart Rate (BPM)
-  Blood Oxygen Level (SpO₂)
-  Body Temperature
-  Humidity
-  Cough Detection (Alert)

---

##  Features

-  Real-time data sync from Firebase
-  Live vitals displayed using TextViews or Cards
-  Simple and responsive UI
-  Abnormal value alerts (future scope)
-  Works on any Android device with internet

---

## 🛠️ Tech Stack

- Java / Kotlin (select based on your app)
- Android Studio
- Firebase Realtime Database
- Material Design UI Components

---

##  Firebase Integration

1. Go to [Firebase Console](https://console.firebase.google.com/)  
2. Add a new Android app to your project  
3. Download `google-services.json` and place it in:
/app/google-services.json

4. Enable Realtime Database and set rules:
{
  "rules": {
    ".read": true,
    ".write": true
  }
}

Your Firebase structure should look like:

json

{
  "HeartRate": 78,
  "SpO2": 96,
  "Temperature": 36.5,
  "Humidity": 55,
  "CoughDetected": "No"
}


---

##  Source & GitHub Repositories for Tools/Libraries Used

| Tool / Library               | Description                                | GitHub / Source Link                                      |
|-----------------------------|--------------------------------------------|-----------------------------------------------------------|
| Arduino IDE                  | Official Arduino IDE source                 | https://github.com/arduino/Arduino                        |
| ESP32 Arduino Core           | ESP32 support for Arduino IDE               | https://github.com/espressif/arduino-esp32                |
| WiFi Library (Arduino ESP32) | WiFi support for ESP32                       | Included in esp32 Arduino Core (see above)                |
| Firebase ESP Client          | Firebase client library for ESP32            | https://github.com/mobizt/Firebase-ESP-Client             |
| FirebaseJson                | JSON parsing helper library for ESP clients | https://github.com/mobizt/Firebase-ESP-Client (included)  |
| MAX30105 Sensor Library      | Arduino library for MAX30105 sensor          | https://github.com/sparkfun/SparkFun_MAX3010_Sensor_Library |
| spo2_algorithm              | SPO2 and heart rate algorithm implementation | Often custom or embedded; some examples on GitHub; no official repo |
| Adafruit AHTX0 Library       | Sensor driver for AHT10/AHT20 temperature/humidity sensors | https://github.com/adafruit/Adafruit_AHTX0                |
| Android Studio              | Official Android IDE source                   | https://android.googlesource.com/platform/tools/studio/   |
| Firebase Android SDK        | Firebase SDK for Android                       | https://github.com/firebase/firebase-android-sdk          |

