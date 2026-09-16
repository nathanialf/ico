#include "common.h"
#include "st13c.h"
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
#include "commonact.h"
#include "enemy_act.h"
#include "way_llf.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "gflag.h"
#include "GsBase.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "weapon.h"

typedef union ActStatus {
    unsigned long long ll;
    int i[2];
} ActStatus;

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

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

/* scpEffectStart's argument block: a 16-byte spawn position, copied as a
   pair of doublewords and written as four floats. */
typedef union EffectArg {
    float f[4];

    struct {
        long long lo; /* 0x00 */
        long long hi; /* 0x08 */
    } d;
} EffectArg;

typedef struct AnimSet {
    int anim[5]; /* 0x00 */
} AnimSet;

typedef struct AnimSet16 {
    int anim[16]; /* 0x00 */
} AnimSet16;

typedef struct AdpcmSlot {
    char pad00[0x2C]; /* 0x00 */
    int unk2C;        /* 0x2C */
} AdpcmSlot;

typedef struct MotObj {
    char pad00[0x514]; /* 0x000 */
    int unk514;        /* 0x514 */
} MotObj;

typedef struct Act {
    char unk00[0x20];  /* 0x00 */
    ActStatus flags20; /* 0x20 */
    char unk28[0xC];   /* 0x28 */
    int unk34;         /* 0x34 */
    char unk38[0x68];  /* 0x38 */
    long long flags;   /* 0xA0 */
    char unkA8[0x28];  /* 0xA8 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
    char unkD8[0x20C]; /* 0xD8 */
    int unk2E4;        /* 0x2E4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x15C]; /* 0x000 */
    int unk15C;        /* 0x15C */
    int unk160;        /* 0x160 */
    int act;           /* 0x164 (Act * handle) */
    int unk168;        /* 0x168 */
    int unk16C;        /* 0x16C */
} PObjGObj;

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern int scpSearchGobj(int a0);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int a0);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
extern void sceVu0SubVector(void *out, void *a, void *b);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpPlayMotReq do not fit the prototype in script.h */
extern void scpPlayMotReq(int a0, int mot);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: this TU's uses of ScpCallCameraOff do not fit the prototype in script.h */
extern void ScpCallCameraOff(void);
/* kept local: this TU's uses of jimakuBegin do not fit the prototype in jimaku.h */
extern void jimakuBegin(int a0);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
extern void memset(void *a0, int a1, int a2);
/* kept local: this TU's uses of ScpCallCameraOn do not fit the prototype in script.h */
extern void ScpCallCameraOn(void);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *a0, int a1);
/* kept local: this TU's uses of jimakuUndisp do not fit the prototype in jimaku.h */
extern void jimakuUndisp(int a0);
/* no prototype in the dev's TU: the C89 implicit-int return is what makes
   ee-gcc treat $v0 as clobbered at every call site (it is why ROM alternates
   $2/$3 across the nine calls below). The definition in src/script.c is void. */
/* kept local: this TU's uses of scpEffectStart do not fit the prototype in script.h */
extern int scpEffectStart(void *a0, int a1);
/* kept local: this TU's uses of scpKillEnemyAll do not fit the prototype in script.h */
extern void scpKillEnemyAll(void);
/* kept local: this TU's uses of scpTorchLightOn do not fit the prototype in script.h */
extern void scpTorchLightOn(int a0);
/* kept local: this TU's uses of scpActStatusDeathFall do not fit the prototype in script.h */
extern int scpActStatusDeathFall(int a0);
/* kept local: this TU's uses of scpLockMaxRotate do not fit the prototype in script.h */
extern void scpLockMaxRotate(int a0, float a1);
/* kept local: this TU's uses of scpUnLockMaxRotate do not fit the prototype in script.h */
extern void scpUnLockMaxRotate(int a0);
/* kept local: this TU's uses of _SCPMoveByWay_ToChar do not fit the prototype in script.h */
extern void _SCPMoveByWay_ToChar(int a0, int a1, int a2, int a3, float f0, float f1);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of scpTorchLightOff do not fit the prototype in script.h */
extern void scpTorchLightOff(int a0);
/* kept local: this TU's uses of scpMaskGeneratorAll do not fit the prototype in script.h */
extern void scpMaskGeneratorAll(void);
/* kept local: this TU's uses of scpSekizouCheckPoint do not fit the prototype in script.h */
extern void scpSekizouCheckPoint(void);
/* kept local: this TU's uses of jimakuJump do not fit the prototype in jimaku.h */
extern void jimakuJump(int a0);
extern int D_00639EA4;
extern int D_0063C590;
extern int D_0028F4C0[];
extern int D_0028F8F4[];
extern JimakuArg jimaku_msg;
extern int jimakuOn;

