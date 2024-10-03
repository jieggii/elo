#ifndef STATUSLINECOMPONENT_H
#define STATUSLINECOMPONENT_H

#include <cstdint>
#include "LCD1602.h"
#include "ViewComponent.h"

#include "base/ClockComponent.h"
#include "base/IconComponent.h"

#include "ModeIndicatorsComponent.h"

/**
 * StatusLineComponent encapsulates mode indicator icons, clock, and overall environmental measurements status icon
 * and represents status line.
 */
class StatusLineComponent final : public ViewComponent {
   public:
    StatusLineComponent(const DisplayCoordinates coordinates, const uint8_t modeIndicatorIcon1ID,
                        const uint8_t modeIndicatorIcon2ID, const ClockTime clockTime,
                        const uint8_t defaultMeasurementStatusIconID)
        : ViewComponent(coordinates),
          modeIndicators({0, 0}, modeIndicatorIcon1ID, modeIndicatorIcon2ID),
          clock(ClockComponent({4, coordinates.row}, clockTime)),
          envMeasurementsStatusIcon({15, coordinates.row}, defaultMeasurementStatusIconID) {}

    void setEnvMeasurementsStatusIconID(const uint8_t iconID) { this->envMeasurementsStatusIcon.setIconID(iconID); }

    void render(LCD1602* display) override {
        this->modeIndicators.render(display);
        this->clock.render(display);
        this->envMeasurementsStatusIcon.render(display);
    };

   private:
    ModeIndicatorsComponent modeIndicators;
    ClockComponent clock;
    IconComponent envMeasurementsStatusIcon;
};

#endif  // STATUSLINECOMPONENT_H