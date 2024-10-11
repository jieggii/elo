//
// Created by jieggii on 10/5/24.
//

#include "ClockComponent.h"

ClockTime ClockTime::fromSTimestamp(const uint16_t timestamp) {
    return ClockTime{static_cast<uint8_t>(timestamp / 3600), static_cast<uint8_t>(timestamp % 3600 / 60),
                     static_cast<uint8_t>(timestamp % 60)};
}

ClockTime ClockTime::fromMsTimestamp(const uint32_t timestamp) { return fromSTimestamp(timestamp / 1000); }

void ClockComponent::setTime(const ClockTime time) { this->time = time; }

void ClockComponent::render(Display* display) {
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
}