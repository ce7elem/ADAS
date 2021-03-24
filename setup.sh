#!/bin/bash

echo "# Installing Dependencies"

[ -d Dependencies ] && mkdir Dependencies && cd Dependencies

echo "	## CppLinuxSerial"
git clone https://github.com/gbmhunter/CppLinuxSerial
cd CppLinuxSerial
mkdir build
cd build
cmake ..
make
sudo make install

echo "Setup completed"
