//
// Created by jieggii on 10/12/24.
//

#ifndef MEASUREMENTSLINECOMPONENTSTATE_H
#define MEASUREMENTSLINECOMPONENTSTATE_H

#include "Display.h"
#include <cstdint>
#include "Timer.h"
#include "EnvSensor.h"

#include <ViewComponentState.h>

class MeasurementsLineComponentState final : public ViewComponentState {
   public:
    /**
     * Environmental measurements.
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

    /**
     * Icon IDs representing evaluations of each measurement.
     */
    struct MeasurementEvaluationIconIDs {
        uint8_t temperature;
        uint8_t humidity;
        uint8_t co2;
    };

    /**
     * Constructor.
     * @param displayMeasurementsDuration how long to display measurements in milliseconds.
     * @param displayEvaluationsDuration how long to display measurement evaluations in milliseconds.
     */
    MeasurementsLineComponentState(const uint32_t displayMeasurementsDuration,
                                   const uint32_t displayEvaluationsDuration)
        : displayMeasurementsDuration(displayMeasurementsDuration),
          displayEvaluationsDuration(displayEvaluationsDuration) {}

    [[nodiscard]] uint32_t getDisplayMeasurementsDuration() const;
    [[nodiscard]] uint32_t getDisplayEvaluationsDuration() const;

    void setMeasurementEvaluationIconIDs(MeasurementEvaluationIconIDs iconIDs);
    [[nodiscard]] MeasurementEvaluationIconIDs getMeasurementEvaluationIconIDs() const;

    void setDisplayingEvaluation(bool displayingEvaluations);
    [[nodiscard]] bool isDisplayingEvaluation() const;

    /**
     * Sets measurements available flag to true.
     */
    void setMeasurementsAvailable(uint32_t now);

    /**
     * Returns true if measurements are available.
     */
    [[nodiscard]] bool areMeasurementsAvailable() const;

    Timer& getSwitchStateTimer();
    Timer& getUpdateMeasurementsTimer();

    void setMeasurements(Measurements measurements);
    [[nodiscard]] const Measurements& getMeasurements() const;

   private:
    /**
     * Duration of displaying measurements.
     */
    const uint32_t displayMeasurementsDuration;

    /**
     * Duration of displaying evaluations.
     */
    const uint32_t displayEvaluationsDuration;

    /**
     * Timer indicating when it is time to update measurements.
     */
    Timer updateMeasurementsTimer;

    /**
     * Flag indicating whether measurement evaluations should be displayed.
     */
    bool displayingEvaluations = false;

    /**
     * Environmental measurements.
     */
    Measurements measurements = Measurements{.temperature = 0, .humidity = 0, .co2 = 0};

    /**
     * Timer controlling state switching.
     */
    Timer switchStateTimer = Timer();

    /**
     * Flag indicating whether measurements are available.
     * Measurement evaluation icons will be displayed only when measurements available.
     */
    bool measurementsAvailable = false;

    /**
     * Icon IDs representing statuses of each measurement.
     */
    MeasurementEvaluationIconIDs measurementEvaluationIconIDs = {.temperature = display::CGRAM::defaultIconSlot,
                                                                 .humidity = display::CGRAM::defaultIconSlot,
                                                                 .co2 = display::CGRAM::defaultIconSlot};
};

#endif  // MEASUREMENTSLINECOMPONENTSTATE_H
