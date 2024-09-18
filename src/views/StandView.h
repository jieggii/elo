//
// Created by jieggii on 9/4/24.
//

#ifndef ELO_STANDVIEW_H
#define ELO_STANDVIEW_H

#include "LCD1602.h"
#include "EnvSensor.h"
#include "ViewController.h"
#include "Settings.h"
#include "Timer.h"

#include <utility>

class StandView : public View {
   private:
    struct Hardware {
        EnvSensor* env_sensor;
    } hardware;

    struct Timers {
        Timer mainTimer; // the main timer of the stand work mode. When it's expired, the state is paused and waits for user input to switch to the sit view.
        Timer exerciseBreakTimer; // timer of the exercise break.
        Timer postureReminderTimer; // timer for the posture reminder
    } timers;

    OperationalConfig* const operationalConfig;

    struct MeasurementsLine {
        enum class State{
            MEASUREMENTS, // measurements are being displayed
            STATUSES, // measurement statuses are being displayed.
        };

        State state = State::MEASUREMENTS; // current state of the measurements line
        Timer displayMeasurementsTimer = Timer(2000); // timer
        Timer displayStatusesTimer = Timer(500);
    } measurementsLine;

    bool isPaused = false;

   public:
    StandView(LCD1602* display, ViewNavigator* navigator, OperationalConfig* operationalConfig, EnvSensor* env_sensor);

    void setup() override;
    void render() override;
    void loop() override;
};

#endif  // ELO_STANDVIEW_H
