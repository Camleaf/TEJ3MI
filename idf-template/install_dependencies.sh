#!/bin/bash
installDirectory="$PWD"
# If scripts runs with root permission, then ESP-IDF gets installed into root directory
if [ "$EUID" -eq 0 ]; then
    echo "This script must not be run with root permission (sudo)"
    exit 1
fi

echo "Installing dependencies for Linux"

echo "Installing ESP-IDF for esp32s3"

# Install dependencies

sudo apt-get install python3 python3-pip python3-venv
sudo apt-get install git wget flex bison gperf cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
# Clone the repo
mkdir -p ~/esp
cd ~/esp
git clone -b v5.5.2 --recursive https://github.com/espressif/esp-idf.git
# run the install script

cd ~/esp/esp-idf
./install.sh esp32,esp32s3

. $HOME/esp/esp-idf/export.sh


idf_tools.py install esp-clang

echo "Finished installing ESP-IDF"




# add other dependencies here


echo "Finished installing dependencies"
echo "Creating initial build"

cd $installDirectory

idf.py set-target esp32s3
idf.py build
