//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_ENVSENSOR_H
#define ELO_ENVSENSOR_H

#include "SparkFun_SCD4x_Arduino_Library.h"
#include "cstdint"

#include <debug_print.h>

// TODO: add a namespace for the library

using temperatureType = float;
using humidityType = float;
using co2Type = uint16_t;

/**
 * Measurements from the environmental sensor.
 */
struct EnvSensorMeasurements {
    /**
     * Indicates whether the measurements are fresh or not.
     */
    bool fresh;

    temperatureType temperature;
    humidityType humidity;
    co2Type co2;
};

/**
 * EnvSensor class is a wrapper around the SCD4x library. It provides an interface to the environmental sensor.
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
     * Reads measurements from the sensor.
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
    /**
     * SCD40 sensor.
     */
    SCD4x scd40;
};

#endif  // ELO_ENVSENSOR_H
