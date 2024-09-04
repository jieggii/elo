//
// Created by jieggii on 8/31/24.
//

#include "LCD1602.h"

void LCD1602::init() {
    this->lcd.init();
    this->lcd.backlight();
}

void LCD1602::clear() {
    this->lcd.clear();
}

void LCD1602::cacheIcon(uint8_t slot, const Icon& icon) {
    // make sure not to use reserved CGRAM slot!
    this->lcd.createChar(slot, reinterpret_cast<const char *>(icon));
}

void LCD1602::displayCachedIcon(uint8_t slot, uint8_t col, uint8_t row) {
    this->lcd.setCursor(col, row);
    this->lcd.write(slot);
}

void LCD1602::displayIcon(const Icon& icon, uint8_t col, uint8 row) {
    this->lcd.setCursor(col, row);
    this->cacheIcon(this->reserved_CGRAM_slot, icon);
    this->displayCachedIcon(this->reserved_CGRAM_slot, col, row);
}

void LCD1602::displayText(const char* text, uint8_t col, uint8_t row) {
    this->lcd.setCursor(col, row);
    this->lcd.print(text);
}
