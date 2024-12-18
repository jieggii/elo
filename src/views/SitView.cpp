//
// Created by jieggii on 10/30/24.
//

#include "SitView.h"

#include "icon.h"

#include "SitView.h"

void SitView::setup(const uint32_t now, display::Display& display) {
    cacheModeIndicatorIcons(display, &icon::modeIndicator::sit::indicator1, &icon::modeIndicator::sit::indicator2);

    this->WorkModeView::setup(now, display);
}

void SitView::update(const uint32_t now) { this->WorkModeView::update(now); }

void SitView::render(display::Display& display) { this->WorkModeView::render(display); }

void SitView::reset(const uint32_t now) { this->WorkModeView::reset(now); }
