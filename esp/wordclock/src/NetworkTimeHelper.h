#ifndef NETWORK_TIME_HELPER_H
#define NETWORK_TIME_HELPER_H

#include <WiFi.h>
#include <time.h>

class NetworkTimeHelper {
public:
    NetworkTimeHelper(char* ssid, char* password, long gmtOffset_sec, int daylightOffset_sec);
    void setup();
    void update();  
    struct tm getLocalTimeStruct(); 
private:
    char* ssid;
    char* password;
    long gmtOffset_sec;  
    int daylightOffset_sec;  
    unsigned long lastSyncTime;
    const unsigned long syncInterval = 86400000;  // 24 hours in milliseconds

    void syncTimeWithNTP(); 
};

#endif
