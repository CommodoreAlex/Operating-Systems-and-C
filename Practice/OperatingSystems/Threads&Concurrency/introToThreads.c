#include <pthread.h> // Includes POSIX threads library for pthreads for multithreading
#include <stdio.h>

// Define a function that will execute in the newly created thread
void* thread_func(void* arg) {
	printf("Hello from thread! arg = %s\n", (char*)arg); // Casts arg to char* to print it as a string
	return NULL; // Threads should return NULL unless they return a meaningful result
}

// The thread_func function starts running in parallel with main() but execution depends on scheduling by the OS
int main() {
	// Declare a variable of type pthread_t, representing a thread
	pthread_t thread;
	const char* message = "Thread 1"; // Creating a constant pointer to our message

	// pthread_create: System call that launches a new thread
	// &thread: Passes the pthread_t variable by reference, allowing the OS to store the thread ID
	// NULL: uses default thread attributes (e.g. scheduling policies, stack size)
	// thread_func: function the thread will execute
	// (void*)message: converts the message pointer into a void* for compatability
	pthread_create(&thread, NULL, thread_func, (void*)message);

	// pthread_join() blocks execution of main() until thread completes. Prevents premature termination of main().
	pthread_join(thread, NULL); // The thread to wait for, no return value is needed from the thread (NULL)

	printf("Back in the main thread\n");
	return 0;
}
