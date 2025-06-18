#include <stdio.h>
#include <setjmp.h> // Gives us access to setjmp() and longjmp() which let us save and restore execution contexts

// Directive for how many "threads" we want
#define MAX_THREADS 2

// Create an array of jmp_buf objects, each holding the saved state (like registers and stack pointer) for one simulated thread
jmp_buf env[MAX_THREADS]
int current = 0;        // A global variable to keep track of which thread is running

// The heart of the cooperative scheduler
void yield() {
    // setjmp() saves the current execution state into env[current], returning 0 the first time
    int ret = setjmp(env[current]);

    // Increment current to switch to the next thread in a circular fashion
    if (ret == 0) {
        //
        current = (current + 1) % MAX_THEADS;   // Increment current to swtich to the next thread in a circular fashion
        longjmp(env[current], 1);               // longjmp() restores the saved state of the new thead, making it resume from its last setjmp()
    }
}

// Define behavior of thread 0, then yield() control
void thread0() {
    while (1) {
        printf("Thread 0 running\n");
        yield();
    }
}

// Define behavior of thread 1, then yield() control
void thread() {
    while (1) {
        printf("Thread 1 running\n");
        yield();
    }
}

int main() {

    // First save the execution states for thread0 and thread1
    // Once both are saved, we jump to the start of thread0
    if (setjmp(env[0]) == 0) {
        if (setjmp(env[1]) == 0) {
            longjmp(env[0], 1);
        }
    }

    // These never both run directly, only one is launched after longjmp() above.
    thread0();
    thread1();

    // Exection ends here, but the execution loops forever between the two threads
    return 0;
}
