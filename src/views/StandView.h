//
// Created by jieggii on 9/4/24.
//

#ifndef ELO_STANDVIEW_H
#define ELO_STANDVIEW_H

#include "LCD1602.h"
#include "SCD40.h"
#include "ViewController.h"
#include "OperationalConfig.h"

#include <utility>

#define DISPLAY_REFRESH_RATE 1  // (times per second)

class StandView : public View {
   private:
    // todo: use namespaces
    OperationalConfig* const operationalConfig;
    SCD40* env_sensor;

    uint8_t some_var = 0;
    uint16_t timer;

   public:
    StandView(LCD1602* display, ViewNavigator* navigator, OperationalConfig* const operationalConfig, SCD40* env_sensor)
        : View(display, navigator), operationalConfig(operationalConfig), env_sensor(env_sensor) {
        this->timer = operationalConfig->standMode.duration;
    };

    void setup() override;
    void render() override;
    void loop() override;
};

#endif  // ELO_STANDVIEW_H
