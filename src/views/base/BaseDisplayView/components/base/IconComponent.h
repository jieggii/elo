#ifndef BASEDISPLAYVIEW_ICONCOMPONENT_H
#define BASEDISPLAYVIEW_ICONCOMPONENT_H

#include <cstdint>

#include "LCD1602.h"

#include "ViewComponent.h"

/**
 * IconComponent represents an icon component, which has its position and its icon ID.
 */
class IconComponent : public ViewComponent {
    uint8_t iconID;

   public:
    IconComponent(LCD1602* display, DisplayCoordinates coordinates, const uint8_t iconID)
        : ViewComponent(display, coordinates), iconID(iconID) {};

    void setIconID(const uint8_t iconID) { this->iconID = iconID; };

    void loop(uint32_t now) override {};
    void render() override { this->display->displayCachedIcon(this->iconID, this->coordinates); };
};

#endif  // BASEDISPLAYVIEW_ICONCOMPONENT_H