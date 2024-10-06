#ifndef WORDCLOCK_H
#define WORDCLOCK_H

#include <Arduino.h>
#include "ClockDisplayHAL.h"
#include "NetworkTimeHelper.h"

class WordClock {
public:
    WordClock(ClockDisplayHAL* clockDisplayHAL, NetworkTimeHelper* timeHelper);
    void displayTime();  // This will handle the main time display logic

private:
    int lastHour;
    String allLastHighlightedWords;
    ClockDisplayHAL* clockDisplayHAL;
    NetworkTimeHelper* timeHelper;

    void highlightWord(const String &word, uint32_t color = 0xFFFFFF);
    String getMinutesWord(int minute);
    uint32_t getRandomColor();
};

#endif
