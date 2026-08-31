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

    for (int i = 0; i < 5; i++) {
        arr[i] = rand() % 100;
        printf("Generated: %d\n", arr[i]);
    }

    /*
     * Open FIFO for writing first.
     * This waits until Program 2 opens it for reading.
     */
    int fd1 = open("sum", O_WRONLY);
    if (fd1 == -1) {
        perror("open");
        return 2;
    }

    if (write(fd1, arr, sizeof(arr)) == -1) {
        perror("write");
        close(fd1);
        return 3;
    }

    close(fd1);

    /*
     * Now open FIFO for reading.
     * Program 2 will write the sum after reading the array.
     */
    int fd2 = open("sum", O_RDONLY);
    if (fd2 == -1) {
        perror("open");
        return 4;
    }

    int sum;

    if (read(fd2, &sum, sizeof(sum)) == -1) {
        perror("read");
        close(fd2);
        return 5;
    }

    close(fd2);

    printf("Sum: %d\n", sum);

    return 0;
}