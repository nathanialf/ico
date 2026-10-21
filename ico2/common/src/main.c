#include "StageManager.h"
#include "mcard.h"
#include "debug.h"
#include "layout_action.h"
#include "cdvd.h"
#include "jimaku.h"
#include "ios.h"
#include "message.h"
#include "gflag.h"
#include "FileManager.h"
#include "GsBase.h"
#include "Matrix.h"
#include "keyInput.h"
#include "pad.h"
#include <eekernel.h>
#include "main.h"
#include <eeregs.h>
#include "s_init.h"
#include "delayFreeManager.h"
#include "adpcm_init.h"
#include "fieldCollision.h"
#include "icoMisc.h"
#include "soundManager.h"
#include "thread.h"
#include "act-game.h"
#include "obj_manager.h"
#include "StageAnimation.h"
#include "mv_main.h"
#include "geometryManager.h"
#include "libgraph.h"
#include <stdlib.h>
#include <libcdvd.h>
#include <sound.h>
#include <sifrpc.h>

/* main.c's .data globals, each with an initialiser. systemStatus starts in PAL mode (word 0;
   NTSC on JPN)
   at a frame step of 2 (word 1). db is the GS double buffer (libgraph's
   sceGsDBuff, 0x230 B), stageMgrMsg the stage manager's message (main.h's
   StgMgrMsg, 0x18 B) and SchedulerMsgQ the scheduler's queue (message.c's
   IosMsgQueue, 0x30 B). */
int systemStatus[12] = {0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7};

sceGsDBuff db = {{{0}}};

StageSetting GlobalStageSetting = {{{0}}};

PadState pad[16] = {{0}};

StgMgrMsg stageMgrMsg = {0};

IosMsgQueue SchedulerMsgQ = {0};

/* .sdata: the scheduler's counters and the network load target */
static int vsyncCount = 0; /* derived name */ /* the scheduler's vsync count */

char NetLoadTARGET[] = "host0:";

/* Main's frame-done flag, -1 before the first frame */
static int frameReady = -1; /* derived name */

static int lastVsyncCount = 0; /* derived name */ /* movie_abort_check's last seen vsyncCount */

typedef struct { /* field names derived */
    IOSThread *th[6];
} ThreadTbl; /* derived name */

/* .bss: the record and the stack of every thread this file starts, then the
   scheduler's message buffer, named after jimaku.c's jimakuThread and
   jimakuThreadStack. A thread record is the ios thread object, 0x70 bytes, of
   which this file reads only the kernel id word at +0x30.  Each stack is
   16-byte aligned, as the kernel's CreateThread requires. */
static IOSThread idleThread; /* derived name */

static char idleThreadStack[8192] __attribute__((aligned(16))); /* derived name */

static IOSThread mainThread; /* derived name */

static char mainThreadStack[24576] __attribute__((aligned(16))); /* derived name */

static IOSThread schedulerThread; /* derived name */

static char schedulerThreadStack[4096] __attribute__((aligned(16))); /* derived name */

static IOSThread mcThread; /* derived name */

static char mcThreadStack[8192] __attribute__((aligned(16))); /* derived name */

static IOSThread cdvdThread; /* derived name */

static char cdvdThreadStack[110592] __attribute__((aligned(16))); /* derived name */

static IOSThread stageManagerThread; /* derived name */

static char stageManagerThreadStack[8192] __attribute__((aligned(16))); /* derived name */

static IOSThread soundThread; /* derived name */

static char soundThreadStack[8192] __attribute__((aligned(16))); /* derived name */

static int schedulerMsgBuff[8]; /* derived name */

/* the pad handle and the two stick readings func_00102618 reads each frame
   for the demo disc's idle countdown */
static IosPadCtx demoIdlePad; /* derived name */

static IosPadStick demoIdleStickL; /* derived name */

static IosPadStick demoIdleStickR; /* derived name */

