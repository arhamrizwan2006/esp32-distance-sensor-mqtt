<div align="center">

<img src="https://capsule-render.vercel.app/api?type=waving&amp;color=0:6C63FF,100:00D4AA&amp;height=180&amp;section=header&amp;text=ESP32%20Distance%20Sensor%20MQTT&amp;fontSize=34&amp;fontColor=ffffff&amp;animation=fadeIn&amp;fontAlignY=38&amp;desc=Cloud-Connected%20Ultrasonic%20Telemetry&amp;descAlignY=58&amp;descSize=16" width="100%"/>

<img src="https://readme-typing-svg.demolab.com/?font=Space+Mono&amp;size=20&amp;duration=3000&amp;pause=800&amp;color=00D4AA&amp;center=true&amp;vCenter=true&amp;width=600&amp;lines=Streams+Distance+Data+via+MQTT;Live+Graphs+on+Adafruit+IO;Non-Blocking+WiFi+%2B+Reconnect+Backoff" alt="Typing SVG"/>

<br/>

![ESP32](https://img.shields.io/badge/ESP32-Wireless-00979D?style=for-the-badge&logo=espressif&logoColor=white)
![MQTT](https://img.shields.io/badge/MQTT-Cloud%20Connected-0078D4?style=for-the-badge)
![Adafruit](https://img.shields.io/badge/Adafruit%20IO-Live%20Dashboard-FF6B35?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-00D4AA?style=for-the-badge)

</div>

---

## 📡 Overview

A cloud-connected security telemetry node — an HC-SR04 ultrasonic sensor measures distance, an ESP32 processes it and streams the reading over WiFi via MQTT to an Adafruit IO dashboard for live, remote monitoring.

---

## 🎯 How It Works

```
   HC-SR04 Sensor
        ↓
   [Measure Distance]
        ↓
   [ESP32 Processes]
        ↓
   [Publish via MQTT]
        ↓
   Adafruit IO Dashboard
        ↓
     Live Graph
```

---

## ⚙️ Components

| Component | Role |
|---|---|
| 🔲 ESP32 Dev Board | WiFi-enabled main controller |
| 📏 HC-SR04 | Ultrasonic distance sensor |
| ☁️ Adafruit IO | Cloud data storage & visualization |
| 🔧 Voltage Divider (1kΩ + 2kΩ) | Steps ECHO line down to 3.3V |

---

## 🔌 Wiring

| HC-SR04 | ESP32 |
|---|---|
| VCC | 5V |
| GND | GND |
| TRIG | GPIO 5 |
| ECHO | GPIO 18 *(via voltage divider)* |

📄 Full wiring breakdown → [`docs/wiring_connections.md`](docs/wiring_connections.md)

---

## 🚀 Setup

<details>
<summary><b>Click to expand full setup steps</b></summary>

<br/>

1. **Copy** `secrets.h.example` → `secrets.h` in the same folder
2. **Fill in credentials:**
```cpp
   #define WIFI_SSID "YourNetwork"
   #define WIFI_PASS "YourPassword"
   #define AIO_USERNAME "your_username"
   #define AIO_KEY "your_api_key"
```
3. **Install libraries:**
   - `Adafruit MQTT Library`
   - `PubSubClient`
   - `WiFi` *(built-in)*
4. **Upload sketch** — `code/distance_sensor_mqtt.ino`
5. **Open Serial Monitor** at 115200 baud to view live readings
6. **Add a chart block** to your `distance` feed on the Adafruit IO dashboard

</details>

---

## 📸 Demo

### Setup
<img src="images/setup_photo.jpeg" width="60%"/>

### Live Dashboard
<img src="images/adafruit_graph.jpeg" width="60%"/>

*Real-time distance graph, data history, and a mobile-friendly view — all on Adafruit IO.*

---

## 🐛 Troubleshooting

<details>
<summary><b>Common issues & fixes</b></summary>

<br/>

| Issue | Solution |
|---|---|
| No WiFi connection | Check SSID/password in `secrets.h` |
| Data not appearing in Adafruit IO | Verify API key & feed name match |
| Sensor readings inaccurate | Check wiring, ensure 5V supply is stable |
| Reconnect loop / rate-limited | Backoff logic handles this — wait it out, don't spam reconnects |

Full breakdown → [`docs/troubleshooting.md`](docs/troubleshooting.md)

</details>

---

## 💡 Key Concepts

✅ ESP32 WiFi connectivity & MQTT publish/subscribe
✅ Blocking WiFi handshake on boot, non-blocking sensor loop after
✅ `dtostrf()` for safe payload formatting (no heap fragmentation)
✅ Exponential backoff on reconnect to respect Adafruit IO's rate limit

---

## 🔮 Possible Improvements

- 📊 Multiple sensor nodes feeding one dashboard
- 🔔 Threshold alerts (push notification on breach)
- 🔋 Deep-sleep mode between readings for battery operation
- 📱 Custom mobile dashboard instead of default Adafruit IO view

---

<div align="center">

**Author:** Arham Rizwan · 2026

<img src="https://capsule-render.vercel.app/api?type=waving&amp;color=0:00D4AA,100:6C63FF&amp;height=100&amp;section=footer" width="100%"/>

</div>