/* st13c.o's own .data run (no MAIN.MAP symbols): actor mail packets. */

static ActMail bmg1_mes[2] = {{430}, {429}};

static ActMail sleep_mes[2] = {{430}, {429}};

static ActMail cageDownMain_mes[2] = {{406, actSt13cCageDownSwitch}, {429}};

static ActMail cageDown_mes[2] = {{430}, {429}};

static ActMail cageDownSwitch_mes[2] = {{430}, {429}};

static ActMail cageFallReady_mes[2] = {{430}, {429}};

static ActMail cageFallChk_mes[2] = {{430}, {429}};

static ActMail cageFallChk2_mes[2] = {{430}, {429}};

static ActMail sekizoJimaku_mes[2] = {{430}, {429}};

static ActMail sekizo_mes[2] = {{430}, {429}};

static ActMail girlCarry_mes[2] = {{430}, {429}};

static ActMail girlCarryChk_mes[2] = {{430}, {429}};

static ActMail girlCarryAgainChk_mes[2] = {{430}, {429}};

static ActMail hand_mes[2] = {{430}, {429}};

static ActMail rescue_mes[2] = {{430}, {429}};

static ActMail buki_mes[2] = {{430}, {429}};

extern int D_0063AA08;
extern int bmg;
extern int hand;
extern int D_00639EAC;
extern unsigned char D_0063C014;
extern int D_0063C010;
extern int D_0063C000;
extern int D_0063C004;
extern int D_0063C00C;
extern int D_0063C594;
extern int D_00639EA8;

void actSt13cInit(void)
{
    if (gflagChk(0x15)) {
        SetWayGroupActive(9, 0);
    }
}

void actSt13cEnd(void)
{
    if (gflagChk(0x1F) == 0) {
        debug_StdPrintfDummy("BackStageOff\n");
        gflagOn(0x186);
    }
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */
typedef union {
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) ConstVec;

/* The animations actSt13cConte04 steps through. */
static const AnimSet conte04Anims = {{625, 626, 627, 628, 629}};

/* Where actSt13cSleepChk turns the sleeping girl to face. */
static const ConstVec sleepFacePos = {{-800.0f, 0.0f, -1000.0f, 1.0f}};

/* The animations actSt13cConte05 steps through. */
static const AnimSet16 conte05Anims = {
    {630, 631, 632, 633, 634, 635, 636, 637, 638, 639, 640, 641, 642, 643, 644, 645}};

/* actSt13cCageFallEffect's nine effect spawns, in the frame order it fires them. */
static const EffectArg cageFallEffect1 = {{-88.0f, -50.0f, -1.0f, 1.0f}};

static const EffectArg cageFallEffect2 = {{-96.0f, -45.0f, 34.0f, 1.0f}};

static const EffectArg cageFallEffect3 = {{72.0f, -50.0f, 8.0f, 1.0f}};

static const EffectArg cageFallEffect4 = {{80.0f, -50.0f, 2.0f, 1.0f}};

static const EffectArg cageFallEffect5 = {{-27.0f, -50.0f, 100.0f, 1.0f}};

static const EffectArg cageFallEffect6 = {{-56.0f, -50.0f, 66.0f, 1.0f}};

static const EffectArg cageFallEffect7 = {{-5.0f, -50.0f, 42.0f, 1.0f}};

static const EffectArg cageFallEffect8 = {{-10.0f, 0.0f, 466.0f, 1.0f}};

static const EffectArg cageFallEffect9 = {{-25.0f, 0.0f, 450.0f, 1.0f}};

void actSt13cBmg1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA8 == 0) {
        return;
    }
    if (gflagChk(0x15) != 0) {
        return;
    }

    ((Act *)((PObjGObj *)D_00639EA4)->act)->flags |= 0x100000;

    if (gflagChk(0x14) != 0) {
        scpPlayPosSet(D_00639EA8, -30.0f, -436.0f, -1.0f);
        _ACTWait(0x3C);
        scpPlayStart(D_00639EA8);
    } else if (gflagChk(0x12) == 0) {
        ScpCallCameraOff();
        scpPlayPosSet(D_00639EA8, -7.0f, -5725.0f, 18.0f);

        bmg1_mes[0].func = actSt13cBmg1Chk;
        self->mail = bmg1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpPlayPosSet(D_00639EA8, -7.0f, -5725.0f, 18.0f);
    }
}