/* the six threads Emergency_DestroyAllThread tears down, every thread boot
   starts except idle; first in this object's .rodata, ahead of Main's
   strings, so it is defined here with the records it points at */
static const ThreadTbl allThreads = {{&mainThread, &schedulerThread, &mcThread, &cdvdThread,
                                      &stageManagerThread, &soundThread}}; /* derived name */

static void idle(void);
static void scheduler(void);
/* motionOrientManager.h carries MotOriName and declares no movieFile */
extern char movieFile[];
int movie_abort_check(void);
/* the development build's Main also called debug_Menu, debug_SetBar and
   debug_SetBar2 and carried a frame-step block; the retail build compiled
   them out. */
void Main(void);

void Main(void)
{
    int n;

    debug_StdPrintfDummy("VSYNC_TIMING    : \x1b[33m%s\x1b[m\n",
                         systemStatus[0] == 0 ? "NTSC" : "PAL");
    debug_StdPrintfDummy("FRAME_STEP      : \x1b[33m%d\x1b[m\n", systemStatus[1]);
    debug_StdPrintfDummy("SYSTEM_FRAMERATE: \x1b[33m%d\x1b[m\n",
                         (60 - systemStatus[0] * 10) / systemStatus[1]);
    stage_no = 0;
    *T0_COUNT = 0;
    exit_no = 0;
    interlace = 1;
    currentScreenWidth = 0;
    systemFault = 0;
    GlobalTimer = 0;
    n = debug_TryToGetStartStage();
    thisIsYourStartStage = n < 103 ? n : 102;
    if (thisIsYourStartStage <= 0) {
        thisIsYourStartStage = 1;
    }
    debug_VariableInit();
    InitDelayFree();
    debug_StdPrintfDummy("Main() in\n");
    debug_StdPrintfDummy("Main() in\n");
    debug_StdPrintfDummy("IosPadLock %d\n", IosPadLock);
    WaitSema(IosPadLock);
    DeleteSema(IosPadLock);
    debug_StdPrintfDummy("IosstgMgrLock %d\n", IosStgMgrLock);
    WaitSema(IosStgMgrLock);
    DeleteSema(IosStgMgrLock);
    /* the demo disc always opens on stage 92 */
    thisIsYourStartStage = 92;
    stgmgrForceSwitchWithFade(thisIsYourStartStage, 255.0f, 16.0f);
    iosThreadCancelWakeup(0);
    systemStatus[5] = 0;
    _InitRandom(1.2345678f);
    gsb_InitGSSystem();
    debug_StdPrintfDummy("main start\n");
    while (1) {
        iosThreadCancelWakeup(0);
        iosThreadSleep();
        if (mpegPlay != 0) {
            /* derived: ret is zeroed where it is declared, as movie_abort_check
               does; movie_proc's result replaces the zero, so it leaves no
               word, but loop.c counts it, which keeps the -2 below in the
               loop (pinned) */
            int ret = 0;

            if (mpegInitDone == 0) {
                continue;
            }
            if (iosCdvdBackGroundMgrRunning != 0) {
                continue;
            }
            ios_partition_mpeg = ios_partition_isys;
            movie_init(&movieFile[mpegPlay * 0x20], 720, 480, 36, 12, soundOutputModeGet() == 1,
                       mpegPlayInitColor);
            ret = movie_proc(movie_abort_check);
            mpegPlay = 0;
            ACTGame_SetActors_Debug(mpegPlayReturnStage, 1);
            gsb_Init(&db);
            stgmgrForceSwitchWithFade(mpegPlayReturnStage, 255.0f, mpegPlayFadeInSpeed);
            if (ret == 1) {
                stage_after_skipping_demo = 0xFFFFFFFE;
            }
            continue;
        }
        MakeCollisionDependGObjList();
        MakeCharGObjList();
        ExecKeyInput();
        ExecIcoMisc();
        if (graphics_ready == 0) {
            stage_CalcAnimationNoParent();
        }
        iosOmMain();
        if (graphics_ready == 0) {
            stage_CalcAnimationParent();
        }
        iosOmCreateDL();
        ExecDelayFree();
        frameReady = 1;
        if (systemFault != 0) {
            break;
        }
    }
    while (1) {
        iosThreadSleep();
    }
}

