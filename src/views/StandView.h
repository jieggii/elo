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
    StandView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
              MeasurementsLineComponentState& measurementsLineComponentState, const uint16_t duration)
        : WorkModeView(hardware, viewNavigator, nextViewID, measurementsLineComponentState, duration, 2000, 60000) {}

    void setup(uint32_t now, Display& display) override;
    void handleInputs(const uint32_t now) override { WorkModeView::handleInputs(now); };
    void update(uint32_t now) override;
    void render(Display& display) override;
    void reset(uint32_t now) override;
};

#endif  // STANDVIEW_H
