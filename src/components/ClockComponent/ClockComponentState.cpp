//
// Created by jieggii on 10/12/24.
//

#include "ClockComponentState.h"

ClockTime ClockTime::zero() { return ClockTime{0, 0, 0}; }

ClockTime ClockTime::fromSTimestamp(const uint16_t timestamp) {
    return ClockTime{static_cast<uint8_t>(timestamp / 3600), static_cast<uint8_t>(timestamp % 3600 / 60),
                     static_cast<uint8_t>(timestamp % 60)};
}

ClockTime ClockTime::fromMsTimestamp(const uint32_t timestamp) { return fromSTimestamp(timestamp / 1000); }

void ClockComponentState::setTime(const ClockTime time) { this->time = time; }

ClockTime ClockComponentState::getTime() const { return this->time; }
