#include <Arduino.h>

#include "LCD1602.h"
#include "SCD40.h"
#include "ViewIndex.h"
#include "ViewController.h"
#include "debug_print.h"
#include "ViewRenderer.h"
#include "OperationalConfig.h"
#include "WiFiConfig.h"
#include "views/IdleView.h"
#include "views/StandView.h"
#include "config.h"

#define VIEW_RENDER_INTERVAL 1000

namespace Hardware {
    LCD1602 SCREEN(0x27);
    SCD40 ENV_SENSOR;
}  // namespace Hardware

namespace Config {
    OperationalConfig OPERATIONAL_CONFIG;
    WiFiConfig WIFI_CONFIG;
}  // namespace Config

namespace UI {
    ViewNavigator VIEW_NAVIGATOR(IDLE_VIEW_INDEX);
    ViewController VIEW_CONTROLLER;
    ViewRenderer VIEW_RENDERER(VIEW_RENDER_INTERVAL);

    namespace Views {
        IdleView IDLE(&Hardware::SCREEN, &VIEW_NAVIGATOR, &Hardware::ENV_SENSOR);
        StandView STAND(&Hardware::SCREEN, &VIEW_NAVIGATOR, &Config::OPERATIONAL_CONFIG, &Hardware::ENV_SENSOR);
    }  // namespace Views
}  // namespace UI

void setup() {
    debug_init(9600);
    debug_println("info: begin setup");

    // initialize hardware:
    Hardware::SCREEN.init();
    Hardware::SCREEN.clear();

    // initialize configuration:
    initDefaultOperationalConfig(&Config::OPERATIONAL_CONFIG);

    // register UI views:
    UI::VIEW_CONTROLLER.registerView(IDLE_VIEW_INDEX, &UI::Views::IDLE);
    UI::VIEW_CONTROLLER.registerView(STAND_VIEW_INDEX, &UI::Views::STAND);

    debug_println("info: finish setup");
}

void loop() {
    // debug print free RAM:
    //    debug_print("inf: free heap: ");
    //    debug_print(ESP.getFreeHeap());
    //    debug_println(" bytes");

    // get current view:
    uint8_t currentViewIndex = UI::VIEW_NAVIGATOR.getViewIndex();
    View* currentView = UI::VIEW_CONTROLLER.getView(currentViewIndex);

    // run set up current view if it's been switched recently:
    if (UI::VIEW_NAVIGATOR.getViewIndexChanged()) {
        // check whether the current view exist (debugging):
        if (currentView == nullptr) {
            debug_print("err: loop: target view with index ");
            debug_print(currentViewIndex);
            debug_println(" was not found");

            // todo: display error on the display2
            // ...

            return;
        }

        UI::VIEW_NAVIGATOR.resetViewIndexChanged();
        currentView->setup();
        UI::VIEW_RENDERER
            .setRenderViewInstantly();  // the view will be rendered instantly instead of waiting for render interval
    }

    // (re)render view (if needed):
    uint32_t now = millis();
    UI::VIEW_RENDERER.conditionallyRender(now, currentView);

    // run loop() for the current view:
    currentView->loop();
}