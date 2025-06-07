#include <pthread.h>
#include <stdio.h>

// Preprocessor directives- to define constants before compilation
#define NUM_THREADS 4
#define NUM_ITERATIONS 1000000

// Demonstrating a race condition: When multiple threads access and modify the same shared variable without synchronization, the result is unpredictable and unsafe.

long long counter = 0; // Shared variable (64-bit integer to accomodate large values)

void* increment_counter(void* arg) {
	// Should run 1,000,000 times per thread
	for (int i = 0; i < NUM_ITERATIONS; i++) {
		counter++; // NOT thread-safe: many threads modify counter simultaneously, the increments can interfere with each other (race-condition - requires mutx() to fix)
	}
	return NULL;
}

int main() {
	// Creating an array of pthread_t objects to manage NUM_THREADS threads
	pthread_t threads[NUM_THREADS];

	// Creating 4 threads that will execute concurrently
	for (int i = 0; i < NUM_THREADS; i++) {
		// Pass reference to the ith thread, using default attributes, call increment_counter function, no arguments are passed
		pthread_create(&threads[i], NULL, increment_counter, NULL);
	}

	// Waiting for all threads to finish, referencing the ith thread
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_join(threads[i], NULL);
	}

	printf("Final counter value: %lld\n", counter); // Expected: 4,000,000 if perfectly synchronized, reality of race-conditions-> probably incorrect due to overlapping operations
	return 0;
}
