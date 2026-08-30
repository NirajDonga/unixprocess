#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main() {

    int fd[2];
    // fd[0] - read
    // fd[1] - write

    if(pipe(fd) == -1) {
        printf("An Error occured with opening file");
        return 1;
    }   

    // parent process waits for data from pipe and keep executing. just like go routine.

    int id = fork();
    if(id == 0) {
        close(fd[0]);
        int x;
        printf("Input Number: ");
        scanf("%d", &x);
        if(write(fd[1], &x, sizeof(int)) == -1) {
            printf("An Error occured with writing to the file");
            return 2;
        }
        close(fd[1]);    
    }
    else {
        close(fd[1]);
        int y;
        if(read(fd[0], &y, sizeof(int)) == -1) {
            printf("An Error occured with reading to the file");
            return 3;
        }
        y = y * 3;
        close(fd[0]);
        printf("got from child process %d \n", y);
    }


    return 0;   
}