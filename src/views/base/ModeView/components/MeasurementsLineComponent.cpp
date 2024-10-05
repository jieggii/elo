//
// Created by jieggii on 10/4/24.
//

#include "MeasurementsLineComponent.h"

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
    void format(const EnvSensorMeasurements* measurements = nullptr) {
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
    static constexpr char DEGREE_SYMBOL = static_cast<char>(223);  // degree symbol ('°')

    char buffer[DISPLAY_COLS + 1] = {};  // the actual buffer for rendering
};

void MeasurementsLineComponent::setMeasurements(const EnvSensorMeasurements measurements) {
    this->measurements = measurements;
}

void MeasurementsLineComponent::setMeasurementStatusIconIDs(const MeasurementStatusIconIDs iconIDs) {
    this->measurementStatusIconIDs = iconIDs;
}

void MeasurementsLineComponent::render(Display* display) {
    const uint32_t now = millis();

    switch (this->state) {
        case State::DISPLAY_MEASUREMENTS:
            this->renderMeasurements(display);
            if (this->displayMeasurementsTimer.isExpired(now)) {
                this->state = State::DISPLAY_STATUS_ICONS;
                this->displayStatusesTimer.set(now);
            }
            break;

        case State::DISPLAY_STATUS_ICONS:
            this->renderStatusIcons(display);

            if (this->displayStatusesTimer.isExpired(now)) {
                this->state = State::DISPLAY_MEASUREMENTS;
                this->displayMeasurementsTimer.set(now);
            }
            break;
    }
}

void MeasurementsLineComponent::renderMeasurements(Display* display) const {
    RenderBuffer renderBuffer;
    renderBuffer.format(&this->measurements);

    display->displayText(renderBuffer.getBuffer(), this->coordinates);
}

void MeasurementsLineComponent::renderStatusIcons(Display* display) const {
    RenderBuffer renderBuffer;
    renderBuffer.format();

    display->displayText(renderBuffer.getBuffer(), {0, 1});

    display->displayIcon(this->measurementStatusIconIDs.temperature, {1, 1});
    display->displayIcon(this->measurementStatusIconIDs.humidity, {6, 1});
    display->displayIcon(this->measurementStatusIconIDs.co2, {12, 1});
}