#include "st10r.h"
#include "gamesys.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "camera-root.h"
#include "generator.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "cage.h"
#include "motionManager2.h"
#include "rotObject.h"
#include "typedef.h"
#include "main.h"
#include "script.h"

/* kept local: this TU's bytes only come out with its own view of PObjGObj, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PObjGObjSt10R {
    char pad00[8];   /* 0x000 */
    int f08;         /* 0x008 */
    int f0C;         /* 0x00C */
    char pad10[332]; /* 0x010 */
    char *f15C;      /* 0x15C */
    char pad160[4];  /* 0x160 */
    Act *act;        /* 0x164 */
    char pad168[4];  /* 0x168 */
    int f16C;        /* 0x16C */
} PObjGObjSt10R;

static ActMail floor_mes[2] = {{430}, {429}};

static ActMail floor_hit_mes[2] = {{430}, {429}};

static ActMail cage_mes[2] = {{430}, {429}};

static ActMail tower_mes[2] = {{430}, {429}};

static ActMail exit_mes[2] = {{430}, {429}};

static ActMail chain_main_mes[2] = {{408, actSt10rChainSwitch}, {429}};

static ActMail chain_mes[2] = {{430}, {429}};

static ActMail chain_switch_mes[2] = {{430}, {429}};

static ActMail ene_mes[2] = {{430}, {429}};

static ActMail fence_mes[2] = {{430}, {429}};

static ActMail fence2_mes[2] = {{430}, {429}};

static ActMail fence_down1_mes[2] = {{430}, {429}};

static ActMail fence_up1_mes[2] = {{430}, {429}};

static ActMail fence_down2_mes[2] = {{430}, {429}};

static ActMail fence_up2_mes[2] = {{430}, {429}};

static ActMail way_mes[2] = {{430}, {429}};

static ActMail way_onchk_mes[2] = {{430}, {429}};

static ActMail way_offchk_mes[2] = {{430}, {429}};

static ActMail tower_resque_mes[2] = {{430}, {429}};

/* .sbss, owned by st10r.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the
   subthreads the wait loops below spin for. */
static int demoEnd;

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec girlWayPos = {{-296.0f, 327.0f, 2125.0f, 0.0f}};

/* The second fence-up watcher's mail record: it installs
   actSt10rFenceDownChk2 here and posts it. Word 0 of each entry is the mail
   id the entry answers (430 the actor post, 429 the trailing entry);
   .func is filled in at run time. Named for the thread that owns and posts
   it. */

/* .sdata, owned by st10r.o, in the ROM's order: the floor and cage stream handles (MAIN.MAP globals), the scene stream MAIN.MAP leaves unnamed, the chain's. */
int st10r_floor = 0;

char *cage10r = 0;

static char *st10r_adpcm = 0; /* derived name */

char *chain10r = 0;

void actSt10rInit(void)
{
    if (gflagChk(300) != 0) {
        stage_SetAnimation(385, 0, -1);
        SetWayGroupActive(15, 1);
    } else {
        stage_SetAnimation(385, 0, 0);
    }

    if (gflagChk(302) == 0) {
        SetWayGroupActive(23, 0);
        stage_SetAnimation(389, 0, 0);
    } else {
        SetWayGroupActive(23, 1);
        stage_SetAnimation(389, 0, -1);
        FinishHint(21);
    }

    if (gflagChk(301) == 0) {
        stage_SetAnimation(388, 0, 0);
    } else {
        stage_SetAnimation(388, 0, -1);
        FinishHint(22);
    }
}

void actSt10rEnd(void)
{
    gamesysObjInfoCls(scpSearchGobj(1634)->kind, scpSearchGobj(1634)->f08);
    gamesysObjInfoCls(scpSearchGobj(1632)->kind, scpSearchGobj(1632)->f08);
}

