#ifndef INCLUDE_MCMINI_TRANSITIONS_WRAPPERS_MCBARRIERWRAPPERS_HPP
#define INCLUDE_MCMINI_TRANSITIONS_WRAPPERS_MCBARRIERWRAPPERS_HPP

#include "mcmini/MCShared.h"
#include <pthread.h>

MC_EXTERN int mc_pthread_barrier_init(pthread_barrier_t *,
                                      const pthread_barrierattr_t *,
                                      unsigned int);
MC_EXTERN int mc_pthread_barrier_wait(pthread_barrier_t *);

#endif // INCLUDE_MCMINI_TRANSITIONS_WRAPPERS_MCBARRIERWRAPPERS_HPP
