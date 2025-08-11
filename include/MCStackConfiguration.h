#ifndef MC_MCSTATECONFIGURATION_H
#define MC_MCSTATECONFIGURATION_H

#include "MCShared.h"

/**
 * A configuration constant which specifies that threads
 * may execute as many transitions as they would like (i.e. are
 * not limited to an execution depth)
 */
#define MC_STATE_CONFIG_THREAD_NO_LIMIT (UINT64_MAX)
#define MC_STATE_CONFIG_PRINT_AT_TRACE  (UINT64_MAX)

/**
 * A configuration constant which specifies that a branch may
 * may execute as many transitions as it wants, given that the
 * total number of transitions in the search tree does not exceed
 * the default bound set by MAX_TOTAL_TRANSITIONS_IN_PROGRAM
 */
#define MC_STATE_CONFIG_BRANCH_NO_LIMIT  (1500)

/**
 * A struct which describes the configurable parameters
 * of the model checking execution
 */
struct MCStackConfiguration final {

  /**
   * The maximum number of transitions that can be run
   * by any single thread while running the model checker
   */
  const uint64_t maxThreadExecutionDepth;

  /**
   * The maximum number of transitions that can be run by
   * all the threads in total while running the model checker
   */
  const uint64_t maxTotalExecutionDepth;

  /**
   * The trace id to stop the model checker at
   * to print the contents of the transition stack.
   */
  const trid_t printBacktraceAtTraceNumber;

  /**
   * Whether or not this model checking session is
   * being used to check for starvation to make statements
   * about forward progress
   *
   * In order that the model checker can check for forward progress,
   * the target program must be modified with calls to GOAL(), which
   * act as marker for where we wish to ensure threads reach after
   * a fixed number of steps. When this option is set, it should be
   * coupled with a reasonable value for `maxThreadExecutionDepth`
   */
  const bool expectForwardProgressOfThreads;

  MCStackConfiguration(uint64_t maxThreadExecutionDepth,
                       uint64_t maxTotalExecutionDepth,
                       trid_t printBacktraceAtTraceNumber,
                       bool firstDeadlock,
                       bool expectForwardProgressOfThreads)
    : maxThreadExecutionDepth(maxThreadExecutionDepth),
      maxTotalExecutionDepth(maxTotalExecutionDepth),
      printBacktraceAtTraceNumber(printBacktraceAtTraceNumber),
      expectForwardProgressOfThreads(expectForwardProgressOfThreads)
  {}
};

#endif // MC_MCSTATECONFIGURATION_H
