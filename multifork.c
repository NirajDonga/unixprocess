#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<sys/wait.h>
#include<errno.h>

int main() {
    
    /*
        parent process 
           /     \
           x     z
           |
           y
    */

    int id1 = fork();
    int id2 = fork();

    // wait(NULL) stops waiting if one child process completes. buut we ned it to wait for all child processes.
    
    while(wait(NULL) != -1 || errno != ECHILD);

    if(id1 == 0) {
        if(id2 == 0) {
            printf("we are process y \n");
        }
        else {
            printf("we are process x \n");
        }
    }
    else {
        if(id2 == 0) {
            printf("we are process z \n");
        }
        else {
            printf("we are parent process \n");
        }
    }


    return 0;   
}