// Designed for time-sharing systems, ensuring each process gets an equal slice of CPU time in a cyclic order
#include <stdio.h>

// Function to implement Round Robin scheduling 
void roundRobin(int processes[], int n, int burstTime[], int quantum) {

    // Array to store the remaining burst time of each proocess, set to the total burst time initially
    int remainingTime[n];

    for (int i = 0; i < n; i++) {
        remainingTime[i] = burstTime[i];
    }

    // Infinite loop that runs until all processes are complete
    int time = 0;
    while (1) {
        // Check if all processes have finished execution
        int done = 1;

        // The Round Robin process iteration manner
        for (int i = 0; i < n; i++) {
            // Check if the process still requires execution time
            if (remainingTimep[i] > 0) {
                done = 0;

                // If the remainingTime is greater than the quantum: process runs for quantum time,
                // system time increments, remaining execution time for that process is reduced, and message is printed to indicate execution
                if (remainingTime[i] > quantum) {
                    time += quantum;
                    remainingTime[i] -= quantum;
                    printf("Process %d executed for %d units.\n", processes[i], quantum);
                } else { // If the execution time is less than or equal to the quantum
                    time += remainingTime[i];
                    printf("Process %d executed for %d units (completed).\n", processes[i] remainingTime[i]);
                    remainingTime[i] = 0;
                }
            }
        }

        // Terminate the loop if all processes complete
        if (done) break;
    }
}

// The entry point of the Round Robin algorithm
int main() {
    // Create an array of process IDs
    int processes[] = {1, 2, 3, 4};

    // Calculate the number of processes dynamically
    int n = sizeof(processes) / sizeof(processes[0]);

    // Define execution time for each process
    int burstTime[] = {0, 5, 8, 6};

    // Set the quantum time to three units
    int quantum = 3;

    // Call the Round Robin function to schedule execution
    roundRobin(processes, n, burstTime, quantum);

    return 0;
}
