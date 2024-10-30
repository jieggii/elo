//
// Created by jieggii on 9/30/24.
//

#ifndef EXPIREABLEMODEVIEW_H
#define EXPIREABLEMODEVIEW_H

#include <cstdint>

#include "Buzzer.h"
#include "Timer.h"

#include "Settings.h"

#include "sfx.h"

#include "views/base/ModeView/ModeView.h"

namespace TimedModeViewSettings {
    /**
     * Blinking interval of the clock component when the view is paused (milliseconds).
     */
    constexpr uint16_t statusLineClockBlinkIntervalWhenPaused = 1250;
}  // namespace TimedModeViewSettings

/**
 * TimedModeView is a base class for all mode views that have a duration, i.e. can be paused, expire, and navigate to
 * the next view.
 */
class TimedModeView : public ModeView {
   public:
    /**
     * Additional hardware dependencies of the view.
     * Other dependencies are inherited from the ModeView.
     */
    struct AdditionalHardware {
        Button& actionButton;
    };

    /**
     * All hardware dependencies of the view.
     */
    struct Hardware {
        ModeView::Hardware hardware;
        AdditionalHardware additionalHardware;
    };

    /**
     * @param hardware
     * @param viewNavigator - pointer to the ViewNavigator.
     * @param nextViewID - ID of the next view.
     * @param measurementsLineComponentState pointer to the MeasurementsLineComponentState (TODO: use referenses).
     * @param duration - duration of the view in seconds.
     * TODO: consider passing hardware by a (const) reference.
     * TODO: is this way to handle and pass hardware dependencies the best?
     * TODO: rename localHardware to something more meaningful.
     */
    TimedModeView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
                  MeasurementsLineComponentState& measurementsLineComponentState, const uint32_t duration,
                  const settings::EnvironmentEvaluation& envEvalSettings)
        : ModeView(hardware.hardware, viewNavigator, nextViewID, ClockTime::fromMsTimestamp(duration),
                   measurementsLineComponentState, envEvalSettings),
          hardware(hardware.additionalHardware),
          viewTimer(Timer(duration)) {}

    void setup(const uint32_t now, display::Display& display) override {
        this->viewTimer.set(now);              // set the view timer
        this->resetStatusLineClockState(now);  // reset the clock component state
        this->pause(now);                      // pause the view on setup

        this->ModeView::setup(now, display);
    }

    void handleInputs(const uint32_t now) override {
        // update action button state:
        this->hardware.actionButton.update();

        // pause/resume view if action button is actuated:
        if (this->hardware.actionButton.isActuated()) {
            if (!this->paused) {
                // play a pause sfx:
                this->ModeView::hardware.buzzer.scheduleMelody(sfx::pause, std::size(sfx::pause));

                // pause the view:
                this->pause(now);
            } else {
                // play a resume sfx:
                this->ModeView::hardware.buzzer.scheduleMelody(sfx::resume, std::size(sfx::resume));

                // resume the view:
                this->resume(now);
            }
        }

        ModeView::handleInputs(now);
    }

    void update(const uint32_t now) override {
        // update clock component time:
        const ClockTime time = ClockTime::fromMsTimestamp(this->viewTimer.left(now));
        this->components.statusLine.getState().getClockComponentState().setTime(time);

        if (this->paused) {
            // reset justPaused flag:
            this->justPaused = false;

            // handle paused view:
            if (this->blinkClockTimer.isExpired(now)) {
                // blink the clock component:
                if (auto& clockComponentState = this->components.statusLine.getState().getClockComponentState();
                    clockComponentState.isHidden()) {
                    clockComponentState.show();
                } else {
                    clockComponentState.hide();
                }
                this->blinkClockTimer.set(now);
            }
        } else {
            // reset justResumed flag:
            this->justResumed = false;

            // handle ongoing view:
            if (this->viewTimer.isExpired(now)) {
                // play an expiration melody:

                // TODO: define a "melody", use a separate file for that
                for (uint8_t i = 0; i < 3; i++) {
                    // this->hardware.buzzer.scheduleNote(440, 250, 500);
                }

                // navigate to the next view:
                this->navigateToNextView();
            }
        }

        this->ModeView::update(now);
    }

    void render(display::Display& display) override { this->ModeView::render(display); }

    void reset(const uint32_t now) override { this->ModeView::reset(now); }

    [[nodiscard]] bool isPaused() const { return this->paused; }

   protected:
    /**
     * Hardware dependencies of the view.
     */
    AdditionalHardware hardware;

    [[nodiscard]] bool wasJustPaused() const { return this->justPaused; }
    [[nodiscard]] bool wasJustResumed() const { return this->justResumed; }

   private:
    /**
     * Timer used to track view expiration.
     */
    Timer viewTimer;

    /**
     * Flag indicating if the view is paused.
     */
    bool paused = true;

    /**
     * Flag indicating if the view has just been paused.
     */
    bool justPaused = true;

    /**
     * Flag indicating if the view has just been resumed.
     */
    bool justResumed = false;

    /**
     * Timer used to blink the clock component when view is paused.
     */
    Timer blinkClockTimer = Timer(TimedModeViewSettings::statusLineClockBlinkIntervalWhenPaused);

    /**
     * Resets the clock component state and the blink clock timer.
     */
    void resetStatusLineClockState(const uint32_t now) {
        this->blinkClockTimer.set(now);
        this->components.statusLine.getState().getClockComponentState().show();
    }

    /**
     * Pauses the view.
     */
    void pause(const uint32_t now) {
        // update flags:
        this->paused = true;
        this->justPaused = true;

        // pause view timer:
        this->viewTimer.pause(now);
    }

    /**
     * Resumes the view.
     */
    void resume(const uint32_t now) {
        // update flags:
        this->paused = false;
        this->justResumed = true;

        // resume view timer:
        this->viewTimer.resume(now);

        // reset status line clock state:
        this->resetStatusLineClockState(now);
    }

    /**
     * Returns true if the view is paused.
     */
    // [[nodiscard]] bool isPaused() const { return this->paused; }
};

#endif  // EXPIREABLEMODEVIEW_H
