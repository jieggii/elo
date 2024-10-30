#include "icon.h"

#include "IdleView.h"

void IdleView::setup(const uint32_t now, display::Display& display) {
    cacheModeIndicatorIcons(display, &icon::modeIndicator::idle::indicator1, &icon::modeIndicator::idle::indicator2);

    this->ModeView::setup(now, display);
}

void IdleView::update(const uint32_t now) {
    // todo: get actual current time from the actual RTC
    constexpr ClockTime currentTime = {23, 59, 59};
    auto& clockComponentState = this->components.statusLine.getState().getClockComponentState();
    clockComponentState.setTime(currentTime);

    ModeView::update(now);
}

void IdleView::render(display::Display& display) { ModeView::render(display); }

void IdleView::reset(const uint32_t now) { ModeView::reset(now); }
