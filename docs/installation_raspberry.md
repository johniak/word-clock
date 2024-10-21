# Raspberry Pi Zero Installation Instructions

## Preparation Raspbian OS
1. Prepare the necessary hardware:
   1. Raspberry Pi Zero W
   2. microSD card (at least 8GB, 16GB or more recommended)
   3. micro USB power adapter
2. Download the necessary software:
   1. Raspberry Pi Imager: [https://www.raspberrypi.org/software/](https://www.raspberrypi.org/software/)
3. Prepare the SD card:
   1. Download the latest version of Raspberry Pi **Lite** OS for the Raspberry Pi Zero W. Make sure to select the 32-bit version. Choose the Lite version from Raspberry Pi OS (other).
   2. After selecting your storage, click "Next" and then `EDIT SETTINGS`. You'll need to fill in the following settings:
      1. Username/Password
      2. WiFi credentials
      3. Timezone
      4. (Optional) You can set a hostname. You should be able to access your device via SSH using the hostname, depending on your local network configuration.
      5. Switch to the "Services" tab and enable SSH.
   3. Write the image to the SD card.
## Project Installation
1. Insert the SD card into your Raspberry Pi and wait for it to connect to the WiFi.
1. Find the IP address of your Raspberry Pi on your router or remember the hostname.
1. Use your preferred tool to access SSH (e.g., PuTTY on Windows or SSH in the terminal).
1. Connect to your Raspberry Pi via SSH.
1. Set up the project:

   ```bash
   sudo apt update
   sudo apt install git libopenjp2-7 python3 python3-pip
   git clone https://github.com/johniak/word-clock.git
   cd word-clock/raspberry-pi/
   sudo pip3 install --break-system-packages -r requirements.txt
   ```

1. Connect your Word Clock following the [device build instructions](device_build.md).
1. To check if everything is working, run the following command (for testing purposes only):

    ```bash
    sudo python3 src/wordclock/main.py --pin D12 --brightness 0.5 --gif ./heart_art_small.gif
    ```

1. To install it as a service (so it starts automatically on device startup), run the following command:

    ```bash
    ./install.sh
    ```