//
// Created by jieggii on 9/15/24.
//

#ifndef ELO_LIB_VIEW_SRC_VIEWRENDERER_H_
#define ELO_LIB_VIEW_SRC_VIEWRENDERER_H_

#include <cstdint>

#include "Display.h"
#include "View.h"
#include "Timer.h"

/**
 * ViewRenderer is responsible for rendering views once per a certain interval.
 */
class ViewRenderer {
    Timer renderTimer;
    bool renderImmediately = true;  // render the first frame immediately by default.

   public:
    /**
     * @param renderInterval - rendering interval in milliseconds
     */
    explicit ViewRenderer(const uint16_t renderInterval) : renderTimer(renderInterval) {
        // we can set the timer to 0 here, because the first frame shall be rendered immediately anyway.
        this->renderTimer.set(0);
    }

    /**
     * Request to render the next frame immediately.
     */
    void requestImmediateRender() { this->renderImmediately = true; }

    /**
     * Conditionally render view.
     * @param display - display to render on.
     * @param view - view to render.
     * @param now - current timestamp in milliseconds.
     */
    void renderIfNeeded(Display* display, View* view, const uint32_t now) {
        if (this->renderImmediately || this->renderTimer.isExpired(now)) {
            view->render(display);
            this->renderTimer.set(now);       // restart timer to render the next frame
            this->renderImmediately = false;  // reset immediate render flag
        }
    }
};

#endif  // ELO_LIB_VIEW_SRC_VIEWRENDERER_H_
