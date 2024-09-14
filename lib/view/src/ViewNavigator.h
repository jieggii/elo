//
// Created by jieggii on 9/12/24.
//

#ifndef ELO_VIEWNAVIGATOR_H_
#define ELO_VIEWNAVIGATOR_H_

#include <cstdint>

#include "debug_print.h"

class ViewNavigator {
   private:
    uint8_t viewIndex = 0;
    bool viewIndexChanged = false;

   public:
    ViewNavigator() = default;

    [[nodiscard]] uint8_t getViewIndex() const { return this->viewIndex; }

    [[nodiscard]] bool getViewIndexChanged() const { return this->viewIndexChanged; }

    void resetViewIndexChanged() { this->viewIndexChanged = false; }

    void navigate(uint8_t nextViewIndex) {
#ifdef DEBUG
        if (nextViewIndex == this->viewIndex) {
            debug_print("err: ViewNavigator.navigate: navigating to the current view ");
            debug_println(nextViewIndex);
        }
#endif
        this->viewIndexChanged = true;
        this->viewIndex = nextViewIndex;
    }
};

#endif  // ELO_VIEWNAVIGATOR_H_
