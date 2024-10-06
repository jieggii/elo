//
// Created by jieggii on 10/5/24.
//

#include "ModeView.h"

void ModeView::setup(Display* display, const Icon* indicatorIcon1, const Icon* indicatorIcon2) {
    cacheModeIndicatorIcons(display, indicatorIcon1, indicatorIcon2);
    cacheMeasurementStatusIcons(display);

    const uint32_t now = millis();  // TODO: get current time from param provided to the method
    this->measurementsTimer.set(now);
}

void ModeView::loop() {
    if (const uint32_t now = millis(); this->measurementsTimer.isExpired(now)) {
        this->measurementsTimer.set(now);
        const EnvSensorMeasurements measurements = this->hardware.envSensor->read();
        this->components.measurementsLine.setMeasurements(measurements);

        // TODO: assess measurements and choose suitable icons:
        const MeasurementsLineComponent::MeasurementStatusIconIDs measurementStatusIconIDs = {
            .temperature = ModeViewIconIDs::measurementStatusOptimal,
            .humidity = ModeViewIconIDs::measurementStatusAcceptable,
            .co2 = ModeViewIconIDs::measurementStatusBad};
        this->components.measurementsLine.setMeasurementStatusIconIDs(measurementStatusIconIDs);
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
