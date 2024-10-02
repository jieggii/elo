//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "LCD1602.h"
#include "Icon.h"

#include "base/ModeView/ModeView.h"
#include "base/ModeView/components/base/ClockComponent.h"

#define IDLE_VIEW_INDICATOR_ICON1_ID 1
#define IDLE_VIEW_INDICATOR_ICON2_ID 2

class IdleView final : public ModeView {
   public:
    explicit IdleView(ViewNavigator* viewNavigator)
        : ModeView(viewNavigator, IDLE_VIEW_INDICATOR_ICON1_ID, IDLE_VIEW_INDICATOR_ICON2_ID, ClockTime(0)) {}

    void setup(LCD1602* display) override {
        const Icon icon1 = {
            B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000,
        };

        const Icon icon2 = {
            B00000, B00000, B00000, B00000, B11111, B01010, B01010, B01010,
        };

        display->cacheIcon(IDLE_VIEW_INDICATOR_ICON1_ID, icon1);
        display->cacheIcon(IDLE_VIEW_INDICATOR_ICON2_ID, icon2);
    }

    void loop() override {}
    void render(LCD1602* display) override {
        this->statusLine.render(display);
        this->measurementsLine.render(display);
    };
    void reset() override{};

    ~IdleView() override = default;
};

#endif  // ELO_IDLEVIEW_H
