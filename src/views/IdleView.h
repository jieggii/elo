//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "Display.h"

#include "base/ModeView/ModeView.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponentState.h"

class IdleView final : public ModeView {
   public:
    IdleView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
             MeasurementsLineComponentState& measurementsLineComponentState)
        : ModeView(hardware, viewNavigator, nextViewID, {0, 0, 0}, measurementsLineComponentState) {}

    void setup(Display& display) override;
    void handleInputs() override { ModeView::handleInputs(); }
    void loop() override;
    void render(Display& display) override;
    void reset() override;

    ~IdleView() override = default;
};

#endif  // ELO_IDLEVIEW_H
