
#include "main.hpp"

#include <CppLinuxSerial/SerialPort.hpp>
#include "utils/rang.hpp"

using namespace mn::CppLinuxSerial;


/**
 * ## Main function 
 * > int main (int argc, char * argv)
 *
 * Entry point of the program
 *
 * ### Parameters
 * 	int argc :  number of parameters
 * 	char * argv : array of parameters
 *
 * ### Returns
 *	int : return 0 all the time
 */


#ifdef DEBUG

#include "debug/debug.hpp"

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#define MAX_BUF 1024


int main(int argc, char * argv[]) {

	std::cout << "Starting DEBUG MODE" << std::endl;

	// Get some ASCII data

	char input[10];

	int fd;

	char myfifo[] = "/tmp/myfifo";
	mkfifo(myfifo, 0666);

	char input_buf[MAX_BUF];


	for(;;) {

		fd = open(myfifo, O_RDONLY);
		read(fd, input_buf, MAX_BUF);
		close(fd);

		int i;
		for (i = 0; input_buf[i] != '\n'; i++){}input_buf[i] = 0;
		std::cout << RPI << input_buf << std::endl;
		
/*		input[1] = 0;
		std::cout << ARDUINO << input << std::endl;
*/
		
		// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	}
	
	std::cout << "End" << std::endl;
}






#elif defined TEST

int main(int argc, char * argv[]) {

	std::cout << "Starting" << std::endl;

	// Create serial port object and open serial port
	SerialPort serialPort("/dev/ttyACM1", 115002);

	serialPort.SetTimeout(500); // Block when reading until any data is received
	serialPort.Open();

	// Write some ASCII data

	char input[10];
	for(;;) {
		std::cout << "Dir > " ;
		std::cin >> input;
		
		input[1] = '\n';
		serialPort.Write(input);
		
		// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
		std::string readData;
		serialPort.Read(readData);

		std::cout << readData << std::endl;
	}
	

	// Close the serial port
	serialPort.Close();

	std::cout << "End" << std::endl;
}

#else

int main(int argc, char * argv[]) {

	std::cout << "Starting PROD MODE" << std::endl;

	// Create serial port object and open serial port
	SerialPort serialPort("/dev/ttyACM1", 115002);

	serialPort.SetTimeout(500); // Block when reading until any data is received
	serialPort.Open();

	// Write some ASCII data

	char input[10];
	for(;;) {
		std::cout << "Dir > " ;
		std::cin >> input;
		
		input[1] = '\n';
		serialPort.Write(input);
		
		// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
		std::string readData;
		serialPort.Read(readData);

		std::cout << readData << std::endl;
	}
	

	// Close the serial port
	serialPort.Close();

	std::cout << "End" << std::endl;
}

#endif