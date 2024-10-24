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
    MeasurementsLineComponent(MeasurementsLineComponentState& state, const DisplayCoordinates coordinates)
        : ViewComponent(state, coordinates) {}

    void update(uint32_t now) override;
    /**
     * Render the component.
     */
    void render(Display& display) override;

   private:
    void renderHidden(Display& display) const override;
    /**
     * Render measurements.
     */
    void renderMeasurements(Display& display) const;

    /**
     * Render measurement status icons.
     */
    void renderMeasurementStatusIcons(Display& display) const;
};

#endif  // MEASUREMENTSLINECOMPONENT_H