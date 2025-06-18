#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Example of a counter without locks

// Creating a structure for a counter
typedef struct __counter_t {
    int value;
} counter_t;

// Initialize the counter
void init(counter_t *c) {
    c->value = 0;
}

// Increment the counter
void increment(counter_t *c) {
    c->value++;
}

// Decrement the counter
void decrement(counter_t *c) {
    c->value--;
}

// Get the value of counter
int get(counter_t *c) {
    return c->value;
}
