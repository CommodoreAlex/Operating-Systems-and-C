#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>   // Threading
#include <semaphore.h> // Semaphores (POSIX API)
#include <unistd.h>    // Sleep

// This program demonstrates the use of binary semaphores (a.k.a mutex-like)
// Semaphores are like traffic lights for shared resources, they control when a thread is allowed to proceed, making sure
// no two threads collide at the same critical junction

// Declare global sempahore variable
sem_t semaphore;

// Thread entry point function to acquire the semaphore
void* worker(void* arg) {

	// Extract the threads identifier passed via the pthread_create() call to help distinguis threads
	int id = *(int*)arg;

	printf("Thread %d: Waiting to enter critical section...\n", id);
	sem_wait(&semaphore);  // Acquire semaphore (Decrement)

	printf("Thread %d: Inside critical section.\n", id);
	sleep(2);  // Simulate work by sleeping for 2 seconds

	printf("Thread %d: Leaving critical section.\n", id);
	sem_post(&semaphore);  // Release semaphore (increment)

	return NULL;
}

int main() {

	// Define three thread variables and give each a unique ID to pass to worker()
	pthread_t threads[3];
	int thread_ids[3] = {1, 2, 3};

	// Initialize semaphore with initial value 1 (binary semaphore)
	if (sem_init(&semaphore, 0, 1) != 0) {  // 0 means the semaphore is used for threads, not inter-process. 1 thread at a time may enter critical section
		perror("sem_init failed");
		exit(EXIT_FAILURE);
	}

	// Create threads (iterate to create all 3)
	for (int i = 0; i < 3; i++) {
		pthread_create(&threads[i], NULL, worker, &thread_ids[i]);
	}

	// Join threads (wait for completion)
	for (int i = 0; i < 3; i++) {
		pthread_join(threads[i], NULL);
	}

	// Destroy semaphore (release any resources)
	sem_destroy(&semaphore);

	return 0;
}
