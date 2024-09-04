//
// Created by jieggii on 8/31/24.
//

#ifndef ELO_LCD1602_H
#define ELO_LCD1602_H

#include "cstdint"

#include <LiquidCrystal_I2C.h>

#include "Icon.h"


class LCD1602 {
private:
    const uint8_t cols = 16;
    const uint8_t rows = 2;

    const uint8_t reserved_CGRAM_slot = 7; // CGRAM slot used to temporally cache not precached icons

    LiquidCrystal_I2C lcd;

public:
    explicit LCD1602(uint8_t addr) : lcd(addr, cols, rows) {};

    void init();
    void clear();

    void cacheIcon(uint8_t slot, const Icon& icon);
    void displayCachedIcon(uint8_t slot, uint8_t col, uint8_t row);

    void displayIcon(const Icon& icon, uint8_t col, uint8 row);

    void displayText(const char *text, uint8_t col, uint8_t row);
};


#endif //ELO_LCD1602_H
