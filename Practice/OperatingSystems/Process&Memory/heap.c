#include <stdio.h>
#include <stdlib.h>  // Includes malloc() and free()
#include <unistd.h>  // Gives access to sbrk() which modifies the heap

// Example output:
// Heap start: 0x5564f2cda000
// Heap end after malloc: 0x5564f2cfb000

int main() {
	// sbrk(0) returns the current break address, marking the heap boundary
	// This tells us where the heap starts before any allocation, the pointer is printed in hexadecimal format %p
	void *start = sbrk(0);
	printf("Heap start: %p\n", start);

	// Allocating memory dynamically, the OS extends the heap to provide space for this allocation
	// returns a pointer *mem to the allocated memory block
	void *mem = malloc(1024 * 1024); // 1 MB

	// Calling sbrk(0) again to show the new heap boundary. Start vs end represents the heap expansion
	void *end = sbrk(0);
	printf("Heap end after malloc: %p\n", end);

	// Deallocates the previously allocated 1MB to allow OS to reclaim memory for reuse
	// sbrk() does not shrink, so the heap boundary remains unchanged.
	free(mem);
	return 0;
}
