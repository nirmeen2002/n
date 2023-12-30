// supermarket.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void initializeSupermarket(Supermarket* supermarket) {
    // Get number of products from the user
    printf("Enter the number of products: ");
    scanf("%d", &supermarket->productCount);

    // Allocate memory for products
    supermarket->products = (Product*)malloc(supermarket->productCount * sizeof(Product));

    for (int i = 0; i < supermarket->productCount; i++) {
        supermarket->products[i].id = i;
        printf("Enter name for product %d: ", i + 1);
        scanf("%49s", supermarket->products[i].name); // Limit input to 49 characters

        printf("Enter total amount for product %d: ", i + 1);
        scanf("%d", &supermarket->products[i].totalAmount);

        printf("Enter amount on shelf for product %d: ", i + 1);
        scanf("%d", &supermarket->products[i].shelfAmount);
    }

    // Get number of shelving teams from the user
    printf("Enter the number of shelving teams: ");
    scanf("%d", &supermarket->teamCount);

    // Allocate memory for teams
    for (int i = 0; i < supermarket->teamCount; i++) {
        printf("Enter the number of employees for team %d: ", i + 1);
        scanf("%d", &supermarket->teams[i].employeeCount);

        supermarket->teams[i].teamId = i;
        pthread_mutex_init(&supermarket->teams[i].teamMutex, NULL);

        // Allocate memory for employee threads within each team
        supermarket->teams[i].employeeThreads = (pthread_t*)malloc(supermarket->teams[i].employeeCount * sizeof(pthread_t));
    }

    // Initialize the storage mutex
    pthread_mutex_init(&supermarket->storageMutex, NULL);
}

void cleanupSupermarket(Supermarket* supermarket) {
    // Free allocated memory for products
    free(supermarket->products);

    // Free allocated memory for employee threads in each team and destroy mutexes
    for (int i = 0; i < supermarket->teamCount; i++) {
        free(supermarket->teams[i].employeeThreads);
        pthread_mutex_destroy(&supermarket->teams[i].teamMutex);
    }

    // Destroy the storage mutex
    pthread_mutex_destroy(&supermarket->storageMutex);
}
