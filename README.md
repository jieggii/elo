# elo (MVP)

Elo is a small, practical device designed to make your workspace more comfortable and efficient.
It keeps track of the temperature, humidity, and CO2 levels in your room, showing the results clearly on its LCD screen.
If any of these values go beyond the optimal range, Elo lets you know so you can adjust your environment.

Elo has three modes:

- Idle Mode: Shows the current time and environmental data.
- Sitting and Standing Modes: Helps you track how long you’ve been sitting or standing with built-in timers.

To keep you feeling your best, Elo also includes a posture reminder that you can set to nudge you at regular intervals
to sit or stand up straight.

Elo makes it easy to stay aware of your surroundings and take better care of yourself while you work.

## MVP includes

- [x] Device in a 3d-printed case.
- [x] Measurements and their evaluations are displayed on the LCD screen.
- [x] Configuration of the device using the source code file (`inclde/default_config.h`).
- [x] Posture reminder notifications.

## Post-MVP plans

- [ ] Redesign the device to be more compact and portable.
- [ ] A separate power source for the SCD40 sensor.
- [ ] Bug fixes and improvements to the code.
- [ ] Add Wi-Fi support to be able to integrate with other devices.
- [ ] User-friendly configuration.
- [ ] Display clock in the idle mode using RTC
- [ ] Light sensor to evaluate room lighting

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
