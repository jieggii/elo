//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "LCD1602.h"
#include "SCD40.h"
#include "View.h"

#include <utility>
#include "iostream"
#include "memory"

class IdleView : public View {
   private:
    std::function<void(uint8_t)> switchView;
    std::shared_ptr<SCD40> CD_sensor;  // carbon dioxide sensor
    std::shared_ptr<LCD1602> display;  // display

   public:
    IdleView(std::function<void(uint8_t)> switchView, std::shared_ptr<SCD40> CD_sensor,
             std::shared_ptr<LCD1602> display)
        : switchView(std::move(switchView)), CD_sensor(std::move(CD_sensor)), display(std::move(display)) {}

    void setup() const override;
    void loop() const override;
    //    void cleanup() const override;
};

#endif  // ELO_IDLEVIEW_H
