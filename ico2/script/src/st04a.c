#include "st04a.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "act.h"
#include "gobj_process.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "fightSound.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "geometryManager.h"
#include "girl.h"
#include "matrixDrive.h"
#include "staticBlur.h"
#include "streamMotionManager.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "Matrix.h"
#include "script.h"
#include "jimaku.h"
#include "main.h"
#include "include_asm.h"

static void actConte09_3_demoCancel(GObj *volatile self);
static void actSt04aGateLSub(GObj *volatile self);
static void actSt04aGateRSub(GObj *volatile self);
static void actSt04aModelOffChk(GObj *volatile self);
static void actSt04aModelOnChk(GObj *volatile self);
static void finishCallBackFunc(struct GObj *obj);

/* this file's own view of Act (the shared one is in typedef.h) */
typedef struct ActSt04A { /* field names derived */
    char pad0[32];        /* 0x00 */
    ActStatus flags20;    /* 0x20 */
    char pad28[12];       /* 0x28 */
    int actMode;          /* 0x34, the current action mode */
    char pad38[152];      /* 0x38 */
    ActMail *mainMail;    /* 0xD0 */
    ActMail *mail;        /* 0xD4 */
    char padD8[920];      /* 0xD8 */
    int torchAnim;        /* 0x470, the stage animation the lit torch plays */
    GObj *torchObj;       /* 0x474, the torch the ball must reach */
    int torchFlag;        /* 0x478, the game flag raised once it is lit */
} ActSt04A;               /* derived name */

/* this file's own view of GObj (the shared one is in typedef.h) */
typedef struct PObjGObjSt04A { /* field names derived */
    char pad00[348];           /* 0x000 */
    Sub15C *dobj;              /* 0x15C */
    char pad160[4];            /* 0x160 */
    ActSt04A *act;             /* 0x164 */
    char pad168[4];            /* 0x168 */
    int active;                /* 0x16C */
} PObjGObjSt04A;               /* derived name */

/* .data, ahead of model_on and model_off: each action's mail pair, the check
   handler stored into its first entry at run time, and the matrix
   finishCallBackFunc writes into every joint. */
static ActMail gate_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open_mail[2] = {{430}, {429}}; /* derived name */

static Mtx44 jointMtxInit = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                              1.0f, 0.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static ActMail gate_open2_ready_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open2_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open3_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_l_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_r_mail[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_mail[2] = {{430}, {429}}; /* derived name */

static ActMail girl_sit_mail[2] = {{430}, {429}}; /* derived name */

static ActMail torch_hint_mail[2] = {{430}, {429}}; /* derived name */

static ActMail model_mail[2] = {{430}, {429}}; /* derived name */

INCLUDE_ASM(actSt04aGate);

typedef struct AnimList28 { /* field names derived */
    int v[28];
} AnimList28; /* derived name */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* .sdata: the first gate's stream handle and gate1, which no code uses.
   actSt04aConte06's "!!\n" trace follows them. */
SqEntry *gate1st = 0;

int gate1 = 0;

/* .sbss: the demo's own end flag, raised by the subthread the wait loops below
   spin for, and a running flag set for the length of the conte09_3 cutscene
   that nothing reads back. */
static int demoEnd;

static int conte09_3Running; /* derived name */

INCLUDE_ASM(actSt04aGateChk);

INCLUDE_ASM(actSt04aConte06);

/* .sdata, after actSt04aConte06's trace: the gate and torch stream handles,
   then the pad shakes and their volumes (declared in st04a.h for
   actSt04aConte06). */
static SqEntry *gate_open = 0; /* derived name */

static SqEntry *gate_open2 = 0; /* derived name */

static SqEntry *conte09_2 = 0; /* derived name */

SqEntry *gate_ready_l = 0;

SqEntry *gate_ready_r = 0;

SqEntry *torch = 0;

int gate_yure_low = 0;

unsigned char gate_yure_low_vol = 0;

int yure1 = 0;

unsigned char vol1 = 0;

int yure2 = 0;

unsigned char vol2 = 0;

void actSt04aConte06Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 250:
            jimaku_msg.sub.block = 25;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1380:
            jimaku_msg.sub.block = 26;
            jimaku_msg.sub.jump = 60;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2380:
            jimaku_msg.sub.block = 31;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2861:
            jimaku_msg.sub.block = 34;
            jimaku_msg.sub.jump = 150;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3160:
            jimaku_msg.sub.block = 35;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3460:
            jimaku_msg.sub.block = 36;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3760:
            jimaku_msg.sub.block = 37;
            jimaku_msg.sub.jump = 174;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4180:
            jimaku_msg.sub.block = 38;
            jimaku_msg.sub.jump = 174;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4800:
            jimaku_msg.sub.block = 43;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 5580:
            jimaku_msg.sub.block = 27;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6050:
            jimaku_msg.sub.block = 29;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6740:
            jimaku_msg.sub.block = 48;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6980:
            jimaku_msg.sub.block = 49;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 7300.0f);
    _ACTWait(0);
}

