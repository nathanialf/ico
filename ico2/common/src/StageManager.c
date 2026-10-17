#include "StageManager.h"
#include "backStage.h"
#include "debug.h"
#include "debug_menu.h"
#include "gamesys.h"
#include "icoMisc.h"
#include "layout_texture.h"
#include "cdvd.h"
#include "memory.h"
#include "message.h"
#include "thread.h"
#include "gobj.h"
#include "isys.h"
#include "s_init.h"
#include "soundManager.h"
#include "fieldCollision.h"
#include "access.h"
#include "fightSound.h"
#include "warpGirl.h"
#include "DisplayP2O.h"
#include "GsBase.h"
#include "Matrix.h"
#include "darkVolume.h"
#include "delayFreeManager.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "motionFileManager.h"
#include "streamMotionManager.h"
#include "tableSin.h"
#include "Basic.h"
#include "ios.h"
#include "jimaku.h"

typedef struct { /* field names derived */
    int stage;
    float dist;
    unsigned char pad8[8];
    float pos[4];
} StgSlot; /* derived name */

/* .data, all zero: the preload buffer, 1024 sectors of 2048
   bytes in this build, the cap stgmgrNextStagePreLoad clamps a read to and the ring cdvd.c's
   stream reads through; the stage manager's message queue record; and the exit
   positions of the fifteen entrances stgmgrNextStagePreLoadEntry collects. */
char stagePreLoadBuff[1024 * 2048] = {0};

IosMsgQueue stageMgrMsgQ = {0};

StgSlot stageExitData[15] = {0};

/* .sbss: the stage stgmgrNextStagePreLoadForceStageSet asks the preloader
   for (this build has no message-queue buffer word before it). */
static int stagePreLoadForceStageNo; /* derived name */

/* .bss: the thread descriptor InitIcoMisc is started through, an IOSThread's
   28 words; InitIcoMisc's flag word at 0x3C is read here as an unsigned word,
   where IOSThread's flags is the int ios/thread.c tests */
static unsigned int initIcoMiscThread[28]; /* derived name */

#include "main.h"
#include <libgraph.h>
#include <libvu0.h>
#include <eekernel.h>
#include <libdma.h>
#include <string.h>
#include "typedef.h"
#include "include_asm.h"

/* .sdata: the movie switches main.c's loop reads, defined before
   stop_free_resources; the preload state before stgmgrNextStagePreLoad; the
   fade speed and the exit count last. */
int mpegPlay = 0;

int mpegInitDone = 0;

int mpegPlayReturnStage = 3;

unsigned int mpegPlayInitColor = 0x80000000;

int stageManagerFreeResourceFlag = 0;

int stgMgrWakeupRequest = 0;

static void stgmgrNextStagePreLoadDiskNotReady(void);

/*SW*/
INCLUDE_ASM(stop_free_resources);

/*SW-END*/
/*SW*/
static void stage_initialize(void)
{
    isysInitialize();
    debug_StdPrintfDummy("InitTableSin\n");
    InitTableSin();
    debug_StdPrintfDummy("InitMatrixDrive\n");
    InitMatrixDrive();
    InitGameOverEffect();
    debug_StdPrintfDummy("debug_Init\n");
    gsb_InitGSSystem();
    debug_StdPrintfDummy("p2o transMicroProgram\n");
    p2o_TransMicroProgram();
    debug_StdPrintfDummy("InitGSSystem\n");
    debug_Init();
    debug_StdPrintfDummy("init debug menu\n");
    init_debug_menu();
    debug_StdPrintfDummy("enable vsync\n");
    EnableIntc(2);
}

/*SW-END*/

static void exit_stage(int stage)
{
    gamesysStageExitTimeSet(stage_no);
    warpGirlOutStage(stage_no, 0);
    warpGirlInStage(stage);
    backStageProcessOutStage();
    sndBgmReadyNextStage(stage, stage_no);
    return DeleteStreamMotionManager();
}

/* systemStatus seen as a record by the mpeg arm, which clears its pause flag
   (systemStatus[5], the game paused while it is set) and its stage-change flag
   (systemStatus[6], set by the stage exit, waited on until the stage is up). */
typedef struct MpegRec { /* field names derived */
    int pad0[5];
    int pause;
    int stageChange;
} MpegRec; /* derived name */

INCLUDE_ASM(start_stage_Load_thread);

/* The DEBUG build's preload report and hold (the report's text derived): a
   debug build reports the stage it is about to preload and, while the debug
   flag word's hold bit is set, repeats the report instead of reading.  Both
   build only under DEBUG; in the retail build the report is empty and the
   hold test is 0, so the loop runs once. */
static __inline__ void stgPreLoadDebugHook(void) /* derived name */
{
#ifdef DEBUG
    scePrintf("preload: leaving stage %d's data\n", stagePreLoadStageNo);
#endif
}

static __inline__ int stgPreLoadDebugHold(void) /* derived name */
{
#ifdef DEBUG
    return debug_font_flag & 0x100;
#else
    return 0;
#endif
}

int stagePreLoadStageNo = 0;

int stagePreLoadReadOffset = 0;

int stagePreLoad2ndReadOffset = 0;

static int stagePreLoadWait = 0; /* derived name */

static int stagePreLoadMode = 0; /* derived name */

static int stagePreLoadNoCancel = 0; /* derived name */

static CdvdBgReq *stagePreLoadMgrEntry = 0; /* derived name */

int stagePreLoadLsn = 0;

int stagePreLoadSectorCnt = 0;

INCLUDE_ASM(stgmgrNextStagePreLoad);

float mpegPlayFadeInSpeed = 0.0f;

int stageExitDataCnt = 0;

INCLUDE_ASM(stgmgrNextStagePreLoadEntry);

INCLUDE_ASM(StageManager);

INCLUDE_ASM(stgmgrForceSwitch);

void stgmgrForceSwitchWithFade(int stage, float fadeIn, float fadeOut)
{
    stgmgrForceSwitchWithFadeColor(stage, fadeIn, fadeOut, 0, 0, 0);
}

INCLUDE_ASM(stgmgrForceSwitchWithFadeColor);

INCLUDE_ASM(stgmgrNextStagePreLoadForceStageSet);

INCLUDE_ASM(stgmgrNextStagePreLoadDistBoyMode);

INCLUDE_ASM(stgmgrNextStagePreLoadForceNoCancel);

INCLUDE_ASM(CheckPoint);

INCLUDE_ASM(stgmgrNextStagePreLoadDiskNotReady);
