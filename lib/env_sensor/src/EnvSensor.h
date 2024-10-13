//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_ENVSENSOR_H
#define ELO_ENVSENSOR_H

#include "SparkFun_SCD4x_Arduino_Library.h"
#include "cstdint"

#include <debug_print.h>

/**
 * Measurements from the environmental sensor.
 */
struct EnvSensorMeasurements {
    bool fresh;  // fresh indicates whether the measurements are fresh or not.
    float temperature;
    float humidity;
    uint16_t co2;
};

/**
 * EnvSensor
 */
class EnvSensor {
   public:
    EnvSensor() = default;

    bool init() {
        if (!this->scd40.begin()) {
            debug_println("EnvSensor.init: begin failed");
            return false;
        }
        if (!this->scd40.startPeriodicMeasurement()) {
            debug_println("EnvSensor.init: start measurements failed");
            return false;
        }

        return true;
    }

    /**
     * Get measurements after they have been read. You should call @performMeasurements first and make sure, that
     * it returned true in order to get valid and fresh measurements.
     * @return measurements.
     */
    EnvSensorMeasurements readMeasurements() {
        const bool fresh = this->scd40.readMeasurement();

        return EnvSensorMeasurements{
            .fresh = fresh,
            .temperature = this->scd40.getTemperature(),
            .humidity = this->scd40.getHumidity(),
            .co2 = this->scd40.getCO2(),
        };
    }

   private:
    SCD4x scd40;
};

#endif  // ELO_ENVSENSOR_H
