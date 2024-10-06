#!/bin/bash

# Get the directory of the currently executing script
BASE_PATH="$(dirname "$(realpath "$0")")"

# Variables
SERVICE_NAME="word_clock.service"
SERVICE_PATH="/etc/systemd/system/$SERVICE_NAME"
SCRIPT_PATH="$BASE_PATH/src/wordclock/main.py"
GIF_PATH="$BASE_PATH/heart_art_small.gif"
WORKING_DIRECTORY="$BASE_PATH/src/wordclock"
PYTHON_PATH="/usr/bin/python3"

# Check if the service already exists
if [ -f "$SERVICE_PATH" ]; then
    echo "Service $SERVICE_NAME already exists. Removing the old service."
    sudo systemctl stop $SERVICE_NAME
    sudo systemctl disable $SERVICE_NAME
    sudo rm "$SERVICE_PATH"
fi

# Create the service file
echo "Creating systemd service file at $SERVICE_PATH"
sudo bash -c "cat > $SERVICE_PATH" <<EOF
[Unit]
Description=Word Clock Service
After=multi-user.target

[Service]
ExecStart=$PYTHON_PATH $SCRIPT_PATH --pin D12 --brightness 0.5 --gif $GIF_PATH
WorkingDirectory=$WORKING_DIRECTORY
StandardOutput=inherit
StandardError=inherit
Restart=always

[Install]
WantedBy=multi-user.target
EOF

# Enable the service
echo "Enabling the $SERVICE_NAME to start on boot"
sudo systemctl enable $SERVICE_NAME

# Start the service
echo "Starting the $SERVICE_NAME service"
sudo systemctl start $SERVICE_NAME

# Check the status
echo "Checking the status of the $SERVICE_NAME service"
sudo systemctl status $SERVICE_NAME

echo "Installation complete!"