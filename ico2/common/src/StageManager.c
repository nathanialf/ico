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

typedef struct {
    int f0;
    unsigned char pad4[36];
} StgFile;

typedef struct {
    int stage;
    float dist;
    unsigned char pad8[8];
    float pos[4];
} StgSlot;

/* .data, owned by StageManager.o (VMA 0x319A00..0x4D9C10, 0x1C0210 B, all zero;
   MAIN.MAP names all three as globals): the preload buffer, 896 sectors of 2048
   bytes, the cap stgmgrNextStagePreLoad clamps a read to and the ring cdvd.c's
   stream reads through; the stage manager's message queue record; and the exit
   positions of the fifteen entrances stgmgrNextStagePreLoadEntry collects. */
char stagePreLoadBuff[896 * 2048] = {0};

int stageMgrMsgQ[12] = {0};

StgSlot stageExitData[15] = {0};

extern StgFile D_0055C53C[];
extern const StgPre stageData[];
extern int stgmgrNextStagePreLoad(CdvdBgReq *bg);

/* .sbss, owned by StageManager.o (VMA 0x63C348..0x63C350, no MAIN.MAP symbol,
   so file statics; names ours): the one-entry buffer of the stage manager's
   message queue, and the stage stgmgrNextStagePreLoadForceStageSet asks the
   preloader for. */
static int stageMgrMsgBuf;

static int stagePreLoadForceStageNo;

/* .bss, owned by StageManager.o (the retail run is 0x70, the size of thread.c's
   own IOSThread record; MAIN.MAP sizes its own link's 0x80 and names no symbol
   in it): the thread descriptor InitIcoMisc is started through. */
/* */
static unsigned int initIcoMiscThread[28];

#include "StageManager.h"
#include "main.h"
#include <libgraph.h>
#include <libvu0.h>
#include <eekernel.h>
#include <libdma.h>
#include <string.h>
#include "typedef.h"

/* .sdata, owned by StageManager.o (VMA 0x63AC98..0x63ACF0, 0x58 B = MAIN.MAP
   StageManager.o .sdata), in the ROM's order: the movie switches main.c's loop
   reads, defined before stop_free_resources, whose "here\n" follows them; the
   preload state before stgmgrNextStagePreLoad, whose "done" follows it; the fade
   speed and the exit count last. MAIN.MAP names every global here; the four
   file statics carry no symbol. */
int mpegPlay = 0;

int mpegInitDone = 0;

int mpegPlayReturnStage = 3;

unsigned int mpegPlayInitColor = 0x80000000;

int stageManagerFreeResourceFlag = 0;

int stgMgrWakeupRequest = 0;

static void stgmgrNextStagePreLoadDiskNotReady(void);

/*SW*/
void stop_free_resources(void)
{
    int i;

    debug_StdPrintfDummy("----- MASK LINK -----\n");
    game_pause = 0;
    for (i = 0; i < 8; i++) {
        isysGObjActiveLink(i, 0);
    }
    if (stageData[before_stage_no].endproc != 0) {
        stageData[before_stage_no].endproc();
    }
    iosThreadCancelWakeup(0);
    isysGObjRemoveAll();
    sceGsSyncPath(0, 0);
    InitDelayFree();
    if (systemStatus[10] != 0) {
        jimakuEnd(&jimaku_msg);
        systemStatus[10] = 0;
    }
    if (sndInitBgmCancelFlag == 0) {
        debug_StdPrintfDummy("sound partition reset\n");
        iosMallocResetPartition(ios_partition_sound);
    } else {
        debug_StdPrintfDummy("sound partition not reset\n");
    }
    iosMallocResetPartition(ios_partition_seki);
    iosMallocResetPartition(ios_partition_sugipon);
    iosMallocResetPartition(ios_partition_dmotion);
    iosMallocResetPartition(ios_partition_oomori);
    iosMallocResetPartition(ios_partition_isys);
    ResetDynamicMotionManager();
    debug_StdPrintfDummy("here\n");
    InitDelayFree();
    girlGObj = 0;
    boyGObj = 0;
}

/*SW-END*/
/*SW*/
void stage_initialize(void)
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

