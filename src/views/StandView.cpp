//
// Created by jieggii on 9/4/24.
//

#include "StandView.h"
#include "debug_print.h"
#include "binary.h"
#include "Icon.h"

#include "core_esp8266_features.h"
#include "ViewIndex.h"

#define ICON_PERSON_STAND_SLOT 0
#define ICON_TABLE_STAND_SLOT 1
#define ICON_ENV_OPTIMAL_SLOT 2


void format_timestamp(uint32_t timestamp, char* buffer) {
    // convert milliseconds to seconds
    uint32_t total_seconds = timestamp / 1000;

    // calculate hours, minutes, and seconds
    uint8_t hours = total_seconds / 3600;
    uint8_t minutes = (total_seconds % 3600) / 60;
    uint8_t seconds = total_seconds % 60;

    // Format the time into the provided buffer in HH:MM:SS format
    buffer[0] = '0' + (hours / 10);
    buffer[1] = '0' + (hours % 10);
    buffer[2] = ':';
    buffer[3] = '0' + (minutes / 10);
    buffer[4] = '0' + (minutes % 10);
    buffer[5] = ':';
    buffer[6] = '0' + (seconds / 10);
    buffer[7] = '0' + (seconds % 10);
    buffer[8] = '\0'; // Null-terminate the string
}

void StandView::setup() {
    debug_println("inf: standView setup start");

    // set all timers:
    uint32_t now = millis();
    this->timers.mainTimer.set(now);
    this->timers.exerciseBreakTimer.set(now);
    this->timers.postureReminderTimer.set(now);

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

    debug_println("inf: standView setup finish");
}

void StandView::render() {
    debug_println("inf: standView render start");
    this->display->displayCachedIcon(ICON_PERSON_STAND_SLOT, 0, 0);
    this->display->displayCachedIcon(ICON_TABLE_STAND_SLOT, 1, 0);
    this->display->displayCachedIcon(ICON_ENV_OPTIMAL_SLOT, 15, 0);

    this->display->displayText("99*C 99% 9999ppm", 0, 1);

    // calculate time left:
    uint32_t now = millis();
    uint32_t time_left = this->timers.mainTimer.left(now);

    char time_left_buf[10];
    format_timestamp(time_left, time_left_buf);

//    this->display->displayText(time_left_buf, 4, 0);

    debug_println(this->hardware.env_sensor->read().temperature);

    debug_println("inf: standView render end");
}

void StandView::loop() {
//    debug_println("loop standView");
    uint32_t now = millis();
    if (this->timers.mainTimer.isExpired(now)) {
        this->viewNavigator->navigate(IDLE_VIEW_INDEX);
    }

//    if (this->timers.exerciseBreakTimer.isExpired(now)) {
//
//    }
//
//    if (this->timers.postureReminderTimer.isExpired(now)) {
//
//    }
}
StandView::StandView(LCD1602 *display, ViewNavigator *navigator, OperationalConfig *const operationalConfig,
                     EnvSensor *env_sensor)
    : View(display, navigator),
      hardware({.env_sensor = env_sensor}),
      timers({.mainTimer = Timer(5 * 1000),
              .exerciseBreakTimer = Timer((uint32_t)operationalConfig->standMode.exerciseBreak.interval * 1000),
              .postureReminderTimer = Timer((uint32_t)operationalConfig->standMode.postureReminder.interval * 1000)}),
      operationalConfig(operationalConfig) {}
