# Controllers Controller

This piece of software is acts like a balancer, filtering inputs between differents
controllers (here, a remote controller [../Telecommande/] and an autopilot [../Autopilot/]
sources based on their priority.
The filtered output is forwarded to a USB Serial Port (here, an Arduino [../Arduino/])

TODO :
	- Add config file instead of hardcoding FIFO paths and USB Serial Port
