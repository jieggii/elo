#ifndef STATUSLINECOMPONENT_H
#define STATUSLINECOMPONENT_H

#include "Display.h"
#include "ViewComponent.h"

#include "components/IconComponent/IconComponent.h"
#include "components/ClockComponent/ClockComponent.h"
#include "components/ModeIndicatorsComponent/ModeIndicatorsComponent.h"
#include "StatusLineComponentState.h"

/**
 * StatusLineComponent encapsulates mode indicator icons, clock, and overall environmental measurements status icon
 * and represents status line.
 */
class StatusLineComponent final : public ViewComponent<StatusLineComponentState> {
   public:
    /**
     * @param state state.
     * @param coordinates coordinates of the component.
     */
    StatusLineComponent(const StatusLineComponentState state, const DisplayCoordinates coordinates)
        : ViewComponent(state, coordinates),
          modeIndicatorsComponent(
              ModeIndicatorsComponent(this->getState().getModeIndicatorsComponentState(), {0, coordinates.row})),
          clockComponent(ClockComponent(this->getState().getClockComponentState(), {4, coordinates.row})),
          measurementsStatusIconComponent(
              IconComponent(this->getState().getMeasurementsStatusIconsComponentState(), {15, coordinates.row})) {}

    /**
     * Renders the component.
     * @param display to render on.
     */
    void render(Display& display) override;

   private:
    ModeIndicatorsComponent modeIndicatorsComponent;
    ClockComponent clockComponent;
    IconComponent measurementsStatusIconComponent;
};

#endif  // STATUSLINECOMPONENT_H