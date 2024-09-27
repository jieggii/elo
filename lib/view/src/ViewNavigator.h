//
// Created by jieggii on 9/12/24.
//

#ifndef ELO_VIEWNAVIGATOR_H_
#define ELO_VIEWNAVIGATOR_H_

#include <cstdint>

#include "debug_print.h"

/**
 * ViewNavigator is responsible for navigating between views.
 */
class ViewNavigator {
   private:
    uint8_t viewIndex;
    bool viewIndexChanged = true;

   public:
    explicit ViewNavigator(uint8_t initialViewIndex) : viewIndex(initialViewIndex) {}

    /**
     * @return current view index.
     */
    [[nodiscard]] uint8_t getViewIndex() const { return this->viewIndex; }

    /**
     * @return true if view index has been changed, false otherwise.
     */
    [[nodiscard]] bool getViewIndexChanged() const { return this->viewIndexChanged; }

    /**
     * Resets view index changed flag.
     */
    void resetViewIndexChanged() { this->viewIndexChanged = false; }

    /**
     * Navigates to the next view.
     * @param nextViewIndex - index of the next view.
     */
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
