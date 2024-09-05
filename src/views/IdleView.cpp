//
// Created by jieggii on 9/3/24.
//

#include "IdleView.h"

#include "HardwareSerial.h"
#include "Icon.h"
#include "ViewIndex.h"
#include "binary.h"

void IdleView::setup() const {
    Serial.println("Idle view setup called!");
    this->display->clear();
}

void IdleView::loop() const {
    Serial.println("Hello from IdleView loop!");

    Icon icon = {
        B00000, B01110, B01110, B00100, B00111, B00100, B00100, B00111,
    };

    display->clear();
    display->displayIcon(icon, 0, 0);

    display->displayText("idle", 1, 0);
    delay(3000);

    this->switchView(STAND_VIEW_INDEX);
}

// void IdleView::cleanup() const {
//
// }
