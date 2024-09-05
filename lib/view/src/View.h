//
// Created by jieggii on 9/3/24.
//

#ifndef ELO_VIEW_H
#define ELO_VIEW_H

#include <utility>

#include "cstdint"
#include "functional"

class View {
   public:
    virtual void setup() const = 0;
    virtual void loop() const = 0;
    //    virtual void cleanup() const = 0;

    virtual ~View() = default;
};

#endif  // ELO_VIEW_H
