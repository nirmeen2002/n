// team.c

#include "supermarket.h"
#include <stdio.h>
#include <unistd.h>

void* shelfEmployee(void* args) {
    Team* team = (Team*)args;
    Supermarket* supermarket = team->supermarket;

    while (1) {
        // Employee shelving logic (to be expanded upon)
        sleep(1); // Simulate work

        // Check for termination condition (to be implemented)
    }
    return NULL;
}

void* teamManager(void* args) {
    Team* team = (Team*)args;
    Supermarket* supermarket = team->supermarket;

    while (1) {
        for (int i = 0; i < supermarket->productCount; i++) {
            pthread_mutex_lock(&supermarket->storageMutex);
            if (supermarket->products[i].shelfAmount < REPLENISH_THRESHOLD) {
                supermarket->products[i].shelfAmount = supermarket->shelfCapacity;
                printf("Manager of Team %d replenished Product %d (Shelf Amount: %d)\n", team->teamId, i, supermarket->products[i].shelfAmount);
            }
            pthread_mutex_unlock(&supermarket->storageMutex);
        }
        sleep(5);  // Simulate management tasks

        // Check for termination condition (to be implemented)
    }
    return NULL;
}
