//
// Created by jieggii on 10/5/24.
//

#include "binary.h"

#include "sfx.h"

#include "ModeView.h"

void ModeView::setup(const uint32_t now, Display& display) {
    // cache icons:
    cacheMeasurementStatusIcons(display);

    // reset measurements timer:
    this->measurementsTimer.set(now);

    // reset flags related to flash notification:
    this->isDisplayingFlashNotification = false;
    this->justStoppedDisplayingFlashNotification = false;
}

void ModeView::handleInputs(const uint32_t now) {
    // update select button state:
    this->hardware.selectButton.update();

    // navigate to the next view if the select button is pressed:
    if (this->hardware.selectButton.isActuated()) {
        this->hardware.buzzer.scheduleMelody(SFX::switchView, std::size(SFX::switchView));
        this->navigateToNextView();
    }
}

void ModeView::update(const uint32_t now) {
    if (this->isDisplayingFlashNotification) {
        this->components.flashNotification.update(now);

        // check whether it is time to stop displaying flash notification:
        if (const Timer& flashNotificationTimer = this->components.flashNotification.getState().getTimer();
            flashNotificationTimer.isExpired(now)) {
            this->isDisplayingFlashNotification = false;
            this->justStoppedDisplayingFlashNotification = true;
        }
    }

    // perform measurements if it is time to do so:
    if (this->measurementsTimer.isExpired(now)) {
        this->measurementsTimer.set(now);

        if (const EnvSensorMeasurements measurements = this->hardware.envSensor.readMeasurements();
            measurements.fresh) {
            // evaluate measurements:
            const env_eval::Evaluation temperatureEval = env_eval::evaluateByRange<temperatureType>(
                measurements.temperature, this->envEvalSettings.temperature.optimal,
                this->envEvalSettings.temperature.acceptable);

            const env_eval::Evaluation humidityEval =
                env_eval::evaluateByRange<humidityType>(measurements.humidity, this->envEvalSettings.humidity.optimal,
                                                        this->envEvalSettings.humidity.acceptable);

            const env_eval::Evaluation co2Eval = env_eval::evaluateByMax<co2Type>(
                measurements.co2, this->envEvalSettings.co2.max_optimal, this->envEvalSettings.co2.max_acceptable);

            const env_eval::Evaluation overallEval =
                env_eval::averageEvaluation(temperatureEval, humidityEval, co2Eval);

            // get status icons for measurements according to their evaluations:
            const uint8_t temperatureStatusIconID = getEnvStatusIconID(temperatureEval);
            const uint8_t humidityStatusIconID = getEnvStatusIconID(humidityEval);
            const uint8_t co2StatusIconID = getEnvStatusIconID(co2Eval);

            const uint8_t overallStatusIconID = getEnvStatusIconID(overallEval);

            // TODO: play a sound if it is the first time when measurements available
            // TODO: show a notification when the env conditions are changed

            // update measurements line:
            MeasurementsLineComponentState& measurementsLineState = this->components.measurementsLine.getState();
            measurementsLineState.setMeasurements(
                MeasurementsLineComponentState::Measurements::fromEnvSensorMeasurements(&measurements));

            measurementsLineState.setMeasurementStatusIconIDs(
                {.temperature = temperatureStatusIconID, .humidity = humidityStatusIconID, .co2 = co2StatusIconID});

            if (!measurementsLineState.isDisplayMeasurementStatusIcons()) {
                // play a melody and start displaying measurements if they are available for the first time:
                this->hardware.buzzer.scheduleMelody(SFX::measurementsAvailable, std::size(SFX::measurementsAvailable));
                measurementsLineState.setDisplayMeasurementStatusIcons(true);
                measurementsLineState.getDisplayMeasurementsTimer().set(now);
            }

            // update status line:
            StatusLineComponentState& statusLineState = this->components.statusLine.getState();
            statusLineState.getMeasurementsStatusIconsComponentState().setIconID(overallStatusIconID);
            if (!statusLineState.isDisplayMeasurementsStatusIcon()) {
                statusLineState.setDisplayMeasurementsStatusIcon(true);
            }
        }
    }

    // update measurements line:
    this->components.measurementsLine.update(now);
}

void ModeView::render(Display& display) {
    if (this->isDisplayingFlashNotification) {
        // render flash notification if displaying it:
        this->components.flashNotification.render(display);
    } else {
        // otherwise, clear the display if flash notification has just stopped displaying, and render status line and
        // measurements line:
        if (this->justStoppedDisplayingFlashNotification) {
            this->justStoppedDisplayingFlashNotification = false;
            display.clear();
        }

        this->components.statusLine.render(display);
        this->components.measurementsLine.render(display);
    }
}

void ModeView::navigateToNextView() const { this->navigateTo(this->nextViewID); }

void ModeView::cacheModeIndicatorIcons(Display& display, const Icon* icon1, const Icon* icon2) {
    display.cacheIcon(ModeViewIconIDs::indicator1, icon1);
    display.cacheIcon(ModeViewIconIDs::indicator2, icon2);
}

void ModeView::displayFlashNotification(const uint32_t now, const char* text, const uint32_t duration) {
    // set up flash notification:
    FlashNotificationComponentState& flashNotificationState = this->components.flashNotification.getState();
    Timer& flashNotificationTimer = flashNotificationState.getTimer();

    flashNotificationState.setText(text);
    flashNotificationTimer.setDuration(duration);
    flashNotificationTimer.set(now);

    // start displaying flash notification:
    this->isDisplayingFlashNotification = true;
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

void ModeView::reset(const uint32_t now) {}
