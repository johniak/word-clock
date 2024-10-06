#include "WordClock.h"

const uint32_t COLORS[] = {
    0xFF0000,  // Red
    0x00FF00,  // Green
    0x0000FF,  // Blue
    0xFFFF00,  // Yellow
    0xFF00FF,  // Magenta
    0x00FFFF,  // Cyan
    0xFFFFFF,  // White
    0xA52A2A   // Brown
};

WordClock::WordClock(ClockDisplayHAL* clockDisplayHAL, NetworkTimeHelper* timeHelper) 
    : clockDisplayHAL(clockDisplayHAL), timeHelper(timeHelper), lastHour(-1), allLastHighlightedWords("") {}

void WordClock::highlightWord(const String &word, uint32_t color) {
    clockDisplayHAL->displayWord(word, color);
}

String WordClock::getMinutesWord(int minute) {
    if (minute < 5) return "OCLOCK";
    else if (minute < 10) return "FIVE";
    else if (minute < 15) return "TEN";
    else if (minute < 20) return "FIFTEEN";
    else if (minute < 25) return "TWENTY";
    else if (minute < 30) return "TWENTYFIVE";
    else if (minute < 35) return "THIRTY";
    else if (minute < 40) return "TWENTYFIVE";
    else if (minute < 45) return "TWENTY";
    else if (minute < 50) return "FIFTEEN";
    else if (minute < 55) return "TEN";
    else return "FIVE";
}

uint32_t WordClock::getRandomColor() {
    int index = random(0, sizeof(COLORS) / sizeof(COLORS[0]));
    return COLORS[index];
}

void WordClock::displayTime() {
    struct tm currentTime = timeHelper->getLocalTimeStruct();

    int hour = currentTime.tm_hour % 12;
    if (hour == 0) hour = 12;  // Handle 12-hour format

    int minute = currentTime.tm_min;
    
    clockDisplayHAL->clearPixels(false);  // Clear the display but don't show yet

    if (hour != lastHour && minute == 0) {
        lastHour = hour;
        clockDisplayHAL->clearPixels(false);
    }

    highlightWord("IT", getRandomColor());
    highlightWord("IS", getRandomColor());
    String allHighlightedWords = "ITIS";

    if (minute < 5) {
        highlightWord("OCLOCK", getRandomColor());
        allHighlightedWords += "OCLOCK";
    } else if (minute < 35) {
        highlightWord("PAST", getRandomColor());
        highlightWord("MINUTES", getRandomColor());
        allHighlightedWords += "PASTMINUTES";
    } else {
        highlightWord("TO", getRandomColor());
        highlightWord("MINUTES", getRandomColor());
        allHighlightedWords += "TOMINUTES";
        hour = (hour + 1) % 12;
        if (hour == 0) hour = 12;
    }

    String hourWord = "HOUR_" + String(hour);
    highlightWord(getMinutesWord(minute), getRandomColor());
    allHighlightedWords += getMinutesWord(minute);
    highlightWord(hourWord, getRandomColor());
    allHighlightedWords += hourWord;

    if (allLastHighlightedWords != allHighlightedWords) {
        clockDisplayHAL->show();  // Only show if there's a change
        allLastHighlightedWords = allHighlightedWords;
    }
}