void actSt13cBmg1Chk(volatile int a0)
{
    AnimSet w;
    int th1;
    int th2;
    unsigned int i;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    ScpCallCameraOn();
    lt_switch_layout(0x37);
    gflagOn(0x12);

    scpAdpcmPlayRequestFunc(0xD, &bmg, 1, 1, 1);

    while (bmg == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    _ACTWait(1);

    th1 = actCreateSubThread(actSt13cConte04, 0x15);
    th2 = actCreateSubThread(actSt13cConte04Jimaku, 0x15);

    D_0063C590 = 0;

    while (D_0063C590 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (D_0063C590 == 0) {
        scpAdpcmFadeCloseFunc(&bmg, 0x100);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri((int *)(th1 + 0x24), 0x22);
        iosThreadSetPri((int *)(th2 + 0x24), 0x22);

        w = conte04Anims;
        for (i = 0; i < 5; i++) {
            stage_SetAnimation(w.anim[i], 1, -1);
            _ACTWait(1);
        }

        jimakuUndisp((int)&jimaku_msg);

        stage_SetAnimation(0x275, 1, -1);
        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri((int *)(th1 + 0x24), 0x22);
        iosThreadSetPri((int *)(th2 + 0x24), 0x22);
    }

    scpPlayMot(D_00639EA4, 0);

    sceVu0SubVector(&w, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, &w);
    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

void actSt13cConte04(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x271, 1, 0);

    scpPlayMot(D_00639EA4, 0x134);
    while (stage_ContinueAnimation(0x271, 0x272) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x135);
    while (stage_ContinueAnimation(0x272, 0x273) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x136);
    while (stage_ContinueAnimation(0x273, 0x274) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x137);
    while (stage_ContinueAnimation(0x274, 0x275) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x138);
    while (stage_CheckAnimationFinish(0x275) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C590 = 1;
    _ACTWait(0);
}

void actSt13cConte04Jimaku(volatile int a0)
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
        case 0x122:
            jimaku_msg.sub.unk2C = 2;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x320:
            jimaku_msg.sub.unk2C = 4;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x42E:
            jimaku_msg.sub.unk2C = 5;
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
    } while (t < 1400.0f);
    _ACTWait(0);
}

void actSt13cCage1stDownDemoCancel(volatile int a0)
{
    float ofs[4];
    float dir[4];
    int *th;

    D_0063C590 = 0;

    th = (int *)(actCreateSubThread(actSt13cCage1stDownDemo, 0x15) + 0x24);

    while (D_0063C590 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th, 0x22);

    if (D_0063C590 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    scpPlayMot(D_00639EA4, 0x13A);
    scpPlayWaitMotEnd(D_00639EA4);

    if (D_0063C590 == 0) {
        scpFadeIn(3.0f);
    }

    while (stage_CheckAnimationFrame(0x49, 0, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);

    memset(ofs, 0, 0x10);
    ofs[3] = 1.0f;
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpPlayEnd(D_00639EA4);

    CameraSetCameraSet(0x25);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

void actSt13cCage1stDown(volatile int a0)
{
    int se;

    lt_switch_layout(0x37);
    gflagOn(0x14);

    scpAdpcmPlayRequestFunc(0xE, &D_0063C000, 1, 1, 1);

    while (D_0063C000 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x48, 1, 0);
    stage_SetAnimation(0x49, 1, 0);

    actCreateSubThread(actSt13cCage1stDownDemoCancel, 0x15);

    scpPlayStart(D_00639EA8);

    while (stage_CheckAnimationFrame(0x48, 0xF, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMotReq(D_00639EA8, 0x11E);

    while (stage_CheckAnimationFrame(0x48, 0x2D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    se = soundSeDefPlay(0x54B, 0, 0, 1);

    while (stage_CheckAnimationFinish(0x48) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    while (stage_CheckAnimationFinish(0x48) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSt13cCageFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x14) == 0) {
        stage_SetAnimation(0x48, -1, -2);

        ((PObjGObj *)scpSearchGobj(0x80))->unk16C = 0;
        SetWeaponTorchChainReactionFlagAll(1);

        cageFallChk_mes[0].func = actSt13cCageFallChk;
        self->mail = cageFallChk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        if (gflagChk(0x16) == 0) {
            ((PObjGObj *)scpSearchGobj(0x80))->unk16C = 0;
            SetWeaponTorchChainReactionFlagAll(1);

            stage_SetAnimation(0x48, 0, -1);
            stage_SetAnimation(0x4C, 0, 0);

            cageFallChk2_mes[0].func = actSt13cCageFallChk;
            self->mail = cageFallChk2_mes;
            ACTSendMailCorrect(a0, 430);
            _ACTWait(0);
        }

        ((PObjGObj *)scpSearchGobj(0x90))->unk16C = 0;

        stage_SetAnimation(0x4C, 0, -1);
        stage_SetAnimation(0x4A, 0, -1);
        stage_SetAnimation(0x4B, 0, -1);
    }
}

void actSt13cCageFallChk(volatile int a0)
{
    AnimSet16 w;
    int th1;
    int th2;
    int th3;
    int cancel;
    unsigned int i;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 160.0f) == 0 || gflagChk(0x14) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x17D);
    CheckPoint();
    gflagOff(0x17D);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gflagOn(0x15);

    while (D_0063C004 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(((AdpcmSlot *)D_0063C004)->unk2C);

    th1 = actCreateSubThread(actSt13cConte05, 0x15);
    th2 = actCreateSubThread(actSt13cConte05Jimaku, 0x15);
    th3 = actCreateSubThread(actSt13cCageFallEffect, 0x15);

    SetWayGroupActive(9, 0);
    _ACTWait(1);

    stage_SetAnimation(0x4A, 1, 0);
    stage_SetAnimation(0x4B, 1, 0);
    stage_SetAnimation(0x4C, 1, 0);

    D_0063C590 = 0;

    while (D_0063C590 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    cancel = D_0063C590 ^ 1;

    if (cancel) {
        scpAdpcmFadeCloseFunc(&D_0063C004, 0x100);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosThreadSetPri((int *)(th1 + 0x24), 0x22);
    iosThreadSetPri((int *)(th2 + 0x24), 0x22);
    iosThreadSetPri((int *)(th3 + 0x24), 0x22);

    if (cancel) {
        w = conte05Anims;
        for (i = 0; i < 16; i++) {
            stage_SetAnimation(w.anim[i], 1, -1);
            _ACTWait(1);
        }

        jimakuUndisp((int)&jimaku_msg);

        ((PObjGObj *)scpSearchGobj(0x80))->unk16C = 1;
        ((PObjGObj *)scpSearchGobj(0x81))->unk16C = 1;
        ((PObjGObj *)scpSearchGobj(0x82))->unk16C = 1;
        ((PObjGObj *)scpSearchGobj(0x36))->unk16C = 1;

        scpTorchLightOn(0x90);
        ResetHandCameraLimitInDemo();
        gflagOn(0x17);
        _ACTWait(0xA);

        Generator_QuickCall(D_0063C594);
        Generator_MaskOff(D_0063C594);

        if (isEnemyActive(scpSearchGobj(0x96)) == 0) {
            memset(&w, 0, 0x10);
            DirectCallEnemy(scpSearchGobj(0x96), D_0063C594, &w, &w, 0);
            iosOmSendMail(scpSearchGobj(0x96), 0x102, scpSearchGobj(0x96));
            _ACTWait(1);
        }

        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayStart(scpSearchGobj(0x96));

        fightSoundProcessRequestStart();

        stage_SetAnimation(0x4A, 0, -1);
        stage_SetAnimation(0x4B, 0, -1);
        stage_SetAnimation(0x4C, 0, -1);
        stage_SetAnimation(0x287, 1, 0);

        scpPlayMot(scpSearchGobj(0x96), 0x3A9);
        SetCameraFlag_LwsCutBack();
        scpPlayEnd(scpSearchGobj(0x96));
        scpWakeupEnemyAll();

        _ACTWait(0xA);

        scpPlayMot(D_00639EA4, 0x143);
        stage_SetAnimation(0x286, 1, 0);
        scpTorchLightOff(0x90);
        scpFadeIn(3.0f);
    } else {
        Generator_MaskOff(D_0063C594);
    }

    scpPlayMot(D_00639EA8, 0x2E0);
    scpPlayStart(scpSearchGobj(0x96));
    scpPlayMot(scpSearchGobj(0x96), 0x3C8);

    while (stage_ContinueAnimation(0x286, 0x287) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x144);
    scpPlayMot(scpSearchGobj(0x96), 0x3A9);

    while (stage_CheckAnimationFinish(0x287) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(scpSearchGobj(0x96));
    scpWakeupEnemyAll();
    ACTEnemyForceSwitchToCarry(scpSearchGobj(0x96));
    scpTorchLightOff(0x90);

    ((PObjGObj *)scpSearchGobj(0x90))->unk16C = 0;

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    ((Act *)((PObjGObj *)scpSearchGobj(0x96))->act)->flags20.ll |= 0x20000;

    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    _ACTWait(0x1E);
    gflagOn(0x19);
    SetWeaponTorchChainReactionFlagAll(0);

    ((Act *)((PObjGObj *)D_00639EA4)->act)->flags &= ~0x100000;
}

void actSt13cConte05(volatile int a0)
{
    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    stage_SetAnimation(0x276, 1, 0);

    scpPlayMot(D_00639EA4, 0x13B);
    scpPlayMot(D_00639EA8, 0x2D6);

    while (stage_ContinueAnimation(0x276, 0x277) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0, 0);
    scpPlayMot(D_00639EA8, 0x2D6);

    while (stage_ContinueAnimation(0x277, 0x278) == 0) {
        _ACTWait(1);
    }

    ResetHandCameraLimitInDemo();
    scpPlayMot(D_00639EA8, 0x2D6);

    while (stage_ContinueAnimation(0x278, 0x279) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2D7);

    while (stage_ContinueAnimation(0x279, 0x27A) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x13C);

    while (stage_ContinueAnimation(0x27A, 0x27B) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x13D);

    while (stage_ContinueAnimation(0x27B, 0x27C) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2D8);
    _ACTWait(1);

    ((PObjGObj *)scpSearchGobj(0x80))->unk16C = 1;
    ((PObjGObj *)scpSearchGobj(0x81))->unk16C = 0;
    ((PObjGObj *)scpSearchGobj(0x82))->unk16C = 0;
    ((PObjGObj *)scpSearchGobj(0x36))->unk16C = 0;

    scpTorchLightOn(0x90);

    while (stage_ContinueAnimation(0x27C, 0x27D) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2D9);

    while (stage_ContinueAnimation(0x27D, 0x27E) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(5, 5);

    ((PObjGObj *)scpSearchGobj(0x36))->unk16C = 1;

    scpPlayMot(D_00639EA4, 0x13E);
    scpPlayMot(D_00639EA8, 0x2DA);

    while (stage_ContinueAnimation(0x27E, 0x27F) == 0) {
        _ACTWait(1);
    }

    ResetHandCameraLimitInDemo();

    scpPlayMot(D_00639EA4, 0x13F);
    scpPlayMot(D_00639EA8, 0x2DB);

    ((PObjGObj *)scpSearchGobj(0x81))->unk16C = 1;
    ((PObjGObj *)scpSearchGobj(0x82))->unk16C = 1;

    _ACTWait(0x12C);
    gflagOn(0x17);

    while (stage_ContinueAnimation(0x27F, 0x280) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(scpSearchGobj(0x96));
    scpPlayMot(scpSearchGobj(0x96), 0x3C4);

    while (stage_ContinueAnimation(0x280, 0x281) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x140);
    scpPlayMot(D_00639EA8, 0x2DC);
    scpPlayMot(scpSearchGobj(0x96), 0x3C4);

    while (stage_ContinueAnimation(0x281, 0x282) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x141);
    scpPlayMot(D_00639EA8, 0x2DD);
    scpPlayMot(scpSearchGobj(0x96), 0x3C5);

    while (stage_ContinueAnimation(0x282, 0x283) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x142);
    scpPlayMot(D_00639EA8, 0x2DE);
    scpPlayMot(scpSearchGobj(0x96), 0x3C6);

    while (stage_ContinueAnimation(0x283, 0x284) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2DF);
    scpPlayMot(scpSearchGobj(0x96), 0x3C7);

    while (stage_ContinueAnimation(0x284, 0x285) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 0x143);

    while (stage_ContinueAnimation(0x285, 0x286) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 0x2E0);
    scpPlayMot(scpSearchGobj(0x96), 0x3C8);

    fightSoundProcessRequestStart();

    D_0063C590 = 1;
    _ACTWait(0);
}

void actSt13cConte05Jimaku(volatile int a0)
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
        case 0x65E:
            jimakuOn = 1;
            jimaku_msg.sub.unk2C = 9;
            jimaku_msg.sub.unk38 = -1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x9BC:
            jimaku_msg.sub.unk2C = 6;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xAC8:
            jimaku_msg.sub.unk2C = 7;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xE80:
            jimaku_msg.sub.unk2C = 8;
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
    } while (t < 4000.0f);
    _ACTWait(0);
}

void actSt13cCageFallEffect(volatile int a0)
{
    EffectArg b1;
    EffectArg b2;
    EffectArg b3;
    EffectArg b4;
    EffectArg b5;
    EffectArg b6;
    EffectArg b7;
    EffectArg b8;
    EffectArg b9;
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0:
            gflagOn(0x16);
            break;
        case 0x40:
            iosPadActRequest(D_00639EAC, 0x11);
            b1 = cageFallEffect1;
            scpEffectStart(&b1, 0);
            b2 = cageFallEffect2;
            scpEffectStart(&b2, 0);
            break;
        case 0x44:
            b3 = cageFallEffect3;
            scpEffectStart(&b3, 0);
            b4 = cageFallEffect4;
            scpEffectStart(&b4, 0);
            break;
        case 0x60:
            b5 = cageFallEffect5;
            scpEffectStart(&b5, 0);
            b6 = cageFallEffect6;
            scpEffectStart(&b6, 0);
            b7 = cageFallEffect7;
            scpEffectStart(&b7, 0);
            break;
        case 0xB4:
            iosPadActRequest(D_00639EAC, 0xF);
            break;
        case 0x12C:
            b8 = cageFallEffect8;
            scpEffectStart(&b8, 0);
            b9 = cageFallEffect9;
            scpEffectStart(&b9, 0);
            break;
        case 0x17C:
            iosPadActRequest(D_00639EAC, 0x10);
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
    } while (t < 400.0f);
    _ACTWait(0);
}

void actSt13cSekizoChk(volatile int a0)
{
    /* the family's SE-handle slot at 4(sp): sound-subsystem owned, and here
       never written before soundSeDefStop reads it back (ROM: lw $4,4($sp)). */
    volatile int se;
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0 || gflagChk(0x1C) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    SetWayGroupActive(2, 1);

    scpAdpcmPlayRequestFunc(0x11, &hand, 1, 1, 1);
    while (hand == 0) {
        _ACTWait(1);
    }

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    stage_SetAnimation(0x4D, 1, 0);

    D_0063C010 = iosPadActRequest(D_00639EAC, 9);
    D_0063C014 = 0x80;
    iosPadActVolumeSet(D_0063C010, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);
    scpPlayPosSet(D_00639EA4, -300.0f, -100.0f, 100.0f);
    scpPlayPosSet(D_00639EA8, -300.0f, -100.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 0x285);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(0x1F);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(0x4D, 0xB4, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(D_0063C010);

    while (stage_CheckAnimationFinish(0x4D) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA8, 0x214);
    scpPlayEnd(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
}

void actSt13cGirlCarryChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(0x19) == 0 || ((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 == 0x6F ||
           ((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 == 0x6E || gflagChk(0x1D) != 0) {
        _ACTWait(1);
    }

    _ACTWait(0xF);

    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x253);
    scpPlayWaitMotEnd(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x254);

    ((MotObj *)((PObjGObj *)D_00639EA8)->unk15C)->unk514 =
        (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f * 30.0f);

    gflagOn(0x1A);

    girlCarryChk_mes[0].func = actSt13cGirlCarryAgainChk;
    self->mail = girlCarryChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);

    _ACTWait(1);
}

void actSt13cHandChk(volatile int a0)
{
    float dir[4];
    int th1;
    int th2;
    int t;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (1) {
        if (scpActStatusDeathFall(D_00639EA4) == 0 &&
            actEnemyFlagCheckDead(scpSearchGobj(0x96)) != 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0x3000000) != 0 && gflagChk(0x1A) != 0 &&
            scpTriggerBall(D_00639EA8, D_00639EA4, 550.0f) != 0 &&
            (((Act *)((PObjGObj *)D_00639EA4)->act)->unk2E4 & 8) != 0 &&
            ((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 != 0x6E) {
            break;
        }
        if (gflagChk(0x1E) != 0) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    ((Act *)((PObjGObj *)scpSearchGobj(0x96))->act)->flags20.ll &= ~0x20000;

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gsb_SetZoom(2.0f, 1000.0f);
    gflagOn(0x1B);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    scpLockMaxRotate(D_00639EA4, 6.0f);
    _SCPMoveByWay_ToChar(D_00639EA4, D_00639EA8, 0, 6, 50.0f, 30.0f);
    scpUnLockMaxRotate(D_00639EA4);

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA4), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    scpAdpcmPlayRequestFunc(0x10, &D_0063C00C, 1, 1, 1);
    while (D_0063C00C == 0) {
        _ACTWait(1);
    }

    ACTGame_ConnectHand();

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0x105);
    scpPlayMot(D_00639EA8, 0x2D1);

    th1 = actCreateSubThread(actSt13cHandJimaku, 0x15);
    th2 = actCreateSubThread(actSt13cHandSub, 0x15);

    D_0063C590 = 0;

    while (D_0063C590 == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th2 + 0x24), 0x22);
    iosThreadSetPri((int *)(th1 + 0x24), 0x22);

    if (D_0063C590 == 0) {
        scpAdpcmFadeCloseFunc(&D_0063C00C, 0x200);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        jimakuUndisp((int)&jimaku_msg);
        scpFadeIn(3.0f);
    }

    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 0x214);

    gsb_SetZoom(1.0f, 1000.0f);
    lt_switch_layout(0x36);

    t = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1];
    _ACTWait(t * 3);

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    ((MotObj *)((PObjGObj *)D_00639EA4)->unk15C)->unk514 =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 30.0f);

    _ACTWait(1);

    iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    fightSoundProcessRequestStart();
    gflagOn(0x1C);
}

void actSt13cHandJimaku(volatile int a0)
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
        case 0x6E:
            jimaku_msg.sub.unk2C = 0xB;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x154:
            jimaku_msg.sub.unk2C = 0xC;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x244:
            jimaku_msg.sub.unk2C = 0xD;
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
    } while (t < 800.0f);
}

void actSt13cSleep(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x13) == 0) {
        sleep_mes[0].func = actSt13cSleepChk;
        self->mail = sleep_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cCageDown(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x14) == 0) {
        stage_SetAnimation(0x48, 0, 0);
        stage_SetAnimation(0x4C, 0, 0);

        cageDown_mes[0].func = actSt13cCageDownMain;
        self->mail = cageDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    if (gflagChk(0x14) != 0) {
        CameraSetCameraSet(0x25);
    }
}

void actSt13cCageFallReady(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x16) == 0) {
        cageFallReady_mes[0].func = actSt13cCageFallReadyChk;
        self->mail = cageFallReady_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cEnemy(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    D_0063C594 = a0;
    Generator_Mask(a0);

    while (gflagChk(0x17) == 0) {
        _ACTWait(1);
    }

    Generator_Call(scpSearchGobj(0x98));
    _ACTWait(0xB4);

    Generator_Call(a0);
    scpSleepEnemyAll();
    gflagOff(0x17);
}

void actSt13cEnemyNull(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x19) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);
}

void actSt13cSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1F) == 0) {
        stage_SetAnimation(0x4D, 0, 0);
        SetWayGroupActive(2, 0);

        sekizo_mes[0].func = actSt13cSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x4D, 0, -1);
        SetWayGroupActive(2, 1);
    }
}

