#ifndef STATUSLINECOMPONENT_H
#define STATUSLINECOMPONENT_H

#include <cstdint>
#include "Display.h"
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
    /**
     * @param coordinates - coordinates of the component
     * @param modeIndicatorIcon1ID - id of the first mode indicator icon
     * @param modeIndicatorIcon2ID - id of the second mode indicator icon
     * @param defaultMeasurementStatusIconID - id of the default environmental measurements status icon
     */
    StatusLineComponent(const DisplayCoordinates coordinates, const uint8_t modeIndicatorIcon1ID,
                        const uint8_t modeIndicatorIcon2ID, const uint8_t defaultMeasurementStatusIconID)
        : ViewComponent(coordinates),
          modeIndicators({0, 0}, modeIndicatorIcon1ID, modeIndicatorIcon2ID),
          clock(ClockComponent({4, coordinates.row})),
          envMeasurementsStatusIcon({15, coordinates.row}, defaultMeasurementStatusIconID) {}

    void setEnvMeasurementsStatusIconID(const uint8_t iconID) { this->envMeasurementsStatusIcon.setIconID(iconID); }

    void setClockTime(const ClockTime clockTime) { this->clock.setTime(clockTime); }

    void render(Display* display) override {
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