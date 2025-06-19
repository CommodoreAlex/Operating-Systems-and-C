#include <stdio.h>

int box;    // global variable

// Switches box to the parameter value
void put(int value) {
    box = value;
}

// Returns the value of box
int get() {
    return box;
}

// Basic routine
int main() {
    put(42);
    printf("Value: %d\n", get());   // Output: 42
    return 0;
}
