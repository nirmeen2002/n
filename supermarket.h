// supermarket.h

#ifndef SUPERMARKET_H
#define SUPERMARKET_H

#include <pthread.h>

#define MAX_TEAMS 10
#define MAX_EMPLOYEES_PER_TEAM 5
#define STORAGE_CAPACITY 1000

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
    pthread_t employeeThreads[MAX_EMPLOYEES_PER_TEAM];
    pthread_mutex_t teamMutex;
} Team;

typedef struct {
    int customerId;
    pid_t customerProcessId;
} Customer;

typedef struct {
    int productCount;
    int shelfCapacity;
    Product* products;
    int teamCount;
    Team teams[MAX_TEAMS];
    pthread_mutex_t storageMutex;
    int storageArea[STORAGE_CAPACITY];
} Supermarket;

void initializeSupermarket(Supermarket* supermarket);
void cleanupSupermarket(Supermarket* supermarket);

#endif // SUPERMARKET_H
