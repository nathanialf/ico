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
#include "include_asm.h"

/* main.c's .data globals, each with an initialiser. systemStatus starts in NTSC mode (word 0)
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

INCLUDE_ASM(Main);

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

INCLUDE_ASM(scheduler);

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

/* the boot thread's kernel id */
static int bootThreadId; /* derived name */

int main(void)
{
    debug_StdPrintfDummy("main\n");
    debug_StdPrintfDummy("main\n");
    ChangeThreadPriority(GetThreadId(), 14);
    bootThreadId = GetThreadId();
    boot();
    return 0;
}

/* vsyncs counted toward systemStatus[1], the frame step */
static int frameStepCount = 0; /* derived name */

/* main.c's .sdata globals.  Each is a 4-byte scalar; the ones marked
   QWORD open a 16-byte quadword of their own, the rest of which stays
   empty. */
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

/* The six quadwords in the Aug-6 map's order (NonLinearCameraMove,
   GlobalTimer, lock_execIcoMisc, graphics_ready, game_pause, data_loading):
   UpdatePointBlur reads the first at gp-28416, way_sys.c stamps its frames
   with the second, stgmgrForceSwitch stores 1 to the third at gp-28384, and
   GsBase.c and fieldCollision.c test the fourth. */
int NonLinearCameraMove QWORD = 0;

int GlobalTimer QWORD = 0;

int lock_execIcoMisc QWORD = 0;

int graphics_ready QWORD = 0;

int game_pause QWORD = 0;

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

GObj *boyGObj = 0;

GObj *girlGObj = 0;

/* the boy's pad handle, the Act.pad his actor connects; this build has no
   girlPad: _ACTCorrectMsg 0x15375C reads gameover_flag at the word after
   boyPad, ACT_LAYOUT_GAMEOVER 0x15B4C8 gameover_layout_flag after it */
IosPadCtx *boyPad = 0;

int gameover_flag = 0;

int gameover_layout_flag = 0;

/* ACTItemWatchMotion runs for the boy only while it is 0 */
int itemWatchOff = 0; /* derived name */

GObj *CurrentTargetGObj QWORD = 0;

GObj *CurrentTargetGObjSub QWORD = 0;

int current_stage_no = 0;

void (*system_stage_func)(void) = 0;

int InterStageSwitchLock = 0;
