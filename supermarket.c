// supermarket.c

#include "supermarket.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void initializeSupermarket(Supermarket* supermarket) {
    // Example initialization logic
    supermarket->productCount = 10; // Example value
    supermarket->shelfCapacity = 50; // Example value
    supermarket->teamCount = 3; // Example value

    // Allocate memory for products and initialize them
    supermarket->products = malloc(supermarket->productCount * sizeof(Product));
    for (int i = 0; i < supermarket->productCount; i++) {
        supermarket->products[i].id = i;
        sprintf(supermarket->products[i].name, "Product %d", i);
        supermarket->products[i].totalAmount = 100; // Example value
        supermarket->products[i].shelfAmount = 50; // Example value
    }

    // Initialize teams and their mutexes
    for (int i = 0; i < supermarket->teamCount; i++) {
        supermarket->teams[i].teamId = i;
        supermarket->teams[i].employeeCount = 5; // Example value
        pthread_mutex_init(&supermarket->teams[i].teamMutex, NULL);
        // More team initialization here
    }

    // Initialize storage mutex
    pthread_mutex_init(&supermarket->storageMutex, NULL);
}

void cleanupSupermarket(Supermarket* supermarket) {
    // Free allocated memory
    free(supermarket->products);

    // Destroy mutexes
    for (int i = 0; i < supermarket->teamCount; i++) {
        pthread_mutex_destroy(&supermarket->teams[i].teamMutex);
    }
    pthread_mutex_destroy(&supermarket->storageMutex);
}
