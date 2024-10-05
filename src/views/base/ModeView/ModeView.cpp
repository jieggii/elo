//
// Created by jieggii on 10/5/24.
//

#include "ModeView.h"

void ModeView::setup(Display* display) {
    const uint32_t now = millis();
    this->measurementsTimer.set(now);
}

void ModeView::loop() {
    if (const uint32_t now = millis(); this->measurementsTimer.isExpired(now)) {
        this->measurementsTimer.set(now);
        const EnvSensorMeasurements measurements = this->hardware.envSensor->read();
        this->components.measurementsLine.setMeasurements(measurements);

        // TODO: assess measurements and choose suitable icons:
        const MeasurementsLineComponent::MeasurementStatusIconIDs measurementStatusIconIDs = {
            .temperature = this->measurementStatusIconIDs.optimal,
            .humidity = this->measurementStatusIconIDs.acceptable,
            .co2 = this->measurementStatusIconIDs.bad};
        this->components.measurementsLine.setMeasurementStatusIconIDs(measurementStatusIconIDs);
    }
}

void ModeView::render(Display* display) {
    this->components.statusLine.render(display);
    this->components.measurementsLine.render(display);
}

void ModeView::setStatusLineClockTime(const ClockTime time) { this->components.statusLine.setClockTime(time); }
