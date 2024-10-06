#include <Arduino.h>
#include "ClockDisplayHAL.h"
#include "NetworkManager.h"
#include "SerialHelper.h"
#include "config.h"
#include "GifPlayer.h"
#include "WordClock.h"

NetworkManager networkManager(WIFI_SSID, WIFI_PASSWORD, GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC);
ClockDisplayHAL clockDisplayHAL(LED_PIN, 255);
GifPlayer gifPlayer(&clockDisplayHAL);
WordClock wordClock(&clockDisplayHAL, &networkManager, &gifPlayer);

void setup()
{
  initSerial();
  networkManager.setup();
  clockDisplayHAL.setup();
  wordClock.setup();
}

void loop()
{
  networkManager.update();
  wordClock.displayTime();
  delay(1000);
}
