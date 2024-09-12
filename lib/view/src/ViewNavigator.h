//
// Created by jieggii on 9/12/24.
//

#ifndef ELO_VIEWNAVIGATOR_H_
#define ELO_VIEWNAVIGATOR_H_

#include <cstdint>

#include "debug_print.h"

class ViewNavigator {
   private:
    uint8_t currentViewIndex = 0;

   public:
    ViewNavigator() = default;

    void navigate(uint8_t viewIndex) {
#ifdef DEBUG
        if (viewIndex == this->currentViewIndex) {
            debug_println("err: ViewNavigator.navigate: navigating to the current view");
        }
#endif
        this->currentViewIndex = viewIndex;
    }

    [[nodiscard]] uint8_t getCurrentViewIndex() const { return this->currentViewIndex; }
};

#endif  // ELO_VIEWNAVIGATOR_H_
