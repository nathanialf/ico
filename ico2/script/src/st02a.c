#include "st02a.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
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
#include "main.h"
#include "act-game.h"
#include <libvu0.h>
#include "script.h"

/* .data: one mail record per posting site. Word 0 of each entry is the mail id
 * the entry answers (377 the actor post, 376 the trailing entry); .func is
 * filled in at run time before the post, except in the two main-mail records,
 * which answer 356 and 357 with their switch threads. Each record is named for
 * the thread that owns and posts it; where one thread owns two, for the
 * watcher it installs. */
void actSt02aFenceSwitch(GObj *volatile self);
void actSt02aGondolaSwitch(GObj *volatile self);

static ActMail door_down_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_up_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_up_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail door_down_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail fence_main_mail[2] = {{356, actSt02aFenceSwitch}, {376}}; /* derived name */

static ActMail fence_mail[2] = {{377}, {376}}; /* derived name */

static ActMail fence_switch_mail[2] = {{377}, {376}}; /* derived name */

static ActMail waterfall_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_main_mail[2] = {{357, actSt02aGondolaSwitch}, {376}}; /* derived name */

static ActMail gondola_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_switch_down_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_switch_up_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_up_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gondola_down_mail[2] = {{377}, {376}}; /* derived name */

static ActMail girl_jump_mail[2] = {{377}, {376}}; /* derived name */

static ActMail ene_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_off_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_on_start_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_on_chk_mail[2] = {{377}, {376}}; /* derived name */

static ActMail way_off_chk_mail[2] = {{377}, {376}}; /* derived name */

void actSt02aInit(void)
{
    if (gflagChk(102) == 0) {
        SetWayGroupActive(26, 0);
        stage_SetAnimation(76, 0, 0);
    } else {
        stage_SetAnimation(76, 0, -1);
    }

    if (gflagChk(104) == 0) {
        stage_SetAnimation(78, 0, 0);
    } else {
        stage_SetAnimation(78, 0, -1);
    }
}

/* The two-part door's SE position, copied into the local the sound call reads. */
static const ConstVec doorSePos = {{-1823.0f, -1174.0f, 2429.0f, 0.0f}}; /* derived name */

/* The door's two effect positions; the up sequence plays them in this order and
 * the down sequence in the other.  ico2/script/src/st08b.c carries the same two
 * points for its own door. */
static const ConstVec doorUpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

/* The two boundary points the boy's splash check tests against. */
static const ConstVec boySplashPos[2] = {{{840.0f, 235.0f, 560.0f, 1.0f}},
                                         {{740.0f, 235.0f, 560.0f, 1.0f}}};

/* The waterfall's reflection mesh and the layout quad it is stretched over:
 * the quad drops from y 280 to y 0, the falling water.  This build has one
 * mesh and one quad (PAL adds the pool's).  The value at offset 0x1C is a
 * hardware field. */
static const PoolMesh fallReflactionMesh = {40, 20, 0, 0, 0, 0, 0, 0x60687080}; /* derived name */

static const PoolMeshQuad fallReflactionQuad = {{{650.0f, 280.0f, 550.0f, 1.0f},
                                                 {650.0f, 0.0f, 700.0f, 1.0f},
                                                 {900.0f, 280.0f, 550.0f, 1.0f},
                                                 {900.0f, 0.0f, 700.0f, 1.0f}}};

/* The girl's jump: the SE position, the point she turns to before she jumps,
 * and the seven points of the effect sequence. */
static const ConstVec girlJumpSePos = {{892.0f, 777.0f, 174.0f, 0.0f}}; /* derived name */

