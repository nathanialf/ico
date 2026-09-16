#include "common.h"
#include "end.h"
#include "layout_texture.h"
#include "adpcm_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "jimaku.h"
#include "camera-root.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "boy.h"
#include "girl.h"
#include "item.h"
#include "staticBlur.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x15C]; /* 0x000 */
    char *f15C;        /* 0x15C */
    char pad160[0x4];  /* 0x160 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

typedef struct JimakuSub {
    char unk00[0x2C]; /* 0x0C */
    int unk2C;        /* 0x38 */
    int n;            /* 0x3C */
    int unk34;        /* 0x40 */
    int unk38;        /* 0x44 */
    void *unk3C;      /* 0x48 */
    void *unk40;      /* 0x4C */
} JimakuSub;

typedef struct JimakuArg {
    int cmd;       /* 0x00 */
    int unk04;     /* 0x04 */
    int done;      /* 0x08 */
    JimakuSub sub; /* 0x0C */
} JimakuArg;

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);

static ActMail demo01_mes[2] = {{430}, {429}};

static ActMail demo02_mes[2] = {{430}, {429}};

static ActMail demo03_mes[2] = {{430}, {429}};

static ActMail demo04_mes[2] = {{430}, {429}};

static ActMail demo05_mes[2] = {{430}, {429}};

static ActMail demo06_mes[2] = {{430}, {429}};

static ActMail demo07_mes[2] = {{430}, {429}};

static ActMail demo10_mes[2] = {{430}, {429}};

static ActMail demo11_mes[2] = {{430}, {429}};

static ActMail demo12_mes[2] = {{430}, {429}};

static ActMail demo13_mes[2] = {{430}, {429}};

static ActMail staff1_mes[2] = {{430}, {429}};

static ActMail staff2_mes[2] = {{430}, {429}};

static ActMail staff3_mes[2] = {{430}, {429}};

static ActMail ed_demo14_mes[2] = {{430}, {429}};

static ActMail st27aEnd_mes[2] = {{430}, {429}};

static ActMail logo_mes[2] = {{430}, {429}};

static ActMail end_mes[2] = {{430}, {429}};

extern int D_0063AA08;

void actEndDemo01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x153) == 0 && gflagChk(0x157) == 0) {
        lt_switch_layout(0x37);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(0x348, 0, 0);
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, 0);
        stage_SetAnimation(0x23, 0, -1);
        stage_SetAnimation(0x21, 0, -1);
        stage_SetAnimation(0x22, 0, -1);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
        demo01_mes[0].func = actEndDemo01Chk;
        self->mail = demo01_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;

void actConte14_1(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x32E, 1, 0);

    scpPlayMot((int)scpSearchGobj(0x9D3), 0x329);

    scpSearchGobj(0x9D3)->f16C = 1;

    while (stage_ContinueAnimation(0x32E, 0x32F) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x32F, 0x330) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x37, 1, 0);

    while (stage_ContinueAnimation(0x330, 0x331) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x331, 0x332) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x332, 0x333) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(0x9D3), 0x32A);

    while (stage_ContinueAnimation(0x333, 0x334) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(0x9D3)->f16C = 0;

    scpPlayMot((int)scpSearchGobj(0x9D4), 0x32B);

    scpSearchGobj(0x9D4)->f16C = 1;

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0x9D4, 0, 0x22A, 0);

    stage_SetLoopFlag(0x22A, 1);

    stage_SetAnimation(0x22A, 1, 0);

    while (stage_ContinueAnimation(0x334, 0x335) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(0x9D4), 0x32C);

    while (stage_ContinueAnimation(0x335, 0x336) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(0x9D4), 0x32D);

    while (stage_ContinueAnimation(0x336, 0x337) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(0x9D4), 0x32E);

    while (stage_CheckAnimationFinish(0x337) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, D_00639EA4, 0, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 0x22A, 0);
    stage_SetLoopFlag(0x22A, 1);
    stage_SetAnimation(0x22A, 1, 0);
    stage_SetAnimation(0x339, 0, 0);
    stage_SetAnimation(0x22C, 0, -1);
    stage_SetAnimation(0x22D, 0, -1);
    stage_SetAnimation(0x22F, 0, -1);
    stage_SetAnimation(0x230, 0, -1);
    stage_SetAnimation(0x231, 0, -1);
    SelectBoyCrown(D_00639EA4, 2);
    demo02_mes[0].func = actEndDemo02Chk;
    self->mail = demo02_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;

