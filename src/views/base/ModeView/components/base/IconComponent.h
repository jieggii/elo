#ifndef BASEDISPLAYVIEW_ICONCOMPONENT_H
#define BASEDISPLAYVIEW_ICONCOMPONENT_H

#include <cstdint>

#include "Display.h"

#include "ViewComponent.h"

/**
 * IconComponent represents a component which renders an icon, which has its position and its icon ID.
 */
class IconComponent final : public ViewComponent {
   public:
    IconComponent(const DisplayCoordinates coordinates, const uint8_t iconID)
        : ViewComponent(coordinates), iconID(iconID) {}

    /**
     * Set the icon ID of the icon component.
     * @param iconID The icon ID to set.
     */
    void setIconID(uint8_t iconID);

    /**
     * Render the icon component on the display.
     * @param display The display to render the icon component on.
     */
    void render(Display* display) override;

   private:
    uint8_t iconID;  // The icon ID of the icon component.
};

#endif  // BASEDISPLAYVIEW_ICONCOMPONENT_H