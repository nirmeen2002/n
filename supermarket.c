// supermarket.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void initializeSupermarket(Supermarket* supermarket) {
    // Prompt for the number of products
    printf("Enter the number of products: ");
    scanf("%d", &supermarket->productCount);

    // Allocate memory for products
    supermarket->products = (Product*)malloc(supermarket->productCount * sizeof(Product));

    for (int i = 0; i < supermarket->productCount; i++) {
        supermarket->products[i].id = i;
        printf("Enter name for product %d: ", i + 1);
        scanf("%49s", supermarket->products[i].name);

        printf("Enter total amount for product %d: ", i + 1);
        scanf("%d", &supermarket->products[i].totalAmount);

        printf("Enter amount on shelf for product %d: ", i + 1);
        scanf("%d", &supermarket->products[i].shelfAmount);
    }

    // Prompt for shelf capacity and replenishment threshold
    printf("Enter shelf capacity for each product: ");
    scanf("%d", &supermarket->shelfCapacity);

    printf("Enter the replenishment threshold for products: ");
    scanf("%d", &supermarket->replenishThreshold);

    // Prompt for the number of shelving teams
    printf("Enter the number of shelving teams: ");
    scanf("%d", &supermarket->teamCount);

    for (int i = 0; i < supermarket->teamCount; i++) {
        supermarket->teams[i].teamId = i;

        // Prompt for the number of employees per team
        printf("Enter the number of employees for team %d: ", i + 1);
        scanf("%d", &supermarket->teams[i].employeeCount);

        // Allocate memory for employee threads
        supermarket->teams[i].employeeThreads = (pthread_t*)malloc(supermarket->teams[i].employeeCount * sizeof(pthread_t));

        // Initialize team mutex and condition variable
        pthread_mutex_init(&supermarket->teams[i].teamMutex, NULL);
        pthread_cond_init(&supermarket->teams[i].condition, NULL);
        supermarket->teams[i].readyToShelve = 0;
        supermarket->teams[i].supermarket = supermarket;
    }

    // Initialize storage mutex
    pthread_mutex_init(&supermarket->storageMutex, NULL);
}

void cleanupSupermarket(Supermarket* supermarket) {
    // Free allocated memory for products
    free(supermarket->products);

    for (int i = 0; i < supermarket->teamCount; i++) {
        // Free allocated memory for employee threads
        free(supermarket->teams[i].employeeThreads);

        // Destroy team mutex and condition variable
        pthread_mutex_destroy(&supermarket->teams[i].teamMutex);
        pthread_cond_destroy(&supermarket->teams[i].condition);
    }

    // Destroy storage mutex
    pthread_mutex_destroy(&supermarket->storageMutex);
}
