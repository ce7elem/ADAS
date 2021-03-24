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

cd ../../
echo "	## boost"
git clone --recursive https://github.com/boostorg/boost.git
cd boost
./bootstrap.sh


echo "Setup completed"
