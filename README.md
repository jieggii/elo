# elo

elo - flow fellow

> work on the project is in progress

## Pinout

Table below shows the pinout of the project.

| external hardware | external hardware pin | esp8266 pin            |
|-------------------|-----------------------|------------------------|
| **LCD**           | `SCL`                 | `D1`                   |
| LCD               | `SDA`                 | `D2`                   |
| LCD               | `VCC`                 | `5V`                   |
| LCD               | `GND`                 | `GND`                  |
| **SCD40**         | `SCL`                 | `D1`                   |
| SCD40             | `SDA`                 | `D2`                   |
| SCD40             | `VCC`                 | `5V`                   |
| SCD40             | `GND`                 | `GND`                  |
| **Select button** | `INPUT`               | `5V`                   |
| Select button     | `OUTPUT`              | `D5` (`10kOhm -> GND`) |
| **Action button** | `INPUT`               | `5V`                   |
| Action button     | `OUTPUT`              | `D6` (`10kOhm -> GND`) |
| **Buzzer**        | `+`                   | `D7`                   |
| Buzzer            | `-`                   | `GND`                  |