#ifndef SERIAL_HELPER_H
#define SERIAL_HELPER_H

#include <Arduino.h>
#include "config.h"

#if USE_SERIAL
    #define SERIAL_PRINT(x) Serial.print(x)
    #define SERIAL_PRINTLN(x) Serial.println(x)
#else
    #define SERIAL_PRINT(x)
    #define SERIAL_PRINTLN(x)
#endif

void initSerial();  // Function to initialize serial if needed

#endif
