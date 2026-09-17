#include "common.h"
#include "st10l.h"
#include "layout_texture.h"
#include "pad.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "girl_act.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "typedef.h"

/* kept local: this TU's bytes only come out with its own view of ActSt10L. */
/* kept local: this TU's bytes only come out with its own view of Act, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct ActSt10L {
    char unk00[0x34];  /* 0x00 */
    int f34;           /* 0x34 */
    char unk38[0x98];  /* 0x38 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} ActSt10L;

/* kept local: this TU's bytes only come out with its own view of PObjGObj, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PObjGObjSt10L {
    char pad00[0x164]; /* 0x000 */
    ActSt10L *act;     /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObjSt10L;

/* the shared pad-state array (op.c's PadState, GsBase.c's GsbPad): 0x58 per
   pad, trg at 0x4. */

extern Pad D_0028F8F0[];
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObjSt10L *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
extern int D_0063A538;
extern int floor10l;
extern int st10l_gondola_up;
extern int st10l_gondola_down;
extern int chain10l;
extern int D_0063AA08;
extern int enable_game_pause;
extern int D_00639EA4;
extern int D_00639EA8;
extern int D_00639EAC;
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int a1, float radius);
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpKillEnemyOne do not fit the prototype in script.h */
extern void scpKillEnemyOne(int a0);
/* kept local: this TU's uses of scpKillSpiderGroup do not fit the prototype in script.h */
extern void scpKillSpiderGroup(int a0);
/* kept local: this TU's uses of scpWakeupEnemyAll do not fit the prototype in script.h */
extern void scpWakeupEnemyAll(void);
/* kept local: this TU's uses of _SCPMoveCharactorByWay do not fit the prototype in script.h */
extern void _SCPMoveCharactorByWay(int a0, int a1, int *buf, int a3, float f);
extern int D_0028F4C0[];
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
/* kept local: this TU's uses of scpAdpcmCloseChkFunc do not fit the prototype in script.h */
extern int scpAdpcmCloseChkFunc(int *handle);
/* kept local: this TU's uses of scpSleepEnemyOne do not fit the prototype in script.h */
extern void scpSleepEnemyOne(int a0);
/* kept local: this TU's uses of scpWakeupEnemyOne do not fit the prototype in script.h */
extern void scpWakeupEnemyOne(int a0);
/* kept local: this TU's uses of scpSleepSpiderGroupOne do not fit the prototype in script.h */
extern void scpSleepSpiderGroupOne(int a0);
/* kept local: this TU's uses of scpWakeupSpiderGroupOne do not fit the prototype in script.h */
extern void scpWakeupSpiderGroupOne(int a0);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float f12, float f13, float f14);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpSekizou do not fit the prototype in script.h */
extern void scpSekizou(int a0, int a1, int a2, int a3, int a4, float x1, float y1, float z1,
                       float x2, float y2, float z2);

/* st10l.o's own .rodata run 0x00622DE0..0x00622DF0 (no MAIN.MAP symbol):
   the girl's way-point packet for actSt10lEneCam3Chk. */
/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec eneCam3ChkPos = {{-33.0f, -72.0f, 470.0f, 0.0f}};

/* st10l.o's own .data run (no MAIN.MAP symbols): actor mail packets. */

static ActMail floorMain_mes[2] = {{406, actSt10lFloorSwitch}, {429}};

static ActMail floor_mes[2] = {{430}, {429}};

static ActMail floorSwitchRight_mes[2] = {{430}, {429}};

static ActMail floorSwitchLeft_mes[2] = {{430}, {429}};

static ActMail floorLeft_mes[2] = {{430}, {429}};

static ActMail floorRight_mes[2] = {{430}, {429}};

static ActMail gondolaMain_mes[2] = {{407, actSt10lGondolaSwitch}, {429}};

static ActMail gondola_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchDown_mes[2] = {{430}, {429}};

static ActMail gondolaSwitchUp_mes[2] = {{430}, {429}};

static ActMail gondolaUp_mes[2] = {{430}, {429}};

static ActMail gondolaDown_mes[2] = {{430}, {429}};

static ActMail eneCam1_mes[2] = {{430}, {429}};

static ActMail box_mes[2] = {{430}, {429}};

static ActMail eneCam2_mes[2] = {{430}, {429}};

static ActMail eneCam3_mes[2] = {{430}, {429}};

