//
// Created by jieggii on 9/4/24.
//

#ifndef ELO_STANDVIEW_H
#define ELO_STANDVIEW_H

#include "LCD1602.h"
#include "SCD40.h"
#include "View.h"
#include "memory"

class StandView : public View {
   private:
    std::function<void(uint8_t)> switchView;
    std::shared_ptr<SCD40> CD_sensor;  // carbon dioxide sensor
    std::shared_ptr<LCD1602> display;  // display

   public:
    StandView(std::function<void(uint8_t)> switchView, std::shared_ptr<SCD40> CD_sensor,
              std::shared_ptr<LCD1602> display)
        : switchView(switchView), CD_sensor(CD_sensor), display(display) {}

    void setup() const override;
    void loop() const override;
};

#endif  // ELO_STANDVIEW_H
