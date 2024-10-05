//
// Created by jieggii on 10/5/24.
//

#include "IconComponent.h"

void IconComponent::setIconID(const uint8_t iconID) { this->iconID = iconID; }

void IconComponent::render(Display* display) { display->displayIcon(this->iconID, this->coordinates); }
