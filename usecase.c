#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>


int main() {

    int arr[] = {1, 2, 3, 4, 1, 2};
    int arrsize = sizeof(arr) / sizeof(int);
    int start, end;
    int fd[2];

    if(pipe(fd) == -1) {
        return 1;
    }

    int id = fork();
    if(id == -1) {
        return 2;
    }

    if(id == 0) {
        start = 0;
        end = arrsize / 2;
    }
    else {
        start = arrsize / 2;
        end = arrsize;
    }

    int sum = 0;
    int i;
    for(i = start; i < end; i++) {
        sum += arr[i];
    }

    printf("calculated sum: %d \n", sum);   

    if(id == 0) {
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    }
    else {
        int y;
        close(fd[1]);
        read(fd[0], &y, sizeof(y));
        close(fd[0]);

        int tsum = sum + y;
        printf("Toal sum: %d \n", tsum);
        // wait(NULL); 
    }

    return 0;   
}