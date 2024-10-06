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
    WorkModeView(const Hardware hardware, ViewNavigator* viewNavigator, const uint16_t duration,
                 const uint8_t nextViewID, const uint16_t postureReminderInterval, const uint16_t exerciseInterval)
        : TimedModeView(hardware, viewNavigator, duration, nextViewID),
          postureReminderTimer(Timer::fromSeconds(postureReminderInterval)),
          exerciseTimer(Timer::fromSeconds(exerciseInterval)) {}

    void setup(Display* display) override = 0;
    void loop() override { TimedModeView::loop(); }
    void render(Display* display) override { TimedModeView::render(display); }
    void reset() override = 0;

    ~WorkModeView() override;

   private:
    Timer postureReminderTimer;
    Timer exerciseTimer;
};

#endif  // WORKMODEVIEW_H
