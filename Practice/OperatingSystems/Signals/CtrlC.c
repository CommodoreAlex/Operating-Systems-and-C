#include <stdio.h>
#include <signal.h>
#include <unistd.h>

// Custom signal handler
void handle_sigint(int sig) {
	printf("\nCaught signal %d (SIGINT). Exiting gracefully.\n", sig);
	_exit(0);	// Use _exit to avoid flushing stdio buffers
}

int main() {

	// Register signal handler
	signal(SIGINT, handle_sigint);

	// Infinite loop to keep program running
	while (1) {
		printf("Running... Press Ctrl+C to stop.\n");
		sleep(1);
	}

	return 0;
}
