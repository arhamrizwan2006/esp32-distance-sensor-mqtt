# 📡 ESP32 Distance Sensor with MQTT

> Cloud-connected ultrasonic distance sensor streaming real-time data to Adafruit IO  
> **Status:** ✅ Complete | **Platform:** ESP32 | **Protocol:** MQTT

![Badge](https://img.shields.io/badge/ESP32-Wireless-blue?style=flat-square)
![Badge](https://img.shields.io/badge/MQTT-Cloud%20Connected-0078D4?style=flat-square)
![Badge](https://img.shields.io/badge/Adafruit%20IO-Live%20Dashboard-FF6B35?style=flat-square)

---

## 🎯 What It Does

```
HC-SR04 Sensor → ESP32 → WiFi → Adafruit IO → Live Graph
(Measure distance)  (Process) (Connect) (Store) (Visualize)
```

Measures distance in real-time and streams data to cloud. Watch live graphs update as objects move closer/farther.

---

## ⚙️ Components

| Component | Purpose |
|-----------|---------|
| **ESP32** | WiFi-enabled microcontroller |
| **HC-SR04** | Ultrasonic distance sensor |
| **Adafruit IO** | Cloud data storage & visualization |

---

## 🚀 Quick Setup

1. **Update `secrets.h.example` → `secrets.h`**
   ```cpp
   #define WIFI_SSID "YourNetwork"
   #define WIFI_PASS "YourPassword"
   #define AIO_USERNAME "your_username"
   #define AIO_KEY "your_api_key"
   ```

2. **Install libraries:**
   - Adafruit MQTT Library
   - PubSubClient
   - WiFi (built-in)

3. **Upload & monitor** — Open Serial Monitor (115200 baud)

4. **View data** — Log into [Adafruit IO](https://io.adafruit.com/) and watch your feed

---

## 📊 Wiring

**See:** [docs/wiring_connections.md](docs/wiring_connections.md)

| HC-SR04 | ESP32 |
|---------|-------|
| VCC | 5V |
| GND | GND |
| TRIG | GPIO 5 |
| ECHO | GPIO 18 |

---

## 🐛 Troubleshooting

**See:** [docs/troubleshooting.md](docs/troubleshooting.md)

| Issue | Fix |
|-------|-----|
| No WiFi connection | Check SSID/password in secrets.h |
| Data not appearing in Adafruit IO | Verify API key & feed name match |
| Sensor readings inaccurate | Check wiring, ensure 5V supply stable |

---

## 📈 Live Dashboard

View your data at **Adafruit IO:**
- Real-time distance graph
- Data history & trends
- Mobile-friendly dashboard

![Adafruit Graph](images/adafruit_graph.jpeg)

---

## 💡 Key Learnings

✅ ESP32 WiFi connectivity & MQTT protocol  
✅ Cloud data streaming to Adafruit IO  
✅ Non-blocking sensor reads  
✅ Secure credential management  

---

**Repo:** [github.com/arhamrizwan2006/esp32-distance-sensor-mqtt](https://github.com/arhamrizwan2006/esp32-distance-sensor-mqtt)  
**Part of:** DecodeLabs IoT Internship (Week 3)
