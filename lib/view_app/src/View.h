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
    virtual void setup(uint32_t now, display::Display& display) = 0;

    /*
     * Update view state.
     * This method should be called before calling @render.
     */
    virtual void update(uint32_t now) = 0;

    /**
     * Handle hardware inputs (e.g. buttons).
     * This method should be called before calling @loop and @render.
     * TODO: consider renaming to "handleInput" or "handle buttons"
     */
    virtual void handleInputs(uint32_t now) = 0;

    /*
     * Render view on the display.
     * This method should be called after @loop and @handleInputs are called.
     */
    virtual void render(display::Display& display) = 0;

    /**
     * Resets view state is called when the view is being left.
     */
    virtual void reset(uint32_t now) = 0;

    virtual ~View() = default;
};

#endif  // ELO_VIEW_H_
