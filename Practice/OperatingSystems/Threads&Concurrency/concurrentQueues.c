#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Linked-list node for the queue
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Queue Structure
typedef struct Queue {
    Node* front;              // Points to the first node (where consumers remove items)
    Node* rear;               // Points to the last node (where producers add items)
    pthread_mutex_t lock;     // Prevent two threads from changing the queue at the same time
    pthread_cond_t not_empty; // A condition variable, allows the consumer thread to "sleep" if the queue is empty and "wake up" when data is added
} Queue;

// Initialize the queue: front, rear (both NULL), initializes mutex and condition variables too
Queue q = {NULL, NULL, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER}

// Enqueue: Add to the queue
void enqueue(int value) {
    Node* newNode = malloc(sizeof(Node));   // Dynamically creates a new node

    // Stores the value and sets 'next' to NULL (going at the back, so there's no one after it (yet))
    newNode->data = value;
    newNode->next = NULL;

    // Lock the queue while we're adding data
    pthread_mutex_lock(&q.lock);

    // Handles cases for empty queue and if not empty
    if (q.rear == NULL) {
        q.front = q.rear = newNode;
    } else {
        q.rear->next = newNode;
        q.rear = newNode;
    }

    pthread_cond_signal(&q.not_empty);  // Wake up any waiting consumers now that queue has data
    pthread_mutex_unlock(&q.lock);      // Unlock the queue so others can use it again
}

// Dequeue: Remove from the front
int dequeue() {

    pthread_mutex_lock(&q.lock);    // Lock the queue before reading or modifying it

    // If the queue is empty, thread sleeps and releases the lock
    // When enqueue signals new data it wakes up and re-acquires the lock
    while (q.front == NULL) {
        pthread_cond_wait(&q.not_empty, &q.lock);
    }

    Node* temp = q.front;       // Node being removed
    int value = temp->data;     // Stores the number we're returning
    q.front = q.front->next;    // Updated to the next node

    // If last node, update rear to reflect the queue is now empty again
    if (q.front == NULL) {
        q.rear = NULL;
    }

    // Free the memory used by the removed node, unlock queue, and return the stored value
    free(temp);
    pthread_mutex_unlock(&q.lock);
    return value;
}

// Producer thread: adds values 0-4 to the queue
void* producer(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Produced: %d\n", i);
        enqueue(i);
        sleep(1);
    }
    return NULL;
}

// Consumer thread: pulls values from the queue 5 times and prints them
void* consumer(void* arg) {
    for (int i = 0; i < 5; i++) {
        int val = dequeue();
        printf("Consumed: %d\n", val);
        sleep(2);
    }
    return NULL;
}

// Entry point and thread management
int main() {
    pthread_t t1, t2;

    pthread_create(&t1, NULL, producer, NULL);
    pthread_create(&t2, NULL, consumer, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
