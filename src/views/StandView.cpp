//
// Created by jieggii on 10/6/24.
//

#include "binary.h"

#include "StandView.h"

void StandView::setup(const uint32_t now, Display& display) {
    constexpr Icon modeIcon1 = {
        // person standing
        B01110, B01110, B00100, B00111, B00100, B00100, B00100, B00100,
    };

    constexpr Icon modeIcon2 = {
        // table in the standing position
        B00000, B00000, B00000, B00000, B11111, B01010, B01010, B01010,
    };
    cacheModeIndicatorIcons(display, &modeIcon1, &modeIcon2);

    this->WorkModeView::setup(now, display);
}

void StandView::update(const uint32_t now) { this->WorkModeView::update(now); }

void StandView::render(Display& display) { this->WorkModeView::render(display); }

void StandView::reset() {}
