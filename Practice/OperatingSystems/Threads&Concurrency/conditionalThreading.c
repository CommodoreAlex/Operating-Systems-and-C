#include <pthread.h>  // Provides threading functions
#include <stdio.h>    // Standard I/O functions
#include <unistd.h>   // Sleep function for simulating delays

int buffer = 0;      // Shared data
int buffer_full = 0; // Flag to indicate if buffer has data

pthread_mutex_t lock; // Mutex for synchronization
pthread_cond_t cond;  // Condition variable for signaling between producer and consumer

// Producer thread that creates data and stores it in the buffer
void* producer(void* arg) {

	for (int i = 1; i <= 5; i++) {
		sleep(1); // Simulate production time

		pthread_mutex_lock(&lock); // Lock to allow one thread at a time to shared variable

		// Waits for consumer to consume the data
		while (buffer_full) {
			pthread_cond_wait(&cond, &lock); // Wait until buffer is empty
		}

		buffer = i;
		buffer_full = 1;
		printf("Produced: %d\n", buffer);

		pthread_cond_signal(&cond);  // Signal the consumer (wakes up one thread waiting on the condition)
		pthread_mutex_unlock(&lock); // Unlock the variable
	}
	return NULL;
}

// Consumer thread that simulates a consumer that retrieves data from buffer
void* consumer(void* arg) {

	for(int i = 1; i < 5; i++) {

		pthread_mutex_lock(&lock); // Lock to allow one thread at a time to shared variable

		while (!buffer_full) {
			pthread_cond_wait(&cond, &lock); // Wait until buffer is full
		}

		printf("Consumed: %d\n", buffer);
		buffer_full = 0;

		pthread_cond_signal(&cond);  // Signal the producer
		pthread_mutex_unlock(&lock); // Unlock the variable

		sleep(1); // Simulate processing time
	}
	return NULL;
}

int main() {
	// Declare threading variables for producer and consumer
	pthread_t prod, cons;

	// Initialize the mutex and condition variables
	pthread_mutex_init(&lock, NULL);
	pthread_cond_init(&cond, NULL);

	// Thread creation
	pthread_create(&prod, NULL, producer, NULL);
	pthread_create(&cons, NULL, consumer, NULL);

	// Wait for these to finish completing
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	// Destroy the mutex and condition variable to free resources
	pthread_mutex_destroy(&lock);
	pthread_cond_destroy(&cond);

	return 0;

}
