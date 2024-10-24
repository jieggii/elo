//
// Created by jieggii on 10/5/24.
//

#include "binary.h"
#include "ModeView.h"

void ModeView::setup(const uint32_t now, Display& display) {
    cacheMeasurementStatusIcons(display);
    this->measurementsTimer.set(now);

    display.clear();
}

void ModeView::handleInputs(const uint32_t now) {
    // update select button state:
    this->hardware.selectButton.update();

    // navigate to the next view if the select button is pressed:
    if (this->hardware.selectButton.isActuated()) {
        this->navigateToNextView();
    }
}

void ModeView::update(const uint32_t now) {
    // perform measurements if it is time to do so:
    if (this->measurementsTimer.isExpired(now)) {
        debug_println("performing measurements...");
        this->measurementsTimer.set(now);

        if (const auto measurements = this->hardware.envSensor.readMeasurements(); measurements.fresh) {
            this->updateStatusLineState(measurements);
            this->updateMeasurementsLineState(measurements);
            debug_println("measurements available");
        } else {
            debug_println("measurements are not fresh yet");
        }
    }

    // update measurements line
    this->components.measurementsLine.update(now);
}

void ModeView::render(Display& display) {
    this->components.statusLine.render(display);
    this->components.measurementsLine.render(display);
}

// void ModeView::setStatusLineClockTime(const ClockTime time) const {
//     auto& statusLineState = this->components.statusLine.getState();
//     statusLineState.getClockComponentState().setTime(time);
// }

void ModeView::navigateToNextView() const { this->navigateTo(this->nextViewID); }

void ModeView::cacheModeIndicatorIcons(Display& display, const Icon* icon1, const Icon* icon2) {
    display.cacheIcon(ModeViewIconIDs::indicator1, icon1);
    display.cacheIcon(ModeViewIconIDs::indicator2, icon2);
}

void ModeView::cacheMeasurementStatusIcons(Display& display) {
    // TODO: move icons to a separate file
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

    display.cacheIcon(ModeViewIconIDs::measurementStatusOptimal, &statusOptimalIcon);
    display.cacheIcon(ModeViewIconIDs::measurementStatusAcceptable, &statusAcceptableIcon);
    display.cacheIcon(ModeViewIconIDs::measurementStatusBad, &statusBadIcon);
}

void ModeView::reset() {}

void ModeView::updateMeasurementsLineState(const EnvSensorMeasurements& measurements) const {
    auto& measurementsLineState = this->components.measurementsLine.getState();

    measurementsLineState.setMeasurements(
        MeasurementsLineComponentState::Measurements::fromEnvSensorMeasurements(&measurements));

    // TODO: assess measurements and set status icons accordingly
    measurementsLineState.setMeasurementStatusIconIDs({.temperature = ModeViewIconIDs::measurementStatusOptimal,
                                                       .humidity = ModeViewIconIDs::measurementStatusAcceptable,
                                                       .co2 = ModeViewIconIDs::measurementStatusBad});

    measurementsLineState.setDisplayMeasurementStatusIcons(true);
}

void ModeView::updateStatusLineState(const EnvSensorMeasurements& measurements) const {
    auto& statusLineState = this->components.statusLine.getState();

    // TODO: assess measurements and set status icon accordingly
    statusLineState.getMeasurementsStatusIconsComponentState().setIconID(ModeViewIconIDs::measurementStatusBad);
    statusLineState.setDisplayMeasurementsStatusIcon(true);
}