INCLUDE_ASM(actSt04aGateOpen);

typedef struct AnimList { /* field names derived */
    int v[13];
} AnimList; /* derived name */

/* .rodata, used here and by actConte09_2: the first lift offset, declared
   ahead and defined with the second after actSt04aGateOpenChk. */
static const ConstVec liftOfs1;

INCLUDE_ASM(actSt04aGateOpenChk);

static const ConstVec liftOfs1 = {{0.0f, 0.0f, 6000.0f, 1.0f}}; /* derived name */

static const ConstVec liftOfs2 = {{-5000.0f, 0.0f, 5300.0f, 1.0f}}; /* derived name */

INCLUDE_ASM(actConte09);

void actConte09Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 2161:
            jimaku_msg.sub.block = 88;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2430:
            jimaku_msg.sub.block = 86;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 2700.0f);
    _ACTWait(0);
}

void actSt04aGateOpen2Chk(GObj *volatile self);

INCLUDE_ASM(actSt04aGateOpen2Chk);

INCLUDE_ASM(actConte09_2);

INCLUDE_ASM(actSt04aGateOpen3);

INCLUDE_ASM(actSt04aGateOpen3Chk);

INCLUDE_ASM(actConte09_3);

INCLUDE_ASM(actSt04aGateLChk);

INCLUDE_ASM(actSt04aGateRChk);

INCLUDE_ASM(actSt04aTorch1);

INCLUDE_ASM(actSt04aTorch1Chk);

INCLUDE_ASM(actSt04aTorchAllFlagfChk);

static void actSt04aTorchHintChk(GObj *volatile self)
{
    while (gflagChk(155) == 0) {
        _ACTWait(1);
    }

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(563), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(564), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(565), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(566), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(567), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(568), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(569), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(570), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(591), 1.0f, 0.001f, 1.0f);

    if (gflagChk(156) == 0) {
        _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 20);
    }

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(563), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(564), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(565), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(566), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(567), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(568), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(569), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(570), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(591), 2.0f, 0.01f, 1.0f);

    gflagOn(156);
}

INCLUDE_ASM(actSt04aGateL);

INCLUDE_ASM(actSt04aGateR);

INCLUDE_ASM(actSt04aTorchXL);

INCLUDE_ASM(actSt04aDeadCam);

