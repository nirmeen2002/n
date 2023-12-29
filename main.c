// main.c

#include "supermarket.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int main() {
    Supermarket supermarket;
    initializeSupermarket(&supermarket);

    // Create threads and processes

    // Main simulation loop

    // Cleanup
    cleanupSupermarket(&supermarket);

    return 0;
}
