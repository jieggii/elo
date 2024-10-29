//
// Created by jieggii on 10/29/24.
//

#ifndef SETTINGS_H
#define SETTINGS_H

#include "Settings.h"

/**
 * Default device settings.
 * Contains default settings for the environmental conditions evaluation and work modes.
 */
constexpr Settings::Settings SETTINGS = {
    .environment = {.temperature = {.optimal = {20.0f, 22.0f}, .acceptable = {19.0f, 23.5f}},
                    .humidity = {.optimal = {40, 60}, .acceptable = {30, 70}},
                    .co2 = {.max_optimal = 800, .max_acceptable = 900}},
    .standWorkMode = {.postureReminder = {.enabled = true, .interval = 3 * 60 * 1000}, .duration = 45 * 60 * 1000},
    .sitWorkMode = {.postureReminder = {.enabled = true, .interval = 3 * 60 * 1000}, .duration = 45 * 60 * 1000},
};

#endif  // SETTINGS_H
