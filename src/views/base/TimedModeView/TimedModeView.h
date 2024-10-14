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
     * @param duration - duration of the view in seconds.
     */
    TimedModeView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID,
                  MeasurementsLineComponentState* measurementsLineComponentState, const uint16_t duration)
        : ModeView(hardware, viewNavigator, nextViewID, ClockTime::fromSTimestamp(duration),
                   measurementsLineComponentState),
          viewTimer(Timer::fromSeconds(duration)) {}

    void setup(Display& display) override { this->ModeView::setup(display); }
    void handleInputs() override { ModeView::handleInputs(); }
    void loop() override { this->ModeView::loop(); }
    void render(Display& display) override {
        const uint32_t now = millis();  // TODO get now from param
        this->setStatusLineClockTime(ClockTime::fromMsTimestamp(this->viewTimer.left(now)));
        this->ModeView::render(display);
    }
    void reset() override { this->ModeView::reset(); }

   protected:
    [[nodiscard]] bool isExpired(const uint32_t now) const { return this->viewTimer.isExpired(now); }

   private:
    Timer viewTimer;  // timer used to track view expiration
};

#endif  // EXPIREABLEMODEVIEW_H
