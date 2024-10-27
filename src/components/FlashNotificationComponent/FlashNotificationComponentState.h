//
// Created by jieggii on 10/26/24.
//

#ifndef FLASHNOTIFICATIONCOMPONENTSTATE_H
#define FLASHNOTIFICATIONCOMPONENTSTATE_H

#include <cstdint>

#include "ViewComponentState.h"

class FlashNotificationComponentState final : public ViewComponentState {
   public:
    void setText(const char* text) {
        this->topRenderBuffer = "Notification....";
        this->bottomRenderBuffer = "text........ (3)";
    }
    const char* getTopRenderBuffer() const { return this->topRenderBuffer; }
    const char* getBottomRenderBuffer() const { return this->bottomRenderBuffer; }

    void setTimeLeft(const uint32_t timeLeft) { this->timeLeft = timeLeft; }
    uint32_t getTimeLeft() const { return timeLeft; }

   private:
    const char* topRenderBuffer = nullptr;
    const char* bottomRenderBuffer = nullptr;

    uint32_t timeLeft = 0;
};

#endif  // FLASHNOTIFICATIONCOMPONENTSTATE_H
