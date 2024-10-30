//
// Created by jieggii on 10/6/24.
//

#include "icon.h"

#include "StandView.h"

void StandView::setup(const uint32_t now, Display& display) {
    cacheModeIndicatorIcons(display, &icon::modeIndicator::stand::modeIcon1, &icon::modeIndicator::stand::modeIcon2);

    this->WorkModeView::setup(now, display);
}

void StandView::update(const uint32_t now) { this->WorkModeView::update(now); }

void StandView::render(Display& display) { this->WorkModeView::render(display); }

void StandView::reset(const uint32_t now) { this->WorkModeView::reset(now); }
