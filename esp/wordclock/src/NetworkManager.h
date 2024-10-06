#ifndef NETWORK_MANAGER_H
#define NETWORK_MANAGER_H

#include <WiFi.h>
#include <time.h>
#include <HTTPClient.h>

class NetworkManager
{
public:
    NetworkManager(char *ssid, char *password, long gmtOffset_sec, int daylightOffset_sec);
    void setup();
    void update();
    struct tm getLocalTimeStruct();
    bool downloadGIF(const char *gifUrl);
    uint8_t *getGifBuffer();
    size_t getGifBufferSize();

private:
    char *ssid;
    char *password;
    long gmtOffset_sec;
    int daylightOffset_sec;
    unsigned long lastSyncTime;
    const unsigned long syncInterval = 86400000;
    uint8_t *gifBuffer = nullptr;
    size_t gifBufferSize = 0;

    void syncTimeWithNTP();
    uint8_t *handleDownloadGIFResponse(HTTPClient &http, int gifSize);
};

#endif
