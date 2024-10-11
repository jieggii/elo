//
// Created by jieggii on 10/11/24.
//

#include <Arduino.h>

#include "Button.h"

Button::Button(const uint8_t addr, const uint32_t longPressDuration) : pin(addr), longPressDuration(longPressDuration) {
    pinMode(addr, INPUT);
}

bool Button::isPressed() const { return this->state == ButtonState::PRESS; }

bool Button::isLongPressed() const { return this->state == ButtonState::LONG_PRESS; }

void Button::updateState(const uint32_t now) {
    const bool isPressed = digitalRead(this->pin) == HIGH;

    if (isPressed && this->state == ButtonState::RELEASE) {
        this->state = ButtonState::PRESS;
        this->longPressStart = now;

    } else if (isPressed && this->state == ButtonState::PRESS) {
        if (now - this->longPressStart >= this->longPressDuration) {
            this->state = ButtonState::LONG_PRESS;
        }

    } else if (!isPressed && this->state != ButtonState::RELEASE) {
        this->state = ButtonState::RELEASE;
    }
}