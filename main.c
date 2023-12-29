// main.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

volatile sig_atomic_t terminate = 0;

void handleSignal(int sig) {
    terminate = 1;
}

int main() {
    Supermarket supermarket;
    initializeSupermarket(&supermarket);

    // Register signal handler
    signal(SIGINT, handleSignal);

    // Create team threads
    for (int i = 0; i < supermarket.teamCount; i++) {
        // Create manager thread
        pthread_create(&supermarket.teams[i].managerThread, NULL, teamManager, &supermarket);

        // Create employee threads
        for (int j = 0; j < supermarket.teams[i].employeeCount; j++) {
            pthread_create(&supermarket.teams[i].employeeThreads[j], NULL, shelfEmployee, &supermarket);
        }
    }

    // Define number of customers
    int numberOfCustomers = 10; // Example number of customers
    pid_t customerPIDs[numberOfCustomers];

    // Create customer processes
    for (int i = 0; i < numberOfCustomers; i++) {
        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            Customer customer;
            customer.customerId = i;
            customerProcess(&customer, &supermarket);
            exit(0);
        } else {
            // Parent process
            customerPIDs[i] = pid;
        }
    }

    // Main simulation loop
    while (!terminate) {
        // Simulation logic here
        sleep(1); // Simulate time passing
    }

    // Terminate and wait for customer processes
    for (int i = 0; i < numberOfCustomers; i++) {
        kill(customerPIDs[i], SIGTERM);
        waitpid(customerPIDs[i], NULL, 0);
    }

    // Join team threads
    for (int i = 0; i < supermarket.teamCount; i++) {
        pthread_join(supermarket.teams[i].managerThread, NULL);

        for (int j = 0; j < supermarket.teams[i].employeeCount; j++) {
            pthread_join(supermarket.teams[i].employeeThreads[j], NULL);
        }
    }

    // Cleanup
    cleanupSupermarket(&supermarket);

    return 0;
}
