#!/bin/bash

BASE_PATH="$(dirname "$(realpath "$0")")"

SERVICE_NAME="word_clock.service"
SERVICE_PATH="/etc/systemd/system/$SERVICE_NAME"
SCRIPT_PATH="$BASE_PATH/src/wordclock/main.py"
GIF_PATH="$BASE_PATH/heart-art.gif"
WORKING_DIRECTORY="$BASE_PATH/src/wordclock"
PYTHON_PATH="/usr/bin/python3"

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

echo "Enabling the $SERVICE_NAME to start on boot"
sudo systemctl enable $SERVICE_NAME

echo "Starting the $SERVICE_NAME service"
sudo systemctl start $SERVICE_NAME

echo "Checking the status of the $SERVICE_NAME service"
sudo systemctl status $SERVICE_NAME

echo "Installation complete!"