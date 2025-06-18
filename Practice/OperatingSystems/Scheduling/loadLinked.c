#include <stdio.h>
#include <stdatomic.h>
#include <stdbool.h>

// The foundation of many lock-free algorithms, load-linked and store conditional

atomic_int shared = 0;

bool simulated_ll_sc_increment() {
    int old_val = atomic_load(&shared);  // Load-linked
    int new_val = old_val + 1;

    // Store-conditional: only store if value hasn't changed
    return atomic_compare_exchange_strong(&shared, &old_val, new_val);
}

int main() {
    for (int i = 0; i < 10; i++) {
        while (!simulated_ll_sc_increment()) {
            // Retry if store-conditional failed
        }
    }

    printf("Final value: %d\n", atomic_load(&shared));
    return 0;
}
