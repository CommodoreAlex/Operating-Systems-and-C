#include <unistd.h>
#include <stdio.h>  // Provides system call functions like pipe(), fork(), read(), write()
#include <string.h>

// Inter-Process Communication with Pipes: connects STDOUT of one process to STDIN of another, or lets related processes share data: UNIDIRECTIONAL

int main() {

	int fd[2];			// Declaring a file descriptor array for pipe ends
	pid_t pid;			// Declare a variable to store the process ID 
	char buffer[100];	// Temporary storage for data received from the pipe

	// Creating a pipe that allows two related processes to exchange information
	pipe(fd);

	// fork() creates a new child process, assigning PID to its pid
	pid = fork();

	if (pid == 0) {								// When 0 child process reads from pipe
		close(fd[1]);                           // Close write end
		read(fd[0], buffer, sizeof(buffer));    // Receive data from fd[0] (pipe's read end)
		printf("Child received: %s\n", buffer); // Display the received message
		close(fd[0]);                           // Close read end
	} else { 									// When anything else, parent process reads to pipe
		close(fd[0]); 							// Close read end since the parent only writes
		char msg[] = "Hello from parent!";      // Defines the message to send
		write(fd[1], msg, strlen(msg) + 1);		// Writes message to pipe, ensuring null-terminator is at end also
		close(fd[1]);							// Close write end
	}

	// Exit
	return 0;
}
