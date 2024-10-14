//
// Created by jieggii on 9/12/24.
//

#ifndef ELO_VIEWNAVIGATOR_H_
#define ELO_VIEWNAVIGATOR_H_

#include <cstdint>

#include "debug_print.h"

/**
 * ViewNavigator is responsible for navigating between views.
 * It basically holds the index of the current view.
 * TODO: split into two classess:
 * 1. Public one, which is capable only of changing view index.
 * 2. Internal one, which has some useful methods and a flag (currentViewIndexChanged).
 */
class ViewNavigator {
   public:
    explicit ViewNavigator(const uint8_t initialViewIndex) : currentViewIndex(initialViewIndex) {}

    /**
     * Returns index of the current view.
     * @return current view index.
     */
    [[nodiscard]] uint8_t getCurrentViewIndex() const { return this->currentViewIndex; }

    /**
     * Returns true if view index has been changed.
     * @return true if view index has been changed.
     */
    [[nodiscard]] bool hasViewIndexChanged() const { return this->currentViewIndexChanged; }

    /**
     * Resets view index changed flag.
     */
    void resetViewIndexChangedFlag() { this->currentViewIndexChanged = false; }

    /**
     * Navigates to the next view.
     * @param viewIndex index of the view to navigate to.
     */
    void navigateTo(const uint8_t viewIndex) {
#ifdef DEBUG
        if (viewIndex == this->currentViewIndex) {
            debug_print("err: ViewNavigator.navigate: navigating to the current view ");
            debug_println(viewIndex);
        }
#endif
        this->currentViewIndexChanged = true;
        this->currentViewIndex = viewIndex;
    }

   private:
    uint8_t currentViewIndex;             // index of the current view
    bool currentViewIndexChanged = true;  // flag indicating that view index has been changed
};

#endif  // ELO_VIEWNAVIGATOR_H_
