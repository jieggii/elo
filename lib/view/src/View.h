//
// Created by jieggii on 9/12/24.
//

#ifndef ELO_VIEW_H_
#define ELO_VIEW_H_

#include "LCD1602.h"
#include "ViewNavigator.h"

class ViewController;
class View {
   protected:
    LCD1602* display;
    ViewNavigator* viewNavigator;

   public:
    View(LCD1602* display, ViewNavigator* viewNavigator)
        : display(display), viewNavigator(viewNavigator) {}

    virtual void setup() const = 0;
    virtual void loop() const = 0;

    virtual ~View() = default;
};

#endif  // ELO_VIEW_H_
