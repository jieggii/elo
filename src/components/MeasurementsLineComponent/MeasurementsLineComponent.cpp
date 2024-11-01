//
// Created by jieggii on 10/4/24.
//

#include "debug_print.h"
#include "MeasurementsLineComponent.h"
#include "MeasurementsLineComponentState.h"

void MeasurementsLineComponent::update(const uint32_t now) {
    MeasurementsLineComponentState& state = this->getState();

    // do nothing if measurements are not available yet:
    if (!state.areMeasurementsAvailable()) {
        return;
    }

    // switch state (from displaying measurements to displaying evaluations and vice versa) if it is time to do so:
    if (Timer& switchStateTimer = state.getSwitchStateTimer(); switchStateTimer.isExpired(now)) {
        if (state.isDisplayingEvaluation()) {
            state.setDisplayingEvaluation(false);
            switchStateTimer.setDuration(state.getDisplayMeasurementsDuration());
        } else {
            state.setDisplayingEvaluation(true);
            switchStateTimer.setDuration(state.getDisplayEvaluationsDuration());
        }
        switchStateTimer.set(now);
    }
}

void MeasurementsLineComponent::render(display::Display& display) {
    const MeasurementsLineComponentState& state = this->getState();
    if (state.isHidden()) {  // render hidden representation if hidden
        this->renderHidden(display);
        return;
    }

    if (!state.areMeasurementsAvailable()) {
        // just display the render buffer without measurements if measurements are not available:
        if (this->renderBuffer.isFormattedWithMeasurements()) {
            this->renderBuffer.removeMeasurements();
        }

        display.displayText(renderBuffer.getBuffer(), this->coordinates);
        return;
    }

    if (state.isDisplayingEvaluation()) {
        // remove measurements from the buffer if they are present:
        if (this->renderBuffer.isFormattedWithMeasurements()) {
            this->renderBuffer.removeMeasurements();
        }

        // display render buffer without measurements:
        display.displayText(renderBuffer.getBuffer(), this->coordinates);

        // display measurement evaluation icons on top of the render buffer:
        const MeasurementsLineComponentState::MeasurementEvaluationIconIDs iconIds =
            state.getMeasurementEvaluationIconIDs();
        display.displayIcon(iconIds.temperature, {1, this->coordinates.row});
        display.displayIcon(iconIds.humidity, {6, this->coordinates.row});
        display.displayIcon(iconIds.temperature, {12, this->coordinates.row});

    } else {
        // add measurements to the buffer if they are not present:
        if (!this->renderBuffer.isFormattedWithMeasurements()) {
            const auto& [temperature, humidity, co2] = state.getMeasurements();
            this->renderBuffer.formatMeasurements(temperature, humidity, co2);
        }

        // display render buffer with measurements:
        display.displayText(renderBuffer.getBuffer(), this->coordinates);
    }
}

void MeasurementsLineComponent::renderHidden(display::Display& display) const {
    // not implemented as not used in the current use case.
}
