// customer.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void customerProcess(Customer* customer, Supermarket* supermarket) {
    srand(time(NULL) ^ (getpid()<<16));
    while (1) {
        int productId = rand() % supermarket->productCount;
        int quantity = rand() % 5 + 1;  // Random quantity from 1 to 5

        pthread_mutex_lock(&supermarket->storageMutex);
        if (supermarket->products[productId].shelfAmount >= quantity) {
            supermarket->products[productId].shelfAmount -= quantity;
            printf("Customer %d bought %d of Product %d (Shelf Amount: %d)\n", customer->customerId, quantity, productId, supermarket->products[productId].shelfAmount);
        } else {
            printf("Customer %d couldn't buy Product %d (Insufficient stock)\n", customer->customerId, productId);
        }
        pthread_mutex_unlock(&supermarket->storageMutex);

        sleep(rand() % 5 + 1);  // Simulate shopping time

        // Check for termination condition (to be implemented)
    }
}
