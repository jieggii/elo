#ifndef BASEDISPLAYVIEW_ICONCOMPONENT_H
#define BASEDISPLAYVIEW_ICONCOMPONENT_H

#include "Display.h"

#include "ViewComponent.h"
#include "IconComponentState.h"

/**
 * IconComponent represents a component which renders an icon, which has its position and its icon ID.
 */
class IconComponent final : public ViewComponent<IconComponentState> {
   public:
    IconComponent(const IconComponentState state, const DisplayCoordinates coordinates)
        : ViewComponent(state, coordinates) {}

    /**
     * Render the icon component on the display.
     * @param display The display to render the icon component on.
     */
    void render(Display& display) override;
};

#endif  // BASEDISPLAYVIEW_ICONCOMPONENT_H