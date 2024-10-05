#ifndef BASE_DISPLAY_VIEW_COMPONENTS
#define BASE_DISPLAY_VIEW_COMPONENTS

#include <cstdint>

#include "Display.h"
#include "ViewComponent.h"

struct ClockTime {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

    /**
     * Creates a ClockTime object from the given timestamp in seconds.
     * @param timestamp - timestamp in seconds
     * Note: The timestamp is expected to be in the range [0, 86399], meaning that the maximum value is around 18 hours.
     */
    static ClockTime fromTimestamp(const uint16_t timestamp) {
        return ClockTime{static_cast<uint8_t>(timestamp / 3600), static_cast<uint8_t>(timestamp % 3600 / 60),
                         static_cast<uint8_t>(timestamp % 60)};
    }
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
    void setTime(const ClockTime time) { this->time = time; }

    void render(Display* display) override {
        char buffer[9];  // buffer for the string representation of the time ("00:00:00")

        buffer[0] = static_cast<char>('0' + this->time.hours / 10);
        buffer[1] = static_cast<char>('0' + this->time.hours % 10);
        buffer[2] = ':';
        buffer[3] = static_cast<char>('0' + this->time.minutes / 10);
        buffer[4] = static_cast<char>('0' + this->time.minutes % 10);
        buffer[5] = ':';
        buffer[6] = static_cast<char>('0' + this->time.seconds / 10);
        buffer[7] = static_cast<char>('0' + this->time.seconds % 10);
        buffer[8] = '\0';  // Null-terminate the string

        display->displayText(buffer, this->coordinates);
    };

   private:
    ClockTime time = {0, 0, 0};
};

#endif