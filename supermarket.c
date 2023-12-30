// supermarket.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void initializeSupermarket(Supermarket* supermarket) {
    // User defines the number of products
    printf("Enter the number of products: ");
    scanf("%d", &supermarket->productCount);

    // Allocate memory for the products
    supermarket->products = (Product*)malloc(supermarket->productCount * sizeof(Product));

    for (int i = 0; i < supermarket->productCount; i++) {
        // User input for each product
        supermarket->products[i].id = i;
        printf("Product %d:\n", i + 1);

        printf(" Name: ");
        scanf("%49s", supermarket->products[i].name);  // Limit name to 49 characters

        printf(" Total amount: ");
        scanf("%d", &supermarket->products[i].totalAmount);

        printf(" Amount on shelf: ");
        scanf("%d", &supermarket->products[i].shelfAmount);
    }

    // Initialize shelf capacity (common for all products)
    printf("Enter shelf capacity for each product: ");
    scanf("%d", &supermarket->shelfCapacity);

    // Initialize team details
    printf("Enter number of shelving teams: ");
    scanf("%d", &supermarket->teamCount);
    for (int i = 0; i < supermarket->teamCount; i++) {
        supermarket->teams[i].teamId = i;
        supermarket->teams[i].employeeCount = MAX_EMPLOYEES_PER_TEAM; // Default value, can be user-defined
        pthread_mutex_init(&supermarket->teams[i].teamMutex, NULL);
        supermarket->teams[i].supermarket = supermarket; // Link to supermarket
    }

    // Initialize storage mutex
    pthread_mutex_init(&supermarket->storageMutex, NULL);
}

void cleanupSupermarket(Supermarket* supermarket) {
    // Free allocated memory for products
    free(supermarket->products);

    // Destroy mutexes
    for (int i = 0; i < supermarket->teamCount; i++) {
        pthread_mutex_destroy(&supermarket->teams[i].teamMutex);
    }
    pthread_mutex_destroy(&supermarket->storageMutex);
}
