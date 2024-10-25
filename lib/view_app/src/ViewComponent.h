#ifndef ELO_VIEWCOMPONENT_H
#define ELO_VIEWCOMPONENT_H

#include "Display.h"

/**
 * ViewComponent is an interface for view components.
 * TODO: ensure that ViewComponentStateType is a reference to an instance of ViewComponentState
 */

template <typename ViewComponentStateType>
class ViewComponent {
   public:
    ViewComponent(ViewComponentStateType state, const DisplayCoordinates coordinates)
        : coordinates(coordinates), state(state) {}

    /**
     * Returns state of the component.
     */
    [[nodiscard]] ViewComponentStateType getState() const { return this->state; }

    /**
     * Updates state of the component.
     * TODO: is this method needed? Remove.
     */
    virtual void update(const uint32_t now){};

    /**
     * Renders view component on the display.
     * If the component is hidden, renders hidden representation of the component (invisible placeholder).
     * @param display - display to render on.
     * TODO: make method const.
     */
    virtual void render(Display& display) = 0;

    virtual ~ViewComponent() = default;

   protected:
    const DisplayCoordinates coordinates;  // coordinates on the display where component is rendered

    static_assert(std::is_reference_v<ViewComponentStateType>, "ViewComponentStateType must be a reference type");

    /**
     * Renders the hidden representation of a component (invisible placeholder).
     * Is called from render method when the component is hidden.
     */
    virtual void renderHidden(Display& display) const = 0;

   private:
    ViewComponentStateType state;  // state of the component
};

#endif  // ELO_VIEWCOMPONENT_H