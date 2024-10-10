#ifndef MEASUREMENTSLINECOMPONENT_H
#define MEASUREMENTSLINECOMPONENT_H

#include <cstdint>
#include "Display.h"
#include "ViewComponent.h"
#include "Timer.h"
#include "EnvSensor.h"
#include <cmath>

/**
 * MeasurementsLineComponent line displaying environmental measurements and their statuses.
 */
class MeasurementsLineComponent final : public ViewComponent {
   public:
    struct Measurements {
        uint8_t temperature;
        uint8_t humidity;
        uint16_t co2;

        Measurements() = default;

        /**
         * Create Measurements from EnvSensorMeasurements.
         */
        static Measurements fromEnvSensorMeasurements(const EnvSensorMeasurements* envSensorMeasurements) {
            return Measurements{.temperature = static_cast<uint8_t>(round(envSensorMeasurements->temperature)),
                                .humidity = static_cast<uint8_t>(round(envSensorMeasurements->humidity)),
                                .co2 = envSensorMeasurements->co2};
        }
    };

    /**
     * Icon IDs representing statuses of each measurement.
     */
    struct MeasurementStatusIconIDs {
        uint8_t temperature;
        uint8_t humidity;
        uint8_t co2;
    };

    // TODO: move constructor implementation to cpp file.
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
    void setMeasurements(Measurements measurements);

    /**
     * Set icon IDs representing statuses of each measurement.
     */
    void setMeasurementStatusIconIDs(MeasurementStatusIconIDs iconIDs);

    /**
     * Enable displaying measurement status icons.
     */
    void enableMeasurementStatusIcons(uint32_t now);

    /**
     * Disable displaying measurement status icons.
     */
    void disableMeasurementStatusIcons();

    /**
     * Render the component.
     */
    void render(Display* display) override;

   private:
    Timer displayMeasurementsTimer;  // timer controlling how long measurements are displayed
    Timer displayStatusesTimer;      // timer controlling how long measurement statuses are displayed

    MeasurementStatusIconIDs measurementStatusIconIDs;  // icon IDs representing statuses of each measurement

    enum class State {
        DISPLAYING_MEASUREMENTS,               // measurements are displayed
        DISPLAYING_STATUSES,                   // icons representing measurement statuses are displayed
    } state = State::DISPLAYING_MEASUREMENTS;  // current state of the component

    Measurements measurements = {.temperature = 0, .humidity = 0, .co2 = 0};  // current measurements

    /**
     * Whether to display measurement status icons.
     */
    bool displayMeasurementStatusIcons = false;

    /**
     * Render measurements.
     */
    void renderMeasurements(Display* display) const;

    /**
     * Render measurement status icons.
     */
    void renderMeasurementStatusIcons(Display* display) const;
};

// todo: change this code and the logic!!!

#endif  // MEASUREMENTSLINECOMPONENT_H