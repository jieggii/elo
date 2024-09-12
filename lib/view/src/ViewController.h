//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_VIEWROUTER_H
#define ELO_VIEWROUTER_H

#include "memory"
#include "debug_print.h"

#include "ViewNavigator.h"

class ViewRouter;
class BaseView {
   protected:
    LCD1602* display;
    ViewRouter* router;

   public:
    BaseView(LCD1602* display, ViewRouter* router)
        : display(display), router(router) {}

    virtual void setup() const = 0;
//    virtual void loop(BaseContext* ctx) const = 0;
    virtual void loop() const = 0;

    virtual ~BaseView() = default;
};

class BaseViewContext {
   public:
    virtual ~BaseViewContext() = default;
};

#define MAX_VIEWS 10
class ViewRouter {
   private:

    BaseView* views[MAX_VIEWS] = {nullptr};
    ViewNavigator* viewNavigator;

   public:
    ViewRouter() = default;

    void registerView(uint8_t index, BaseView* view) {
#ifdef DEBUG
        if (index > MAX_VIEWS - 1) {
            debug_println("err: registerView: index is out of bounds");
            return;
        }

        if (this->views[index] != nullptr) {
            debug_print("err: registerView: index ");
            debug_print(index);
            debug_println(" is already taken");
            return;
        }
#endif
        this->views[index] = view;
    }

    void switchView(uint8_t index) {
#ifdef DEBUG
        if (index > MAX_VIEWS - 1) {
            debug_println("error: registerView: index is out of bounds");
            return;
        }

        if (this->views[index] == nullptr) {
            debug_print("err: switchView: index ");
            debug_print(index);
            debug_println(" is not registered");
            return;
        }
#endif
        this->current_view_index = index;
    }

    [[nodiscard]] BaseView* getCurrentView() { // todo: make const method and const pointer?
#ifdef DEBUG
        if (this->views[this->current_view_index] == nullptr) {
            debug_println("err: getCurrentView: current view is a null pointer");
        }
#endif
        return this->views[current_view_index];
    }
};

#endif  // ELO_VIEWROUTER_H
// todo: ViewController and ViewSwitcher? ViewNavigator?