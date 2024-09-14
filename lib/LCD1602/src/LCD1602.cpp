//
// Created by jieggii on 8/31/24.
//

#include "LCD1602.h"
#include "debug_print.h"

void LCD1602::init() {
    this->lcd.init();
    this->lcd.backlight();
}

void LCD1602::clear() { this->lcd.clear(); }

void LCD1602::cacheIcon(uint8_t slot, const Icon& icon) {
    if (slot > MAX_SLOT) {
        debug_println("err: LCD1602.cacheIcon: slot is out of bounds");
        return;
    }
    this->lcd.createChar(slot, reinterpret_cast<const char*>(icon));
}

void LCD1602::displayCachedIcon(uint8_t slot, uint8_t col, uint8_t row) {
    this->lcd.setCursor(col, row);
    this->lcd.write(slot);
}

void LCD1602::displayText(const char* text, uint8_t col, uint8_t row) {
    this->lcd.setCursor(col, row);
    this->lcd.print(text);
}
