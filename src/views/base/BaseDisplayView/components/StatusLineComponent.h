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
    ModeIndicatorsComponent modeIndicators;
    ClockComponent clock;
    IconComponent envMeasurementsStatusIcon;

   public:
    StatusLineComponent(LCD1602* display, DisplayCoordinates coordinates, uint8_t modeIndicatorIcon1ID,
                        uint8_t modeIndicatorIcon2ID, ClockComponent clock)
        : ViewComponent(display, coordinates),
          modeIndicators(display, DisplayCoordinates(0, 0), modeIndicatorIcon1ID, modeIndicatorIcon2ID),
          clock(clock),  // todo: init clock not from provided instance, but from initial time values
          envMeasurementsStatusIcon(display, coordinates, 0) {}

    void setEnvMeasurementsIcon(const uint8_t iconID) { this->envMeasurementsStatusIcon.setIconID(iconID); }

    void loop(uint32_t now) override {};
    void render() override {
        this->modeIndicators.render();
        this->clock.render();
        this->envMeasurementsStatusIcon.render();
    };
};

#endif  // STATUSLINECOMPONENT_H