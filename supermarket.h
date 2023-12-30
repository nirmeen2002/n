// supermarket.h

#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <pthread.h>

#define MAX_TEAMS 10
#define MAX_EMPLOYEES_PER_TEAM 5

typedef struct {
    int id;
    char name[50];
    int totalAmount;
    int shelfAmount;
} Product;

typedef struct {
    int teamId;
    int employeeCount;
    pthread_t managerThread;
    pthread_t *employeeThreads;
    pthread_mutex_t teamMutex;
    struct Supermarket* supermarket;
} Team;

typedef struct Supermarket {
    int productCount;
    int shelfCapacity;
    int replenishThreshold;
    Product* products;
    int teamCount;
    Team teams[MAX_TEAMS];
    pthread_mutex_t storageMutex;
} Supermarket;

void initializeSupermarket(Supermarket* supermarket);
void cleanupSupermarket(Supermarket* supermarket);

#endif // SUPERMARKET_H
