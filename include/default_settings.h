//
// Created by jieggii on 10/29/24.
//

#ifndef SETTINGS_H
#define SETTINGS_H

#include "Settings.h"

namespace default_settings {
    /**
     * Default device settings.
     * Contains default settings for the environmental conditions evaluation and work modes.
     * NOTE: please do not forget to indicate integer literal types (e.g. 10UL) to avoid overflow, if values exceed int
     * range (default integer literal type in cpp).
     */
    constexpr settings::Settings defaultSettings = {
        .environment = {.temperature = {.optimal = {20.0f, 22.0f}, .acceptable = {19.0f, 23.5f}},
                        .humidity = {.optimal = {40, 60}, .acceptable = {30, 70}},
                        .co2 = {.max_optimal = 800, .max_acceptable = 900}},
        .standWorkMode = {.postureReminder = {.enabled = true, .interval = 30UL * 1000}, .duration = 45UL * 60 * 1000},
        .sitWorkMode = {.postureReminder = {.enabled = true, .interval = 30UL * 1000},
                        .duration = 45UL * 60 * 1000},
    };
}  // namespace default_settings

#endif  // SETTINGS_H
