//
// Created by jieggii on 9/4/24.
//

#include "StandView.h"
#include "debug_print.h"
#include "binary.h"
#include "Icon.h"

// #include "ViewIndex.h"
#include "core_esp8266_features.h"
#include "cstdlib"


#define ICON_PERSON_STAND_SLOT 0
#define ICON_TABLE_STAND_SLOT 1
#define ICON_ENV_OPTIMAL_SLOT 2

void StandView::setup()  {
    Icon envOptimalIcon = {
        B00000, B00000, B01010, B01010, B00000, B10001, B01110, B00000,
    };

    Icon tableStandIcon = {
        B00000, B00000, B00000, B00000, B11111, B01010, B01010, B01010,
    };

    Icon personStandIcon = {
        B01110, B01110, B00100, B00111, B00100, B00100, B00100, B00100,
    };

    this->display->cacheIcon(ICON_PERSON_STAND_SLOT, personStandIcon);
    this->display->cacheIcon(ICON_TABLE_STAND_SLOT, tableStandIcon);
    this->display->cacheIcon(ICON_ENV_OPTIMAL_SLOT, envOptimalIcon);

    this->display->clear();

    debug_println("finish stand setup");
}

void StandView::render() {
    some_var++;
    this->display->displayCachedIcon(ICON_PERSON_STAND_SLOT, 0, 0);
    this->display->displayCachedIcon(ICON_TABLE_STAND_SLOT, 1, 0);

    this->display->displayText("99:99:99", 4, 0);
    this->display->displayCachedIcon(ICON_ENV_OPTIMAL_SLOT, 15, 0);

    char some_var_buffer[3+1];
    itoa(this->some_var, some_var_buffer, 10);
    const char* cstr = some_var_buffer;
    this->display->displayText(cstr, 12, 0);

    this->display->displayText("99.9*C 99% 9999p", 0, 1);

    debug_println("update screen");
}

void StandView::loop() {
//    debug_println("loop called");
}