/* .sbss: the idle thread's spin counters */
static int idleCount; /* derived name */

static int idleLoop; /* derived name */

static void idle(void)
{
    debug_StdPrintfDummy("idle() in\n");
    debug_StdPrintfDummy("--------------------------------------------------------------\n");
    iosThreadCreate(&cdvdThread, 6, iosCdvdManager, 0, cdvdThreadStack, sizeof(cdvdThreadStack),
                    0x1C);
    iosThreadStart(&cdvdThread);
    iosThreadCreate(&stageManagerThread, 7, StageManager, 0, stageManagerThreadStack,
                    sizeof(stageManagerThreadStack), 0x1B);
    iosThreadStart(&stageManagerThread);
    iosThreadCreate(&mcThread, 5, iosMcManager, 0, mcThreadStack, sizeof(mcThreadStack), 0x1B);
    iosThreadStart(&mcThread);
    iosThreadCreate(&jimakuThread, 9, jimakuManager, 0, jimakuThreadStack, 0x2000, 0x1B);
    iosThreadStart(&jimakuThread);
    iosThreadCreate(&soundThread, 8, sndManager, 0, soundThreadStack, sizeof(soundThreadStack),
                    0x10);
    iosThreadStart(&soundThread);
    iosThreadCreate(&mainThread, 3, Main, 0, mainThreadStack, sizeof(mainThreadStack), 0x1B);
    iosThreadStart(&mainThread);
    debug_StdPrintfDummy("--- loop continues infinitely ... ---\n");
    iosThreadSetPri(0, 0x20);
    while (1) {
        idleCount++;
        if (idleCount < 10000000) {
            continue;
        }
        idleCount = 0;
        idleLoop++;
        debug_StdPrintfDummy("idle time:%d\n", idleLoop);
    }
}

/* vsyncs counted toward systemStatus[1], the frame step */
static int frameStepCount = 0; /* derived name */

static void scheduler(void)
{
    int msg[4];

    debug_StdPrintfDummy("scheduler() in\n");
    iosMsgQueueCreate(&SchedulerMsgQ, schedulerMsgBuff, 8);
    iosMsgSetEvent(2, &SchedulerMsgQ, 2);
    while (1) {
        iosMsgRecv(&SchedulerMsgQ, msg, 1);
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
                    gsb_UpdateGSSystem();
                    if (systemStatus[5] != 0) {
                        if (iosCdvdDiskStatusGet() != 0) {
                            frameReady = 0;
                            goto wake;
                        }
                    }
                    GlobalTimer++;
                }
                frameReady = 0;
            wake:
                iosThreadCancelWakeup(&mainThread);
                if (iosThreadWakeup(&mainThread) < 0) {
                    /* failed to start the main thread */
                    debug_StdPrintfDummy("メーンスレッドの起動失敗しました\n");
                }
                frameStepCount = 0;
            }
        skip:
            iosThreadWakeup(&soundThread);
            if (IosMcLock >= 0) {
                SignalSema(IosMcLock);
            }
            if (IosCdvdMgrSleep != 0 && (mpegPlay == 0 || iosCdvdBackGroundMgrRunning != 0)) {
                iosThreadWakeup(&cdvdThread);
            }
            if (stgMgrWakeupRequest != 0) {
                iosThreadWakeup(&stageManagerThread);
            }
        } else {
            /* an unknown message arrived */
            debug_StdPrintfDummy("不明なメッセージの着信を確認しました in Scheduler\n");
        }
    }
    /* unreachable: the loop above never exits */
    debug_StdPrintfDummy("scheduler() out\n");
}

