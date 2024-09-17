//
// Created by jieggii on 9/4/24.
//

#ifndef ELO_STANDVIEW_H
#define ELO_STANDVIEW_H

#include "LCD1602.h"
#include "SCD40.h"
#include "ViewController.h"
#include "OperationalConfig.h"
#include "Timer.h"

#include <utility>

class StandView : public View {
   private:
    struct Hardware {
        SCD40* env_sensor;
    } hardware;

    struct Timers {
        Timer mainTimer; // main timer of the current state (stand)
        Timer exerciseBreakTimer; // timer of the exersiseBreak
        Timer postureReminderTimer; // timer for the posture reminder
    } timers;

    bool isPaused;
    OperationalConfig* const operationalConfig;

   public:
    StandView(LCD1602* display, ViewNavigator* navigator, OperationalConfig* operationalConfig,
              SCD40* env_sensor);

    void setup() override;
    void render() override;
    void loop() override;
};

#endif  // ELO_STANDVIEW_H
