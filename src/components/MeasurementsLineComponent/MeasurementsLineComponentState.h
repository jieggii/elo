//
// Created by jieggii on 10/12/24.
//

#ifndef MEASUREMENTSLINECOMPONENTSTATE_H
#define MEASUREMENTSLINECOMPONENTSTATE_H

#include "Display.h"
#include <cstdint>
#include "Timer.h"
#include "EnvSensor.h"

class MeasurementsLineComponentState final {
   public:
    enum class State {
        DISPLAYING_MEASUREMENTS,  // measurements are displayed
        DISPLAYING_STATUSES,      // icons representing measurement statuses are displayed
    };

    /**
     * Icon IDs representing statuses of each measurement.
     */
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

    struct MeasurementStatusIconIDs {
        uint8_t temperature;
        uint8_t humidity;
        uint8_t co2;
    };

    MeasurementsLineComponentState(const uint16_t displayMeasurementsDuration, const uint16_t displayStatusesDuration)
        : measurementStatusIconIDs({.temperature = DisplayCGRAMInfo::defaultIconSlot,
                                    .humidity = DisplayCGRAMInfo::defaultIconSlot,
                                    .co2 = DisplayCGRAMInfo::defaultIconSlot}),
          displayMeasurementsTimer(Timer(displayMeasurementsDuration)),
          displayStatusesTimer(Timer(displayStatusesDuration)) {}

    void setMeasurementStatusIconIDs(MeasurementStatusIconIDs iconIDs);
    MeasurementStatusIconIDs getMeasurementStatusIconIDs();

    Timer& getDisplayMeasurementsTimer();
    Timer& getDisplayStatusesTimer();

    void setMeasurements(Measurements measurements);
    Measurements& getMeasurements();

    void setState(State state);
    [[nodiscard]] State getState() const;

    void setDisplayMeasurementStatusIcons(bool displayMeasurementStatusIcons);
    [[nodiscard]] bool isDisplayMeasurementStatusIcons() const;

   private:
    /**
     * Icon IDs representing statuses of each measurement.
     */
    MeasurementStatusIconIDs measurementStatusIconIDs;

    /**
     * Timer controlling how long measurements are displayed.
     */
    Timer displayMeasurementsTimer;

    /**
     * Timer controlling how long measurement statuses are displayed.
     */
    Timer displayStatusesTimer;

    /**
     * Current measurements to display.
     */
    Measurements measurements = {.temperature = 0, .humidity = 0, .co2 = 0};

    /**
     * Current state of the component.
     */
    State state = State::DISPLAYING_MEASUREMENTS;

    /**
     * Whether to display measurement status icons.
     */
    bool displayMeasurementStatusIcons = false;
};

#endif  // MEASUREMENTSLINECOMPONENTSTATE_H
