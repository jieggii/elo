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
   public:
    struct MeasurementStatusIconIDs {
        uint8_t temperature;
        uint8_t humidity;
        uint8_t co2;
    };

    MeasurementsLineComponent(const DisplayCoordinates coordinates, const uint16_t displayMeasurementsDuration,
                              const uint16_t displayStatusesDuration, const uint8_t defaultMeasurementStatusIconID)
        : ViewComponent(coordinates),
          displayMeasurementsTimer(Timer(displayMeasurementsDuration)),
          displayStatusesTimer(Timer(displayStatusesDuration)),
          measurementStatusIconIDs({.temperature = defaultMeasurementStatusIconID,
                                    .humidity = defaultMeasurementStatusIconID,
                                    .co2 = defaultMeasurementStatusIconID}) {}

    /**
     * Set measurements to be displayed.
     */
    void setMeasurements(const EnvSensorMeasurements measurements) { this->measurements = measurements; }

    /**
     * Set icon IDs representing statuses of each measurement.
     */
    void setMeasurementStatusIconIDs(const MeasurementStatusIconIDs iconIDs) {
        this->measurementStatusIconIDs = iconIDs;
    }

    void render(LCD1602* display) override {
        const uint32_t now = millis();

        switch (this->state) {
            case State::DISPLAY_MEASUREMENTS:
                // TODO: display actual measurements
                display->displayText("00*C 00% 0000ppm", this->coordinates);

                if (this->displayMeasurementsTimer.isExpired(now)) {
                    this->state = State::DISPLAY_MEASUREMENT_STATUS_ICONS;
                    this->displayStatusesTimer.set(now);
                }
                break;

            case State::DISPLAY_MEASUREMENT_STATUS_ICONS:
                display->displayText("  *C   %     ppm",
                                     {0, 1});  // todo: is there a better way to do this? For
                                               // example, just remove/replace with " " reading values from the line
                display->displayIcon(this->measurementStatusIconIDs.temperature, {1, 1});
                display->displayIcon(this->measurementStatusIconIDs.humidity, {6, 1});
                display->displayIcon(this->measurementStatusIconIDs.co2, {12, 1});

                if (this->displayStatusesTimer.isExpired(now)) {
                    this->state = State::DISPLAY_MEASUREMENTS;
                    this->displayMeasurementsTimer.set(now);
                }
                break;
        }
    }

   private:
    Timer displayMeasurementsTimer;
    Timer displayStatusesTimer;

    MeasurementStatusIconIDs measurementStatusIconIDs;  // icon IDs representing statuses of each measurement

    enum class State {
        DISPLAY_MEASUREMENTS,               // actual measurements are displayed
        DISPLAY_MEASUREMENT_STATUS_ICONS,   // icons representing measurement statuses are displayed
    } state = State::DISPLAY_MEASUREMENTS;  // current state of the component

    EnvSensorMeasurements measurements = {.temperature = 0, .humidity = 0, .co2 = 0};  // current measurements
};

#endif  // MEASUREMENTSLINECOMPONENT_H