#ifndef MEASUREMENTSLINECOMPONENT_H
#define MEASUREMENTSLINECOMPONENT_H

#include "Display.h"
#include "ViewComponent.h"
#include "MeasurementsLineComponentState.h"

/**
 * MeasurementsLineComponent line displaying environmental measurements and their statuses.
 * TODO: include logic for isNeedRerendering. If icons are being displayed, do not rerender the component to avoid
 * flickering.
 */
class MeasurementsLineComponent final : public ViewComponent<MeasurementsLineComponentState&> {
   public:
    // TODO: move constructor implementation to cpp file.
    MeasurementsLineComponent(MeasurementsLineComponentState& state, const display::Coordinates coordinates)
        : ViewComponent(state, coordinates) {}

    void update(uint32_t now) override;
    /**
     * Render the component.
     */
    void render(display::Display& display) override;

   private:
    void renderHidden(display::Display& display) const override;
    /**
     * Render measurements.
     */
    void renderMeasurements(display::Display& display) const;

    /**
     * Render measurement status icons.
     */
    void renderMeasurementStatusIcons(display::Display& display) const;
};

#endif  // MEASUREMENTSLINECOMPONENT_H