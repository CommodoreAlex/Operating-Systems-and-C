#include <stdio.h>
#include <setjmp.h>

// Example of how park(), unpark(), and yield() work together in a cooperative threading system

#define MAX_THREADS 2

jmp_buf env[MAX_THREADS];
int current = 0;
int parked[MAX_THREADS] = {0, 0};   // 0 = runnable, 1 = parked

void yield() {
    int ret = setjmp(env[current]);
    if (ret == 0) {
        do {
            current = (current + 1) % MAX_THREADS;
        } while (parked[current]);  // Skip parked threads
        longjmp(env[current], 1);
    }
}

void park() {
    parked[current] = 1;
    yield();    // Give up CPU
}

void unpark(int thread_id) {
    parked[thread_id] = 0;
}

void thread0() {
    printf("Thread 0: running\n");
    printf("Thread 0: parking myself\n");
    park();  // Block this thread
    printf("Thread 0: resumed!\n");
    yield();
}

void thread1() {
    printf("Thread 1: running\n");
    printf("Thread 1: unparking thread 0\n");
    unpark(0);  // Wake up thread 0
    yield();
}

int main() {
    if (setjmp(env[0]) == 0) {
        if (setjmp(env[1]) == 0) {
            longjmp(env[0], 1);
        }
    }

    if (current == 0) thread0();
    else thread1();

    return 0;
}
