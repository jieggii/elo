//
// Created by jieggii on 10/5/24.
//

#include "ModeIndicatorsComponent.h"

ModeIndicatorsComponent::ModeIndicatorsComponent(DisplayCoordinates coordinates, const uint8_t icon1ID,
                                                 const uint8_t icon2ID)
    : ViewComponent(coordinates),
      icon1(coordinates, icon1ID),
      icon2({static_cast<uint8_t>(coordinates.col + 1), coordinates.row}, icon2ID) {}

void ModeIndicatorsComponent::render(Display* display) {
    this->icon1.render(display);
    this->icon2.render(display);
}