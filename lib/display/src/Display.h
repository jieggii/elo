//
// Created by jieggii on 8/31/24.
//

#ifndef ELO_Display_H
#define ELO_Display_H

#include <LiquidCrystal_I2C.h>

#include "Icon.h"
#include "cstdint"

namespace display {
    /**
     * Display dimensions.
     */
    namespace dimensions {
        constexpr uint8_t cols = 16;
        constexpr uint8_t rows = 2;
    }  // namespace dimensions

    /**
     * Display CGRAM information.
     */
    namespace CGRAM {
        constexpr uint8_t maxSlot = 7;
        constexpr uint8_t defaultIconSlot = 0;
    }  // namespace CGRAM

    /**
     * Represents the coordinates of the display.
     */
    struct Coordinates {
        uint8_t col;
        uint8_t row;

        Coordinates(const uint8_t col, const uint8_t row) : col(col), row(row) {}
    };

    /**
     * Display class encapsulates the LiquidCrystal_I2C library and provides an interface for working with the display.
     */
    class Display {
       public:
        explicit Display(const uint8_t addr) : lcd(addr, dimensions::cols, dimensions::rows) {}

        void init();
        void clear();

        void setCursor(Coordinates coordinates);

        void cacheIcon(uint8_t slot, const Icon* icon);
        void displayIcon(uint8_t slot, Coordinates coordinates);
        void displayText(const char* text, Coordinates coordinates);

       private:
        LiquidCrystal_I2C lcd;

        /**
         * Cache icon in the CGRAM of the LCD.
         */
        void cacheIconInternal(uint8_t slot, const Icon* icon);
    };

}  // namespace display

#endif  // ELO_Display_H
