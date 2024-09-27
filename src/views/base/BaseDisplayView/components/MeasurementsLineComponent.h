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
    MeasurementsLineComponent(LCD1602* display, DisplayCoordinates coordinates,
                              const uint16_t displayMeasurementsDuration, const uint16_t displayStatusesDuration)
        : ViewComponent(display, coordinates),
          displayMeasurementsTimer(Timer(displayMeasurementsDuration)),
          displayStatusesTimer((Timer(displayStatusesDuration))) {}

    void setMeasurements(const EnvSensorMeasurements measurements) { this->measurements = measurements; }

    void setMeasurementStatusIcons(const MeasurementStatusIcons measurementStatusIcons) {
        this->measurementStatusIcons = measurementStatusIcons;
    }

    void loop(const uint32_t now) override {
        switch (this->state) {
            case State::DISPLAY_MEASUREMENTS:
                if (this->displayMeasurementsTimer.isExpired(now)) {
                    this->state = State::DISPLAY_STATUSES;
                    this->displayStatusesTimer.set(now);
                }
                break;
            case State::DISPLAY_STATUSES:
                if (this->displayStatusesTimer.isExpired(now)) {
                    this->state = State::DISPLAY_MEASUREMENTS;
                    this->displayMeasurementsTimer.set(now);
                }
                break;
        }
    }

    void render() override {
        switch (this->state) {
            case State::DISPLAY_MEASUREMENTS:
                // todo: display measurements
                display->displayText("00*C 00% 0000ppm", this->coordinates);
                break;
            case State::DISPLAY_STATUSES:
                // todo: display statuses
                display->displayText(" :)   :)    :)  ", this->coordinates);
                break;
        }
    }
};

#endif  // MEASUREMENTSLINECOMPONENT_H