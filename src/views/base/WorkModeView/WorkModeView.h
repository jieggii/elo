//
// Created by jieggii on 9/20/24.
//

#ifndef WORKMODEVIEW_H
#define WORKMODEVIEW_H

#include "Buzzer.h"
#include "Display.h"
#include "ViewNavigator.h"
#include "views/base/TimedModeView/TimedModeView.h"

#include "Settings.h"

#include "sfx.h"

namespace WorkModeViewSettings {
    /**
     * Duration of the posture reminder flash notification in milliseconds.
     */
    constexpr uint16_t postureReminderFlashNotificationDuration = 3000;
}  // namespace WorkModeViewSettings

/**
 * Base class for all mode views that are timed and have a posture reminder and exercise timer.
 */
class WorkModeView : public TimedModeView {
   public:
    /**
     * @param hardware
     * @param viewNavigator
     * @param duration duration of the view in seconds
     * @param nextViewID
     * @param measurementsLineComponentState reference to the static measurements line component state
     * @param postureReminderInterval posture reminder interval in milliseconds.
     * @param exerciseInterval exercise interval in milliseconds
     * TODO: remove duration param.
     */
    WorkModeView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
                 MeasurementsLineComponentState& measurementsLineComponentState,
                 const settings::EnvironmentEvaluation& envEvalSettings, const settings::WorkMode& workModeSettings)
        : TimedModeView(hardware, viewNavigator, nextViewID, measurementsLineComponentState, workModeSettings.duration,
                        envEvalSettings),
          postureReminderTimer(workModeSettings.postureReminder.interval) {}  // TODO: do Timer(...)

    void setup(const uint32_t now, display::Display& display) override {
        // set posture reminder timer:
        // (NOTE: there is no need to pause it in the setup as it will be paused in the update method automatically)
        this->postureReminderTimer.set(now);

        this->TimedModeView::setup(now, display);
    }

    void handleInputs(const uint32_t now) override { this->TimedModeView::handleInputs(now); }

    void update(const uint32_t now) override {
        if (this->isPaused() && this->wasJustPaused()) {
            // pause posture reminder and exercise timers when view is paused:
            this->postureReminderTimer.pause(now);
        } else {
            if (this->wasJustResumed()) {
                this->postureReminderTimer.resume(now);
            }

            // play posture reminder if it is time to:
            if (this->postureReminderTimer.isExpired(now)) {
                debug_println("POSTURE REMINDER timer expired");
                this->ModeView::hardware.buzzer.scheduleMelody(sfx::postureReminder, std::size(sfx::postureReminder));
                this->postureReminderTimer.set(now);

                this->displayFlashNotification(
                    now, "Remember about  your posture!",  // TODO: add more texts, rotate them randomly
                    // TODO: use PROGMEM to store string literals
                    WorkModeViewSettings::postureReminderFlashNotificationDuration);
            }
        }

        this->TimedModeView::update(now);
    }
    void render(display::Display& display) override { this->TimedModeView::render(display); }
    void reset(const uint32_t now) override { this->TimedModeView::reset(now); }

    // ~WorkModeView() override = default;

   private:
    /**
     * Timer used to remind about the posture.
     */
    Timer postureReminderTimer;
};

#endif  // WORKMODEVIEW_H
