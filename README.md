# ADAS

This project consists of a RaspberryPi and an Ardunio board working together to run an autonomous car.

## Abstract
The RapberryPi is in charge of determining the direction of the car by the car's control camera. This video recognition part uses OpenCV and its subproject is in ./Autopilot.
We implemented a manual remote control to be able to take the control in case of need. This one takes the form of a real time web application, it can be found in ./Telecommande

These two controllers send their information to the Arduino board which is in charge of controlling the car's motors. These control informations are filtered by the sub-project ./ControllersController to manage the priorities between controllers.

## Installation
### Arduino
You just have to remove the driver `./Arduino/driver.ino` in the board by the usual means (typically via the Arduino IDE)

### Raspberry Pi
 First, clone the project on the Raspberry Pi with `git clone https://github.com/TERRUSS/ADAS && cd ADAS`.
 Then we want to install all the dependencies: `./setup.sh`. This operation takes some time, don't hesitate to comment the unnecessary installation steps.

 Then :
 - Launch the ControllersController (in the ControllersController folder):
 ```
 > make # required the first time
 > ./controller
 ```
 - Launch the telecommand (in the Telecommand folder):
 ```
 > cd server
 > npm i && node app.js
 ```
 - Launch the autopilot (in the Autopilot folder):
 ```
 > ./build.sh # required the first time
 > ./autopilot
 ```
 Once we have checked that all the steps are working correctly (and that the build steps have been done), we can start everything simply with the `run.sh` scritpt in the root of the project.

