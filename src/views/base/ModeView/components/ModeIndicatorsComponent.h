#ifndef MODE_INDICATORS_COMPONENT_H
#define MODE_INDICATORS_COMPONENT_H

#include "ViewComponent.h"
#include "base/IconComponent.h"

/**
 * ModeIndicatorComponent is a component which encapsulates two IconComponents and represents mode indicator.
 * The first icon is located at the given coordinates, the second icon is located at the next column and the same row.
 */
class ModeIndicatorsComponent final : public ViewComponent {
    IconComponent icon1;  // icon component for the first icon (left)
    IconComponent icon2;  // icon component for the second icon (right)

   public:
    /**
     * Creates a new instance of ModeIndicatorsComponent.
     * @param coordinates Coordinates of the first icon.
     * @param icon1ID ID of the first icon (displayed on the left).
     * @param icon2ID ID of the second icon (displayed on the right).
     */
    ModeIndicatorsComponent(DisplayCoordinates coordinates, uint8_t icon1ID, uint8_t icon2ID);

    /**
     * Renders the component.
     * @param display Display to render on.
     */
    void render(Display* display) override;
};

#endif  // MODE_INDICATORS_COMPONENT_H