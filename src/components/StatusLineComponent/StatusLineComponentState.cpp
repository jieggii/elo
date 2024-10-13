//
// Created by jieggii on 10/12/24.
//

#include "StatusLineComponentState.h"

ModeIndicatorsComponentState& StatusLineComponentState::getModeIndicatorsComponentState() {
    return modeIndicatorsComponentState;
}

ClockComponentState& StatusLineComponentState::getClockComponentState() { return clockComponentState; }

IconComponentState& StatusLineComponentState::getMeasurementsStatusIconsComponentState() {
    return this->measurementsStatusIconComponentState;
}

void StatusLineComponentState::setDisplayMeasurementsStatusIcon(const bool displayMeasurementsStatusIcon) {
    this->displayMeasurementsStatusIcon = displayMeasurementsStatusIcon;
}

bool StatusLineComponentState::isDisplayMeasurementsStatusIcon() const { return this->displayMeasurementsStatusIcon; }
