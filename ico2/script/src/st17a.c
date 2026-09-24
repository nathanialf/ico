#include "common.h"
#include "st17a.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act-game.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "act.h"
#include "e3.h"
#include "typedef.h"

static ActMail linkTest_mes[2] = {{430}, {429}};

static ActMail doorInit_mes[2] = {{430}, {429}};

static ActMail doorDown_mes[2] = {{430}, {429}};

static ActMail doorUp_mes[2] = {{430}, {429}};

static ActMail doorUpChk_mes[2] = {{430}, {429}};

/* actSt17aDoorDownChk's record. The name is ours (no map names a file static)
   but not free: gcse.c hashes a SYMBOL_REF by its characters, and the spellings
   doorDownChk_mes and door_down_chk_mes both swap that function's s4/s5 (the
   complete66 audit, re-measured in chain 1 pass 108); door_mes gives the ROM's. */
static ActMail door_mes[2] = {{430}, {429}};

static ActMail hasi_mes[2] = {{430}, {429}};

static ActMail intro_mes[2] = {{430}, {429}};

static ActMail hint1_mes[2] = {{430}, {429}};

static ActMail fall_mes[2] = {{430}, {429}};

static const ConstVec doorChkSePos = {{6646.0f, -2157.0f, 1102.0f, 0.0f}};

static const ConstVec doorUpEffectPos = {{6690.0f, -2000.0f, 1100.0f, 1.0f}};

static const ConstVec doorDownEffectPos = {{6690.0f, -2300.0f, 1100.0f, 1.0f}};

static const ConstVec doorDownEffect2Pos = {{6600.0f, -2000.0f, 1100.0f, 1.0f}};

static const ConstVec hasiChkSePos = {{3587.0f, -2072.0f, 1124.0f, 0.0f}};

extern int *D_00639EA4;
extern void *D_00639EA8;
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, void *a1, float radius);

