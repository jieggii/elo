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
    bool areFresh;  // indicates whether readings are fresh
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
     * Perform measurements.
     * NOTE: it takes some time for the sensor to start reporting measurements,
     * so during the first few seconds after powering up the sensor, this function will be returning false.
     * @return true if measurements were performed successfully, false otherwise.
     */
    bool performMeasurements() { return this->scd40.readMeasurement(); }

    /**
     * Get measurements after they have been performed. You should call @performMeasurements first and make sure, that
     * it returned true in order to get valid and fresh measurements.
     * @return measurements.
     */
    EnvSensorMeasurements getMeasurements() {
        return EnvSensorMeasurements{
            .temperature = this->scd40.getTemperature(),
            .humidity = this->scd40.getHumidity(),
            .co2 = this->scd40.getCO2(),
        };
    }

   private:
    SCD4x scd40;
};

#endif  // ELO_ENVSENSOR_H
