//
// Created by jieggii on 10/12/24.
//

#ifndef MODEINDICATORSCOMPONENTSTATE_H
#define MODEINDICATORSCOMPONENTSTATE_H

#include "components/IconComponent/IconComponentState.h"
#include "ViewComponentState.h"

class ModeIndicatorsComponentState final : public ViewComponentState {
   public:
    ModeIndicatorsComponentState(const uint8_t icon1ID, const uint8_t icon2ID)
        : icon1State(IconComponentState(icon1ID)), icon2State(icon2ID) {}

    /**
     * Get the icon 1 state of the mode indicators component.
     */
    [[nodiscard]] IconComponentState& getIcon1State();

    /**
     * Get the icon 2 state of the mode indicators component.
     */
    [[nodiscard]] IconComponentState& getIcon2State();

   private:
    IconComponentState icon1State;
    IconComponentState icon2State;
};

#endif  // MODEINDICATORSCOMPONENTSTATE_H
