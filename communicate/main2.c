#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int main() {
    if (mkfifo("sum", 0777) == -1) {
        if (errno != EEXIST) {
            perror("Could not create FIFO");
            return 1;
        }
    }

    int arr[5];

    /*
     * Open FIFO for reading first.
     * This waits until Program 1 opens it for writing.
     */
    int fd1 = open("sum", O_RDONLY);
    if (fd1 == -1) {
        perror("open");
        return 2;
    }

    if (read(fd1, arr, sizeof(arr)) == -1) {
        perror("read");
        close(fd1);
        return 3;
    }

    close(fd1);

    int sum = 0;

    for (int i = 0; i < 5; i++) {
        sum += arr[i];
    }

    printf("Calculated sum: %d\n", sum);

    /*
     * Open FIFO for writing and send the sum back.
     */
    int fd2 = open("sum", O_WRONLY);
    if (fd2 == -1) {
        perror("open");
        return 4;
    }

    if (write(fd2, &sum, sizeof(sum)) == -1) {
        perror("write");
        close(fd2);
        return 5;
    }

    close(fd2);

    return 0;
}