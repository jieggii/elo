//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_ENVSENSOR_H
#define ELO_ENVSENSOR_H

#include "SparkFun_SCD4x_Arduino_Library.h"
#include "cstdint"

struct EnvSensorMeasurements {
    uint8_t temperature;
    uint8_t humidity;
    uint16_t co2;
};

class EnvSensor {
    SCD4x scd40;

   public:
    EnvSensor() = default;

    void init() { this->scd40.begin(); }

    EnvSensorMeasurements read() {
        // TODO: actual implementation

        return EnvSensorMeasurements{.temperature = 20, .humidity = 60, .co2 = 6000};
        // this->scd40.readMeasurement();
        // return EnvSensorMeasurements{
        //     .temperature = static_cast<uint8_t>(this->scd40.getTemperature()),
        //     .humidity = static_cast<uint8_t>(this->scd40.getHumidity()),
        //     .co2 = this->scd40.getCO2(),
        // };
    }
};

#endif  // ELO_ENVSENSOR_H
