//
// Created by jieggii on 10/5/24.
//

#ifndef STANDVIEW_H
#define STANDVIEW_H

#include "Display.h"
#include "base/WorkModeView/WorkModeView.h"

namespace StandViewIcons {}

class StandView final : public WorkModeView {
   public:
    StandView(const Hardware hardware, ViewNavigator* viewNavigator, const uint8_t nextViewID, const uint16_t duration)
        : WorkModeView(hardware, viewNavigator, nextViewID, duration, 60, 60) {}

    void setup(Display* display) override;
    void loop() override;
    void render(Display* display) override;
    void reset() override;
};  // namespace StandViewIconsclassStandViewfinal:public WorkModeView

#endif  // STANDVIEW_H
