//
// Created by jieggii on 9/16/24.
//

#ifndef ELO_LIB_TIMER_SRC_TIMER_H_
#define ELO_LIB_TIMER_SRC_TIMER_H_

#include "cstdint"

#include "debug_print.h"

class Timer {
    uint32_t duration;     // timer duration in ms
    uint32_t startTS = 0;  // timestamp of the timer set

   public:
    explicit Timer(const uint32_t duration) : duration(duration) {}

    /**
     * Returns number of milliseconds elapsed.
     * @param now - current timestamp in milliseconds.
     * @return number of milliseconds elapsed since last set.
     */
    [[nodiscard]] uint32_t elapsed(const uint32_t now) const { return now - this->startTS; }

    /**
     * Returns true if the timer has expired.
     * @param now - current timestamp in milliseconds.
     * @return
     */
    [[nodiscard]] bool isExpired(const uint32_t now) const {
        if (this->left(now) == 0) {
            return true;
        }
        return false;
    }

    /**
     * Returns number of seconds left.
     * @param now - current timestamp in milliseconds.
     * @return number of milliseconds left since last set.
     * Returns 0 if number of milliseconds elapsed is more than timer duration.
     */
    [[nodiscard]] uint32_t left(const uint32_t now) const {
        uint32_t elapsed = this->elapsed(now);
        if (elapsed >= duration) {
            return 0;
        }
        return this->duration - elapsed;
    }

    /**
     * Start or restart the timer.
     * @param now - current timestamp in ms.
     */
    void set(const uint32_t now) { this->startTS = now; }
};

#endif  // ELO_LIB_TIMER_SRC_TIMER_H_
