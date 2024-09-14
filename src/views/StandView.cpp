//
// Created by jieggii on 9/4/24.
//

#include "StandView.h"
#include "debug_print.h"
#include "binary.h"
#include "Icon.h"

//#include "ViewIndex.h"

void StandView::setup() const {
    Icon optimal = {
        B00000,
        B00000,
        B01010,
        B01010,
        B00000,
        B10001,
        B01110,
        B00000,
    };

    Icon tableStand = {
        B00000,
        B00000,
        B00000,
        B00000,
        B11111,
        B01010,
        B01010,
        B01010,
    };

    Icon personStand = {
        B01110,
        B01110,
        B00100,
        B00111,
        B00100,
        B00100,
        B00100,
        B00100,
    };

    this->display->cacheIcon(0, optimal);
    this->display->cacheIcon(1, personStand);
    this->display->cacheIcon(2, tableStand);

    this->display->clear();
}

void StandView::loop() const {
    this->display->displayCachedIcon(1, 0, 0);
    this->display->displayCachedIcon(2, 1, 0);

    this->display->displayText("99:99:99", 4, 0);
    this->display->displayCachedIcon(0, 15, 0);

    this->display->displayText("99*C 99% 9999ppm", 0, 1);

    delay(2500);
    this->display->displayText("  *C   %     ppm", 0, 1);
    this->display->displayCachedIcon(0, 1, 1);
    this->display->displayCachedIcon(0, 6, 1);
    this->display->displayCachedIcon(0, 12, 1);

    delay(1000);
//    this->viewNavigator->navigate(IDLE_VIEW_INDEX);
}
