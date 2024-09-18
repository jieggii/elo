//
// Created by jieggii on 9/18/24.
//

#ifndef ELO_SRC_VIEWS_BASEVIEW_H_
#define ELO_SRC_VIEWS_BASEVIEW_H_

#include "View.h"
#include "Icon.h"
#include "Timer.h"
#include "EnvSensor.h"
#include "cstdint"

class BaseView : View {
   protected:
    struct Hardware {
        EnvSensor* env_sensor;
    } hardware;

    struct StatusLine {
        Icon favicon;
    } statusLine;

    struct MeasurementsLine {
        bool isDisplayingStatuses = false;
        Timer displayMeasurementsTimer = Timer(3500); // todo: make magic numbers const
        Timer displayStatusesTimer = Timer(750); // todo: make magic numbers const
    } measurementsLine;

    uint8_t nextViewIndex;

   public:
    void setup() override = 0;
    void loop() override = 0;
    void render() override = 0;
};

#endif  // ELO_SRC_VIEWS_BASEVIEW_H_
