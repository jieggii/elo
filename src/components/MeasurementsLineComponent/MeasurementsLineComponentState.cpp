//
// Created by jieggii on 10/12/24.
//

#include "MeasurementsLineComponentState.h"

Timer& MeasurementsLineComponentState::getDisplayMeasurementsTimer() { return this->displayMeasurementsTimer; }

Timer& MeasurementsLineComponentState::getDisplayStatusesTimer() { return this->displayStatusesTimer; }

void MeasurementsLineComponentState::setMeasurements(const Measurements measurements) {
    this->measurements = measurements;
}

MeasurementsLineComponentState::Measurements& MeasurementsLineComponentState::getMeasurements() {
    return this->measurements;
}

void MeasurementsLineComponentState::setState(const State state) { this->state = state; }

MeasurementsLineComponentState::State MeasurementsLineComponentState::getState() const { return this->state; }

void MeasurementsLineComponentState::setMeasurementStatusIconIDs(const MeasurementStatusIconIDs iconIDs) {
    this->measurementStatusIconIDs = iconIDs;
}

MeasurementsLineComponentState::MeasurementStatusIconIDs MeasurementsLineComponentState::getMeasurementStatusIconIDs() {
    return this->measurementStatusIconIDs;
}

bool MeasurementsLineComponentState::isDisplayMeasurementStatusIcons() const {
    return this->displayMeasurementStatusIcons;
}

void MeasurementsLineComponentState::setDisplayMeasurementStatusIcons(const bool displayMeasurementStatusIcons) {
    this->displayMeasurementStatusIcons = displayMeasurementStatusIcons;

    // set displayMeasurementsTimer so that measurements are displayed once again:
    // this->displayMeasurementsTimer.set(now);
}
