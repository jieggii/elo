//
// Created by jieggii on 10/26/24.
//

#ifndef FLASHNOTIFICATIONCOMPONENT_H
#define FLASHNOTIFICATIONCOMPONENT_H

#include "Display.h"
#include "ViewComponent.h"
#include "FlashNotificationComponentState.h"

class FlashNotificationComponent final : public ViewComponent<FlashNotificationComponentState &> {
   public:
    FlashNotificationComponent(FlashNotificationComponentState &state, const display::Coordinates coordinates)
        : ViewComponent(state, coordinates) {}

    void update(const uint32_t now) override {
        FlashNotificationComponentState &state = this->getState();
        const Timer &timer = state.getTimer();

        // update seconds left:
        // (we add one to the result to round up the division)
        const uint8_t secondsLeft = timer.left(now) / 1000 + 1;
        state.setSecondsLeft(secondsLeft);
    }

    void render(display::Display &display) override {
        const FlashNotificationComponentState &state = this->getState();

        display.displayText(state.getTopRenderBuffer(), {0, 0});
        display.displayText(state.getBottomRenderBuffer(), {0, 1});
    }

   protected:
    void renderHidden(display::Display &display) const override {}
};
#endif  // FLASHNOTIFICATIONCOMPONENT_H
