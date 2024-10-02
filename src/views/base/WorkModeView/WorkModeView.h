//
// Created by jieggii on 9/20/24.
//

#ifndef WORKMODEVIEW_H
#define WORKMODEVIEW_H

#include "LCD1602.h"
#include "ViewNavigator.h"
#include "views/base/TimedModeView/TimedModeView.h"

/**
 * Base class for all mode views that are timed and have a posture reminder and exercise timer.
 */
class WorkModeView : public TimedModeView {
    Timer postureReminderTimer;
    Timer exerciseTimer;

   public:
    /**
     * @param viewNavigator
     * @param modeIndicatorIcon1ID
     * @param modeIndicatorIcon2ID
     * @param duration
     * @param nextViewID
     * @param postureReminderInterval - posture reminder interval in seconds
     * @param exerciseInterval - exercise interval in seconds
     */
    WorkModeView(ViewNavigator* viewNavigator, const uint8_t modeIndicatorIcon1ID, const uint8_t modeIndicatorIcon2ID,
                 const uint16_t duration, const uint8_t nextViewID, const uint16_t postureReminderInterval,
                 const uint16_t exerciseInterval)
        : TimedModeView(viewNavigator, modeIndicatorIcon1ID, modeIndicatorIcon2ID, duration, nextViewID),
          postureReminderTimer(Timer(static_cast<uint32_t>(postureReminderInterval * 1000))),
          exerciseTimer(Timer(static_cast<uint32_t>(exerciseInterval * 1000))) {}

    void setup(LCD1602* display) override = 0;
    void loop() override = 0;
    void render(LCD1602* display) override = 0;
    void reset() override = 0;

    ~WorkModeView() override;
};

#endif  // WORKMODEVIEW_H
