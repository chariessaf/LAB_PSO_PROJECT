#include "HAL9000.h"
#include "thread_internal.h"
#include "semaphore.h"


_No_competing_thread_
void
SemaphoreInit(
    OUT         PSEMAPHORE      Semaphore,
    IN          DWORD     InitialValue
)
{
    // Busy waiting can be inefficient because the looping procedure
    // is a waste of computer resources

    // Busy waiting implementation using the block/unblock mechanism

    wait(Semaphore) {
        Semaphore->InitialValue--;
        if (Semaphore->InitialValue < 0)
        {
            // add process to queue
            block();
        }
    }
    signal(Semaphore) {
        Semaphore->InitialValue++;
        if (Semaphore->InitialValue <= 0) {
            // remove process p from queue
            wakeup(p);
        }
    }
    void
    SemaphoreDown(
        INOUT   PSEMAPHORE      Semaphore,
        IN        DWORD           Value)
        // Vezi curs 4.1 pag 158
}