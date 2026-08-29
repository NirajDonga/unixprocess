#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
    int id = fork();
    // wait(NULL);

    // this makes child process sleeps so that parent terminate before print statement. 
    // new parent has been assigned to child process because old terminates.
    if(id == 0) { 
        sleep(1);
    }

    printf("Current ID: %d, parent ID: %d \n", getpid(), getppid());
    


    return 0;   
}