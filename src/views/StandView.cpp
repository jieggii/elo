//
// Created by jieggii on 10/6/24.
//

#include "icon.h"

#include "StandView.h"

void StandView::setup(const uint32_t now, display::Display& display) {
    cacheModeIndicatorIcons(display, &icon::modeIndicator::stand::indicator1, &icon::modeIndicator::stand::indicator2);

    this->WorkModeView::setup(now, display);
}

void StandView::update(const uint32_t now) { this->WorkModeView::update(now); }

void StandView::render(display::Display& display) { this->WorkModeView::render(display); }

void StandView::reset(const uint32_t now) { this->WorkModeView::reset(now); }
