#include <stdio.h>      // For input/output functions like printf()
#include <stdlib.h>     // For dynamic memory functions like malloc(), free(), and NULL
#include <string.h>     // Optional: useful if string keys are added later (e.g., strcmp, strcpy)

#define BUCKETS (101)   // Number of buckets in the hash table (prime number helps reduce collisions)

// Define the hash table structure, using separate chaining
typedef struct __hash_t {
    list_t lists[BUCKETS];  // Each bucket is a linked list to handle collisions
} hash_t;

// Initializes each linked list in the hash table
void Hash_Init(hash_t *H) {
    for (int i = 0; i < BUCKETS; i++) {
        List_Init(&H->lists[i]);  // Initialize each bucket's list
    }
}

// Inserts a key into the appropriate bucket, based on its hash
int Hash_Insert(hash_t *H, int key) {
    int index = key % BUCKETS;           // Compute which bucket to use
    return List_Insert(&H->lists[index], key);  // Insert the key into the bucket’s list
}

// Looks up a key by searching the appropriate bucket
int Hash_Lookup(hash_t *H, int key) {
    int index = key % BUCKETS;                 // Compute which bucket the key would be in
    return List_Lookup(&H->lists[index], key); // Search for the key in the corresponding list
}
