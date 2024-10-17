//
// Created by jieggii on 9/30/24.
//

#ifndef EXPIREABLEMODEVIEW_H
#define EXPIREABLEMODEVIEW_H

#include <cstdint>
#include "Timer.h"
#include "views/base/ModeView/ModeView.h"
#include "components/ClockComponent/ClockComponent.h"

/**
 * TimedModeView is a base class for all mode views that have a duration, i.e. can be paused, expire, and navigate to
 * the next view.
 */
class TimedModeView : public ModeView {
   public:
    /**
     * @param hardware
     * @param viewNavigator - pointer to the ViewNavigator.
     * @param nextViewID - ID of the next view.
     * @param measurementsLineComponentState pointer to the MeasurementsLineComponentState (TODO: use referenses).
     * @param duration - duration of the view in seconds.
     */
    TimedModeView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
                  MeasurementsLineComponentState& measurementsLineComponentState, const uint16_t duration)
        : ModeView(hardware, viewNavigator, nextViewID, ClockTime::fromSTimestamp(duration),
                   measurementsLineComponentState),
          viewTimer(Timer::fromSeconds(duration)) {}

    void setup(Display& display) override { this->ModeView::setup(display); }

    void handleInputs() override { ModeView::handleInputs(); }

    void serveExpired() {
        // TODO: blink timer
    }

    void serveNonExpired() {
        // TODO get now from param
        const uint32_t now = millis();
        if (this->viewTimer.isExpired(now)) {
            // TODO: beep
            this->isExpired = true;
        }
    }

    void loop() override {
        const uint32_t now = millis();  // TODO get now from param

        if (!this->isExpired) {
            this->serveNonExpired();
        } else {
            this->serveExpired();
        }

        // debug_println(this->viewTimer.left(now));
        this->setStatusLineClockTime(ClockTime::fromMsTimestamp(this->viewTimer.left(now)));

        this->ModeView::loop();

        // auto x = this->statusLineState.getClockComponentState().getTime();
        // debug_print(x.hours);
        // debug_print(":");
        // debug_print(x.minutes);
        // debug_print(":");
        // debug_println(x.seconds);
    }

    void render(Display& display) override { this->ModeView::render(display); }

    void reset() override { this->ModeView::reset(); }

   protected:
    void pause() { this->isPaused = true; };

    void resume(const uint32_t now) {
        this->isPaused = false;
        // TODO: do something with timer
    };

   private:
    /**
     * Timer used to track view expiration.
     */
    Timer viewTimer;

    bool isPaused = false;
    bool isExpired = false;
};

#endif  // EXPIREABLEMODEVIEW_H
