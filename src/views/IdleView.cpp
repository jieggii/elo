#include "IdleView.h"

#include "base/ModeView/components/base/ClockComponent.h"

void IdleView::setup(Display* display) {
    constexpr Icon modeIcon1 = {
        // empty icon
        B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000,
    };

    constexpr Icon modeIcon2 = {
        // table
        B00000, B00000, B00000, B00000, B11111, B01010, B01010, B01010,
    };

    ModeView::setup(display, &modeIcon1, &modeIcon2);

    display->clear();
}

void IdleView::loop() { ModeView::loop(); }

void IdleView::render(Display* display) {
    // todo: get actual current time from the actual RTC
    const ClockTime currentTime = {23, 59, 59};
    this->setStatusLineClockTime(currentTime);

    ModeView::render(display);
}

void IdleView::reset() {}