static void boot(void)
{
    debug_StdPrintfDummy("boot()\n");
    debug_StdPrintfDummy("file init\n");
    file_Init();
    debug_StdPrintfDummy("iosInit\n");
    iosInitialize();
    gflagInit();
    systemStatus[2] = 1;
    stage_no = 1;
    CheckPoint();
    iosThreadCreate(&idleThread, 1, idle, 0, idleThreadStack, sizeof(idleThreadStack), 0x1B);
    iosThreadStart(&idleThread);
    iosThreadCreate(&schedulerThread, 1, scheduler, 0, schedulerThreadStack,
                    sizeof(schedulerThreadStack), 0xF);
    iosThreadStart(&schedulerThread);
    iosThreadSleep();
}

/* the boot thread's kernel id, which func_001025F0 wakes */
static int bootThreadId; /* derived name */

/* demoDisc.c's pair, whose names this build does not record: the first
   keeps the arguments the magazine menu started the game with and reads the
   disc's settings out of them, the second (DemoDiscEnd) reloads the menu
   with them */
int func_00246828(int argc, char **argv, unsigned short *language, unsigned short *aspect,
                  unsigned short *playmode, unsigned short *toInactive, unsigned short *toTotal,
                  unsigned short *mediaType);

void DemoDiscEnd(int status);
/* thread.c defines it `inline` with no header declaration */
void iosThreadAllQuit(int self);

/* the demo disc's entry: it reads the menu's settings, runs the game until
   func_001025F0 wakes it, shuts the game down and goes back to the menu */
int main(int argc, char **argv)
{
    unsigned short language;
    unsigned short aspect;
    unsigned short playmode;
    unsigned short toInactive;
    unsigned short toTotal;
    unsigned short mediaType;
    int i;

    func_00246828(argc, argv, &language, &aspect, &playmode, &toInactive, &toTotal, &mediaType);
    debug_StdPrintfDummy("l %d a %d pm %d toa %d tot %d\n", language, aspect, playmode, toInactive,
                         toTotal);
    debug_StdPrintfDummy("MEDIA TYpE %d\n", mediaType);
    sampleModeStageInit();
    if (mediaType == 0) {
        iosCdvdMediaType = 1;
    } else {
        iosCdvdMediaType = 2;
    }
    debug_StdPrintfDummy("main\n");
    debug_StdPrintfDummy("main\n");
    ChangeThreadPriority(GetThreadId(), 14);
    bootThreadId = GetThreadId();
    boot();
    iosThreadAllQuit(bootThreadId);
    SgQuit();
    SgInit();
    i = 10;
    while (i--) {
        sceGsSyncV(0);
    }
    sceFsReset();
    sceGsResetPath();
    sceVpu0Reset();
    gsb_InitGSSystem();
    sceSifExitCmd();
    debug_StdPrintfDummy("demo end !!!!!!!!!!!!!!!!!!\n");
    DemoDiscEnd(5);
    return 0;
}

