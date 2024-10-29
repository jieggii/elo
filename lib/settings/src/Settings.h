//
// Created by jieggii on 9/13/24.
//

#ifndef ELO_LIB_SETTINGS_SRC_SETTINGS_H_
#define ELO_LIB_SETTINGS_SRC_SETTINGS_H_

#include <cstdint>

#include "env_eval.h"

// TODO: decide which work mode should be first: stand or sit.
namespace settings {
    /**
     * Represents the settings for the environmental conditions evaluation.
     */
    struct EnvironmentEvaluation {
        struct Temperature {
            env_eval::ValueRange<float> optimal;     // optimal temperature range
            env_eval::ValueRange<float> acceptable;  // acceptable temperature range
        } temperature;

        struct Humidity {
            env_eval::ValueRange<uint8_t> optimal;     // optimal humidity range
            env_eval::ValueRange<uint8_t> acceptable;  // acceptable humidity range
        } humidity;

        struct CO2 {
            uint16_t max_optimal;     // optimal max CO2 value (ppm)
            uint16_t max_acceptable;  // acceptable max CO2 value (ppm)
        } co2;
    };

    /**
     * Represents the settings of a work mode.
     */
    struct WorkMode {
        /**
         * Posture reminder settings.
         * Posture reminder is a short notification that reminds the user to correct their posture.
         */
        struct PostureReminder {
            bool enabled;       // enable posture reminder
            uint32_t interval;  // posture reminder interval in milliseconds
        } postureReminder;

        uint32_t duration;  // duration of the work mode in milliseconds
    };

    /**
     * Represents the device settings.
     * Contains settings for the environmental conditions evaluation and work modes.
     */
    struct Settings {
        EnvironmentEvaluation environment;
        WorkMode standWorkMode;  // stand work mode settings
        WorkMode sitWorkMode;    // sit work mode settings
    };
}  // namespace settings

#endif  // ELO_LIB_SETTINGS_SRC_SETTINGS_H_
