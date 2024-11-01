//
// Created by jieggii on 10/12/24.
//

#include "MeasurementsLineComponentState.h"

uint32_t MeasurementsLineComponentState::getDisplayMeasurementsDuration() const {
    return this->displayMeasurementsDuration;
}

uint32_t MeasurementsLineComponentState::getDisplayEvaluationsDuration() const {
    return this->displayEvaluationsDuration;
}

Timer& MeasurementsLineComponentState::getSwitchStateTimer() { return this->switchStateTimer; }

Timer& MeasurementsLineComponentState::getUpdateMeasurementsTimer() { return this->updateMeasurementsTimer; }

void MeasurementsLineComponentState::setMeasurements(const Measurements measurements) {
    this->measurements = measurements;
}

void MeasurementsLineComponentState::setMeasurementEvaluationIconIDs(const MeasurementEvaluationIconIDs iconIDs) {
    this->measurementEvaluationIconIDs = iconIDs;
}

const MeasurementsLineComponentState::Measurements& MeasurementsLineComponentState::getMeasurements() const {
    return this->measurements;
}

MeasurementsLineComponentState::MeasurementEvaluationIconIDs
MeasurementsLineComponentState::getMeasurementEvaluationIconIDs() const {
    return this->measurementEvaluationIconIDs;
}

void MeasurementsLineComponentState::setDisplayingEvaluation(const bool displayingEvaluations) {
    this->displayingEvaluations = displayingEvaluations;
}

bool MeasurementsLineComponentState::isDisplayingEvaluation() const { return this->displayingEvaluations; }

void MeasurementsLineComponentState::setMeasurementsAvailable(const uint32_t now) {
    // setup and set timer switchStateTimer:
    this->switchStateTimer.setDuration(this->displayMeasurementsDuration);
    this->switchStateTimer.set(now);

    // update flag:
    this->measurementsAvailable = true;
}

bool MeasurementsLineComponentState::areMeasurementsAvailable() const { return this->measurementsAvailable; }
