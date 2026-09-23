#include "common.h"
#include "StageManager.h"
#include "debug.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "sceneManager.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "jimaku.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "fightSound.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include "staticBlur.h"
#include "windManager.h"
#include <libvu0.h>
#include <string.h>
#include "act.h"
#include "typedef.h"
#include "commonact.h"
#include "streamMotionManager.h"

extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;
extern int enable_game_pause;
extern int D_0028F4C0[];
/* as script.h declares it; this TU does not include that header */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* as script.h declares it; this TU does not include that header */
extern int scpFadeChk(void);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);

void actE3WarningChk(volatile int a0)
{
    int x = a0;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    stgmgrNextStagePreLoadForceStageSet(0x5F);

    i = 0;
    while (i++ < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 5) {
        _ACTWait(1);
    }

    scpFadeOut(6.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    _ACTWait((int)(float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]));

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 0.0f);
}

/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeIn(float t);

#include "e3.h"

static ActMail title_mes[2] = {{430}, {429}};

static ActMail inst1_mes[2] = {{430}, {429}};

static ActMail capsule_mes[2] = {{430}, {429}};

static ActMail doorMain_mes[2] = {{406, actE3DoorSwitch}, {429}};

static ActMail door_mes[2] = {{430}, {429}};

static ActMail doorSwitch_mes[2] = {{430}, {429}};

static float doorUpPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f};

static ActMail st13cIntro_mes[2] = {{430}, {429}};

static ActMail cageFallReady_mes[2] = {{430}, {429}};

static ActMail cageFall_mes[2] = {{430}, {429}};

static ActMail st01bEne_mes[2] = {{430}, {429}};

static float st09aSekizoPos[4] = {1548.0f, -412.0f, -608.0f, 0.0f};

static ActMail st09aSekizoChk_mes[2] = {{430}, {429}};

static ActMail gate_mes[2] = {{430}, {429}};

static ActMail st09aBrgMain_mes[2] = {{407, actE3St09aBrgSwitch}, {429}};

static ActMail st09aBrg_mes[2] = {{430}, {429}};

static ActMail st09aBrgSwitch_mes[2] = {{430}, {429}};

extern int D_0063B4D0;
extern int D_0063BDF4;

