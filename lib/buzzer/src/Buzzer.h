//
// Created by jieggii on 10/25/24.
//

#ifndef BUZZER_H
#define BUZZER_H

#include "Timer.h"
#include "cstdint"
#include "Arduino.h"

#include <debug_print.h>

using frequencyType = uint16_t;
using durationType = uint16_t;

struct Note {
    /**
     * Frequency of the note in Hz.
     */
    frequencyType frequency;

    /**
     * Duration of the note in milliseconds.
     */
    durationType duration;

    /**
     * Duration of a pause after the note in milliseconds.
     */
    durationType pauseDuration;
};

/**
 * NoteQueue is a queue of notes that can be played by the buzzer.
 * Maximum number of notes in the queue is determined by maxQueueSize member.
 */
class NoteQueue {
   public:
    NoteQueue() = default;

    /**
     * Get the first note from the queue and remove it.
     * Will return an empty note if the queue is empty.
     */
    Note get() {
        const Note note = this->queue[0];
        if (this->isEmpty()) {
            // return an empty note if the queue is empty
            return note;
        }

        // move all notes one position to the left:
        for (uint8_t i = 0; i < this->len; i++) {
            this->queue[i] = this->queue[i + 1];
        }

        this->len--;

        return note;
    }

    /**
     * Add a note to the queue.
     */
    void add(const Note note) {
        if (this->len == maxQueueSize) {
            // do not add element to the queue if it is full
            return;
        }

        this->queue[this->len] = note;
        this->len++;
    }

    [[nodiscard]] bool isEmpty() const { return this->len == 0; }

    // [[nodiscard]] bool isFull() const { return this->len == maxQueueSize; }

   private:
    static constexpr uint8_t maxQueueSize = 8;

    uint8_t len = 0;
    Note queue[maxQueueSize] = {};
};

class Buzzer {
   public:
    explicit Buzzer(const uint8_t pin) : pin(pin) {}

    void init() const { pinMode(this->pin, OUTPUT); }

    void serve(const uint32_t now) {
        if (!this->currentNoteTimer.isExpired(now)) {
            // do not serve if the current note is still playing
            return;
        }

        if (this->noteQueue.isEmpty()) {
            // do not serve if the note queue is empty
            return;
        }

        const Note note = this->noteQueue.get();
        tone(this->pin, note.frequency, note.duration);

        this->currentNoteTimer.setDuration(note.duration + note.pauseDuration);
        this->currentNoteTimer.set(now);
    }

    /**
     * Add a note to the queue.
     * It will be played after all the notes that are already in the queue.
     */
    void scheduleNote(const frequencyType frequency, const durationType duration,
                      const durationType pauseDuration = 0) {
        const Note note = {.frequency = frequency, .duration = duration, .pauseDuration = pauseDuration};
        this->noteQueue.add(note);
    }

   private:
    /**
     * Pin of the buzzer.
     */
    const uint8_t pin;

    /**
     * Queue of notes to be played.
     */
    NoteQueue noteQueue;

    /**
     * Timer used to track the current note.
     */
    Timer currentNoteTimer = Timer(0);
};

#endif  // BUZZER_H
