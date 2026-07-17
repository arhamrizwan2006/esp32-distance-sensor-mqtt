# Troubleshooting Log

## Issue 1: No Readings / Stuck at 0
Symptom: Serial Monitor shows distance stuck at 0.00 cm or no output at all.

Cause: Usually one of the following — TRIG and ECHO pins swapped in code vs. wiring, or GND not common between ESP32, HC-SR04, and the voltage divider resistors.

Fix: Double-check pin assignments match the physical wiring, and confirm all GND connections are tied together.

## Issue 2: Random / Garbage Distance Values
Symptom: Readings jump wildly or don't make physical sense.

Cause: Voltage divider wired incorrectly — the midpoint node has the wrong number of connections, or resistor values/orientation are off.

Fix: Confirm the midpoint has exactly 3 connections: the 1kΩ leg from ECHO, the 2kΩ leg to GND, and the wire to GPIO 18.

## Issue 3: Board Not Detected in Arduino IDE
Symptom: Upload fails, or the correct COM port doesn't appear.

Fix: Under Tools in Arduino IDE, confirm the correct ESP32 board and port are selected. Also confirmed baud rate was set to 115200 in Serial Monitor (ESP32 default), not 9600 (Uno default) — using the wrong baud rate produces garbled or no output.

## Issue 4: Adafruit IO Rate Limit / Reconnect Ban
Symptom: After running for a while, Serial Monitor showed repeated "Publish failed!" messages, followed by "Connecting to MQTT... Connection failed" and eventually "Exceeded reconnect rate limit. Please try again later."

Root Cause: The Wi-Fi or MQTT connection dropped at some point due to weak signal, a router hiccup, or long uptime. The original MQTT_connect() function retried every 3 seconds in a tight loop. Adafruit IO detected this as rapid-fire reconnecting and triggered its anti-abuse rate limit, temporarily blocking the connection.

Fix: Two changes were made. First, exponential backoff was added to the reconnect logic — after 5 failed retries, the code waits 30 seconds before trying again, spacing out reconnection attempts so they don't trip the rate limit. Second, the publish interval was increased from 2 seconds to 3 seconds, giving more safety margin under Adafruit IO's 60 requests/minute limit.

Resolution: Waited 5-10 minutes for Adafruit IO's temporary ban to lift (this happens automatically), then re-uploaded the updated code with backoff logic. Connection has been stable since.

## Issue 5: Occasional 0.00 cm Readings During Long Runs
Symptom: Sporadic Distance: 0.00 cm readings appeared during extended testing, unrelated to the MQTT issue.

Cause: The HC-SR04's echo pulse timed out, likely due to nothing being in range, a momentarily loose wire connection, or sensor noise.

Status: Noted as a minor issue to monitor. Does not affect overall system stability since it self-corrects on the next read cycle.