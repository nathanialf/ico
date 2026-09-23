#include "common.h"
#include "st08b.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "cage.h"
#include "geometryManager.h"
#include "item.h"
#include "typedef.h"

static ActMail kurenMain_mes[2] = {{406, actSt08bKurenSwitch}, {429}};

static ActMail kuren_mes[2] = {{430}, {429}};

static ActMail kurenSwitch_mes[2] = {{430}, {429}};

static ActMail doorDownchk_mes[2] = {{430}, {429}};

static ActMail doorUpchk_mes[2] = {{430}, {429}};

static ActMail doorUpChk_mes[2] = {{430}, {429}};

static ActMail door_down_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

extern int D_00639EA8;
extern int D_0063AA08;
/* as script.h declares it; this TU does not include that header */
extern void scpPlayEnd(int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int a0);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec kurenSwitchPos = {{248.0f, -2626.0f, 705.0f, 1.0f}};

static const ConstVec kurenSwitch2Pos = {{280.0f, -3748.0f, 2416.0f, 1.0f}};

static const ConstVec doorUpChkPos = {{-1319.0f, -2429.0f, -405.0f, 0.0f}};

static const ConstVec doorUpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}};

static const ConstVec doorUpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}};

/* kept local: this TU's uses of scpEffectStart do not fit the prototype in script.h */
extern void scpEffectStart(int *buf, int a1);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int a1, float radius);
/* kept local: this TU's uses of scpTriggerFloorAttrTargetMan do not fit the prototype in script.h */
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);
/* as script.h declares it; this TU does not include that header */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *h, int a1);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* as script.h declares it; this TU does not include that header */
extern int scpFadeChk(void);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeIn(float a0);

typedef union Pos {
    long long ll[2];
    float f[4];
} Pos;

extern PadState D_0028F8F0[];
void actSt08bKurenLeft(volatile int a0);
void actSt08bKurenRight(volatile int a0);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);
extern int D_00639EA4;
/* The door-boundary X/Z corners live in the -G8 gp float pool and are written
   by the stage's layout/script side, so their loads may not sink into the jal
   delay slot; ROM has a nop at both call sites. */
void actSt08bDoorUpChk(volatile int a0);
void actSt08bDoorDownChk(volatile int a0);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
extern int D_00639EAC;

/* .sbss, owned by st08b.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthreads the wait loop below spins for. */
static int demoEnd;

inline void actSt08bKuren(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    kuren_mes[0].func = actSt08bKurenMain;
    self->mail = kuren_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt08bKurenMain(volatile int a0)
{
    int sub = *(int *)(a0 + 0x164);

    D_0063AA08 = 0;
    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }
    *(int *)(sub + 0xD0) = (int)kurenMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt08bKurenSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    Pos p1;
    Pos p2;
    int h;
    int th = 0;
    int thread;
    int frame;

    D_0063AA08 = 1;
    sub->mainMail = 0;

    if (D_00639EA8 != 0) {
        if (scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
            th = actCreateSubThread(actSt08aGirlYoro, 21);
        }
    }

    lt_switch_layout(55);

    if (gflagChk(80) != 0) {
        scpAdpcmPlayRequestFunc(58, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenRight, 21);
        frame = 0x3FC;
    } else {
        scpAdpcmPlayRequestFunc(57, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenLeft, 21);
        frame = 0x1FE;
    }

    _ACTWait(3);

    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(thread + 0x24, 34);
    if (th != 0) {
        iosThreadSetPri(th + 0x24, 34);
    }

    if (demoEnd == 0) {
        scpAdpcmFadeCloseFunc(&h, 0x80);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(370, 1, frame - 0x3C);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(365));
        HotInitCageGeo(scpSearchGobj(364));
        _ACTWait(1);
        if (th != 0) {
            scpPlayMot(D_00639EA8, 532);
            if (gflagChk(80) != 0) {
                p1.ll[0] = kurenSwitchPos.d[0];
                p1.ll[1] = kurenSwitchPos.d[1];
                SetDirectRootPosition(D_00639EA8, &p1);
            } else {
                p2.ll[0] = kurenSwitch2Pos.d[0];
                p2.ll[1] = kurenSwitch2Pos.d[1];
                p2.f[1] += *(float *)(*(int *)((int)GOBJ_SUB(D_00639EA8) + 0x8C) + 0x14);
                SetDirectRootPosition(D_00639EA8, &p2);
            }
        }
        scpFadeIn(3.0f);
    }

    if (D_00639EA8 != 0) {
        GetRootPosition(&p1, D_00639EA8);
        *(float *)((int)GOBJ_SUB(D_00639EA8) + 0x254) = p1.f[1];
    }

    while (stage_CheckAnimationFrame(370, frame, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(54);

    if (gflagChk(80) != 0) {
        scpSearchGobj(365)->f16C = 1;
        scpSearchGobj(364)->f16C = 0;
        _ACTWait(1);
        gflagOff(80);
    } else {
        gflagOn(80);
    }

    kurenSwitch_mes[0].func = actSt08bKurenMain;
    sub->mail = kurenSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08bKurenLeft(volatile int a0)
{
    ReviveAllCarryableItemsWithNonSleepFrame(300);

    stage_SetAnimation(370, 1, 0);

    scpSearchGobj(365)->f16C = 0;
    scpSearchGobj(364)->f16C = 1;

    while (stage_CheckAnimationFrame(370, 5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(370, 215, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(370, 465, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt08bKurenRight(volatile int a0)
{
    ReviveAllCarryableItemsWithNonSleepFrame(300);

    stage_SetAnimation(370, 1, 0x1FF);

    while (stage_CheckAnimationFrame(370, 732, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(370, 822, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(370, 995, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    demoEnd = 1;
    _ACTWait(0);
}

inline void actSt08aGirlYoro(volatile int a0)
{
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 546);
    scpPlayWaitMotEnd(D_00639EA8);
    scpPlayMot(D_00639EA8, 595);
    scpPlayWaitMotEnd(D_00639EA8);
    _ACTWait(0);
}

inline void actSt08bDoorEvent(int x)
{
    volatile int local = x;
}

void actSt08bDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
        (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetAnimation(372, 0, 0);
        _ACTWait(60);
        doorDownchk_mes[0].func = actSt08bDoorDownChk;
        self->mail = doorDownchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(371, 0, 0);
        doorUpchk_mes[0].func = actSt08bDoorUpChk;
        self->mail = doorUpchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt08bDoorUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt08bDoorUpEffect, 21);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(371, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(371) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    doorUpChk_mes[0].func = actSt08bDoorDownChk;
    sub->mail = doorUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt08bDoorUpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorUpEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = doorUpEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

inline void actSt08bDoorDownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffect2Pos.d[0];
    long long v0b = doorUpEffectPos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorUpEffect2Pos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = doorUpEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

/* TU-owned mail record: role-named file static per the 2026-09-07 ruling,
   same shape as st17a's door_mes / st18a's switch_l_mes. */

void actSt08bDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];

    while (scpTriggerFloorAttrTargetMan(a0, 0x4000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);

    actCreateSubThread(actSt08bDoorDownEffect, 21);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(372, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(30);
    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(372) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_down_mes[0].func = actSt08bDoorUpChk;
    sub->mail = door_down_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

inline void actSt08bEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(81) == 0) {
        ene_mes[0].func = actSt08bEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

inline void actSt08bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(81);
    gflagOn(82);
}

inline void actSt08bEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(82) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}

inline void actSt08bEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(82) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
}