void actConte14_2(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x338, 1, 0);

    scpPlayMot(D_00639EA4, 0x1B9);

    while (stage_ContinueAnimation(0x338, 0x339) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x339, 0x33A) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(0xA7E), 0x32F);

    scpSearchGobj(0xA7E)->f16C = 1;

    _ACTWait(1);

    stage_SetAnimation(0x33B, 1, 0);

    while (stage_ContinueAnimation(0x33A, 0x33C) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1BA);

    scpPlayMot((int)scpSearchGobj(0xA7E), 0x330);

    while (stage_ContinueAnimation(0x33C, 0x33D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1BB);

    scpPlayMot((int)scpSearchGobj(0xA7E), 0x331);

    while (stage_ContinueAnimation(0x33D, 0x33E) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1BC);

    scpPlayMot((int)scpSearchGobj(0xA7E), 0x332);

    while (stage_ContinueAnimation(0x33E, 0x33F) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1BD);

    scpPlayMot((int)scpSearchGobj(0xA7E), 0x333);

    _ACTWait(1);

    stage_SetAnimation(0x340, 1, 0);

    while (stage_CheckAnimationFinish(0x33F) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(D_00639EA4);

    lt_switch_layout(0x36);

    RequestStageChange(3, D_00639EA4, 0, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo06(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x158) == 0 && gflagChk(0x157) != 0) {
        lt_switch_layout(0x37);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0x9D4, 0, 0x22A, 0);
        stage_SetLoopFlag(0x22A, 1);
        stage_SetAnimation(0x22A, 1, 0);
        stage_SetAnimation(0x348, 0, 0);
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, 0);
        stage_SetAnimation(0x23, 0, -1);
        stage_SetAnimation(0x21, 0, -1);
        stage_SetAnimation(0x22, 0, -1);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
        SelectBoyCrown(D_00639EA4, 2);
        demo06_mes[0].func = actEndDemo06Chk;
        self->mail = demo06_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_6(volatile int a0)
{
    preload(3);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x346, 1, 0);

    stage_SetAnimation(0x348, 1, 0);

    stage_SetAnimation(0x349, 1, 0);

    scpPlayMot(D_00639EA4, 0x1BE);

    scpPlayMot((int)scpSearchGobj(0x9D4), 0x334);

    scpSearchGobj(0x9D4)->f16C = 1;

    while (stage_ContinueAnimation(0x346, 0x347) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1BF);

    scpPlayMot((int)scpSearchGobj(0x9D4), 0x335);

    while (stage_CheckAnimationFinish(0x347) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo07(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 0x22A, 0);
    stage_SetAnimation(0xAD, 0, 0);
    stage_SetLoopFlag(0x22A, 1);
    stage_SetAnimation(0x22A, 1, 0);

    if (gflagChk(0x159) == 0) {
        SelectBoyCrown(D_00639EA4, 2);
        demo07_mes[0].func = actEndDemo07Chk;
        self->mail = demo07_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpPlayMotNode do not fit the prototype in script.h */
extern void scpPlayMotNode(int a0, int mot, int node, int a3);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */
typedef union {
    float f[4];
    long long d[2];
} ConstVec;

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}};

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}};

static const ConstVec conte14_14Pos = {{16975.0f, 71.0f, -4332.0f, 1.0f}};

extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_7(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    preload(6);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x34A, 1, 0);

    stage_SetAnimation(0xAD, 1, 0x1D7);

    _ACTWait(1);

    scpPlayPosSet(D_00639EA4, -4757.0f, -660.0f, 2646.0f);

    scpPlayPosSet((int)scpSearchGobj(0x954), -4757.0f, -664.0f, 2646.0f);

    _ACTWait(1);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)scpSearchGobj(0x954)));
    scpPlayMotDir((int)scpSearchGobj(0x954), dir);

    scpPlayMotNode(D_00639EA4, 0x1C0, (int)scpSearchGobj(0x954), 0x2C);

    scpPlayMot((int)scpSearchGobj(0x954), 0x336);

    scpSearchGobj(0x954)->f16C = 1;

    while (stage_CheckAnimationFinish(0x34A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo10(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 0x22A, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0x34, 0x3A, 0);
    stage_SetLoopFlag(0x22A, 1);
    stage_SetAnimation(0x22A, 1, 0);
    SelectBoyCrown(D_00639EA4, 2);
    stage_SetAnimation(0x352, 0, 0);
    demo10_mes[0].func = actEndDemo10Chk;
    self->mail = demo10_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int ed6;
extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_10(volatile int a0)
{
    preload(3);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x34B, 1, 0);

    scpPlayMot(D_00639EA4, 0x1C1);

    scpPlayMot((int)scpSearchGobj(0x84A), 0x337);

    scpSearchGobj(0x84A)->f16C = 1;

    _ACTWait(1);

    stage_SetAnimation(0x2D, 1, 0);

    stage_SetAnimation(0x34C, 1, 0);

    while (stage_ContinueAnimation(0x34B, 0x34D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1C2);

    scpPlayMot((int)scpSearchGobj(0x84A), 0x338);

    _ACTWait(1);

    stage_SetAnimation(0x2E, 1, 0);

    while (stage_ContinueAnimation(0x34D, 0x34E) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1C3);

    scpPlayMot((int)scpSearchGobj(0x84A), 0x339);

    _ACTWait(1);

    stage_SetAnimation(0x2F, 1, 0);

    while (stage_ContinueAnimation(0x34E, 0x34F) == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(ed6 + 0x2C));

    scpPlayMot(D_00639EA4, 0x1C4);

    scpPlayMot((int)scpSearchGobj(0x84A), 0x33A);

    _ACTWait(1);

    stage_SetAnimation(0x30, 1, 0);

    while (stage_ContinueAnimation(0x34F, 0x350) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1C5);

    scpPlayMot((int)scpSearchGobj(0x84A), 0x33B);

    _ACTWait(1);

    stage_SetAnimation(0x31, 1, 0);

    while (stage_ContinueAnimation(0x350, 0x351) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1C6);

    _ACTWait(1);

    stage_SetAnimation(0x32, 1, 0);

    stage_SetAnimation(0x38, 1, 0);

    stage_SetAnimation(0x352, 1, 0);

    while (stage_ContinueAnimation(0x351, 0x353) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1C7);

    _ACTWait(1);

    stage_SetAnimation(0x33, 1, 0);

    stage_SetAnimation(0x39, 1, 0);

    while (stage_CheckAnimationFinish(0x353) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_13(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    scpFadeIn(3.0f);

    preload(6);

    stage_SetAnimation(0x356, 1, 0);

    scpPlayMot(D_00639EA4, 0x1C8);

    while (stage_ContinueAnimation(0x356, 0x357) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x35, 1, 0);

    stage_SetAnimation(0x1D1, 1, 0);

    scpPlayMot(D_00639EA4, 0x1C8);

    while (stage_CheckAnimationFinish(0x357) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(D_00639EA4);

    RequestStageChange(6, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

extern int D_0063AA08;

void actStaff1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    stage_SetAnimation(0x1E, 0, -1);
    stage_SetAnimation(0x1A, 0, 0);
    stage_SetAnimation(0x21, 0, 0);
    stage_SetAnimation(0x22, 0, 0);
    stage_SetAnimation(0x24, 0, 0);
    stage_SetAnimation(0x26, 0, 0);
    stage_SetAnimation(0x23, 0, 0);
    staff1_mes[0].func = actStaff1Chk;
    self->mail = staff1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: the declaration in staffroll.h changes this TU codegen */
extern void staffRollStart(int a0, float a1);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;

void actStaff1Demo(volatile int a0)
{
    preload(1);

    staffRollStart(0xFF, 1.0f);

    stage_SetAnimation(0x366, 1, 0);

    while (stage_ContinueAnimation(0x366, 0x367) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x1A, 1, 0);

    scpPlayMot(D_00639EA4, 0x120);

    while (stage_ContinueAnimation(0x367, 0x369) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x369, 0x36A) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x121);

    _ACTWait(0x82);

    stage_SetAnimation(0x20, 1, 0);

    while (stage_ContinueAnimation(0x36A, 0x36B) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x36B, 0x36C) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x122);

    while (stage_ContinueAnimation(0x36C, 0x36D) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x36D, 0x36E) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x124);

    _ACTWait(1);

    stage_SetAnimation(0x20, 1, 0xD0);

    while (stage_ContinueAnimation(0x36E, 0x36F) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x125);

    while (stage_ContinueAnimation(0x36F, 0x370) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x126);

    while (stage_ContinueAnimation(0x370, 0x371) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x127);

    while (stage_ContinueAnimation(0x371, 0x372) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x128);

    while (stage_ContinueAnimation(0x372, 0x373) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x129);

    while (stage_CheckAnimationFrame(0x373, 0x64, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(8.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, D_00639EA8, 0.0f, 8.0f);
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;

void actStaff2Demo(volatile int a0)
{
    preload(1);

    stage_SetAnimation(0x38B, 1, 0);

    stage_SetAnimation(0x10D, 1, 0);

    scpPlayMot(D_00639EA4, 0x147);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2E1);

    scpSearchGobj(0xAE5)->f16C = 1;

    while (stage_ContinueAnimation(0x38B, 0x38C) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x148);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2E2);

    while (stage_ContinueAnimation(0x38C, 0x38D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x149);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2E3);

    while (stage_ContinueAnimation(0x38D, 0x38E) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x38E, 0x38F) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x14A);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2E4);

    while (stage_ContinueAnimation(0x38F, 0x390) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x14B);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2E5);

    while (stage_ContinueAnimation(0x390, 0x391) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x14C);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2E6);

    while (stage_ContinueAnimation(0x391, 0x392) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x14D);

    while (stage_ContinueAnimation(0x392, 0x3A1) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x155);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2EC);

    while (stage_ContinueAnimation(0x3A1, 0x3A2) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x156);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2ED);

    while (stage_ContinueAnimation(0x3A2, 0x3A3) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x157);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2EE);

    while (stage_ContinueAnimation(0x3A3, 0x3A4) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x158);

    scpPlayMot((int)scpSearchGobj(0xAE5), 0x2EF);

    while (stage_CheckAnimationFrame(0x3A4, 0xC8, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    reg_SetScissorSw(0);

    SetStaticBlur(1);

    scpFadeOut(8.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, D_00639EA8, 0.0f, 8.0f);
}

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
extern void sceVu0SubVector(void *out, void *a, void *b);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern int D_00639EA4;

void actStaff3Demo(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    stage_SetAnimation(0x374, 1, 0);

    scpPlayPosSet((int)scpSearchGobj(0xB19), -7.0f, -5725.0f, 18.0f);

    ofs[0] = staff3DemoPos.d[0];
    ofs[1] = staff3DemoPos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)scpSearchGobj(0xB19)));
    scpPlayMotDir((int)scpSearchGobj(0xB19), dir);

    scpPlayMot((int)scpSearchGobj(0xB19), 0x227);

    scpSearchGobj(0xB19)->f16C = 1;

    scpPlayMot(D_00639EA4, 0x134);

    while (stage_ContinueAnimation(0x374, 0x375) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x135);

    while (stage_ContinueAnimation(0x375, 0x376) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x136);

    while (stage_ContinueAnimation(0x376, 0x377) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x137);

    while (stage_ContinueAnimation(0x377, 0x37F) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x4A, 0, -1);

    scpPlayMot(D_00639EA4, 0x13E);

    scpPlayMot((int)scpSearchGobj(0xB19), 0x2D8);

    while (stage_ContinueAnimation(0x37F, 0x380) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x13E);

    scpPlayMot((int)scpSearchGobj(0xB19), 0x2D9);

    while (stage_ContinueAnimation(0x380, 0x381) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x13E);

    scpPlayMot((int)scpSearchGobj(0xB19), 0x2DA);

    while (stage_ContinueAnimation(0x381, 0x382) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x13F);

    scpPlayMot((int)scpSearchGobj(0xB19), 0x2DB);

    while (stage_ContinueAnimation(0x382, 0x384) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x140);

    scpPlayMot((int)scpSearchGobj(0xB19), 0x2DC);

    while (stage_CheckAnimationFrame(0x384, 0xC8, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(6.0f, 0, 0, 0);
}

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);

