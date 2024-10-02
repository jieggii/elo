#ifndef MEASUREMENTSLINECOMPONENT_H
#define MEASUREMENTSLINECOMPONENT_H

#include <cstdint>
#include "LCD1602.h"
#include "ViewComponent.h"
#include "Timer.h"
#include "EnvSensor.h"

/**
 * MeasurementsLineComponent line displaying environmental measurements and their statuses.
 */
class MeasurementsLineComponent final : public ViewComponent {
    Timer displayMeasurementsTimer;
    Timer displayStatusesTimer;

    enum class State {
        DISPLAY_MEASUREMENTS,
        DISPLAY_STATUSES,
    } state = State::DISPLAY_MEASUREMENTS;

    struct MeasurementStatusIcons {
        uint8_t temperature;
        uint8_t humidity;
        uint8_t co2;
    } measurementStatusIcons = {.temperature = 0, .humidity = 0, .co2 = 0};
    EnvSensorMeasurements measurements = {.temperature = 0, .humidity = 0, .co2 = 0};

   public:
    MeasurementsLineComponent(const DisplayCoordinates coordinates, const uint16_t displayMeasurementsDuration,
                              const uint16_t displayStatusesDuration)
        : ViewComponent(coordinates),
          displayMeasurementsTimer(Timer(displayMeasurementsDuration)),
          displayStatusesTimer((Timer(displayStatusesDuration))) {}

    void setMeasurements(const EnvSensorMeasurements measurements) { this->measurements = measurements; }

    void setMeasurementStatusIcons(const MeasurementStatusIcons measurementStatusIcons) {
        this->measurementStatusIcons = measurementStatusIcons;
    }

    void render(LCD1602* display) override {
        const uint32_t now = millis();

        switch (this->state) {
            case State::DISPLAY_MEASUREMENTS:
                // todo: display actual measurements
                display->displayText("00*C 00% 0000ppm", this->coordinates);

                if (this->displayMeasurementsTimer.isExpired(now)) {
                    this->state = State::DISPLAY_STATUSES;
                    this->displayStatusesTimer.set(now);
                }
                break;

            case State::DISPLAY_STATUSES:
                // todo: display actual statuses
                display->displayText(" :)   :)    :)  ", this->coordinates);

                if (this->displayStatusesTimer.isExpired(now)) {
                    this->state = State::DISPLAY_MEASUREMENTS;
                    this->displayMeasurementsTimer.set(now);
                }
                break;
        }
    }
};

#endif  // MEASUREMENTSLINECOMPONENT_H