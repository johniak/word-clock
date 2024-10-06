#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "ClockDisplayHAL.h"
#include "NetworkTimeHelper.h"
#include "SerialHelper.h"
#include "config.h"
#include "WordClock.h"

NetworkTimeHelper timeHelper(WIFI_SSID, WIFI_PASSWORD, GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC);
ClockDisplayHAL clockDisplayHAL(LED_PIN, 255);
WordClock wordClock(&clockDisplayHAL, &timeHelper);

void setup()
{
    initSerial();
    timeHelper.setup();
    clockDisplayHAL.setup();
}

void loop()
{
    timeHelper.update();
    wordClock.displayTime();
    delay(1000);
}