//
// Created by jieggii on 10/27/24.
//

#ifndef NOTEQUEUE_H
#define NOTEQUEUE_H

#include "Note.h"

/**
 * NoteQueue is a queue of notes that can be played by the buzzer.
 * Maximum number of notes in the queue is determined by maxQueueSize member.
 */
class NoteQueue {
   public:
    /**
     * Maximum number of notes in the queue.
     */
    static constexpr uint8_t maxLen = 8;

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
        if (this->len == maxLen) {
            // do not add element to the queue if it is full
            return;
        }

        this->queue[this->len] = note;
        this->len++;
    }

    [[nodiscard]] bool isEmpty() const { return this->len == 0; }

    // [[nodiscard]] bool isFull() const { return this->len == maxQueueSize; }

   private:
    uint8_t len = 0;
    Note queue[maxLen] = {};
};

#endif  // NOTEQUEUE_H
