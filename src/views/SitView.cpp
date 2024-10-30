//
// Created by jieggii on 10/30/24.
//

#include "SitView.h"

#include "icon.h"

#include "SitView.h"

void SitView::setup(const uint32_t now, Display& display) {
    cacheModeIndicatorIcons(display, &icon::modeIndicator::sit::modeIcon1, &icon::modeIndicator::sit::modeIcon2);

    this->WorkModeView::setup(now, display);
}

void SitView::update(const uint32_t now) { this->WorkModeView::update(now); }

void SitView::render(Display& display) { this->WorkModeView::render(display); }

void SitView::reset(const uint32_t now) { this->WorkModeView::reset(now); }
