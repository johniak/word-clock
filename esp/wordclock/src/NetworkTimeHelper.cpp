#include "NetworkTimeHelper.h"
#include "SerialHelper.h"

NetworkTimeHelper::NetworkTimeHelper(char* ssid, char* password, long gmtOffset_sec, int daylightOffset_sec)
    : ssid(ssid), password(password), gmtOffset_sec(gmtOffset_sec), daylightOffset_sec(daylightOffset_sec), lastSyncTime(0) {}

void NetworkTimeHelper::setup() {
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        SERIAL_PRINT(".");
    }
    SERIAL_PRINTLN("WiFi connected");

    syncTimeWithNTP();
}

void NetworkTimeHelper::update() {
    unsigned long currentMillis = millis();
    if (currentMillis - lastSyncTime >= syncInterval) {
        syncTimeWithNTP();
    }
}

void NetworkTimeHelper::syncTimeWithNTP() {
    const char* ntpServer = "pool.ntp.org";
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

    struct tm timeinfo;
    if (!getLocalTime(&timeinfo)) {
        SERIAL_PRINTLN("Failed to obtain time");
    }
    lastSyncTime = millis();
}

struct tm NetworkTimeHelper::getLocalTimeStruct() {
    struct tm timeinfo;
    if (getLocalTime(&timeinfo)) {
        return timeinfo;
    } else {
        memset(&timeinfo, 0, sizeof(struct tm));
        SERIAL_PRINTLN("Failed to obtain local time");
        return timeinfo;
    }
}
