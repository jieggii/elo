//
// Created by jieggii on 10/25/24.
//

#ifndef BUZZER_H
#define BUZZER_H

#include "cstdint"

#include "Arduino.h"

#include "Timer.h"

#include "Note.h"
#include "internal/NoteQueue.h"

/**
 * Buzzer is an abstraction of a buzzer.
 */
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
     * Schedule a melody to be played.
     */
    void scheduleMelody(const Note notes[], const uint8_t len) {
        for (uint8_t i = 0; i < len; i++) {
            const Note note = {notes[i].frequency, notes[i].duration, notes[i].pauseDuration};
            this->noteQueue.add(note);
        }
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
    Timer currentNoteTimer = Timer();
};

#endif  // BUZZER_H
