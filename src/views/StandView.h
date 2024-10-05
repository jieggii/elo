//
// Created by jieggii on 10/5/24.
//

#ifndef STANDVIEW_H
#define STANDVIEW_H

#include "Display.h"
#include "base/WorkModeView/WorkModeView.h"

#define STAND_VIEW_INDICATOR_ICON1_ID 1
#define STAND_VIEW_INDICATOR_ICON2_ID 2

class StandView final : public WorkModeView {
   public:
    StandView(const Hardware hardware, ViewNavigator* viewNavigator, const uint16_t duration)
        : WorkModeView(hardware, viewNavigator, STAND_VIEW_INDICATOR_ICON1_ID, STAND_VIEW_INDICATOR_ICON2_ID,
                       duration) {}

    void setup(Display* display) override;
    void loop() override;
    void render(Display* display) override;
    void reset() override;
};

#endif  // STANDVIEW_H
