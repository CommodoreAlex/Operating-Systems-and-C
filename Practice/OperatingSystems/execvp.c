#include <stdio.h>
#include <unistd.h> // Contains system calls for memory management

// Child replaces itself with a new program image (e.g. ls), executing with execvp() - System Call practice
// Example output:
// Parent process continues
// total 36
// -rwxr-xr-x 1 root root 16160 Jun  7 00:16 fork
// -rw-r--r-- 1 root root   696 Jun  7 00:22 fork_basics.c
// -rwxr-xr-x 1 root root 16112 Jun  7 00:22 replace

int main() {

	// fork() creates a parent and child process, referenced by 'pid'
	pid_t pid = fork();

	// This getsevalauted independently, both will eventually run
	if (pid == 0) { // 0 = child process
		char *args[] = { "ls", "-l", NULL }; // Creates an array to store cmdline arguments
		execvp("ls", args); 				 // Replace child process with the 'ls' command, process never returns, it gets REPLACED.
		perror("execvp failed");			 // Error handling if execvp() fails
	} else {
		// This does not stop the parent from running like typical if-else statements.
		// Does not wait in lieu of not wait() being called, parent will keep executing rather than wait for child process to finish
		printf("Parent process continues\n"); 
	}

	return 0;
}
