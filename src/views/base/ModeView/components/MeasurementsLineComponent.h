#ifndef MEASUREMENTSLINECOMPONENT_H
#define MEASUREMENTSLINECOMPONENT_H

#include <cstdint>
#include "LCD1602.h"
#include "ViewComponent.h"
#include "Timer.h"
#include "EnvSensor.h"

class RenderBuffer {
   public:
    RenderBuffer() = default;

    /**
     * Format the buffer with the given measurements.
     * If no measurements are provided, the buffer will be formatted as a template with no measurements displayed.
     */
    void format(const EnvSensorMeasurements* measurements = nullptr) {
        // display temperature if available:
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

        // display humidity if available:
        if (measurements) {
            buffer[5] = static_cast<char>('0' + measurements->humidity / 10);
            buffer[6] = static_cast<char>('0' + measurements->humidity % 10);
        } else {
            buffer[5] = ' ';
            buffer[6] = ' ';
        }
        buffer[7] = '%';

        buffer[8] = ' ';

        // display CO2 if available:
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

    [[nodiscard]] const char* getBuffer() const { return this->buffer; }

   private:
    static constexpr char DEGREE_SYMBOL = static_cast<char>(223);

    char buffer[DISPLAY_COLS + 1] = {};
};

/**
 * MeasurementsLineComponent line displaying environmental measurements and their statuses.
 */
class MeasurementsLineComponent final : public ViewComponent {
   public:
    struct MeasurementStatusIconIDs {
        uint8_t temperature;
        uint8_t humidity;
        uint8_t co2;
    };

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
    void setMeasurements(const EnvSensorMeasurements measurements) { this->measurements = measurements; }

    /**
     * Set icon IDs representing statuses of each measurement.
     */
    void setMeasurementStatusIconIDs(const MeasurementStatusIconIDs iconIDs) {
        this->measurementStatusIconIDs = iconIDs;
    }

    void renderMeasurements(LCD1602* display) const {
        RenderBuffer renderBuffer;
        renderBuffer.format(&this->measurements);

        display->displayText(renderBuffer.getBuffer(), this->coordinates);
    }

    void renderStatusIcons(LCD1602* display) const {
        RenderBuffer renderBuffer;
        renderBuffer.format();

        display->displayText(renderBuffer.getBuffer(), {0, 1});

        display->displayIcon(this->measurementStatusIconIDs.temperature, {1, 1});
        display->displayIcon(this->measurementStatusIconIDs.humidity, {6, 1});
        display->displayIcon(this->measurementStatusIconIDs.co2, {12, 1});
    }

    void render(LCD1602* display) override {
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

   private:
    Timer displayMeasurementsTimer;
    Timer displayStatusesTimer;

    MeasurementStatusIconIDs measurementStatusIconIDs;  // icon IDs representing statuses of each measurement

    enum class State {
        DISPLAY_MEASUREMENTS,               // actual measurements are displayed
        DISPLAY_STATUS_ICONS,               // icons representing measurement statuses are displayed
    } state = State::DISPLAY_MEASUREMENTS;  // current state of the component

    EnvSensorMeasurements measurements = {.temperature = 0, .humidity = 0, .co2 = 0};  // current measurements
};

#endif  // MEASUREMENTSLINECOMPONENT_H