void actSt04aGateOpen2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(141) == 0) {
        scpSearchGobj(669)->active = 0;

        gate_open2_mail[0].func = actSt04aGateOpen2Chk;
        act->mail = gate_open2_mail;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04aGateOpen2Ready(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    gate_open2_ready_mail[0].func = actSt04aGateOpen2ReadyChk;
    act->mail = gate_open2_ready_mail;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04aGirlSit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    girl_sit_mail[0].func = actSt04aGirlSitChk;
    act->mail = girl_sit_mail;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04aTorchHint(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        torch_hint_mail[0].func = actSt04aTorchHintChk;
        act->mail = torch_hint_mail;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
}

void actSt04aModel(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSearchGobj(648)->active = 0;

    model_mail[0].func = actSt04aModelOnChk;
    act->mail = model_mail;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

void actSt04aEnvSe(GObj *volatile self)
{
    float f = 0.0f;

    scpSeEnvMasterVolRate = 0.0f;

    for (;;) {
        float nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 5401) {
            scpSeEnvMasterVolRate += 1.0f / 1800.0f;
            if (scpSeEnvMasterVolRate > 1.0f) {
                scpSeEnvMasterVolRate = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actSt04aEnvSeWakare1(GObj *volatile self)
{
    float f = 0.0f;

    scpSeEnvMasterVolRate = 0.0f;

    for (;;) {
        float nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2201) {
            scpSeEnvMasterVolRate += 1.0f / 3800.0f;
            if (scpSeEnvMasterVolRate > 1.0f) {
                scpSeEnvMasterVolRate = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

typedef struct { /* field names derived */
    float m[4];
} Vec4St04A; /* derived name */

static void finishCallBackFunc(GObj *obj)
{
    Vec4St04A v;
    int i;

    _ApplyMatrix(&v, GOBJ_SUB(obj)->nodeMtx, YUnitVector);
    v.m[1] = 0.0f;
    _NormalizeVector(GOBJ_SUB(obj)->ctrl.dir, &v);

    for (i = 0; i < GOBJ_SUB(obj)->skelNodeNum; i++) {
        *(Mtx44 *)&GOBJ_SUB(obj)->nodeRotElem[i] = jointMtxInit;
    }
}

void actSt04aGateOpen2ReadyChk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(streamMotion[3].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(32, &gate_open2, 1, 0, 0);
}

void actSt04aEnvSeWakare2(GObj *volatile self)
{
    float f = 0.0f;

    for (;;) {
        float nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2351) {
            scpSeEnvMasterVolRate -= 1.0f / 720.0f;
            if (scpSeEnvMasterVolRate < 0.0f) {
                scpSeEnvMasterVolRate = 0.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actConte09_3Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 2470:
            jimaku_msg.sub.block = 91;
            jimaku_msg.sub.jump = 300;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 3000.0f);
}

static void actConte09_3_demoCancel(GObj *volatile self)
{
    while (1) {
        _ACTWait(1);
    }
}

INCLUDE_ASM(actSt04aGateLSub);

INCLUDE_ASM(actSt04aGateRSub);

void actSt04aGirlSitChk(GObj *volatile self)
{
    int n;

    while (gflagChk(140) == 0) {
        _ACTWait(1);
    }
    GOBJ_ACT(girlGObj)->flags20.ll |= 0x10000;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 20) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < n) {
            iosOmSendMail(girlGObj, 109, girlGObj);
            n = 0;
        }
        _ACTWait(1);
    }
}

/* The model-on watcher's mail record: it installs actSt04aModelOffChk here
   and posts it. Word 0 of each entry is the mail id the entry answers (430
   the actor post, 429 the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
static ActMail model_on[2] = {{430}, {429}}; /* derived name */

static void actSt04aModelOnChk(GObj *volatile self)
{
    ActSt04A *sub = ((PObjGObjSt04A *)self)->act;

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(648)->active = 1;

    model_on[0].func = actSt04aModelOffChk;
    sub->mail = model_on;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}

/* The model-off watcher's own mail record (installs actSt04aModelOnChk). */
static ActMail model_off[2] = {{430}, {429}}; /* derived name */

static void actSt04aModelOffChk(GObj *volatile self)
{
    ActSt04A *sub = ((PObjGObjSt04A *)self)->act;

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(648)->active = 0;

    model_off[0].func = actSt04aModelOnChk;
    sub->mail = model_off;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
