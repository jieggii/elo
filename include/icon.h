//
// Created by jieggii on 10/30/24.
//

#ifndef ICON_H
#define ICON_H

#include "Icon.h"

namespace icon {
    namespace modeIndicator {
        namespace idle {
            constexpr Icon modeIcon1 = {
                // empty icon
                0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
            };

            constexpr Icon modeIcon2 = {
                // table
                0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b01010, 0b01010, 0b01010,
            };
        }  // namespace idle

        namespace stand {
            constexpr Icon modeIcon1 = {
                // person standing
                0b01110, 0b01110, 0b00100, 0b00111, 0b00100, 0b00100, 0b00100, 0b00100,
            };

            constexpr Icon modeIcon2 = {
                // table in the standing position
                0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b01010, 0b01010, 0b01010,
            };
        }  // namespace stand
    }  // namespace modeIndicator

    namespace measurementsStatus {
        constexpr Icon optimal = {
            // icon representing smiling face :)
            0b00000, 0b01010, 0b01010, 0b00000, 0b10001, 0b01110, 0b00000, 0b00000,
        };

        constexpr Icon acceptable = {
            // icon representing neutral face :|
            0b00000, 0b01010, 0b01010, 0b00000, 0b00000, 0b11111, 0b00000, 0b00000,
        };

        constexpr Icon bad = {
            // icon representing sad face :(
            0b00000, 0b01010, 0b01010, 0b00000, 0b00000, 0b01110, 0b10001, 0b00000,
        };
    }  // namespace measurementsStatus
}  // namespace icon

#endif  // ICON_H