void actSt13cSekizoJimaku(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1F) == 0) {
        sekizoJimaku_mes[0].func = actSt13cSekizoJimakuChk;
        self->mail = sekizoJimaku_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cHand(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1B) == 0) {
        hand_mes[0].func = actSt13cHandChk;
        self->mail = hand_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cGirlCarry(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1B) == 0) {
        girlCarry_mes[0].func = actSt13cGirlCarryChk;
        self->mail = girlCarry_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cRescue(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x1E) == 0 && gflagChk(0x1B) == 0) {
        rescue_mes[0].func = actSt13cRescueChk;
        self->mail = rescue_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cBuki(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    buki_mes[0].func = actSt13cBukiChk;
    self->mail = buki_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actE3St13cSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x1F, 0x4D, 0, 0x11, -300.0f, -100.0f, 100.0f, -300.0f, -100.0f, 0.0f);

    if (gflagChk(0x1F) == 0) {
        SetWayGroupActive(2, 0);
    } else {
        SetWayGroupActive(2, 1);
    }
}

void actSt13cBmg1Event(int x)
{
    volatile int local = x;
}

void actSt13cSleepEvent(int x)
{
    volatile int local = x;
}

void actSt13cSleepChk(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA8, 200.0f) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(D_00639EA8);
    _ACTWait(1);

    ofs[0] = sleepFacePos.d[0];
    ofs[1] = sleepFacePos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    scpPlayMotReq(D_00639EA8, 0x11D);
}

