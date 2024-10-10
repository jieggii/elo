//
// Created by jieggii on 10/5/24.
//

#include "StatusLineComponent.h"

void StatusLineComponent::setEnvMeasurementsStatusIconID(const uint8_t iconID) {
    this->envMeasurementsStatusIcon.setIconID(iconID);
}

void StatusLineComponent::setClockTime(const ClockTime clockTime) { this->clock.setTime(clockTime); }

void StatusLineComponent::enableMeasurementsStatusIcon() { this->displayMeasurementsStatusIcon = true; }

void StatusLineComponent::disableMeasurementsStatusIcon() { this->displayMeasurementsStatusIcon = false; }

void StatusLineComponent::render(Display* display) {
    this->modeIndicators.render(display);
    this->clock.render(display);

    if (this->displayMeasurementsStatusIcon) {
        this->envMeasurementsStatusIcon.render(display);
    }
}
