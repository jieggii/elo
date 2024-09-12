//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_VIEWCONTROLLER_H
#define ELO_VIEWCONTROLLER_H

#include "memory"
#include "debug_print.h"

#include "ViewNavigator.h"
#include "View.h"

#define MAX_VIEWS 10
class ViewController {
   private:
    View* views[MAX_VIEWS] = {nullptr};

   public:
    ViewController() = default;

    void registerView(uint8_t index, View* view) {
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

    [[nodiscard]] View* getView(uint8_t index) {
        if (index > MAX_VIEWS - 1) {
            debug_println("err: ViewController.getView: view index is out of bounds");
            return nullptr;
        }
        return this->views[index];
    }
};

#endif  // ELO_VIEWCONTROLLER_H