void Emergency_DestroyAllThread(void)
{
    int me = GetThreadId();
    ThreadTbl t = allThreads;
    unsigned int i;

    for (i = 0; i < 6; i++) {
        if (me != t.th[i]->id) {
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

/* the demo disc's idle countdown: sampleModeNoContTimeOutMain counts it
   down each frame the pads are idle and resets it on input;
   sampleModeStageInit and sampleModeExec set it */
static int demoIdleTimeout; /* derived name */

/* the demo disc's frames for one second: 60 on NTSC, 50 on PAL, over the
   frame step */
#define FRAME_RATE ((60 - systemStatus[0] * 10) / systemStatus[1]) /* derived name */

/* ends the demo: wakes the boot thread, which hands the disc back, and
   sleeps for good (demoEnd in the PAL and Aug-6 maps, which e3.c's static
   flag of that name rules out here) */
void func_001025F0(void) /* derived name */
{
    WakeupThread(bootThreadId);
    while (1) {
        iosThreadSleep();
    }
}

/* counts the idle timeout down while nobody touches the pad, and winds it
   back to four minutes on any button or stick */
void sampleModeNoContTimeOutMain(void)
{
    if (iosPadEnableGet() == 0) {
        demoIdleTimeout = FRAME_RATE * 240;
        return;
    }
    iosPadRead(&demoIdlePad);
    iosPadGetStick(&demoIdlePad, &demoIdleStickL, 0, 2, 2, 0);
    iosPadGetStick(&demoIdlePad, &demoIdleStickR, 1, 2, 2, 0);
    if (demoIdlePad.trg != 0 || demoIdleStickL.mag > 0.1f || demoIdleStickR.mag > 0.1f) {
        demoIdleTimeout = FRAME_RATE * 240;
    } else {
        demoIdleTimeout--;
    }
}

/* the two ways out of the demo: to stage 101, and to stage 102 when the
   timeout runs out or the player quits; the movie returns to stage 92 */
void sampleModeDemoEnd(void)
{
    systemStatus[5] = 1;
    mpegPlayReturnStage = 92;
    InterStageSwitchLock++;
    stgmgrForceSwitchWithFade(101, 4.0f, 4.0f);
}

void sampleModeDemoEndTimeOut(void)
{
    systemStatus[5] = 1;
    mpegPlayReturnStage = 92;
    InterStageSwitchLock++;
    stgmgrForceSwitchWithFade(102, 4.0f, 4.0f);
}

void sampleModeStageInit(void)
{
    iosPadConnect(&demoIdlePad, 0, 0, &iosPadConfDefault);
    demoIdleTimeout = FRAME_RATE * 240;
}

void sampleModeExec(void)
{
    sampleModeNoContTimeOutMain();
    if (demoIdleTimeout < 0 && systemStatus[6] == 0 && graphics_ready == 0) {
        sampleModeDemoEndTimeOut();
        demoIdleTimeout = FRAME_RATE * 240;
    }
}

/* main.c's .sdata globals.  Both builds add six to the January map's (marked
   derived): one quadword after game_pause and the girl-control block before
   boyGObj.  Each is a 4-byte scalar; the ones marked QWORD open a 16-byte
   quadword of their own, the rest of which stays empty. */
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

/* the screen width GsBase and the effects read: this build keeps it here, in
   main.o's .sdata (0x679470), where PAL has NonLinearCameraMove */
int currentScreenWidth QWORD = 0;

int GlobalTimer QWORD = 0;

/* graphics_ready comes first in this build (0x679490): the stage manager's
   switch sets it, InitIcoMisc clears it, the main loop, the stage animation and
   the script read it; the frame counter after game_pause has no reader */
int graphics_ready QWORD = 0;

/* game_pause comes first in this build (0x6794A0) */
int game_pause QWORD = 0;

int lock_execIcoMisc QWORD = 0;

int data_loading QWORD = 0;

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

/* This build has none of PAL's option words (optionControlType,
   optionScreenMode, girlControlMode), nor its girlPad or reserved quadword:
   no word of the demo's .text addresses them, and boyGObj follows systemFault
   in the demo's .sdata. */
GObj *boyGObj = 0;

GObj *girlGObj = 0;

/* the boy's pad handle, the Act.pad his actor connects */
IosPadCtx *boyPad = 0;

int gameover_flag = 0;

int gameover_layout_flag = 0;

/* ACTItemWatchMotion runs for the boy only while it is 0 */
int itemWatchOff = 0; /* derived name */

/* 16-aligned in the demo (0x679580, after zero fill) */
GObj *CurrentTargetGObj QWORD = 0;

GObj *CurrentTargetGObjSub QWORD = 0;

int current_stage_no = 0;

void (*system_stage_func)(void) = 0;

/* 16-aligned in the demo (0x6795A0) */
int InterStageSwitchLock QWORD = 0;
