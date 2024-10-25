//
// Created by jieggii on 9/5/24.
//

#ifndef ELO_DEBUG_PRINT_H
#define ELO_DEBUG_PRINT_H

#ifdef DEBUG
#include "SoftwareSerial.h"
#define debug_init(x) Serial.begin(x)
#define debug_print(x) Serial.print(x)
#define debug_println(x) Serial.println(x)
#else
#define debug_init(x)
#define debug_print(x)
#define debug_println(x)
#endif

#endif  // ELO_DEBUG_PRINT_H
