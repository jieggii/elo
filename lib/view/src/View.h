//
// Created by jieggii on 9/12/24.
//

#ifndef ELO_VIEW_H_
#define ELO_VIEW_H_

#include "Display.h"

class ViewController;

/**
 * View is an interface for views.
 */
class View {
   public:
    View() = default;

    /**
     * Setup view.
     */
    virtual void setup(Display* display) = 0;

    /*
     * Update view state.
     */
    virtual void loop() = 0;

    /*
     * Render view on the display.
     */
    virtual void render(Display* display) = 0;

    /**
     * Reset view state.
     */
    virtual void reset() = 0;

    virtual ~View() = default;
};

#endif  // ELO_VIEW_H_
