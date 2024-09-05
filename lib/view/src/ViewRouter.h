//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_VIEWROUTER_H
#define ELO_VIEWROUTER_H

#include "View.h"
#include "memory"

#define MAX_VIEWS 10

using ViewFactory = std::function<std::shared_ptr<View>()>;

class ViewRouter {
   private:
    ViewFactory view_factories[MAX_VIEWS];
    std::shared_ptr<View> current_view;

   public:
    ViewRouter() = default;

    void registerView(uint8_t index, const ViewFactory& factory) {
        if (index < 0 || index > MAX_VIEWS - 1) {
            debug_println("error: registerView: index is out of bounds");
            return;
        }

        this->view_factories[index] = factory;
    }

    void switchView(uint8_t index) {
        if (index < 0 || index > MAX_VIEWS - 1) {
            debug_println("error: switchView: index is out of bounds");
            return;
        }

        ViewFactory view_factory = this->view_factories[index];
        this->current_view = view_factory();
        this->getCurrentView()->setup();
    }

    [[nodiscard]] std::shared_ptr<View> getCurrentView() const { return this->current_view; }
};

#endif  // ELO_VIEWROUTER_H
