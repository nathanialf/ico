#include "ios.h"
#include "debug.h"
#include "memory.h"
#include "message.h"
#include "thread.h"
#include "s_init.h"
#include <eekernel.h>
#include <sifrpc.h>
#include "main.h"
#include <sound.h>
#include "include_asm.h"

/* the IOP heap shortfall the allocator records, then a word no retail code
   reads or writes */
int iopBuffOver = 0;

static int iosUnusedWord = 0; /* derived name */

inline int iosSifAllocIopHeapDebug(int size, const char *file, int line)
{
    int p = sceSifAllocIopHeap(size);

    if (p == 0) {
        debug_StdPrintfDummy("iosSifAllocIopHeapDebug: %s %d not alloc\n", file, line);
        if (iopBuffOver != 0) {
            while (sceSifAllocIopHeap(size - iopBuffOver) == 0) {
                iopBuffOver++;
            }
        } else {
            iopBuffOver = size;
        }
    }
    return p;
}

/* the four semaphore descriptors ios_init_plus fills in and hands to CreateSema */
static struct SemaParam padLockSemaParam; /* derived name */

static struct SemaParam stgMgrLockSemaParam; /* derived name */

static struct SemaParam cdLockSemaParam; /* derived name */

static struct SemaParam sndLockSemaParam; /* derived name */

/* keyInput.h is not included */
extern void InitKeyInput(int unused);

INCLUDE_ASM(ios_init_plus);

INCLUDE_ASM(iosInitialize);

/* .sdata, after iosInitialize's partition names: the partition handles, then
   global_variable, which no retail code uses. */
IosMemPart *ios_partition_root = 0;

IosMemPart *ios_partition_event = 0;

IosMemPart *ios_partition_isys = 0;

IosMemPart *ios_partition_hara = 0;

IosMemPart *ios_partition_sugipon = 0;

IosMemPart *ios_partition_common = 0;

IosMemPart *ios_partition_dmotion = 0;

IosMemPart *ios_partition_smotion = 0;

IosMemPart *ios_partition_s2motion = 0;

IosMemPart *ios_partition_seki = 0;

IosMemPart *ios_partition_oomori = 0;

IosMemPart *ios_partition_horagai = 0;

IosMemPart *ios_partition_sound = 0;

IosMemPart *ios_partition_sound_semi = 0;

IosMemPart *ios_partition_shock = 0;

IosMemPart *ios_partition_inflate = 0;

IosMemPart *ios_partition_mpeg = 0;

int global_variable = 0;
