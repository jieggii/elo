//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_IDLEVIEW_H
#define ELO_IDLEVIEW_H

#include "Display.h"
#include "Icon.h"

#include "base/ModeView/ModeView.h"
#include "base/ModeView/components/base/ClockComponent.h"

#define IDLE_VIEW_INDICATOR_ICON1_ID 1
#define IDLE_VIEW_INDICATOR_ICON2_ID 2
#define IDLE_VIEW_MEASUREMENT_STATUS_OPTIMAL_ICON_ID 3
#define IDLE_VIEW_MEASUREMENT_STATUS_ACCEPTABLE_ICON_ID 4
#define IDLE_VIEW_MEASUREMENT_STATUS_BAD_ICON_ID 5

class IdleView final : public ModeView {
   public:
    explicit IdleView(const Hardware hardware, ViewNavigator* viewNavigator)
        : ModeView(hardware, viewNavigator,
                   MeasurementStatusIconIDs{.optimal = IDLE_VIEW_MEASUREMENT_STATUS_OPTIMAL_ICON_ID,
                                            .acceptable = IDLE_VIEW_MEASUREMENT_STATUS_ACCEPTABLE_ICON_ID,
                                            .bad = IDLE_VIEW_MEASUREMENT_STATUS_BAD_ICON_ID},
                   IDLE_VIEW_INDICATOR_ICON1_ID, IDLE_VIEW_INDICATOR_ICON2_ID, ClockTime(65)) {}

    void setup(Display* display) override {
        const Icon modeIcon1 = {
            // empty icon
            B00000, B00000, B00000, B00000, B00000, B00000, B00000, B00000,
        };

        const Icon modeIcon2 = {
            // table
            B00000, B00000, B00000, B00000, B11111, B01010, B01010, B01010,
        };

        display->cacheIcon(IDLE_VIEW_INDICATOR_ICON1_ID, modeIcon1);
        display->cacheIcon(IDLE_VIEW_INDICATOR_ICON2_ID, modeIcon2);

        const Icon statusOptimalIcon = {
            // icon representing face :)
            B00000, B01010, B01010, B00000, B10001, B01110, B00000, B00000,
        };

        const Icon statusAcceptableIcon = {
            // icon representing face :|
            B00000, B01010, B01010, B00000, B00000, B11111, B00000, B00000,
        };

        const Icon statusBadIcon = {
            // icon representing face :(
            B00000, B01010, B01010, B00000, B00000, B01110, B10001, B00000,
        };

        display->cacheIcon(IDLE_VIEW_MEASUREMENT_STATUS_OPTIMAL_ICON_ID, statusOptimalIcon);
        display->cacheIcon(IDLE_VIEW_MEASUREMENT_STATUS_ACCEPTABLE_ICON_ID, statusAcceptableIcon);
        display->cacheIcon(IDLE_VIEW_MEASUREMENT_STATUS_BAD_ICON_ID, statusBadIcon);

        this->setStatusLineClockTime(ClockTime(65));
    }

    void loop() override { ModeView::loop(); }
    void render(Display* display) override { ModeView::render(display); };
    void reset() override{};

    ~IdleView() override = default;
};

#endif  // ELO_IDLEVIEW_H
