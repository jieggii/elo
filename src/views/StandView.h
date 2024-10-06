//
// Created by jieggii on 10/5/24.
//

#ifndef STANDVIEW_H
#define STANDVIEW_H

#include "Display.h"
#include "view_index.h"
#include "base/WorkModeView/WorkModeView.h"

// #define STAND_VIEW_INDICATOR_ICON1_ID 1
// #define STAND_VIEW_INDICATOR_ICON2_ID 2
// #define STAND_VIEW_MEASUREMENT_STATUS_OPTIMAL_ICON_ID 3
// #define STAND_VIEW_MEASUREMENT_STATUS_ACCEPTABLE_ICON_ID 4
// #define STAND_VIEW_MEASUREMENT_STATUS_BAD_ICON_ID 5

// class StandView final : public WorkModeView {
//    public:
//     StandView(const Hardware hardware, ViewNavigator* viewNavigator, const uint16_t duration)
//         : WorkModeView(hardware, viewNavigator,
//                        MeasurementStatusIconIDs{
//                            .optimal = STAND_VIEW_MEASUREMENT_STATUS_OPTIMAL_ICON_ID,
//                            .acceptable = STAND_VIEW_MEASUREMENT_STATUS_ACCEPTABLE_ICON_ID,
//                            .bad = STAND_VIEW_MEASUREMENT_STATUS_BAD_ICON_ID,
//                        },
//                        STAND_VIEW_INDICATOR_ICON1_ID, STAND_VIEW_INDICATOR_ICON2_ID, duration, SIT_VIEW_INDEX, 10,
//                        10) {
//     }
//
//     void setup(Display* display) override;
//     void loop() override;
//     void render(Display* display) override;
//     void reset() override;
// };

#endif  // STANDVIEW_H
