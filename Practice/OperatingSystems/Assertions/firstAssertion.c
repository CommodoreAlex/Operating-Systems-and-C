#include <stdio.h>
#include <assert.h>

int divide(int a, int b) {
    assert(b != 0); // Make sure we're not dividing by zero
    return a / b;
}

int main() {
    printf("%d\n", divide(10, 2));  // Okay
    printf("%d\n", divide(10, 0));  // Assertion fails
    return 0;
}

