#include <pthread.h>
#include <stdio.h>

#define NUM_THREADS 4
#define NUM_ITERATIONS 1000000

// Shared variable 64-bit integer
long long counter = 0;

// A 'mutex' (Mutual Execlusion Lock), ensuring only one thread modifies counter at a time
pthread_mutex_t lock;

void* increment_counter(void* arg) {
	for (int i = 0; i < NUM_ITERATIONS; ++i) {
		pthread_mutex_lock(&lock);     // Acquire lock before modifying counter
		counter ++;					   // Critical section (modifies shared counter)
		pthread_mutex_unlock(&lock);   // Release lock, allow other threads to proceed
	}
	return NULL;
}

int main() {

	pthread_t threads[NUM_THREADS];   // Declare an array to store thread identifiers
	pthread_mutex_init(&lock, NULL);  // Initialize the mutex with default attributes (NULL)

	// The number of threads to create, pointing to our function
	for (int i = 0; i < NUM_THREADS; ++i) {
		pthread_create(&threads[i], NULL, increment_counter, NULL);
	}

	// Wait for all threads to complete executing
	for (int i = 0; i < NUM_THREADS; ++i) {
		pthread_join(threads[i], NULL);
	}

	// This will print the correct 4,000,000 operations, due to no race-condition via shared variable modification simultaneously
	printf("Final counter value: %lld\n", counter);
	pthread_mutex_destroy(&lock);  // Cleanup when done
	return 0;
}
