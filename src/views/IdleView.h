//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "Display.h"
#include "Icon.h"

#include "base/ModeView/ModeView.h"

class IdleView final : public ModeView {
   public:
    IdleView(const Hardware hardware, ViewNavigator* viewNavigator) : ModeView(hardware, viewNavigator) {}

    void setup(Display* display) override;
    void loop() override;
    void render(Display* display) override;
    void reset() override;

    ~IdleView() override = default;
};

#endif  // ELO_IDLEVIEW_H
