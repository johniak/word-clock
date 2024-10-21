# ESP32 Installation Instructions
2. You need Visual Studio Code with PlatformIO installed to build and upload the code to the ESP32.
1. **Open the Project**
   Open the `esp/wordclock/` directory in PlatformIO.
1. **Configuration**

   Make a copy of `esp/wordclock/src/config.h.example` and rename it to `esp/wordclock/src/config.h`.

   You need to set there the WiFi SSID and password, and time zone informations.
1. Connect your Word Clock following the [device build instructions](device_build.md).
1. **Upload the Code**
   Connect your ESP32 board to your computer and upload the code using the PlatformIO upload button.