static ActMail boxA_mes[2] = {{430}, {429}};

static ActMail boxB_mes[2] = {{430}, {429}};

static ActMail chainMain_mes[2] = {{408, actSt10lChainSwitch}, {429}};

static ActMail chain_mes[2] = {{430}, {429}};

static ActMail chainSwitch_mes[2] = {{430}, {429}};

static ActMail eneKill_mes[2] = {{430}, {429}};

void actSt10lInit(void)
{
    if (gflagChk(0x121) != 0) {
        SetWayGroupActive(0x16, 1);
        SetWayGroupActive(0x17, 1);
        stage_SetAnimation(0x17B, 0, 0x59);
    } else {
        SetWayGroupActive(0x14, 1);
        SetWayGroupActive(0x15, 1);
        stage_SetAnimation(0x17B, 0, 0);
    }
}

/*SWEEPactSt10lFloorLeft*/
void actSt10lFloorLeft(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    if (gflagChk(0x122) == 0 && D_00639EA8 != 0 &&
        scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        gflagOn(0x122);
    }

    if (D_00639EA8 != 0 && scpTriggerFloorAttr(D_00639EA8, 0x2000000) != 0) {
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 0x214);
    }

    if (gflagChk(0x122) != 0 && D_00639EA8 != 0 &&
        scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        scpPlayPosSet(D_00639EA8, -167.0f, -72.0f, -705.0f);
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 0x214);
    }

    scpAdpcmPlayRequestFunc(0x5B, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17B, 1, 0);

    SetWayGroupActive(0x14, 0);
    SetWayGroupActive(0x15, 0);
    SetWayGroupActive(0x16, 1);
    SetWayGroupActive(0x17, 1);

    gflagOn(0x121);

    while (stage_CheckAnimationFrame(0x17B, 0x59, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(0x122) != 0) {
        gflagOn(0x128);
    }

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xA);

    if (gflagChk(0x127) == 0) {
        D_0063AA08 = 0;
        lt_switch_layout(0x36);
        scpWakeupEnemyAll();

        if (D_00639EA8 != 0) {
            scpPlayEnd(D_00639EA8);
        }
    }

    floorLeft_mes[0].func = actSt10lFloorMain;
    sub->mail = floorLeft_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/*SWEEP-ENDactSt10lFloorLeft*/
