//
// Created by jieggii on 9/3/24.
//

#include "IdleView.h"

#include "HardwareSerial.h"
#include "Icon.h"
#include "ViewIndex.h"
#include "binary.h"

void IdleView::setup() {
    Serial.println("Idle view setup called!");
    this->display->clear();
}

void IdleView::render() {
    debug_println("render IdleView");
    this->display->displayText("idle", 0, 0);
}

void IdleView::loop() {
//    this->viewNavigator->navigate(STAND_VIEW_INDEX);
}
