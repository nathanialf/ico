#include "debug.h"
#include "memory.h"
#include "debug_exception.h"
#include <assert.h>

/* three frames of pointers queued for a delayed iosFree, 128 a frame in this
   build (InitDelayFree clears entries 127 down to 0) */
static void *delayFreeBuffer[3][128]; /* derived name */

/* the frame being filled and its entry count */
static int delayFreeNo = 0; /* derived name */

static int delayFreeCount = 0; /* derived name */

#include "delayFreeManager.h"
#include "include_asm.h"

static inline void ClearDelayFreeBuffer(int no) /* derived name */
{
    int i;

    for (i = 128 - 1; i >= 0; i--) {
        delayFreeBuffer[no][i] = 0;
    }
}

static inline void FreeDelayFreeBuffer(int no) /* derived name */
{
    int i;

    for (i = 0; delayFreeBuffer[no][i] != 0; i++) {
        iosFree(delayFreeBuffer[no][i]);
    }
}

INCLUDE_ASM(EntryDelayFree);

INCLUDE_ASM(InitDelayFree);

INCLUDE_ASM(ExecDelayFree);
