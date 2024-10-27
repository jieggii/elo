//
// Created by jieggii on 9/20/24.
//

#ifndef WORKMODEVIEW_H
#define WORKMODEVIEW_H

#include "Display.h"
#include "ViewNavigator.h"
#include "views/base/TimedModeView/TimedModeView.h"

#include <Buzzer.h>

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
     */
    WorkModeView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
                 MeasurementsLineComponentState& measurementsLineComponentState, const uint16_t duration,
                 const uint32_t postureReminderInterval, const uint32_t exerciseInterval)
        : TimedModeView(hardware, viewNavigator, nextViewID, measurementsLineComponentState, duration),
          postureReminderTimer(postureReminderInterval),
          exerciseTimer(exerciseInterval) {}

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
                this->hardware.buzzer.scheduleNote(440, 100);  // TODO: use constants for frequency and duration
                this->postureReminderTimer.set(now);

                this->displayFlashNotification(now, "test", 3000);  // TODO: test this out
            }

            if (this->exerciseTimer.isExpired(now)) {
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
