#include <stdio.h>
#include <fcntl.h>  // File Control Definitions, providing open()
#include <unistd.h> // POSIX Operating System API, allowing access to write() and close()
#include <string.h> // String Manipulation Functions, enabling operations like strlen()

// Using Named Pipes (FIFO)

int main() {

	// Initialize the file descriptor (handler for I/O)
	int fd;

	// Creating a constant pointer to our message
	const char *message = "Message from writer";

	fd = open("myfifo", O_WRONLY);			 // Open the file in write-only mode (O_WRONLY)
	write(fd, message, strlen(message) + 1); // Writing with fd (handler, message, length of message + 1 for null-terminator \0) 
	close(fd);

	return 0;
}
