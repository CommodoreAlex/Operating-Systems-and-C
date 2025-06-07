#include <stdio.h> // I/O headres (printf,perror)
#include <unistd.h> // Fork() for process creation
#include <sys/types.h> // Types like pid_t (process IDs)

// Example output to learn process creation
// Parent: My PID is 12345, I created child PID 12346
// Child: My PID is 12346, Parent PID is 12345

int main() {
	// Creates a new child process, pid helps distinguish between parent and child
	pid_t pid = fork();


	if (pid < 0) {
		// Process creation failed (not enough resources if less than 0 is returned)
		perror("fork failed");
		return 1;
	} else if (pid == 0) {
		// Child process block- getpid() for child's process ID, getppid() for parent's process ID
		printf("Child: My PID is %d, Parent PID is %d\n", getpid(), getppid());
	} else {
		// Parent process is greater than 0. Fetch that PID and return child process ID vai fork()
		printf("Parent: My PID is %d, I created child PID %d\n", getpid(), pid);
	}

	return 0;
}
