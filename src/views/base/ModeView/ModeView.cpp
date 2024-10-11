//
// Created by jieggii on 10/5/24.
//

#include "ModeView.h"

void ModeView::setup(Display* display) {
    cacheMeasurementStatusIcons(display);

    const uint32_t now = millis();  // TODO: get current time from param provided to the method
    this->measurementsTimer.set(now);

    display->clear();
}

void ModeView::loop() {
    const uint32_t now = millis();  // todo: get from loop param

    // update measurements if it is time to do so:
    if (this->measurementsTimer.isExpired(now)) {
        // reset measurements timer
        this->measurementsTimer.set(now);

        // perform measurements and update information about measurements availability:
        if (this->hardware.envSensor->performMeasurements()) {  // if sensor could perform measurements
            const EnvSensorMeasurements measurements = this->hardware.envSensor->getMeasurements();

            // update the measurements on the measurements line:
            this->components.measurementsLine.setMeasurements(
                MeasurementsLineComponent::Measurements::fromEnvSensorMeasurements(&measurements));

            // assess measurements:
            // TODO: assess measurements and choose suitable icons:
            const MeasurementsLineComponent::MeasurementStatusIconIDs measurementStatusIconIDs = {
                .temperature = ModeViewIconIDs::measurementStatusOptimal,
                .humidity = ModeViewIconIDs::measurementStatusAcceptable,
                .co2 = ModeViewIconIDs::measurementStatusBad};

            // update overall measurement status icon on the status line:
            this->components.statusLine.setEnvMeasurementsStatusIconID(ModeViewIconIDs::measurementStatusBad);

            // update measurement status icons on the measurements line:
            this->components.measurementsLine.setMeasurementStatusIconIDs(measurementStatusIconIDs);

            // update ModeView state if necessary:
            if (!this->measurementsAvailable) {
                this->measurementsAvailable = true;
                this->components.statusLine.enableMeasurementsStatusIcon();
                this->components.measurementsLine.enableMeasurementStatusIcons(now);
            }
        } else {  // if sensor could not perform measurements
            // update ModeView state if necessary:
            if (this->measurementsAvailable) {
                this->measurementsAvailable = false;
                this->components.statusLine.disableMeasurementsStatusIcon();
                this->components.measurementsLine.disableMeasurementStatusIcons();
            }
        }
    }
}

void ModeView::render(Display* display) {
    this->components.statusLine.render(display);
    this->components.measurementsLine.render(display);
}

void ModeView::setStatusLineClockTime(const ClockTime time) { this->components.statusLine.setClockTime(time); }

void ModeView::cacheModeIndicatorIcons(Display* display, const Icon* icon1, const Icon* icon2) {
    display->cacheIcon(ModeViewIconIDs::indicator1, icon1);
    display->cacheIcon(ModeViewIconIDs::indicator2, icon2);
}

void ModeView::cacheMeasurementStatusIcons(Display* display) {
    constexpr Icon statusOptimalIcon = {
        // icon representing face :)
        B00000, B01010, B01010, B00000, B10001, B01110, B00000, B00000,
    };

    constexpr Icon statusAcceptableIcon = {
        // icon representing face :|
        B00000, B01010, B01010, B00000, B00000, B11111, B00000, B00000,
    };

    constexpr Icon statusBadIcon = {
        // icon representing face :(
        B00000, B01010, B01010, B00000, B00000, B01110, B10001, B00000,
    };

    display->cacheIcon(ModeViewIconIDs::measurementStatusOptimal, &statusOptimalIcon);
    display->cacheIcon(ModeViewIconIDs::measurementStatusAcceptable, &statusAcceptableIcon);
    display->cacheIcon(ModeViewIconIDs::measurementStatusBad, &statusBadIcon);
}

void ModeView::reset() {}