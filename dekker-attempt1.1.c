#include <pthread.h>
#include <stdatomic.h>
#include "MCProgress.h"

atomic_int turn = 1;

void *process1(void *arg)
{
    while (1) {
        while (atomic_load(&turn) != 1)
            ;


        /* critical section */

        atomic_store(&turn, 2);
        MC_PROGRESS();

        /* remainder section */
    }
    return NULL;
}

void *process2(void *arg)
{
    while (1) {
        while (atomic_load(&turn) != 2)
            ;


        /* critical section */

        atomic_store(&turn, 1);
        MC_PROGRESS();

        /* remainder section */
    }
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, process1, NULL);
    pthread_create(&t2, NULL, process2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return 0;
}
