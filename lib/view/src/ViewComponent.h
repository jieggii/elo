#ifndef ELO_VIEWCOMPONENT_H
#define ELO_VIEWCOMPONENT_H

#include <cstdint>
#include "LCD1602.h"

/**
 * ViewComponent is an interface for view components.
 */
class ViewComponent {
   protected:
    LCD1602* display;                // display on which component is rendered
    DisplayCoordinates coordinates;  // coordinates on the display where component is rendered

   public:
    ViewComponent(LCD1602* display, DisplayCoordinates coordinates) : coordinates(coordinates) {}

    virtual void loop(uint32_t now) = 0;
    virtual void render() = 0;

    virtual ~ViewComponent() = default;
};

#endif  // ELO_VIEWCOMPONENT_H