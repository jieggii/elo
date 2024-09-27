//
// Created by jieggii on 9/20/24.
//

#ifndef BASEELAPSABLEVIEW_H
#define BASEELAPSABLEVIEW_H

#include "Timer.h"
#include "BaseDisplayView.h"

/**
 * BaseExpirableView is a base class for display views that have an expiration time.
 */
class BaseExpirableView : public BaseDisplayView {
    Timer timer;

    bool isPaused = false;
    bool isExpired = false;
    uint8_t nextViewID;

   public:
    BaseExpirableView(LCD1602* display, ViewNavigator* viewNavigator, StatusLineComponent StatusLineComponent,
                      MeasurementsLineComponent measurementsLineComponent) {}

    void setup() override = 0;
    void loop() override = 0;
    void render() override = 0;

    virtual ~BaseExpirableView() = default;
};

#endif  // BASEELAPSABLEVIEW_H
