#ifndef BASEDISPLAYVIEW_ICONCOMPONENT_H
#define BASEDISPLAYVIEW_ICONCOMPONENT_H

#include <cstdint>

#include "debug_print.h"
#include "Display.h"

#include "ViewComponent.h"

/**
 * IconComponent represents an icon component, which has its position and its icon ID.
 */
class IconComponent final : public ViewComponent {
    uint8_t iconID;

   public:
    IconComponent(const DisplayCoordinates coordinates, const uint8_t iconID)
        : ViewComponent(coordinates), iconID(iconID){};

    void setIconID(const uint8_t iconID) { this->iconID = iconID; };

    void render(Display* display) override { display->displayIcon(this->iconID, this->coordinates); };
};

#endif  // BASEDISPLAYVIEW_ICONCOMPONENT_H