#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

#include<sys/stat.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>

int main() {
    if(mkfifo("myfifo1", 0777) == -1) {
        if(errno != EEXIST) {
            printf("Could not create fifio file");
            return 1;
        }
    }

    int fd = open("myfifo1", O_WRONLY);
    int x = 99;

    /*
        This write blocks the execution untill any other process read from the file. 
        try cat myfifo1 in other terminal and it will end executing.
    */
    if(write(fd, &x, sizeof(x)) == -1) {
        return 2;
    }
    
    close(fd);

    
    return 0;   
}