#include <stdio.h>
#include <stdatomic.h>	// Introduces atomic types like atomic_flag (C11 Standard)
#include <pthread.h>	// POSIX threads for multithreading
#include <unistd.h>		// Provides functions like sleep() (optional here but common in concurrency testing).

// Constants to control the number of threads and how many times each thread will increment a shared counter
#define NUM_THREADS 4
#define INCREMENTS_PER_THREAD 100000

// Spinlock Structure
typedef struct {

	// Boolean atomic type, guaranteed to be lock-free. Supports test_and_set and clear.
	atomic_flag locked;
} spinlock_t;

// Initialize the spinlock
void spinlock_init(spinlock_t *lock) {
	atomic_flag_clear(&lock->locked);
}

// Acquire the spinlock
void spinlock_lock(spinlock_t *lock) {
	while (atomic_flag_test_and_set(&lock->locked)) {
		// Busy Wait
	}
}

// Release the spinlock
void spinlock_unlock(spinlock_t *lock) {
	atomic_flag_clear(&lock->locked);
}

long counter = 0;
spinlock_t my_lock;

void* increment(void* arg) {
	for (int i = 0; i < INCREMENTS_PER_THREAD; i++) {
		spinlock_lock(&my_lock);
		++counter;
		spinlock_unlock(&my_lock);
	}
	return NULL;
}

int main() {

	pthread_t threads[NUM_THREADS];

	spinlock_init(&my_lock);

	// Create Thrads
	for (int i = 0; i < NUM_THREADS; i++) {
		pthread_create(&threads[i], NULL, increment, NULL);
	}

	// Waits for threads to finish
	for (int i = 0; i < NUM_THREADS; ++i) {
		pthread_join(threads[i], NULL);
	}

	printf("Final counter value: %ld\n", counter);
	return 0;
}
