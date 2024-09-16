//
// Created by jieggii on 9/3/24.
//

#include "IdleView.h"

#include "HardwareSerial.h"
#include "Icon.h"
#include "ViewIndex.h"
#include "binary.h"

void IdleView::setup()  {
    Serial.println("Idle view setup called!");
    this->display->clear();
}

void IdleView::render() {}

void IdleView::loop()  {
    Serial.println("Hello from IdleView loop!");

    //    Icon icon = {
    //        B00000, B01110, B01110, B00100, B00111, B00100, B00100, B00111,
    //    };

    //    display->clear();
    //    display->displayIcon(icon, 0, 0);
    this->display->clear();
    this->display->displayText("idle", 0, 0);
    delay(1);

    this->viewNavigator->navigate(STAND_VIEW_INDEX);
}
