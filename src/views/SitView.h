//
// Created by jieggii on 10/30/24.
//

#ifndef SITVIEW_H
#define SITVIEW_H


#include "Display.h"

#include "base/WorkModeView/WorkModeView.h"

class SitView final : public WorkModeView {
public:
    SitView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
              MeasurementsLineComponentState& measurementsLineComponentState,
              const settings::EnvironmentEvaluation& envEvalSettings, const settings::WorkMode& workModeSettings)
        : WorkModeView(hardware, viewNavigator, nextViewID, measurementsLineComponentState, envEvalSettings,
                       workModeSettings) {}

    void setup(uint32_t now, display::Display& display) override;
    void handleInputs(const uint32_t now) override { WorkModeView::handleInputs(now); };
    void update(uint32_t now) override;
    void render(display::Display& display) override;
    void reset(uint32_t now) override;
};

#endif //SITVIEW_H
