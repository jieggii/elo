#ifndef ELO_VIEWCOMPONENT_H
#define ELO_VIEWCOMPONENT_H

#include "Display.h"

/**
 * ViewComponent is an interface for view components.
 */
class ViewComponent {
   protected:
    DisplayCoordinates coordinates;  // coordinates on the display where component is rendered

   public:
    explicit ViewComponent(const DisplayCoordinates coordinates) : coordinates(coordinates) {}

    /**
     * Sets up view component.
     * @param display - display to set up on.
     */
    // virtual void setup(Display* display) = 0;

    /**
     * Checks if view component needs to be rendered.
     * The first render is always needed, even if this method returns false. ??? should this statement be true? or
     * should needsRerender be renamed to needsRender and checked even before the first render?
     * @return true if it needs to be rerender.
     */
    // virtual bool needsRerender() = 0;
    /**
     * Renders view component on the display.
     * @param display - display to render on.
     */
    virtual void render(Display* display) = 0;

    virtual ~ViewComponent() = default;
};

#endif  // ELO_VIEWCOMPONENT_H