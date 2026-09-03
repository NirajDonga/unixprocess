#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
#include<signal.h>

int main(int argc, char* argv[]) {

    int pid = fork();
    if(pid == -1) {
        return 1;
    }

    if(pid == 0) {
        while(1) {
            printf("some text goes here \n");
            usleep(1000000); // 1 second
        }
        
    }
    else {
        sleep(1);
        kill(pid, SIGKILL);
        wait(NULL);
    }

    return 0;   
}