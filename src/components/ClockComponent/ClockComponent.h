#ifndef BASE_DISPLAY_VIEW_COMPONENTS
#define BASE_DISPLAY_VIEW_COMPONENTS

#include "Display.h"
#include "ViewComponent.h"
#include "ClockComponentState.h"

/**
 * ClockComponent represents a clock which displays hours, minutes and seconds.
 * TODO: store render buffer inside of the component, do not create a new instance every render() call.
 */
class ClockComponent final : public ViewComponent<ClockComponentState&> {
   public:
    /**
     * Creates a clock component with the given coordinates and time.
     */
    ClockComponent(ClockComponentState& state, const display::Coordinates coordinates)
        : ViewComponent(state, coordinates) {}

    /**
     * Renders the clock on the display.
     */
    void render(display::Display& display) override;

   private:
    /**
     * Renders the hidden copy of the clock on the display.
     */
    void renderHidden(display::Display& display) const override;
};

#endif