//
// Created by jieggii on 10/12/24.
//

#ifndef STATUSLINECOMPONENTSTATE_H
#define STATUSLINECOMPONENTSTATE_H

#include "components/ClockComponent/ClockComponentState.h"
#include "components/ModeIndicatorsComponent/ModeIndicatorsComponent.h"
#include "components/IconComponent/IconComponentState.h"

class StatusLineComponentState final {
   public:
    StatusLineComponentState(const uint8_t modeIndicatorIcon1ID, const uint8_t modeIndicatorIcon2ID,
                             const ClockTime clockTime)
        : modeIndicatorsComponentState(ModeIndicatorsComponentState(modeIndicatorIcon1ID, modeIndicatorIcon2ID)),
          clockComponentState(ClockComponentState(clockTime)),
          measurementsStatusIconComponentState(IconComponentState(0)) {}

    [[nodiscard]] ModeIndicatorsComponentState& getModeIndicatorsComponentState();
    [[nodiscard]] ClockComponentState& getClockComponentState();
    [[nodiscard]] IconComponentState& getMeasurementsStatusIconsComponentState();

    void setDisplayMeasurementsStatusIcon(bool displayMeasurementsStatusIcon);
    [[nodiscard]] bool isDisplayMeasurementsStatusIcon() const;

   private:
    /**
     * Flag indicating whether to display environmental measurements status icon.
     * False by default as measurements are not available instantly; must be set to true when they are available.
     */
    bool displayMeasurementsStatusIcon = false;

    ModeIndicatorsComponentState modeIndicatorsComponentState;
    ClockComponentState clockComponentState;
    IconComponentState measurementsStatusIconComponentState;
};

#endif  // STATUSLINECOMPONENTSTATE_H
