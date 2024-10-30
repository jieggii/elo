//
// Created by jieggii on 10/5/24.
//

#include "ModeIndicatorsComponent.h"
#include "ModeIndicatorsComponentState.h"

#include <debug_print.h>

ModeIndicatorsComponent::ModeIndicatorsComponent(ModeIndicatorsComponentState& state,
                                                 const display::Coordinates coordinates)
    : ViewComponent(state, coordinates),
      icon1(IconComponent(this->getState().getIcon1State(), coordinates)),
      icon2(IconComponent(this->getState().getIcon2State(),
                          {static_cast<uint8_t>(coordinates.col + 1), coordinates.row})) {}

void ModeIndicatorsComponent::render(display::Display& display) {
    if (const auto& state = this->getState(); state.isHidden()) {
        this->renderHidden(display);
        return;
    }  // render hidden representation if hidden

    this->icon1.render(display);
    this->icon2.render(display);
}

void ModeIndicatorsComponent::renderHidden(display::Display& display) const {
    // TODO: implement if needed
}