void exit_stage(int *self)
{
    gamesysStageExitTimeSet(stage_no);
    warpGirlOutStage(stage_no, 0);
    warpGirlInStage(self);
    backStageProcessOutStage();
    sndBgmReadyNextStage(self, stage_no);
    return DeleteStreamMotionManager();
}

/* The mpeg-restart record the stream side owns; the two fields this arm
   clears are at +0x14 and +0x18 of it. */
typedef struct MpegRec {
    int _0[5];
    int f14;
    int f18;
} MpegRec;

void start_stage_Load_thread(int stage)
{
    before_stage_no = stage_no;
    stage_no = stage;
    gsb_SetBGColor(db, 1, 1, 1);
    sceGsSyncPath(0, 0);
    stageManagerFreeResourceFlag = 1;
    stop_free_resources();
    if (mpegPlay == 0) {
        long flags;

        stage_initialize();
        stageManagerFreeResourceFlag = 0;
        iosThreadCancelWakeup(0);
        gsb_SetMotionBlur();
        current_stage_no = stage;
        iosThreadCreateS(initIcoMiscThread, 1, InitIcoMisc, (int)&stage_no, ios_partition_root,
                         0x18000, 27);
        iosThreadStart(initIcoMiscThread);
        flags = initIcoMiscThread[15];
        debug_StdPrintfDummy("auto stack %d\n", (int)flags & 1);
        game_pause = 1;
        debug_StdPrintfDummy("-----------------Enable VSync\n");
    } else {
        isysInitialize();
        sceGsResetPath();
        sceVpu0Reset();
        sceDmaReset(1);
        mpegInitDone = 1;
        ((MpegRec *)systemStatus)->f14 = 0;
        ((MpegRec *)systemStatus)->f18 = 0;
        girlGObj = 0;
        boyGObj = 0;
        stageManagerFreeResourceFlag = 0;
    }
}

/* The DEBUG build's preload report and hold (names and texts ours): a debug
   build reports the stage it is about to preload and, while the debug flag
   word's hold bit is set, repeats the report instead of reading. Both build
   only under DEBUG; the retail report inlines to one (use (const_int 0)) and
   the retail hold test to 0, which cse folds, so the loop runs once. WHAT THE
   BYTES PIN: the ROM puts the -1 in GetDataFileName's delay slot, after both
   argument moves (listing row 656, 0x1ab29c-0x1ab2a8). sched2 gives that order
   only when the first argument move carries a loop-note barrier
   (haifa-sched.c 3677-3724): it holds the second move and the -1 back one
   cycle, so both issue before the call. The notes have to sit mid-block
   behind a zero-code insn, which this loop with the report as its body
   gives, and the -1 has to be set after the move. Rows 654 and 655 carry no
   code. WHAT THEY CANNOT PIN: what the debug build printed or tested, or
   where `ret = -1` sat between the GetDataFileName call and row 659. */
static __inline__ void stgPreLoadDebugHook(void)
{
#ifdef DEBUG
    scePrintf("preload: leaving stage %d's data\n", stagePreLoadStageNo);
#endif
}

static __inline__ int stgPreLoadDebugHold(void)
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

static int stagePreLoadMgrEntry = 0; /* derived name */

int stagePreLoadLsn = 0;

int stagePreLoadSectorCnt = 0;

