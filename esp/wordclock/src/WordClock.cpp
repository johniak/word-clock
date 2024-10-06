#include "WordClock.h"
#include "SerialHelper.h"

const uint32_t COLORS[] = {
    0xFF0000,
    0x00FF00,
    0x0000FF,
    0xFFFF00,
    0xFF00FF,
    0x00FFFF,
    0xFFFFFF,
    0xA52A2A};

WordClock::WordClock(ClockDisplayHAL *clockDisplayHAL, NetworkManager *networkManager, GifPlayer *gifPlayer)
    : clockDisplayHAL(clockDisplayHAL), networkManager(networkManager), gifPlayer(gifPlayer), lastHour(-1), allLastHighlightedWords(""), gifDownloaded(false) {}

void WordClock::setup()
{
    downloadGIF();
}

void WordClock::downloadGIF()
{
    if (!gifDownloaded)
    {
        const char *gifUrl = "https://raw.githubusercontent.com/johniak/word-clock/refs/heads/main/raspberry-pi/heart_art_small.gif";
        if (networkManager->downloadGIF(gifUrl))
        {
            uint8_t *gifBuffer = networkManager->getGifBuffer();
            size_t gifSize = networkManager->getGifBufferSize();
            if (gifSize > 0 && gifBuffer != nullptr)
            {
                if (gifPlayer->loadGIF(gifBuffer, gifSize))
                {
                    gifDownloaded = true;
                    SERIAL_PRINTLN("GIF downloaded and loaded successfully.");
                }
            }
        }
        else
        {
            SERIAL_PRINTLN("Failed to download GIF.");
        }
    }
}

void WordClock::highlightWord(const String &word, uint32_t color)
{
    clockDisplayHAL->displayWord(word, color);
}

String WordClock::getMinutesWord(int minute)
{
    if (minute < 5)
        return "OCLOCK";
    else if (minute < 10)
        return "FIVE";
    else if (minute < 15)
        return "TEN";
    else if (minute < 20)
        return "FIFTEEN";
    else if (minute < 25)
        return "TWENTY";
    else if (minute < 30)
        return "TWENTYFIVE";
    else if (minute < 35)
        return "THIRTY";
    else if (minute < 40)
        return "TWENTYFIVE";
    else if (minute < 45)
        return "TWENTY";
    else if (minute < 50)
        return "FIFTEEN";
    else if (minute < 55)
        return "TEN";
    else
        return "FIVE";
}

uint32_t WordClock::getRandomColor()
{
    int index = random(0, sizeof(COLORS) / sizeof(COLORS[0]));
    return COLORS[index];
}

void WordClock::displayTime()
{
    struct tm currentTime = networkManager->getLocalTimeStruct();
    int hour = currentTime.tm_hour % 12;
    if (hour == 0)
        hour = 12;
    int minute = currentTime.tm_min;

    clockDisplayHAL->clearPixels(false);

    if (hour != lastHour && minute == 0)
    {
        lastHour = hour;
        if (gifDownloaded)
        {
            gifPlayer->playGIF(4000);
        }
        clockDisplayHAL->clearPixels(false);
    }

    highlightWord("IT", getRandomColor());
    highlightWord("IS", getRandomColor());
    String allHighlightedWords = "ITIS";

    if (minute < 5)
    {
        highlightWord("OCLOCK", getRandomColor());
        allHighlightedWords += "OCLOCK";
    }
    else if (minute < 35)
    {
        highlightWord("PAST", getRandomColor());
        highlightWord("MINUTES", getRandomColor());
        allHighlightedWords += "PASTMINUTES";
    }
    else
    {
        highlightWord("TO", getRandomColor());
        highlightWord("MINUTES", getRandomColor());
        allHighlightedWords += "TOMINUTES";
        hour = (hour + 1) % 12;
        if (hour == 0)
            hour = 12;
    }

    String hourWord = "HOUR_" + String(hour);
    highlightWord(getMinutesWord(minute), getRandomColor());
    allHighlightedWords += getMinutesWord(minute);
    highlightWord(hourWord, getRandomColor());
    allHighlightedWords += hourWord;

    if (allLastHighlightedWords != allHighlightedWords)
    {
        clockDisplayHAL->show();
        allLastHighlightedWords = allHighlightedWords;
    }
}
