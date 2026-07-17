# Wiring Connections — ESP32 + HC-SR04

## Components
- ESP32 Dev Board
- HC-SR04 Ultrasonic Sensor
- 1kΩ resistor
- 2kΩ resistor

## Why a Voltage Divider is Needed
The HC-SR04 ECHO pin outputs 5V signals, but the ESP32's GPIO pins are only
3.3V tolerant. Connecting ECHO directly to the ESP32 can damage the board.
A voltage divider steps the 5V signal down to a safe ~3.3V.

## Pin Connections

| HC-SR04 Pin | Connects To            |
|-------------|-------------------------|
| VCC         | ESP32 5V (VIN)          |
| TRIG        | ESP32 GPIO 5            |
| ECHO        | Voltage divider midpoint |
| GND         | ESP32 GND               |

## Voltage Divider Wiring
1. HC-SR04 ECHO pin → one leg of the 1kΩ resistor
2. Other leg of 1kΩ resistor → midpoint node
3. Midpoint node → one leg of the 2kΩ resistor
4. Other leg of 2kΩ resistor → GND
5. Midpoint node → ESP32 GPIO 18

The midpoint should have exactly 3 things touching it:
- 1kΩ resistor leg (from ECHO)
- 2kΩ resistor leg (to GND)
- Wire to GPIO 18

## Summary
- TRIG → GPIO 5 (direct connection, no divider needed — this is an output from ESP32)
- ECHO → GPIO 18 (via voltage divider, since this is an input reading 5V from the sensor)
- VCC → 5V
- GND → GND (common ground between ESP32, HC-SR04, and both resistors)

## Important Note
GND must be common across the ESP32, the HC-SR04, and both resistors in the
divider. Without a shared ground reference, the voltage divider won't work
correctly and readings will be unstable or stuck at 0.