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
#include "main.h"

/* main.c's own .data, VMA 0x0028F4C0..0x0028FEB8 (0x9F8 B), the six globals
   MAIN.MAP lists for main.o in ROM order. Each has an initialiser: the ROM
   holds them in .data, not .bss. systemStatus starts in PAL mode (word 0)
   at a frame step of 2 (word 1). db is the GS double buffer (libgraph's
   sceGsDBuff, 0x230 B), stageMgrMsg the stage manager's message
   (StageManager.c's StgMgrMsg, 0x18 B) and SchedulerMsgQ the scheduler's
   queue (message.c's IosMsgQueue, 0x30 B); those three records are still
   local to the TUs that read their fields, so this file holds them as words. */
int systemStatus[12] = {1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7};

int db[140] = {0};

StageSetting GlobalStageSetting = {{{0}}};

PadState pad[16] = {{0}};

int stageMgrMsg[6] = {0};

int SchedulerMsgQ[12] = {0};

/* main.c's own .sdata head, VMA 0x00639C80..0x00639CA8, in ROM order (the
   string literals Main, boot and main print land between these as the
   compiler meets them). NetLoadTARGET is MAIN.MAP's; the three counters are
   file statics, names ours. */
static int vsyncCount = 0; /* derived name: the scheduler's vsync count */

char NetLoadTARGET[] = "host0:";

static int frameReady = -1; /* derived name: Main's frame-done flag, -1 before the first frame */

static int lastVsyncCount = 0; /* derived name: movie_abort_check's last seen vsyncCount */

typedef struct {
    int *th[6];
} ThreadTbl;

/* main.c's own .bss, VMA 0x0063D010..0x00667340 (0x2A330 B, MAIN.MAP main.o
   .bss), in ROM order: the record and the stack of every thread this file
   starts, then the scheduler's message buffer. The map names none of them, so
   they are file statics; the names are ours, after jimaku.c's jimakuThread and
   jimakuThreadStack. A thread record is the ios thread object, 0x70 bytes, of
   which this file reads only the kernel id word at +0x30. */
static int idleThread[28]; /* derived name */

static char idleThreadStack[8192]; /* derived name */

static int mainThread[28]; /* derived name */

static char mainThreadStack[24576]; /* derived name */

static int schedulerThread[28]; /* derived name */

static char schedulerThreadStack[4096]; /* derived name */

static int mcThread[28]; /* derived name */

static char mcThreadStack[8192]; /* derived name */

static int cdvdThread[28]; /* derived name */

static char cdvdThreadStack[110592]; /* derived name */

static int stageManagerThread[28]; /* derived name */

static char stageManagerThreadStack[8192]; /* derived name */

static int soundThread[28]; /* derived name */

static char soundThreadStack[8192]; /* derived name */

static int schedulerMsgBuff[8]; /* derived name */

/* Main, idle, scheduler and boot open the object at VMA 0x00101C80. The
   listing records all four in main.c (lines 1011 to 1502); splat had left
   them inside the libkernl run that precedes them. */
extern char D_0054D6D8[];
extern char D_0054D6E8[];
/* kept local: this TU's uses of iosThreadCreate do not fit the prototype in thread.h, but the
 * stack size is that header's `long stackSize` and the ROM proves it: idle's first call passes
 * 0x1B000, and as an `int` the SImode large_int splitter in mips.md cuts it into lui and ori
 * before sched1, which then hoists the lui five slots ahead of its ori; as a `long` it stays one
 * DImode `dli` the assembler expands into the adjacent lui/ori pair the ROM has. */
