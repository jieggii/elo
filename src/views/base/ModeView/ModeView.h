//
// Created by jieggii on 9/20/24.
//

#ifndef MODEVIEW_H
#define MODEVIEW_H

#include <cstdint>

#include "View.h"
#include "EnvSensor.h"
#include "Button.h"
#include "Display.h"
#include "ViewNavigator.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponent.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponentState.h"
#include "components/StatusLineComponent/StatusLineComponent.h"
#include "components/StatusLineComponent/StatusLineComponentState.h"

// TODO: shall I move those constants to the .cpp file?

namespace ModeViewIconIDs {
    // id of the first mode indicator icon.
    constexpr uint8_t indicator1 = 1;

    // id of the second mode indicator icon.
    constexpr uint8_t indicator2 = 2;

    // id of the icon representing optimal measurement status.
    constexpr uint8_t measurementStatusOptimal = 3;

    // id of the icon representing acceptable measurement status.
    constexpr uint8_t measurementStatusAcceptable = 4;

    // id of the icon representing bad measurement status.
    constexpr uint8_t measurementStatusBad = 5;

    // id of the icon representing placeholder for measurements.
    constexpr uint8_t measurementsPlaceholder = 6;

}  // namespace ModeViewIconIDs

namespace ModeViewSettings {
    // interval between measurements updates in milliseconds.
    constexpr uint16_t measurementsUpdateInterval = 1000;

    // duration of displaying measurements in milliseconds.
    constexpr uint16_t measurementsDisplayDuration = 4000;

    // duration of displaying measurement statuses in milliseconds.
    constexpr uint16_t measurementsStatusDisplayDuration = 1000;

}  // namespace ModeViewSettings

/**
 * Base class for all mode views.
 * Has status line and measurements line; is capable of switching to another view.
 */
class ModeView : public View {
   public:
    /**
     * Hardware dependencies of the mode view.
     * Contains an environment sensor.
     */
    struct Hardware {
        EnvSensor* envSensor;
        Button* selectButton;
    };
    /**
     * Constructor.
     * @param hardware hardware dependencies of the mode view.
     * @param viewNavigator view navigator used to navigate to another view.
     * @param nextViewID ID of the view to switch to.
     * @param clockTime the initial clock time to display in the status line.
     * @param measurementsLineComponentState measurements line state.
     * TODO: move constructor implementation to the .cpp file
     */
    ModeView(const Hardware hardware, ViewNavigator* viewNavigator, const uint8_t nextViewID, const ClockTime clockTime,
             MeasurementsLineComponentState* measurementsLineComponentState)
        : View(),
          hardware(hardware),
          viewNavigator(viewNavigator),
          nextViewID(nextViewID),
          measurementsTimer(ModeViewSettings::measurementsDisplayDuration),
          components({.statusLine = StatusLineComponent(
                          StatusLineComponentState(ModeViewIconIDs::indicator1, ModeViewIconIDs::indicator2, clockTime),
                          {0, 0}),
                      .measurementsLine = MeasurementsLineComponent(measurementsLineComponentState, {0, 1})}) {}

    /**
     * Initializes the view.
     * @param display pointer to the display.
     */
    void setup(Display* display) override;

    void handleInputs() override;

    /**
     * Main view loop.
     * It is responsible for reading environment measurements, assessing them, and displaying the results.
     */
    void loop() override;

    /**
     * Renders status line and measurements line.
     * @param display - pointer to the display.
     */
    void render(Display* display) override;

    void reset() override;

    ~ModeView() override = default;

   protected:
    /**
     * Sets the clock time displayed in the status line.
     * @param time clock time to set.
     */
    void setStatusLineClockTime(ClockTime time) const;

    /**
     * Navigates to the next view.
     */
    void navigateToNextView() const;

    /**
     * Caches mode indicator icons.
     * @param display pointer to the display.
     * @param icon1
     * @param icon2
     */
    static void cacheModeIndicatorIcons(Display* display, const Icon* icon1, const Icon* icon2);

   private:
    /**
     * Hardware dependencies of the mode view.
     * Contains an environment sensor.
     */
    Hardware hardware;

    /**
     * View navigator used to navigate to another view.
     */
    ViewNavigator* viewNavigator;

    /**
     * ID of the view to switch to.
     */
    const uint8_t nextViewID;

    /**
     * Timer used to track measurements update interval.
     */
    Timer measurementsTimer;

    /**
     * View components.
     */
    struct Components {
        StatusLineComponent statusLine;
        MeasurementsLineComponent measurementsLine;
    } components;

    // bool measurementsAvailable = false;

    void updateMeasurementsLineState(const EnvSensorMeasurements& measurements) const;
    void updateStatusLineState(const EnvSensorMeasurements& measurements) const;

    /**
     * Caches measurement status icons.
     * @param display pointer to the display.
     */
    static void cacheMeasurementStatusIcons(Display* display);
};

#endif  // MODEVIEW_H