void actSt10rFloorChk(volatile int a0)
{
    int th;

    while (scpTriggerBall(a0, boyGObj, 50.0f) == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 0x10);

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(300);
    WakeupHint(21);

    scpAdpcmPlayRequestFunc(92, &st10r_floor, 1, 1, 1);
    while (st10r_floor == 0) {
        _ACTWait(1);
    }

    demoEnd = 0;
    th = actCreateSubThread(actSt10rFloorSub, 21);
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st10r_floor, 0x200);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        stage_SetAnimation(385, 0, -1);
        scpFadeIn(3.0f);
    }

    SetWayGroupActive(15, 1);
    scpWakeupEnemyAll();
    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);
}

void actSt10rFloorHitChk(volatile int a0)
{
    for (;;) {
        while (scpTriggerBall(a0, boyGObj, 100.0f) == 0 || gflagChk(300) != 0 ||
               (ForMotionViewer_GetCurrentMotion(boyGObj) != 0x2F &&
                ForMotionViewer_GetCurrentMotion(boyGObj) != 0x30 &&
                ForMotionViewer_GetCurrentMotion(boyGObj) != 0x31 &&
                ForMotionViewer_GetCurrentMotion(boyGObj) != 0x3E)) {
            _ACTWait(1);
        }

        stage_SetAnimation(386, 1, 0);

        while (stage_CheckAnimationFrame(386, 12, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        soundSeDefPlay(1335, 0, 0, 1);
        soundSeDefPlay(1335, 0, 0, 1);

        while (stage_CheckAnimationFinish(386) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }
}

void actSt10rCageMain(volatile int a0)
{
    int th;

    while (!(scpGetRotObjectRotCount(0x645) < -2.0f)) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    gflagOn(301);
    FinishHint(22);

    SetRotObjectLockFlag(scpSearchGobj(1605), 1);

    demoEnd = 0;
    scpAdpcmPlayRequestFunc(73, &cage10r, 1, 1, 0);

    th = actCreateSubThread(actSt10rCageSub, 21);

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (cage10r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&cage10r, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(388, 0, -1);
        _ACTWait(1);

        HotInitCageGeo(scpSearchGobj(1627));
        _ACTWait(1);

        scpFadeIn(3.0f);
    }

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(54);
}

void actSt10rTowerChk(volatile int a0)
{
    int th;
    int n;
    int f;

    while ((n = scpIsBombExplode(19)) == 0 || scpTriggerBall(a0, n, 350.0f) == 0) {
        _ACTWait(1);
    }

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x4000000) != 0) {
        actCreateSubThread(actSt10rGirlWay, 21);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();

    FinishHint(21);

    reg_SetScissorSw(1);

    scpAdpcmPlayRequestFunc(72, &st10r_adpcm, 1, 1, 0);

    _ACTWait(60);
    while (st10r_adpcm == 0) {
        _ACTWait(1);
    }

    gflagOn(302);

    th = actCreateSubThread(actSt10rTowerConte, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    f = demoEnd ^ 1;

    if (f) {
        scpAdpcmFadeCloseFunc(&st10r_adpcm, 0xC0);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    iosPadActStopAll();

    iosThreadSetPri((int *)((GProc *)th)->thread, 34);

    if (f) {
        stage_SetAnimation(389, 1, -1);
        SetCameraFlag_GamecamCutBack();
        scpPlayMot(boyGObj, 0);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(8.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    scpSearchGobj(1594)->f16C = 1;
    scpSearchGobj(1595)->f16C = 1;

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(54);

    reg_SetScissorSw(0);

    SetWayGroupActive(23, 1);

    gflagOn(303);
}

void actSt10rTowerConte(volatile int a0)
{
    stage_SetAnimation(389, 1, 0);

    AdpcmPlay(((AdpcmObj *)st10r_adpcm)->stream);

    scpSearchGobj(1594)->f16C = 0;
    scpSearchGobj(1595)->f16C = 0;

    while (stage_CheckAnimationFrame(389, 215, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 0xF);

    while (stage_CheckAnimationFrame(389, 270, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 0x11);

    while (stage_CheckAnimationFrame(389, 280, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 0xF);

    while (stage_CheckAnimationFrame(389, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 0x10);

    while (stage_CheckAnimationFinish(389) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 6);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt10rChainMove(volatile int a0)
{
    int th;

    lt_switch_layout(55);

    scpSleepEnemyAll();

    gflagOn(304);

    scpSearchGobj(1622)->f16C = 1;

    scpAdpcmPlayRequestFunc(93, &chain10r, 1, 1, 0);

    demoEnd = 0;

    th = actCreateSubThread(actSt10rChainMoveSub, 21);

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri((int *)((GProc *)th)->thread, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (chain10r == 0) {
            _ACTWait(1);
        }

        scpAdpcmFadeCloseFunc(&chain10r, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(387, 0, -1);

        scpFadeIn(3.0f);
    }

    soundSeDefPlay(1288, 0, 0, 1);

    iosPadActRequest(boyPad, 0x11);

    scpWakeupEnemyAll();

    scpBoyControlReadDisable = 0;

    lt_switch_layout(54);
}

void actSt10rFence(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(317) == 0) {
        scpSearchGobj(1631)->f16C = 0;
        scpSearchGobj(1632)->f16C = 0;
        scpSearchGobj(1635)->f16C = 0;
        scpSearchGobj(1636)->f16C = 0;
        scpSearchGobj(1637)->f16C = 0;
        scpSearchGobj(1638)->f16C = 0;
        scpSearchGobj(1639)->f16C = 0;
        scpSearchGobj(1640)->f16C = 0;
        scpSearchGobj(1641)->f16C = 0;
        scpSearchGobj(1642)->f16C = 0;

        scpLinkBGAtoLayoutedTarget(0x661, 0x95);

        stage_SetAnimation(149, 0, 0x1E);

        SetWayGroupActive(37, 1);
        SetWayGroupActive(38, 1);

        fence_mes[0].func = actSt10rFenceUpChk;
        self->mail = fence_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(1633)->f16C = 0;
        scpSearchGobj(1634)->f16C = 0;
        scpSearchGobj(1639)->f16C = 0;
        scpSearchGobj(1640)->f16C = 0;
        scpSearchGobj(1641)->f16C = 0;
        scpSearchGobj(1642)->f16C = 0;

        gflagOff(317);

        scpLinkBGAtoLayoutedTarget(0x65F, 0x95);

        stage_SetAnimation(149, 0, 0);

        if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
            scpPlayPosSet(girlGObj, 417.0f, 900.0f, -1096.0f);
        }

        fence2_mes[0].func = actSt10rFenceDownChk2;
        self->mail = fence2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10rFenceDownChk(volatile int a0)
{
    Act *sub = ((PObjGObjSt10R *)a0)->act;

    while (scpTriggerBall(a0, (int)scpSearchGobj(1633), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1639)->f16C = 0;
    scpSearchGobj(1640)->f16C = 0;
    scpSearchGobj(1641)->f16C = 0;
    scpSearchGobj(1642)->f16C = 0;

    stage_SetAnimation(149, 1, 0);

    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(308);

    fence_down1_mes[0].func = actSt10rFenceUpChk;
    sub->mail = fence_down1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/*SWEEPactSt10rFenceUpChk*/

void actSt10rFenceUpChk(volatile int a0)
{
    Act *sub = ((PObjGObjSt10R *)a0)->act;

    while (scpTriggerBall(a0, (int)scpSearchGobj(1633), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1639)->f16C = 1;
    scpSearchGobj(1640)->f16C = 1;
    scpSearchGobj(1641)->f16C = 1;
    scpSearchGobj(1642)->f16C = 1;

    stage_SetAnimation(149, 1, 0x1F);

    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

    while (stage_CheckAnimationFinish(149) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(308);

    fence_up1_mes[0].func = actSt10rFenceDownChk;
    sub->mail = fence_up1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/*SWEEP-ENDactSt10rFenceUpChk*/

void actSt10rFenceDownChk2(volatile int a0)
{
    Act *sub = ((PObjGObjSt10R *)a0)->act;

    while (scpTriggerBall(a0, (int)scpSearchGobj(1631), 5.0f) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1635)->f16C = 0;
    scpSearchGobj(1636)->f16C = 0;
    scpSearchGobj(1637)->f16C = 0;
    scpSearchGobj(1638)->f16C = 0;

    stage_SetAnimation(149, 1, 0);

    while (stage_CheckAnimationFrame(149, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

    while (stage_CheckAnimationFrame(149, 30, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 1);
    SetWayGroupActive(38, 1);

    gflagOff(308);

    fence_down2_mes[0].func = actSt10rFenceUpChk2;
    sub->mail = fence_down2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10rFenceUpChk2(volatile int a0)
{
    Act *sub = ((PObjGObjSt10R *)a0)->act;

    while (scpTriggerBall(a0, (int)scpSearchGobj(1631), 5.0f) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1635)->f16C = 1;
    scpSearchGobj(1636)->f16C = 1;
    scpSearchGobj(1637)->f16C = 1;
    scpSearchGobj(1638)->f16C = 1;

    stage_SetAnimation(149, 1, 0x1F);

    while (stage_CheckAnimationFrame(149, 40, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    soundSeDefPlay(1339, 0, 0, 1);

    while (stage_CheckAnimationFinish(149) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetWayGroupActive(37, 0);
    SetWayGroupActive(38, 0);

    gflagOn(308);

    fence_up2_mes[0].func = actSt10rFenceDownChk2;
    sub->mail = fence_up2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10rFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(300) == 0) {
        SleepHint(21);

        floor_mes[0].func = actSt10rFloorChk;
        self->mail = floor_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10rFloorHit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(300) == 0) {
        floor_hit_mes[0].func = actSt10rFloorHitChk;
        self->mail = floor_hit_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10rCage(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    scpSetCageVelocityFriction(0x65B, 0.95f);

    if (gflagChk(301) == 0) {
        cage_mes[0].func = actSt10rCageMain;
        self->mail = cage_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetRotObjectLockFlag(scpSearchGobj(1605), 1);
    }
}

void actSt10rTower(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(302) == 0) {
        tower_mes[0].func = actSt10rTowerChk;
        self->mail = tower_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10rTowerResque(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(302) == 0) {
        tower_resque_mes[0].func = actSt10rTowerResqueChk;
        self->mail = tower_resque_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10rExit(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    exit_mes[0].func = actSt10rExitChk;
    self->mail = exit_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10rChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(304) == 0) {
        stage_SetAnimation(387, 0, 0);
        scpSearchGobj(1622)->f16C = 0;

        chain_mes[0].func = actSt10rChainMain;
        self->mail = chain_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(387, 0, -1);
    }
}

void actSt10rSekizo(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpSekizou(a0, 0x131, 0x186, 0, 0x12, 0.0f, 327.0f, 4649.0f, -75.0f, 327.0f, 4649.0f);
}

void actSt10rEne(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(306) == 0) {
        ene_mes[0].func = actSt10rEneChk;
        self->mail = ene_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt10rEnemy1(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(307) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);
    _ACTWait(60);
    Generator_Call(a0);

    Generator_MaskOff(a0);
}

void actSt10rEnemy2(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    Generator_Mask(a0);

    while (gflagChk(307) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    Generator_MaskOff(a0);
}

void actSt10rElv(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(317) != 0) {
        scpSearchGobj(1633)->f16C = 0;
        scpSearchGobj(1634)->f16C = 0;
        gflagOff(317);
    } else {
        scpSearchGobj(1631)->f16C = 0;
        scpSearchGobj(1632)->f16C = 0;
    }
}

void actSt10rGateXL(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(243) == 0) {
        scpSearchGobj(1598)->f16C = 0;
    } else {
        scpSearchGobj(1597)->f16C = 0;
    }
}

void actSt10rWay(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    way_mes[0].func = actSt10rWayOnChk;
    self->mail = way_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10rFloorSub(volatile int a0)
{
    stage_SetAnimation(385, 1, 0);

    while (stage_CheckAnimationFrame(385, 67, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 0x10);

    while (stage_CheckAnimationFrame(385, 80, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 0x11);

    while (stage_CheckAnimationFinish(385) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt10rCageSub(volatile int a0)
{
    _ACTWait(30);

    while (cage10r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(((AdpcmObj *)cage10r)->stream);

    stage_SetAnimation(388, 1, 0);

    while (stage_CheckAnimationFinish(388) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 0x11);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt10rGirlWay(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = girlWayPos.d[0];
    buf[1] = girlWayPos.d[1];
    _SCPMoveCharactorByWay(girlGObj, 0, (float *)buf, 100.0f, 0);
    _ACTWait(0);
}

void actSt10rExitChk(volatile int a0)
{
    while (scpTriggerBall(a0, boyGObj, 400.0f) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(309);
    gflagOff(317);

    if (girlGObj != 0 && scpTriggerFloorAttr(girlGObj, 0x2000000) != 0) {
        OnGirlEscortFlag();
        RequestStageChange(1, boyGObj, girlGObj, 2.0f, 8.0f);
    }
    RequestStageChange(1, boyGObj, 0, 2.0f, 8.0f);
}

void actSt10rChainMain(volatile int a0)
{
    Act *sub = GOBJ_ACT(a0);

    sub->mainMail = chain_main_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt10rChainSwitch(volatile int a0)
{
    Act *self = ((PObjGObjSt10R *)a0)->act;

    scpBoyControlReadDisable = 1;
    self->mainMail = 0;
    chain_switch_mes[0].func = actSt10rChainMove;
    self->mail = chain_switch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10rChainMoveSub(volatile int a0)
{
    int se;

    _ACTWait(30);

    while (chain10r == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(((AdpcmObj *)chain10r)->stream);

    stage_SetAnimation(387, 1, 0);

    se = soundSeDefPlay(1287, 0, 0, 1);

    _ACTWait(180);

    soundSeDefStop(se);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt10rSekizoEvent(int x)
{
    volatile int local = x;
}

void actSt10rEneChk(volatile int a0)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 ||
           scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    gflagOn(306);
    gflagOn(307);
}

void actSt10rWayOnChk(volatile int a0)
{
    Act *sub = ((PObjGObjSt10R *)a0)->act;

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() != 0 || scpTriggerFloorAttr(girlGObj, 0x5000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(20, 1);

    way_onchk_mes[0].func = actSt10rWayOffChk;
    sub->mail = way_onchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10rWayOffChk(volatile int a0)
{
    Act *sub = ((PObjGObjSt10R *)a0)->act;

    if (girlGObj == 0) {
        _ACTWait(0);
    }
    while (scpCheckExistAliveEnemy() == 0 && scpTriggerFloorAttr(girlGObj, 0x6000000) == 0) {
        _ACTWait(1);
    }

    SetWayGroupActive(20, 0);

    way_offchk_mes[0].func = actSt10rWayOnChk;
    sub->mail = way_offchk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt10rTowerResqueChk(volatile int a0)
{
    while (gflagChk(303) != 0 || gflagChk(302) == 0 || scpTriggerBall(a0, boyGObj, 500.0f) == 0 ||
           (ForMotionViewer_GetCurrentMotion(boyGObj) != 0x54 &&
            ForMotionViewer_GetCurrentMotion(boyGObj) != 0x55)) {
        _ACTWait(1);
    }

    scpPlayStart(boyGObj);
    scpPlayPosSet(boyGObj, 135.0f, 321.0f, 2101.0f);
    scpPlayMot(boyGObj, 0);
    _ACTWait(120);
    scpPlayEnd(boyGObj);
}
