    1  htop
    2  vcgencmd 
    3  vcgencmd measure_temp
    4  ls
    5  mkdir Code
    6  cd Code
    7  ls
    8  sudo apt-get update
    9  git clone https://github.com/TERRUSS/ADAS
   10  apt-get upgrade
   11  sudo apt-get upgrade
   12  sudo apt install cmake build-essential pkg-config git
   13  sudo apt install libjpeg-dev libtiff-dev libjasper-dev libpng-dev libwebp-dev libopenexr-dev
   14  sudo apt install libavcodec-dev libavformat-dev libswscale-dev libv4l-dev libxvidcore-dev libx264-dev libdc1394-22-dev libgstreamer-plugins-base1.0-dev libgstreamer1.0-dev
   15  sudo apt install libgtk-3-dev libqtgui4 libqtwebkit4 libqt4-test python3-pyqt5
   16  sudo apt install libatlas-base-dev liblapacke-dev gfortran
   17  sudo apt install libhdf5-dev libhdf5-103
   18  sudo nano /etc/dphys-swapfile
   19  sudo systemctl restart dphys-swapfile
   20  cd ..
   21  git clone https://github.com/opencv/opencv.git
   22  ls
   23  git clone https://github.com/opencv/opencv_contrib.git
   24  mkdir ~/opencv/build
   25  cd ~/opencv/build
   26  cmake -D CMAKE_BUILD_TYPE=RELEASE     -D CMAKE_INSTALL_PREFIX=/usr/local     -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules     -D ENABLE_NEON=ON     -D ENABLE_VFPV3=ON     -D BUILD_TESTS=OFF     -D INSTALL_PYTHON_EXAMPLES=OFF     -D OPENCV_ENABLE_NONFREE=ON     -D CMAKE_SHARED_LINKER_FLAGS=-latomic     -D BUILD_EXAMPLES=OFF ..
   27  make -j4
   28  htop
   29  cd ../../Code/ADAS/LineDetector/
   30  ls
   31  gedit utils.h main.cpp build.sh 
   32  bg
   33  sh build.sh 
   34  sudo apt-file search opencv.pc
   35  cd /usr/local/bin/
   36  ls
   37  ./opencv_version 
   38  cd opencv
   39  cd build/
   40  ls
   41  make -j4
   42  make -j1
   43  make install
   44  sudo make install
   45  sudo ldconfig
   46  python
   47  cd ..
   48  ls
   49  cd Code/
   50  cd ADAS/LineDetector/
   51  ls
   52  sh build.sh 
   53  pkg-config lib opencv
   54  ls
   55  sh build.sh 
   56  apt-file search opencv.pc
   57  asudo pt install apt-file
   58  sudo apt install apt-file
   59  apt-file search opencv.pc
   60  apt-file update
   61  sudo apt-file update
   62  sudo apt-file search opencv.pc
   63  gedit build.sh 
   64  nano build.sh 
   65  sh build.sh 
   66  cd ../..
   67  cd ..
   68  ls
   69  cd opencv
   70  ls
   71  cmake -D CMAKE_BUILD_TYPE=RELEASE     -D CMAKE_INSTALL_PREFIX=/usr/local     -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules     -D ENABLE_NEON=ON     -D ENABLE_VFPV3=ON     -D BUILD_TESTS=OFF     -D INSTALL_PYTHON_EXAMPLES=OFF     -D OPENCV_ENABLE_NONFREE=ON     -D CMAKE_SHARED_LINKER_FLAGS=-latomic -DOPENCV_GENERATE_PKGCONFIG=ON    -D BUILD_EXAMPLES=OFF ..
   72  ls
   73  cd build/
   74  cmake -D CMAKE_BUILD_TYPE=RELEASE     -D CMAKE_INSTALL_PREFIX=/usr/local     -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules     -D ENABLE_NEON=ON     -D ENABLE_VFPV3=ON     -D BUILD_TESTS=OFF     -D INSTALL_PYTHON_EXAMPLES=OFF     -D OPENCV_ENABLE_NONFREE=ON     -D CMAKE_SHARED_LINKER_FLAGS=-latomic -DOPENCV_GENERATE_PKGCONFIG=ON    -D BUILD_EXAMPLES=OFF ..
   75  make -j4
   76  sudo make install
   77  cd ..
   78  ls
   79  cd Code/ADAS/LineDetector/
   80  ls
   81  sh build.sh 
   82  sudo apt-get install gedit
   83  gedit main.cpp 
   84  gedit main.cpp &
   85  gedit utils.h &
   86  sh build.sh 
   87  cd ..
   88  ls
   89  cd opencv
   90  git checkout 3.4.9 
   91  cd ..
   92  cd opencv_contrib/
   93  git checkout 3.4.9 
   94  cd ..
   95  cd opencv
   96  ls
   97  mkdir build
   98  ls
   99  cd build/
  100  ls
  101  cd ..
  102  git log
  103  mkdir build3.4.9
  104  cd build3.4.9/
  105  cmake -D CMAKE_BUILD_TYPE=RELEASE     -D CMAKE_INSTALL_PREFIX=/usr/local     -D OPENCV_EXTRA_MODULES_PATH=~/opencv_contrib/modules     -D ENABLE_NEON=ON     -D ENABLE_VFPV3=ON     -D BUILD_TESTS=OFF     -D INSTALL_PYTHON_EXAMPLES=OFF     -D OPENCV_ENABLE_NONFREE=ON     -D CMAKE_SHARED_LINKER_FLAGS=-latomic -DOPENCV_GENERATE_PKGCONFIG=ON  -D BUILD_EXAMPLES=OFF ..
  106  make -j4
  107  cd ..
  108  ls
  109  git checkout 2.4.13.7
  110  ls
  111  mkdri build2.4
  112  mkdir build2.4
  113  cd build2.4/
  114  ls
  115  sudo apt-get -y install build-essential cmake cmake-curses-gui pkg-config libpng12-0 libpng12-dev libpng++-dev libpng3 libpnglite-dev zlib1g-dbg zlib1g zlib1g-dev pngtools libtiff4-dev libtiff4 libtiffxx0c2 libtiff-tools libeigen3-dev
  116  sudo apt-get -y install libjpeg8 libjpeg8-dev libjpeg8-dbg libjpeg-progs ffmpeg libavcodec-dev libavcodec53 libavformat53 libavformat-dev libgstreamer0.10-0-dbg libgstreamer0.10-0 libgstreamer0.10-dev libxine1-ffmpeg libxine-dev libxine1-bin libunicap2 libunicap2-dev swig libv4l-0 libv4l-dev python-numpy libpython2.6 python-dev python2.6-dev libgtk2.0-dev 
  117  ls
  118  cmake -D CMAKE_BUILD_TYPE=RELEASE     -D CMAKE_INSTALL_PREFIX=/usr/local      -D ENABLE_NEON=ON     -D ENABLE_VFPV3=ON     -D BUILD_TESTS=OFF     -D INSTALL_PYTHON_EXAMPLES=OFF     -D OPENCV_ENABLE_NONFREE=ON     -D CMAKE_SHARED_LINKER_FLAGS=-latomic -DOPENCV_GENERATE_PKGCONFIG=ON  -D BUILD_EXAMPLES=OFF ..
  119  make -j4
  120  sudo make install
  121  sudo ldconfig 
  122  lz
  123  cd ..
  124  cd
  125  cd Code/ADAS/LineDetector/
  126  gedit main.cpp &
  127  gedit build.sh &
  128  sh build.sh 
  129  cd ..
  130  ls
  131  cd ..
  132  rm -rf ADAS/
  133  git clone https://github.com/TERRUSS/ADAS
  134  cd ADAS/LineDetector/
  135  ls
  136  gedit build.sh &
  137  sh build.sh 
  138  ./main 
  139  sudo apt-get install libgtk-dev
  140  sudo apt-get install libgtk2.0-dev
  141  sh build.sh 
  142  ./main 
  143  sh build.sh 
  144  ./main 
  145  cd ..
  146  cd opencv
  147  cd build2.4/
  148  cmake -D CMAKE_BUILD_TYPE=RELEASE     -D CMAKE_INSTALL_PREFIX=/usr/local      -D ENABLE_NEON=ON     -D ENABLE_VFPV3=ON     -D BUILD_TESTS=OFF     -D INSTALL_PYTHON_EXAMPLES=OFF     -D OPENCV_ENABLE_NONFREE=ON     -D CMAKE_SHARED_LINKER_FLAGS=-latomic -DOPENCV_GENERATE_PKGCONFIG=ON  -D BUILD_EXAMPLES=OFF ..
  149  make -j4
  150  sudo apt-get install libtiff4-dev
  151  sudo apt-get install libtiff-dev
  152  sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
  153  make -j4
  154  ls
  155  sudo make install
  156  sudo ldconfig 
  157  cd ..
  158  cd Code/ADAS/LineDetector/
  159  sh build.sh 
  160  ./main 
  161  gedit main.cpp 
  162  bg
  163  sh build.sh 
  164  ./main 
  165  sh build.sh 
  166  ./main 
  167  sh build.sh 
  168  ./main 
  169  sh build.sh 
  170  ./main 
  171  sh build.sh 
  172  ./main 
  173  sh build.sh 
  174  ./main 
  175  sh build.sh 
  176  ./main 
  177  sh build.sh 
  178  ./main 
  179  sh build.sh 
  180  ./main 
  181  sh build.sh 
  182  ./main 
  183  sh build.sh 
  184  ./main 
  185  sh build.sh 
  186  ./main 
  187  sh build.sh 
  188  ./main 
  189  sh build.sh 
  190  ./main 
  191  sh build.sh 
  192  ./main 
  193  sh build.sh 
  194  ./main 
  195  sh build.sh 
  196  ./main 
  197  sh build.sh 
  198  ./main 
  199  sh build.sh 
  200  ./main 
  201  sh build.sh 
  202  ./main 
  203  sh build.sh 
  204  ./main 
  205  sh build.sh 
  206  ./main 
  207  fg
  208  ./main 
  209  git add ..
  210  git add .
  211  git add *
  212  git commit -m "fix camera right line detected"
  213  git config --global user.email "vincent.maxime.pro"
  214  git config --global user.email "vincent.maxime.pro@gmail.com"
  215  git config --global user.name "ADAS RB PI 3"
  216  git commit -m "fix camera right line detected"
  217  git push
  218  history
  219  cd Code/
  220  cd ADAS/
  221  ls
  222  cd LineDetector/
  223  history
  224  history > history_install.md