void actE3Title(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    enable_game_pause = 0;
    D_0063AA08 = 1;

    gflagOff(356);

    D_0063BDF4 = 0;
    scpAdpcmPlayRequestFunc(5, &D_0063BDF4, 0, 1, 0);

    while (D_0063B4D0 == 0) {
        _ACTWait(1);
    }

    D_0028F4C0[0xB] = 7;

    scpFadeOut(255.0f, 0, 0, 0);

    while (D_0063BDF4 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    stage_SetAnimation(32, 0, 0);
    stage_SetAnimation(26, 0, -1);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(33, 0, 0);
    stage_SetAnimation(36, 0, 0);
    stage_SetAnimation(38, 0, 0);
    stage_SetAnimation(43, 0, 0);

    title_mes[0].func = actE3TitleChk;
    sub->mail = title_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern PadState D_0028F8F0[];

void actE3TitleChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    actCreateSubThread(actE3TitleFrameChk, 21);

    while (gflagChk(356) != 0 || (D_0028F8F0[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

    gflagOn(357);
    debug_StdPrintfDummy("game_start\n");

    AdpcmPlay(*(int *)(D_0063BDF4 + 0x2C));

    scpFadeOut(4.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 16.0f);
}

extern int NonLinearCameraMove;
/* kept local: this TU's uses of scpAdpcmCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmCloseFunc(int *h);
extern int D_0063B5F0;
extern int mpegPlayReturnStage;

void actE3TitleFrameChk(volatile int a0)
{
    int intro = 0x3AF;
    int loop = 0x3AA;
    int outro = 0x3B4;
    int i;

    stage_SetAnimation(935, 1, 0);

    switch (NonLinearCameraMove) {
    case 3:
        intro = 0x3B0;
        break;
    case 4:
        intro = 0x3B1;
        break;
    case 6:
        intro = 0x3B3;
        break;
    case 5:
        intro = 0x3B2;
        break;
    }
    stage_SetAnimation(intro, 1, 0);

    while (stage_ContinueAnimation(935, 936) == 0) {
        _ACTWait(1);
    }

    stage_SetLoopFlag(936, 1);

    switch (NonLinearCameraMove) {
    case 3:
        loop = 0x3AB;
        break;
    case 4:
        loop = 0x3AC;
        break;
    case 6:
        loop = 0x3AE;
        break;
    case 5:
        loop = 0x3AD;
        break;
    }
    stage_SetLoopFlag(loop, 1);
    stage_SetAnimation(loop, 1, 0);

    i = 0;
    while (i++ < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x2D) {
        _ACTWait(1);
    }

    stage_SetAnimation(937, 1, 0);

    switch (NonLinearCameraMove) {
    case 3:
        outro = 0x3B5;
        break;
    case 4:
        outro = 0x3B6;
        break;
    case 6:
        outro = 0x3B8;
        break;
    case 5:
        outro = 0x3B7;
        break;
    }
    stage_SetAnimation(outro, 1, 0);

    while (stage_CheckAnimationFinish(937) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(357) == 0) {
        debug_StdPrintfDummy("mpeg_start\n");

        gflagOn(356);

        if (D_0063BDF4 != 0) {
            scpAdpcmCloseFunc(&D_0063BDF4);
        }

        mpegPlayReturnStage = 0x5F;
        D_0063B5F0 = 0x5F;

        stgmgrForceSwitchWithFade(0x67, 4.0f, 4.0f);
    }
}

void actE3Inst1Chk(volatile int a0)
{
    int x = a0;
    int anim;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    anim = 0x3C0;
    switch (NonLinearCameraMove) {
    case 3:
        anim = 0x3C1;
        break;
    case 4:
        anim = 0x3C2;
        break;
    case 6:
        anim = 0x3C4;
        break;
    case 5:
        anim = 0x3C3;
        break;
    }

    stage_SetLoopFlag(anim, 1);
    stage_SetAnimation(anim, 1, 0);

    i = 0;
    while (i++ < (0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xA &&
           (D_0028F8F0[0].flags & 0x840) == 0) {
        _ACTWait(1);
    }

    soundSeDefPlay(1390, 0, 0, 1);

    scpFadeOut(3.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 16.0f);
}

/* as script.h declares it; this TU does not include that header */
extern void ScpCallCameraOff(void);

void actE3Capsule(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA8 == 0) {
        ScpCallCameraOff();
    }

    if (gflagChk(358) == 0) {
        if (D_00639EA4 != 0) {
            scpPlayMot(D_00639EA4, 0);
        }

        scpFadeOut(255.0f, 0, 0, 0);

        lt_switch_layout(55);

        stage_SetAnimation(32, 0, 0);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);

        capsule_mes[0].func = actE3CapsuleChk;
        sub->mail = capsule_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
    }
}

/* .sbss, owned by e3.o and reached only from this file (MAIN.MAP names no
   symbol in the run), in the ROM's run order: the capsule demo's sub-thread
   and the flag that thread raises when the demo has finished. */
static int capsuleDemoThread;

static int demoEnd;

extern int e3capsule;

void actE3CapsuleDemoCancel(volatile int a0)
{
    while (demoEnd == 0 || (D_0028F8F0[0].flags & 0x800) == 0) {
        _ACTWait(1);
    }

    iosThreadSetPri(capsuleDemoThread + 0x24, 34);

    scpFadeOut(8.0f, 0, 0, 0);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmCloseFunc(&e3capsule);

    stage_SetAnimation(32, 0, -1);
    stage_SetAnimation(26, 0, -1);
    stage_SetAnimation(594, -1, -2);
    stage_SetAnimation(599, -1, -2);
    stage_SetAnimation(601, -1, -2);
    stage_SetAnimation(602, -1, -2);
    stage_SetAnimation(603, -1, -2);
    stage_SetAnimation(604, -1, -2);
    stage_SetAnimation(605, -1, -2);
    stage_SetAnimation(606, -1, -2);
    stage_SetAnimation(624, 1, 0);

    scpFadeIn(6.0f);

    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

/* as script.h declares it; this TU does not include that header */
extern void scpPlayStart(int a0);

void actE3CapsuleDemo(volatile int a0)
{
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);

    demoEnd = 1;
    actCreateSubThread(actE3CapsuleDemoCancel, 21);

    stage_SetAnimation(594, 1, 0);
    _ACTWait(95);
    stage_SetAnimation(32, 1, 0);

    while (stage_ContinueAnimation(594, 599) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 288);

    while (stage_ContinueAnimation(599, 601) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 288);

    while (stage_ContinueAnimation(601, 602) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 292);

    _ACTWait(1);

    stage_SetAnimation(32, 1, 0xD0);

    while (stage_ContinueAnimation(602, 603) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 293);

    while (stage_ContinueAnimation(603, 604) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 294);

    while (stage_ContinueAnimation(604, 605) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 295);

    while (stage_ContinueAnimation(605, 606) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 296);

    while (stage_ContinueAnimation(606, 624) == 0) {
        _ACTWait(1);
    }

    demoEnd = 0;
    actCreateSubThread(actE3CapsuleDemoEnd, 21);
}

void actE3St13cInit(void)
{
    SetWayGroupActive(7, 0);

    if (gflagChk(360) != 0) {
        SetWayGroupActive(9, 0);
    }
}

/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);

void actE3CageFall(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(360) == 0) {
        stage_SetAnimation(76, 0, 0);
        stage_SetAnimation(72, 0, -1);

        if (D_00639EA8 == 0) {
            _ACTWait(0);
        }

        scpPlayPosSet(D_00639EA8, -30.0f, -436.0f, -1.0f);

        cageFall_mes[0].func = actE3CageFallChk;
        sub->mail = cageFall_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(76, 0, 0);
        stage_SetAnimation(74, 0, -1);
        stage_SetAnimation(75, 0, -1);
    }
}

