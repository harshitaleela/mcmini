// TO COMPILE:  gcc -g3 -O0 THIS_FILE -pthread
// This version of barrier works for any NUM_THREADS.
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

pthread_mutex_t mut;
sem_t sem;

int num_threads_in_barrier = 0;

#define NUM_THREADS 3
#define NUM_BARRIERS 2

// This is a possible implementation of pthread_barrier_init()
//   and pthread_barrier_wait().  But this one has a bug!
// For convenience, we combine the two functions into just one function.
void mybarrier(int num_threads_total) {
  pthread_mutex_lock(&mut);
  int this_is_last_thread = (++num_threads_in_barrier == num_threads_total);
  pthread_mutex_unlock(&mut);
  if (this_is_last_thread) {
    // This is the last thread to reach the barrier.
    for (int i = 0; i < num_threads_total - 1; i++) {
      sem_post(&sem);
    }
  } else {
    sem_wait(&sem); // Wait for the last thread to join the barrier.
  }
  pthread_mutex_lock(&mut);
  num_threads_in_barrier--; // We're no longer in the barrier.
  pthread_mutex_unlock(&mut);
}

void *do_work(void *arg) {
  char self = *(int *)arg;
  int phase = 0;
  for (phase = 0; phase < NUM_BARRIERS; phase++) {
    // sleep(1);
    printf("Thread: %c, Phase: %d\n", self, phase + 1); fflush(stdout);
    mybarrier(NUM_THREADS);
  }
  printf("Thread: %c, Done (Phase %d: exiting)\n", self, phase + 1);
  fflush(stdout);
  return NULL;
}

int main() {
  pthread_t thread[NUM_THREADS];
  char thread_number[NUM_THREADS];

  for (int i = 0; i < NUM_THREADS; i++) {
    thread_number[i] = 'A' + i;
  }

  pthread_mutex_init(&mut, NULL);
  sem_init(&sem, 0, 0); // Set semaphore count to 0
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_create(&thread[i], NULL, do_work, &thread_number[i]);
  }
  for (int i = 0; i < NUM_THREADS; i++) {
    pthread_join(thread[i], NULL);
  }
  return 0;
}
