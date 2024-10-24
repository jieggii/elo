//
// Created by jieggii on 10/5/24.
//

#include "IconComponent.h"

void IconComponent::render(Display& display) {
    const auto& state = this->getState();
    if (state.isHidden()) {  // do not render if hidden.
        return;
    }

    display.displayIcon(state.getIconID(), this->coordinates);
}
