#include "NetworkManager.h"
#include "SerialHelper.h"

#define MAX_GIF_SIZE 32768 // 32KB limit

NetworkManager::NetworkManager(char *ssid, char *password, long gmtOffset_sec, int daylightOffset_sec)
    : ssid(ssid), password(password), gmtOffset_sec(gmtOffset_sec), daylightOffset_sec(daylightOffset_sec), lastSyncTime(0), gifBuffer(nullptr), gifBufferSize(0) {}

void NetworkManager::setup()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        SERIAL_PRINT(".");
    }
    SERIAL_PRINTLN("WiFi connected");

    syncTimeWithNTP();
}

void NetworkManager::update()
{
    unsigned long currentMillis = millis();
    if (currentMillis - lastSyncTime >= syncInterval)
    {
        syncTimeWithNTP();
    }
}

void NetworkManager::syncTimeWithNTP()
{
    const char *ntpServer = "pool.ntp.org";
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo))
    {
        SERIAL_PRINTLN("Failed to obtain time");
    }
    lastSyncTime = millis();
}

struct tm NetworkManager::getLocalTimeStruct()
{
    struct tm timeinfo;
    if (getLocalTime(&timeinfo))
    {
        return timeinfo;
    }
    else
    {
        memset(&timeinfo, 0, sizeof(struct tm));
        SERIAL_PRINTLN("Failed to obtain local time");
        return timeinfo;
    }
}

bool NetworkManager::downloadGIF(const char *gifUrl)
{
    if (WiFi.status() == WL_CONNECTED)
    {
        HTTPClient http;
        http.begin(gifUrl);

        int httpResponseCode = http.GET();
        if (httpResponseCode == HTTP_CODE_OK)
        {
            int gifSize = http.getSize();

            if (gifSize > MAX_GIF_SIZE)
            {
                SERIAL_PRINTLN("GIF is too large. Max size allowed is 32KB.");
                http.end();
                return false;
            }

            gifBuffer = handleDownloadGIFResponse(http, gifSize);
            gifBufferSize = gifSize;
            http.end();
            return gifBuffer != nullptr;
        }
        else
        {
            SERIAL_PRINTLN("Failed to download GIF");
            http.end();
            return false;
        }
    }
    else
    {
        SERIAL_PRINTLN("WiFi not connected");
        return false;
    }
}

uint8_t *NetworkManager::handleDownloadGIFResponse(HTTPClient &http, int gifSize)
{
    WiFiClient *stream = http.getStreamPtr();

    if (gifSize > 0)
    {
        SERIAL_PRINTLN("Downloading GIF...");

        uint8_t *buffer = (uint8_t *)malloc(gifSize);
        if (buffer == nullptr)
        {
            SERIAL_PRINTLN("Memory allocation failed for GIF");
            return nullptr;
        }

        int bytesRead = 0;
        while (http.connected() && stream->available() > 0 && bytesRead < gifSize)
        {
            int byte = stream->read();
            buffer[bytesRead++] = byte;
        }

        SERIAL_PRINTLN("GIF downloaded and stored in memory");
        return buffer;
    }
    else
    {
        SERIAL_PRINTLN("No data available for GIF");
        return nullptr;
    }
}

uint8_t *NetworkManager::getGifBuffer()
{
    return gifBuffer;
}

size_t NetworkManager::getGifBufferSize()
{
    return gifBufferSize;
}
