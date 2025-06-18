#include <stdio.h>
#include <stdlib.h>     // Memory / Utilities
#include <pthread.h>    // POSIX threads
#include <stdatomic.h>  // Atomic operations for thread-safe counters

// A ticket lock is a spinlock mechanism- ensures threads acquire the lock in the order they requested it

typedef struct {
    atomic_int ticket;  // next ticket number to hand out
    atomic_int turn;    // current ticket being served
} ticket_lock_t;

// Lock initialization (initialize atomic counters of the lock to 0)
void ticket_lock_init(ticket_lock_t *lock) {
    atomic_init(&lock->ticket, 0);

    // Every thread will call ticket_lock_acquire() to get a ticket and wait their turn
    atomic_init(&lock->turn, 0);
}

// Atomically increases the ticket and stores the thread's spot in line as my_ticket (thread unique queue number)
void ticket_lock_acquire(ticket_lock_t *lock) {
    int my_ticket = atomic_fetch_add(&lock->ticket, 1);

    // Thread keeps checking whether it's their to enter the critical section
    while (atomic_load(&lock->turn) != my_ticket) {
        // spin-wait
    }
}

// When finished, increment turn, signal next waiting thread (one with ticket) to proceed
void ticket_lock_release(ticket_lock_t *lock) {
    atomic_fetch_add(&lock->turn, 1);
}

// Each thread runs this function -> Acquires hte lock, does its work (prints), then releases the lock
ticket_lock_t lock;

void* worker(void* arg) {
    ticket_lock_acquire(&lock);
    printf("Thread %ld in critical section\n", (long)arg);
    ticket_lock_release(&lock);
    return NULL;
}


int main() {

    // Declares 5 thread handles and initializes the ticket lock
    pthread_t threads[5];
    ticket_lock_init(&lock);

    // Launch 5 threads, each get a unique ID as an argument (see (void*)i)
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, worker, (void*)i);
    }

        /// Wait for all threads to finish before exiting
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