extern void iosThreadCreate(void *th, int a1, void (*entry)(void), int a3, void *stack, long size,
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
extern int mpegPlay;
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
extern char D_0054D520[];
extern char D_0054D540[];
extern char D_0054D560[];
extern char D_0054D580[];
extern char D_0054D590[];
extern char D_0054D5A0[];
extern char D_0054D5B8[];
extern char D_005D3CE8[];
extern int mpegInitDone;
extern int mpegPlayInitColor;
extern int mpegPlayReturnStage;
extern float mpegPlayFadeInSpeed;
extern int D_0063A430;
extern int D_0063A468;
extern unsigned int D_0063B5F0;
extern int debug_TryToGetStartStage(void);
extern void debug_VariableInit(void);
extern void InitDelayFree(void);
extern void stgmgrForceSwitchWithFade(int stage, float a, float b);
extern void _InitRandom(float seed);
extern void gsb_InitGSSystem(void);
/* gsb_ResetSnap and gsb_TakeSnap return a value the callers drop, and the ROM
   proves it here: the load that follows each of the two calls takes $3, not
   $2, because local-alloc still has $2 live over the load's birth index for
   the call's unused result (mpegPlay after gsb_ResetSnap, systemFault after
   gsb_TakeSnap). Their definitions in ico2/seki/src/GsBase.c are empty, so the
   declaration is the only evidence; GsBase.o is byte-identical either way. */
extern int gsb_ResetSnap(void);
extern void AdpcmStreamFree(void);
extern void soundAllocIopFree(void);
extern int soundOutputModeGet(void);
extern void movie_init(void *p, int w, int h, int a3, int a4, int a5, int col);
extern int movie_proc(int (*abort)(void));
extern void soundAllocIopHeap(void);
extern void AdpcmStreamHeap(void);
extern void ACTGame_SetActors_Debug(int stage, int a1);
extern void gsb_Init(void *p);
extern void debug_ResetBar(void);
extern void MakeCollisionDependGObjList(void);
extern void MakeCharGObjList(void);
extern void ExecIcoMisc(void);
extern void stage_ResetAnimation(void);
extern void stage_CalcAnimationNoParent(void);
extern void iosOmMain(void);
extern void stage_CalcAnimationParent(void);
extern void iosOmCreateDL(void);
extern void ExecDelayFree(void);
extern int gsb_TakeSnap(void);
int movie_abort_check(void);

/* SRCFILE.TXT's Main also calls debug_Menu, debug_SetBar and debug_SetBar2
   (main.c:1110, 1176-1182, 1206-1209, 1250) and carries a frame-step block at
   1160-1167; the retail ELF has none of that code, so this build compiled it
   out and it is not spelled here. */
void Main(void)
{
    int ret;
    int n;

    debug_StdPrintfDummy(D_0054D520, systemStatus[0] == 0 ? "NTSC" : "PAL");
    debug_StdPrintfDummy(D_0054D540, systemStatus[1]);
    debug_StdPrintfDummy(D_0054D560, (60 - systemStatus[0] * 10) / systemStatus[1]);
    *(volatile int *)0x10000000 = 0;
    NonLinearCameraMove = 3;
    stage_no = 0;
    exit_no = 0;
    interlace = 1;
    GlobalTimer = 0;
    systemFault = 0;
    lock_execIcoMisc = 0;
    n = debug_TryToGetStartStage();
    thisIsYourStartStage = n < 106 ? n : 105;
    if (thisIsYourStartStage <= 0) {
        thisIsYourStartStage = 1;
    }
    debug_VariableInit();
    InitDelayFree();
    debug_StdPrintfDummy(D_0054D580);
    debug_StdPrintfDummy(D_0054D580);
    debug_StdPrintfDummy(D_0054D590, IosPadLock);
    WaitSema(IosPadLock);
    DeleteSema(IosPadLock);
    debug_StdPrintfDummy(D_0054D5A0, IosStgMgrLock);
    WaitSema(IosStgMgrLock);
    DeleteSema(IosStgMgrLock);
    stgmgrForceSwitchWithFade(thisIsYourStartStage < 0 ? 1 : thisIsYourStartStage, 255.0f, 0.0f);
    iosThreadCancelWakeup(0);
    systemStatus[5] = 0;
    _InitRandom(1.2345678f);
    gsb_InitGSSystem();
    debug_StdPrintfDummy(D_0054D5B8);
    while (1) {
        iosThreadCancelWakeup(0);
        iosThreadSleep();
        gsb_ResetSnap();
        if (mpegPlay != 0) {
            if (mpegInitDone == 0) {
                continue;
            }
            if (D_0063A3B8 != 0) {
                continue;
            }
            D_0063A468 = D_0063A430;
            AdpcmStreamFree();
            soundAllocIopFree();
            movie_init(&D_005D3CE8[mpegPlay * 0x20], 720, systemStatus[0] ? 576 : 480, 36, 12,
                       soundOutputModeGet() == 1, mpegPlayInitColor);
            ret = movie_proc(movie_abort_check);
            sceGsSyncV(0);
            soundAllocIopHeap();
            AdpcmStreamHeap();
            ACTGame_SetActors_Debug(mpegPlayReturnStage, 1);
            gsb_UpdateGSSystem(1);
            gsb_UpdateGSSystem(1);
            gsb_Init(db);
            mpegPlay = 0;
            stgmgrForceSwitchWithFade(mpegPlayReturnStage, 255.0f, mpegPlayFadeInSpeed);
            if (ret == 1) {
                D_0063B5F0 = 0xFFFFFFFE;
            }
            continue;
        }
        debug_ResetBar();
        MakeCollisionDependGObjList();
        MakeCharGObjList();
        ExecKeyInput();
        ExecIcoMisc();
        if (graphics_ready == 0) {
            stage_ResetAnimation();
            stage_CalcAnimationNoParent();
        }
        iosOmMain();
        if (graphics_ready == 0) {
            stage_CalcAnimationParent();
        }
        iosOmCreateDL();
        ExecDelayFree();
        gsb_TakeSnap();
        frameReady = 1;
        if (systemFault != 0) {
            break;
        }
    }
    while (1) {
        iosThreadSleep();
    }
}

extern char D_0054D5C8[];
extern char D_0054D5D8[];
extern char D_0054D618[];
extern char D_0054D640[];
extern char jimakuThread[];
extern char jimakuThreadStack[];
extern void iosCdvdManager(void);
extern void iosMcManager(void);
extern void jimakuManager(void);
extern void sndManager(void);
extern void Main(void);
extern void iosThreadSetPri(int id, int pri);

/* main.c's own first two small-bss cells, at 0x0063C100 and 0x0063C104, ahead of
   the boot thread id: the idle thread's spin counters. The names are ours. */
static int idleCount;

static int idleLoop;

void idle(void)
{
    debug_StdPrintfDummy(D_0054D5C8);
    debug_StdPrintfDummy(D_0054D5D8);
    iosThreadCreate(cdvdThread, 6, iosCdvdManager, 0, cdvdThreadStack, sizeof(cdvdThreadStack),
                    0x1C);
    iosThreadStart(cdvdThread);
    iosThreadCreate(stageManagerThread, 7, StageManager, 0, stageManagerThreadStack,
                    sizeof(stageManagerThreadStack), 0x1B);
    iosThreadStart(stageManagerThread);
    iosThreadCreate(mcThread, 5, iosMcManager, 0, mcThreadStack, sizeof(mcThreadStack), 0x1B);
    iosThreadStart(mcThread);
    iosThreadCreate(jimakuThread, 9, jimakuManager, 0, jimakuThreadStack, 0x2000, 0x1B);
    iosThreadStart(jimakuThread);
    iosThreadCreate(soundThread, 8, sndManager, 0, soundThreadStack, sizeof(soundThreadStack),
                    0x10);
    iosThreadStart(soundThread);
    iosThreadCreate(mainThread, 3, Main, 0, mainThreadStack, sizeof(mainThreadStack), 0x1B);
    iosThreadStart(mainThread);
    debug_StdPrintfDummy(D_0054D618);
    iosThreadSetPri(0, 0x20);
    while (1) {
        idleCount++;
        if (idleCount < 10000000) {
            continue;
        }
        idleCount = 0;
        idleLoop++;
        debug_StdPrintfDummy(D_0054D640, idleLoop);
    }
}

static int frameStepCount =
    0; /* derived name: vsyncs counted toward systemStatus[1], the frame step */

void scheduler(void)
{
    int msg[4];

    debug_StdPrintfDummy(D_0054D650);
    sceGsSyncV(0);
    iosMsgQueueCreate(SchedulerMsgQ, schedulerMsgBuff, 8);
    iosMsgSetEvent(2, SchedulerMsgQ, 2);
    while (1) {
        iosMsgRecv(SchedulerMsgQ, msg, 1);
        if (msg[0] == 2) {
            vsyncCount++;
            frameStepCount++;
            if (frameStepCount >= systemStatus[1] && stageManagerFreeResourceFlag == 0) {
                if (frameReady > 0) {
                    if (mpegPlay != 0) {
                        frameReady = 0;
                        goto wake;
                    }
                    if (gsb_SyncGSSystem() != 0) {
                        goto skip;
                    }
                    _PushVu0Registers();
                    gsb_UpdateGSSystem(0);
                    _PopVu0Registers();
                    if (systemStatus[5] != 0) {
                        if (iosCdvdDiskStatusGet() != 0) {
                            frameReady = 0;
                            goto wake;
                        }
                    }
                    lock_execIcoMisc++;
                }
                frameReady = 0;
            wake:
                iosThreadCancelWakeup(mainThread);
                startStagePauseDisableTimer++;
                if (iosThreadWakeup(mainThread) < 0) {
                    debug_StdPrintfDummy(D_0054D660);
                }
                frameStepCount = 0;
            }
        skip:
            iosThreadWakeup(soundThread);
            if (D_0063A47C >= 0) {
                SignalSema(D_0063A47C);
            }
            if (D_0063A368 != 0 && (mpegPlay == 0 || D_0063A3B8 != 0)) {
                iosThreadWakeup(cdvdThread);
            }
            if (stgMgrWakeupRequest != 0) {
                iosThreadWakeup(stageManagerThread);
            }
            la_playtime_count();
        } else {
            debug_StdPrintfDummy(D_0054D688);
        }
    }
}

void boot(void)
{
    debug_StdPrintfDummy("boot()\n");
    debug_StdPrintfDummy(D_0054D6D8);
    file_Init();
    debug_StdPrintfDummy(D_0054D6E8);
    iosInitialize();
    gflagInit();
    systemStatus[2] = 1;
    stage_no = 1;
    CheckPoint();
    iosThreadCreate(idleThread, 1, idle, 0, idleThreadStack, sizeof(idleThreadStack), 0x1B);
    iosThreadStart(idleThread);
    iosThreadCreate(schedulerThread, 1, scheduler, 0, schedulerThreadStack,
                    sizeof(schedulerThreadStack), 0xF);
    iosThreadStart(schedulerThread);
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
    if (lastVsyncCount != vsyncCount) {
        lastVsyncCount = vsyncCount;
        ExecKeyInput();
        ret = 0;
        ret = (pad[0].flags & 0x800) != ret;
    }
    return ret;
}

void demoEnd(void) {}

/* main.c's own small-bss cell at 0x0063C108, the boot thread id. It has to be a
   DEFINITION in this TU rather than an extern off the sbss run base: gas emits a
   non-macro gp-relative store only for a symbol it already knows is small, and
   only a non-macro store is swapped into the `jal boot` delay slot. The name is
   ours; MAIN.MAP does not name the cell. */
static int bootThreadId;

int main(void)
{
    debug_StdPrintfDummy("main\n");
    debug_StdPrintfDummy("main\n");
    ChangeThreadPriority(GetThreadId(), 14);
    bootThreadId = GetThreadId();
    boot();
    return 0;
}

/* main.c's globals, VMA 0x00639CC0..0x00639EE0 in .sdata, in ROM order. They
   follow main's literal in the section, so they are defined here, after main.
   MAIN.MAP lists 38 of them. The PAL build adds six (marked derived), and its
   layout is the January map's shifted by one inserted quadword after game_pause
   and by the girl-control block before boyGObj; the ROM pins each placement by
   its accessors and the strings the lock words are printed with ("IosPadLock %d"
   in Main, "IosCdLock %d" in StageManager, "IosSndLock %d" in sndManager,
   "IosstgMgrLock %d" in Main). Each word is a 4-byte scalar (every $gp access
   is lw, sw or lwc1). The ones marked QWORD open a 16-byte quadword of their
   own: the ROM leaves the rest of that quadword empty, which only an
   alignment of 16 on the object produces. */
#define QWORD __attribute__((aligned(16)))

int buffer_ID QWORD = 0;

int odd_even QWORD = 0;

int frame_count QWORD = 0;

char *matrixptr QWORD = 0;

int debugMoveMode QWORD = 0;

int stage_no QWORD = 0;

int before_stage_no QWORD = 0;

int exit_no QWORD = 0;

int motionFrameUpdate QWORD = 0;

int interlace QWORD = 0;

int thisIsYourStartStage QWORD = 0;

int NonLinearCameraMove QWORD = 0;

int GlobalTimer QWORD = 0;

int lock_execIcoMisc QWORD = 0;

int graphics_ready QWORD = 0;

int game_pause QWORD = 0;

int data_loading QWORD = 0;

static int reservedWord QWORD =
    0; /* derived name: the PAL build's inserted, unreferenced quadword */

int screen_offset_x QWORD = 0;

int screen_offset_y QWORD = 0;

int fall_death_active QWORD = 0;

int title_fading_out QWORD = 0;

int collis_flg_stock QWORD = 0;

int IosPadLock QWORD = 0;

int IosCdLock QWORD = 0;

int IosSndLock QWORD = 0;

int IosStgMgrLock QWORD = 0;

int systemFault QWORD = 0;

int optionControlType QWORD =
    0; /* derived name: the 0/1 game option that selects the pad word +0x2E0 or +0x2E4 the actions read */

int optionScreenMode QWORD =
    0; /* derived name: the five-way game option GsBase indexes its per-mode tint and blur rows with */

int girlControlMode QWORD =
    0; /* derived name: ChangeGirlControlMode's flag, the game option that hands the girl to pad 2 */

GObj *boyGObj = 0;

GObj *girlGObj = 0;

int boyPad = 0;

int girlPad = 0; /* derived name: the girl's pad word, girl_act's +0x2D8, boyPad's twin */

int gameover_flag = 0;

int gameover_layout_flag = 0;

int itemWatchOff = 0; /* derived name: ACTItemWatchMotion runs for the boy only while it is 0 */

GObj *CurrentTargetGObj = 0;

GObj *CurrentTargetGObjSub QWORD = 0;

int current_stage_no = 0;

void (*system_stage_func)(void) = 0;

int InterStageSwitchLock = 0;
