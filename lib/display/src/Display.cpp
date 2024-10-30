//
// Created by jieggii on 8/31/24.
//

#include "Display.h"
#include "debug_print.h"

namespace display {
    void Display::init() {
        this->lcd.init();       // init LCD
        this->lcd.clear();      // clear LCD
        this->lcd.backlight();  // turn on backlight

        // cache default icon:
        constexpr Icon defaultIcon = {
            0b01010, 0b10101, 0b01010, 0b10101, 0b01010, 0b10101, 0b01010, 0b10101,
        };
        this->cacheIconInternal(CGRAM::defaultIconSlot, &defaultIcon);
    }

    void Display::clear() { this->lcd.clear(); }

    void Display::setCursor(const Coordinates coordinates) { this->lcd.setCursor(coordinates.col, coordinates.row); }

    // TODO: accept icon as a referense?
    // TODO: is "cache" a proper term? Maybe use store/save/register?
    void Display::cacheIcon(const uint8_t slot, const Icon* icon) {
        if (slot == CGRAM::defaultIconSlot) {
            debug_println("err: Display.cacheIcon: slot is reserved for the default icon");
            return;
        }
        this->cacheIconInternal(slot, icon);
    }

    void Display::displayIcon(const uint8_t slot, const Coordinates coordinates) {
        this->setCursor(coordinates);
        this->lcd.write(slot);
    }

    void Display::displayText(const char* text, const Coordinates coordinates) {
        this->setCursor(coordinates);
        this->lcd.print(text);
    }

    void Display::cacheIconInternal(const uint8_t slot, const Icon* icon) {
        if (slot > CGRAM::maxSlot) {
            debug_println("err: Display.cacheIconInternal: slot is out of bounds");
            return;
        }
        this->lcd.createChar(slot, reinterpret_cast<const char*>(icon));
    }
}  // namespace display
