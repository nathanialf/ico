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
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
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
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *h, int a1);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float a0);

typedef union Pos {
    long long ll[2];
    float f[4];
} Pos;

extern PadState D_0028F8F0[];
void actSt08bKurenLeft(volatile int a0);
void actSt08bKurenRight(volatile int a0);
/* kept local: this TU's uses of scpWakeupItemWithBoundary do not fit the prototype in script.h */
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
extern int D_0063C56C;

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
            th = actCreateSubThread(actSt08aGirlYoro, 0x15);
        }
    }

    lt_switch_layout(0x37);

    if (gflagChk(0x50) != 0) {
        scpAdpcmPlayRequestFunc(0x3A, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenRight, 0x15);
        frame = 0x3FC;
    } else {
        scpAdpcmPlayRequestFunc(0x39, &h, 1, 1, 1);
        while (h == 0) {
            _ACTWait(1);
        }
        thread = actCreateSubThread(actSt08bKurenLeft, 0x15);
        frame = 0x1FE;
    }

    _ACTWait(3);

    D_0063C56C = 0;
    while (D_0063C56C == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(thread + 0x24, 0x22);
    if (th != 0) {
        iosThreadSetPri(th + 0x24, 0x22);
    }

    if (D_0063C56C == 0) {
        scpAdpcmFadeCloseFunc(&h, 0x80);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(0x172, 1, frame - 0x3C);
        _ACTWait(1);
        HotInitCageGeo(scpSearchGobj(0x16D));
        HotInitCageGeo(scpSearchGobj(0x16C));
        _ACTWait(1);
        if (th != 0) {
            scpPlayMot(D_00639EA8, 0x214);
            if (gflagChk(0x50) != 0) {
                p1.ll[0] = kurenSwitchPos.d[0];
                p1.ll[1] = kurenSwitchPos.d[1];
                SetDirectRootPosition(D_00639EA8, &p1);
            } else {
                p2.ll[0] = kurenSwitch2Pos.d[0];
                p2.ll[1] = kurenSwitch2Pos.d[1];
                p2.f[1] += *(float *)(*(int *)(*(int *)(D_00639EA8 + 0x15C) + 0x8C) + 0x14);
                SetDirectRootPosition(D_00639EA8, &p2);
            }
        }
        scpFadeIn(3.0f);
    }

    if (D_00639EA8 != 0) {
        GetRootPosition(&p1, D_00639EA8);
        *(float *)(*(int *)(D_00639EA8 + 0x15C) + 0x254) = p1.f[1];
    }

    while (stage_CheckAnimationFrame(0x172, frame, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    lt_switch_layout(0x36);

    if (gflagChk(0x50) != 0) {
        scpSearchGobj(0x16D)->f16C = 1;
        scpSearchGobj(0x16C)->f16C = 0;
        _ACTWait(1);
        gflagOff(0x50);
    } else {
        gflagOn(0x50);
    }

    kurenSwitch_mes[0].func = actSt08bKurenMain;
    sub->mail = kurenSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt08bKurenLeft(volatile int a0)
{
    ReviveAllCarryableItemsWithNonSleepFrame(0x12C);

    stage_SetAnimation(0x172, 1, 0);

    scpSearchGobj(0x16D)->f16C = 0;
    scpSearchGobj(0x16C)->f16C = 1;

    while (stage_CheckAnimationFrame(0x172, 0x5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(0x172, 0xD7, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x172, 0x1D1, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    D_0063C56C = 1;
    _ACTWait(0);
}

void actSt08bKurenRight(volatile int a0)
{
    ReviveAllCarryableItemsWithNonSleepFrame(0x12C);

    stage_SetAnimation(0x172, 1, 0x1FF);

    while (stage_CheckAnimationFrame(0x172, 0x2DC, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x172, 0x336, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x172, 0x3E3, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    D_0063C56C = 1;
    _ACTWait(0);
}

inline void actSt08aGirlYoro(volatile int a0)
{
    scpPlayStart(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x222);
    scpPlayWaitMotEnd(D_00639EA8);
    scpPlayMot(D_00639EA8, 0x253);
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
        stage_SetAnimation(0x174, 0, 0);
        _ACTWait(0x3C);
        doorDownchk_mes[0].func = actSt08bDoorDownChk;
        self->mail = doorDownchk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x173, 0, 0);
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
    _ACTWait(0xF);

    actCreateSubThread(actSt08bDoorUpEffect, 0x15);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(0x173, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x173) == 0) {
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
    for (i = 0; i < 0x32; i++) {
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
    for (i = 0; i < 0x32; i++) {
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
    _ACTWait(0xF);

    actCreateSubThread(actSt08bDoorDownEffect, 0x15);

    scpWakeupItemWithBoundary(-1189.0f, -2326.0f, -408.0f, 100.0f);

    stage_SetAnimation(0x174, 1, 0);

    buf[0] = doorUpChkPos.d[0];
    buf[1] = doorUpChkPos.d[1];
    soundSeDefPlay(0x4C4, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C5, 0, (float *)buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlay(0x4C6, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(0x174) == 0) {
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

    if (gflagChk(0x51) == 0) {
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
    gflagOn(0x51);
    gflagOn(0x52);
}

inline void actSt08bEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x52) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

inline void actSt08bEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x52) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}
