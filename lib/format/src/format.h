////
//// Created by jieggii on 9/17/24.
////
//
// #ifndef ELO_LIB_FORMAT_SRC_FORMAT_H_
// #define ELO_LIB_FORMAT_SRC_FORMAT_H_
//
// #include "cstdint"
// #include "stdio.h"
//
///**
// * Formats timestamp in HH:MM:SS string format.
// * @param timestamp - timestamp in milliseconds.
// * @return
// */
// void format_timestamp(uint32_t timestamp, char* buffer) {
//    // convert milliseconds to seconds
//    uint32_t total_seconds = timestamp / 1000;
//
//    // calculate hours, minutes, and seconds
//    uint8_t hours = total_seconds / 3600;
//    uint8_t minutes = (total_seconds % 3600) / 60;
//    uint8_t seconds = total_seconds % 60;
//
//    // Format the time into the provided buffer in HH:MM:SS format
//    buffer[0] = '0' + (hours / 10);
//    buffer[1] = '0' + (hours % 10);
//    buffer[2] = ':';
//    buffer[3] = '0' + (minutes / 10);
//    buffer[4] = '0' + (minutes % 10);
//    buffer[5] = ':';
//    buffer[6] = '0' + (seconds / 10);
//    buffer[7] = '0' + (seconds % 10);
//    buffer[8] = '\0'; // Null-terminate the string
//}
//
// #endif  // ELO_LIB_FORMAT_SRC_FORMAT_H_
