#include <Arduino.h>

#include "Display.h"
#include "EnvSensor.h"
#include "Button.h"
#include "view_index.h"
#include "debug_print.h"
#include "views/IdleView.h"
#include "views/StandView.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponentState.h"
#include "App.h"

constexpr uint16_t SERIAL_BAUD_RATE = 9600;

namespace Hardware {
    Display display(0x27);
    EnvSensor envSensor;
    Button selectButton(D5);
    Button actionButton(D6);
}  // namespace Hardware

namespace UI {
    namespace Settings {
        constexpr uint16_t VIEW_RENDER_INTERVAL = 1000;
    }

    App APP(Hardware::display, Settings::VIEW_RENDER_INTERVAL);

    namespace StaticComponentStates {
        MeasurementsLineComponentState measurementsLineComponentState(2000, 1000);
    };

    namespace Views {
        IdleView idle({.envSensor = Hardware::envSensor, .selectButton = Hardware::selectButton},
                      APP.getViewNavigator(), STAND_VIEW_INDEX, StaticComponentStates::measurementsLineComponentState);
        StandView stand(
            {
                {
                    .envSensor = Hardware::envSensor,
                    .selectButton = Hardware::selectButton,
                },
                .actionButton = Hardware::actionButton,
            },
            APP.getViewNavigator(), IDLE_VIEW_INDEX, StaticComponentStates::measurementsLineComponentState, 61);

    };  // namespace Views

};  // namespace UI

void initHardware() {
    // init display:
    Hardware::display.init();
    Hardware::display.clear();
    Hardware::display.displayText("Booting elo...", {0, 0});

    // init env sensor:
    Hardware::envSensor.init();

    // init select button:
    Hardware::selectButton.init();
}

void registerAppViews() {
    UI::APP.registerView(IDLE_VIEW_INDEX, &UI::Views::idle);
    UI::APP.registerView(STAND_VIEW_INDEX, &UI::Views::stand);
}

void setup() {
    debug_init(SERIAL_BAUD_RATE);
    debug_println("info: begin setup");

    initHardware();
    registerAppViews();

    debug_println("info: finish setup");
}

void loop() {
    const uint32_t now = millis();
    UI::APP.serve(now);
}