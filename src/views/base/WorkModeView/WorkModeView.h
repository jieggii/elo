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
                 MeasurementsLineComponentState& measurementsLineComponentState, const uint32_t exerciseInterval,
                 const Settings::EnvironmentEvaluation& envEvalSettings, const Settings::WorkMode& workModeSettings)
        : TimedModeView(hardware, viewNavigator, nextViewID, measurementsLineComponentState, workModeSettings.duration,
                        envEvalSettings),
          postureReminderTimer(workModeSettings.postureReminder.interval),  // TODO: do Timer(...)
          exerciseTimer(exerciseInterval) {}                                // TODO: do Timer(...)

    void setup(const uint32_t now, Display& display) override {
        // set posture reminder and exercise timers:
        // (NOTE: there is no need to pause them in the setup as they will be paused in the update method automatically)
        this->postureReminderTimer.set(now);
        this->exerciseTimer.set(now);

        this->TimedModeView::setup(now, display);
    }

    void handleInputs(const uint32_t now) override { this->TimedModeView::handleInputs(now); }

    void update(const uint32_t now) override {
        if (this->isPaused() && this->wasJustPaused()) {
            // pause posture reminder and exercise timers when view is paused:
            this->postureReminderTimer.pause(now);
            this->exerciseTimer.pause(now);
        } else {
            if (this->wasJustResumed()) {
                this->postureReminderTimer.resume(now);
                this->exerciseTimer.resume(now);
            }

            // play posture reminder if it is time to:
            if (this->postureReminderTimer.isExpired(now)) {
                debug_println("POSTURE REMINDER timer expired");
                this->ModeView::hardware.buzzer.scheduleMelody(SFX::postureReminder, std::size(SFX::postureReminder));
                this->postureReminderTimer.set(now);

                this->displayFlashNotification(
                    now, "Remember about  your posture!",  // TODO: add more texts, rotate them randomly
                    // TODO: use PROGMEM to store string literals
                    WorkModeViewSettings::postureReminderFlashNotificationDuration);
            }

            // go to exercise view if it is time to:
            if (this->exerciseTimer.isExpired(now)) {
                // TODO: implement
                debug_println("EXERCISE timer expired");
                this->exerciseTimer.set(now);
            }
        }

        this->TimedModeView::update(now);
    }
    void render(Display& display) override { this->TimedModeView::render(display); }
    void reset(const uint32_t now) override { this->TimedModeView::reset(now); }

    // ~WorkModeView() override = default;

   private:
    Timer postureReminderTimer;
    Timer exerciseTimer;
};

#endif  // WORKMODEVIEW_H
