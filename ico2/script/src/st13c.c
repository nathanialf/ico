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
#include "script.h"
#include "GsBase.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "weapon.h"
#include <libvu0.h>
#include <string.h>
#include "e3.h"
#include "typedef.h"

/* scpEffectStart's argument block: a 16-byte spawn position, copied as a
   pair of doublewords and written as four floats. */

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

/* kept local: this TU's bytes only come out with its own view of PObjGObjSt13c. */
/* kept local: this TU's bytes only come out with its own view of PObjGObj, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PObjGObjSt13c {
    char pad00[0x15C]; /* 0x000 */
    int unk15C;        /* 0x15C */
    int unk160;        /* 0x160 */
    int act;           /* 0x164 (Act * handle) */
    int unk168;        /* 0x168 */
    int unk16C;        /* 0x16C */
} PObjGObjSt13c;

/* kept local: this TU's uses of jimakuBegin do not fit the prototype in jimaku.h */
extern void jimakuBegin(int a0);
/* kept local: this TU's uses of jimakuUndisp do not fit the prototype in jimaku.h */
extern void jimakuUndisp(int a0);
/* kept local: this TU's uses of jimakuJump do not fit the prototype in jimaku.h */
extern void jimakuJump(int a0);
extern int D_00639EA4;

/* .sbss, owned by st13c.o and reached only from this file (MAIN.MAP names no
   symbol in the run), in the ROM's run order: the flag each demo raises when
   it is over, and the generator the boss fight calls through. */
static int demoEnd;

static int bossGenerator;

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

static ActMail cageFall_mes[2] = {{430}, {429}};

static ActMail cageFall2_mes[2] = {{430}, {429}};

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
extern int D_00639EA8;

void actSt13cInit(void)
{
    if (gflagChk(21)) {
        SetWayGroupActive(9, 0);
    }
}

