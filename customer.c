// customer.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void customerProcess(Customer* customer, Supermarket* supermarket) {
    srand(time(NULL) ^ (getpid() << 16)); // Ensure different seed for each process

    while (1) {
        // Customer randomly chooses a product
        int productId = rand() % supermarket->productCount;
        // Customer randomly decides on a quantity
        int quantity = rand() % 5 + 1; // Random quantity between 1 and 5

        pthread_mutex_lock(&supermarket->storageMutex);
        if (supermarket->products[productId].shelfAmount >= quantity) {
            // If enough stock is available, customer buys the product
            supermarket->products[productId].shelfAmount -= quantity;
            printf("Customer %d bought %d of Product %d (Shelf Amount: %d)\n", customer->customerId, quantity, productId, supermarket->products[productId].shelfAmount);
        } else {
            printf("Customer %d could not buy Product %d (Insufficient stock)\n", customer->customerId, productId);
        }
        pthread_mutex_unlock(&supermarket->storageMutex);

        // Simulate time taken for shopping before choosing another product
        sleep(rand() % 5 + 1); // Sleep for 1 to 5 seconds

        // Implement termination condition check if needed
    }
}
