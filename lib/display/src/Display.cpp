//
// Created by jieggii on 8/31/24.
//

#include "Display.h"
#include "debug_print.h"
#include "binary.h"  // todo: avoid using binary.h

void Display::init() {
    this->lcd.init();       // init LCD
    this->lcd.backlight();  // turn on backlight

    const Icon defaultIcon = {
        B01010, B10101, B01010, B10101, B01010, B10101, B01010, B10101,
    };
    this->cacheDefaultIcon(defaultIcon);
}

void Display::clear() { this->lcd.clear(); }

void Display::setCursor(const DisplayCoordinates coordinates) { this->lcd.setCursor(coordinates.col, coordinates.row); }

// todo: accept icon as a pointer.
void Display::cacheIcon(const uint8_t slot, const Icon& icon) {
    if (slot == DISPLAY_DEFAULT_ICON_CGRAM_SLOT) {
        debug_println("err: Display.cacheIcon: slot is reserved for the default icon");
        return;
    }
    this->cacheIconInternal(slot, icon);
}

void Display::displayIcon(const uint8_t slot, const DisplayCoordinates coordinates) {
    this->setCursor(coordinates);
    this->lcd.write(slot);
}

void Display::displayText(const char* text, const DisplayCoordinates coordinates) {
    this->setCursor(coordinates);
    this->lcd.print(text);
}

void Display::cacheIconInternal(const uint8_t slot, const Icon& icon) {
    if (slot > DISPLAY_MAX_CGRAM_SLOT) {
        debug_println("err: Display.cacheIconInternal: slot is out of bounds");
        return;
    }
    this->lcd.createChar(slot, reinterpret_cast<const char*>(icon));
}

void Display::cacheDefaultIcon(const Icon& icon) { this->cacheIconInternal(DISPLAY_DEFAULT_ICON_CGRAM_SLOT, icon); }
