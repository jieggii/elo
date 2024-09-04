//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "iostream"
#include "memory"

#include "SCD40.h"
#include "LCD1602.h"

#include "View.h"


class IdleView : public View {
private:
    std::function<void(uint8_t)> switchView;
    std::shared_ptr<SCD40> CD_sensor; // carbon dioxide sensor
    std::shared_ptr<LCD1602> display; // display

public:
    IdleView(std::function<void(uint8_t)> switchView, std::shared_ptr<SCD40> CD_sensor, std::shared_ptr<LCD1602> display)
    : switchView(switchView), CD_sensor(CD_sensor), display(display) {}

    void setup() const override;
    void loop() const override;
//    void cleanup() const override;
};

#endif //ELO_IDLEVIEW_H
