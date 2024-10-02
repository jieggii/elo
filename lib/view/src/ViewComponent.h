#ifndef ELO_VIEWCOMPONENT_H
#define ELO_VIEWCOMPONENT_H

#include "LCD1602.h"

/**
 * ViewComponent is an interface for view components.
 */
class ViewComponent {
   protected:
    DisplayCoordinates coordinates;  // coordinates on the display where component is rendered

   public:
    explicit ViewComponent(const DisplayCoordinates coordinates) : coordinates(coordinates) {}

    /**
     * Renders view component on the display.
     * @param display - display to render on.
     */
    virtual void render(LCD1602* display) = 0;

    virtual ~ViewComponent() = default;
};

#endif  // ELO_VIEWCOMPONENT_H