int stgmgrNextStagePreLoad(CdvdBgReq *bg)
{
    float root[4];
    float d[4];
    int size;
    int stage = 0;
    int i;
    float dist;

    if (stagePreLoadWait++ < 15) {
        return 0;
    }
    stagePreLoadWait = 0;
    if (iosCdvdBackGroundMgrEntryNum() >= 3 && stagePreLoadNoCancel == 0) {
        return 0;
    }
    switch (stagePreLoadMode) {
    case 0: {
        int best = -1;

        if (boyGObj == 0) {
            return 0;
        }
        GetRootPosition(root, boyGObj);
        for (i = 0; i < stageExitDataCnt; i++) {
            StgSlot *e;

            _SubVector(d, root, stageExitData[i].pos);
            dist = _InnerProduct(d, d);
            e = &stageExitData[i];
            e->dist = dist;
            if (best == -1) {
                best = i;
                stage = e->stage;
            } else if (dist < (&stageExitData[best])->dist) {
                best = i;
                stage = e->stage;
            }
        }
        break;
    }
    case 1:
        stage = stagePreLoadForceStageNo;
        break;
    }
    if (stage != 0 && stage != stagePreLoadStageNo && stageData[stage].mpegNo == 0) {
        int readSize;
        int ret;

        /* The DEBUG build's report and hold, see stgPreLoadDebugHook. */
        do {
            stgPreLoadDebugHook();
        } while (stgPreLoadDebugHold());
        strcpy(bg->name, GetDataFileName(stage, 1));
        ret = -1;
        iosCdvdChgFileName(bg);
        stagePreLoadLsn = bg->lsn = iosCdvdGetFileLsn(bg->name, &size);
        size = (size + 0x7FF) / 0x800 * 0x800;
        readSize = size > 0x1C0000 ? 0x1C0000 : size;
        debug_StdPrintfDummy("preload %s move %d total %d reset %d\n", bg, readSize, size,
                             size - readSize);
        bg->pos = 0;
        ret = iosCdvdBackGroundRead(bg, stagePreLoadBuff, readSize);
        debug_StdPrintfDummy("done");
        stagePreLoadSectorCnt = readSize >> 11;
        stagePreLoadStageNo = stage;
    }
    return 0;
}

static inline void stgmgrNextStagePreLoadDiskNotReady(void)
{
    stagePreLoadStageNo = 0;
    stagePreLoadWait = 0;
    stagePreLoadLsn = 0;
}

float mpegPlayFadeInSpeed = 0.0f;

int stageExitDataCnt = 0;

void stgmgrNextStagePreLoadEntry(int stage)
{
    const StgPre *pre = &stageData[stage];
    int i;
    CdvdBgReq *ret;

    stageExitDataCnt = 0;
    for (i = 0; i < 15; i++) {
        short s = pre->ent[i];
        if (s != 0) {
            int count = stageExitDataCnt;
            stageExitData[count].stage = D_0055C53C[s].f0;
            if (PositionOfExit(stageExitData[count].pos, i + 1) == 0) {
                stageExitDataCnt = stageExitDataCnt + 1;
            }
        }
    }
    ret = iosCdvdBackGroundMgrAdd("DFDATAS/COMMON.DF", stgmgrNextStagePreLoad, 0,
                                  stgmgrNextStagePreLoadDiskNotReady, 0, 0, 0, 0);
    stagePreLoadMgrEntry = ret;
    iosCdvdBackGroundMgrNotDiskReadyPauseSet(ret, 1);
    stagePreLoadStageNo = 0;
    stagePreLoadSectorCnt = 0;
    stagePreLoadLsn = 0;
    stagePreLoadReadOffset = 0;
    stagePreLoad2ndReadOffset = 0;
    stagePreLoadWait = 0;
    stagePreLoadMode = 0;
}

inline void stgmgrNextStagePreLoadDistBoyMode(void)
{
    stagePreLoadMode = 0;
    stagePreLoadNoCancel = 0;
}

inline void stgmgrNextStagePreLoadForceStageSet(int val)
{
    stagePreLoadForceStageNo = val;
    stagePreLoadMode = 1;
    stagePreLoadNoCancel = 0;
}

inline void stgmgrNextStagePreLoadForceNoCancel(int val)
{
    stagePreLoadNoCancel = val;
}

