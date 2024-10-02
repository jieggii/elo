#ifndef BASE_DISPLAY_VIEW_COMPONENTS
#define BASE_DISPLAY_VIEW_COMPONENTS

#include <cstdint>

#include "LCD1602.h"
#include "ViewComponent.h"

struct ClockTime {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;

    ClockTime(const uint8_t hours, const uint8_t minutes, const uint8_t seconds)
        : hours(hours), minutes(minutes), seconds(seconds){};

    /**
     * Creates ClockTime with the given time value provided as a timestamp in seconds.
     * For example, timestamp=65 will set hours to 0, minutes to 1 and seconds to 5.
     *
     * Note: the methods supports only uint16_t timestamps in seconds, meaning, that maximum value is ~18 hours.
     */
    explicit ClockTime(const uint16_t timestamp)
        : hours(static_cast<uint8_t>(timestamp / 3600)),
          minutes(static_cast<uint8_t>((timestamp % 3600) / 60)),
          seconds(static_cast<uint8_t>(timestamp % 60)) {}
};

/**
 * ClockComponent represents a clock which displays hours, minutes and seconds.
 */
class ClockComponent final : public ViewComponent {
    ClockTime time;

   public:
    /**
     * Creates a clock component with the given coordinates and time.
     */
    ClockComponent(const DisplayCoordinates coordinates, const ClockTime time)
        : ViewComponent(coordinates), time(time) {}

    /**
     * Sets clock to the given time provided as hours, minutes and seconds.
     */
    void setTime(const ClockTime time) { this->time = time; }

    void render(LCD1602* display) override { display->displayText("00:00:00", this->coordinates); };  // todo
};

#endif