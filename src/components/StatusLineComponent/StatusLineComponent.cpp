//
// Created by jieggii on 10/5/24.
//

#include "StatusLineComponent.h"

void StatusLineComponent::render(Display& display) {
    this->modeIndicatorsComponent.render(display);
    this->clockComponent.render(display);

    if (const auto& state = this->getState(); state.isDisplayMeasurementsStatusIcon()) {
        this->measurementsStatusIconComponent.render(display);
    }
}