void StageManager(void)
{
    StgMgrMsg *msg;

    debug_StdPrintfDummy("stage manager() in\n");
    iosMsgQueueCreate(stageMgrMsgQ, &stageMgrMsgBuf, 1);
    debug_StdPrintfDummy("IosCdLock %d\n", IosCdLock);
    WaitSema(IosCdLock);
    DeleteSema(IosCdLock);
    SignalSema(IosStgMgrLock);
    debug_StdPrintfDummy("STAGE MANAGER START\n");
    while (1) {
        iosMsgRecv(stageMgrMsgQ, &msg, 1);
        mpegPlayFadeInSpeed = 128.0f;
        fadeSpeed = 0;
        switch (msg->cmd) {
        case 0:
            break;
        case 1:
            fadeStatus = 1;
            fadeSpeed = msg->fadeIn;
            fadeColor[0] = msg->r;
            fadeColor[1] = msg->g;
            fadeColor[2] = msg->b;
            fadeColor[3] = 0;
            fadeContinue = 1;
            fbKeep = 1;
            if (stageData[msg->stage].mpegNo != 0) {
                stgMgrWakeupRequest = 1;
                mpegPlayFadeInSpeed = msg->fadeOut;
                do {
                    iosThreadSleep();
                } while (fadeStatus != 3);
            }
            break;
        default:
            goto badCmd;
        }
        if (stageData[msg->stage].mpegNo != 0) {
            mpegInitDone = 0;
            fightSoundClose();
            soundDataSegAllClose(0, 2);
        }
        if (stagePreLoadMgrEntry != 0) {
            iosCdvdBackGroundMgrDelete(stagePreLoadMgrEntry);
        }
        stagePreLoadMgrEntry = 0;
        if (msg->stage <= 0xFFFF) {
            exit_stage((int *)msg->stage);
            lt_switch_layout(0x35);
            systemStatus[6] = 1;
            systemStatus[5] = 1;
            stgMgrWakeupRequest = 1;
            while (iosCdvdBackGroundMgrDeleteRequestGet() != 0) {
                iosThreadSleep();
            }
            stgMgrWakeupRequest = 0;
            mpegPlay = stageData[msg->stage].mpegNo;
            start_stage_Load_thread(msg->stage);
        } else {
            debug_StdPrintfDummy("out of stage %d\n", msg->stage);
        }
        if (msg->fadeOut == 0.0f) {
            fadeStatus = 0;
            stgMgrWakeupRequest = 1;
            while (systemStatus[6] != 0) {
                iosThreadSleep();
            }
            if (mpegPlay == 0) {
                stgmgrNextStagePreLoadEntry(msg->stage);
            }
            fbKeep = 0;
            stgMgrWakeupRequest = 0;
        } else {
            stgMgrWakeupRequest = 1;
            while (systemStatus[6] != 0) {
                iosThreadSleep();
            }
            if (mpegPlay == 0) {
                stgmgrNextStagePreLoadEntry(msg->stage);
            }
            fadeContinue = 0;
            fadeStatus = 1;
            fbKeep = 0;
            stgMgrWakeupRequest = 0;
            fadeSpeed = -msg->fadeOut;
        }
        continue;
    badCmd:
        debug_StdPrintfDummy("StageManager:unknown msg\n");
    }
    /* Unreachable after the loop (the listing has no row between the loop's
       909 and the closing 911), but its string is the TU's last .rodata entry
       at 0x6191B8. */
    debug_StdPrintfDummy("stage manager() out\n");
}

inline void CheckPoint(void)
{
    if (systemStatus[2]) {
        gamesysMemorySave(gameSysMemoryFuncList, gameSysMainSaveBuff, 0);
        systemStatus[3] = 1;
    }
}

void stgmgrForceSwitch(int stage)
{
    stageMgrMsg.cmd = 0;
    stageMgrMsg.stage = stage;
    graphics_ready = 1;
    stageMgrMsg.fadeOut = 0;
    iosMsgSend(stageMgrMsgQ, &stageMgrMsg, 1);
}

void stgmgrForceSwitchWithFade(int stage, float fadeIn, float fadeOut)
{
    stgmgrForceSwitchWithFadeColor(stage, fadeIn, fadeOut, 0, 0, 0);
}

void stgmgrForceSwitchWithFadeColor(int stage, float fadeIn, float fadeOut, unsigned char r,
                                    unsigned char g, unsigned char b)
{
    stageMgrMsg.cmd = 1;
    stageMgrMsg.stage = stage;
    stageMgrMsg.fadeOut = fadeOut;
    stageMgrMsg.fadeIn = fadeIn;
    stageMgrMsg.r = r;
    stageMgrMsg.g = g;
    stageMgrMsg.b = b;
    mpegPlayInitColor = 0x80000000 | (b << 16) | (g << 8) | r;
    graphics_ready = 1;
    iosMsgSend(stageMgrMsgQ, &stageMgrMsg, 1);
}