void actSt17aDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(32) == 0) {
        stage_SetLoopFlag(131, 1);
        stage_SetAnimation(131, 1, 0);

        doorInit_mes[0].func = actSt17aDoorUpChk;
        self->mail = doorInit_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else if (scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 ||
               (D_00639EA8 != 0 && scpTriggerBall(a0, D_00639EA8, 400.0f) != 0)) {
        stage_SetLoopFlag(131, 1);
        stage_SetAnimation(131, 1, 0);

        _ACTWait(60);
        doorDown_mes[0].func = actSt17aDoorDownChk;
        self->mail = doorDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(129, 0, 0);
        doorUp_mes[0].func = actSt17aDoorUpChk;
        self->mail = doorUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of scpTriggerFloorAttrTargetMan do not fit the prototype in script.h */
extern int scpTriggerFloorAttrTargetMan(int a0, int attr);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupItemWithBoundary(float a0, float a1, float a2, float a3);

void actSt17aDoorUpChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(15);

    actCreateSubThread(actSt17aDoorUpEffect, 21);

    scpWakeupItemWithBoundary(6573.0f, -2077.0f, 1089.0f, 100.0f);

    stage_SetAnimation(129, 1, 0);

    buf[0] = doorChkSePos.d[0];
    buf[1] = doorChkSePos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);

    h = soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(60);
    soundSeDefStop(h);

    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(129) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetLoopFlag(131, 1);
    stage_SetAnimation(131, 1, 0);

    doorUpChk_mes[0].func = actSt17aDoorDownChk;
    sub->mail = doorUpChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt17aDoorDownChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;
    long long buf[2];
    int h;

    while (scpTriggerFloorAttrTargetMan(a0, 0x3000000) != 0) {
        _ACTWait(1);
    }

    _ACTWait(15);

    actCreateSubThread(actSt17aDoorDownEffect, 21);

    scpWakeupItemWithBoundary(6573.0f, -2077.0f, 1089.0f, 100.0f);

    stage_SetLoopFlag(131, 0);

    stage_SetAnimation(130, 1, 0);

    buf[0] = doorChkSePos.d[0];
    buf[1] = doorChkSePos.d[1];
    soundSeDefPlay(1220, 0, (float *)buf, 1);
    _ACTWait(30);

    h = soundSeDefPlay(1221, 0, (float *)buf, 1);
    _ACTWait(38);
    soundSeDefStop(h);

    soundSeDefPlay(1222, 0, (float *)buf, 1);

    while (stage_CheckAnimationFinish(130) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    door_mes[0].func = actSt17aDoorUpChk;
    sub->mail = door_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(void *obj, int attr);
/* as script.h declares it; this TU does not include that header */
extern int scpSearchGobj(int a0);
extern int D_0063AA08;
extern void *D_00639EAC;
extern int D_0028F4C0[];
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(void *o);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(void *o, int mot);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(void *o);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(void *o);

void actSt17aHasiChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((*(int *)(*(int *)((char *)D_00639EA8 + 0x164) + 0x34) != 0x6F && D_00639EA8 != 0 &&
             scpTriggerFloorAttr(D_00639EA8, 0x1000000) != 0 &&
             scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0) ||
            (*(int *)(*(int *)((char *)D_00639EA8 + 0x164) + 0x34) != 0x6F && D_00639EA8 != 0 &&
             scpTriggerFloorAttr(D_00639EA8, 0x4000000) != 0 &&
             scpTriggerFloorAttr(D_00639EA4, 0x2000000) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    gflagOn(33);

    iosPadActRequest(D_00639EAC, 0xF);
    SetWayGroupActive(3, 0);

    *(int *)(scpSearchGobj(243) + 0x16C) = 0;
    *(int *)(scpSearchGobj(244) + 0x16C) = 1;

    stage_SetAnimation(133, 1, 0);
    SetCameraFlag_LwsCutBack();

    actCreateSubThread(actSt17aHasiEffect, 21);

    if (ACTGame_FLAG_TETSUNAGI() == 0) {
        long long buf[2];

        scpPlayStart(D_00639EA8);

        stage_SetAnimation(132, 1, 0);

        buf[0] = hasiChkSePos.d[0];
        buf[1] = hasiChkSePos.d[1];
        soundSeDefPlay(1290, 0, (float *)buf, 1);

        scpPlayMot(D_00639EA8, 723);
        scpPlayWaitMotEnd(D_00639EA8);

        scpPlayMot(D_00639EA8, 532);
        GOBJ_SUB(D_00639EA8)->f_514 =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);

        scpPlayEnd(D_00639EA8);

        D_0063AA08 = 0;
    } else {
        long long buf2[2];

        scpPlayStart(D_00639EA4);
        scpPlayStart(D_00639EA8);

        stage_SetAnimation(132, 1, 0);

        buf2[0] = hasiChkSePos.d[0];
        buf2[1] = hasiChkSePos.d[1];
        soundSeDefPlay(1290, 0, (float *)buf2, 1);

        scpPlayMot(D_00639EA4, 262);
        scpPlayMot(D_00639EA8, 722);
        scpPlayWaitMotEnd(D_00639EA4);

        scpPlayEnd(D_00639EA4);
        scpPlayEnd(D_00639EA8);

        scpPlayMot(D_00639EA4, 0);
        scpPlayMot(D_00639EA8, 532);
        GOBJ_SUB(D_00639EA8)->f_514 =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);
    }

    while (stage_CheckAnimationFinish(132) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

/* The seven spawn positions are initialised block locals, as in e3.c's
 * actE3CageFallEffect: their templates are this TU's anonymous .rodata
 * (VMA 0x622FB0..0x623020), and loop.c hoists each template's first
 * doubleword out of the frame loop because the constant cannot change. */
void actSt17aHasiEffect(volatile int a0)
{
    float t;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 0: {
            EffectArg b1 = {{3645.0f, -1966.0f, 1122.0f, 1.0f}};
            scpEffectStart(&b1, 15);
        } break;
        case 15: {
            EffectArg b2 = {{3753.0f, -1936.0f, 1090.0f, 1.0f}};
            scpEffectStart(&b2, 0);
        }
            {
                EffectArg b3 = {{3605.0f, -1866.0f, 1150.0f, 1.0f}};
                scpEffectStart(&b3, 15);
            }
            break;
        case 60: {
            EffectArg b4 = {{3759.0f, -1666.0f, 1152.0f, 1.0f}};
            scpEffectStart(&b4, 15);
        }
            {
                EffectArg b5 = {{3305.0f, -1566.0f, 1082.0f, 1.0f}};
                scpEffectStart(&b5, 0);
            }
            break;
        case 120: {
            EffectArg b6 = {{3545.0f, -1466.0f, 1120.0f, 1.0f}};
            scpEffectStart(&b6, 0);
        }
            {
                EffectArg b7 = {{3655.0f, -1066.0f, 1477.0f, 1.0f}};
                scpEffectStart(&b7, 0);
            }
            break;
        }
        n = (int)t;
        t += (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if (n != (int)t) {
            _ACTWait(1);
        } else {
            t += 1.0f;
        }
    } while (t < 1000.0f);
}

extern PadState D_0028F8F0[];
/* as script.h declares it; this TU does not include that header */
extern int scpAdpcmPlayRequestNum(void);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* as script.h declares it; this TU does not include that header */
extern int scpFadeChk(void);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeIn(float f);

/* .sbss, owned by st17a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for. */
static int demoEnd;

/* a0 is the actor entry parameter: its stack home is the actor-thread frame
   slot the scheduler reads, so it is volatile like every other stage actor. */
void actSt17aIntroCancel(volatile int a0)
{
    demoEnd = 0;

    while (lt_fade_status() != 2) {
        _ACTWait(1);
    }

    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(83, 1, -1);
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }

    lt_switch_layout(54);
    D_0063AA08 = 0;
}

void actLinkTest(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    linkTest_mes[0].func = actLinkTestChk;
    self->mail = linkTest_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt17aSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x20, 0x52, 0x82, 0x12, 6450.0f, -2100.0f, 1000.0f, 6450.0f, -2100.0f, 1100.0f);
}

