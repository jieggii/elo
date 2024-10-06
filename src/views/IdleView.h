//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "Display.h"
#include "Icon.h"

#include "base/ModeView/ModeView.h"
#include "base/ModeView/components/base/ClockComponent.h"

class IdleView final : public ModeView {
   public:
    IdleView(const Hardware hardware, ViewNavigator* viewNavigator) : ModeView(hardware, viewNavigator) {}

    void setup(Display* display) override {
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

    void loop() override { ModeView::loop(); }
    void render(Display* display) override {
        // todo: get actual current time from the actual RTC
        const ClockTime currentTime = {23, 59, 59};
        this->setStatusLineClockTime(currentTime);

        ModeView::render(display);
    }
    void reset() override {}

    ~IdleView() override = default;
};

#endif  // ELO_IDLEVIEW_H
