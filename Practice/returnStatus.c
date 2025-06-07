#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

// An example that demonstrates the timeline of creation to exit, exchanging exit information between processes
// ┌──(root㉿kali)-[/home/kali/C/Class]
// └─# ./status 
// Child process running...
// Child exited with status 42

int main() {

	// Creating a child and parent process
	pid_t pid = fork();

	if (pid == 0) {
		printf("Child process running...\n");
		sleep(2);  // Pauses execution for 2 seconds
		return 42; // Passing status '42' to the parent process
	} else {
		// Stores the child process exit status '42'
		int status;
		waitpid(pid, &status, 0); // Waits for child process to finish, status captures the exit information

		// "WIFEXITED(status) checks if the child terminated normally"
		if (WIFEXITED(status)) {
			// WEXITSTATUS extracts the exit status 42 from return 42
			printf("Child exited with status %d\n", WEXITSTATUS(status));
		}
	}

	// Program termination and both processes exit, parent finishes after child process exit status
	return 0;
}
