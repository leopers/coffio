# Coffio ☕

**Coffio** is a Wi-Fi-enabled coffee maker controller built with an ESP8266, a relay, and a mobile-friendly web app. It lets you brew coffee manually or schedule it for a specific time — all from your iPhone. Add it to your home screen and enjoy a native app feel without the App Store.

---

## 🚀 Features

* ☕ Manual "Make Coffee Now" button
* ⏰ Scheduled brewing (syncs with internet time via NTP)
* 🌐 Web interface hosted by the ESP8266 (LittleFS)
* 📱 Mobile-first aesthetic web app
* 📲 Add-to-home-screen support (PWA-style)
* 🔧 Modular, maintainable C++ code structure

---

## 🛠 Hardware Requirements

* 1x ESP8266 (NodeMCU, Wemos D1 Mini, etc.)
* 1x Relay Module
* A coffee maker with a mechanical on/off switch
* 5V power supply

---

## 📁 Project Structure

```
coffio/
├── data/               # Web UI files served via LittleFS
│   ├── index.html
│   ├── style.css
│   ├── script.js
│   ├── manifest.json
│   └── cat.jpg
├── include/            # Header files
│   ├── secrets.h       # Wi-Fi credentials (excluded from git)
│   ├── web_server.hpp
│   └── scheduler.hpp
├── src/
│   ├── main.cpp        # Project entry point
│   ├── web_server.cpp
│   └── scheduler.cpp
├── .gitignore
└── platformio.ini      # PlatformIO config
```

---

## 🔧 Setup Instructions

### 1. Clone the repo

```bash
git clone https://github.com/leopers/coffio.git
cd coffio
```

### 2. Create your Wi-Fi credentials file

Create `include/secrets.h`:

```cpp
#pragma once
const char* ssid = "YourWiFi";
const char* password = "YourPassword";
```

> ⚠️ This file is ignored via `.gitignore`

### 3. Upload web UI to the ESP8266

```bash
pio run --target uploadfs
```

### 4. Upload the firmware

```bash
pio run --target upload
```

### 5. Open the Serial Monitor

```bash
pio device monitor
```

Find the ESP8266 IP address.

### 6. Access Coffio in your browser

```
http://<ESP_IP_ADDRESS>
```

### 7. (Optional) Add to iPhone home screen

* Open in Safari
* Tap Share → "Add to Home Screen"
* Enjoy your Coffio app ☕

---

## 🧱 Technologies Used

* **PlatformIO + Arduino Framework**
* **LittleFS** for serving frontend
* **ESP8266WebServer**
* **NTP time sync** (`time.h`)
* **Progressive Web App (PWA)** support

---

## 📦 Roadmap / Ideas

* 🔁 Save schedules to EEPROM
* 🔔 Brew notification with tone or LED
* 🔄 OTA firmware updates
* 📊 Brew log viewer

---

## 📜 License

MIT License — do whatever you want, but share some love ☕
