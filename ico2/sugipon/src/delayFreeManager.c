#include "debug.h"
#include "memory.h"
#include "debug_exception.h"
#include <assert.h>

/* .bss, owned by delayFreeManager.o and reached only from this file (MAIN.MAP
   names no symbol in the run): three frames of pointers queued for a delayed
   iosFree. */
static void *delayFreeBuffer[3][384];

/* The TU's .sdata (MAIN.MAP names nothing in it): the frame being filled and
   its entry count, then EntryDelayFree's assert literal. */
static int delayFreeNo = 0; /* derived name */

static int delayFreeCount = 0; /* derived name */

#include "delayFreeManager.h"

static inline void ClearDelayFreeBuffer(int no)
{
    int i;

    for (i = 384 - 1; i >= 0; i--) {
        delayFreeBuffer[no][i] = 0;
    }
}

static inline void FreeDelayFreeBuffer(int no)
{
    int i;

    for (i = 0; delayFreeBuffer[no][i] != 0; i++) {
        iosFree(delayFreeBuffer[no][i]);
    }
}

inline void InitDelayFree(void)
{
    ClearDelayFreeBuffer(0);
    ClearDelayFreeBuffer(1);
    ClearDelayFreeBuffer(2);
    delayFreeCount = 0;
    delayFreeNo = 0;
}

inline void ExecDelayFree(void)
{
    int no = (delayFreeNo + 2) % 3;

    FreeDelayFreeBuffer(no);
    ClearDelayFreeBuffer(no);
    delayFreeCount = 0;
    delayFreeNo = no;
}

void EntryDelayFree(void *p)
{
    delayFreeBuffer[delayFreeNo][delayFreeCount++] = p;
    if (delayFreeCount >= 384) {
        debug_StdPrintfDummy("[33mERROR!!! TOO MANY DELAY FREE LIST ENTRY!!! EXIT...[m\n");
        debug_assert("src/delayFreeManager.c", 51);
        __assert("src/delayFreeManager.c", 51, "0");
    }
}
