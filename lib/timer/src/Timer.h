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
     * TODO: set default value for duration to 0.
     */
    explicit Timer(const uint32_t duration) : duration(duration) {}

    /**
     * Set the duration of the timer.
     * TODO: move to cpp file.
     */
    void setDuration(const uint32_t duration) { this->duration = duration; }

    /**
     * Create a timer from seconds.
     * @param duration duration of the timer in seconds.
     * @return Timer object.
     */
    static Timer fromSeconds(uint16_t duration);

    /**
     * Returns true if the timer is paused.
     */
    [[nodiscard]] bool isPaused() const;

    /**
     * Start or restart the timer.
     * If the timer is paused, it will be resumed.
     * @param now current timestamp in milliseconds.
     */
    void set(uint32_t now);

    /**
     * Pause the timer.
     */
    void pause(uint32_t now);

    /**
     * Resume the timer.
     */
    void resume(uint32_t now);

    /**
     * Returns number of milliseconds elapsed.
     * If the timer is paused, returns time elapsed until paused.
     * Cannot return more than timer duration.
     * @param now current timestamp in milliseconds.
     */
    [[nodiscard]] uint32_t elapsed(uint32_t now) const;

    /**
     * Returns number of seconds left until timer expires.
     * Cannot return less than 0.
     * @param now current timestamp in milliseconds.
     */
    [[nodiscard]] uint32_t left(uint32_t now) const;

    /**
     * Returns true if the timer has expired.
     * @param now current timestamp in milliseconds.
     */
    [[nodiscard]] bool isExpired(uint32_t now) const;

   private:
    uint32_t duration;  // timer duration in ms

    uint32_t startTimestamp = 0;  // timestamp of the timer set
    uint32_t pauseTimestamp = 0;  // timestamp of the timer pause

    bool paused = false;
};

#endif  // ELO_LIB_TIMER_SRC_TIMER_H_
