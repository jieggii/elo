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
    ModeIndicatorsComponent(LCD1602* display, DisplayCoordinates coordinates, const uint8_t icon1ID,
                            const uint8_t icon2ID)
        : ViewComponent(display, coordinates),
          icon1(display, coordinates, icon1ID),
          icon2(display, {coordinates.col + 1, coordinates.row}, icon2ID) {}

    void loop(uint32_t now) override {};
    void render() override {
        this->icon1.render();
        this->icon2.render();
    };
};

#endif  // MODE_INDICATORS_COMPONENT_H