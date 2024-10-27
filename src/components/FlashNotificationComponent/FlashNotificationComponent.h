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
    FlashNotificationComponent(FlashNotificationComponentState &state, const DisplayCoordinates coordinates)
        : ViewComponent(state, coordinates) {}

    void render(Display &display) override {
        const auto &state = this->getState();

        // const uint16_t secondsLeft = state.getTimeLeft() / 1000;

        display.displayText(state.getTopRenderBuffer(), {0, 0});
        display.displayText(state.getBottomRenderBuffer(), {0, 1});
    };

   protected:
    void renderHidden(Display &display) const override{};
};
#endif  // FLASHNOTIFICATIONCOMPONENT_H
