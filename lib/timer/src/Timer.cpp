//
// Created by jieggii on 10/6/24.
//

#include "Timer.h"

Timer Timer::fromSeconds(const uint16_t duration) { return Timer(static_cast<uint32_t>(duration * 1000)); }

void Timer::set(const uint32_t now) { this->startTS = now; }

uint32_t Timer::elapsed(const uint32_t now) const { return now - this->startTS; }

[[nodiscard]] uint32_t Timer::left(const uint32_t now) const {
    const uint32_t elapsed = this->elapsed(now);
    if (elapsed >= duration) {
        return 0;
    }
    return this->duration - elapsed;
}

bool Timer::isExpired(const uint32_t now) const {
    if (this->left(now) == 0) {
        return true;
    }
    return false;
}
