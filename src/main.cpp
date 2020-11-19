#include "main.hpp"

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

int main(int argc, char * argv) {

	std::cout << "Starting" << std::endl;

	// Create serial port object and open serial port
	SerialPort serialPort("/dev/ttyARDUINO", BaudRate::B_57600);

	serialPort.SetTimeout(-1); // Block when reading until any data is received
	serialPort.Open();

	// Write some ASCII datae
	serialPort.Write("ping");

	// Read some data back (will block until at least 1 byte is received due to the SetTimeout(-1) call above)
	std::string readData;
	serialPort.Read(readData);

	// Close the serial port
	serialPort.Close();

	std::cout << "End" << std::endl;
}