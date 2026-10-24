#include "debug.h"
#include "memory.h"
#include "debug_exception.h"
#include <assert.h>

/* three frames of pointers queued for a delayed iosFree */
#ifdef VERSION_NTSC
static void *delayFreeBuffer[3][256]; /* derived name */
#else
static void *delayFreeBuffer[3][384]; /* derived name */
#endif

/* the frame being filled and its entry count */
static int delayFreeNo = 0; /* derived name */

static int delayFreeCount = 0; /* derived name */

#include "delayFreeManager.h"

#ifdef VERSION_NTSC
static inline void ClearDelayFreeBuffer(int no) /* derived name */
{
    int i;

    for (i = 256 - 1; i >= 0; i--) {
        delayFreeBuffer[no][i] = 0;
    }
}
#else
static inline void ClearDelayFreeBuffer(int no) /* derived name */
{
    int i;

    for (i = 384 - 1; i >= 0; i--) {
        delayFreeBuffer[no][i] = 0;
    }
}
#endif

static inline void FreeDelayFreeBuffer(int no) /* derived name */
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

#ifdef VERSION_NTSC
void EntryDelayFree(void *p)
{
    delayFreeBuffer[delayFreeNo][delayFreeCount++] = p;
    if (delayFreeCount >= 256) {
        debug_StdPrintfDummy("[33mERROR!!! TOO MANY DELAY FREE LIST ENTRY!!! EXIT...[m\n");
        debug_assert("src/delayFreeManager.c", 51);
        __assert("src/delayFreeManager.c", 51, "0");
    }
}
#else
void EntryDelayFree(void *p)
{
    delayFreeBuffer[delayFreeNo][delayFreeCount++] = p;
    if (delayFreeCount >= 384) {
        debug_StdPrintfDummy("[33mERROR!!! TOO MANY DELAY FREE LIST ENTRY!!! EXIT...[m\n");
        debug_assert("src/delayFreeManager.c", 51);
        __assert("src/delayFreeManager.c", 51, "0");
    }
}
#endif
