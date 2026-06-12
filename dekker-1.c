#include <pthread.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "MCProgress.h"

// Shared variables
bool flag[2] = {false, false};
int turn = 0; 

void* thread_func(void* arg) {
    int self = *(int*)arg;
    int other = 1 - self;

    // Thread 0 will run twice, Thread 1 will try to run continuously
    int iterations = (self == 0) ? 2 : 5;

    for (int i = 0; i < iterations; i++) {
        
        // --- STAGE 1: Strict Alternation Turn Check ---
        // ISSUE: Thread spins here if it is not its turn, before even setting its flag.
        while (turn != self) {
            // If the other thread terminates, turn never changes, causing permanent starvation.
        }
        
        flag[self] = true;
        MC_PROGRESS(); // Progress 1: Passed the turn barrier and set flag

        // --- STAGE 2: Collision Detection & Resolution ---
        while (flag[other]) {
            if (turn != self) {
                flag[self] = false;
                while (turn != self) {}
                flag[self] = true;
            }
        }
        MC_PROGRESS(); // Progress 2: Entered Critical Section boundary

        // --- STAGE 3: Critical Section ---
        printf("Thread %d entered Critical Section (Iteration %d/%d)\n", self, i + 1, iterations);
        usleep(100000); // Simulate work

        // --- STAGE 4: Exit Protocol ---
        turn = other;
        flag[self] = false;
        MC_PROGRESS(); // Progress 3: Left Critical Section and handed over turn
        
        usleep(100000); // Remainder section
    }

    printf("### Thread %d has completely finished its execution and exited. ###\n", self);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    int id0 = 0, id1 = 1;

    pthread_create(&t1, NULL, thread_func, &id0);
    pthread_create(&t2, NULL, thread_func, &id1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: All threads joined successfully.\n");
    return 0;
}
