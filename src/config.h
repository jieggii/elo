//
// Created by jieggii on 9/14/24.
//

#ifndef ELO_SRC_CONFIG_H_
#define ELO_SRC_CONFIG_H_

#include "WiFiConfig.h"
#include "OperationalConfig.h"

void initDefaultOperationalConfig(OperationalConfig* config) {
    config->environment = OperationalConfig::Environment{
        .temperature =
            OperationalConfig::Environment::Temperature{
                .units = OperationalConfig::Environment::Temperature::Units::CELSIUS,
                .optimal = OperationalConfig::Environment::Temperature::ValueRange{20, 20},
                .acceptable = OperationalConfig::Environment::Temperature::ValueRange{19, 21},
            },
        .humidity =
            OperationalConfig::Environment::Humidity{
                .optimal = OperationalConfig::Environment::Humidity::ValueRange{60, 70},
                .acceptable = OperationalConfig::Environment::Humidity::ValueRange{59, 71},
            },
        .co2 =
            OperationalConfig::Environment::CO2{
                .max_optimal = 850,
                .max_acceptable = 950,
            },
    };

    config->sitMode = OperationalConfig::Mode{
        .enabled = true,
        .duration = 25 * 60,
        .exerciseBreak =
            OperationalConfig::Mode::ExerciseBreak{
                .enabled = true,
                .duration = 4 * 60,
                .interval = 30 * 60,
            },
        .postureReminder =
            OperationalConfig::Mode::PostureReminder{
                .enabled = true,
                .interval = 60 * 3,
            },
    };

    config->standMode = OperationalConfig::Mode{
        .enabled = true,
        .duration = 75 * 60,
        .exerciseBreak =
            OperationalConfig::Mode::ExerciseBreak{
                .enabled = true,
                .duration = 4 * 60,
                .interval = 30 * 60,
            },
        .postureReminder =
            OperationalConfig::Mode::PostureReminder{
                .enabled = true,
                .interval = 60 * 3,
            },
    };
}

// void initDefaultWiFiConfig(WiFiConfig* config) {
//     config->mode = WiFiMode::HOST;
//     config->hostWiFiSettings.SSID = "elo";
//     config->hostWiFiSettings.PASSWORD = "password1234";
// }

#endif  // ELO_SRC_CONFIG_H_
