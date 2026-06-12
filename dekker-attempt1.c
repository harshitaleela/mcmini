#include <pthread.h>
#include "MCProgress.h"

int turn = 1;

void *process1(void *arg)
{
    while (1) {
        while (turn != 1)
            ;


        /* critical section */

        turn = 2;
        MC_PROGRESS();

        /* remainder section */
    }
    return NULL;
}

void *process2(void *arg)
{
    while (1) {
        while (turn != 2)
            ;


        /* critical section */

        turn = 1;
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
