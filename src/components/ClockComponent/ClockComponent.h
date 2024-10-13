#ifndef BASE_DISPLAY_VIEW_COMPONENTS
#define BASE_DISPLAY_VIEW_COMPONENTS

#include "Display.h"
#include "ViewComponent.h"
#include "ClockComponentState.h"

/**
 * ClockComponent represents a clock which displays hours, minutes and seconds.
 */
class ClockComponent final : public ViewComponent<ClockComponentState> {
   public:
    /**
     * Creates a clock component with the given coordinates and time.
     */
    ClockComponent(const ClockComponentState state, const DisplayCoordinates coordinates)
        : ViewComponent(state, coordinates) {}

    /**
     * Renders the clock on the display.
     */
    void render(Display* display) override;
};

#endif