//
// Created by jieggii on 8/31/24.
//

#ifndef ELO_LCD1602_H
#define ELO_LCD1602_H

#include <LiquidCrystal_I2C.h>

#include "Icon.h"
#include "cstdint"

#define MAX_SLOT 7

class LCD1602 {
   private:
    const uint8_t cols = 16;
    const uint8_t rows = 2;

    LiquidCrystal_I2C lcd;

   public:
    explicit LCD1602(uint8_t addr) : lcd(addr, cols, rows) {};

    void init();
    void clear();

    void cacheIcon(uint8_t slot, const Icon& icon);
    void displayCachedIcon(uint8_t slot, uint8_t col, uint8_t row);
    void displayText(const char* text, uint8_t col, uint8_t row);
};

#endif  // ELO_LCD1602_H
