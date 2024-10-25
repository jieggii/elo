//
// Created by jieggii on 9/30/24.
//

#ifndef EXPIREABLEMODEVIEW_H
#define EXPIREABLEMODEVIEW_H

#include <cstdint>
#include "Timer.h"
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
     * Hardware dependencies of the view.
     */
    struct Hardware {
        ModeView::Hardware modeViewHardware;

        Button& actionButton;
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
                  MeasurementsLineComponentState& measurementsLineComponentState, const uint16_t duration)
        : ModeView(hardware.modeViewHardware, viewNavigator, nextViewID, ClockTime::fromSTimestamp(duration),
                   measurementsLineComponentState),
          hardware({.actionButton = hardware.actionButton}),
          viewTimer(Timer::fromSeconds(duration)) {}

    void setup(const uint32_t now, Display& display) override {
        this->viewTimer.set(now);  // set the view timer
        this->blinkClockTimer.set(now);
        this->pause(now);  // pause the view on setup

        this->ModeView::setup(now, display);
    }

    void handleInputs(const uint32_t now) override {
        // update action button state:
        this->hardware.actionButton.update();

        // pause/resume view if action button is actuated:
        if (this->hardware.actionButton.isActuated()) {
            if (!this->paused) {
                debug_println("PAUSE view");
                this->pause(now);
            } else {
                debug_println("RESUME view");
                this->resume(now);
            }
        }

        ModeView::handleInputs(now);
    }

    void update(const uint32_t now) override {
        // update clock component time:
        const ClockTime time = ClockTime::fromMsTimestamp(this->viewTimer.left(now));
        this->getComponents().statusLine.getState().getClockComponentState().setTime(time);

        if (this->paused) {
            // handle paused view:
            // TODO: move to a separate loop function?
            if (this->blinkClockTimer.isExpired(now)) {
                if (auto& clockComponentState = this->getComponents().statusLine.getState().getClockComponentState();
                    clockComponentState.isHidden()) {
                    clockComponentState.show();
                } else {
                    clockComponentState.hide();
                }
                this->blinkClockTimer.set(now);
            }
        } else {
            // handle ongoing view:
            if (this->viewTimer.isExpired(now)) {
                debug_println("view has expired");
                this->navigateToNextView();
            }
        }

        this->ModeView::update(now);
    }

    void render(Display& display) override { this->ModeView::render(display); }

    void reset(const uint32_t now) override { this->ModeView::reset(now); }

    [[nodiscard]] bool isPaused() const { return this->paused; }

   private:
    /**
     * Hardware dependencies of the view.
     */
    struct {
        Button& actionButton;
    } hardware;

    /**
     * Timer used to track view expiration.
     */
    Timer viewTimer;

    /**
     * Hardware used by the view.
     */
    // Hardware hardware;

    /**
     * Flag indicating if the view is paused.
     */
    bool paused = true;

    /**
     * Timer used to blink the clock component when view is paused.
     */
    Timer blinkClockTimer = Timer(TimedModeViewSettings::statusLineClockBlinkIntervalWhenPaused);

    /**
     * Pauses the view.
     */
    void pause(const uint32_t now) {
        this->paused = true;
        this->viewTimer.pause(now);
    }

    /**
     * Resumes the view.
     */
    void resume(const uint32_t now) {
        this->paused = false;
        this->viewTimer.resume(now);

        // show the clock component:
        // this is needed for the case when user resumed the view when the clock component was hidden
        this->getComponents().statusLine.getState().getClockComponentState().show();
    }

    /**
     * Returns true if the view is paused.
     */
    // [[nodiscard]] bool isPaused() const { return this->paused; }
};

#endif  // EXPIREABLEMODEVIEW_H
