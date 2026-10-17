#include "debug.h"
#include "memory.h"
#include "DmaPacket.h"
#include "GifPacket.h"
#include "MicroCode.h"
#include "DisplayList.h"
#include <eekernel.h>
#include <libdma.h>
#include "GsBase.h"
#include "ios.h"
#include "debug_exception.h"
#include "Basic.h"
#include <assert.h>
#include "include_asm.h"

#define DL_DEBUG 0 /* derived name */

/* One priority's display list: whether a DMA tag is open, where the open tag
   is, the address and quadword count it refers to and its tag id, the start
   of the list's buffer and the write pointer.  0x60 bytes in this build (the
   stubs step the table by 96 and read the start and write pointer at 0x58
   and 0x5C); the words between the id and them are not named here. */
typedef struct {           /* field names derived */
    int open;              /* 0x00 */
    int tag;               /* 0x04 */
    long long addr;        /* 0x08 */
    unsigned int qwc;      /* 0x10 */
    int pad14;             /* 0x14 */
    unsigned long long id; /* 0x18 */
    char pad20[0x38];      /* 0x20 */
    int start;             /* 0x58 */
    int cur;               /* 0x5C */
} DlEntry;                 /* derived name */

/* The bank the list is built into and the priority it is building at, then the 13
   list entries, the two banks of 13 buffer heads they are reloaded from, and
   the eight-deep priority stack. */
static int dlBank; /* derived name */

static int dlPriority; /* derived name */

static DlEntry dlEntries[13]; /* derived name */

static int dlBufferHead[2][13]; /* derived name */

/* The depth of the priority stack below. */
static int dlStackDepth = 0; /* derived name */

static int dlPriorityStack[8]; /* derived name */

/* The size of each priority's list buffer. */
static const int dlBufferSize[13] = {
    /* derived name */
    /* this build's sizes */
    98304, 16384, 32768, 4096, 16384, 49152, 49152, 16384, 28672, 16384, 4096, 12288, 24576,
};

INCLUDE_ASM(dl_Init);

INCLUDE_ASM(dl_Clear);

inline void dl_SetDLPriority(int pri);
inline void dl_OpenDma(int id, void *addr, int qwc);

INCLUDE_ASM(dl_Swap);

INCLUDE_ASM(dl_PushPriority);

INCLUDE_ASM(dl_PopPriority);

inline int dl_GetPri(void)
{
    return dlPriority;
}

INCLUDE_ASM(dl_Debug);

INCLUDE_ASM(dl_CloseDma);

INCLUDE_ASM(dl_Out);

INCLUDE_ASM(dl_SetDLPriority);

INCLUDE_ASM(dl_OpenDma);
