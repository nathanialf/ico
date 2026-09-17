#include "common.h"
#include "ios.h"
#include "debug.h"
#include "memory.h"
#include "message.h"
#include "thread.h"
#include "s_init.h"
#include <eekernel.h>
#include <sifrpc.h>

extern int D_0063A3E0;

inline int iosSifAllocIopHeapDebug(int size, char *file, int line)
{
    int p = sceSifAllocIopHeap(size);

    if (p == 0) {
        debug_StdPrintfDummy("iosSifAllocIopHeapDebug: %s %d not alloc\n", file, line);
        if (D_0063A3E0 != 0) {
            while (sceSifAllocIopHeap(size - D_0063A3E0) == 0) {
                D_0063A3E0++;
            }
        } else {
            D_0063A3E0 = size;
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

extern int IosCdLock;
extern int IosSndLock;
extern int systemFault;
extern int IosStgMgrLock;
extern int D_00639ED8;
extern int screen_offset_y;
extern int fall_death_active;
/* kept local: this TU's uses of InitKeyInput do not fit the prototype in keyInput.h */
extern void InitKeyInput();
extern void SgSndn2RemoteInit(void);

void ios_init_plus(void)
{
    cdLockSemaParam.attr = 1;
    cdLockSemaParam.initCount = 1;
    cdLockSemaParam.maxCount = 0;
    IosCdLock = CreateSema(&cdLockSemaParam);
    sndLockSemaParam.attr = 1;
    sndLockSemaParam.initCount = 1;
    sndLockSemaParam.maxCount = 0;
    IosSndLock = CreateSema(&sndLockSemaParam);
    faultSemaParam.attr = 1;
    faultSemaParam.initCount = 1;
    faultSemaParam.maxCount = 0;
    systemFault = CreateSema(&faultSemaParam);
    stgMgrLockSemaParam.attr = 1;
    stgMgrLockSemaParam.initCount = 1;
    stgMgrLockSemaParam.maxCount = 0;
    IosStgMgrLock = CreateSema(&stgMgrLockSemaParam);
    D_00639ED8 = 0;
    InitKeyInput(0);
    debug_StdPrintfDummy("SgSndn2RemoteInit()\n");
    SgSndn2RemoteInit();
    sceSifInitIopHeap();
    debug_StdPrintfDummy("allocate IOP heap memory - \n");
    soundAllocIopHeap();
    soundInit();
    screen_offset_y = 0;
    fall_death_active = 0;
}

extern char D_0063A3E8[];
extern char D_0063A3F0[];
extern char D_0063A3F8[];
extern char D_0063A400[];
extern char D_0063A408[];
extern char D_0063A410[];
extern char D_0063A418[];
extern char D_0063A420[];
extern int D_0063A428;
extern int D_0063A42C;
extern int D_0063A430;
extern int D_0063A434;
extern int D_0063A438;
extern int D_0063A43C;
extern int D_0063A440;
extern int D_0063A444;
extern int D_0063A448;
extern int D_0063A44C;
extern int D_0063A450;
extern int D_0063A454;
extern int D_0063A458;
extern int D_0063A45C;
extern int D_0063A460;

void iosInitialize(void)
{
    debug_StdPrintfDummy("iosInitialize()\n");
    iosThreadInit();
    D_0063A428 = iosMallocInitPartition(0x760000, 0x1FEFFF0);
    D_0063A43C = iosMallocSetPartition(D_0063A428, 0x408000, 0x10);
    D_0063A444 = iosMallocSetPartition(D_0063A428, 0x120000, 0x10);
    D_0063A448 = iosMallocSetPartition(D_0063A428, 0x300000, 0x10);
    D_0063A42C = iosMallocSetPartition(D_0063A428, 0x40000, 0x10);
    D_0063A450 = iosMallocSetPartition(D_0063A428, 0x50000, 0x10);
    D_0063A454 = iosMallocSetPartition(D_0063A428, 1, 0x10);
    D_0063A458 = iosMallocSetPartition(D_0063A428, 0x8000, 0x10);
    D_0063A45C = iosMallocSetPartition(D_0063A428, 0x5000, 0x10);
    D_0063A460 = iosMallocSetPartition(D_0063A428, 0x2800, 0x10);
    D_0063A434 = iosMallocSetPartition(D_0063A428, 1, 0x10);
    /* the chain's store order is what the ROM's four gp stores record */
    D_0063A430 = D_0063A44C = D_0063A438 = D_0063A440 =
        iosMallocSetPartition(D_0063A428, 0xF18000, 0x10);
    iosMallocSetPartitionName(D_0063A430, D_0063A3E8);
    iosMallocSetPartitionName(D_0063A444, "stat mot");
    iosMallocSetPartitionName(D_0063A448, "demo mot");
    iosMallocSetPartitionName(D_0063A42C, D_0063A3F0);
    iosMallocSetPartitionName(D_0063A434, D_0063A3F8);
    iosMallocSetPartitionName(D_0063A450, D_0063A400);
    iosMallocSetPartitionName(D_0063A454, D_0063A408);
    iosMallocSetPartitionName(D_0063A458, D_0063A410);
    iosMallocSetPartitionName(D_0063A460, D_0063A418);
    iosMallocSetPartitionName(D_0063A43C, D_0063A420);
    iosMsgInit();
    ios_init_plus();
}
