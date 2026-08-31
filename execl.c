#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char* argv[]) {

    char *args[] = {"ping", "google.com", NULL};
    char *args2[] = {"ping", "google.com", NULL};

    // path, name, arguments, null
    // use p then no path. automatic default path for direct processes.
    execl("/usr/bin/ping", "ping", "google.com", NULL);
    execv("/usr/bin/ping", args);
    execlp("ping", "ping", "google.com", NULL);
    execvp("ping", args2);


    // this wont be printed
    printf("ping successfull");

    return 0;   
}