/* Demo 14's mail record: the actor installs actEndDemo14Chk in it and posts
   it. Word 0 of each entry is the mail id the entry answers (430 the actor
   post, 429 the trailing entry); .func is filled in at run time. Named in
   this TU's own terse snake_case house style (its MAIN.MAP globals are
   ed1..ed6, sea, happy_end) for the ending demo it belongs to. */

extern int D_0063A054;
extern int D_0063AA08;
extern int D_0063BE34;
extern int D_00639EA4;

void actEndDemo14(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    D_0063A054 = 1;
    scpFadeOut(3.0f, 0xFF, 0xFF, 0xFF);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    D_0063A054 = 0;
    ScpCallCameraSetTarget(7046.0f, -77.0f, 1678.0f);

    scpAdpcmPlayRequestFunc(0x5F, &D_0063BE34, 1, 0, 1);

    while (D_0063BE34 == 0) {
        _ACTWait(1);
    }

    SelectBoyCrown(D_00639EA4, 2);
    SetGirlClothDispSwitch(scpSearchGobj(0x8CD), 1, 2);
    ed_demo14_mes[0].func = actEndDemo14Chk;
    self->mail = ed_demo14_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
extern void sceVu0SubVector(void *out, void *a, void *b);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
extern int D_00639EA4;
extern int D_0063AA08;

void actConte14_14(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    scpPlayStart(D_00639EA4);

    scpFadeIn(6.0f);

    stage_SetAnimation(0x35C, 1, 0);

    scpPlayMot(D_00639EA4, 0x1CD);

    while (stage_ContinueAnimation(0x35C, 0x35D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1CE);

    while (stage_ContinueAnimation(0x35D, 0x35E) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1CF);

    _ACTWait(1);

    stage_SetAnimation(0x36, 1, 0);

    while (stage_ContinueAnimation(0x35E, 0x35F) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1D0);

    while (stage_ContinueAnimation(0x35F, 0x360) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1D1);

    while (stage_ContinueAnimation(0x360, 0x361) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x1D2);

    scpPlayMot((int)scpSearchGobj(0x8CD), 0x33D);

    scpSearchGobj(0x8CD)->f16C = 1;

    while (stage_CheckAnimationFinish(0x361) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(0xB4);

    scpPlayMot(D_00639EA4, 0);

    ofs[0] = conte14_14Pos.d[0];
    ofs[1] = conte14_14Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    lt_switch_layout(0x36);

    gflagOff(0x152);
}

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
extern int D_0063AA00;

void actSt27aEnd(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_0063AA00 == 0) {
        scpSearchGobj(0x8D0)->f16C = 0;
        scpSearchGobj(0x8D1)->f16C = 0;
        scpSearchGobj(0x8D2)->f16C = 0;
        scpSearchGobj(0x8D3)->f16C = 0;
        scpSearchGobj(0x8D4)->f16C = 0;
        scpSearchGobj(0x8D5)->f16C = 0;
        scpSearchGobj(0x8D6)->f16C = 0;
        scpSearchGobj(0x8D7)->f16C = 0;
    }

    if (gflagChk(0x163) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        self->mail = st27aEnd_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern int D_00639EA4;
extern int D_0063AA08;
extern float D_0063AA0C;
extern int D_0063BE34;
extern int D_0063BE38;
extern int D_0028F4C0[];
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int gobj, int attr);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);

/* listing lines 2614-2661 */
void actSt27aEndChk(volatile int a0)
{
    float max;
    float t;

    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    if (GetCharHeldItem(D_00639EA4) == 3) {
        gflagOn(0x162);
        scpPlayMot(D_00639EA4, 0x9D);
    }

    if (D_0063BE34 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BE34, 0x1B);
    }
    scpAdpcmPlayRequestFunc(0x33, &D_0063BE38, 0, 1, 1);
    while (D_0063BE38 == 0) {
        _ACTWait(1);
    }

    gflagOn(0x163);

    actCreateSubThread(actSt27aEndDemo, 0x15);

    max = (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 20);
    t = (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 20);
    while (t > 0.0f) {
        D_0063AA0C = t / max;
        t -= 1.0f;
        _ACTWait(1);
    }
    D_0063AA0C = 0;
}

/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpDisActivateAllWithKind do not fit the prototype in script.h */
extern void scpDisActivateAllWithKind(int a0);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063BE38;

void actSt27aEndDemo(volatile int a0)
{
    stage_SetAnimation(0x362, 1, 0);

    if (gflagChk(0x162) == 0) {
        scpPlayMot(D_00639EA4, 0x1D3);
    } else {
        scpPlayMot(D_00639EA4, 0x1D6);
    }

    scpPlayMot((int)scpSearchGobj(0x8CD), 0x33E);

    scpSearchGobj(0x8CD)->f16C = 1;

    while (stage_ContinueAnimation(0x362, 0x363) == 0) {
        _ACTWait(1);
    }

    if (gflagChk(0x162) == 0) {
        scpPlayMot(D_00639EA4, 0x1D4);
    } else {
        scpPlayMot(D_00639EA4, 0x1D7);
    }

    scpPlayMot((int)scpSearchGobj(0x8CD), 0x33F);

    while (stage_ContinueAnimation(0x363, 0x364) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0xA, 0xA);

    SetZoomMaxValInDemo(0x1E);

    if (gflagChk(0x162) == 0) {
        scpPlayMot(D_00639EA4, 0x1D5);
    } else {
        scpPlayMot(D_00639EA4, 0x1D8);
    }

    scpPlayMot((int)scpSearchGobj(0x8CD), 0x340);

    if (gflagChk(0x162) == 0) {
        while (stage_CheckAnimationFinish(0x364) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        ResetHandCameraLimitInDemo();

        ResetZoomMaxValInDemo();

        RequestStageChange(1, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
    } else {
        if (D_0063BE38 != 0) {
            scpAdpcmFadeCloseFunc(&D_0063BE38, 0x50);
        }

        while (stage_CheckAnimationFrame(0x364, 0x186, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        ResetHandCameraLimitInDemo();

        ResetZoomMaxValInDemo();

        scpFadeOut(6.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        scpDisActivateAllWithKind(0x13);

        scpFadeIn(1.5f);

        stage_SetAnimation(0x365, 1, 0);

        stage_SetAnimation(0xC6, 1, 0);

        scpPlayMot(D_00639EA4, 0x1D9);

        scpPlayMot((int)scpSearchGobj(0x8CD), 0x341);

        while (stage_CheckAnimationFrame(0x365, 0x186, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        scpFadeOut(3.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        _ACTWait(0xA);

        scpPlayMot(D_00639EA4, 0);

        _ACTWait(0xA);

        RequestStageChange(1, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
    }
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);

/* The ending's save hand-off mail record: the logo watcher installs
   actEndingSave in it and posts it. Word 0 of each entry is the mail id the
   entry answers (430 the actor post, 429 the trailing entry); .func is
   filled in at run time. Named in this TU's own terse snake_case house style
   (its MAIN.MAP globals are ed1..ed6, sea, happy_end) for the sequence it
   belongs to; among the role-plausible spellings this is one that also puts
   the record ahead of the handler in gcc's expression-hash order. */

extern int D_0063AA08;
extern int NonLinearCameraMove;
extern int enable_game_pause;
extern int D_0028F4C0[];

void actEndLogoChk(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    int id = 0x3C;

    _ACTWait(1);

    D_0063AA08 = 1;
    enable_game_pause = 0;

    switch (NonLinearCameraMove) {
    case 3:
        id = 0x3D;
        break;
    case 4:
        id = 0x3E;
        break;
    case 6:
        id = 0x40;
        break;
    case 5:
        id = 0x3F;
        break;
    }

    stage_SetLoopFlag(id, 1);

    stage_SetAnimation(id, 1, 0);

    SetHandCameraLimitInDemo(0, 0);

    SetZoomMaxValInDemo(0);

    preload(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x1E);

    scpFadeOut(6.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(id, -1, -2);

    scpFadeIn(6.0f);

    end_mes[0].func = actEndingSave;
    self->mail = end_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    stage_SetAnimation(0x4A, 0, -1);
    stage_SetAnimation(0x4B, 0, -1);
    stage_SetAnimation(0x4D, 0, -1);
    demo03_mes[0].func = actEndDemo03Chk;
    self->mail = demo03_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo04(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    demo04_mes[0].func = actEndDemo04Chk;
    self->mail = demo04_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int D_0063AA08;

void actEndDemo05(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    demo05_mes[0].func = actEndDemo05Chk;
    self->mail = demo05_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo11(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    SelectBoyCrown(D_00639EA4, 2);
    demo11_mes[0].func = actEndDemo11Chk;
    self->mail = demo11_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int D_0063AA08;

void actEndDemo12(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    stage_SetAnimation(0x50, 0, -1);
    demo12_mes[0].func = actEndDemo12Chk;
    self->mail = demo12_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern int D_0063AA08;
extern int D_00639EA4;

void actEndDemo13(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0xFF, 0xFF, 0xFF);
    SelectBoyCrown(D_00639EA4, 2);
    demo13_mes[0].func = actEndDemo13Chk;
    self->mail = demo13_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpSetBoyWeaponGObj do not fit the prototype in script.h */
extern void scpSetBoyWeaponGObj(PObjGObj *gobj);
extern int D_0063AA08;

void actStaff2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSetBoyWeaponGObj(scpSearchGobj(0xAEB));
    *(int *)(scpSearchGobj(0xAE9)->f15C + 0x658) = 1;
    *(int *)(scpSearchGobj(0xAEA)->f15C + 0x658) = 1;
    stage_SetAnimation(0x10D, 0, 0);
    staff2_mes[0].func = actStaff2Chk;
    self->mail = staff2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern int D_0063AA08;

void actStaff3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    DeleteBoyWeapon();
    stage_SetAnimation(0x48, 0, 0);
    stage_SetAnimation(0x4D, 0, 0);
    staff3_mes[0].func = actStaff3Chk;
    self->mail = staff3_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndLogo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    logo_mes[0].func = actEndLogoChk;
    self->mail = logo_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int ed1;

void actEndDemo01Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(0x2B, &ed1, 0, 1, 1);

    while (ed1 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(2);

    gflagOn(3);

    gflagOn(4);

    gflagOn(0x153);

    actCreateSubThread(actConte14_1, 0x15);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int ed2;

void actEndDemo02Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(0x2C, &ed2, 0, 1, 1);

    while (ed2 == 0) {
        _ACTWait(1);
    }

    preload(3);

    scpFadeIn(6.0f);

    gflagOn(0x154);

    actCreateSubThread(actConte14_2, 0x15);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int ed3;

void actEndDemo03Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(0x2D, &ed3, 0, 1, 1);

    while (ed3 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(0x155);

    actCreateSubThread(actConte14_3, 0x15);
}

/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;

void actConte14_3(volatile int a0)
{
    stage_SetAnimation(0x341, 1, 0);

    while (stage_CheckAnimationFinish(0x341) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, D_00639EA4, 0, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int ed4;

void actEndDemo04Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(0x2E, &ed4, 0, 1, 1);

    while (ed4 == 0) {
        _ACTWait(1);
    }

    preload(5);

    scpFadeIn(6.0f);

    gflagOn(0x156);

    actCreateSubThread(actConte14_4, 0x15);
}

/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_4(volatile int a0)
{
    stage_SetAnimation(0x342, 1, 0);

    while (stage_CheckAnimationFinish(0x342) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(5, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

void actEndDemo05Chk(volatile int a0)
{
    gflagOn(0x157);

    actCreateSubThread(actConte14_5, 0x15);
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_5(volatile int a0)
{
    preload(6);

    stage_SetAnimation(0x343, 1, 0);

    while (stage_CheckAnimationFinish(0x343) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int sea;

void actEndDemo06Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(0x2F, &sea, 0, 1, 1);

    while (sea == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOff(0x153);

    gflagOff(0x157);

    actCreateSubThread(actConte14_6, 0x15);
}

/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);

void actEndDemo07Chk(volatile int a0)
{
    _ACTWait(0x1E);

    scpFadeIn(6.0f);

    gflagOn(0x159);

    actCreateSubThread(actConte14_7, 0x15);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int ed6;

void actEndDemo10Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(0x30, &ed6, 0, 1, 0);

    while (ed6 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOn(0x15C);

    actCreateSubThread(actConte14_10, 0x15);

    actCreateSubThread(actConte14_10_Jimaku, 0x15);
}

extern JimakuArg jimaku_msg;
extern int jimakuOn;
extern int D_0028F4C0[];

void actConte14_10_Jimaku(volatile int a0)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin((int)&jimaku_msg);
            break;
        case 1500:
            jimaku_msg.sub.unk2C = 0x70;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 1800.0f);
}

void actEndDemo11Chk(volatile int a0)
{
    gflagOn(0x15D);

    actCreateSubThread(actConte14_11, 0x15);
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_11(volatile int a0)
{
    preload(2);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x354, 1, 0);

    while (stage_CheckAnimationFinish(0x354) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

void actEndDemo12Chk(volatile int a0)
{
    gflagOn(0x15E);

    actCreateSubThread(actConte14_12, 0x15);
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of RequestStageChangeWithColor do not fit the prototype in script.h */
extern int RequestStageChangeWithColor(int a0, int a1, int a2, float a3, float a4, int r, int g,
                                       int b);
extern int D_00639EA4;
extern int D_00639EA8;

void actConte14_12(volatile int a0)
{
    stage_SetAnimation(0x355, 1, 0);

    preload(4);

    while (stage_CheckAnimationFinish(0x355) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChangeWithColor(4, D_00639EA4, D_00639EA8, 16.0f, 16.0f, 0xFF, 0xFF, 0xFF);
}

void actEndDemo13Chk(volatile int a0)
{
    gflagOn(0x15F);

    actCreateSubThread(actConte14_13, 0x15);
}

void actStaff1Chk(volatile int a0)
{
    actCreateSubThread(actStaff1Demo, 0x15);
}

void actStaff2Chk(volatile int a0)
{
    reg_SetScissorSw(1);

    SetStaticBlur(0);

    actCreateSubThread(actStaff2Demo, 0x15);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
extern int D_0063BE30;

void actStaff3Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(0x31, &D_0063BE30, 0, 1, 1);

    while (D_0063BE30 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    actCreateSubThread(actStaff3Demo, 0x15);

    actCreateSubThread(actStaff3RollChk, 0x15);
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;
extern int staffRollStartFlag;
extern int ed6;

void actStaff3RollChk(volatile int a0)
{
    preload(1);

    while (staffRollStartFlag != 0) {
        _ACTWait(1);
    }

    if (ed6 != 0) {
        scpAdpcmFadeCloseFunc(&ed6, 0x50);
    }

    RequestStageChange(1, D_00639EA4, 0, 16.0f, 0.001f);
}

void actEndDemo14Chk(volatile int a0)
{
    gflagOn(0x160);

    actCreateSubThread(actConte14_14, 0x15);
}

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_0029B9D0[];
extern int D_0063AA00;
extern int D_0063B60C;
extern int CurrentTargetGObjSub;
extern int D_00639EA4;

void actEndingSave(volatile int a0)
{
    if (D_0063AA00 == 0) {
        int save;

        D_0063AA00 = 1;
        save = D_0029B9D0[2];
        gflagInit();
        D_0029B9D0[2] = save;
        gflagOn(0x18B);
        lt_switch_layout(0x1C);
        _ACTWait(0x3C);

        while (D_0063B60C != 0x36) {
            _ACTWait(1);
        }
        D_0063AA00 = 0;
    }

    scpFadeOut(255.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    CurrentTargetGObjSub = 0;
    RequestStageChange(1, D_00639EA4, 0, 255.0f, 8.0f);
}
