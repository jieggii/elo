//
// Created by jieggii on 9/15/24.
//

#ifndef ELO_LIB_VIEW_SRC_VIEWRENDERER_H_
#define ELO_LIB_VIEW_SRC_VIEWRENDERER_H_

#include "cstdint"
#include "View.h"
#include "Timer.h"

/**
 * ViewRenderer is responsible for peridocally rendering views.
 */
class ViewRenderer {
   private:
    Timer renderTimer;
    bool renderViewInstantly = false;

    /**
     * Renders given view and resets render timer.
     * @param now - current timestamp in milliseconds.
     * @param view - view to render.
     */
    void render(uint32_t now, View* view) {
        view->render();
        this->setTimer(now);  // restart timer to render the next frame
    }

   public:
    /**
     * @param renderInterval - rendering interval in milliseconds
     */
    explicit ViewRenderer(uint16_t renderInterval) : renderTimer(renderInterval) {}

    /**
     * Starts render timer.
     * @param now - current timestamp in milliseconds.
     */
    void setTimer(uint32_t now) { this->renderTimer.set(now); }

    /**
     * Render next view instantly, omitting waiting for render interval.
     */
    void renderNextFrameInstantly() { this->renderViewInstantly = true; }

    /**
     * Conditionally render view.
     * @param now - current timestamp in milliseconds.
     * @param view - view to render.
     */
    void conditionallyRender(uint32_t now, View* view) {
        // render view if it must be rendered instantly:
        if (this->renderViewInstantly) {
            this->renderViewInstantly = false;
            this->render(now, view);
            return;
        }

        // render view if renderTimer has expired:
        if (this->renderTimer.isExpired(now)) {
            this->render(now, view);
            return;
        }
    }
};

#endif  // ELO_LIB_VIEW_SRC_VIEWRENDERER_H_