static const ConstVec girlJumpPos = {{1400.0f, 0.0f, 175.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffectPos = {{3645.0f, -1966.0f, 1122.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect2Pos = {{3753.0f, -1936.0f, 1090.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect3Pos = {{3605.0f, -1866.0f, 1150.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect4Pos = {{3759.0f, -1666.0f, 1152.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect5Pos = {{3305.0f, -1566.0f, 1082.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect6Pos = {{3545.0f, -1466.0f, 1120.0f, 1.0f}}; /* derived name */

static const ConstVec girlJumpEffect7Pos = {{3655.0f, -1066.0f, 1477.0f, 1.0f}}; /* derived name */

void actSt02aDoorUpChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorUpEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(74, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1170, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(74) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    door_up_chk_mail[0].func = actSt02aDoorDownChk;
    sub->mail = door_up_chk_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt02aDoorDownChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);
    ConstVec pos;
    int h;

    while (scpTriggerFloorAttrTargetMan(self, 0x1000000) != 0) {
        _ACTWait(1);
    }
    _ACTWait(15);
    actCreateSubThread(actSt02aDoorDownEffect, 21);
    scpWakeupItemWithBoundary(-1827.0f, -1072.0f, 2285.0f, 100.0f);
    stage_SetAnimation(75, 1, 0);
    pos = doorSePos;
    soundSeDefPlay(1170, 0, pos.f, 1);
    _ACTWait(30);
    h = soundSeDefPlay(1171, 0, pos.f, 1);
    _ACTWait(30);
    soundSeDefStop(h);
    soundSeDefPlay(1172, 0, pos.f, 1);
    while (stage_CheckAnimationFinish(75) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    door_down_chk_mail[0].func = actSt02aDoorUpChk;
    sub->mail = door_down_chk_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

/* .sdata */
SqEntry *st02a_fence = 0;

void actSt02WaterFallBoySplashCheck(GObj *volatile self)
{
    ConstVec buf[2];
    ConstVec buf2;
    int idx;

    if (boyGObj == 0)
        return;

    buf[0].d[0] = boySplashPos[0].d[0];
    buf[0].d[1] = boySplashPos[0].d[1];
    buf[1].d[0] = boySplashPos[1].d[0];
    buf[1].d[1] = boySplashPos[1].d[1];

    for (;;) {
        idx = GetSkeltonFocusNode(boyGObj, 35);
        CopyVector(buf2.f, (float *)(GOBJ_SUB(boyGObj)->nodeMtx + (idx << 6) + 48));
        if (scpTriggerPosBall(buf[0].f, buf2.f, 100.0f))
            scpEffectStart(buf2.f, 46);
        _ACTWait(10);

        idx = GetSkeltonFocusNode(boyGObj, 35);
        CopyVector(buf2.f, (float *)(GOBJ_SUB(boyGObj)->nodeMtx + (idx << 6) + 48));
        if (scpTriggerPosBall(buf[1].f, buf2.f, 100.0f))
            scpEffectStart(buf2.f, 46);
        _ACTWait(10);
    }
}

SqEntry *gondola = 0;

void actSt02aGondolaUp(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(80, &gondola, 1, 1, 1);
    while (gondola == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(77, 1, 0);
    gflagOn(103);
    while (stage_CheckAnimationFrame(77, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(77, 149, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (gondola != 0) {
        soundDataClose(gondola);
    }
    gondola_up_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_up_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

SqEntry *gondola_test = 0;

void actSt02aGondolaDown(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpAdpcmPlayRequestFunc(80, &gondola_test, 1, 1, 1);
    while (gondola_test == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(77, 1, 150);
    gflagOff(103);
    while (stage_CheckAnimationFrame(77, 260, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(77, 300, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    if (gondola_test != 0) {
        soundDataClose(gondola_test);
    }
    gondola_down_mail[0].func = actSt02aGondolaMain;
    sub->mail = gondola_down_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt02aGirlJumpChk(GObj *volatile self) /* derived name */
{
    ConstVec pos;
    ConstVec v;
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(104);
    pos = girlJumpSePos;
    soundSeDefPlay(1278, 0, pos.f, 1);
    if (ACTGame_FLAG_TETSUNAGI() == 0) {
        stage_SetAnimation(78, 1, 0);
        scpPlayMot(girlGObj, 521);
        _ACTWait(10);
        v = girlJumpPos;
        sceVu0SubVector(dir, v.f, test_CURRENTROOT(girlGObj));
        scpPlayMotDir(girlGObj, dir);
        _ACTWait(10);
        scpPlayJump(girlGObj, 259);
    } else {
        iosPadActRequest(boyPad, 16);
        _SCPBoySupportGirl(-875.0f, -900.0f, -175.0f, -1075.0f, -900.0f, -175.0f);
        stage_SetAnimation(78, 1, 0);
    }
    actCreateSubThread(actSt02aGirlJumpEffect, 21);
    while (stage_CheckAnimationFinish(78) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actSt02aGirlJumpEffect(GObj *volatile self) /* derived name */
{
    ConstVec b1;
    ConstVec b2;
    ConstVec b3;
    ConstVec b4;
    ConstVec b5;
    ConstVec b6;
    ConstVec b7;
    float f;
    float nf;

    for (f = 0.0f; f < 1000.0f;) {
        switch ((int)f) {
        case 0:
            b1 = girlJumpEffectPos;
            scpEffectStart(b1.f, 15);
            break;
        case 15:
            b2 = girlJumpEffect2Pos;
            scpEffectStart(b2.f, 0);
            b3 = girlJumpEffect3Pos;
            scpEffectStart(b3.f, 15);
            break;
        case 60:
            b4 = girlJumpEffect4Pos;
            scpEffectStart(b4.f, 15);
            b5 = girlJumpEffect5Pos;
            scpEffectStart(b5.f, 0);
            break;
        case 120:
            b6 = girlJumpEffect6Pos;
            scpEffectStart(b6.f, 0);
            b7 = girlJumpEffect7Pos;
            scpEffectStart(b7.f, 0);
            break;
        }
        nf = f + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
    }
}

void actSt02aDoor(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (scpTriggerBall(self, boyGObj, 200.0f) != 0) {
        stage_SetAnimation(75, 0, 0);
        _ACTWait(60);
        door_down_start_mail[0].func = actSt02aDoorDownChk;
        act->mail = door_down_start_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(74, 0, 0);
        door_up_start_mail[0].func = actSt02aDoorUpChk;
        act->mail = door_up_start_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt02aGondola(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(103) != 0) {
        stage_SetAnimation(77, 0, 0);
        _ACTWait(10);
        stage_SetAnimation(77, 0, 149);
    } else {
        stage_SetAnimation(77, 0, 300);
    }
    gondola_mail[0].func = actSt02aGondolaMain;
    act->mail = gondola_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt02aFence(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(102) == 0) {
        fence_mail[0].func = actSt02aFenceMain;
        act->mail = fence_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt02aWaterFall(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(92) != 0) {
        waterfall_mail[0].func = actSt02aWaterFallChk;
        act->mail = waterfall_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
    actCreateSubThread(actSt02WaterFallBoySplashCheck, 21);
    actCreateSubThread(actSt02aWaterFallReflactionEffect, 21);
}

void actSt02aGirlJump(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(104) == 0) {
        girl_jump_mail[0].func = actSt02aGirlJumpChk;
        act->mail = girl_jump_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt02aBox(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);

    _ACTWait(1);

    if (gflagChk(95) != 0) {
        scpSearchGobj(1504)->active = 0;
    }
    if (gflagChk(94) != 0) {
        scpSearchGobj(1505)->active = 0;
    }
    if (gflagChk(94) == 0 && gflagChk(95) == 0) {
        scpSearchGobj(1504)->active = 0;
        scpSearchGobj(1505)->active = 0;
    }
}

void actSt02aBoxEvent2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);

    _ACTWait(1);

    if (gflagChk(96) == 0) {
        scpSearchGobj(1507)->active = 0;
    }
}

void actSt02aEne(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(105) == 0) {
        ene_mail[0].func = actSt02aEneChk;
        act->mail = ene_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt02aEnemy1(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(106) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt02aEnemy2(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);

    _ACTWait(1);

    Generator_Mask(self);

    while (gflagChk(106) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    Generator_MaskOff(self);
    Generator_Call(self);
    _ACTWait(60);
    Generator_Call(self);
}

void actSt02aSekizo(GObj *volatile self)
{
    GObj *x = self;
    actInitialize(self);

    _ACTWait(1);

    scpSekizou(self, 107, 79, 0, 21, 900.0f, 1828.0f, 1150.0f, 800.0f, 1828.0f, 1150.0f);
}

void actSt02aWay(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(108) == 0) {
        way_off_start_mail[0].func = actSt02aWayOffChk;
        act->mail = way_off_start_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        way_on_start_mail[0].func = actSt02aWayOnChk;
        act->mail = way_on_start_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt02aDoorEvent(int x)
{
    volatile int local = x;
}

void actSt02aDoorUpEffect(GObj *volatile self)
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
            scpEffectStart(b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffect2Pos.d[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt02aDoorDownEffect(GObj *volatile self)
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
            scpEffectStart(b1, 0);
            break;
        case 30:
            b2[0] = v0b;
            b2[1] = doorUpEffectPos.d[1];
            scpEffectStart(b2, 0);
            break;
        }
        _ACTWait(1);
    }
}

void actSt02aFenceMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    scpBoyControlReadDisable = 0;
    sub->mainMail = fence_main_mail;
    while (1) {
        _ACTWait(1);
    }
}

void actSt02aFenceSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    fence_switch_mail[0].func = actSt02aFenceOpen;
    sub->mail = fence_switch_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt02aFenceOpen(GObj *volatile self)
{
    gflagOn(102);
    scpAdpcmPlayRequestFunc(89, &st02a_fence, 1, 1, 1);
    while (st02a_fence == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(76, 1, 0);
    while (stage_CheckAnimationFinish(76) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(26, 1);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt02aWaterFallChk(GObj *volatile self)
{
    scpSearchGobj(1486)->active = 0;
    DeleteParticleLayout(scpSearchGobj(1519));
    DeleteParticleLayout(scpSearchGobj(1520));
    DeleteParticleLayout(scpSearchGobj(1521));
    DeleteParticleLayout(scpSearchGobj(1522));
    stage_SetAnimation(321, -1, -2);
}

void actSt02aWaterFallReflactionEffect(GObj *volatile self)
{
    PoolMesh m0 = fallReflactionMesh;
    PoolMeshQuad q0 = fallReflactionQuad;

    InitLayoutedPoolReflactionMesh(&m0, &q0);
    for (;;) {
        SetLayoutedPoolReflactionMesh(&m0);
        DispLimitedPoolReflactionMesh(&m0);
        _ACTWait(1);
    }
}

void actSt02aGondolaMain(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    lt_switch_layout(50);
    scpBoyControlReadDisable = 0;
    sub->mainMail = gondola_main_mail;
    while (1) {
        _ACTWait(1);
    }
}

void actSt02aGondolaSwitch(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    sub->mainMail = 0;
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    if (gflagChk(103) != 0) {
        gondola_switch_down_mail[0].func = actSt02aGondolaDown;
        sub->mail = gondola_switch_down_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
    gondola_switch_up_mail[0].func = actSt02aGondolaUp;
    sub->mail = gondola_switch_up_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt02aGirlJumpEvent(int x) /* derived name */
{
    volatile int local = x;
}

void actSt02aEneChk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    gflagOn(105);
    gflagOn(106);
}

void actSt02aSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt02aWayOnChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x4000000) == 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(53, 1);
    gflagOff(108);
    way_on_chk_mail[0].func = actSt02aWayOffChk;
    sub->mail = way_on_chk_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt02aWayOffChk(GObj *volatile self)
{
    Act *sub = GOBJ_ACT(self);

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }
    SetWayGroupActive(53, 0);
    gflagOn(108);
    way_off_chk_mail[0].func = actSt02aWayOnChk;
    sub->mail = way_off_chk_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}
