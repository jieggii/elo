//
// Created by jieggii on 10/11/24.
//

#include <Arduino.h>

#include "Button.h"

Button::Button(const uint8_t pin) : pin(pin) {}

void Button::init() const { pinMode(this->pin, INPUT); }

void Button::update() {
    const bool isPressed = digitalRead(this->pin) == HIGH;

    switch (this->state) {
        case ButtonState::IS_RELEASED:
            if (isPressed) {
                this->state = ButtonState::IS_ACTUATED;
            }
            break;
        case ButtonState::IS_ACTUATED:
            if (isPressed) {
                this->state = ButtonState::IS_PRESSED;
            } else {
                this->state = ButtonState::IS_RELEASED;
            }
            break;
        case ButtonState::IS_PRESSED:
            if (!isPressed) {
                this->state = ButtonState::IS_RELEASED;
            }
            break;
    }
}

bool Button::isActuated() const { return this->state == ButtonState::IS_ACTUATED; }
bool Button::isPressed() const { return this->state == ButtonState::IS_PRESSED; }
bool Button::isReleased() const { return this->state == ButtonState::IS_RELEASED; }
