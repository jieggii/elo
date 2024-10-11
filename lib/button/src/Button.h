//
// Created by jieggii on 10/11/24.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>

class Button {
   public:
    Button(uint8_t addr, uint32_t longPressDuration);

    /**
     * Returns true if the button is pressed.
     */
    [[nodiscard]] bool isPressed() const;

    /**
     * Returns true if the button is long pressed.
     */
    [[nodiscard]] bool isLongPressed() const;

    /**
     * Updates the state of the button.
     * @param now - current time in milliseconds
     */
    void updateState(uint32_t now);

   private:
    const uint8_t pin;
    const uint32_t longPressDuration;

    uint32_t longPressStart = 0;
    enum class ButtonState {
        PRESS,       // button is pressed
        LONG_PRESS,  // button is long pressed
        RELEASE,     // button is released
    } state = ButtonState::RELEASE;
};

#endif  // BUTTON_H
