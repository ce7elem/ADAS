#!/bin/bash

echo "# Installing Dependencies"

[ -d Dependencies ] && rm -rf Dependencies

mkdir Dependencies && cd Dependencies

echo "	## installing Node.js..."
sudo apt install curl
curl -sL https://deb.nodesource.com/setup_14.x -o nodesource_setup.sh
sudo bash nodesource_setup.sh
sudo apt install nodejs

echo "	## Installing CppLinuxSerial..."
git clone https://github.com/gbmhunter/CppLinuxSerial
cd CppLinuxSerial
mkdir build
cd build
cmake ..
make
sudo make install

echo " ## Installing OpenCV dependencies..."
alias i="sudo apt install -y"

i cmake build-essential pkg-config git
i libjpeg-dev libtiff-dev libjasper-dev libpng-dev libwebp-dev libopenexr-dev
i avcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libdc1394-22-dev libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
i libgtk-3-dev libqtgui4 libqtwebkit4 libqt4-test python3-pyqt5
i libatlas-base-dev liblapacke-dev gfortran
i libhdf5-dev libhdf5-103
i cmake-curses-gui libpng12-0 libpng12-dev libpng++-dev libpng3 libpnglite-dev zlib1g-dbg zlib1g zlib1g-dev pngtools libtiff4-dev libtiff4 libtiffxx0c2 libtiff-tools libeigen3-dev
libjpeg8 libjpeg8-dev libjpeg8-dbg libjpeg-progs ffmpeg libavcodec-dev libavcodec53 libavformat53 libavformat-dev libgstreamer0.10-0-dbg libgstreamer0.10-0 libgstreamer0.10-dev libxine1-ffmpeg libxine-dev libxine1-bin libunicap2 libunicap2-dev swig libv4l-0 libv4l-dev python-numpy libpython2.6 python-dev python2.6-dev libgtk2.0-dev libgtk-dev

echo " ## Installing OpenCV 2.4..."
git clone https://github.com/opencv/opencv.git
cd opencv
git checkout 2.4.13.7
mkdir build && cd build
cmake \
	-D CMAKE_BUILD_TYPE=RELEASE    -D CMAKE_INSTALL_PREFIX=/usr/local \
	-D ENABLE_NEON=ON              -D ENABLE_VFPV3=ON \
	-D BUILD_TESTS=OFF             -D INSTALL_PYTHON_EXAMPLES=OFF \
	-D OPENCV_ENABLE_NONFREE=ON    -D CMAKE_SHARED_LINKER_FLAGS=-latomic \
	-DOPENCV_GENERATE_PKGCONFIG=ON -D BUILD_EXAMPLES=OFF ..
make -j4
sudo make install
sudo ldconfig

echo "Setup completed"
