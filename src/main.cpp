#include <Arduino.h>

#include "LCD1602.h"
#include "SCD40.h"
#include "ViewIndex.h"
#include "ViewController.h"
#include "debug_print.h"
#include "views/IdleView.h"
#include "views/StandView.h"

namespace Hardware {
    LCD1602 SCREEN(0x27);
    SCD40 ENV_SENSOR;
}

namespace UI {
    ViewNavigator VIEW_NAVIGATOR;
    ViewController VIEW_CONTROLLER;

    namespace Views {
        IdleView IDLE(&Hardware::SCREEN, &VIEW_NAVIGATOR, &Hardware::ENV_SENSOR);
        StandView STAND(&Hardware::SCREEN, &VIEW_NAVIGATOR, &Hardware::ENV_SENSOR);
    }
}

void setup() {
    debug_init(9600);
    debug_println("info: begin setup");

    Hardware::SCREEN.init();
    Hardware::SCREEN.clear();

    UI::VIEW_CONTROLLER.registerView(IDLE_VIEW_INDEX, &UI::Views::IDLE);
    UI::VIEW_CONTROLLER.registerView(STAND_VIEW_INDEX, &UI::Views::STAND);

    UI::VIEW_NAVIGATOR.navigate(IDLE_VIEW_INDEX);

    debug_println("info: finish setup");
}

void loop() {
    // debug print free RAM:
    debug_print("inf: free heap: ");
    debug_print(ESP.getFreeHeap());
    debug_println(" bytes");

    // get current view:
    uint8_t currentViewIndex = UI::VIEW_NAVIGATOR.getCurrentViewIndex();
    View* currentView = UI::VIEW_CONTROLLER.getView(currentViewIndex);
    if (currentView == nullptr) {
        debug_print("err: loop: target view with index ");
        debug_print(currentViewIndex);
        debug_println(" was not found");

        // todo: display error
        // ...

        return;
    }

    // run loop() for the current view:
    currentView->loop();
}