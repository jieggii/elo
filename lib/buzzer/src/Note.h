//
// Created by jieggii on 10/27/24.
//

#ifndef NOTE_H
#define NOTE_H

#include <cstdint>

/**
 * Type of the frequency of the note.
 * Does not need to be precise and should not exceed 2**16 - 1 Hz, so uint16_t is enough.
 */
using noteFrequencyType = uint16_t;

/**
 * Type of the duration of the note in milliseconds.
 * Should not exceed 65 seconds, so uint16_t is enough.
 */
using noteDurationType = uint16_t;

/**
 * Note is a struct that represents a note that can be played by the buzzer.
 */
struct Note {
    /**
     * Frequency of the note in Hz.
     */
    noteFrequencyType frequency;

    /**
     * Duration of the note in milliseconds.
     */
    noteDurationType duration;

    /**
     * Duration of a pause after the note in milliseconds.
     * TODO: consider setting 0 as default value.
     */
    noteDurationType pauseDuration;
};

#endif  // NOTE_H