/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int id);
extern int D_0063BDFC;

void actE3CageFallChk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 160.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;

    ((Act *)scpSearchGobj(3229)->act)->flags20.ll |= 0x20000;
    ((Act *)scpSearchGobj(3230)->act)->flags20.ll |= 0x20000;

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    gflagOn(360);

    while (D_0063BDFC == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(D_0063BDFC + 0x2C));

    actCreateSubThread(actE3CageFallDemo, 21);

    stage_SetAnimation(74, 1, 0);
    stage_SetAnimation(75, 1, 0);

    actCreateSubThread(actE3CageFallEffect, 21);

    while (stage_CheckAnimationFinish(74) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(9, 0);
}

/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* as script.h declares it; this TU does not include that header */
extern void scpPlayEnd(int a0);
extern int stage_no;

void actE3CageFallDemo(volatile int a0)
{
    float dir[4];

    lt_switch_layout(55);

    D_0063AA08 = 1;

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    stage_SetAnimation(630, 1, 0);

    scpPlayMot(D_00639EA4, 315);

    while (stage_ContinueAnimation(630, 631) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0, 0);

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
    scpPlayMot(D_00639EA4, 325);

    while (stage_ContinueAnimation(635, 636) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA8, 728);

    while (stage_ContinueAnimation(636, 637) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA8, 729);

    _ACTWait(240);

    gflagOn(364);

    fightSoundProcessRequestStart();

    while (stage_ContinueAnimation(637, 955) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 323);

    while (stage_ContinueAnimation(955, 956) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA8, 326);

    while (stage_CheckAnimationFrame(956, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 324);

    while (stage_CheckAnimationFinish(956) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    lt_switch_layout(54);

    scpPlayMot(D_00639EA8, 532);
    {
        int self = D_00639EA8;

        GOBJ_SUB(self)->f_514 =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 30.0f);

        scpPlayEnd(self);
    }

    gflagOn(381);

    gamesysObjInfoPosSetStage((int *)D_00639EA4, *(int *)(*(int *)(D_00639EA4 + 0x164) + 0x444), 0,
                              stage_no);

    CheckPoint();

    gflagOff(381);
}

/* no prototype in the dev's TU: the C89 implicit-int return is what makes
   ee-gcc treat $v0 as clobbered at every call site. The definition in
   src/script.c is void. */
/* as script.h declares it; this TU does not include that header */
extern int scpEffectStart(void *a0, int a1);
extern int D_00639EAC;
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);

