//
// Created by jieggii on 10/6/24.
//

#include "Timer.h"

Timer Timer::fromSeconds(const uint16_t duration) { return Timer(static_cast<uint32_t>(duration * 1000)); }

[[nodiscard]] bool Timer::isPaused() const { return this->paused; }

void Timer::set(const uint32_t now) {
    this->paused = false;
    this->startTimestamp = now;
}

void Timer::pause(const uint32_t now) {
    this->paused = true;
    this->pauseTimestamp = now;
}

void Timer::resume(const uint32_t now) {
    this->paused = false;

    // move startTimestamp
    this->startTimestamp = now - (this->pauseTimestamp - this->startTimestamp);
}

[[nodiscard]] uint32_t Timer::elapsed(uint32_t now) const {
    if (this->paused) {
        // if paused, use pauseTimestamp as now
        now = this->pauseTimestamp;
    }

    uint32_t elapsed = now - this->startTimestamp;
    if (elapsed >= this->duration) {
        return this->duration;
    }

    return elapsed;
}

[[nodiscard]] uint32_t Timer::left(const uint32_t now) const { return this->duration - this->elapsed(now); }

bool Timer::isExpired(const uint32_t now) const {
    if (this->elapsed(now) == this->duration) {
        return true;
    }
    return false;
}
