
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <thread>

#include "main.hpp"
#include "controllers.hpp"
#include "utils/rang.hpp"

/**
 * ## Main function 
 * > int main (int argc, char * argv)
 *
 * Entry point of the program
 * Starts two threads :
 *  - a listener for the remote controller
 *  - a listener for the FLYEYES3000 visual detection
 *
 * ### Parameters
 *
 * ### Returns
 *	int : return 0 all the time
 */
int main(int argc, char * argv[]) {

  system("rm /tmp/rcontroller /tmp/flyeyes 2> /dev/null");
	mkfifo("/tmp/rcontroller", 0666);
	mkfifo("/tmp/flyeyes", 0666);

  std::thread rcTread (listenRController);
  sleep(1);
  std::thread flyEyesTread (listenFlyEyes);

  rcTread.join();                // pauses until first finishes
  flyEyesTread.join(); 
  
	std::cout << "End" << std::endl;

  return 0;
}
