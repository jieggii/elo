#ifndef BASE_DISPLAY_VIEW_COMPONENTS
#define BASE_DISPLAY_VIEW_COMPONENTS

#include <cstdint>

#include "Display.h"
#include "ViewComponent.h"

/**
 * ClockTime represents a time in hours, minutes and seconds, which is displayed by the @ClockComponent.
 */
struct ClockTime {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

    /**
     * Creates a ClockTime object from the given timestamp in seconds.
     * @param timestamp - timestamp in seconds
     * Note: timestamp is expected to be in the range of uint16_t, meaning that the maximum value is around 18 hours.
     */
    static ClockTime fromSTimestamp(uint16_t timestamp);

    /**
     * Creates a ClockTime object from the given timestamp in milliseconds.
     * @param timestamp - timestamp in milliseconds
     */
    static ClockTime fromMsTimestamp(uint32_t timestamp);
};

/**
 * ClockComponent represents a clock which displays hours, minutes and seconds.
 */
class ClockComponent final : public ViewComponent {
   public:
    /**
     * Creates a clock component with the given coordinates and time.
     */
    explicit ClockComponent(const DisplayCoordinates coordinates) : ViewComponent(coordinates) {}

    /**
     * Sets clock to the given time provided as hours, minutes and seconds.
     */
    void setTime(ClockTime time);

    /**
     * Renders the clock on the display.
     */
    void render(Display* display) override;

   private:
    ClockTime time = {0, 0, 0};
};

#endif