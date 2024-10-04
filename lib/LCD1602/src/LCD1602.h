//
// Created by jieggii on 8/31/24.
//

#ifndef ELO_LCD1602_H
#define ELO_LCD1602_H

#include <LiquidCrystal_I2C.h>

#include "Icon.h"
#include "cstdint"

#define DISPLAY_MAX_CGRAM_SLOT 7           // the last available CGRAM slot for storing custom characters (icons)
#define DISPLAY_DEFAULT_ICON_CGRAM_SLOT 0  // CGRAM slot which is reserved for storing the default icon

#define DISPLAY_COLS 16
#define DISPLAY_ROWS 2

/**
 * Represents the coordinates of the display.
 */
struct DisplayCoordinates {
    uint8_t col;
    uint8_t row;

    DisplayCoordinates(const uint8_t col, const uint8_t row) : col(col), row(row){};
};

/**
 * LCD1602 class encapsulates the LiquidCrystal_I2C library and provides an interface for working with the LCD1602
 * display.
 */
class LCD1602 {
   public:
    explicit LCD1602(const uint8_t addr) : lcd(addr, DISPLAY_COLS, DISPLAY_ROWS){};

    void init();
    void clear();

    void setCursor(DisplayCoordinates coordinates);

    void cacheIcon(uint8_t slot, const Icon& icon);
    void displayIcon(uint8_t slot, DisplayCoordinates coordinates);
    void displayText(const char* text, DisplayCoordinates coordinates);

   private:
    LiquidCrystal_I2C lcd;

    /**
     * Cache icon in the CGRAM of the LCD.
     */
    void cacheIconInternal(uint8_t slot, const Icon& icon);
    void cacheDefaultIcon(const Icon& icon);
};

#endif  // ELO_LCD1602_H
