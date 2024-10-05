#ifndef MODE_INDICATORS_COMPONENT_H
#define MODE_INDICATORS_COMPONENT_H

#include "ViewComponent.h"
#include "base/IconComponent.h"

/**
 * ModeIndicatorComponent is a component which encapsulates two IconComponents and represents mode indicator.
 * The first icon is located at the given coordinates, the second icon is located at the next column and the same row.
 */
class ModeIndicatorsComponent final : public ViewComponent {
    IconComponent icon1;
    IconComponent icon2;

   public:
    ModeIndicatorsComponent(DisplayCoordinates coordinates, const uint8_t icon1ID, const uint8_t icon2ID)
        : ViewComponent(coordinates),
          icon1(coordinates, icon1ID),
          icon2({static_cast<uint8_t>(coordinates.col + 1), coordinates.row}, icon2ID) {}

    void render(Display* display) override {
        this->icon1.render(display);
        this->icon2.render(display);
    };
};

#endif  // MODE_INDICATORS_COMPONENT_H