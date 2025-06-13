#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

// Interrupt handler (e.g. triggered by CTRL+C)
void interrupt_handler(int signum) {

	printf("Interrupt received! Handling it now...\n");
	exit(0);
}

// Trap example (division by zero)
int trap_example() {

	int x = 5;
	int y = 0;
	return x / y; // This will cause a trap (division by zero)
}

int main() {

	// Register interrupt handler for SIGINT (Ctrl+C)
	signal(SIGINT, interrupt_handler);

	printf("Press Ctrl+C to trigger an interrupt...\n");

	// Uncomment the next line to trigger a trap
	// int result = trap_example();
	
	while (1); // Infinite loop to keep the program running
	return 0;
}