void actSt13cEnd(void)
{
    if (gflagChk(31) == 0) {
        debug_StdPrintfDummy("BackStageOff\n");
        gflagOn(390);
    }
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */
/* kept local: this TU's bytes only come out with its own view of ConstVecSt13c. */
typedef union {
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) ConstVecSt13c;

/* The animations actSt13cConte04 steps through. */
static const AnimSet conte04Anims = {{625, 626, 627, 628, 629}};

/* Where actSt13cSleepChk turns the sleeping girl to face. */
static const ConstVecSt13c sleepFacePos = {{-800.0f, 0.0f, -1000.0f, 1.0f}};

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
    if (gflagChk(21) != 0) {
        return;
    }

    ((Act *)((PObjGObjSt13c *)D_00639EA4)->act)->flags |= 0x100000;

    if (gflagChk(20) != 0) {
        scpPlayPosSet(D_00639EA8, -30.0f, -436.0f, -1.0f);
        _ACTWait(60);
        scpPlayStart(D_00639EA8);
    } else if (gflagChk(18) == 0) {
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
    lt_switch_layout(55);
    gflagOn(18);

    scpAdpcmPlayRequestFunc(13, &bmg, 1, 1, 1);

    while (bmg == 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 1;
    _ACTWait(1);

    th1 = actCreateSubThread(actSt13cConte04, 21);
    th2 = actCreateSubThread(actSt13cConte04Jimaku, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        scpAdpcmFadeCloseFunc(&bmg, 0x100);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        iosThreadSetPri((int *)(th1 + 0x24), 34);
        iosThreadSetPri((int *)(th2 + 0x24), 34);

        w = conte04Anims;
        for (i = 0; i < 5; i++) {
            stage_SetAnimation(w.anim[i], 1, -1);
            _ACTWait(1);
        }

        jimakuUndisp((int)&jimaku_msg);

        stage_SetAnimation(629, 1, -1);
        scpFadeIn(3.0f);
    } else {
        iosThreadSetPri((int *)(th1 + 0x24), 34);
        iosThreadSetPri((int *)(th2 + 0x24), 34);
    }

    scpPlayMot(D_00639EA4, 0);

    sceVu0SubVector(&w, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, &w);
    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt13cConte04(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(625, 1, 0);

    scpPlayMot(D_00639EA4, 308);
    while (stage_ContinueAnimation(625, 626) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 309);
    while (stage_ContinueAnimation(626, 627) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 310);
    while (stage_ContinueAnimation(627, 628) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 311);
    while (stage_ContinueAnimation(628, 629) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 312);
    while (stage_CheckAnimationFinish(629) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
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

    demoEnd = 0;

    th = (int *)(actCreateSubThread(actSt13cCage1stDownDemo, 21) + 0x24);

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    scpPlayMot(D_00639EA4, 314);
    scpPlayWaitMotEnd(D_00639EA4);

    if (demoEnd == 0) {
        scpFadeIn(3.0f);
    }

    while (stage_CheckAnimationFrame(73, 0, 1) == 0) {
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
    lt_switch_layout(54);
}

void actSt13cCage1stDown(volatile int a0)
{
    int se;

    lt_switch_layout(55);
    gflagOn(20);

    scpAdpcmPlayRequestFunc(14, &D_0063C000, 1, 1, 1);

    while (D_0063C000 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(72, 1, 0);
    stage_SetAnimation(73, 1, 0);

    actCreateSubThread(actSt13cCage1stDownDemoCancel, 21);

    scpPlayStart(D_00639EA8);

    while (stage_CheckAnimationFrame(72, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMotReq(D_00639EA8, 0x11E);

    while (stage_CheckAnimationFrame(72, 45, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    se = soundSeDefPlay(1355, 0, 0, 1);

    while (stage_CheckAnimationFinish(72) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefStop(se);

    while (stage_CheckAnimationFinish(72) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSt13cCageFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(20) == 0) {
        stage_SetAnimation(72, -1, -2);

        ((PObjGObjSt13c *)scpSearchGobj(128))->unk16C = 0;
        SetWeaponTorchChainReactionFlagAll(1);

        cageFall_mes[0].func = actSt13cCageFallChk;
        self->mail = cageFall_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        if (gflagChk(22) == 0) {
            ((PObjGObjSt13c *)scpSearchGobj(128))->unk16C = 0;
            SetWeaponTorchChainReactionFlagAll(1);

            stage_SetAnimation(72, 0, -1);
            stage_SetAnimation(76, 0, 0);

            cageFall2_mes[0].func = actSt13cCageFallChk;
            self->mail = cageFall2_mes;
            ACTSendMailCorrect(a0, 430);
            _ACTWait(0);
        }

        ((PObjGObjSt13c *)scpSearchGobj(144))->unk16C = 0;

        stage_SetAnimation(76, 0, -1);
        stage_SetAnimation(74, 0, -1);
        stage_SetAnimation(75, 0, -1);
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

    while (scpTriggerBall(a0, D_00639EA4, 160.0f) == 0 || gflagChk(20) == 0) {
        _ACTWait(1);
    }

    gflagOn(381);
    CheckPoint();
    gflagOff(381);

    lt_switch_layout(55);
    D_0063AA08 = 1;

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gflagOn(21);

    while (D_0063C004 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(((AdpcmSlot *)D_0063C004)->unk2C);

    th1 = actCreateSubThread(actSt13cConte05, 21);
    th2 = actCreateSubThread(actSt13cConte05Jimaku, 21);
    th3 = actCreateSubThread(actSt13cCageFallEffect, 21);

    SetWayGroupActive(9, 0);
    _ACTWait(1);

    stage_SetAnimation(74, 1, 0);
    stage_SetAnimation(75, 1, 0);
    stage_SetAnimation(76, 1, 0);

    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    cancel = demoEnd ^ 1;

    if (cancel) {
        scpAdpcmFadeCloseFunc(&D_0063C004, 0x100);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosThreadSetPri((int *)(th1 + 0x24), 34);
    iosThreadSetPri((int *)(th2 + 0x24), 34);
    iosThreadSetPri((int *)(th3 + 0x24), 34);

    if (cancel) {
        w = conte05Anims;
        for (i = 0; i < 16; i++) {
            stage_SetAnimation(w.anim[i], 1, -1);
            _ACTWait(1);
        }

        jimakuUndisp((int)&jimaku_msg);

        ((PObjGObjSt13c *)scpSearchGobj(128))->unk16C = 1;
        ((PObjGObjSt13c *)scpSearchGobj(129))->unk16C = 1;
        ((PObjGObjSt13c *)scpSearchGobj(130))->unk16C = 1;
        ((PObjGObjSt13c *)scpSearchGobj(54))->unk16C = 1;

        scpTorchLightOn(144);
        ResetHandCameraLimitInDemo();
        gflagOn(23);
        _ACTWait(10);

        Generator_QuickCall(bossGenerator);
        Generator_MaskOff(bossGenerator);

        if (isEnemyActive(scpSearchGobj(150)) == 0) {
            memset(&w, 0, 0x10);
            DirectCallEnemy(scpSearchGobj(150), bossGenerator, &w, &w, 0);
            iosOmSendMail(scpSearchGobj(150), 0x102, scpSearchGobj(150));
            _ACTWait(1);
        }

        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);
        scpPlayStart(scpSearchGobj(150));

        fightSoundProcessRequestStart();

        stage_SetAnimation(74, 0, -1);
        stage_SetAnimation(75, 0, -1);
        stage_SetAnimation(76, 0, -1);
        stage_SetAnimation(647, 1, 0);

        scpPlayMot(scpSearchGobj(150), 937);
        SetCameraFlag_LwsCutBack();
        scpPlayEnd(scpSearchGobj(150));
        scpWakeupEnemyAll();

        _ACTWait(10);

        scpPlayMot(D_00639EA4, 323);
        stage_SetAnimation(646, 1, 0);
        scpTorchLightOff(144);
        scpFadeIn(3.0f);
    } else {
        Generator_MaskOff(bossGenerator);
    }

    scpPlayMot(D_00639EA8, 736);
    scpPlayStart(scpSearchGobj(150));
    scpPlayMot(scpSearchGobj(150), 968);

    while (stage_ContinueAnimation(646, 647) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 324);
    scpPlayMot(scpSearchGobj(150), 937);

    while (stage_CheckAnimationFinish(647) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(scpSearchGobj(150));
    scpWakeupEnemyAll();
    ACTEnemyForceSwitchToCarry(scpSearchGobj(150));
    scpTorchLightOff(144);

    ((PObjGObjSt13c *)scpSearchGobj(144))->unk16C = 0;

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    ((Act *)((PObjGObjSt13c *)scpSearchGobj(150))->act)->flags20.ll |= 0x20000;

    D_0063AA08 = 0;
    lt_switch_layout(54);

    _ACTWait(30);
    gflagOn(25);
    SetWeaponTorchChainReactionFlagAll(0);

    ((Act *)((PObjGObjSt13c *)D_00639EA4)->act)->flags &= ~0x100000;
}

void actSt13cConte05(volatile int a0)
{
    lt_switch_layout(55);
    D_0063AA08 = 1;

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    stage_SetAnimation(630, 1, 0);

    scpPlayMot(D_00639EA4, 315);
    scpPlayMot(D_00639EA8, 726);

    while (stage_ContinueAnimation(630, 631) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0, 0);
    scpPlayMot(D_00639EA8, 726);

    while (stage_ContinueAnimation(631, 632) == 0) {
        _ACTWait(1);
    }

    ResetHandCameraLimitInDemo();
    scpPlayMot(D_00639EA8, 726);

    while (stage_ContinueAnimation(632, 633) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 727);

    while (stage_ContinueAnimation(633, 634) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 316);

    while (stage_ContinueAnimation(634, 635) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 317);

    while (stage_ContinueAnimation(635, 636) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 728);
    _ACTWait(1);

    ((PObjGObjSt13c *)scpSearchGobj(128))->unk16C = 1;
    ((PObjGObjSt13c *)scpSearchGobj(129))->unk16C = 0;
    ((PObjGObjSt13c *)scpSearchGobj(130))->unk16C = 0;
    ((PObjGObjSt13c *)scpSearchGobj(54))->unk16C = 0;

    scpTorchLightOn(144);

    while (stage_ContinueAnimation(636, 637) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 729);

    while (stage_ContinueAnimation(637, 638) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(5, 5);

    ((PObjGObjSt13c *)scpSearchGobj(54))->unk16C = 1;

    scpPlayMot(D_00639EA4, 318);
    scpPlayMot(D_00639EA8, 730);

    while (stage_ContinueAnimation(638, 639) == 0) {
        _ACTWait(1);
    }

    ResetHandCameraLimitInDemo();

    scpPlayMot(D_00639EA4, 319);
    scpPlayMot(D_00639EA8, 731);

    ((PObjGObjSt13c *)scpSearchGobj(129))->unk16C = 1;
    ((PObjGObjSt13c *)scpSearchGobj(130))->unk16C = 1;

    _ACTWait(300);
    gflagOn(23);

    while (stage_ContinueAnimation(639, 640) == 0) {
        _ACTWait(1);
    }

    scpPlayStart(scpSearchGobj(150));
    scpPlayMot(scpSearchGobj(150), 964);

    while (stage_ContinueAnimation(640, 641) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 320);
    scpPlayMot(D_00639EA8, 732);
    scpPlayMot(scpSearchGobj(150), 964);

    while (stage_ContinueAnimation(641, 642) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 321);
    scpPlayMot(D_00639EA8, 733);
    scpPlayMot(scpSearchGobj(150), 965);

    while (stage_ContinueAnimation(642, 643) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 322);
    scpPlayMot(D_00639EA8, 734);
    scpPlayMot(scpSearchGobj(150), 966);

    while (stage_ContinueAnimation(643, 644) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 735);
    scpPlayMot(scpSearchGobj(150), 967);

    while (stage_ContinueAnimation(644, 645) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 323);

    while (stage_ContinueAnimation(645, 646) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 736);
    scpPlayMot(scpSearchGobj(150), 968);

    fightSoundProcessRequestStart();

    demoEnd = 1;
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
            gflagOn(22);
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
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0 || gflagChk(28) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    SetWayGroupActive(2, 1);

    scpAdpcmPlayRequestFunc(17, &hand, 1, 1, 1);
    while (hand == 0) {
        _ACTWait(1);
    }

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    stage_SetAnimation(77, 1, 0);

    D_0063C010 = iosPadActRequest(D_00639EAC, 9);
    D_0063C014 = 0x80;
    iosPadActVolumeSet(D_0063C010, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayMot(D_00639EA8, 532);
    scpPlayPosSet(D_00639EA4, -300.0f, -100.0f, 100.0f);
    scpPlayPosSet(D_00639EA8, -300.0f, -100.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpSekizouCheckPoint();

    scpPlayMot(D_00639EA8, 645);
    scpPlayWaitMotEnd(D_00639EA8);

    gflagOn(31);

    soundSeDefStop(se);

    while (stage_CheckAnimationFrame(77, 180, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(D_0063C010);

    while (stage_CheckAnimationFinish(77) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA8, 532);
    scpPlayEnd(D_00639EA8);
    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt13cGirlCarryChk(volatile int a0)
{
    Act *self = (Act *)((PObjGObjSt13c *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(25) == 0 || ((Act *)((PObjGObjSt13c *)D_00639EA8)->act)->unk34 == 0x6F ||
           ((Act *)((PObjGObjSt13c *)D_00639EA8)->act)->unk34 == 0x6E || gflagChk(29) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);

    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 595);
    scpPlayWaitMotEnd(D_00639EA8);
    scpPlayMot(D_00639EA8, 596);

    ((MotObj *)((PObjGObjSt13c *)D_00639EA8)->unk15C)->unk514 =
        (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) / 60.0f * 30.0f);

    gflagOn(26);

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
            actEnemyFlagCheckDead(scpSearchGobj(150)) != 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA4, 0x3000000) != 0 && gflagChk(26) != 0 &&
            scpTriggerBall(D_00639EA8, D_00639EA4, 550.0f) != 0 &&
            (((Act *)((PObjGObjSt13c *)D_00639EA4)->act)->unk2E4 & 8) != 0 &&
            ((Act *)((PObjGObjSt13c *)D_00639EA8)->act)->unk34 != 0x6E) {
            break;
        }
        if (gflagChk(30) != 0) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    ((Act *)((PObjGObjSt13c *)scpSearchGobj(150))->act)->flags20.ll &= ~0x20000;

    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gsb_SetZoom(2.0f, 1000.0f);
    gflagOn(27);
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

    scpAdpcmPlayRequestFunc(16, &D_0063C00C, 1, 1, 1);
    while (D_0063C00C == 0) {
        _ACTWait(1);
    }

    ACTGame_ConnectHand();

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA4, 261);
    scpPlayMot(D_00639EA8, 721);

    th1 = actCreateSubThread(actSt13cHandJimaku, 21);
    th2 = actCreateSubThread(actSt13cHandSub, 21);

    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)(th2 + 0x24), 34);
    iosThreadSetPri((int *)(th1 + 0x24), 34);

    if (demoEnd == 0) {
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
    scpPlayMot(D_00639EA8, 532);

    gsb_SetZoom(1.0f, 1000.0f);
    lt_switch_layout(54);

    t = (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1];
    _ACTWait(t * 3);

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    ((MotObj *)((PObjGObjSt13c *)D_00639EA4)->unk15C)->unk514 =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 30.0f);

    _ACTWait(1);

    iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    fightSoundProcessRequestStart();
    gflagOn(28);
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

    if (gflagChk(19) == 0) {
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

    if (gflagChk(20) == 0) {
        stage_SetAnimation(72, 0, 0);
        stage_SetAnimation(76, 0, 0);

        cageDown_mes[0].func = actSt13cCageDownMain;
        self->mail = cageDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    if (gflagChk(20) != 0) {
        CameraSetCameraSet(0x25);
    }
}

void actSt13cCageFallReady(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(22) == 0) {
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

    bossGenerator = a0;
    Generator_Mask(a0);

    while (gflagChk(23) == 0) {
        _ACTWait(1);
    }

    Generator_Call(scpSearchGobj(152));
    _ACTWait(180);

    Generator_Call(a0);
    scpSleepEnemyAll();
    gflagOff(23);
}

void actSt13cEnemyNull(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(25) == 0) {
        _ACTWait(1);
    }

    Generator_MaskOff(a0);
}

void actSt13cSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(31) == 0) {
        stage_SetAnimation(77, 0, 0);
        SetWayGroupActive(2, 0);

        sekizo_mes[0].func = actSt13cSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(77, 0, -1);
        SetWayGroupActive(2, 1);
    }
}

void actSt13cSekizoJimaku(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(31) == 0) {
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

    if (gflagChk(27) == 0) {
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

    if (gflagChk(27) == 0) {
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

    if (gflagChk(30) == 0 && gflagChk(27) == 0) {
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

void actE3St13cSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x1F, 0x4D, 0, 0x11, -300.0f, -100.0f, 100.0f, -300.0f, -100.0f, 0.0f);

    if (gflagChk(31) == 0) {
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
    Act *sub = (Act *)((PObjGObjSt13c *)a0)->act;

    sub->mainMail = cageDownMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13cCageDownSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObjSt13c *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    if (gflagChk(20) == 0) {
        cageDownSwitch_mes[0].func = actSt13cCage1stDown;
        sub->mail = cageDownSwitch_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13cCage1stDownDemo(volatile int a0)
{
    scpPlayStart(D_00639EA4);
    scpPlayMot(D_00639EA4, 313);
    scpPlayWaitMotEnd(D_00639EA4);
    _ACTWait(240);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13cCageFallReadyChk(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 || gflagChk(20) == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(15, &D_0063C004, 1, 1, 0);
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

    while (gflagChk(31) == 0) {
        _ACTWait(1);
    }

    gflagOff(390);
    actCreateSubThread(actSt13cSekizoJimakuEff, 21);
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
    Act *self = (Act *)((PObjGObjSt13c *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (((Act *)((PObjGObjSt13c *)D_00639EA8)->act)->unk34 != 0x6F) {
        _ACTWait(1);
    }

    gflagOff(26);

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
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13cRescueChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (((Act *)((PObjGObjSt13c *)D_00639EA8)->act)->unk34 != 0x6E) {
        _ACTWait(1);
    }

    gflagOn(29);
    D_0063AA08 = 1;
    _ACTWait(200);

    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 596);
    _ACTWait(120);

    gflagOn(30);
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
    stage_SetAnimation(76, -1, -2);
}
