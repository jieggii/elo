//
// Created by jieggii on 10/27/24.
// This file contains various sound effects that can be played by the device.
//

#ifndef SFX_H
#define SFX_H

#include "Note.h"
#include "tone.h"

namespace SFX {
    /**
     * Sound effect that is played when the device is booted.
     */
    constexpr Note boot[] = {
        {Tone::C4, 50, 0},
        {Tone::E4, 50, 0},
        {Tone::G4, 50, 0},
        {Tone::C5, 150, 0},
    };

    /**
     * Sound effect that is played when work mode view is resumed.
     */
    constexpr Note resume[] = {
        {Tone::C4, 100, 0},
        {Tone::D4, 100, 0},
        {Tone::E4, 100, 0},
    };

    /**
     * Sound effect that is played when work mode view is paused.
     */
    constexpr Note pause[] = {
        {Tone::E4, 100, 0},
        {Tone::D4, 100, 0},
        {Tone::C4, 100, 0},
    };

    /**
     * Sound effect that is played as a posture reminder.
     */
    constexpr Note postureReminder[] = {
        {Tone::C4, 100, 0},
        {Tone::C5, 100, 0},
        {Tone::D4, 100, 0},
        {Tone::D5, 100, 0},
    };
}  // namespace SFX

#endif  // SFX_H