void actSt10lFloorRight(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    if (gflagChk(0x122) != 0 && D_00639EA8 != 0 &&
        scpTriggerFloorAttr(D_00639EA8, 0x3000000) != 0) {
        scpPlayPosSet(D_00639EA8, -196.0f, -72.0f, 62.0f);
        scpPlayStart(D_00639EA8);
        scpPlayMot(D_00639EA8, 0x214);
    }

    scpAdpcmPlayRequestFunc(0x5B, &floor10l, 1, 1, 1);

    while (floor10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17B, 1, 0x5A);

    SetWayGroupActive(0x14, 1);
    SetWayGroupActive(0x15, 1);
    SetWayGroupActive(0x16, 0);
    SetWayGroupActive(0x17, 0);

    gflagOff(0x121);

    while (stage_CheckAnimationFrame(0x17B, 0xB4, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0xB);

    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    scpWakeupEnemyAll();

    if (D_00639EA8 != 0) {
        scpPlayEnd(D_00639EA8);
    }

    floorRight_mes[0].func = actSt10lFloorMain;
    sub->mail = floorRight_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaUp(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    scpAdpcmPlayRequestFunc(0x58, &st10l_gondola_up, 1, 1, 1);

    while (st10l_gondola_up == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17C, 1, 0);

    while (stage_CheckAnimationFrame(0x17C, 0xA9, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_CheckAnimationFrame(0x17C, 0xB3, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(0x123);

    if (st10l_gondola_up != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_up, 0x100);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_up) != 0) {
        _ACTWait(1);
    }

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(0x36);

    gondolaUp_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaDown(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    SetGirlDangerGObj(D_00639EA4);

    scpAdpcmPlayRequestFunc(0x59, &st10l_gondola_down, 1, 1, 1);

    while (st10l_gondola_down == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x17C, 1, 0xB4);

    while (stage_CheckAnimationFrame(0x17C, 0x154, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(0x17C, 0x168, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(0x123);

    if (st10l_gondola_down != 0) {
        scpAdpcmFadeCloseFunc(&st10l_gondola_down, 0x100);
    }

    while (scpAdpcmCloseChkFunc(&st10l_gondola_down) != 0) {
        _ACTWait(1);
    }

    ClearGirlDangerGObj();

    D_0063AA08 = 0;
    scpWakeupEnemyAll();
    lt_switch_layout(0x36);

    gondolaDown_mes[0].func = actSt10lGondolaMain;
    sub->mail = gondolaDown_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEneCam2Chk(volatile int a0)
{
    int save;

    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0 ||
           gflagChk(0x11F) == 0 || ((PObjGObjSt10L *)D_00639EA8)->act->f34 == 0x6F) {
        _ACTWait(1);
    }

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    save = D_0063A538;
    D_0063A538 = 0;

    scpKillEnemyOne(0x3E0);
    scpKillEnemyOne(0x3E1);
    scpKillSpiderGroup(0x3E2);
    scpSleepEnemyOne(0xEAD);
    scpSleepEnemyOne(0x3DF);
    scpSleepEnemyOne(0x3EE);
    scpSleepSpiderGroupOne(0x3EF);

    _ACTWait(0x1E);

    gflagOn(0x126);

    D_0063A538 = save;

    stage_SetAnimation(0x17D, 1, 0);

    while (stage_CheckAnimationFinish(0x17D) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;

    scpWakeupEnemyOne(0xEAD);
    scpWakeupEnemyOne(0x3E0);
    scpWakeupEnemyOne(0x3E1);
    scpWakeupSpiderGroupOne(0x3E2);
    scpWakeupEnemyOne(0x3DF);
    scpWakeupEnemyOne(0x3EE);
    scpWakeupSpiderGroupOne(0x3EF);
}

void actSt10lEneCam3Chk(volatile int a0)
{
    long long buf[2];

    while (gflagChk(0x128) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x127);
    FinishHint(0xE);

    stage_SetAnimation(0x17E, 1, 0);

    buf[0] = eneCam3ChkPos.d[0];
    buf[1] = eneCam3ChkPos.d[1];
    _SCPMoveCharactorByWay(D_00639EA8, 0, (int *)buf, 0, 100.0f);

    while (stage_CheckAnimationFinish(0x17E) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOff(0x127);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x3);

    lt_switch_layout(0x36);
    D_0063AA08 = 0;
    scpWakeupEnemyAll();
}

void actSt10lChainMove(volatile int a0)
{
    lt_switch_layout(0x37);
    scpSleepEnemyAll();

    gflagOn(0x11F);
    FinishHint(0xD);

    _ACTWait(0x1E);

    scpAdpcmPlayRequestFunc(0x61, &chain10l, 1, 1, 1);

    while (chain10l == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x180, 1, 0);
    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(0x180, 0xF0, 0) == 0) {
        if ((D_0028F8F0[0].trg & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&chain10l, 0x200);

            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }

            stage_SetAnimation(0x180, 1, 0xEF);
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }

    scpWakeupEnemyAll();
    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]);

    stage_SetAnimation(0x180, 0, 0);

    scpSearchGobj(0x3D9)->f16C = 1;
}

void actSt10lChain(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x11F) == 0) {
        stage_SetAnimation(0x180, 0, 0);

        scpSearchGobj(0x3D9)->f16C = 0;

        chain_mes[0].func = actSt10lChainMain;
        self->mail = chain_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x180, 0, 0);
        FinishHint(0xD);
    }
}

void actSt10lFloor(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    floor_mes[0].func = actSt10lFloorMain;
    self->mail = floor_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondola(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x123) != 0) {
        stage_SetAnimation(0x17C, 0, 0);
        _ACTWait(0xA);
        stage_SetAnimation(0x17C, 0, 0xB3);
    } else {
        stage_SetAnimation(0x17C, 0, 0);
    }

    gondola_mes[0].func = actSt10lGondolaMain;
    self->mail = gondola_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x120, 0x17F, 0, 0x13, 0.0f, -72.0f, 1274.0f, 76.0f, -72.0f, 1274.0f);
}

void actSt10lBox(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    box_mes[0].func = actSt10lBoxChk;
    self->mail = box_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEnemy1_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);
    Generator_Mask((int)scpSearchGobj(0x3E5));

    while (gflagChk(0x125) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x74);

    Generator_Call(a0);
    Generator_MaskOff(a0);
    Generator_Call((int)scpSearchGobj(0x3E5));
}

