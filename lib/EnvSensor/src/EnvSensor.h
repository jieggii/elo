//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_ENVSENSOR_H
#define ELO_ENVSENSOR_H

#include "SparkFun_SCD4x_Arduino_Library.h"
#include "cstdint"

struct EnvSensorMeasurement {
    uint8_t temperature;
    uint8_t humidity;
    uint16_t co2;
};

class EnvSensor {
   private:
    SCD4x scd40;

   public:
    explicit EnvSensor() : scd40() {}

    void init() {
        this->scd40.begin();
    }

    EnvSensorMeasurement read() {
        this->scd40.readMeasurement();
        return EnvSensorMeasurement{
            .temperature=static_cast<uint8_t>(this->scd40.getTemperature()),
            .humidity=static_cast<uint8_t>(this->scd40.getHumidity()),
            .co2=this->scd40.getCO2(),
        };
    }
};

#endif  // ELO_ENVSENSOR_H
