//
// Created by jieggii on 9/4/24.
//

#ifndef ELO_STANDVIEW_H
#define ELO_STANDVIEW_H

#include "LCD1602.h"
#include "SCD40.h"
#include "ViewController.h"

#include <utility>
#include "memory"

class StandView : public View {
   private:
    SCD40* env_sensor;

   public:
    StandView(LCD1602* display, ViewNavigator* navigator, SCD40* env_sensor)
        : View(display, navigator), env_sensor(env_sensor) {};

    void setup() const override;
//    void loop(BaseContext* ctx) const override;
    void loop() const override;
};

#endif  // ELO_STANDVIEW_H
