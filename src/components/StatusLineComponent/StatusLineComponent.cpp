//
// Created by jieggii on 10/5/24.
//

#include "StatusLineComponent.h"

void StatusLineComponent::render(display::Display& display) {
    if (const auto& state = this->getState(); state.isHidden()) {
        this->renderHidden(display);
        return;
    }  // render hidden representation if hidden

    this->modeIndicatorsComponent.render(display);
    this->clockComponent.render(display);

    if (const auto& state = this->getState(); state.isDisplayMeasurementsStatusIcon()) {
        this->measurementsStatusIconComponent.render(display);
    }
}

void StatusLineComponent::renderHidden(display::Display& display) const {
    // TODO: implement if needed
}
