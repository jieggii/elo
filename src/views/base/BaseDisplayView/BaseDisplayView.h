//
// Created by jieggii on 9/20/24.
//

#ifndef BASEDISPLAYVIEW_H
#define BASEDISPLAYVIEW_H

#include <cstdint>

#include "View.h"
#include "ViewComponent.h"
#include "Timer.h"
#include "EnvSensor.h"
#include "LCD1602.h"

class BaseDisplayView : public View {
    StatusLineComponent statusLine;
    MeasurementsLineComponent measurementsLine;

   public:
    BaseDisplayView(LCD1602* display, ViewNavigator* viewNavigator, ModeIndicatorComponent modeIndicator,
                    ClockComponent clock, IconComponent envMeasurementsStatusIcon,
                    MeasurementsLineComponent measurementsLineComponent)
        : View(display, viewNavigator),
          statusLine({0, 0}, modeIndicator, clock, envMeasurementsStatusIcon),
          measurementsLine(measurementsLineComponent) {}

    void setup() override = 0;
    void loop() override = 0;
    void render() override = 0;

    virtual ~BaseDisplayView() = default;
};

#endif  // BASEDISPLAYVIEW_H
