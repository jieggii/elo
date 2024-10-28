//
// Created by jieggii on 10/26/24.
//

#ifndef FLASHNOTIFICATIONCOMPONENTSTATE_H
#define FLASHNOTIFICATIONCOMPONENTSTATE_H

#include "Display.h"
#include "Timer.h"
#include "ViewComponentState.h"

class RenderBuffers {
    /**
     * Max length of a text can be displayed.
     * Is equal to the number of characters that can be displayed on the screen minus 3
     * (3 chars are reserved to display notification display time left).
     */
    static constexpr uint8_t maxTextLen = DisplayDimensions::cols * DisplayDimensions::rows - 3;

    /**
     * Length of the buffer for one line.
     */
    static constexpr uint8_t bufferLen = DisplayDimensions::cols;

    /**
     * Number of characters reserved to display seconds left.
     */
    static constexpr uint8_t secondsLeftLen = 3;

   public:
    RenderBuffers() = default;

    /**
     * Format the text to be displayed.
     * @param text text to be displayed.
     */
    void setText(const char *text) {
        char textBuffer[maxTextLen + 1];
        makeTextBuffer(text, textBuffer);

        // fill top buffer:
        for (uint8_t i = 0; i < bufferLen; i++) {
            this->topRenderBuffer[i] = textBuffer[i];
        }

        // fill bottom buffer:
        for (uint8_t i = 0; i < bufferLen - secondsLeftLen; i++) {
            this->bottomRenderBuffer[i] = textBuffer[bufferLen + i];
        }
    }

    void setSecondsLeft(const uint8_t secondsLeft) {
        this->bottomRenderBuffer[bufferLen - secondsLeftLen] = '(';
        this->bottomRenderBuffer[bufferLen - secondsLeftLen + 1] = static_cast<char>('0' + secondsLeft % 10);
        this->bottomRenderBuffer[bufferLen - secondsLeftLen + 2] = ')';
    }

    [[nodiscard]] const char *getTopRenderBuffer() const { return this->topRenderBuffer; }
    [[nodiscard]] const char *getBottomRenderBuffer() const { return this->bottomRenderBuffer; }

   private:
    /**
     * Buffer for the top line of the display.
     * (Part of the text to be displayed).
     */
    char topRenderBuffer[bufferLen] = {};

    /**
     * Buffer for the bottom line of the display.
     * (Part of the text and seconds left to be displayed).
     */
    char bottomRenderBuffer[bufferLen] = {};

    /**
     * Fill the text buffer with the text.
     * Example: makeTextBuffer("test string", buffer, 20) -> buffer = "test string         \0"
     */
    static void makeTextBuffer(const char *text, char *dest) {
        const uint8_t textLen = strlen(text);

        // fill the textBuffer with the text:
        for (size_t i = 0; i < maxTextLen; i++) {
            if (i == textLen) {
                // if the text is shorter than the buffer, break the loop
                break;
            }
            dest[i] = text[i];
        }

        // fill the text buffer with spaces if the text is shorter than the buffer:
        for (size_t i = textLen; i < maxTextLen; i++) {
            dest[i] = ' ';
        }

        // ensure the text buffer is null-terminated:
        dest[maxTextLen] = '\0';
    }
};

class FlashNotificationComponentState final : public ViewComponentState {
   public:
    /**
     * Set notification text.
     * @param text notification text.
     */
    void setText(const char *text) { this->renderBuffers.setText(text); }

    /**
     * Returns the top render buffer.
     */
    [[nodiscard]] const char *getTopRenderBuffer() const { return this->renderBuffers.getTopRenderBuffer(); }

    /**
     * Returns the bottom render buffer.
     */
    [[nodiscard]] const char *getBottomRenderBuffer() const { return this->renderBuffers.getBottomRenderBuffer(); }

    /**
     * Set the number of seconds left to display the notification.
     */
    void setSecondsLeft(const uint8_t secondsLeft) { this->renderBuffers.setSecondsLeft(secondsLeft); }

    Timer &getTimer() { return this->timer; }

   private:
    /**
     * Render buffers for the notification text.
     */
    RenderBuffers renderBuffers;

    /**
     * Notification timer used to display the notification for a certain duration.
     */
    Timer timer = Timer();
};

#endif  // FLASHNOTIFICATIONCOMPONENTSTATE_H
