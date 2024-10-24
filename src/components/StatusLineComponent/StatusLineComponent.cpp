//
// Created by jieggii on 10/5/24.
//

#include "StatusLineComponent.h"

void StatusLineComponent::render(Display& display) {
    if (const auto& state = this->getState(); state.isHidden()) {
        return;
    }  // do not render if hidden

    this->modeIndicatorsComponent.render(display);
    this->clockComponent.render(display);

    if (const auto& state = this->getState(); state.isDisplayMeasurementsStatusIcon()) {
        this->measurementsStatusIconComponent.render(display);
    }
}
