//
// Created by jieggii on 10/14/24.
//

#ifndef APP_H
#define APP_H

#include <cstdint>

#include "debug_print.h"

#include "Display.h"
#include "ViewNavigator.h"
#include "internal/ViewRegistry.h"
#include "internal/ViewRenderer.h"

class App {
   public:
    explicit App(Display& display, const uint16_t renderInterval)
        : display(display), viewNavigator(0), viewRenderer(this->display, renderInterval){};

    void registerView(const uint8_t viewID, View* view) { this->viewRegistry.registerView(viewID, view); }

    ViewNavigator& getViewNavigator() { return this->viewNavigator; }

    void serve(const uint32_t now) {
        // TODO: if now is needed only in the end of this function, then get it there
        // because there is a big chance, that it will not be used at all.
        const uint8_t currentViewIndex = this->viewNavigator.getCurrentViewIndex();
        View* currentView = this->viewRegistry.getView(currentViewIndex);

        if (this->viewNavigator.hasViewIndexChanged()) {
#ifdef DEBUG
            if (currentView == nullptr) {
                debug_print("err: App.serve: view with index ");
                debug_print(currentViewIndex);
                debug_println(" is not registered");
                return;
            }
#endif
            this->viewNavigator.resetViewIndexChangedFlag();
            currentView->setup(now, this->display);
            this->viewRenderer.requestImmediateRender();
            display.clear();  // clear display after view change
        }

        currentView->handleInputs(now);
        if (this->viewNavigator.hasViewIndexChanged()) {  // stop serving this view if view has changed due to inputs
            return;
        }

        currentView->update(now);
        if (this->viewNavigator.hasViewIndexChanged()) {  // stop serving this view if view has changed due to loop call
            return;
        }

        this->viewRenderer.renderIfNeeded(currentView, now);
    }

   private:
    /**
     * Display used to render views.
     */
    Display& display;

    /**
     * View registry used to store views.
     */
    ViewRegistry viewRegistry;

    /**
     * View navigator used to navigate between views.
     */
    ViewNavigator viewNavigator;

    /**
     * View renderer used to render views.
     */
    ViewRenderer viewRenderer;
};

#endif  // APP_H
