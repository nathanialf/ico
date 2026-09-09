#include "common.h"

extern char D_00551058[];
extern int D_0063A3E0;
extern int sceSifAllocIopHeap(int size);
extern void debug_StdPrintfDummy(char *fmt, ...);
/* prototypes: their order is the inline tail's emission order */
int iosSifAllocIopHeapDebug(int size, char *file, int line);

inline int iosSifAllocIopHeapDebug(int size, char *file, int line)
{
    int p = sceSifAllocIopHeap(size);

    if (p == 0) {
        debug_StdPrintfDummy(D_00551058, file, line);
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
    int attr; /* 0x10 */
    char _p14[0xC];
} SemaParam;

extern SemaParam D_006BC860;
extern SemaParam D_006BC878;
extern SemaParam D_006BC890;
extern SemaParam D_006BC8A8;
extern int IosCdLock;
extern int IosSndLock;
extern int systemFault;
extern int IosStgMgrLock;
extern int D_00639ED8;
extern int screen_offset_y;
extern int fall_death_active;
extern char D_00551088[];
extern char D_005510A0[];
extern int CreateSema(SemaParam *p);
extern void InitKeyInput();
extern void SgSndn2RemoteInit(void);
extern void sceSifInitIopHeap(void);
extern void soundAllocIopHeap(void);
extern void soundInit(void);

void ios_init_plus(void)
{
    D_006BC860.attr = 1;
    D_006BC860.initCount = 1;
    D_006BC860.maxCount = 0;
    IosCdLock = CreateSema(&D_006BC860);
    D_006BC890.attr = 1;
    D_006BC890.initCount = 1;
    D_006BC890.maxCount = 0;
    IosSndLock = CreateSema(&D_006BC890);
    D_006BC878.attr = 1;
    D_006BC878.initCount = 1;
    D_006BC878.maxCount = 0;
    systemFault = CreateSema(&D_006BC878);
    D_006BC8A8.attr = 1;
    D_006BC8A8.initCount = 1;
    D_006BC8A8.maxCount = 0;
    IosStgMgrLock = CreateSema(&D_006BC8A8);
    D_00639ED8 = 0;
    InitKeyInput(0);
    debug_StdPrintfDummy(D_00551088);
    SgSndn2RemoteInit();
    sceSifInitIopHeap();
    debug_StdPrintfDummy(D_005510A0);
    soundAllocIopHeap();
    soundInit();
    screen_offset_y = 0;
    fall_death_active = 0;
}

extern char D_005510C0[];
extern char D_005510D8[];
extern char D_005510E8[];
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
extern void iosThreadInit(void);
extern int iosMallocInitPartition(int base, int size);
extern int iosMallocSetPartition(int part, int size, int align);
extern void iosMallocSetPartitionName(int part, char *name);
extern void iosMsgInit(void);
extern void ios_init_plus(void);

void iosInitialize(void)
{
    debug_StdPrintfDummy(D_005510C0);
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
    iosMallocSetPartitionName(D_0063A444, D_005510D8);
    iosMallocSetPartitionName(D_0063A448, D_005510E8);
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
