//
// Created by jieggii on 10/5/24.
//

#include "ModeIndicatorsComponent.h"
#include "ModeIndicatorsComponentState.h"

ModeIndicatorsComponent::ModeIndicatorsComponent(const ModeIndicatorsComponentState state,
                                                 const DisplayCoordinates coordinates)
    : ViewComponent(state, coordinates),
      icon1(IconComponent(this->getState().getIcon1State(), coordinates)),
      icon2(IconComponent(this->getState().getIcon2State(),
                          {static_cast<uint8_t>(coordinates.col + 1), coordinates.row})) {}

void ModeIndicatorsComponent::render(Display& display) {
    this->icon1.render(display);
    this->icon2.render(display);
}