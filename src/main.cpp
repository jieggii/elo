#include <Arduino.h>

#include "Display.h"
#include "EnvSensor.h"
#include "Button.h"
#include "Buzzer.h"

#include "sfx.h"
#include "default_settings.h"
#include "view_index.h"
#include "debug_print.h"

#include "views/IdleView.h"
#include "views/StandView.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponentState.h"

#include "App.h"

#include <views/SitView.h>

constexpr uint16_t serialBaudRate = 9600;

namespace Hardware {
    Display display(0x27);
    EnvSensor envSensor;
    Button selectButton(D5);
    Button actionButton(D6);
    Buzzer buzzer(D7);
}  // namespace Hardware

namespace UI {
    constexpr uint16_t viewRenderInterval = 17;      // 58.823529 fps
    App APP(Hardware::display, viewRenderInterval);  // app instance

    namespace StaticComponentStates {
        constexpr uint16_t measurementsLineComponentStateDisplayMeasurementsDuration = 7000;
        constexpr uint16_t measurementsLineComponentsStateDisplayStatusesDuration = 1750;
        MeasurementsLineComponentState measurementsLineComponentState(
            measurementsLineComponentStateDisplayMeasurementsDuration,
            measurementsLineComponentsStateDisplayStatusesDuration);
    }  // namespace StaticComponentStates

    namespace Views {
        IdleView idle({.envSensor = Hardware::envSensor,
                       .selectButton = Hardware::selectButton,
                       .buzzer = Hardware::buzzer},
                      APP.getViewNavigator(), STAND_VIEW_INDEX, StaticComponentStates::measurementsLineComponentState,
                      defaultSettings.environment);

        StandView stand({{
                             .envSensor = Hardware::envSensor,
                             .selectButton = Hardware::selectButton,
                             .buzzer = Hardware::buzzer,
                         },
                         {
                             .actionButton = Hardware::actionButton,
                         }},
                        APP.getViewNavigator(), SIT_VIEW_INDEX, StaticComponentStates::measurementsLineComponentState,
                        defaultSettings.environment, defaultSettings.standWorkMode);

        SitView sit({{
                         .envSensor = Hardware::envSensor,
                         .selectButton = Hardware::selectButton,
                         .buzzer = Hardware::buzzer,
                     },
                     {
                         .actionButton = Hardware::actionButton,
                     }},
                    APP.getViewNavigator(), IDLE_VIEW_INDEX, StaticComponentStates::measurementsLineComponentState,
                    defaultSettings.environment, defaultSettings.sitWorkMode);

    }  // namespace Views
}  // namespace UI

/**
 * Initializes hardware components.
 */
void initHardware() {
    // init display:
    Hardware::display.init();
    Hardware::display.displayText("Booting elo...", {0, 0});

    // init env sensor:
    Hardware::envSensor.init();

    // init buttons:
    Hardware::selectButton.init();
    Hardware::actionButton.init();

    // init buzzer:
    // TODO: move magic numbers frequencies to constants; move melody to a separate file
    Hardware::buzzer.init();
    Hardware::buzzer.scheduleMelody(SFX::boot, std::size(SFX::boot));
}

/**
 * Registers all views in the app.
 */
void registerAppViews() {
    UI::APP.registerView(IDLE_VIEW_INDEX, &UI::Views::idle);
    UI::APP.registerView(STAND_VIEW_INDEX, &UI::Views::stand);
    UI::APP.registerView(SIT_VIEW_INDEX, &UI::Views::sit);
}

void setup() {
    debug_init(serialBaudRate);
    debug_println("info: begin setup");

    initHardware();
    registerAppViews();

    debug_println("info: finish setup");
}

void loop() {
    const uint32_t now = millis();
    UI::APP.serve(now);
}