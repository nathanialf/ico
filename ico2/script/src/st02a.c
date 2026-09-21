#include "common.h"
#include "st02a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "box.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "particleLayout.h"
#include "pool.h"
#include "typedef.h"

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);

void actSt02aInit(void)
{
    if (gflagChk(118) == 0) {
        SetWayGroupActive(26, 0);
        stage_SetAnimation(99, 0, 0);
    } else {
        stage_SetAnimation(99, 0, -1);
    }
}

/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
extern char *D_00639EA4;
extern int D_00639EA8;
extern ActMail D_004F8050[];
extern ActMail D_004F8070[];

void actSt02aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);
    if (scpTriggerBall(a0, (int)D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(98, 0, 0);
        _ACTWait(60);
        D_004F8050[0].func = actSt02aDoorDownChk;
        self->mail = D_004F8050;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(97, 0, 0);
        D_004F8070[0].func = actSt02aDoorUpChk;
        self->mail = D_004F8070;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern long long D_00622710[];
extern ActMail D_004F8090[];
/* kept local: this TU's uses of scpTriggerFloorAttrTargetMan do not fit the prototype in script.h */
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
/* kept local: this TU's uses of scpWakeupItemWithBoundary do not fit the prototype in script.h */
extern void scpWakeupItemWithBoundary(float x, float y, float z, float r);

void actSt02aDoorUpChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;
    long long pos[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorUpEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(97, 1, 0);
    pos[0] = D_00622710[0];
    pos[1] = D_00622710[1];
    soundSeDefPlay(1220, 0, pos, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos, 1);
    while (stage_CheckAnimationFinish(97) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004F8090[0].func = actSt02aDoorDownChk;
    sub->mail = D_004F8090;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern ActMail D_004F80B0[];

void actSt02aDoorDownChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;
    long long pos[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorDownEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(98, 1, 0);
    pos[0] = D_00622710[0];
    pos[1] = D_00622710[1];
    soundSeDefPlay(1220, 0, pos, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1221, 0, pos, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1222, 0, pos, 1);
    while (stage_CheckAnimationFinish(98) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004F80B0[0].func = actSt02aDoorUpChk;
    sub->mail = D_004F80B0;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int D_0028F8F4[];
extern int D_0063AA08;
extern int st02a_fence;

/* .sbss, owned by st02a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern int scpAdpcmFadeCloseFunc(int *h, int fade);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float t);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);

void actSt02aFenceOpen(volatile int a0)
{
    int th;

    scpSleepEnemyAll();
    gflagOn(118);
    scpAdpcmPlayRequestFunc(96, &st02a_fence, 1, 1, 1);
    th = actCreateSubThread(actSt02aFenceOpenSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (st02a_fence == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&st02a_fence, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(99, 0, -1);
        stage_SetAnimation(100, 0, -1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    SetWayGroupActive(26, 1);
    D_0063AA08 = 0;
    lt_switch_layout(54);
    scpWakeupEnemyAll();
}

extern long long D_00622740[];
/* kept local: this TU's uses of scpEffectStart do not fit the prototype in script.h */
extern void scpEffectStart(void *buf, int kind);
/* kept local: this TU's uses of scpTriggerPosBall do not fit the prototype in script.h */
extern int scpTriggerPosBall(void *a, void *b, float f);

void actSt02WaterFallBoySplashCheck(volatile int a0)
{
    long long buf[4];
    long long buf2[2];
    int idx;
    if (D_00639EA4 == 0)
        return;
    buf[0] = D_00622740[0];
    buf[1] = D_00622740[1];
    buf[2] = D_00622740[2];
    buf[3] = D_00622740[3];
    for (;;) {
        idx = GetSkeltonFocusNode(D_00639EA4, 0x23);
        CopyVector(buf2, (float *)(GOBJ_SUB(D_00639EA4)->f_C + (idx << 6) + 0x30));
        if (scpTriggerPosBall(&buf[0], buf2, 100.0f))
            scpEffectStart(buf2, 0x2F);
        _ACTWait(10);
        idx = GetSkeltonFocusNode(D_00639EA4, 0x23);
        CopyVector(buf2, (float *)(GOBJ_SUB(D_00639EA4)->f_C + (idx << 6) + 0x30));
        if (scpTriggerPosBall(&buf[2], buf2, 100.0f))
            scpEffectStart(buf2, 0x2F);
        _ACTWait(10);
    }
}

/* The waterfall's two reflection meshes and the two layout quads they are
 * stretched over, read straight out of .rodata by the %hi/%lo pairs the ROM
 * carries; `const` is what keeps the four copies in the ROM's order. */
extern const PoolMesh D_00622760;
extern const PoolMesh D_00622780;
extern const PoolMeshQuad D_006227A0;
extern const PoolMeshQuad D_006227E0;

void actSt02aWaterFallReflactionEffect(volatile int a0)
{
    PoolMesh m0 = D_00622760;
    PoolMesh m1 = D_00622780;
    PoolMeshQuad q0 = D_006227A0;
    PoolMeshQuad q1 = D_006227E0;

    InitLayoutedPoolReflactionMesh((char *)&m0, (char *)&q0);
    InitLayoutedPoolReflactionMesh((char *)&m1, (char *)&q1);
    for (;;) {
        SetLayoutedPoolReflactionMesh((char *)&m0);
        DispLimitedPoolReflactionMesh((int *)&m0);
        SetLayoutedPoolReflactionMesh((char *)&m1);
        DispLimitedPoolReflactionMesh((int *)&m1);
        _ACTWait(1);
    }
}

/* kept local: this TU's uses of scpTransGObj do not fit the prototype in script.h */
extern void scpTransGObj(void *a0, float x, float y, float z);

void actSt02aWaterFallChk(volatile int a0)
{
    Act *act = ((PObjGObj *)D_00639EA4)->act;

    *(long long *)((char *)act + 0x20) &= ~0x80000000000LL;
    scpSearchGobj(1713)->f16C = 1;
    scpSearchGobj(1670)->f16C = 0;
    scpSearchGobj(1687)->f16C = 0;
    scpSearchGobj(1688)->f16C = 0;
    scpSearchGobj(1691)->f16C = 0;
    DeleteParticleLayout(scpSearchGobj(1722));
    DeleteParticleLayout(scpSearchGobj(1723));
    DeleteParticleLayout(scpSearchGobj(1724));
    DeleteParticleLayout(scpSearchGobj(1725));
    stage_SetAnimation(391, -1, -2);
    scpTransGObj(scpSearchGobj(1705), 0.0f, -200.0f, 0.0f);
    scpTransGObj(scpSearchGobj(1707), 0.0f, -200.0f, 0.0f);
    _ACTWait(5);
    ReInitBoxGeo(scpSearchGobj(1705));
    ReInitBoxGeo(scpSearchGobj(1707));
}

extern int gondola;
extern int D_00639EAC;
extern ActMail D_004F81D0[];
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmCloseFunc(int *a0);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);

void actSt02aGondolaUp(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    scpAdpcmPlayRequestFunc(87, &gondola, 1, 1, 1);

    while (gondola == 0) {
        _ACTWait(1);
    }

    _ACTWait(16);
    stage_SetAnimation(101, 1, 0);
    gflagOn(119);

    while (stage_CheckAnimationFrame(101, 140, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(101, 149, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(120);

    if (gondola != 0) {
        scpAdpcmCloseFunc(&gondola);
    }

    lt_switch_layout(54);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();

    D_004F81D0[0].func = actSt02aGondolaMain;
    sub->mail = D_004F81D0;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int gondola_test;
extern ActMail D_004F81F0[];

void actSt02aGondolaDown(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    scpAdpcmPlayRequestFunc(87, &gondola_test, 1, 1, 1);

    while (gondola_test == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(101, 1, 0x96);
    gflagOff(119);

    while (stage_CheckAnimationFrame(101, 295, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(101, 300, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    _ACTWait(120);

    if (gondola_test != 0) {
        scpAdpcmCloseFunc(&gondola_test);
    }

    lt_switch_layout(54);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();

    D_004F81F0[0].func = actSt02aGondolaMain;
    sub->mail = D_004F81F0;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt02aBox(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    if (gflagChk(109) != 0) {
        scpSearchGobj(1705)->f16C = 0;
        if (gflagChk(106) != 0) {
            scpSearchGobj(1705)->f16C = 0;
            scpSearchGobj(1706)->f16C = 0;
        } else {
            scpSearchGobj(1707)->f16C = 0;
        }
    }
    if (gflagChk(108) != 0) {
        scpSearchGobj(1706)->f16C = 0;
        scpSearchGobj(1707)->f16C = 0;
    }
    if (gflagChk(108) == 0 && gflagChk(109) == 0) {
        scpSearchGobj(1705)->f16C = 0;
        scpSearchGobj(1706)->f16C = 0;
        scpSearchGobj(1707)->f16C = 0;
    }
}

extern ActMail D_004F8170[];

void actSt02aGondola(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(119) != 0) {
        stage_SetAnimation(101, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(101, 0, 0x95);
    } else {
        stage_SetAnimation(101, 0, 0x12C);
    }

    D_004F8170[0].func = actSt02aGondolaMain;
    self->mail = D_004F8170;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern ActMail D_004F80F0[];

void actSt02aFence(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(118) == 0) {
        D_004F80F0[0].func = actSt02aFenceMain;
        self->mail = D_004F80F0;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern ActMail D_004F8130[];

void actSt02aWaterFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(106) != 0) {
        D_004F8130[0].func = actSt02aWaterFallChk;
        self->mail = D_004F8130;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    scpSearchGobj(1713)->f16C = 0;

    actCreateSubThread(actSt02WaterFallBoySplashCheck, 21);
    actCreateSubThread(actSt02aWaterFallReflactionEffect, 21);
}

void actSt02aBoxEvent2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(110) == 0) {
        scpSearchGobj(1709)->f16C = 0;
    }
}

extern ActMail D_004F8210[];

void actSt02aEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(121) == 0) {
        D_004F8210[0].func = actSt02aEneChk;
        self->mail = D_004F8210;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt02aEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(122) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

void actSt02aEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);
    Generator_Mask((int)scpSearchGobj(1703));

    while (gflagChk(122) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_Call((int)scpSearchGobj(1703));
}

/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt02aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x7B, 0x66, 0, 0x12, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
}

extern ActMail D_004F8230[];
extern ActMail D_004F8250[];

void actSt02aWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(124) == 0) {
        D_004F8230[0].func = actSt02aWayOffChk;
        self->mail = D_004F8230;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        D_004F8250[0].func = actSt02aWayOnChk;
        self->mail = D_004F8250;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern ActMail D_004F82B0[];

void actSt02aTakiWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(106) != 0) {
        D_004F82B0[0].func = actSt02aTakiWayOnChk;
        self->mail = D_004F82B0;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern ActMail D_004F8310[];

void actSt02aSecretItem(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(114) == 0) {
        D_004F8310[0].func = actSt02aSecretItemChk;
        self->mail = D_004F8310;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt02aDoorEvent(int x)
{
    volatile int local = x;
}

extern long long D_00622720[];
extern long long D_00622730[];

void actSt02aDoorUpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622720[0];
    long long v0b = D_00622730[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622720[1];
            scpEffectStart(b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622730[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt02aDoorDownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = D_00622730[0];
    long long v0b = D_00622720[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = D_00622730[1];
            scpEffectStart(b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = D_00622720[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

extern ActMail D_004F80D0[];

void actSt02aFenceMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F80D0;
    while (1) {
        _ACTWait(1);
    }
}

extern ActMail D_004F8110[];

void actSt02aFenceSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(55);
    D_0063AA08 = 1;

    D_004F8110[0].func = actSt02aFenceOpen;
    sub->mail = D_004F8110;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt02aFenceOpenSub(volatile int a0)
{
    while (st02a_fence == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(99, 1, 0);
    stage_SetAnimation(100, 1, 0);
    while (stage_CheckAnimationFinish(100) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

extern ActMail D_004F8150[];
extern ActMail D_004F8190[];
extern ActMail D_004F81B0[];

void actSt02aGondolaMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = D_004F8150;
    while (1) {
        _ACTWait(1);
    }
}

void actSt02aGondolaSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(119) != 0) {
        D_004F8190[0].func = actSt02aGondolaDown;
        sub->mail = D_004F8190;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    D_004F81B0[0].func = actSt02aGondolaUp;
    sub->mail = D_004F81B0;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt02aEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(121);
    gflagOn(122);
}

void actSt02aSekizoEvent(int x)
{
    volatile int local = x;
}

/* kept local: this TU's uses of scpCheckExistAliveEnemy do not fit the prototype in script.h */
extern int scpCheckExistAliveEnemy(void);

/* The way-on watcher's mail record: it installs actSt02aWayOffChk here and
   posts it. Word 0 of each entry is the mail id the entry answers (430 the
   actor post, 429 the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
static ActMail way_on_mail[2] = {{430}, {429}};

void actSt02aWayOnChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(D_00639EA8, 0x4000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(53, 1);
    SetWayGroupActive(55, 1);
    SetWayGroupActive(56, 1);
    SetWayGroupActive(57, 1);
    gflagOff(124);

    way_on_mail[0].func = actSt02aWayOffChk;
    sub->mail = way_on_mail;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern ActMail D_004F8290[];

void actSt02aWayOffChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(D_00639EA8, 0x3000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(53, 0);
    SetWayGroupActive(55, 0);
    SetWayGroupActive(56, 0);
    SetWayGroupActive(57, 0);
    gflagOn(124);

    D_004F8290[0].func = actSt02aWayOnChk;
    sub->mail = D_004F8290;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* The waterfall way-on watcher's own mail record (installs
   actSt02aTakiWayOffChk). */
static ActMail taki_on_mail[2] = {{430}, {429}};

void actSt02aTakiWayOnChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(D_00639EA8, 0x6000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(35, 1);
    SetWayGroupActive(59, 1);

    taki_on_mail[0].func = actSt02aTakiWayOffChk;
    sub->mail = taki_on_mail;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* The waterfall way-off watcher's own mail record (installs
   actSt02aTakiWayOnChk). */
static ActMail taki_off_mail[2] = {{430}, {429}};

void actSt02aTakiWayOffChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(D_00639EA8, 0x5000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(35, 0);
    SetWayGroupActive(59, 0);

    taki_off_mail[0].func = actSt02aTakiWayOnChk;
    sub->mail = taki_off_mail;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpExplodeSecretItem do not fit the prototype in script.h */
extern void scpExplodeSecretItem(void);

void actSt02aSecretItemChk(volatile int a0)
{
    while (scpSearchGobj(1770) == 0) {
        _ACTWait(1);
    }
    _ACTWait(60);

    scpExplodeSecretItem();
}
