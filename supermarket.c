// supermarket.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void initializeSupermarket(Supermarket* supermarket) {
    printf("Enter the number of products: ");
    scanf("%d", &supermarket->productCount);
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

    printf("Enter shelf capacity for each product: ");
    scanf("%d", &supermarket->shelfCapacity);

    printf("Enter the replenishment threshold for products: ");
    scanf("%d", &supermarket->replenishThreshold);

    printf("Enter the number of shelving teams: ");
    scanf("%d", &supermarket->teamCount);

    for (int i = 0; i < supermarket->teamCount; i++) {
        supermarket->teams[i].teamId = i;
        printf("Enter the number of employees for team %d: ", i + 1);
        scanf("%d", &supermarket->teams[i].employeeCount);

        supermarket->teams[i].employeeThreads = (pthread_t*)malloc(supermarket->teams[i].employeeCount * sizeof(pthread_t));
        pthread_mutex_init(&supermarket->teams[i].teamMutex, NULL);
        supermarket->teams[i].supermarket = supermarket;
    }

    pthread_mutex_init(&supermarket->storageMutex, NULL);
}

void cleanupSupermarket(Supermarket* supermarket) {
    free(supermarket->products);
    
    for (int i = 0; i < supermarket->teamCount; i++) {
        free(supermarket->teams[i].employeeThreads);
        pthread_mutex_destroy(&supermarket->teams[i].teamMutex);
    }
    
    pthread_mutex_destroy(&supermarket->storageMutex);
}
