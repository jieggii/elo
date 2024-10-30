//
// Created by jieggii on 10/5/24.
//

#include "icon.h"
#include "sfx.h"

#include "ModeView.h"

/**
 * IDs of the icons used by the mode view.
 * NOTE: icon IDs must be unique and only from 1 to 7.
 */
namespace iconIds {
    namespace modeIndicator {
        // id of the first mode indicator icon.
        constexpr uint8_t indicator1 = 1;

        // id of the second mode indicator icon.
        constexpr uint8_t indicator2 = 2;
    }  // namespace modeIndicator

    namespace measurementStatus {
        // id of the icon representing optimal measurement status.
        constexpr uint8_t optimal = 3;

        // id of the icon representing acceptable measurement status.
        constexpr uint8_t acceptable = 4;

        // id of the icon representing bad measurement status.
        constexpr uint8_t bad = 5;

        // id of the icon representing placeholder for measurements.
        // constexpr uint8_t measurementsPlaceholder = 6;
    }  // namespace measurementStatus

}  // namespace iconIds

namespace Settings {
    /**
     * Interval between measurements updates in milliseconds.
     */
    constexpr uint16_t measurementsUpdateInterval = 10000;
}  // namespace Settings

/**
 * Returns an icon ID corresponding to the given environmental evaluation.
 * @param evaluation environmental measurement evaluation.
 * @return icon ID.
 */
uint8_t getEnvStatusIconID(const env_eval::Evaluation& evaluation) {
    switch (evaluation) {
        case env_eval::Evaluation::OPTIMAL:
            return iconIds::measurementStatus::optimal;
        case env_eval::Evaluation::ACCEPTABLE:
            return iconIds::measurementStatus::acceptable;
        case env_eval::Evaluation::BAD:
            return iconIds::measurementStatus::bad;
        default:
            return display::CGRAM::defaultIconSlot;
    }
}

ModeView::ModeView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
                   const ClockTime clockTime, MeasurementsLineComponentState& measurementsLineComponentState,
                   const settings::EnvironmentEvaluation& envEvalSettings)
    : View(),
      hardware(hardware),
      components({.statusLine = StatusLineComponent(this->componentStates.statusLine, {0, 0}),
                  .measurementsLine = MeasurementsLineComponent(measurementsLineComponentState, {0, 1}),
                  .flashNotification = FlashNotificationComponent(this->componentStates.flashNotification, {0, 0})}),
      viewNavigator(viewNavigator),
      nextViewID(nextViewID),
      componentStates({
          .statusLine = StatusLineComponentState(iconIds::modeIndicator::indicator1, iconIds::modeIndicator::indicator2,
                                                 clockTime),
          .flashNotification = FlashNotificationComponentState(),
      }),
      envEvalSettings(envEvalSettings) {}

void ModeView::setup(const uint32_t now, display::Display& display) {
    // cache icons:
    cacheMeasurementStatusIcons(display);

    // reset flags related to flash notification:
    this->isDisplayingFlashNotification = false;
    this->justStoppedDisplayingFlashNotification = false;
}

void ModeView::handleInputs(const uint32_t now) {
    // update select button state:
    this->hardware.selectButton.update();

    // navigate to the next view if the select button is pressed:
    if (this->hardware.selectButton.isActuated()) {
        this->hardware.buzzer.scheduleMelody(sfx::switchView, std::size(sfx::switchView));
        this->navigateToNextView();
    }
}

void ModeView::update(const uint32_t now) {
    // handle hardware:
    this->hardware.buzzer.serve(now);

    // handle flash notification if it is being displayed:
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
    if (Timer& updateMeasurementsTimer = this->components.measurementsLine.getState().getUpdateMeasurementsTimer();
        updateMeasurementsTimer.isExpired(now)) {
        updateMeasurementsTimer.set(now);

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

            // TODO: show a notification when the env conditions are changed

            // update measurements line:
            MeasurementsLineComponentState& measurementsLineState = this->components.measurementsLine.getState();
            measurementsLineState.setMeasurements(
                MeasurementsLineComponentState::Measurements::fromEnvSensorMeasurements(&measurements));

            measurementsLineState.setMeasurementStatusIconIDs(
                {.temperature = temperatureStatusIconID, .humidity = humidityStatusIconID, .co2 = co2StatusIconID});

            if (!measurementsLineState.isDisplayMeasurementStatusIcons()) {
                // play a melody and start displaying measurements if they are available for the first time:
                this->hardware.buzzer.scheduleMelody(sfx::measurementsAvailable, std::size(sfx::measurementsAvailable));
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

void ModeView::render(display::Display& display) {
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

void ModeView::cacheModeIndicatorIcons(display::Display& display, const Icon* icon1, const Icon* icon2) {
    display.cacheIcon(iconIds::modeIndicator::indicator1, icon1);
    display.cacheIcon(iconIds::modeIndicator::indicator2, icon2);
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

void ModeView::navigateToNextView() const { this->viewNavigator.navigateTo(this->nextViewID); }

void ModeView::cacheMeasurementStatusIcons(display::Display& display) {
    display.cacheIcon(iconIds::measurementStatus::optimal, &icon::measurementStatus::optimal);
    display.cacheIcon(iconIds::measurementStatus::acceptable, &icon::measurementStatus::acceptable);
    display.cacheIcon(iconIds::measurementStatus::bad, &icon::measurementStatus::bad);
}

void ModeView::reset(const uint32_t now) {}
