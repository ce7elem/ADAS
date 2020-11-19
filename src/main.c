#include <stdio.h>
#include <stdlib.h>
#include "./src1/f1.h"
#include "./src2/f2.h"
#include "./src2/subsrc1/f3.h"


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

	printf("\033[1;33m");	//set term output color in yellow
    printf("%s\n", f1() );		// print the heads
    printf("%s\n", f2() );
    printf("%s\n", f3() );
	printf("\033[0m\n");	// reset default term color

    return 0;
}