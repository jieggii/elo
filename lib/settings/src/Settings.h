//
// Created by jieggii on 9/13/24.
//

#ifndef ELO_LIB_SETTINGS_SRC_SETTINGS_H_
#define ELO_LIB_SETTINGS_SRC_SETTINGS_H_

#include "cstdint"

struct Settings {
    struct Environment {
        struct Temperature {
            enum class Units {
                CELSIUS,
                FAHRENHEIT,
            } units;
            struct ValueRange {
                float min;
                float max;
            } optimal, acceptable;
        } temperature;

        struct Humidity {
            struct ValueRange {
                uint8_t min;
                uint8_t max;
            } optimal, acceptable;
        } humidity;

        struct CO2 {
            uint16_t max_optimal;     // optimal max CO2 value (ppm)
            uint16_t max_acceptable;  // acceptable max CO2 value (ppm)
        } co2;
    } environment;

    struct Mode {
        struct PostureReminder {
            bool enabled;       // enable posture reminder
            uint16_t interval;  // posture reminder interval in seconds
        } postureReminder;

        struct ExerciseBreak {
            bool enabled;       // enable Exercise
            uint16_t duration;  // Exercise duration in seconds
            uint16_t interval;  // Exercise interval in seconds
        } exerciseBreak;

        bool enabled;                     // enable work mode
        uint16_t duration;                // work mode duration in seconds
    } sitMode, standMode;
};

#endif  // ELO_LIB_SETTINGS_SRC_SETTINGS_H_
