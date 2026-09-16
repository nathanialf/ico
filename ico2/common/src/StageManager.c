#include "common.h"
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

/* header prototypes (order fixes the inline tail) */
typedef struct {
    char name[0x110];
    int f110;
    int lsn;
} CdvdBgReq;

typedef struct {
    unsigned char _0[0xA0];
    short ent[0x18];
    unsigned char _d0[0x80];
    void (*endproc)(void);
    unsigned char _154[0x38];
    unsigned int attr;
    unsigned char _190[0x4];
} StgPre;

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

extern int stage_no;
extern StgSlot stageExitData[];
extern StgFile D_0055C53C[];
extern StgPre D_005F5D50[];
extern char D_00619128[];
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
extern int D_0063C34C;
extern int D_0028F4C0[];
extern int D_004DA788[];
extern int D_004DD700[];

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

extern StgMgrMsg D_0028FE70;
extern int stageMgrMsgQ[];
extern int graphics_ready;
extern unsigned int mpegPlayInitColor;
extern void sceGsResetPath(void);
extern void sceVpu0Reset(void);
extern int sceDmaReset(int a0);
extern int D_0028F4F0[];
extern unsigned int D_006FAC80[];
extern void *D_0063A428;
extern int D_00639ED4;
extern int mpegPlay;
extern int mpegInitDone;
extern int stageManagerFreeResourceFlag;
extern char D_006190D0[];
extern char D_006190E0[];
extern char *strcpy(char *dst, const char *src);
extern char stagePreLoadBuff[];
extern char D_00619100[];
extern char D_0063ACE0[];
extern void WaitSema(int s);
extern void DeleteSema(int s);
extern void SignalSema(int s);
extern int IosSndLock;
extern int systemFault;
extern int D_0063C348;
extern int fadeStatus;
extern float fadeSpeed;
extern int fadeContinue;
extern unsigned char fadeColor;
extern unsigned char D_0063BCB1;
extern unsigned char D_0063BCB2;
extern unsigned char D_0063BCB3;
extern float mpegPlayFadeInSpeed;
extern int D_0063A054;
extern int stgMgrWakeupRequest;
extern int D_0063ACD0;
extern char D_00619140[];
extern char D_00619158[];
extern char D_00619168[];
extern char D_00619180[];
extern char D_00619198[];
extern void sceGsSyncPath(int a, int b);
/* kept local: this TU's uses of jimakuEnd do not fit the prototype in jimaku.h */
extern void jimakuEnd();
extern int game_pause;
extern int before_stage_no;
extern int D_0063A684;
extern void *D_0063A430;
extern void *D_0063A438;
extern void *D_0063A440;
extern void *D_0063A44C;
extern void *D_0063A450;
extern void *D_0063A458;
extern void *D_00639EA4;
extern void *D_00639EA8;
extern int D_0028F4C0[];
extern int jimaku_msg[];
extern char D_00618FF8[];
extern char D_00619010[];
extern char D_00619028[];
extern char D_0063ACB0[];
extern void EnableIntc(int ch);
extern char D_00619048[];
extern char D_00619058[];
extern char D_00619070[];
extern char D_00619080[];
extern char D_00619098[];
extern char D_006190A8[];
extern char D_006190C0[];
/* prototypes: their order is the inline tail's emission order */
void stgmgrNextStagePreLoadForceStageSet(int val);
void stgmgrNextStagePreLoadDistBoyMode(void);
void stgmgrNextStagePreLoadForceNoCancel(int val);
void CheckPoint(void);
static void stgmgrNextStagePreLoadDiskNotReady(void);

/*SW*/
void stop_free_resources(void)
{
    int i;

    debug_StdPrintfDummy(D_00618FF8);
    game_pause = 0;
    for (i = 0; i < 8; i++) {
        isysGObjActiveLink(i, 0);
    }
    if (D_005F5D50[before_stage_no].endproc != 0) {
        D_005F5D50[before_stage_no].endproc();
    }
    iosThreadCancelWakeup(0);
    isysGObjRemoveAll();
    sceGsSyncPath(0, 0);
    InitDelayFree();
    if (D_0028F4C0[10] != 0) {
        jimakuEnd(jimaku_msg);
        D_0028F4C0[10] = 0;
    }
    if (D_0063A684 == 0) {
        debug_StdPrintfDummy(D_00619010);
        iosMallocResetPartition(D_0063A458);
    } else {
        debug_StdPrintfDummy(D_00619028);
    }
    iosMallocResetPartition(D_0063A44C);
    iosMallocResetPartition(D_0063A438);
    iosMallocResetPartition(D_0063A440);
    iosMallocResetPartition(D_0063A450);
    iosMallocResetPartition(D_0063A430);
    ResetDynamicMotionManager();
    debug_StdPrintfDummy(D_0063ACB0);
    InitDelayFree();
    D_00639EA8 = 0;
    D_00639EA4 = 0;
}