inline void actE3CapsuleDemoEnd(volatile int a0)
{
    scpPlayMot(D_00639EA4, 307);

    while (stage_CheckAnimationFinish(624) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(D_00639EA4, 0);

    {
        EffectArg ofs = {{-1000.0f, 0.0f, -2200.0f, 1.0f}};
        float dir[4];

        sceVu0SubVector(dir, &ofs, test_CURRENTROOT(D_00639EA4));
        scpPlayMotDir(D_00639EA4, dir);
    }

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    lt_switch_layout(54);

    enable_game_pause = 1;
}

void actE3CageFallEffect(volatile int a0)
{
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
            {
                EffectArg b1 = {{-88.0f, -50.0f, -1.0f, 1.0f}};
                scpEffectStart(&b1, 0);
            }
            {
                EffectArg b2 = {{-96.0f, -45.0f, 34.0f, 1.0f}};
                scpEffectStart(&b2, 0);
            }
            break;
        case 0x44: {
            EffectArg b3 = {{72.0f, -50.0f, 8.0f, 1.0f}};
            scpEffectStart(&b3, 0);
        }
            {
                EffectArg b4 = {{80.0f, -50.0f, 2.0f, 1.0f}};
                scpEffectStart(&b4, 0);
            }
            break;
        case 0x60: {
            EffectArg b5 = {{-27.0f, -50.0f, 100.0f, 1.0f}};
            scpEffectStart(&b5, 0);
        }
            {
                EffectArg b6 = {{-56.0f, -50.0f, 66.0f, 1.0f}};
                scpEffectStart(&b6, 0);
            }
            {
                EffectArg b7 = {{-5.0f, -50.0f, 42.0f, 1.0f}};
                scpEffectStart(&b7, 0);
            }
            break;
        case 0xB4:
            iosPadActRequest(D_00639EAC, 0xF);
            break;
        case 0x12C: {
            EffectArg b8 = {{-10.0f, 0.0f, 466.0f, 1.0f}};
            scpEffectStart(&b8, 0);
        }
            {
                EffectArg b9 = {{-25.0f, 0.0f, 450.0f, 1.0f}};
                scpEffectStart(&b9, 0);
            }
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
}

/* as script.h declares it; this TU does not include that header */
extern void ScpCallCameraSetTarget(float x, float y, float z);

/* e3.o's own .data run (no MAIN.MAP symbol): the sekizou's SE position. */

void actE3St09aSekizo(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    soundSeDefPlay(1346, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1347, 0, st09aSekizoPos, 1);
    soundSeDefPlay(1348, 0, st09aSekizoPos, 1);

    if (gflagChk(366) == 0) {
        stage_SetAnimation(376, 0, 0);

        st09aSekizoChk_mes[0].func = actE3St09aSekizoChk;
        sub->mail = st09aSekizoChk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
        stage_SetAnimation(376, 0, -1);
    }
}

/* as script.h declares it; this TU does not include that header */
extern void scpSekizouCheckPoint(void);
/* as script.h declares it; this TU does not include that header */
extern void scpKillEnemyAll(void);
/* as script.h declares it; this TU does not include that header */
extern void scpMaskGeneratorAll(void);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int a0);
extern int sekizo_e3_vol;
extern unsigned char D_0063BE0C;
/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
/* kept local: this TU's uses of RequestStageChangeDirect do not fit the prototype in script.h */
extern void RequestStageChangeDirect(int a0, int a1, int *buf, int a3);

inline void actE3St09aGirlWay(volatile int a0)
{
    EffectArg buf = {{-1410.0f, -100.0f, 1950.0f, 0.0f}};
    long long way[2];

    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)&buf, 0, 100.0f);

    memset(way, 0, 0x10);
    RequestStageChangeDirect(D_00639EA8, 0x66, (int *)way, 0xB4);

    lt_switch_layout(54);

    D_0063AA08 = 0;
    brainUnlockGirl();
}

