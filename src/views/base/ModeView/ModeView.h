//
// Created by jieggii on 9/20/24.
//

#ifndef MODEVIEW_H
#define MODEVIEW_H

#include <cstdint>

#include "View.h"
#include "EnvSensor.h"
#include "Display.h"
#include "ViewNavigator.h"
#include "components/MeasurementsLineComponent.h"
#include "components/StatusLineComponent.h"

#define MODE_VIEW_MEASUREMENTS_UPDATE_INTERVAL 1000          // interval between measurements updates
#define MODE_VIEW_MEASUREMENTS_DISPLAY_DURATION 6000         // duration of displaying measurements
#define MODE_VIEW_MEASUREMENTS_STATUS_DISPLAY_DURATION 2000  // duration of displaying measurement statuses

/**
 * Base class for all mode views.
 * Has status line and measurements line; is capable of switching to another view.
 */
class ModeView : public View {
   public:
    struct MeasurementStatusIconIDs {  // icons reflecting the status of measurements
        uint8_t optimal;               // id of the icon representing optimal measurement status
        uint8_t acceptable;            // id of the icon representing acceptable measurement status
        uint8_t bad;                   // id of the icon representing bad measurement status
    };

    struct Hardware {
        EnvSensor* envSensor;
    };

    ModeView(const Hardware hardware, ViewNavigator* viewNavigator,
             const MeasurementStatusIconIDs measurementStatusIconIDs, const uint8_t modeIndicatorIcon1ID,
             const uint8_t modeIndicatorIcon2ID)
        : View(),
          hardware(hardware),
          viewNavigator(viewNavigator),
          measurementStatusIconIDs(measurementStatusIconIDs),
          measurementsTimer(Timer(MODE_VIEW_MEASUREMENTS_UPDATE_INTERVAL)),
          components({.statusLine = StatusLineComponent({0, 0}, modeIndicatorIcon1ID, modeIndicatorIcon2ID,
                                                        measurementStatusIconIDs.optimal),
                      .measurementsLine = MeasurementsLineComponent({0, 1}, MODE_VIEW_MEASUREMENTS_DISPLAY_DURATION,
                                                                    MODE_VIEW_MEASUREMENTS_STATUS_DISPLAY_DURATION,
                                                                    measurementStatusIconIDs.optimal)}) {}

    void setup(Display* display) override {
        const uint32_t now = millis();
        this->measurementsTimer.set(now);
    };

    /**
     * Main view loop.
     * It is responsible for reading environment measurements, assessing them, and displaying the results.
     */
    void loop() override {
        if (const uint32_t now = millis(); this->measurementsTimer.isExpired(now)) {
            this->measurementsTimer.set(now);
            const EnvSensorMeasurements measurements = this->hardware.envSensor->read();
            this->components.measurementsLine.setMeasurements(measurements);

            // TODO: assess measurements and choose suitable icons:
            const MeasurementsLineComponent::MeasurementStatusIconIDs measurementStatusIconIDs = {
                .temperature = this->measurementStatusIconIDs.optimal,
                .humidity = this->measurementStatusIconIDs.acceptable,
                .co2 = this->measurementStatusIconIDs.bad};
            this->components.measurementsLine.setMeasurementStatusIconIDs(measurementStatusIconIDs);
        }
    };

    /**
     * Renders status line and measurements line.
     * @param display - pointer to the display.
     */
    void render(Display* display) override {
        this->components.statusLine.render(display);
        this->components.measurementsLine.render(display);
    }

    void reset() override = 0;

    ~ModeView() override = default;

   protected:
    /**
     * Sets the clock time displayed in the status line.
     * @param time - clock time to set.
     */
    void setStatusLineClockTime(const ClockTime time) { this->components.statusLine.setClockTime(time); }

   private:
    Hardware hardware;                                  // hardware dependencies
    ViewNavigator* viewNavigator;                       // view navigator used to navigate to another view
    MeasurementStatusIconIDs measurementStatusIconIDs;  // icons reflecting the status of measurements

    Timer measurementsTimer;  // timer used to track measurements update interval
    struct Components {
        StatusLineComponent statusLine;
        MeasurementsLineComponent measurementsLine;
    } components;  // view components
};

#endif  // MODEVIEW_H
