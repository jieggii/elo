//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_VIEWCONTROLLER_H
#define ELO_VIEWCONTROLLER_H

// #include "memory"
#include <cstdint>

#include "debug_print.h"

#include "View.h"
#include "ViewNavigator.h"

/**
 * Maximum number of views can be registered.
 */
constexpr uint8_t MAX_VIEWS = 10;

/**
 * ViewController is responsible for managing views.
 * It allows to register and retrieve views by their indexes.
 * TODO: change terms: view index -> view ID?
 */
class ViewRegistry {
    View* views[MAX_VIEWS] = {nullptr};

   public:
    ViewRegistry() = default;

    /**
     * Registers view.
     */
    void registerView(const uint8_t index, View* view) {
        if (index > MAX_VIEWS - 1) {
            debug_println("err: ViewController.registerView: view index is out of bounds");
            return;
        }

        if (this->views[index] != nullptr) {
            debug_print("err: ViewController.registerView: view with index ");
            debug_print(index);
            debug_println(" is already registered");
            return;
        }

        this->views[index] = view;
    }

    /**
     * Returns view by its index. Returns nullptr if view with such index is not registered.
     * @param id view id.
     * TODO: consider returning reference instead of a pointer?
     */
    [[nodiscard]] View* getView(const uint8_t index) const {
        if (index > MAX_VIEWS - 1) {
            debug_println("err: ViewController.getView: view index is out of bounds");
            return nullptr;
        }
        return this->views[index];
    }
};

#endif  // ELO_VIEWCONTROLLER_H
