//
// Created by jieggii on 9/20/24.
//

#ifndef WORKMODEVIEW_H
#define WORKMODEVIEW_H

#include "Display.h"
#include "ViewNavigator.h"
#include "views/base/TimedModeView/TimedModeView.h"

/**
 * Base class for all mode views that are timed and have a posture reminder and exercise timer.
 */
class WorkModeView : public TimedModeView {
   public:
    /**
     * @param hardware
     * @param viewNavigator
     * @param duration - duration of the view in seconds
     * @param nextViewID
     * @param postureReminderInterval - posture reminder interval in seconds
     * @param exerciseInterval - exercise interval in seconds
     */
    WorkModeView(const Hardware hardware, ViewNavigator* viewNavigator, const uint8_t nextViewID,
                 const uint16_t duration, const uint16_t postureReminderInterval, const uint16_t exerciseInterval)
        : TimedModeView(hardware, viewNavigator, nextViewID, duration),
          postureReminderTimer(Timer::fromSeconds(postureReminderInterval)),
          exerciseTimer(Timer::fromSeconds(exerciseInterval)) {}

    void setup(Display* display) override { this->TimedModeView::setup(display); }
    void loop() override {
        const uint32_t now = millis();  // TODO: get now from param

        if (this->postureReminderTimer.isExpired(now)) {
            // TODO
        }

        if (this->exerciseTimer.isExpired(now)) {
            // TODO
        }

        if (this->isExpired(now)) {
            // TODO
        }

        this->TimedModeView::loop();
    }
    void render(Display* display) override { this->TimedModeView::render(display); }
    void reset() override { this->TimedModeView::reset(); }

    // ~WorkModeView() override = default;

   private:
    Timer postureReminderTimer;
    Timer exerciseTimer;
};

#endif  // WORKMODEVIEW_H
