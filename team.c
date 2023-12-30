// team.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void* shelfEmployee(void* args) {
    Team* team = (Team*)args;
    Supermarket* supermarket = team->supermarket;

    while (1) {
        // Employee waits for the signal to shelve a product
        pthread_mutex_lock(&team->teamMutex);
        while (!team->readyToShelve) {
            pthread_cond_wait(&team->condition, &team->teamMutex);
        }
        
        // Simulate shelving a product
        printf("Employee in Team %d is shelving a product\n", team->teamId);
        sleep(1); // Simulating the time taken to shelve

        // Reset the flag and signal the manager that shelving is done
        team->readyToShelve = 0;
        pthread_mutex_unlock(&team->teamMutex);
        // Notify the manager or perform other actions as needed
    }
    return NULL;
}

void* teamManager(void* args) {
    Team* team = (Team*)args;
    Supermarket* supermarket = team->supermarket;
    srand(time(NULL) ^ (team->teamId << 16)); // Seed for random number generation

    while (1) {
        for (int i = 0; i < supermarket->productCount; i++) {
            pthread_mutex_lock(&supermarket->storageMutex);
            if (supermarket->products[i].shelfAmount < supermarket->replenishThreshold) {
                // Randomly select a team manager for replenishment
                int selectedTeam = rand() % supermarket->teamCount;
                if (selectedTeam == team->teamId) {
                    printf("Team %d manager replenishing Product %d\n", team->teamId, i);
                    // Simulate replenishing the product
                    supermarket->products[i].shelfAmount = supermarket->shelfCapacity;
                    
                    // Notify an employee to shelve the product
                    pthread_mutex_lock(&team->teamMutex);
                    team->readyToShelve = 1;
                    pthread_cond_signal(&team->condition);
                    pthread_mutex_unlock(&team->teamMutex);
                }
            }
            pthread_mutex_unlock(&supermarket->storageMutex);
            sleep(1); // Prevents constant locking, simulates time taken for checking
        }
        // Manager can perform other tasks or checks here
    }
    return NULL;
}
