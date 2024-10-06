#include "ClockDisplayHAL.h"

ClockDisplayHAL::WordMapping const ClockDisplayHAL::WORDS_TO_LEDS[] = {
    {"HOUR_1", 20, 22}, {"HOUR_2", 45, 47}, {"HOUR_3", 15, 19}, {"HOUR_4", 67, 70}, {"HOUR_5", 40, 43}, {"HOUR_6", 12, 14}, {"HOUR_7", 55, 59}, {"HOUR_8", 29, 35}, {"HOUR_9", 36, 39}, {"HOUR_10", 9, 11}, {"HOUR_11", 24, 29}, {"HOUR_12", 48, 53}, {"OCLOCK", 0, 5}, {"PAST", 60, 63}, {"TO", 63, 64}, {"MINUTES", 77, 83}, {"THIRTY", 84, 89}, {"TWENTY", 102, 107}, {"TWENTYFIVE", 98, 107}, {"FIVE", 98, 101}, {"TEN", 91, 93}, {"FIFTEEN", 110, 116}, {"IS", 127, 128}, {"IT", 130, 131}};

ClockDisplayHAL::ClockDisplayHAL(uint8_t pin, uint8_t brightness)
    : pixels(NUM_LEDS, pin, NEO_GRB + NEO_KHZ800), brightness(brightness)
{
}

void ClockDisplayHAL::setup()
{
    pixels.setBrightness(255);
    pixels.begin();
    pixels.show();
}

void ClockDisplayHAL::displayWord(const String &word, uint32_t color)
{
    for (auto mapping : WORDS_TO_LEDS)
    {
        if (word.equals(mapping.word))
        {
            for (uint8_t i = mapping.start; i <= mapping.end; ++i)
            {
                pixels.setPixelColor(i, color);
            }
            break;
        }
    }
}

uint16_t ClockDisplayHAL::cartesianToWordClockLEDStripIndex(uint8_t x, uint8_t y)
{
    uint16_t row_index;
    uint16_t index;

    if (y % 2 == 0)
    {
        row_index = NUM_LEDS - (y * WIDTH);
        index = row_index - (x + 1);
    }
    else
    {
        row_index = NUM_LEDS - ((y + 1) * WIDTH);
        index = row_index + x;
    }

    if (index < 0 || index >= NUM_LEDS)
    {
        return 0;
    }

    return index;
}

void ClockDisplayHAL::setPixel(uint8_t x, uint8_t y, uint32_t color)
{
    uint16_t index = cartesianToWordClockLEDStripIndex(x, y);
    pixels.setPixelColor(index, color);
}

void ClockDisplayHAL::clearPixels(bool show)
{
    pixels.clear();
    if (show)
    {
        pixels.show();
    }
}

void ClockDisplayHAL::show()
{
    pixels.show();
}