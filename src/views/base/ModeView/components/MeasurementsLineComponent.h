#ifndef MEASUREMENTSLINECOMPONENT_H
#define MEASUREMENTSLINECOMPONENT_H

#include <cstdint>
#include "LCD1602.h"
#include "ViewComponent.h"
#include "Timer.h"
#include "EnvSensor.h"

/**
 * MeasurementsLineComponent line displaying environmental measurements and their statuses.
 */
class MeasurementsLineComponent final : public ViewComponent {
   public:
    /**
     * Icon IDs representing statuses of each measurement.
     */
    struct MeasurementStatusIconIDs {
        uint8_t temperature;
        uint8_t humidity;
        uint8_t co2;
    };

    // TODO: move constructor to the cpp file.
    MeasurementsLineComponent(const DisplayCoordinates coordinates, const uint16_t displayMeasurementsDuration,
                              const uint16_t displayStatusesDuration, const uint8_t defaultMeasurementStatusIconID)
        : ViewComponent(coordinates),
          displayMeasurementsTimer(Timer(displayMeasurementsDuration)),
          displayStatusesTimer(Timer(displayStatusesDuration)),
          measurementStatusIconIDs({.temperature = defaultMeasurementStatusIconID,
                                    .humidity = defaultMeasurementStatusIconID,
                                    .co2 = defaultMeasurementStatusIconID}) {}

    /**
     * Set measurements to be displayed.
     */
    void setMeasurements(EnvSensorMeasurements measurements);

    /**
     * Set icon IDs representing statuses of each measurement.
     */
    void setMeasurementStatusIconIDs(MeasurementStatusIconIDs iconIDs);

    /**
     * Render the component.
     */
    void render(LCD1602* display) override;

   private:
    Timer displayMeasurementsTimer;  // timer controlling how long measurements are displayed
    Timer displayStatusesTimer;      // timer controlling how long measurement statuses are displayed

    MeasurementStatusIconIDs measurementStatusIconIDs;  // icon IDs representing statuses of each measurement

    enum class State {
        DISPLAY_MEASUREMENTS,               // actual measurements are displayed
        DISPLAY_STATUS_ICONS,               // icons representing measurement statuses are displayed
    } state = State::DISPLAY_MEASUREMENTS;  // current state of the component

    EnvSensorMeasurements measurements = {.temperature = 0, .humidity = 0, .co2 = 0};  // current measurements

    /**
     * Render measurements.
     */
    void renderMeasurements(LCD1602* display) const;

    /**
     * Render measurement status icons.
     */
    void renderStatusIcons(LCD1602* display) const;
};

#endif  // MEASUREMENTSLINECOMPONENT_H