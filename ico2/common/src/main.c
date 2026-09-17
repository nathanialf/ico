#include "common.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_action.h"
#include "cdvd.h"
#include "ios.h"
#include "message.h"
#include "gflag.h"
#include "FileManager.h"
#include "GsBase.h"
#include "Matrix.h"
#include "keyInput.h"
#include <eekernel.h>

extern int D_0028F8F4[];
extern int D_00639C80;
extern int D_00639C94;

typedef struct {
    int *th[6];
} ThreadTbl;

/* Main, idle, scheduler and boot open the object at VMA 0x00101C80. The
   listing records all four in main.c (lines 1011 to 1502); splat had left
   them inside the libkernl run that precedes them. */
extern char D_00639CA8[];
extern char D_0054D6D8[];
extern char D_0054D6E8[];
extern char D_0063D010[];
extern char D_0063D080[];
extern char D_006450F0[];
extern char D_00645160[];
extern int D_0028F4C8[];
extern int stage_no;
/* kept local: this TU's uses of iosThreadCreate do not fit the prototype in thread.h */
extern void iosThreadCreate(void *th, int a1, void (*entry)(void), int a3, void *stack, int size,
                            int pri);
/* kept local: this TU's uses of iosThreadStart do not fit the prototype in thread.h */
extern void iosThreadStart(void *th);
/* kept local: this TU's uses of iosThreadSleep do not fit the prototype in thread.h */
extern void iosThreadSleep(void);
void idle(void);
void scheduler(void);
extern char D_0054D650[];
extern char D_0054D660[];
extern char D_0054D688[];
extern int D_0028F4C0[];
extern char D_0028FE88[];
extern char D_00667320[];
extern char D_0063F080[];
extern char D_006652B0[];
extern char D_006481D0[];
extern char D_00663240[];
extern int D_00639C90;
extern int D_00639CA4;
extern int mpegPlay;
extern int lock_execIcoMisc;
extern int stageManagerFreeResourceFlag;
extern int startStagePauseDisableTimer;
extern int stgMgrWakeupRequest;
extern int D_0063A368;
extern int D_0063A3B8;
extern int D_0063A47C;
extern void sceGsSyncV(int mode);
/* kept local: this TU's uses of iosThreadCancelWakeup do not fit the prototype in thread.h */
extern int iosThreadCancelWakeup(void *th);
/* kept local: this TU's uses of iosThreadWakeup do not fit the prototype in thread.h */
extern int iosThreadWakeup(void *th);

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/main", Main);
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/main", idle);

void scheduler(void)
{
    int msg[4];

    debug_StdPrintfDummy(D_0054D650);
    sceGsSyncV(0);
    iosMsgQueueCreate(D_0028FE88, D_00667320, 8);
    iosMsgSetEvent(2, D_0028FE88, 2);
    while (1) {
        iosMsgRecv(D_0028FE88, msg, 1);
        if (msg[0] == 2) {
            D_00639C80++;
            D_00639CA4++;
            if (D_00639CA4 >= D_0028F4C0[1] && stageManagerFreeResourceFlag == 0) {
                if (D_00639C90 > 0) {
                    if (mpegPlay != 0) {
                        D_00639C90 = 0;
                        goto wake;
                    }
                    if (gsb_SyncGSSystem() != 0) {
                        goto skip;
                    }
                    _PushVu0Registers();
                    gsb_UpdateGSSystem(0);
                    _PopVu0Registers();
                    if (D_0028F4C0[5] != 0) {
                        if (iosCdvdDiskStatusGet() != 0) {
                            D_00639C90 = 0;
                            goto wake;
                        }
                    }
                    lock_execIcoMisc++;
                }
                D_00639C90 = 0;
            wake:
                iosThreadCancelWakeup(D_0063F080);
                startStagePauseDisableTimer++;
                if (iosThreadWakeup(D_0063F080) < 0) {
                    debug_StdPrintfDummy(D_0054D660);
                }
                D_00639CA4 = 0;
            }
        skip:
            iosThreadWakeup(D_006652B0);
            if (D_0063A47C >= 0) {
                SignalSema(D_0063A47C);
            }
            if (D_0063A368 != 0 && (mpegPlay == 0 || D_0063A3B8 != 0)) {
                iosThreadWakeup(D_006481D0);
            }
            if (stgMgrWakeupRequest != 0) {
                iosThreadWakeup(D_00663240);
            }
            la_playtime_count();
        } else {
            debug_StdPrintfDummy(D_0054D688);
        }
    }
}

void boot(void)
{
    debug_StdPrintfDummy(D_00639CA8);
    debug_StdPrintfDummy(D_0054D6D8);
    file_Init();
    debug_StdPrintfDummy(D_0054D6E8);
    iosInitialize();
    gflagInit();
    D_0028F4C8[0] = 1;
    stage_no = 1;
    CheckPoint();
    iosThreadCreate(D_0063D010, 1, idle, 0, D_0063D080, 0x2000, 0x1B);
    iosThreadStart(D_0063D010);
    iosThreadCreate(D_006450F0, 1, scheduler, 0, D_00645160, 0x1000, 0xF);
    iosThreadStart(D_006450F0);
    iosThreadSleep();
}

extern ThreadTbl D_0054D508;
/* kept local: this TU's uses of iosThreadDestroy do not fit the prototype in thread.h */
extern void iosThreadDestroy(int *th);

void Emergency_DestroyAllThread(void)
{
    int me = GetThreadId();
    ThreadTbl t = D_0054D508;
    unsigned int i;

    for (i = 0; i < 6; i++) {
        if (me != t.th[i][0x30 / 4]) {
            iosThreadDestroy(t.th[i]);
        }
    }
}

int movie_abort_check(void)
{
    int ret = 0;
    if (D_00639C94 != D_00639C80) {
        D_00639C94 = D_00639C80;
        ExecKeyInput();
        ret = 0;
        ret = (D_0028F8F4[0] & 0x800) != ret;
    }
    return ret;
}

void demoEnd(void) {}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/main", main);
