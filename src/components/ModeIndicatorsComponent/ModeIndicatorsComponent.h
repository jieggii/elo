#ifndef MODE_INDICATORS_COMPONENT_H
#define MODE_INDICATORS_COMPONENT_H

#include "ViewComponent.h"

#include "components/IconComponent/IconComponent.h"
#include "ModeIndicatorsComponentState.h"

/**
 * ModeIndicatorComponent is a component which encapsulates two IconComponents and represents mode indicator.
 * The first icon is located at the given coordinates, the second icon is located at the next column and the same row.
 */
class ModeIndicatorsComponent final : public ViewComponent<ModeIndicatorsComponentState&> {
   public:
    /**
     * Creates a new instance of ModeIndicatorsComponent
     * @param state state of the component.
     * @param coordinates coordinates of the first icon.
     */
    ModeIndicatorsComponent(ModeIndicatorsComponentState& state, display::Coordinates coordinates);

    /**
     * Renders the component.
     * @param display Display to render on.
     */
    void render(display::Display& display) override;

   private:
    IconComponent icon1;
    IconComponent icon2;

    void renderHidden(display::Display& display) const override;
};

#endif  // MODE_INDICATORS_COMPONENT_H