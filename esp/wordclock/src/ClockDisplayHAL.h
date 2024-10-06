#ifndef CLOCKDISPLAYHAL_H
#define CLOCKDISPLAYHAL_H

#include <Adafruit_NeoPixel.h>

class ClockDisplayHAL
{
public:
    static const uint16_t WIDTH = 12;
    static const uint16_t HEIGHT = 11;
    static const uint16_t NUM_LEDS = WIDTH * HEIGHT;

    ClockDisplayHAL(uint8_t pin, uint8_t brightness);
    void setup();
    void displayWord(const String &word, uint32_t color);
    void setPixel(uint8_t x, uint8_t y, uint32_t color);
    void clearPixels(bool show = true);
    void show();

private:
    Adafruit_NeoPixel pixels;
    uint8_t brightness;

    static const struct WordMapping
    {
        const char *word;
        uint8_t start;
        uint8_t end;
    } WORDS_TO_LEDS[];

    uint16_t cartesianToWordClockLEDStripIndex(uint8_t x, uint8_t y);
};

#endif