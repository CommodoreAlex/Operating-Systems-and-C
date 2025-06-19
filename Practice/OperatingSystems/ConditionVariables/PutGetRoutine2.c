#include <stdio.h>

int data[100];  // Pretend this is our data store

void put(int index, int value) {
    data[index] = value;
}

int get(int index) {
    return data[index];
}

// Simple put and get scenario with Arrays
int main() {
    put(10, 99);
    put(3, 42);

    printf("At 10: %d\n", get(10));  // Output: 99
    printf("At 3: %d\n", get(3));    // Output: 42
    return 0;
}
