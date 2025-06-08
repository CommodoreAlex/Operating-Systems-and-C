#include <fcntl.h>  // Assigning levels of permission
#include <unistd.h> // Access POSIX
#include <stdio.h>  // Basic I/O

// Low-Level I/O: open, read, write

int main() {

	// Creating a file opening handler (fd), creating the filename. The 0644 permissions (owner can read/write; others can only read)
	// O_WRONLY (Open the file in write-only mode) | O_CREAT (if does not exist, create) | O_TRUNC (if file exists it is truncated, clear previous contents)
	int fd = open("lowlevel.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

	// Error handler
	if (fd < 0) {
		perror("open failed");
		return 1;
	}

	// Creating a constnat char pointer 'msg' with our message
	const char *msg = "Low-level write\n";

	// Sending 16 bytes from msg into "lowlevel.txt"
	write(fd, msg, 16);

	// Closing teh file, ensuring all data is flushed
	close(fd);

	// Opening the file in read-only mode (O_RDONLY)
	fd = open("lowlevel.txt", O_RDONLY);

	// Create a character array buffer to temporarily store file contents when reading data
	// Acts as a storage for the read() function to place retrieved data from the file
	char buffer[100];

	// Read from the file associated with file descriptor (fd): 
	// We do sizeof(buffer)-1) to read up to 99 bytes, leaving space for the null terminator (\0)
	int bytes = read(fd, buffer, sizeof(buffer)-1);

	// Null-Terminating the Buffer, ensures the data in buffer is properly terminated as a valid C string
	buffer[bytes] = '\0';

	// Displaying the read content
	printf("Read: %s", buffer);

	// Closing the file handler and exiting the program
	close(fd);
	return 0;
}
