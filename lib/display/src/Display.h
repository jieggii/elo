//
// Created by jieggii on 8/31/24.
//

#ifndef ELO_Display_H
#define ELO_Display_H

#include <LiquidCrystal_I2C.h>

#include "Icon.h"
#include "cstdint"

// #define DISPLAY_MAX_CGRAM_SLOT 7           // the last available CGRAM slot for storing custom characters (icons)
// #define DISPLAY_DEFAULT_ICON_CGRAM_SLOT 0  // CGRAM slot which is reserved for storing the default icon

namespace DisplayCGRAMInfo {
    constexpr uint8_t maxSlot = 7;
    constexpr uint8_t defaultIconSlot = 0;
}  // namespace DisplayCGRAMInfo

// #define DISPLAY_COLS 16
// #define DISPLAY_ROWS 2

namespace DisplayDimensions {
    constexpr uint8_t cols = 16;
    constexpr uint8_t rows = 2;
}  // namespace DisplayDimensions

/**
 * Represents the coordinates of the display.
 */
struct DisplayCoordinates {
    uint8_t col;
    uint8_t row;

    DisplayCoordinates(const uint8_t col, const uint8_t row) : col(col), row(row){};
};

/**
 * Display class encapsulates the LiquidCrystal_I2C library and provides an interface for working with the display.
 */
class Display {
   public:
    explicit Display(const uint8_t addr) : lcd(addr, DisplayDimensions::cols, DisplayDimensions::rows) {}

    void init();
    void clear();

    void setCursor(DisplayCoordinates coordinates);

    void cacheIcon(uint8_t slot, const Icon* icon);
    void displayIcon(uint8_t slot, DisplayCoordinates coordinates);
    void displayText(const char* text, DisplayCoordinates coordinates);

   private:
    LiquidCrystal_I2C lcd;

    /**
     * Cache icon in the CGRAM of the LCD.
     */
    void cacheIconInternal(uint8_t slot, const Icon* icon);
};

#endif  // ELO_Display_H
