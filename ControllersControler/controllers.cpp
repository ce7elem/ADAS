
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include <mutex>

#include "debug/debug.hpp"
#include "utils/rang.hpp"

#ifndef DEBUG
#include <CppLinuxSerial/SerialPort.hpp>
using namespace mn::CppLinuxSerial;
#endif

#define MAX_BUF 1024

bool autopilot(true);

int filterInternalcommands(char * input) {

  if ( strcmp(input, "RESUME_AUTO") == 0 ) {
    autopilot = true;
    return 1;
  }

  return 0;
}

/**
 * ## Remote Controller listener routine
 * > void listenRController()
 *
 * Listen for an input in the /tmp/rcontroller FIFO
 * Then forwards it to the Arduino driver
 *
 * ### Parameters
 *
 * ### Returns
 */
void listenRController (){
  
	std::cout << INFO << "Listener for remote controller started" << std::endl;

	char input[10];
	int fd;
	char input_buf[MAX_BUF];

#ifndef DEBUG
	// Create serial port object and open serial port
	SerialPort serialPort("/dev/ttyACM1", 115002);
	serialPort.SetTimeout(500); // Block when reading until any data is received
	serialPort.Open();
#endif

  for(;;) {

    fd = open("/tmp/rcontroller", O_RDONLY);
    read(fd, input_buf, MAX_BUF);
    close(fd);

    int i;
    for (i = 0; input_buf[i] != '\n'; i++){}input_buf[i] = 0;

    autopilot = false;

    if ( ! filterInternalcommands(input_buf) ) {

#ifdef DEBUG
      std::cout << RC << input_buf << std::endl;
#else
      serialPort.Write(input);
      std::string readData;
      serialPort.Read(readData);

      std::cout << RPI << readData << std::endl;
#endif

    }

  }

#ifndef DEBUG
	serialPort.Close();
#endif

  return;
}


/**
 * ## Visual recognition listener routine
 * > void listenFlyEyes()
 *
 * Listen for an input in the /tmp/flyeyes FIFO
 * Then forwards it to the Arduino driver
 *
 * ### Parameters
 *
 * ### Returns
 */
void listenFlyEyes(){

	std::cout << INFO << "Listener for visual recognition started" << std::endl;
  
	char input[10];
	int fd;
	char input_buf[MAX_BUF];

#ifndef DEBUG
	// Create serial port object and open serial port
	SerialPort serialPort("/dev/ttyACM1", 115002);
	serialPort.SetTimeout(500); // Block when reading until any data is received
	serialPort.Open();
#endif

  for(;;) {

    fd = open("/tmp/flyeyes", O_RDONLY);
    read(fd, input_buf, MAX_BUF);
    close(fd);

    int i;
    for (i = 0; input_buf[i] != '\n'; i++){}input_buf[i] = 0;

    if (autopilot) {
#ifdef DEBUG
      std::cout << VISION << input_buf << std::endl;
#else
      serialPort.Write(input);
      std::string readData;
      serialPort.Read(readData);

      std::cout << RPI << readData << std::endl;
#endif
    }

  }

#ifndef DEBUG
	serialPort.Close();
#endif

  return;
}
