//
// Created by jieggii on 9/20/24.
//

#ifndef MODEVIEW_H
#define MODEVIEW_H

#include <cstdint>

#include "View.h"
#include "EnvSensor.h"
#include "LCD1602.h"
#include "ViewNavigator.h"
#include "components/MeasurementsLineComponent.h"
#include "components/StatusLineComponent.h"

/**
 * Base class for all mode views.
 * Has status line and measurements line; is capable of switching to another view.
 */
class ModeView : public View {
    uint8_t modeIndicatorIcon1ID;
    uint8_t modeIndicatorIcon2ID;

   protected:
    ViewNavigator* viewNavigator;  // view navigator used to navigate to another view

    StatusLineComponent statusLine;
    MeasurementsLineComponent measurementsLine;

   public:
    ModeView(ViewNavigator* viewNavigator, const uint8_t modeIndicatorIcon1ID, const uint8_t modeIndicatorIcon2ID,
             const ClockTime clockTime)
        : View(),
          modeIndicatorIcon1ID(modeIndicatorIcon1ID),
          modeIndicatorIcon2ID(modeIndicatorIcon2ID),
          viewNavigator(viewNavigator),
          statusLine({0, 0}, modeIndicatorIcon1ID, modeIndicatorIcon2ID, clockTime),
          measurementsLine({0, 1}, 3000, 1000) {}

    [[nodiscard]] uint8_t getModeIndicatorIcon1ID() const { return this->modeIndicatorIcon1ID; }
    [[nodiscard]] uint8_t getModeIndicatorIcon2ID() const { return this->modeIndicatorIcon2ID; }

    // void render_components(LCD1602* display) {
    // this->statusLine.render(display);
    // this->measurementsLine.render(display);
    // };

    void setup(LCD1602* display) override = 0;
    void loop() override = 0;
    void render(LCD1602* display) override = 0;
    void reset() override = 0;

    ~ModeView() override = default;
};

#endif  // MODEVIEW_H
