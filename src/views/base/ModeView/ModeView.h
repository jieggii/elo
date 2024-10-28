//
// Created by jieggii on 9/20/24.
//

#ifndef MODEVIEW_H
#define MODEVIEW_H

#include <cstdint>

#include "EnvSensor.h"
#include "Button.h"
#include "Display.h"
#include "Buzzer.h"

#include "View.h"
#include "ViewNavigator.h"

#include "components/MeasurementsLineComponent/MeasurementsLineComponent.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponentState.h"
#include "components/StatusLineComponent/StatusLineComponent.h"
#include "components/StatusLineComponent/StatusLineComponentState.h"
#include "components/FlashNotificationComponent/FlashNotificationComponent.h"

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
    /**
     * Interval between measurements updates in milliseconds.
     * TODO: check with specs, it seems that value should be not less than 5000.
     */
    constexpr uint16_t measurementsUpdateInterval = 10000;
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
        EnvSensor& envSensor;
        Button& selectButton;
        Buzzer& buzzer;
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
    ModeView(const Hardware hardware, ViewNavigator& viewNavigator, const uint8_t nextViewID, const ClockTime clockTime,
             MeasurementsLineComponentState& measurementsLineComponentState)
        : View(),
          hardware(hardware),
          viewNavigator(viewNavigator),
          nextViewID(nextViewID),
          measurementsTimer(ModeViewSettings::measurementsUpdateInterval),
          componentStates({
              .statusLine =
                  StatusLineComponentState(ModeViewIconIDs::indicator1, ModeViewIconIDs::indicator2, clockTime),
              .flashNotification = FlashNotificationComponentState(),
          }),
          components(
              {.statusLine = StatusLineComponent(this->componentStates.statusLine, {0, 0}),
               .measurementsLine = MeasurementsLineComponent(measurementsLineComponentState, {0, 1}),
               .flashNotification = FlashNotificationComponent(this->componentStates.flashNotification, {0, 0})}) {}

    /**
     * Initializes the view.
     * @param now
     * @param display pointer to the display.
     */
    void setup(uint32_t now, Display& display) override;

    void handleInputs(uint32_t now) override;

    /**
     * Main view loop.
     * It is responsible for reading environment measurements, assessing them, and displaying the results.
     */
    void update(uint32_t now) override;

    /**
     * Renders status line and measurements line.
     * @param display - pointer to the display.
     */
    void render(Display& display) override;

    void reset(uint32_t now) override;

    ~ModeView() override = default;

   protected:
    struct Components {
        StatusLineComponent statusLine;
        MeasurementsLineComponent measurementsLine;
        FlashNotificationComponent flashNotification;
    };

    /**
     * Hardware dependencies of the mode view.
     * Contains an environment sensor.
     */
    Hardware hardware;

    /**
     * Returns components of the view.
     */
    Components& getComponents() { return this->components; }

    /**
     * Navigates to the given view.
     */
    void navigateTo(const uint8_t viewID) const { this->viewNavigator.navigateTo(viewID); }

    /**
     * Navigates to the next view.
     */
    void navigateToNextView() const;

    /**
     * Displays a toast message.
     * @param text toast message text.
     * @param duration duration of the toast message in milliseconds.
     */
    void displayFlashNotification(uint32_t now, const char* text, uint32_t duration);

    /**
     * Caches mode indicator icons.
     * @param display pointer to the display.
     * @param icon1
     * @param icon2
     */
    static void cacheModeIndicatorIcons(Display& display, const Icon* icon1, const Icon* icon2);

   private:
    /**
     * View navigator used to navigate to another view.
     */
    ViewNavigator& viewNavigator;

    /**
     * ID of the view to switch to.
     */
    const uint8_t nextViewID;

    /**
     * Timer used to track measurements update interval.
     */
    Timer measurementsTimer;

    /**
     * Timer used to display flash notifications.
     */
    // Timer flashNotificationTimer = Timer(0);

    /**
     * Flag indicating whether a flash notification is currently being displayed.
     */
    bool isDisplayingFlashNotification = false;

    /**
     * Flag indicating whether a flash notification has just stopped displaying.
     */
    bool justStoppedDisplayingFlashNotification = false;

    /**
     * States of the local components.
     */
    struct ComponentStates {
        StatusLineComponentState statusLine;
        FlashNotificationComponentState flashNotification;
    } componentStates;

    /**
     * View components.
     */
    Components components;

    void updateMeasurementsLineState(const EnvSensorMeasurements& measurements) const;
    void updateStatusLineState(const EnvSensorMeasurements& measurements) const;

    /**
     * Caches measurement status icons.
     * @param display pointer to the display.
     */
    static void cacheMeasurementStatusIcons(Display& display);
};

#endif  // MODEVIEW_H
