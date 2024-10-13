#include <Arduino.h>

#include "Display.h"
#include "EnvSensor.h"
#include "Button.h"
#include "view_index.h"
#include "ViewRegistry.h"
#include "debug_print.h"
#include "ViewRenderer.h"
#include "views/IdleView.h"
#include "views/StandView.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponent.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponentState.h"

constexpr uint16_t VIEW_RENDER_INTERVAL = 1000;

namespace Hardware {
    Display display(0x27);
    EnvSensor envSensor;
    Button selectButton(D5);

}  // namespace Hardware

namespace Config {
    // Settings OPERATIONAL_CONFIG;
    // WiFiSettings WIFI_CONFIG;
}  // namespace Config

namespace UI {
    ViewRegistry viewRegistry;
    ViewNavigator viewNavigator(IDLE_VIEW_INDEX);
    ViewRenderer viewRenderer(VIEW_RENDER_INTERVAL);

    namespace StaticComponentStates {
        MeasurementsLineComponentState measurementsLineComponentState(1000, 1000);
    }  // namespace StaticComponentStates

    namespace Views {
        IdleView idle({.envSensor = &Hardware::envSensor, .selectButton = &Hardware::selectButton}, &viewNavigator,
                      STAND_VIEW_INDEX, &StaticComponentStates::measurementsLineComponentState);
        StandView stand({.envSensor = &Hardware::envSensor, .selectButton = &Hardware::selectButton}, &viewNavigator,
                        IDLE_VIEW_INDEX, &StaticComponentStates::measurementsLineComponentState, 61);
    }  // namespace Views

}  // namespace UI
void setup() {
    debug_init(9600);
    debug_println("info: begin setup");

    // initialize display:
    Hardware::display.init();
    Hardware::display.clear();
    Hardware::display.displayText("Booting elo...", {0, 0});

    // initialize env sensor:
    Hardware::envSensor.init();
    Hardware::selectButton.init();

    // initialize operational configuration:
    // initDefaultOperationalConfig(&Config::OPERATIONAL_CONFIG);

    // register UI views:
    UI::viewRegistry.registerView(IDLE_VIEW_INDEX, &UI::Views::idle);
    UI::viewRegistry.registerView(STAND_VIEW_INDEX, &UI::Views::stand);

    debug_println("info: finish setup");
}

void loop() {
    // debug print free RAM:
    // debug_print("info: free heap: ");
    // debug_print(ESP.getFreeHeap());
    // debug_println(" bytes");
    // Hardware::selectButton.update();

    // get current view:
    const uint8_t currentViewIndex = UI::viewNavigator.getCurrentViewIndex();
    View* currentView = UI::viewRegistry.getView(currentViewIndex);

    // run set up current view if it's been switched recently:
    if (UI::viewNavigator.hasViewIndexChanged()) {
#ifdef DEBUG
        // check whether the current view exist:
        if (currentView == nullptr) {
            debug_print("err: loop: target view with index ");
            debug_print(currentViewIndex);
            debug_println(" was not found");
        }
#endif

        UI::viewNavigator.resetViewIndexChangedFlag();
        currentView->setup(&Hardware::display);
        UI::viewRenderer
            .requestImmediateRender();  // the view will be rendered instantly instead of waiting for render interval
    }

    // run handleInputs() for the current view:
    currentView->handleInputs();
    if (UI::viewNavigator.hasViewIndexChanged()) {  // we do not want to render old view if it has changed
        return;
    }

    // run loop() for the current view (if needed):
    currentView->loop();
    if (UI::viewNavigator.hasViewIndexChanged()) {  // we do not want to render old view if it has changed
        return;
    }

    // (re)render the view (if needed):
    const uint32_t now = millis();
    UI::viewRenderer.renderIfNeeded(&Hardware::display, currentView, now);
}