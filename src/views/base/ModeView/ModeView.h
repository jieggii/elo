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

#include "Settings.h"

#include "View.h"
#include "ViewNavigator.h"

#include "components/MeasurementsLineComponent/MeasurementsLineComponent.h"
#include "components/MeasurementsLineComponent/MeasurementsLineComponentState.h"
#include "components/StatusLineComponent/StatusLineComponent.h"
#include "components/StatusLineComponent/StatusLineComponentState.h"
#include "components/FlashNotificationComponent/FlashNotificationComponent.h"

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
     * ModeView constructor.
     * @param hardware hardware dependencies of the mode view.
     * @param viewNavigator view navigator used to navigate to another view.
     * @param nextViewID ID of the view to switch to.
     * @param clockTime the initial clock time to display in the status line.
     * @param measurementsLineComponentState measurements line state.
     * @param envEvalSettings environment evaluation settings.
     */
    ModeView(Hardware hardware, ViewNavigator& viewNavigator, uint8_t nextViewID, ClockTime clockTime,
             MeasurementsLineComponentState& measurementsLineComponentState,
             const settings::EnvironmentEvaluation& envEvalSettings);

    /**
     * Initializes the view.
     * @param now
     * @param display pointer to the display.
     */
    void setup(uint32_t now, display::Display& display) override;

    /**
     * Handles user inputs.
     */
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
    void render(display::Display& display) override;

    void reset(uint32_t now) override;

    ~ModeView() override = default;  // TODO: check if it is necessary to define destructor

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
     * View components.
     */
    Components components;

    /**
     * Returns components of the view.
     */
    // Components& getComponents();

    /**
     * Displays a toast message.
     * @param now current time.
     * @param text toast message text.
     * @param duration duration of the toast message in milliseconds.
     */
    void displayFlashNotification(uint32_t now, const char* text, uint32_t duration);

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
    static void cacheModeIndicatorIcons(display::Display& display, const Icon* icon1, const Icon* icon2);

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
     * Environment evaluation settings.
     */
    const settings::EnvironmentEvaluation& envEvalSettings;

    /**
     * Caches measurement status icons.
     * @param display reference to display.
     */
    static void cacheMeasurementStatusIcons(display::Display& display);
};

#endif  // MODEVIEW_H
