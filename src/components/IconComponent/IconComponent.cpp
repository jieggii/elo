//
// Created by jieggii on 10/5/24.
//

#include "IconComponent.h"

void IconComponent::render(Display* display) {
    const auto iconID = this->getState().getIconID();
    display->displayIcon(iconID, this->coordinates);
}
