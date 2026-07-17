# Cloud-Connected Security Node — IoT Telemetry (ESP32 + MQTT)

## Overview
This project implements Project 3 of the DecodeLabs IoT Internship: a
security telemetry node that broadcasts real-time physical boundary data
from an ESP32 to a centralized cloud dashboard, bridging local sensor
events with global internet infrastructure.

## Architecture
**Input (Physical Boundary):** HC-SR04 ultrasonic sensor
**Process (Local Edge Engine):** ESP32 microcontroller running Wi-Fi + MQTT logic
**Output (Global Cloud):** Adafruit IO dashboard

## Hardware
- ESP32 Dev Board
- HC-SR04 Ultrasonic Sensor
- Voltage divider (1kΩ + 2kΩ resistors) on the ECHO line, since the
  HC-SR04 outputs 5V and ESP32 GPIOs are only 3.3V tolerant

## Wiring
- TRIG → GPIO 5
- ECHO → GPIO 18 (via voltage divider)
- VCC → 5V
- GND → GND

## How It Works
1. On boot, the ESP32 blocks execution until Wi-Fi connects successfully,
   preventing the main loop from running without network access.
2. Every 2 seconds (non-blocking, using `millis()` rather than `delay()`),
   the ESP32 triggers the HC-SR04 and calculates distance from the echo
   pulse duration:
   `distance = (duration / 2) * 0.0343`
3. The reading is safely formatted into a static character buffer with
   `dtostrf()` to avoid heap fragmentation from dynamic String objects.
4. The payload is published via MQTT (publish-subscribe, low overhead)
   to an Adafruit IO feed at `username/feeds/distance`.
5. Reconnection logic uses exponential backoff to avoid tripping
   Adafruit IO's rate limit (60 requests/minute) during network drops.

## Why MQTT over HTTP
MQTT uses a persistent TCP connection with ~2 bytes of fixed header
overhead per message, versus HTTP's 700–1000+ bytes per request. This
makes it far more efficient for continuous, low-power telemetry streams.

## Setup
1. Install the **Adafruit MQTT Library** in Arduino IDE
   (Sketch → Include Library → Manage Libraries → search "Adafruit MQTT Library")
2. Copy `secrets.h.example` to a new file named `secrets.h`
3. Fill in your Wi-Fi credentials and Adafruit IO username/key in `secrets.h`
4. Upload the sketch to your ESP32
5. Open Serial Monitor at 115200 baud to view live readings
6. Add a chart block to your `distance` feed on the Adafruit IO dashboard
   to visualize the live stream

## Notes
- `secrets.h` is intentionally excluded from this repo to keep credentials private.
- Adafruit IO enforces a rate limit on reconnect attempts; this sketch
  handles that with backoff delays to avoid temporary bans.

## Status
✅ Sensor + voltage divider verified over Serial
✅ Wi-Fi connection with blocking handshake on boot
✅ MQTT publish to Adafruit IO confirmed working
✅ Non-blocking timing and reconnect backoff implemented

## Author
DecodeLabs IoT Internship — Batch 2026
