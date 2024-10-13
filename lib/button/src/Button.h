//
// Created by jieggii on 10/11/24.
//

#ifndef BUTTON_H
#define BUTTON_H

#include <cstdint>

;

class Button {
   public:
    enum class ButtonState {
        IS_RELEASED,
        IS_ACTUATED,
        IS_PRESSED,
    };

    explicit Button(uint8_t pin);

    void init() const;
    void update();

    bool isActuated() const;
    bool isPressed() const;
    bool isReleased() const;

    // [[nodiscard]] ButtonState getState() const;

   private:
    const uint8_t pin;

    ButtonState state = ButtonState::IS_RELEASED;
};

#endif  // BUTTON_H
