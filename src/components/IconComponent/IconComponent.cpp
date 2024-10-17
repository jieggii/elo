//
// Created by jieggii on 10/5/24.
//

#include "IconComponent.h"

void IconComponent::render(Display& display) {
    const auto& state =
        this->getState();  // TODO: this looks great. Use auto& in similar methods of other components please!

    display.displayIcon(state.getIconID(), this->coordinates);
}
