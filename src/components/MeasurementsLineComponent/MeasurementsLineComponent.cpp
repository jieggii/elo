//
// Created by jieggii on 10/4/24.
//

#include "debug_print.h"
#include "MeasurementsLineComponent.h"
#include "MeasurementsLineComponentState.h"

/**
 * Buffer for rendering measurements line on the display.
 */
class RenderBuffer {
   public:
    RenderBuffer() = default;

    /**
     * Format the buffer with the given measurements.
     * If no measurements are provided, the buffer will be formatted as a template with no measurements displayed.
     * I.e formats buffer as "99°C 99% 9999ppm" if measurements provided, otherwise as "  °C  %    ppm".
     * TODO: rename this method to something more descriptive.
     */
    void format(const MeasurementsLineComponentState::Measurements* measurements = nullptr) {
        // display temperature if measurements provided:
        if (measurements) {
            buffer[0] = static_cast<char>('0' + measurements->temperature / 10);
            buffer[1] = static_cast<char>('0' + measurements->temperature % 10);
        } else {
            buffer[0] = ' ';
            buffer[1] = ' ';
        }
        buffer[2] = DEGREE_SYMBOL;
        buffer[3] = 'C';

        buffer[4] = ' ';

        // display humidity if measurements provided:
        if (measurements) {
            buffer[5] = static_cast<char>('0' + measurements->humidity / 10);
            buffer[6] = static_cast<char>('0' + measurements->humidity % 10);
        } else {
            buffer[5] = ' ';
            buffer[6] = ' ';
        }
        buffer[7] = '%';

        buffer[8] = ' ';

        // display CO2 if measurements provided:
        if (measurements) {
            buffer[9] = static_cast<char>('0' + measurements->co2 / 1000);
            buffer[10] = static_cast<char>('0' + measurements->co2 % 1000 / 100);
            buffer[11] = static_cast<char>('0' + measurements->co2 % 100 / 10);
            buffer[12] = static_cast<char>('0' + measurements->co2 % 10);
        } else {
            buffer[9] = ' ';
            buffer[10] = ' ';
            buffer[11] = ' ';
            buffer[12] = ' ';
        }

        buffer[13] = 'p';
        buffer[14] = 'p';
        buffer[15] = 'm';
        buffer[16] = '\0';  // Null-terminate the string
    }

    /**
     * Get the buffer.
     */
    [[nodiscard]] const char* getBuffer() const { return this->buffer; }

   private:
    // TODO: add methods for formatting individual measurements (temperature, humidity, co2)

    static constexpr char DEGREE_SYMBOL = static_cast<char>(223);  // degree symbol ('°')

    char buffer[DisplayDimensions::cols + 1] = {};  // the underlying buffer for rendering
};

void MeasurementsLineComponent::update(const uint32_t now) {
    MeasurementsLineComponentState& componentState = this->getState();
    // TODO: improve code readability here, because it's hard to distinguish between "state" and "state".

    switch (componentState.getState()) {
        case MeasurementsLineComponentState::State::DISPLAYING_MEASUREMENTS:
            if (componentState.isDisplayMeasurementStatusIcons()) {  // if statuses should be displayed
                if (const Timer& displayMeasurementsTimer = componentState.getDisplayMeasurementsTimer();
                    displayMeasurementsTimer.isExpired(now)) {  // if measurements display time expired

                    // update state to display statuses:
                    componentState.setState(MeasurementsLineComponentState::State::DISPLAYING_STATUSES);

                    // set display statuses timer:
                    componentState.getDisplayStatusesTimer().set(now);
                }
            }
            break;

        case MeasurementsLineComponentState::State::DISPLAYING_STATUSES:
            if (const Timer& displayStatusesTimer = componentState.getDisplayStatusesTimer();
                displayStatusesTimer.isExpired(now)) {  // if statuses display time expired

                // update state to display measurements:
                componentState.setState(MeasurementsLineComponentState::State::DISPLAYING_MEASUREMENTS);

                // set display measurements timer:
                componentState.getDisplayMeasurementsTimer().set(now);
            }
            break;
    }
}

void MeasurementsLineComponent::render(Display& display) {
    const auto& componentState = this->getState();
    // TODO: improve code readability here, because it's hard to distinguish between "state" and "state".

    switch (componentState.getState()) {
        case MeasurementsLineComponentState::State::DISPLAYING_MEASUREMENTS:
            this->renderMeasurements(display);
            break;

        case MeasurementsLineComponentState::State::DISPLAYING_STATUSES:
            this->renderMeasurementStatusIcons(display);
            break;
    }
}

void MeasurementsLineComponent::renderMeasurements(Display& display) const {
    const auto measurements = this->getState().getMeasurements();

    RenderBuffer renderBuffer;
    renderBuffer.format(&measurements);
    display.displayText(renderBuffer.getBuffer(), this->coordinates);
}

void MeasurementsLineComponent::renderMeasurementStatusIcons(Display& display) const {
    RenderBuffer renderBuffer;
    renderBuffer.format();
    display.displayText(renderBuffer.getBuffer(), {0, this->coordinates.row});

    const auto [temperature, humidity, co2] = this->getState().getMeasurementStatusIconIDs();
    display.displayIcon(temperature, {1, this->coordinates.row});
    display.displayIcon(humidity, {6, this->coordinates.row});
    display.displayIcon(co2, {12, this->coordinates.row});
}
