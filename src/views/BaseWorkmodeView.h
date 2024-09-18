//
// Created by jieggii on 9/18/24.
//

#ifndef ELO_SRC_VIEWS_BASEWORKMODEVIEW_H_
#define ELO_SRC_VIEWS_BASEWORKMODEVIEW_H_

#include "BaseView.h"
#include "EnvSensor.h"
#include "Settings.h"
#include "Timer.h"

class BaseWorkmodeView : public BaseView {
   private:
    struct StatusLine : public BaseView::StatusLine {
        Timer timerShowTimer;
        Timer timeHideTimer;
    };

   public:
    void setup() override = 0;
    void loop() override = 0;
    void render() override = 0;
};

#endif  // ELO_SRC_VIEWS_BASEWORKMODEVIEW_H_
