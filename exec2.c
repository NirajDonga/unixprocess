#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>

int main(int argc, char* argv[]) {

    int pid = fork();
    if(pid == -1) {
        return 1;
    }

    if(pid == 0) {

        int file = open("pingresults.txt", O_WRONLY | O_CREAT, 0777);
        if(file == -1) {
            return 2;
        }

        // file descriptor 0 -> stdin, 1 -> stdout, 2 -> stderr, 3 -> pingresults.txt
        // it close stdout(1) file descriptor completly and open it again to our pingresults.txt .
        int file2 = dup2(file, STDOUT_FILENO);
        close(file);

        // child process gets replaced by ping.
        int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
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