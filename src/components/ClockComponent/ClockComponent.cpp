//
// Created by jieggii on 10/5/24.
//

#include "debug_print.h"

#include "ClockComponent.h"

class RenderBuffer {
   public:
    RenderBuffer() = default;

    /**
     * Returns empty buffer.
     * @return empty buffer.
     */
    static RenderBuffer empty() {
        constexpr RenderBuffer buffer;
        return buffer;
    }

    /**
     * Returns buffer with formatted time.
     * @param hours hours.
     * @param minutes minutes.
     * @param seconds seconds.
     * @return buffer with formatted time.
     */
    static RenderBuffer formated(const uint8_t hours, const uint8_t minutes, const uint8_t seconds) {
        RenderBuffer buffer;
        buffer.format(hours, minutes, seconds);
        return buffer;
    }

    [[nodiscard]] const char* getBuffer() const { return buffer; }

   private:
    static constexpr uint8_t BUFFER_SIZE = 9;

    static constexpr uint8_t HOURS_OFFSET = 0;
    static constexpr uint8_t MINUTES_OFFSET = 3;
    static constexpr uint8_t SECONDS_OFFSET = 6;
    static constexpr uint8_t VALUE_LEN = 2;

    char buffer[BUFFER_SIZE] = {};

    void format(const uint8_t hours, const uint8_t minutes, const uint8_t seconds) {
        this->formatValue(hours, HOURS_OFFSET);
        this->formatColon(HOURS_OFFSET + VALUE_LEN);

        this->formatValue(minutes, MINUTES_OFFSET);
        this->formatColon(MINUTES_OFFSET + VALUE_LEN);

        this->formatValue(seconds, SECONDS_OFFSET);
        this->formatNullTerm();
    }

    void formatValue(const uint8_t value, const uint8_t offset) {
        buffer[offset] = static_cast<char>('0' + value / 10);
        buffer[offset + 1] = static_cast<char>('0' + value % 10);
    }

    void formatColon(const uint8_t offset) { buffer[offset] = ':'; }

    void formatNullTerm() { buffer[BUFFER_SIZE - 1] = '\0'; }
};

void ClockComponent::render(display::Display& display) {
    const auto& state = this->getState();
    if (state.isHidden()) {  // render hidden if hidden
        this->renderHidden(display);
        return;
    }

    const auto [hours, minutes, seconds] = state.getTime();
    const auto renderBuffer = RenderBuffer::formated(hours, minutes, seconds);
    display.displayText(renderBuffer.getBuffer(), this->coordinates);
}

void ClockComponent::renderHidden(display::Display& display) const {
    // const auto renderBuffer = RenderBuffer::empty();
    display.displayText("        ", this->coordinates);
}
