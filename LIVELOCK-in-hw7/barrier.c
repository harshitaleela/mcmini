// TO COMPILE:  gcc -g3 -O0 THIS_FILE -pthread
// This version of barrier works only for _two_ threads.
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

int barrierArray[2] = {0, 0};
pthread_t self;

void barrier(int self) {
  pthread_mutex_lock(&mut);
  barrierArray[self] = 1;
  pthread_mutex_unlock(&mut);
  // Wait until both threads have reached the barrier.
  pthread_mutex_lock(&mut);
  while (barrierArray[self] == 0 || barrierArray[1-self] == 0) {}
  pthread_mutex_unlock(&mut);
  pthread_mutex_lock(&mut);
  barrierArray[self] = 0;
  pthread_mutex_unlock(&mut);
  // Now wait until both threads are ready to exit the barrier.
  pthread_mutex_lock(&mut);
  while (barrierArray[self] == 1 || barrierArray[1-self] == 1) {}
  pthread_mutex_unlock(&mut);
  // Now both threads should have barrierArray[] set to 0,
  //   and be ready for the next barriers.
}

void *do_work(void *arg) {
  int self = *(int *)arg;
  int iteration;
  for (iteration = 0; iteration < 2; iteration++) {
    barrier(self);
    sleep(5);
    printf("Thread: %d, iteration: %d\n", self, iteration); fflush(stdout);
  }
}

int main() {
  int thread1 = 0;
  int thread2 = 1;
  pthread_t thread[2];
  // McMini does not yet work with PTHREAD_MUTEX_INITIALIZER; 
  pthread_mutex_init(&mut, NULL);
  pthread_create(&thread[0], NULL, do_work, &thread1);
  pthread_create(&thread[1], NULL, do_work, &thread2);
  pthread_join(thread[0], NULL);
  pthread_join(thread[1], NULL);
  return 0;
}