void actSt13cCageDownMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = cageDownMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13cCageDownSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    if (gflagChk(0x14) == 0) {
        cageDownSwitch_mes[0].func = actSt13cCage1stDown;
        sub->mail = cageDownSwitch_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cCage1stDownDemo(volatile int a0)
{
    scpPlayStart(D_00639EA4);
    scpPlayMot(D_00639EA4, 0x139);
    scpPlayWaitMotEnd(D_00639EA4);
    _ACTWait(0xF0);
    D_0063C590 = 1;
    _ACTWait(0);
}

void actSt13cCageFallReadyChk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 || gflagChk(0x14) == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0xF, &D_0063C004, 1, 1, 0);
}

void actSt13cCageFallEvent(int x)
{
    volatile int local = x;
}

void actE3St13cSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt13cSekizoJimakuChk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    while (gflagChk(0x1F) == 0) {
        _ACTWait(1);
    }

    gflagOff(0x186);
    actCreateSubThread(actSt13cSekizoJimakuEff, 0x15);
}

void actSt13cSekizoJimakuEff(volatile int a0)
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
        case 0x2D:
            jimaku_msg.sub.unk2C = 0x13;
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
    } while (t < 500.0f);
}

void actSt13cGirlCarryAgainChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 != 0x6F) {
        _ACTWait(1);
    }

    gflagOff(0x1A);

    girlCarryAgainChk_mes[0].func = actSt13cGirlCarryChk;
    self->mail = girlCarryAgainChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);

    _ACTWait(1);
}

void actSt13cHandSub(volatile int a0)
{
    _ACTWait(100);
    scpPlayWaitMotEnd(D_00639EA4);
    D_0063C590 = 1;
    _ACTWait(0);
}

void actSt13cRescueChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (((Act *)((PObjGObj *)D_00639EA8)->act)->unk34 != 0x6E) {
        _ACTWait(1);
    }

    gflagOn(0x1D);
    D_0063AA08 = 1;
    _ACTWait(0xC8);

    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x254);
    _ACTWait(0x78);

    gflagOn(0x1E);
}

void actSt13cBukiEvent(int x)
{
    volatile int local = x;
}

void actSt13cBukiChk(volatile int a0)
{
    while (ForMotionViewer_GetCurrentMotion(D_00639EA4) != 0xE7) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x4C, -1, -2);
}