/*SW-END*/
/*SW*/
void stage_initialize(void)
{
    isysInitialize();
    debug_StdPrintfDummy(D_00619048);
    InitTableSin();
    debug_StdPrintfDummy(D_00619058);
    InitMatrixDrive();
    InitGameOverEffect();
    debug_StdPrintfDummy(D_00619070);
    gsb_InitGSSystem();
    debug_StdPrintfDummy(D_00619080);
    p2o_TransMicroProgram();
    debug_StdPrintfDummy(D_00619098);
    debug_Init();
    debug_StdPrintfDummy(D_006190A8);
    init_debug_menu();
    debug_StdPrintfDummy(D_006190C0);
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
    gsb_SetBGColor(D_0028F4F0, 1, 1, 1);
    sceGsSyncPath(0, 0);
    stageManagerFreeResourceFlag = 1;
    stop_free_resources();
    if (mpegPlay == 0) {
        long flags;

        stage_initialize();
        stageManagerFreeResourceFlag = 0;
        iosThreadCancelWakeup(0);
        gsb_SetMotionBlur();
        D_00639ED4 = stage;
        iosThreadCreateS(D_006FAC80, 1, InitIcoMisc, (int)&stage_no, D_0063A428, 0x18000, 27);
        iosThreadStart(D_006FAC80);
        flags = D_006FAC80[15];
        debug_StdPrintfDummy(D_006190D0, (int)flags & 1);
        game_pause = 1;
        debug_StdPrintfDummy(D_006190E0);
    } else {
        isysInitialize();
        sceGsResetPath();
        sceVpu0Reset();
        sceDmaReset(1);
        mpegInitDone = 1;
        ((MpegRec *)D_0028F4C0)->f14 = 0;
        ((MpegRec *)D_0028F4C0)->f18 = 0;
        D_00639EA8 = 0;
        D_00639EA4 = 0;
        stageManagerFreeResourceFlag = 0;
    }
}

/*SW*/
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/StageManager", stgmgrNextStagePreLoad);

/*SW-END*/

static inline void stgmgrNextStagePreLoadDiskNotReady(void)
{
    stagePreLoadStageNo = 0;
    D_0063ACC4 = 0;
    stagePreLoadLsn = 0;
}

void stgmgrNextStagePreLoadEntry(int stage)
{
    StgPre *pre = &D_005F5D50[stage];
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
    ret = iosCdvdBackGroundMgrAdd(D_00619128, stgmgrNextStagePreLoad, 0,
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
    D_0063C34C = val;
    D_0063ACC8 = 1;
    D_0063ACCC = 0;
}

inline void stgmgrNextStagePreLoadForceNoCancel(int val)
{
    D_0063ACCC = val;
}

/*SW*/
INCLUDE_ASM("asm/nonmatchings/ico2/common/src/StageManager", StageManager);

/*SW-END*/

inline void CheckPoint(void)
{
    if (D_0028F4C0[2]) {
        gamesysMemorySave(D_004DA788, D_004DD700, 0);
        D_0028F4C0[3] = 1;
    }
}

void stgmgrForceSwitch(int stage)
{
    D_0028FE70.cmd = 0;
    D_0028FE70.stage = stage;
    graphics_ready = 1;
    D_0028FE70.fC = 0;
    iosMsgSend(stageMgrMsgQ, &D_0028FE70, 1);
}

void stgmgrForceSwitchWithFade(int stage, float fadeIn, float fadeOut)
{
    stgmgrForceSwitchWithFadeColor(stage, fadeIn, fadeOut, 0, 0, 0);
}

void stgmgrForceSwitchWithFadeColor(int stage, float fadeIn, float fadeOut, unsigned char r,
                                    unsigned char g, unsigned char b)
{
    D_0028FE70.cmd = 1;
    D_0028FE70.stage = stage;
    D_0028FE70.fC = fadeOut;
    D_0028FE70.f10 = fadeIn;
    D_0028FE70.r = r;
    D_0028FE70.g = g;
    D_0028FE70.b = b;
    mpegPlayInitColor = 0x80000000 | (b << 16) | (g << 8) | r;
    graphics_ready = 1;
    iosMsgSend(stageMgrMsgQ, &D_0028FE70, 1);
}
