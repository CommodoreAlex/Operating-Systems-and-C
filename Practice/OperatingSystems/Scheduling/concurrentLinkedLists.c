#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Concurrent Linked Lists

// We can write Node* instead of struct Node*
typedef struct Node {
    int data;           // Holds the integer value
    struct Node* next;  // Points to the next node in the list (or NULL if it's the last one)
} Node;

// Global head pointer for the list, initially NUL (empty)
Node* head = NULL;
// Requires thread protection (locking) since multiple threads access it
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

// Inserting into the concurrent linked list
void insert(int value) {
    pthread_mutex_lock(&lock);  // Acquire lock

    // Cast it to Node* so we can treat it like a node right away
    Node* newNode = (Node*)malloc(sizeof(Node));    // Allocates enough space in memory for a new node

    newNode->data = value;  // Stores the value the thread wants to insert
    newNode->next = head;   // Makes this new node point to the current head node (even if head is NULL)
    head = newNode;         // Updates the head pointer to point to this new node- now it's the first one in the list

    pthread_mutex_unlock(&lock);    // Release lock
}

// Thread entry point (return type is void* because that is what pthread_create() expects)
void* thread_func(void* arg) {
    int val = *(int*)arg;   // Receives a pointer to an int as an argument, so we cast and dereference it for the actual number
    insert(val);            // Calls insert() with that value 
    return NULL;            // Returns NULL to signal the end of the thread
}

// Printing the list
void printList() {
    // Start from the head node
    Node* temp = head;

    // Keep walking down the list, printing each value followed by an arrow
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");   // Marks the end of the list, example: 40 -> 30 -> 20 -> 10 -> NULL
}

int main() {

    // Declaration of thread count and values to insert
    pthread_t threads[4];
    int vals[4] = {10, 20, 30, 40};

    // Creating threads
    for (int i = 0; i < 4; i++) {
        pthread_create(&threads[i], NULL, thread_func, &vals[i]);
    }

    // Joining (wait to finish)
    for (int i = 0; i < 4; i++) {
        pthread_join(threads[i], NULL);
    }

    // Print our data and exit program
    printList();
    return 0;
}
