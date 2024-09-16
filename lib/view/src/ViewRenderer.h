//
// Created by jieggii on 9/15/24.
//

#ifndef ELO_LIB_VIEW_SRC_VIEWRENDERER_H_
#define ELO_LIB_VIEW_SRC_VIEWRENDERER_H_

#include "cstdint"
#include "View.h"

class ViewRenderer {
   private:
    uint16_t renderInterval;
    uint32_t lastRenderTs = 0;
    bool renderInstantly = true;

    /**
     * Returns true if it is time to render view (considering current time, render interval and last render time).
     * @param now
     * @return
     */
    [[nodiscard]] bool isTimeToRender(uint32_t now) const {
        if (now - this->lastRenderTs >= this->renderInterval) {
            return true;
        }
        return false;
    }

   public:
    ViewRenderer(uint16_t renderInterval) : renderInterval(renderInterval) {}

    /**
     * Render next view instantly, omitting waiting for render interval.
     */
    void setRenderViewInstantly() {
        this->renderInstantly = true;
    }

    /**
     * Conditionally render view.
     * @param now
     * @param view
     */
    void conditionallyRender(uint32_t now, View* view) {
        if (this->renderInstantly) {
            view->render();
            this->renderInstantly = false;
        } else if (this->isTimeToRender(now)) {
            view->render();
        }

        this->lastRenderTs = now;
    }
};

#endif  // ELO_LIB_VIEW_SRC_VIEWRENDERER_H_
