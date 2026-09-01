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
        int err = execlp("ping", "ping", "-c", "3", "google.con", NULL);
        if(err == -1) {
            printf("could not find program to execute \n");
            return 2;   
        }

        // this should not be printed in successfull run.
        printf("success\n");
    }
    else {
        int wtstatus;
        wait(&wtstatus);
        if(WIFEXITED(wtstatus)) {
            int statuscode = WEXITSTATUS(wtstatus);
            if(statuscode == 0) {
                printf("Success \n");
            }
            else {
                printf("Failure \n");
            }
        }

        printf("post processing \n");
    }

    return 0;   
}