//
// Created by jieggii on 9/14/24.
//

#ifndef ELO_SRC_CONFIG_H_
#define ELO_SRC_CONFIG_H_

#include "WiFiSettings.h"
#include "Settings.h"

void initDefaultOperationalConfig(Settings* config) {
    config->environment = Settings::Environment{
        .temperature =
            Settings::Environment::Temperature{
                .units = Settings::Environment::Temperature::Units::CELSIUS,
                .optimal = Settings::Environment::Temperature::ValueRange{20, 20},
                .acceptable = Settings::Environment::Temperature::ValueRange{19, 21},
            },
        .humidity =
            Settings::Environment::Humidity{
                .optimal = Settings::Environment::Humidity::ValueRange{60, 70},
                .acceptable = Settings::Environment::Humidity::ValueRange{59, 71},
            },
        .co2 =
            Settings::Environment::CO2{
                .max_optimal = 850,
                .max_acceptable = 950,
            },
    };

    config->sitMode = Settings::Mode{
        .enabled = true,
        .duration = 25 * 60,
        .exerciseBreak =
            Settings::Mode::ExerciseBreak{
                .enabled = true,
                .duration = 4 * 60,
                .interval = 30 * 60,
            },
        .postureReminder =
            Settings::Mode::PostureReminder{
                .enabled = true,
                .interval = 60 * 3,
            },
    };

    config->standMode = Settings::Mode{
        .enabled = true,
        .duration = 75 * 60,
        .exerciseBreak =
            Settings::Mode::ExerciseBreak{
                .enabled = true,
                .duration = 4 * 60,
                .interval = 30 * 60,
            },
        .postureReminder =
            Settings::Mode::PostureReminder{
                .enabled = true,
                .interval = 60 * 3,
            },
    };
}

// void initDefaultWiFiConfig(WiFiSettings* settings) {
//     settings->mode = WiFiMode::HOST;
//     settings->hostWiFiSettings.SSID = "elo";
//     settings->hostWiFiSettings.PASSWORD = "password1234";
// }

#endif  // ELO_SRC_CONFIG_H_
