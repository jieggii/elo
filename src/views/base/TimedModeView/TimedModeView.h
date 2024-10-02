//
// Created by jieggii on 9/30/24.
//

#ifndef EXPIREABLEMODEVIEW_H
#define EXPIREABLEMODEVIEW_H

#include <cstdint>
#include "Timer.h"
#include "views/base/ModeView/ModeView.h"
#include "views/base/ModeView/components/base/ClockComponent.h"

/**
 * TimedModeView is a base class for all mode views that have a duration, i.e. can be paused, expire, and navigate to
 * the next view.
 */
class TimedModeView : public ModeView {
   protected:
    uint8_t nextViewID;  // ID of the next view to navigate to after expiration
    Timer viewTimer;     // timer used to track view expiration

    bool isPaused = false;

   public:
    /**
     * @param viewNavigator - pointer to the ViewNavigator.
     * @param modeIndicatorIcon1ID - ID of the first mode indicator icon.
     * @param modeIndicatorIcon2ID - ID of the second mode indicator icon.
     * @param duration - duration of the view in seconds.
     * @param nextViewID - ID of the next view.
     */
    TimedModeView(ViewNavigator* viewNavigator, const uint8_t modeIndicatorIcon1ID, const uint8_t modeIndicatorIcon2ID,
                  const uint16_t duration, const uint8_t nextViewID)
        : ModeView(viewNavigator, modeIndicatorIcon1ID, modeIndicatorIcon2ID, ClockTime(duration)),
          nextViewID(nextViewID),
          viewTimer(static_cast<uint32_t>(duration * 1000)) {}

    void pause() { this->isPaused = true; }

    [[nodiscard]] bool getIsPaused() const { return this->isPaused; }
    [[nodiscard]] bool isExpired(const uint32_t now) const { return this->viewTimer.isExpired(now); }

    void navigateToNextView() const { this->viewNavigator->navigateTo(this->nextViewID); }

    void setup(LCD1602* display) override = 0;
    void loop() override = 0;
    void render(LCD1602* display) override = 0;
    void reset() override = 0;
};

#endif  // EXPIREABLEMODEVIEW_H
