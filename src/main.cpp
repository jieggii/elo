#include <Arduino.h>

#include "LCD1602.h"
#include "SCD40.h"

#include "ViewIndex.h"

#include "debug_print.h"
#include "ViewRouter.h"

#include "views/IdleView.h"
#include "views/StandView.h"

namespace Hardware {
    std::shared_ptr<LCD1602> screen = std::make_shared<LCD1602>(0x27);
    std::shared_ptr<SCD40> cd_sensor = std::make_shared<SCD40>(); // environmental sensor sensor
}

ViewRouter VIEW_ROUTER;

void init_views() {
    VIEW_ROUTER.registerView(IDLE_VIEW_INDEX, []() {
        return std::make_shared<IdleView>([&](uint8_t index) { VIEW_ROUTER.switchView(index); }, Hardware::cd_sensor,Hardware::screen);
    });
    VIEW_ROUTER.registerView(STAND_VIEW_INDEX, []() {
        return std::make_shared<StandView>([&](uint8_t index) { VIEW_ROUTER.switchView(index); }, Hardware::cd_sensor, Hardware::screen);
    });
}

// Globals:
void setup() {
#ifdef DEBUG
    Serial.begin(9600);
#endif
    debug_println("begin setup");

    // Init screen:
    Hardware::screen->init();
    Hardware::screen->clear();

    // Create and register views:
    init_views();

    // Set and initialize current view:
    VIEW_ROUTER.switchView(IDLE_VIEW_INDEX);
    VIEW_ROUTER.getCurrentView()->setup();

    debug_println("finish setup");
}

void loop() {
#ifdef DEBUG
    unsigned long freeRAM = ESP.getFreeHeap();
    Serial.print("dbg: free RAM: ");
    Serial.print(freeRAM);
    Serial.println(" bytes");
#endif

    VIEW_ROUTER.getCurrentView()->loop();
}