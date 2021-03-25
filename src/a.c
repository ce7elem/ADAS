#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
  
int main(int argc, char * argv[]){
  if (argc != 2) return 0;
    int fd;
  
    // Creating the named file(FIFO)
    // mkfifo(<pathname>, <permission>)
    //mkfifo(argv[1], 0666);
  
    char arr1[80], arr2[80];
    while (1)
    {
        // Open FIFO for write only
        fd = open(argv[1], O_WRONLY);
  
        // Take an input arr2ing from user.
        // 80 is maximum length
        fgets(arr2, 80, stdin);
  
        // Write the input arr2ing on FIFO
        // and close it
        write(fd, arr2, strlen(arr2)+1);
        close(fd);
    }
    return 0;
}
