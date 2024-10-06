#include "SerialHelper.h"

void initSerial()
{
#if USE_SERIAL
    Serial.begin(9600);
#endif
}