void actSt10lEnemy1_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x125) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x64);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy2_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x126) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x74);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy2_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x126) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x64);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy2_3(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x126) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x82);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy3_1(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x127) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x1);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEnemy3_2(volatile int a0)
{
    int x = a0;

    actInitialize(a0);

    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(0x127) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x140);

    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void actSt10lEneCam1(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x125) == 0) {
        eneCam1_mes[0].func = actSt10lEneCam1Chk;
        self->mail = eneCam1_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam2(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x126) == 0) {
        eneCam2_mes[0].func = actSt10lEneCam2Chk;
        self->mail = eneCam2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lEneCam3(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x128) == 0) {
        eneCam3_mes[0].func = actSt10lEneCam3Chk;
        self->mail = eneCam3_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        FinishHint(0xE);
    }
}

void actSt10lEneKill(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x129) == 0) {
        eneKill_mes[0].func = actSt10lEneKillChk;
        self->mail = eneKill_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10lBoxA(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x12A) == 0) {
        boxA_mes[0].func = actSt10lBoxAChk;
        self->mail = boxA_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x3D1)->f16C = 0;
    }
}

void actSt10lBoxB(volatile int a0)
{
    int x = a0;
    ActSt10L *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x12B) == 0) {
        boxB_mes[0].func = actSt10lBoxBChk;
        self->mail = boxB_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(0x3D2)->f16C = 0;
    }
}

void actSt10lGateXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0xAE) == 0) {
        scpSearchGobj(0x3CB)->f16C = 0;
    } else {
        scpSearchGobj(0x3CA)->f16C = 0;
    }
}

void actSt10lFloorMain(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = floorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lFloorSwitch(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x121) != 0) {
        floorSwitchRight_mes[0].func = actSt10lFloorRight;
        sub->mail = floorSwitchRight_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    floorSwitchLeft_mes[0].func = actSt10lFloorLeft;
    sub->mail = floorSwitchLeft_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lGondolaMain(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = gondolaMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lGondolaSwitch(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpSleepEnemyAll();

    if (gflagChk(0x123) != 0) {
        gondolaSwitchDown_mes[0].func = actSt10lGondolaDown;
        sub->mail = gondolaSwitchDown_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }

    gondolaSwitchUp_mes[0].func = actSt10lGondolaUp;
    sub->mail = gondolaSwitchUp_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEneCam1Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while ((D_00639EA8 == 0 || gflagChk(0x124) == 0) &&
           (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 ||
            scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0)) {
        _ACTWait(1);
    }

    gflagOn(0x125);
}

void actSt10lBoxChk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr((int)scpSearchGobj(0x3DC), 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x124);
}

void actSt10lSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10lBoxAChk(volatile int a0)
{
    while (scpTriggerBall(a0, (int)scpSearchGobj(0x3D1), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x12A);
    scpSearchGobj(0x3D1)->f16C = 0;
    _ACTWait(0x1E);
    soundSeDefPlay(0x4F6, 0, 0, 1);
}

void actSt10lBoxBChk(volatile int a0)
{
    while (scpTriggerBall(a0, (int)scpSearchGobj(0x3D2), 100.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(0x12B);
    scpSearchGobj(0x3D2)->f16C = 0;
    _ACTWait(0x1E);
    soundSeDefPlay(0x4F7, 0, 0, 1);
}

void actSt10lChainMain(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = chainMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10lChainSwitch(volatile int a0)
{
    ActSt10L *sub = ((PObjGObjSt10L *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    chainSwitch_mes[0].func = actSt10lChainMove;
    sub->mail = chainSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10lEneKillChk(volatile int a0)
{
    int save;

    while (scpTriggerBall(a0, (int)D_00639EA4, 500.0f) == 0) {
        _ACTWait(1);
    }

    enable_game_pause = 0;
    _ACTWait(1);

    save = D_0063A538;
    D_0063A538 = 0;
    _ACTWait(0x1E);

    gflagOn(0x129);
    scpKillEnemyOne(0x3E8);
    scpKillEnemyOne(0x3E9);
    scpKillSpiderGroup(0x3EA);
    _ACTWait(0x1E);

    D_0063A538 = save;
    _ACTWait(1);
    enable_game_pause = 1;
}
