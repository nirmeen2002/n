// main.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>

volatile sig_atomic_t terminate = 0;
int minArrivalInterval, maxArrivalInterval; // User-defined arrival intervals

void handleSignal(int sig) {
    terminate = 1;
}

void createCustomerProcess(Supermarket *supermarket, int customerId) {
    pid_t pid = fork();
    if (pid == 0) {
        // Child process
        Customer customer;
        customer.customerId = customerId;
        customerProcess(&customer, supermarket);
        exit(0);
    }
}

int main() {
    srand(time(NULL)); // Set the seed for random number generation

    Supermarket supermarket;
    initializeSupermarket(&supermarket);
    signal(SIGINT, handleSignal);

    // Get customer arrival intervals from the user
    printf("Enter the minimum customer arrival interval (seconds): ");
    scanf("%d", &minArrivalInterval);
    printf("Enter the maximum customer arrival interval (seconds): ");
    scanf("%d", &maxArrivalInterval);

    int customerId = 0;

    // Main simulation loop
    while (!terminate) {
        int interval = rand() % (maxArrivalInterval - minArrivalInterval + 1) + minArrivalInterval;
        sleep(interval); // Wait for the next customer

        createCustomerProcess(&supermarket, customerId++);
        
        // Other simulation logic can be added here if needed
    }

    // Cleanup
    cleanupSupermarket(&supermarket);

    return 0;
}
