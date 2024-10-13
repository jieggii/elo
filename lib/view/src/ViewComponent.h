#ifndef ELO_VIEWCOMPONENT_H
#define ELO_VIEWCOMPONENT_H

#include "Display.h"

/**
 * ViewComponent is an interface for view components.
 */

template <typename ViewComponentStateType>
class ViewComponent {
   protected:
    const DisplayCoordinates coordinates;  // coordinates on the display where component is rendered

   public:
    ViewComponent(ViewComponentStateType state, const DisplayCoordinates coordinates)
        : coordinates(coordinates), state(state) {}

    /**
     * Returns state of the component.
     */
    [[nodiscard]] ViewComponentStateType getState() const { return this->state; }

    /**
     * Renders view component on the display.
     * @param display - display to render on.
     */
    virtual void render(Display* display) = 0;

    virtual ~ViewComponent() = default;

   private:
    ViewComponentStateType state;  // state of the component
};

#endif  // ELO_VIEWCOMPONENT_H