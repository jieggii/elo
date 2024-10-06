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

}  // namespace ModeViewIconIDs

namespace ModeViewSettings {
    // interval between measurements updates in milliseconds.
    constexpr uint16_t measurementsUpdateInterval = 1000;

    // duration of displaying measurements in milliseconds.
    constexpr uint16_t measurementsDisplayDuration = 1000;

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
    };

    // TODO: move constructor implementation to the .cpp file
    ModeView(const Hardware hardware, ViewNavigator* viewNavigator)
        : View(),
          hardware(hardware),
          viewNavigator(viewNavigator),
          measurementsTimer(ModeViewSettings::measurementsDisplayDuration),
          components(
              {.statusLine = StatusLineComponent({0, 0}, ModeViewIconIDs::indicator1, ModeViewIconIDs::indicator2,
                                                 ModeViewIconIDs::measurementStatusOptimal),
               .measurementsLine = MeasurementsLineComponent({0, 1}, ModeViewSettings::measurementsDisplayDuration,
                                                             ModeViewSettings::measurementsStatusDisplayDuration,
                                                             ModeViewIconIDs::measurementStatusOptimal)}) {}

    void setup(Display* display) override = 0;

    /**
     * Initializes the view.
     * @param display pointer to the display.
     * @param indicatorIcon1 pointer to the first mode indicator icon.
     * @param indicatorIcon2 pointer to the second mode indicator icon.
     */
    void setup(Display* display, const Icon* indicatorIcon1, const Icon* indicatorIcon2);

    /**
     * Main view loop.
     * It is responsible for reading environment measurements, assessing them, and displaying the results.
     */
    void loop() override = 0;

    /**
     * Renders status line and measurements line.
     * @param display - pointer to the display.
     */
    void render(Display* display) override = 0;

    void reset() override = 0;

    ~ModeView() override = default;

   protected:
    /**
     * Sets the clock time displayed in the status line.
     * @param time clock time to set.
     */
    void setStatusLineClockTime(ClockTime time);

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

    /**
     * Caches mode indicator icons.
     * @param display pointer to the display.
     * @param icon1
     * @param icon2
     */
    static void cacheModeIndicatorIcons(Display* display, const Icon* icon1, const Icon* icon2);

    /**
     * Caches measurement status icons.
     * @param display pointer to the display.
     */
    static void cacheMeasurementStatusIcons(Display* display);
};

#endif  // MODEVIEW_H
