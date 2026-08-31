#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc, char* argv[]) {

    int pid = fork();
    if(pid == -1) {
        return 1;
    }

    if(pid == 0) {
        // child process gets replaced by ping.
        execlp("ping", "ping", "-c", "3", "google.com", NULL);
        
        // this should not be printed.
        printf("success\n");
    }
    else {
        wait(NULL);
        printf("post processing \n");
    }

    return 0;   
}