#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd;
    char buffer[100];

    printf("[Reader] Waiting to open FIFO...\n");
    fd = open("myfifo", O_RDONLY);
    printf("[Reader] FIFO opened. Waiting to read...\n");
    read(fd, buffer, sizeof(buffer));
    printf("[Reader] Received: %s\n", buffer);
    close(fd);
    return 0;
}
