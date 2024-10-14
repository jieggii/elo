//
// Created by jieggii on 10/5/24.
//

#include "ClockComponent.h"

class RenderBuffer {
   public:
    RenderBuffer() = default;

    void format(const uint8_t hours, const uint8_t minutes, const uint8_t seconds) {
        this->formatValue(hours, HOURS_OFFSET);
        this->formatColon(HOURS_OFFSET + VALUE_LEN);

        this->formatValue(minutes, MINUTES_OFFSET);
        this->formatColon(MINUTES_OFFSET + VALUE_LEN);

        this->formatValue(seconds, SECONDS_OFFSET);
        this->formatNullTerm();
    }

    [[nodiscard]] const char* getBuffer() const { return buffer; }

   private:
    static constexpr uint8_t BUFFER_SIZE = 9;

    static constexpr uint8_t HOURS_OFFSET = 0;
    static constexpr uint8_t MINUTES_OFFSET = 3;
    static constexpr uint8_t SECONDS_OFFSET = 6;
    static constexpr uint8_t VALUE_LEN = 2;

    char buffer[BUFFER_SIZE] = {};

    void formatValue(const uint8_t value, const uint8_t offset) {
        buffer[offset] = static_cast<char>('0' + value / 10);
        buffer[offset + 1] = static_cast<char>('0' + value % 10);
    }

    void formatColon(const uint8_t offset) { buffer[offset] = ':'; }

    void formatNullTerm() { buffer[BUFFER_SIZE - 1] = '\0'; }
};

void ClockComponent::render(Display& display) {
    const auto [hours, minutes, seconds] = this->getState().getTime();

    RenderBuffer renderBuffer;
    renderBuffer.format(hours, minutes, seconds);
    display.displayText(renderBuffer.getBuffer(), this->coordinates);
}