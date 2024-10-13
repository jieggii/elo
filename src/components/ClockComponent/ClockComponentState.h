//
// Created by jieggii on 10/12/24.
//

#ifndef CLOCKCOMPONENTSTATE_H
#define CLOCKCOMPONENTSTATE_H

#include <cstdint>

/**
 * ClockTime represents a time in hours, minutes and seconds, which is displayed by the @ClockComponent.
 */
struct ClockTime {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

    /**
     * Creates a ClockTime object with the zero time (00:00:00).
     */
    static ClockTime zero();

    /**
     * Creates a ClockTime object from the given timestamp in seconds.
     * @param timestamp - timestamp in seconds
     * Note: timestamp is expected to be in the range of uint16_t, meaning that the maximum value is around 18 hours.
      TODO: rename to fromSeconds.
    */
    static ClockTime fromSTimestamp(uint16_t timestamp);

    /**
     * Creates a ClockTime object from the given timestamp in milliseconds.
     * @param timestamp - timestamp in milliseconds
     * TODO: rename to fromMilliseconds.
     */
    static ClockTime fromMsTimestamp(uint32_t timestamp);
};

class ClockComponentState {
   public:
    /**
     * Creates a ClockComponentState object with the given time.
     */
    explicit ClockComponentState(const ClockTime time) : time(time){};

    /**
     * Sets clock to the given time provided as hours, minutes and seconds.
     */
    void setTime(ClockTime time);

    /**
     * Returns the time currently set.
     */
    [[nodiscard]] ClockTime getTime() const;

   private:
    ClockTime time = {0, 0, 0};
};

#endif  // CLOCKCOMPONENTSTATE_H