void actSt17aHasi(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(33) == 0) {
        *(int *)(scpSearchGobj(244) + 0x16C) = 0;
        stage_SetAnimation(132, 0, 0);
        SetWayGroupActive(3, 1);
        hasi_mes[0].func = actSt17aHasiChk;
        self->mail = hasi_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        *(int *)(scpSearchGobj(243) + 0x16C) = 0;
        stage_SetAnimation(132, 0, -1);
    }
}

void actSt17aIntro(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(34) == 0) {
        intro_mes[0].func = actSt17aIntroChk;
        self->mail = intro_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt17aHint1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(35) == 0) {
        hint1_mes[0].func = actSt17aHint1Chk;
        self->mail = hint1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(0);
    }
}

void actSt17aFall(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(33) == 0) {
        fall_mes[0].func = actSt17aFallChk;
        self->mail = fall_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt17aSekizoEvent(int x)
{
    volatile int local = x;
}

/* kept local: this TU's uses of scpGetWallCollision do not fit the prototype in script.h */
extern void scpGetWallCollision(float a0, float a1, float a2, float a3, float a4, float a5);

void actLinkTestChk(volatile int a0)
{
    *(int *)(D_00639EA4[0x57] + 0x4E8) = 1;
    *(int *)(D_00639EA4[0x57] + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(60);
}

void actSt17aDoorEvent(int x)
{
    volatile int local = x;
}

/* kept local: this TU's uses of scpEffectStart do not fit the prototype in script.h */
extern void scpEffectStart(int *buf, int a1);

void actSt17aDoorUpEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorUpEffectPos.d[0];
    long long v0b = doorDownEffectPos.d[0];
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
            b2[1] = doorDownEffectPos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt17aDoorDownEffect(volatile int a0)
{
    long long b1[2];
    long long b2[2];
    long long v0a = doorDownEffectPos.d[0];
    long long v0b = doorDownEffect2Pos.d[0];
    int i;
    for (i = 0; i < 50; i++) {
        switch (i) {
        case 0:
            b1[0] = v0a;
            b1[1] = doorDownEffectPos.d[1];
            scpEffectStart((int *)b1, 0);
            break;
        case 0x1E:
            b2[0] = v0b;
            b2[1] = doorDownEffect2Pos.d[1];
            scpEffectStart((int *)b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt17aHasiEvent(int x)
{
    volatile int local = x;
}

extern int cam;
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);

void actSt17aIntroChk(volatile int a0)
{
    lt_switch_layout(55);
    D_0063AA08 = 1;
    gflagOn(34);
    scpAdpcmPlayRequestFunc(53, &cam, 1, 1, 1);
    _ACTWait(1);
    stage_SetAnimation(83, 1, 0);
    SetCameraFlag_LwsCutBack();
    actCreateSubThread(actSt17aIntroCancel, 21);

    while (stage_CheckAnimationFinish(83) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
}

/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern void _SCPMoveCharactorByWay(void *a0, int a1, int *buf, int a3, float f);

void actSt17aGirlWay(volatile int a0)
{
    EffectArg buf = {{1547.0f, -2070.0f, 1495.0f, 0.0f}};

    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)&buf, 2, 100.0f);
}

void actSt17aHint1Chk(volatile int a0)
{
    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("HINT1_FINISH!!!!!!!!!!!!!!!\n");

    gflagOn(35);
    FinishHint(0);
}

void actSt17aFallChk(volatile int a0)
{
    while (!(gflagChk(33) && scpTriggerBall(a0, D_00639EA4, 1800.0f))) {
        _ACTWait(1);
    }

    debug_StdPrintfDummy("FAAAAALL!\n");

    iosOmSendMail(D_00639EA4, 0xE2, D_00639EA4);
}
