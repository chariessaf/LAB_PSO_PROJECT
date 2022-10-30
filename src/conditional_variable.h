#pragma once

typedef struct _CONDITIONAL_VARIABLE
{
    LIST_ENTRY              WaiterList;
} CONDITIONAL_VARIABLE, * PCONDITIONAL_VARIABLE;

// Initializes condition variable CondVariable.  A condition variable
// allows one piece of code to signal a condition and cooperating
// code to receive the signal and act upon it.
void
CondVariableInit(
    OUT     PCONDITIONAL_VARIABLE   CondVariable
);

// Atomically releases Lock and waits for CondVariable to be signaled by
// some other piece of code.  After CondVariable is signaled, Lock is
// reacquired before returning.  Lock must be held before calling
// this function.
//
// The monitor implemented by this function is "Mesa" style, not
// "Hoare" style, that is, sending and receiving a signal are not
// an atomic operation.  Thus, typically the caller must recheck
// the condition after the wait completes and, if necessary, wait
// again.
//
// A given condition variable is associated with only a single
// lock, but one lock may be associated with any number of
// condition variables.  That is, there is a one-to-many mapping
// from locks to condition variables.
//
// This function may sleep, so it must not be called within an
// interrupt handler.  This function may be called with
// interrupts disabled, but interrupts will be turned back on if
// we need to sleep. */    
void
CondVariableWait(
    INOUT   PCONDITIONAL_VARIABLE   CondVariable,
    INOUT   PMUTEX                  Lock
);

// If any threads are waiting on CondVariable (protected by Lock), then
// this function signals one of them to wake up from its wait.
// Lock must be held before calling this function.
//
// An interrupt handler cannot acquire a lock, so it does not
// make sense to try to signal a condition variable within an
// interrupt handler.
void
CondVariableSignal(
    INOUT   PCONDITIONAL_VARIABLE   CondVariable,
    INOUT   PMUTEX                  Lock
);

// Wakes up all threads, if any, waiting on CondVariable (protected by
// Lock). Lock must be held before calling this function.
//
// An interrupt handler cannot acquire a lock, so it does not
// make sense to try to signal a condition variable within an
// interrupt handler.
void
CondVariableBroadcast(
    INOUT   PCONDITIONAL_VARIABLE   CondVariable,
    INOUT   PMUTEX                  Lock
);