void actE3St09aSekizoChk(volatile int a0)
{
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 ||
           scpTriggerBall(a0, D_00639EA8, 200.0f) == 0 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x4B) {
        _ACTWait(1);
    }

    scpSekizouCheckPoint();

    scpAdpcmPlayRequestFunc(18, 0, 1, 1, 1);

    scpKillEnemyAll();
    scpMaskGeneratorAll();

    lt_switch_layout(55);

    D_0063AA08 = 1;
    brainLockGirl();

    gflagOn(366);

    _ACTWait(60);

    stage_SetAnimation(376, 1, 0);

    sekizo_e3_vol = iosPadActRequest(D_00639EAC, 9);
    D_0063BE0C = 0x80;
    iosPadActVolumeSet(sekizo_e3_vol, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpPlayPosSet(D_00639EA8, -1410.0f, -100.0f, 1515.0f);
    scpPlayPosSet(D_00639EA4, -1330.0f, -100.0f, 1515.0f);

    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    D_0063AA08 = 1;

    sceVu0SubVector(dir, test_CURRENTROOT(D_00639EA8), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayMot(D_00639EA8, 645);
    scpPlayWaitMotEnd(D_00639EA8);

    while (stage_CheckAnimationFrame(376, 151, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(sekizo_e3_vol);

    scpPlayMot(D_00639EA8, 532);
    scpPlayEnd(D_00639EA8);

    actCreateSubThread(actE3St09aGirlWay, 21);

    _ACTWait(30);

    scpPlayMot(D_00639EA4, 252);
    scpPlayWaitMotEnd(D_00639EA4);

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);

    ScpCallCameraSetTarget(1421.0f, 97.0f, -1885.0f);
}

extern char D_00618F00[];
extern int e3gate1st;

void actE3GateChk(volatile int a0)
{
    int i;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 3000.0f) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(D_00618F00);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    lt_switch_layout(55);

    SetWindManager(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

    scpPlayStart(D_00639EA8);

    reg_SetScissorSw(1);
    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(4, &e3gate1st, 1, 1, 0);
    while (e3gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(361);
    _ACTWait(1);

    actCreateSubThread(actE3GateDemo, 21);
    actCreateSubThread(actE3GateJimaku, 21);

    stage_SetAnimation(269, 1, 0);
}

/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
extern float D_0063AA0C;

void actE3GateDemo(volatile int a0)
{
    scpSearchGobj(3382)->f16C = 1;

    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion(D_00639EA8);
    EntryStreamMotion((int)scpSearchGobj(3382));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    stage_SetAnimation(648, 1, 0);

    while (stage_CheckAnimationFrame(648, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    AdpcmPlay(*(int *)(e3gate1st + 0x2C));

    while (stage_ContinueAnimation(648, 649) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(649, 650) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(650, 651) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(651, 652) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(652, 653) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(653, 654) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(654, 655) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(655, 656) == 0) {
        _ACTWait(1);
    }

    SetStaticBlur(8);
    SetAuraInspireParam(100.0f);

    stage_SetAnimation(475, 1, 0);

    iosPadActRequest(D_00639EAC, 0xF);

    soundSeDefPlay(1425, 0, 0, 0);

    while (stage_CheckAnimationFrame(656, 45, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (e3gate1st != 0) {
        scpAdpcmFadeCloseFunc(&e3gate1st, 0x50);
    }

    ReinitWindManager();

    lt_switch_layout(54);

    enable_game_pause = 0;

    scpFadeOut(4.0f, 0xFF, 0xFF, 0xFF);
    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (D_0063AA0C > 0.0f) {
        D_0063AA0C -= 0.012f;
        _ACTWait(1);
    }

    mpegPlayReturnStage = 0x5F;

    stgmgrForceSwitchWithFadeColor(0x68, 255.0f, 4.0f, 0, 0, 0);
}

extern JimakuArg jimaku_msg;
extern int jimakuOn;

void actE3GateJimaku(volatile int a0)
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
        case 0x12C:
            jimaku_msg.sub.unk2C = 0x19;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x58C:
            jimaku_msg.sub.unk2C = 0x1A;
            jimaku_msg.sub.unk38 = 0x1E;
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
    } while (t < 7300.0f);
}

void actE3St01bInit(void)
{
    stage_SetAnimation(183, 0, -1);
}

extern int sekizo_e3;

void actE3St09aBrgDown(volatile int a0)
{
    lt_switch_layout(55);
    gflagOn(86);

    scpAdpcmPlayRequestFunc(90, &sekizo_e3, 1, 1, 1);
    while (sekizo_e3 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(378, 1, 0);

    while (stage_CheckAnimationFrame(378, 115, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(378, 165, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFinish(378) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063AA08 = 0;

    lt_switch_layout(54);
}

void actE3Warning(volatile int a0)
{
    int x = a0;
    actInitialize(a0);

    scpFadeOut(255.0f, 0, 0, 0);

    enable_game_pause = 0;

    _ACTWait(1);

    D_0063AA08 = 1;
    InitStageLight(stage_no);

    RequestStageChange(1, D_00639EA4, 0, 255.0f, 0.0f);
}

extern StgPre D_005F5D50[];
extern int D_0055C518[][10];

void actE3Inst1(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);
    StgPre *pre;

    _ACTWait(1);

    D_0063AA08 = 1;
    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    pre = &D_005F5D50[stage_no];
    stgmgrNextStagePreLoadForceStageSet(D_0055C518[pre->ent[0]][9]);

    inst1_mes[0].func = actE3Inst1Chk;
    sub->mail = inst1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actE3Door(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(359) == 0) {
        stage_SetAnimation(953, 0, 0);

        door_mes[0].func = actE3DoorMain;
        sub->mail = door_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(953, 0, -1);
    }
}

void actE3CageFallReady(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(360) == 0) {
        cageFallReady_mes[0].func = actE3CageFallReadyChk;
        sub->mail = cageFallReady_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actE3St13cIntro(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(363) == 0) {
        st13cIntro_mes[0].func = actE3St13cIntroChk;
        sub->mail = st13cIntro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actE3St13cGene1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(364) == 0) {
        _ACTWait(1);
    }
    _ACTWait(400);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3St13cGene2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(364) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(120);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3Floor(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

void actE3St01bEne(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(362) == 0) {
        st01bEne_mes[0].func = actE3St01bEneChk;
        sub->mail = st01bEne_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actE3St01bGene1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(362) == 0) {
        _ACTWait(1);
    }
    _ACTWait(30);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3St01bGene2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(362) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3St01bGene3(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(362) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actE3St09aBrg(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(86) == 0) {
        stage_SetAnimation(378, 0, 0);

        st09aBrg_mes[0].func = actE3St09aBrgMain;
        sub->mail = st09aBrg_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(378, 0, -1);
    }
}

void actE3Gate(volatile int a0)
{
    int x = a0;
    Act *sub = (Act *)actInitialize(a0);

    _ACTWait(1);

    MallocStreamMotionBuffer();

    scpSearchGobj(3382)->f16C = 0;

    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayMot(D_00639EA4, 0);

    scpFadeOut(255.0f, 0, 0, 0);

    stage_SetAnimation(269, 0, 0);
    stage_SetAnimation(272, 0, 0);

    gate_mes[0].func = actE3GateChk;
    sub->mail = gate_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* as script.h declares it; this TU does not include that header */
extern void scpFadeIn(float f);

void actE3CapsuleChk(volatile int a0)
{
    scpSekizouCheckPoint();

    gflagOn(358);

    scpAdpcmPlayRequestFunc(2, &e3capsule, 1, 1, 1);
    while (e3capsule == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    capsuleDemoThread = actCreateSubThread(actE3CapsuleDemo, 21);
}

/* e3.o's own .data run (no MAIN.MAP symbol): actor mail packets. */

inline void actE3DoorMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = doorMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

inline void actE3DoorSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    doorSwitch_mes[0].func = actE3DoorUp;
    sub->mail = doorSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* e3.o's own .data run (no MAIN.MAP symbol): the door's SE position. */

inline void actE3DoorUp(volatile int a0)
{
    lt_switch_layout(55);
    gflagOn(359);

    _ACTWait(60);

    stage_SetAnimation(953, 1, 0);

    soundSeDefPlay(1221, 0, doorUpPos, 1);

    _ACTWait(30);

    soundSeDefPlay(1222, 0, doorUpPos, 1);

    while (stage_CheckAnimationFinish(953) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063AA08 = 0;

    lt_switch_layout(54);
}

inline void actE3St13cIntroChk(volatile int a0)
{
    lt_switch_layout(55);
    gflagOn(363);

    D_0063AA08 = 1;
    _ACTWait(120);

    stage_SetAnimation(954, 1, 0);

    while (stage_CheckAnimationFinish(954) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);

    D_0063AA08 = 0;
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);

inline void actE3CageFallReadyChk(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    D_0063BDFC = 0;
    _ACTWait(1);
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) {
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(3, &D_0063BDFC, 1, 1, 0);
}

inline void actE3St01bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;
    _ACTWait(30);

    gflagOn(362);

    stage_SetAnimation(182, 1, 0);

    while (stage_CheckAnimationFinish(182) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);

    D_0063AA08 = 0;
}

inline void actE3St09aBrgMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    sub->mainMail = st09aBrgMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

inline void actE3St09aBrgSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    st09aBrgSwitch_mes[0].func = actE3St09aBrgDown;
    sub->mail = st09aBrgSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
