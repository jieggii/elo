#ifndef BASE_DISPLAY_VIEW_COMPONENTS
#define BASE_DISPLAY_VIEW_COMPONENTS

#include <cstdint>

#include "LCD1602.h"
#include "ViewComponent.h"

/**
 * ClockComponent represents a clock which displays hours, minutes and seconds.
 */
class ClockComponent final : public ViewComponent {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

   public:
    /**
     * Creates a clock component with the given coordinates and time.
     */
    ClockComponent(LCD1602* display, DisplayCoordinates coordinates, uint8_t hours, uint8_t minutes, uint8_t seconds)
        : ViewComponent(display, coordinates), hours(hours), minutes(minutes), seconds(seconds) {}

    /**
     * Creates a clock component with the given coordinates and time provided as a timestamp in seconds.
     */
    ClockComponent(LCD1602* display, DisplayCoordinates coordinates, uint16_t timestamp)
        : ViewComponent(display, coordinates) {
        this->setTimeFromTimestamp(timestamp);
    }

    /**
     * Sets clock to the given time provided as hours, minutes and seconds.
     */
    void setTime(uint8_t hours, uint8_t minutes, uint8_t seconds) {
        this->hours = hours;
        this->minutes = minutes;
        this->seconds = seconds;
    }

    /**
     * Sets clock to the given time provideded as a timestamp in seconds.
     * For example, timestamp=65 will set hours to 0, minutes to 1 and seconds to 5.
     *
     * Note: the methods supports only uint16_t timestamps in seconds, meaning, that maximum value is ~18 hours.
     * If you need to set higher values, use setTime method.
     */
    void setTimeFromTimestamp(uint16_t timestamp) {
        this->hours = timestamp / 3600;
        this->minutes = (timestamp % 3600) / 60;
        this->seconds = timestamp % 60;
    }

    void loop(uint32_t now) override {};
    void render() override { this->display->displayText("00:00:00", this->coordinates); };  // todo
};

#endif