//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "LCD1602.h"
#include "EnvSensor.h"

#include <utility>
#include "iostream"
#include "memory"

#include "ViewController.h"

#include "ViewController.h"

class IdleView : public View {
   private:
    EnvSensor* env_sensor;

   public:
    IdleView(LCD1602* display, ViewNavigator* navigator, EnvSensor* env_sensor)
        : View(display, navigator), env_sensor(env_sensor) {}
    void setup() override;
    void render() override;
    void loop() override;
};

#endif  // ELO_IDLEVIEW_H
