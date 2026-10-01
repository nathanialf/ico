#include "ios.h"
#include "debug.h"
#include "memory.h"
#include "message.h"
#include "thread.h"
#include "s_init.h"
#include <eekernel.h>
#include <sifrpc.h>

/* .sdata, owned by ios.o in MAIN.MAP's order: the IOP heap shortfall the
   allocator records, then a word no retail code reads or writes (MAIN.MAP
   names no symbol for it). */
int iopBuffOver = 0;

static int iosUnusedWord = 0; /* derived name */

inline int iosSifAllocIopHeapDebug(int size, char *file, int line)
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

/* the semaphore descriptor CreateSema takes: only three of its words are set */
typedef struct SemaParam {
    char _p0[0x4];
    int initCount; /* 0x04 */
    int maxCount;  /* 0x08 */
    char _pC[0x4];
    int attr;       /* 0x10 */
    char _p14[0x4]; /* 0x14: the record is 0x18 bytes, which is the stride
                        between the four descriptors in the ROM's .bss run */
} SemaParam;

/* .bss, owned by ios.o and reached only from this file (MAIN.MAP names no
   symbol in the run), in the ROM's run order: the four semaphore descriptors
   iosInit fills in and hands to CreateSema. */
static SemaParam cdLockSemaParam;

static SemaParam faultSemaParam;

static SemaParam sndLockSemaParam;

static SemaParam stgMgrLockSemaParam;

extern int IosPadLock;
extern int IosCdLock;
extern int IosStgMgrLock;
extern int IosSndLock;
extern int D_00639ED8;
extern int screen_offset_x;
extern int screen_offset_y;
/* kept local: this TU's uses of InitKeyInput do not fit the prototype in keyInput.h */
extern void InitKeyInput();
extern void SgSndn2RemoteInit(void);

void ios_init_plus(void)
{
    cdLockSemaParam.attr = 1;
    cdLockSemaParam.initCount = 1;
    cdLockSemaParam.maxCount = 0;
    IosPadLock = CreateSema(&cdLockSemaParam);
    sndLockSemaParam.attr = 1;
    sndLockSemaParam.initCount = 1;
    sndLockSemaParam.maxCount = 0;
    IosCdLock = CreateSema(&sndLockSemaParam);
    faultSemaParam.attr = 1;
    faultSemaParam.initCount = 1;
    faultSemaParam.maxCount = 0;
    IosStgMgrLock = CreateSema(&faultSemaParam);
    stgMgrLockSemaParam.attr = 1;
    stgMgrLockSemaParam.initCount = 1;
    stgMgrLockSemaParam.maxCount = 0;
    IosSndLock = CreateSema(&stgMgrLockSemaParam);
    D_00639ED8 = 0;
    InitKeyInput(0);
    debug_StdPrintfDummy("SgSndn2RemoteInit()\n");
    SgSndn2RemoteInit();
    sceSifInitIopHeap();
    debug_StdPrintfDummy("allocate IOP heap memory - \n");
    soundAllocIopHeap();
    soundInit();
    screen_offset_x = 0;
    screen_offset_y = 0;
}

void iosInitialize(void)
{
    debug_StdPrintfDummy("iosInitialize()\n");
    iosThreadInit();
    ios_partition_root = iosMallocInitPartition(0x760000, 0x1FEFFF0);
    ios_partition_common = iosMallocSetPartition(ios_partition_root, 0x408000, 0x10);
    ios_partition_smotion = iosMallocSetPartition(ios_partition_root, 0x120000, 0x10);
    ios_partition_s2motion = iosMallocSetPartition(ios_partition_root, 0x300000, 0x10);
    ios_partition_event = iosMallocSetPartition(ios_partition_root, 0x40000, 0x10);
    ios_partition_oomori = iosMallocSetPartition(ios_partition_root, 0x50000, 0x10);
    ios_partition_horagai = iosMallocSetPartition(ios_partition_root, 1, 0x10);
    ios_partition_sound = iosMallocSetPartition(ios_partition_root, 0x8000, 0x10);
    ios_partition_sound_semi = iosMallocSetPartition(ios_partition_root, 0x5000, 0x10);
    ios_partition_shock = iosMallocSetPartition(ios_partition_root, 0x2800, 0x10);
    ios_partition_hara = iosMallocSetPartition(ios_partition_root, 1, 0x10);
    /* the chain's store order is what the ROM's four gp stores record */
    ios_partition_isys = ios_partition_seki = ios_partition_sugipon = ios_partition_dmotion =
        iosMallocSetPartition(ios_partition_root, 0xF18000, 0x10);
    iosMallocSetPartitionName(ios_partition_isys, "stage");
    iosMallocSetPartitionName(ios_partition_smotion, "stat mot");
    iosMallocSetPartitionName(ios_partition_s2motion, "demo mot");
    iosMallocSetPartitionName(ios_partition_event, "event");
    iosMallocSetPartitionName(ios_partition_hara, "hara");
    iosMallocSetPartitionName(ios_partition_oomori, "oomori");
    iosMallocSetPartitionName(ios_partition_horagai, "horagai");
    iosMallocSetPartitionName(ios_partition_sound, "sound");
    iosMallocSetPartitionName(ios_partition_shock, "shock");
    iosMallocSetPartitionName(ios_partition_common, "common");
    iosMsgInit();
    ios_init_plus();
}

/* .sdata, after iosInitialize's partition names: the partition handles (MAIN.MAP
   globals, in its order), then global_variable, which no retail code uses. */
int ios_partition_root = 0;

int ios_partition_event = 0;

int ios_partition_isys = 0;

int ios_partition_hara = 0;

int ios_partition_sugipon = 0;

int ios_partition_common = 0;

int ios_partition_dmotion = 0;

int ios_partition_smotion = 0;

int ios_partition_s2motion = 0;

int ios_partition_seki = 0;

int ios_partition_oomori = 0;

int ios_partition_horagai = 0;

int ios_partition_sound = 0;

int ios_partition_sound_semi = 0;

int ios_partition_shock = 0;

int ios_partition_inflate = 0;

int ios_partition_mpeg = 0;

int global_variable = 0;
