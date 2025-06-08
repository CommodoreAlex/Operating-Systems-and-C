#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h> // Needed for mkfifo

int main() {
    const char *fifo_path = "myfifo";
    int fd; // Creating the file descriptor handler

    // Create FIFO (ignore if it already exists)
    if (mkfifo(fifo_path, 0666) == -1) {
        perror("[Writer] mkfifo (may already exist)");
    } else {
        printf("[Writer] FIFO created.\n");
    }

    char *message = "Message from writer";

    printf("[Writer] Waiting to open FIFO...\n");
    fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("[Writer] open");
        return 1;
    }

    printf("[Writer] Writing to FIFO...\n");
    write(fd, message, strlen(message) + 1);
    close(fd);

    printf("[Writer] Done.\n");
    return 0;
}
