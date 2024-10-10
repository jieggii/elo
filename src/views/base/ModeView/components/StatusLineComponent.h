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
     * @param coordinates coordinates of the component
     * @param modeIndicatorIcon1ID id of the first mode indicator icon
     * @param modeIndicatorIcon2ID id of the second mode indicator icon
     * @param defaultMeasurementStatusIconID id of the default environmental measurements status icon
     */
    StatusLineComponent(const DisplayCoordinates coordinates, const uint8_t modeIndicatorIcon1ID,
                        const uint8_t modeIndicatorIcon2ID, const uint8_t defaultMeasurementStatusIconID)
        : ViewComponent(coordinates),
          modeIndicators({0, 0}, modeIndicatorIcon1ID, modeIndicatorIcon2ID),
          clock(ClockComponent({4, coordinates.row})),
          envMeasurementsStatusIcon({15, coordinates.row}, defaultMeasurementStatusIconID) {}

    /**
     * Sets environmental measurements status icon.
     * @param iconID icon ID.
     */
    void setEnvMeasurementsStatusIconID(uint8_t iconID);

    /**
     * Sets clock time.
     * @param clockTime clock time.
     */
    void setClockTime(ClockTime clockTime);

    /**
     * Enables environmental measurements status icon.
     */
    void enableMeasurementsStatusIcon();

    /**
     * Disables environmental measurements status icon.
     */
    void disableMeasurementsStatusIcon();

    /**
     * Renders the component.
     * @param display to render on.
     */
    void render(Display* display) override;

   private:
    ModeIndicatorsComponent modeIndicators;   // Mode indicators (displayed on the left side of the status line)
    ClockComponent clock;                     // Clock (displayed in the middle of the status line)
    IconComponent envMeasurementsStatusIcon;  // Environmental measurements status icon (displayed on the right side of
                                              // the status line)

    /**
     * Flag indicating whether to display environmental measurements status icon.
     */
    bool displayMeasurementsStatusIcon = false;
};

#endif  // STATUSLINECOMPONENT_H