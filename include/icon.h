//
// Created by jieggii on 10/30/24.
//

#ifndef ICON_H
#define ICON_H

#include "Icon.h"

/**
 * All icons displayed by various views.
 */
namespace icon {
    /**
     * Mode indicators used by various modes.
     */
    namespace modeIndicator {
        /**
         * Mode indicators for the idle mode.
         */
        namespace idle {
            constexpr Icon indicator1 = {
                // empty icon
                0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
            };

            constexpr Icon indicator2 = {
                // table
                0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b01010, 0b01010, 0b01010,
            };
        }  // namespace idle

        /**
         * Mode indicators for the stand mode.
         */
        namespace stand {
            constexpr Icon indicator1 = {
                // person standing
                0b01110, 0b01110, 0b00100, 0b00111, 0b00100, 0b00100, 0b00100, 0b00100,
            };

            constexpr Icon indicator2 = {
                // table in the standing position
                0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b01010, 0b01010, 0b01010,
            };
        }  // namespace stand

        /**
         * Mode indicators for the sit mode.
         */
        namespace sit {
            constexpr Icon indicator1 = {
                // person sitting
                0b00000, 0b01110, 0b01110, 0b00100, 0b00111, 0b00100, 0b00100, 0b00111};

            constexpr Icon indicator2 = {
                // table in the sitting position
                0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b11111, 0b01010, 0b01010,
            };
        }  // namespace sit
    }  // namespace modeIndicator

    /**
     * Icons representing environmental measurement evaluations.
     */
    namespace measurementStatus {
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
    }  // namespace measurementStatus
}  // namespace icon

#endif  // ICON_H
