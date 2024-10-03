//
// Created by jieggii on 9/20/24.
//

#ifndef MODEVIEW_H
#define MODEVIEW_H

#include <cstdint>

#include "View.h"
#include "EnvSensor.h"
#include "LCD1602.h"
#include "ViewNavigator.h"
#include "components/MeasurementsLineComponent.h"
#include "components/StatusLineComponent.h"

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
             const uint8_t modeIndicatorIcon2ID, const ClockTime clockTime, const uint32_t measurementsUpdateInterval)
        : View(),
          hardware(hardware),
          viewNavigator(viewNavigator),
          measurementStatusIconIDs(measurementStatusIconIDs),
          measurementsTimer(Timer(measurementsUpdateInterval)),
          components(
              {.statusLine = StatusLineComponent({0, 0}, modeIndicatorIcon1ID, modeIndicatorIcon2ID, clockTime,
                                                 measurementStatusIconIDs.optimal),
               .measurementsLine = MeasurementsLineComponent({0, 1}, 3000, 1000, measurementStatusIconIDs.optimal)}) {}

    void setup(LCD1602* display) override {
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
    void render(LCD1602* display) override {
        this->components.statusLine.render(display);
        this->components.measurementsLine.render(display);
    };

    void reset() override = 0;

    ~ModeView() override = default;

   protected:
    /**
     * Navigates to the specified view.
     * @param viewID - ID of the view to navigate to.
     */
    // void navigateTo(const uint8_t viewID) const { this->viewNavigator->navigateTo(viewID); }

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
