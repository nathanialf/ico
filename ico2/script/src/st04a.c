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
static ActMail gate_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open2_ready_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open2_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open3_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_l_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_r_mail[2] = {{377}, {376}}; /* derived name */

static ActMail torch1_mail[2] = {{377}, {376}}; /* derived name */

static ActMail girl_sit_mail[2] = {{377}, {376}}; /* derived name */

typedef struct AnimList28 { /* field names derived */
    int v[28];
} AnimList28; /* derived name */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* .sdata: the first gate's stream handle (func_00200E08 plays it). */
SqEntry *gate1st = 0;

/* No .sbss here in this build: no function of the demo addresses these flags. */

INCLUDE_ASM(actSt04aObj535);

INCLUDE_ASM(func_00200E08);

INCLUDE_ASM(actSt04aConte06);

/* .sdata: the gate and torch stream handles, then the pad shakes and their
   volumes (declared in st04a.h for actSt04aConte06). In this build the
   handles are the demo's five words its functions address (func_00201A10,
   actSt04aGateOpen3Chk with the environment sounds, actConte09_2 with
   actSt04aGateOpen3Chk, actSt04aTorchAllFlagfChk), and only actSt04aConte06
   and actConte09 shake the pad: no gate1, no gate-ready handles, no third
   shake. */
static SqEntry *gate_open = 0; /* derived name */

static SqEntry *gate_open2 = 0; /* derived name */

static SqEntry *conte09_2 = 0; /* derived name */

SqEntry *torch = 0;

int gate_yure_low = 0;

unsigned char gate_yure_low_vol = 0;

int yure1 = 0;

unsigned char vol1 = 0;

INCLUDE_ASM(actSt04aConte06Jimaku);

INCLUDE_ASM(actSt04aGateOpen);

INCLUDE_ASM(func_00201A10);

typedef struct AnimList { /* field names derived */
    int v[13];
} AnimList; /* derived name */

/* .rodata, used here and by actConte09_2: the first lift offset, declared
   ahead and defined with the second after actSt04aGateOpenChk. */
static const ConstVec liftOfs1;

static const ConstVec liftOfs1 = {{0.0f, 0.0f, 6000.0f, 1.0f}}; /* derived name */

static const ConstVec liftOfs2 = {{-5000.0f, 0.0f, 5300.0f, 1.0f}}; /* derived name */

INCLUDE_ASM(actConte09);

INCLUDE_ASM(actConte09Jimaku);

void actSt04aGateOpen2Chk(GObj *volatile self);

INCLUDE_ASM(actConte09_2);

INCLUDE_ASM(actSt04aGateOpen3Chk);

INCLUDE_ASM(actConte09_3);

void actSt04aGateLChk(GObj *volatile self);

INCLUDE_ASM(actSt04aGateRChk);

INCLUDE_ASM(actSt04aTorch1);

INCLUDE_ASM(actSt04aTorch1Chk);

INCLUDE_ASM(actSt04aTorchAllFlagfChk);

INCLUDE_ASM(actSt04aGateL);

INCLUDE_ASM(actSt04aGateR);

INCLUDE_ASM(actSt04aTorchXL);

INCLUDE_ASM(actSt04aGateOpen2);

INCLUDE_ASM(actSt04aGateOpen3);

INCLUDE_ASM(actSt04aGateOpen2Ready);

INCLUDE_ASM(actSt04aGirlSit);

INCLUDE_ASM(actSt04aEnvSe);

INCLUDE_ASM(actSt04aEnvSeWakare1);

typedef struct { /* field names derived */
    float m[4];
} Vec4St04A; /* derived name */

INCLUDE_ASM(finishCallBackFunc);

INCLUDE_ASM(actSt04aGateOpen2ReadyChk);

INCLUDE_ASM(actSt04aGirlSitChk);

/* The model-on watcher's mail record: it installs actSt04aModelOffChk here
   and posts it. Word 0 of each entry is the mail id the entry answers (430
   the actor post, 429 the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
/* The model-off watcher's own mail record (installs actSt04aModelOnChk). */
