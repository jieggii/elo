//
// Created by jieggii on 8/31/24.
//

#include "Display.h"
#include "debug_print.h"
#include "binary.h"  // todo: avoid using binary.h

void Display::init() {
    this->lcd.init();       // init LCD
    this->lcd.clear();      // clear LCD
    this->lcd.backlight();  // turn on backlight

    // cache default icon:
    constexpr Icon defaultIcon = {
        B01010, B10101, B01010, B10101, B01010, B10101, B01010, B10101,
    };
    this->cacheIconInternal(DisplayCGRAMInfo::defaultIconSlot, &defaultIcon);
}

void Display::clear() { this->lcd.clear(); }

void Display::setCursor(const DisplayCoordinates coordinates) { this->lcd.setCursor(coordinates.col, coordinates.row); }

// TODO: accept icon as a referense?
// TODO: is "cache" a proper term? Maybe use store/save/register?
void Display::cacheIcon(const uint8_t slot, const Icon* icon) {
    if (slot == DisplayCGRAMInfo::defaultIconSlot) {
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

void Display::cacheIconInternal(const uint8_t slot, const Icon* icon) {
    if (slot > DisplayCGRAMInfo::maxSlot) {
        debug_println("err: Display.cacheIconInternal: slot is out of bounds");
        return;
    }
    this->lcd.createChar(slot, reinterpret_cast<const char*>(icon));
    // this->lcd.createChar(slot, reinterpret_cast<const char*>(&icon));
}
