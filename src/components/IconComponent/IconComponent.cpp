//
// Created by jieggii on 10/5/24.
//

#include "IconComponent.h"

void IconComponent::render(display::Display& display) {
    const auto& state = this->getState();
    if (state.isHidden()) {  // render hidden representation if hidden
        this->renderHidden(display);
        return;
    }

    display.displayIcon(state.getIconID(), this->coordinates);
}

void IconComponent::renderHidden(display::Display& display) const {
    display.displayText(nullptr, this->coordinates);  // TODO: this has never been tested
}
