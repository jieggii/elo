//
// Created by jieggii on 9/16/24.
//

#ifndef ELO_LIB_TIMER_SRC_TIMER_H_
#define ELO_LIB_TIMER_SRC_TIMER_H_

#include "cstdint"

class Timer {
   public:
    /**
     * Create a timer from milliseconds.
     * @param duration duration of the timer in milliseconds.
     */
    explicit Timer(const uint32_t duration) : duration(duration) {}

    /**
     * Create a timer from seconds.
     * @param duration duration of the timer in seconds.
     * @return Timer object.
     */
    static Timer fromSeconds(uint16_t duration);

    /**
     * Start or restart the timer.
     * @param now current timestamp in milliseconds.
     */
    void set(uint32_t now);

    /**
     * Returns number of milliseconds elapsed.
     * @param now current timestamp in milliseconds.
     * @return number of milliseconds elapsed since last set.
     */
    [[nodiscard]] uint32_t elapsed(uint32_t now) const;

    /**
     * Returns number of seconds left.
     * @param now current timestamp in milliseconds.
     * @return number of milliseconds left since last set.
     * Returns 0 if number of milliseconds elapsed is more than timer duration.
     */
    [[nodiscard]] uint32_t left(uint32_t now) const;

    /**
     * Returns true if the timer has expired.
     * @param now current timestamp in milliseconds.
     */
    [[nodiscard]] bool isExpired(uint32_t now) const;

   private:
    uint32_t duration;     // timer duration in ms
    uint32_t startTS = 0;  // timestamp of the timer set
};

#endif  // ELO_LIB_TIMER_SRC_TIMER_H_
