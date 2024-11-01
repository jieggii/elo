#ifndef MEASUREMENTSLINECOMPONENT_H
#define MEASUREMENTSLINECOMPONENT_H

#include "Display.h"
#include "ViewComponent.h"
#include "MeasurementsLineComponentState.h"

/**
 * Buffer for rendering measurements line on the display.
 * TODO: move to a separate file.
 */
class RenderBuffer {
    static constexpr uint8_t temperaturePlaceholderLen = 2;
    static constexpr uint8_t humidityPlaceholderLen = 2;
    static constexpr uint8_t co2PlaceholderLen = 4;

   public:
    RenderBuffer() {
        static constexpr char degreeSymbol = static_cast<char>(223);  // degree symbol (°)

        buffer[0] = ' ';
        buffer[1] = ' ';
        buffer[2] = degreeSymbol;
        buffer[3] = 'C';

        buffer[4] = ' ';

        buffer[5] = ' ';
        buffer[6] = ' ';
        buffer[7] = '%';

        buffer[8] = ' ';

        buffer[9] = ' ';
        buffer[10] = ' ';
        buffer[11] = ' ';
        buffer[12] = ' ';

        buffer[13] = 'p';
        buffer[14] = 'p';
        buffer[15] = 'm';

        buffer[16] = '\0';
    }

    void removeMeasurements() {
        char temperaturePlaceholderBuffer[temperaturePlaceholderLen];
        char humidityPlaceholderBuffer[humidityPlaceholderLen];
        char co2PlaceholderBuffer[co2PlaceholderLen];

        temperaturePlaceholderBuffer[0] = ' ';
        temperaturePlaceholderBuffer[1] = ' ';

        humidityPlaceholderBuffer[0] = ' ';
        humidityPlaceholderBuffer[1] = ' ';

        co2PlaceholderBuffer[0] = ' ';
        co2PlaceholderBuffer[1] = ' ';
        co2PlaceholderBuffer[2] = ' ';
        co2PlaceholderBuffer[3] = ' ';

        this->setMeasurementPlaceholders(temperaturePlaceholderBuffer, humidityPlaceholderBuffer, co2PlaceholderBuffer);

        this->formattedWithMeasurements = false;
    }

    /**
     * Format the buffer with temperature, humidity, and co2 measurements.
     */
    void formatMeasurements(const uint8_t temperature, const uint8_t humidity, const uint16_t co2) {
        char temperaturePlaceholderBuffer[temperaturePlaceholderLen];
        char humidityPlaceholderBuffer[humidityPlaceholderLen];
        char co2PlaceholderBuffer[co2PlaceholderLen];

        temperaturePlaceholderBuffer[0] = static_cast<char>('0' + temperature / 10);
        temperaturePlaceholderBuffer[1] = static_cast<char>('0' + temperature % 10);

        humidityPlaceholderBuffer[0] = static_cast<char>('0' + humidity / 10);
        humidityPlaceholderBuffer[1] = static_cast<char>('0' + humidity % 10);

        co2PlaceholderBuffer[0] = static_cast<char>('0' + co2 / 1000);
        co2PlaceholderBuffer[1] = static_cast<char>('0' + co2 % 1000 / 100);
        co2PlaceholderBuffer[2] = static_cast<char>('0' + co2 % 100 / 10);
        co2PlaceholderBuffer[3] = static_cast<char>('0' + co2 % 10);

        this->setMeasurementPlaceholders(temperaturePlaceholderBuffer, humidityPlaceholderBuffer, co2PlaceholderBuffer);

        this->formattedWithMeasurements = true;
    }

    [[nodiscard]] bool isFormattedWithMeasurements() const { return this->formattedWithMeasurements; }

    /**
     * Get the buffer.
     */
    [[nodiscard]] const char* getBuffer() const { return this->buffer; }

   private:
    /**
     * The underlying buffer.
     */
    char buffer[display::dimensions::cols + 1] = {};

    /**
     * Flag indicating whether the buffer is formatted with measurements.
     */
    bool formattedWithMeasurements = false;

    /**
     * Set measurement placeholders.
     */
    void setMeasurementPlaceholders(const char temperature[temperaturePlaceholderLen],
                                    const char humidity[humidityPlaceholderLen], const char co2[co2PlaceholderLen]) {
        buffer[0] = temperature[0];
        buffer[1] = temperature[1];

        buffer[5] = humidity[0];
        buffer[6] = humidity[1];

        buffer[9] = co2[0];
        buffer[10] = co2[1];
        buffer[11] = co2[2];
        buffer[12] = co2[3];
    }
};

/**
 * MeasurementsLineComponent line displaying environmental measurements and their statuses.
 */
class MeasurementsLineComponent final : public ViewComponent<MeasurementsLineComponentState&> {
   public:
    // TODO: move constructor implementation to cpp file.
    MeasurementsLineComponent(MeasurementsLineComponentState& state, const display::Coordinates coordinates)
        : ViewComponent(state, coordinates) {}

    void update(uint32_t now) override;

    /**
     * Render the component.
     */
    void render(display::Display& display) override;

   private:
    RenderBuffer renderBuffer = RenderBuffer();

    void renderHidden(display::Display& display) const override;
};

#endif  // MEASUREMENTSLINECOMPONENT_H