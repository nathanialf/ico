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

typedef struct {
    char name[0x110];
    int f110;
    int lsn;
} CdvdBgReq;

typedef struct {
    int f0;
    unsigned char _4[0x24];
} StgFile;

typedef struct {
    int stage;
    float dist;
    unsigned char _8[0x8];
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

extern int stage_no;
extern StgFile D_0055C53C[];
extern const StgPre stageData[];
extern int stagePreLoadStageNo;
extern int stagePreLoadReadOffset;
extern int stagePreLoad2ndReadOffset;
extern int D_0063ACC4;
extern int D_0063ACC8;
extern int D_0063ACD0;
extern int stagePreLoadLsn;
extern int stagePreLoadSectorCnt;
extern int stageExitDataCnt;
extern int stgmgrNextStagePreLoad(CdvdBgReq *bg);
/* kept local: the declaration in StageManager.h changes this TU codegen */
extern void stgmgrForceSwitchWithFadeColor(int stage, float fadeIn, float fadeOut, unsigned char r,
                                           unsigned char g, unsigned char b);
extern int D_0063ACCC;

/* .sbss, owned by StageManager.o (VMA 0x63C348..0x63C350, no MAIN.MAP symbol,
   so file statics; names ours): the one-entry buffer of the stage manager's
   message queue, and the stage stgmgrNextStagePreLoadForceStageSet asks the
   preloader for. */
static int stageMgrMsgBuf;

static int stagePreLoadForceStageNo;

/* kept local: main.c's global; this TU does not include main.h */
extern int systemStatus[];

typedef struct {
    int cmd;
    int stage;
    int _8;
    float fC;
    float f10;
    unsigned char r;
    unsigned char g;
    unsigned char b;
} StgMgrMsg;

/* kept local: main.c's global; this TU does not include main.h */
extern StgMgrMsg stageMgrMsg;
extern int graphics_ready;
extern unsigned int mpegPlayInitColor;
/* kept local: main.c's global; this TU does not include main.h */
extern int db[];

/* .bss, owned by StageManager.o (the retail run is 0x70, the size of thread.c's
   own IOSThread record; MAIN.MAP sizes its own link's 0x80 and names no symbol
   in it): the thread descriptor InitIcoMisc is started through. */
/* */
static unsigned int initIcoMiscThread[28];

/* kept local: this TU's view of the ios partition handles (ios.h declares them int) */
extern void *ios_partition_root;
/* kept local: main.c's global; this TU does not include main.h */
extern int current_stage_no;
extern int mpegPlay;
extern int mpegInitDone;
extern int stageManagerFreeResourceFlag;
extern char D_0063ACE0[];
extern int IosCdLock;
extern int IosStgMgrLock;
extern int fadeStatus;
extern float fadeSpeed;
extern int fadeContinue;
extern unsigned char fadeColor[4];
extern float mpegPlayFadeInSpeed;
extern int stgMgrWakeupRequest;
/* kept local: this TU's uses of jimakuEnd do not fit the prototype in jimaku.h */
extern void jimakuEnd();
extern int game_pause;
extern int before_stage_no;
extern void *ios_partition_isys;
extern void *ios_partition_sugipon;
extern void *ios_partition_dmotion;
extern void *ios_partition_seki;
extern void *ios_partition_oomori;
extern void *ios_partition_sound;
/* kept local: main.c's global; this TU does not include main.h */
extern void *boyGObj;
/* kept local: main.c's global; this TU does not include main.h */
extern void *girlGObj;
extern int jimaku_msg[];
extern char D_0063ACB0[];

#include "StageManager.h"
#include <libgraph.h>
#include <libvu0.h>
#include <eekernel.h>
#include <libdma.h>
#include <string.h>
#include "typedef.h"

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
        jimakuEnd(jimaku_msg);
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
    debug_StdPrintfDummy(D_0063ACB0);
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

int stgmgrNextStagePreLoad(CdvdBgReq *bg)
{
    float root[4];
    float d[4];
    int size;
    int stage = 0;
    int i;
    float dist;

    if (D_0063ACC4++ < 15) {
        return 0;
    }
    D_0063ACC4 = 0;
    if (iosCdvdBackGroundMgrEntryNum() >= 3 && D_0063ACCC == 0) {
        return 0;
    }
    switch (D_0063ACC8) {
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
        stagePreLoadLsn = bg->lsn = iosCdvdGetFileLsn(bg, &size);
        size = (size + 0x7FF) / 0x800 * 0x800;
        readSize = size > 0x1C0000 ? 0x1C0000 : size;
        debug_StdPrintfDummy("preload %s move %d total %d reset %d\n", bg, readSize, size,
                             size - readSize);
        bg->f110 = 0;
        ret = iosCdvdBackGroundRead(bg, stagePreLoadBuff, readSize);
        debug_StdPrintfDummy(D_0063ACE0);
        stagePreLoadSectorCnt = readSize >> 11;
        stagePreLoadStageNo = stage;
    }
    return 0;
}

static inline void stgmgrNextStagePreLoadDiskNotReady(void)
{
    stagePreLoadStageNo = 0;
    D_0063ACC4 = 0;
    stagePreLoadLsn = 0;
}

void stgmgrNextStagePreLoadEntry(int stage)
{
    const StgPre *pre = &stageData[stage];
    int i;
    int ret;

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
    D_0063ACD0 = ret;
    iosCdvdBackGroundMgrNotDiskReadyPauseSet(ret, 1);
    stagePreLoadStageNo = 0;
    stagePreLoadSectorCnt = 0;
    stagePreLoadLsn = 0;
    stagePreLoadReadOffset = 0;
    stagePreLoad2ndReadOffset = 0;
    D_0063ACC4 = 0;
    D_0063ACC8 = 0;
}

inline void stgmgrNextStagePreLoadDistBoyMode(void)
{
    D_0063ACC8 = 0;
    D_0063ACCC = 0;
}

inline void stgmgrNextStagePreLoadForceStageSet(int val)
{
    stagePreLoadForceStageNo = val;
    D_0063ACC8 = 1;
    D_0063ACCC = 0;
}

inline void stgmgrNextStagePreLoadForceNoCancel(int val)
{
    D_0063ACCC = val;
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
            fadeSpeed = msg->f10;
            fadeColor[0] = msg->r;
            fadeColor[1] = msg->g;
            fadeColor[2] = msg->b;
            fadeColor[3] = 0;
            fadeContinue = 1;
            fbKeep = 1;
            if (stageData[msg->stage].mpegNo != 0) {
                stgMgrWakeupRequest = 1;
                mpegPlayFadeInSpeed = msg->fC;
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
        if (D_0063ACD0 != 0) {
            iosCdvdBackGroundMgrDelete(D_0063ACD0);
        }
        D_0063ACD0 = 0;
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
        if (msg->fC == 0.0f) {
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
            fadeSpeed = -msg->fC;
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
    stageMgrMsg.fC = 0;
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
    stageMgrMsg.fC = fadeOut;
    stageMgrMsg.f10 = fadeIn;
    stageMgrMsg.r = r;
    stageMgrMsg.g = g;
    stageMgrMsg.b = b;
    mpegPlayInitColor = 0x80000000 | (b << 16) | (g << 8) | r;
    graphics_ready = 1;
    iosMsgSend(stageMgrMsgQ, &stageMgrMsg, 1);
}
