#include "common.h"
#include "st01b.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "way_llf.h"
#include "chain.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "typedef.h"

/* This stage's actor mail records. Word 0 of each entry is the mail id the
   entry answers (430 = the actor's own wake-up post, 429 = the trailing
   entry); the handler in .func is installed at run time just before the
   record is posted. Each record is named for the actor thread that owns
   and posts it. */
static ActMail ene_mes[2] = {{430}, {429}};

static ActMail floor_mes[2] = {{430}, {429}};

static ActMail way_mes[2] = {{430}, {429}};

static ActMail way_on_mes[2] = {{430}, {429}};

static ActMail way_off_mes[2] = {{430}, {429}};

void actSt01bInit(void)
{
    if (gflagChk(70) == 0) {
        SetWayGroupActive(2, 0);
        stage_SetAnimation(183, 0, 0);
        return stage_SetAnimation(180, 0, 0);
    }
    SetWayGroupActive(2, 1);
    stage_SetAnimation(183, 0, -1);
    stage_SetAnimation(180, 0, -1);
    return FinishHint(9);
}

extern int D_00639EA4;
extern int D_00639EA8;
extern int D_0063AA08;
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int gobj, int attr);
/* as script.h declares it; this TU does not include that header */
extern void scpSleepEnemyOne(int id);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupEnemyOne(int id);

void actSt01bEneChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (gflagChk(70) == 0 || scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0 ||
           (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 &&
            scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0)) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyOne(3757);
    _ACTWait(30);
    gflagOn(68);
    gflagOn(69);
    stage_SetAnimation(182, 1, 0);
    while (stage_CheckAnimationFrame(182, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    while (stage_CheckAnimationFinish(182) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_switch_layout(54);
    D_0063AA08 = 0;
    scpWakeupEnemyOne(3757);
}

typedef struct {
    char pad00[0x2C];
    int f2C;
} FloorRec;

extern FloorRec *st01b_floor;
extern unsigned int st01b_yure;
extern unsigned char st01b_yure_vol;

/* .sbss, owned by st01b.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthread the wait loop below spins for, and the handle of the looping
   sound effect the demo starts. */
static int demoEnd;

static int seHandle;

extern int D_00639EAC;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec floorChkSubPos = {{-101.0f, -381.0f, -398.0f, 0.0f}};

void actSt01bFloorChkSub(volatile int a0)
{
    long long pos[2];

    while (st01b_floor == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(st01b_floor->f2C);
    stage_SetAnimation(180, 1, 0);
    stage_SetAnimation(181, 1, 0);
    pos[0] = floorChkSubPos.d[0];
    pos[1] = floorChkSubPos.d[1];
    seHandle = soundSeDefPlay(1325, 0, pos, 1);
    _ACTWait(90);
    soundSeDefStop(seHandle);
    seHandle = -1;
    soundSeDefPlay(1288, 0, 0, 1);
    stage_SetAnimation(183, 1, 0);
    st01b_yure = iosPadActRequest(D_00639EAC, 9);
    st01b_yure_vol = 0x80;
    iosPadActVolumeSet(st01b_yure, 0x80);
    while (stage_CheckAnimationFrame(183, 180, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

extern int D_0028F8F4[];
/* as script.h declares it; this TU does not include that header */
extern int scpIsHangChainOptional(int gobj, int id);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int gobj, float x, float y, float z);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern int scpAdpcmFadeCloseFunc(void *h, int fade);
/* as script.h declares it; this TU does not include that header */
extern int scpAdpcmPlayRequestNum(void);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* as script.h declares it; this TU does not include that header */
extern void scpFadeIn(float t);
/* as script.h declares it; this TU does not include that header */
extern int scpFadeChk(void);
/* as script.h declares it; this TU does not include that header */
extern void scpSleepEnemyAll(void);
/* as script.h declares it; this TU does not include that header */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern void *scpSearchGobj(int id);

void actSt01bFloorChk(volatile int a0)
{
    int th;
    int notdone;

    while (scpIsHangChainOptional(D_00639EA4, 0x325) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSleepEnemyAll();
    gflagOn(70);
    FinishHint(9);
    SetWayGroupActive(2, 1);
    if (D_00639EA8 != 0) {
        scpPlayPosSet(D_00639EA8, -200.0f, 900.0f, -200.0f);
    }
    scpAdpcmPlayRequestFunc(81, &st01b_floor, 1, 1, 0);
    th = actCreateSubThread(actSt01bFloorChkSub, 21);
    seHandle = -1;
    st01b_yure = 0xFFFFFFFF;
    demoEnd = 0;
    st01b_floor = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    notdone = demoEnd ^ 1;
    if (notdone) {
        while (st01b_floor == 0) {
            _ACTWait(1);
        }
        scpAdpcmFadeCloseFunc(&st01b_floor, 0x100);
        scpFadeOut(16.0f, 0, 0, 0);
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosThreadSetPri(th + 0x24, 34);

    if (notdone) {
        stage_SetAnimation(181, 1, -1);
        stage_SetAnimation(180, 1, -1);
        stage_SetAnimation(183, 0, 0xB4);
        if (seHandle >= 0) {
            soundSeDefStop(seHandle);
            soundSeDefPlay(1288, 0, 0, 1);
        }
        _ACTWait(1);
        ChainPositionReset(scpSearchGobj(805));
        _ACTWait(1);
        scpFadeIn(3.0f);
    }

    iosPadActStop(st01b_yure);
    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

void actSt01bSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x41, 0xB2, 0, 0x12, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
}

void actSt01bEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(68) == 0) {
        ene_mes[0].func = actSt01bEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt01bEnemy1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(69) == 0) {
        _ACTWait(1);
    }

    _ACTWait(116);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt01bEnemy2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(69) == 0) {
        _ACTWait(1);
    }

    _ACTWait(100);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt01bEnemy3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(69) == 0) {
        _ACTWait(1);
    }

    _ACTWait(130);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt01bEnemy4(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(69) == 0) {
        _ACTWait(1);
    }

    _ACTWait(115);
    Generator_Call(a0);
}

void actSt01bEnemy5(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(69) == 0) {
        _ACTWait(1);
    }

    _ACTWait(125);
    Generator_Call(a0);
}

void actSt01bEnemy6(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);

    while (gflagChk(69) == 0) {
        _ACTWait(1);
    }

    _ACTWait(110);
    Generator_Call(a0);
}

void actSt01bFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(70) == 0) {
        floor_mes[0].func = actSt01bFloorChk;
        self->mail = floor_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt01bWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    way_mes[0].func = actSt01bWayOnChk;
    self->mail = way_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt01bEnd(void) {}

void actSt01bSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt01bFloorEvent(int x)
{
    volatile int local = x;
}

/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);

void actSt01bWayOnChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 || gflagChk(70) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 1);

    way_on_mes[0].func = actSt01bWayOffChk;
    sub->mail = way_on_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt01bWayOffChk(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0 || gflagChk(70) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(4, 0);

    way_off_mes[0].func = actSt01bWayOnChk;
    sub->mail = way_off_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
