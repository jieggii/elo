//
// Created by jieggii on 8/31/24.
//

#include "LCD1602.h"
#include "debug_print.h"
#include "binary.h"  // todo: avoid using binary.h

void LCD1602::init() {
    this->lcd.init();       // init LCD
    this->lcd.backlight();  // turn on backlight

    const Icon defaultIcon = {
        B01010, B10101, B01010, B10101, B01010, B10101, B01010, B10101,
    };
    this->cacheDefaultIcon(defaultIcon);
}

void LCD1602::clear() { this->lcd.clear(); }

void LCD1602::setCursor(const DisplayCoordinates coordinates) { this->lcd.setCursor(coordinates.col, coordinates.row); }

// todo: accept icon as a pointer.
void LCD1602::cacheIcon(const uint8_t slot, const Icon& icon) {
    if (slot == DISPLAY_DEFAULT_ICON_CGRAM_SLOT) {
        debug_println("err: LCD1602.cacheIcon: slot is reserved for the default icon");
        return;
    }
    this->cacheIconInternal(slot, icon);
}

void LCD1602::displayIcon(const uint8_t slot, const DisplayCoordinates coordinates) {
    this->setCursor(coordinates);
    this->lcd.write(slot);
}

void LCD1602::displayText(const char* text, const DisplayCoordinates coordinates) {
    this->setCursor(coordinates);
    this->lcd.print(text);
}

void LCD1602::cacheIconInternal(const uint8_t slot, const Icon& icon) {
    if (slot > DISPLAY_MAX_CGRAM_SLOT) {
        debug_println("err: LCD1602.cacheIconInternal: slot is out of bounds");
        return;
    }
    this->lcd.createChar(slot, reinterpret_cast<const char*>(icon));
}

void LCD1602::cacheDefaultIcon(const Icon& icon) { this->cacheIconInternal(DISPLAY_DEFAULT_ICON_CGRAM_SLOT, icon); }
