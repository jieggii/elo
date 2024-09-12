//
// Created by jieggii on 9/4/24.
//

#include "StandView.h"

#include "SoftwareSerial.h"
#include "ViewIndex.h"

void StandView::setup() const { this->display->clear(); }

void StandView::loop() const {
    Serial.println("Hi from stand view");
    this->display->displayText("standing!", 0, 0);

    delay(1500);

    this->viewNavigator->navigate(IDLE_VIEW_INDEX);
}
