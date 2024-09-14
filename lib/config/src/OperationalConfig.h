//
// Created by jieggii on 9/13/24.
//

#ifndef ELO_LIB_SETTINGS_SRC_CONFIG_H_
#define ELO_LIB_SETTINGS_SRC_CONFIG_H_

#include "cstdint"

struct OperationalConfig {
    struct Environment {
        struct Temperature {
            enum class Units {
                CELSIUS,
                FAHRENHEIT,
            };
            struct ValueRange {
                float min;
                float max;
            };

            Units units; // temperature units
            ValueRange optimal; // optimal temperature range
            ValueRange acceptable; // acceptable temperature range
        };

        struct Humidity {
            struct ValueRange {
                uint8_t min;
                uint8_t max;
            };

            ValueRange optimal; // optimal humidity range (%)
            ValueRange acceptable; // acceptable humidity range (%)
        };

        struct CO2 {
            uint16_t max_optimal; // optimal max CO2 value (ppm)
            uint16_t max_acceptable; // acceptable max CO2 value (ppm)
        };

        Temperature temperature;
        Humidity humidity;
        CO2 co2;
    };

    struct Mode {
        struct PostureReminder {
            bool enabled; // enable posture reminder
            uint16_t interval; // posture reminder interval in seconds
        };

        struct ExerciseBreak {
            bool enabled; // enable Exercise
            uint16_t duration; // Exercise duration in seconds
            uint16_t interval; // Exercise interval in seconds
        };

        bool enabled; // enable work mode
        uint16_t duration; // work mode duration in seconds
        ExerciseBreak exerciseBreak; // work mode exercise settings
        PostureReminder postureReminder; // work mode posture reminder settings
    };

    Environment environment; // environment settings

    Mode sitMode; // sit mode settings
    Mode standMode; // stand mode settings
};

#endif  // ELO_LIB_SETTINGS_SRC_CONFIG_H_
