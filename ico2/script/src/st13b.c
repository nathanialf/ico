#include "common.h"
#include "st13b.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "jimaku.h"
#include "itou_boss.h"
#include "camera-root.h"
#include "fightSound.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"

extern int D_0063AA08;
extern int D_00639EAC;
extern int D_0063BFF4;
extern unsigned char D_0063BFF8;

/* .sbss, owned by st13b.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, the conte-02
   end flag, the pad actuator handle and volume byte the door-up subthread
   holds, and the flag actSt13bDoorUpSub raises when the door is up. */
static int demoEnd;

static int conte02End;

static int padAct;

static unsigned char padActVolume;

static int doorUpDone;

extern int D_00639EA4;
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int gobj, float r);
extern int D_00639ED4;
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(void *a0, int mot);
extern JimakuArg jimaku_msg;
extern int jimakuOn;
extern int D_0028F4C0[];
/* st13b.o's own .data run (no MAIN.MAP symbols): actor mail packets. */
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float f, int a1, int a2, int a3);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *h, short a1);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern int D_0063BFC0;
extern int boss;
extern float D_0063AA0C;
extern PadState D_0028F8F0[];
extern int D_0028F8F4[];
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int a0);
extern int st13b_down;
extern int st13b_up;
extern int sd;
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(void *a0, float x, float y, float z);
/* kept local: this TU's uses of scpAdpcmCloseChkFunc do not fit the prototype in script.h */
extern int scpAdpcmCloseChkFunc(int *h);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayWaitMotEnd do not fit the prototype in script.h */
extern void scpPlayWaitMotEnd(int a0);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, float *dir);
/* kept local: this TU's uses of scpSekizouCheckPoint do not fit the prototype in script.h */
extern void scpSekizouCheckPoint(void);
/* kept local: this TU's uses of scpGameStat_BoyWeaponkind do not fit the prototype in script.h */
extern int scpGameStat_BoyWeaponkind(void);
extern int boss_dead;
extern int sekizo13b;
extern int sekizo13b2;
extern int meets_again;
extern StgPre D_005F5D50[];
extern const ExitData D_0055C518[];
extern int stage_no;
extern int sekizo_13b;
extern int sekizo_13b_vol;

static ActMail floor_mes[2] = {{430}, {429}};

static ActMail sekizo_mes[2] = {{430}, {429}};

static ActMail sekizo2_mes[2] = {{430}, {429}};

static ActMail meetAgain_mes[2] = {{430}, {429}};

static ActMail boss_mes[2] = {{430}, {429}};

static ActMail bossAfter_mes[2] = {{430}, {429}};

static ActMail elevMain_mes[2] = {{406, actSt13bElevSwitch}, {429}};

static ActMail elev_mes[2] = {{430}, {429}};

static ActMail elevSwitch_mes[2] = {{430}, {429}};

static ActMail elevUp_mes[2] = {{430}, {429}};

static ActMail doorMain_mes[2] = {{407, actSt13bDoorSwitch}, {429}};

static ActMail door_mes[2] = {{430}, {429}};

static ActMail doorSwitch_mes[2] = {{430}, {429}};

static float doorUpSubPos[4] = {-3434.0f, -200.0f, 0.0f, 0.0f};

static ActMail elev2Chk_mes[2] = {{430}, {429}};

static ActMail elev2Chk2_mes[2] = {{430}, {429}};

static ActMail elev2chara_mes[2] = {{430}, {429}};

static ActMail elev2CharaChk_mes[2] = {{430}, {429}};

extern int st13b_yure;
extern unsigned char st13b_yure_vol;

void actSt13bFloor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(5) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        lt_switch_layout(55);
        D_0063AA08 = 1;

        stage_SetAnimation(30, 0, 0);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(34, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
        stage_SetAnimation(40, 0, 0xEB);
        stage_SetAnimation(43, 0, 0);
        stage_SetAnimation(35, 0, 0);

        floor_mes[0].func = actSt13bFloorChk;
        self->mail = floor_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
    }
}

void actSt13bFloorChk(volatile int a0)
{
    int v = 0x20;

    gflagOn(5);
    actCreateSubThread(actSt13bConte02, 21);
    actCreateSubThread(actSt13bConte02Jimaku, 21);

    conte02End = 0;
    D_0063BFC0 = 0;

    do {
        _ACTWait(1);
    } while (D_0063BFC0 == 0);

    while (conte02End == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    if (conte02End == 0) {
        v = 0x40;
    }

    if (D_0063BFC0 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BFC0, v);
    }

    RequestStageChange(4, D_00639EA4, 0, 0.025f, 2.0f);
}

void actSt13bConte02(volatile int a0)
{
    scpPlayStart(D_00639EA4);
    stgmgrNextStagePreLoadForceStageSet(0);
    scpAdpcmPlayRequestFunc(11, &D_0063BFC0, 0, 1, 0);

    while (D_0063BFC0 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(8.0f);

    stgmgrNextStagePreLoadForceStageSet(D_0055C518[(&D_005F5D50[stage_no])->ent[3]].f_24);
    stgmgrNextStagePreLoadForceNoCancel(1);

    stage_SetAnimation(586, 1, 0);
    scpPlayMot((void *)D_00639EA4, 282);
    scpPlayMot(scpSearchGobj(2403), 1001);
    scpSearchGobj(2403)->f16C = 1;
    scpPlayMot(scpSearchGobj(2404), 1023);
    scpSearchGobj(2404)->f16C = 1;
    scpPlayMot(scpSearchGobj(2405), 1047);
    scpSearchGobj(2405)->f16C = 1;
    _ACTWait(1);

    stage_SetAnimation(34, 1, 0);
    stage_SetAnimation(21, 1, 0);

    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 0.15);

    if (D_0028F4C0[0] != 0) {
        _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 1.0);
    }

    AdpcmPlay(*(int *)(D_0063BFC0 + 0x2C));

    while (stage_ContinueAnimation(586, 587) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 283);
    scpPlayMot(scpSearchGobj(2403), 1002);
    scpPlayMot(scpSearchGobj(2404), 1024);
    scpPlayMot(scpSearchGobj(2405), 1048);
    _ACTWait(1);

    stage_SetAnimation(27, 1, 0);
    stage_SetAnimation(22, 1, 0);

    while (stage_ContinueAnimation(587, 588) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    stage_SetAnimation(28, 1, 0);

    while (stage_ContinueAnimation(588, 589) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 284);
    scpPlayMot(scpSearchGobj(2403), 1003);
    scpPlayMot(scpSearchGobj(2404), 1025);
    scpPlayMot(scpSearchGobj(2405), 1049);
    _ACTWait(1);

    stage_SetAnimation(29, 1, 0);
    stage_SetAnimation(23, 1, 0);

    while (stage_ContinueAnimation(589, 590) == 0) {
        _ACTWait(1);
    }

    scpFadeIn(3.0f);

    scpPlayMot((void *)D_00639EA4, 285);
    scpPlayMot(scpSearchGobj(2404), 1026);
    _ACTWait(1);

    stage_SetAnimation(30, 1, 0);

    while (stage_ContinueAnimation(590, 591) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 286);
    scpPlayMot(scpSearchGobj(2403), 1002);
    scpPlayMot(scpSearchGobj(2404), 1024);
    scpPlayMot(scpSearchGobj(2405), 1048);
    _ACTWait(1);

    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(591, 592) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2403), 1004);
    scpPlayMot(scpSearchGobj(2404), 1027);
    scpPlayMot(scpSearchGobj(2405), 1050);
    _ACTWait(1);

    stage_SetAnimation(24, 1, 0);

    while (stage_ContinueAnimation(592, 593) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 287);
    scpSearchGobj(2403)->f16C = 0;
    scpSearchGobj(2404)->f16C = 0;
    scpSearchGobj(2405)->f16C = 0;

    stage_SetAnimation(34, 0, 0);

    while (stage_CheckAnimationFrame(593, 200, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

    stage_SetAnimation(593, -1, -2);
    scpFadeIn(3.0f);
    stage_SetAnimation(594, 1, 0);

    while (stage_ContinueAnimation(594, 595) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 288);
    _ACTWait(1);

    stage_SetAnimation(26, 1, 0);
    _ACTWait(60);

    padAct = iosPadActRequest(D_00639EAC, 9);
    padActVolume = 0x80;
    iosPadActVolumeSet(padAct, 0x80);

    while (stage_ContinueAnimation(595, 596) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(596, 597) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(25, 1, 0);

    while (stage_ContinueAnimation(597, 598) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 289);
    _ACTWait(130);

    stage_SetAnimation(32, 1, 0);

    while (stage_ContinueAnimation(598, 599) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(599, 600) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(padAct);
    scpPlayMot((void *)D_00639EA4, 290);

    while (stage_ContinueAnimation(600, 601) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 288);

    while (stage_ContinueAnimation(601, 602) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 292);
    _ACTWait(1);

    stage_SetAnimation(32, 1, 0xD0);

    while (stage_ContinueAnimation(602, 603) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 293);
    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_ContinueAnimation(603, 604) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 294);

    _ACTWait(30);
    iosPadActRequest(D_00639EAC, 0xF);
    _ACTWait(30);
    iosPadActRequest(D_00639EAC, 0x11);
    _ACTWait(15);
    iosPadActRequest(D_00639EAC, 0x11);
    _ACTWait(5);
    iosPadActRequest(D_00639EAC, 0x10);
    _ACTWait(15);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_ContinueAnimation(604, 605) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 295);

    while (stage_ContinueAnimation(605, 606) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 296);

    while (stage_ContinueAnimation(606, 607) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((void *)D_00639EA4, 297);

    while (stage_CheckAnimationFrame(607, 150, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    conte02End = 1;
}

void actSt13bSekizoChk(volatile int a0)
{
    float dir[4];

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x4B) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpAdpcmPlayRequestFunc(19, &sekizo13b, 1, 1, 1);

    while (sekizo13b == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(33, 1, 0);

    st13b_yure = iosPadActRequest(D_00639EAC, 9);
    st13b_yure_vol = 0x80;
    iosPadActVolumeSet(st13b_yure, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayPosSet((void *)D_00639EA4, 3085.0f, -1338.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)D_00639EA4, 251);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    gflagOn(10);

    while (stage_CheckAnimationFrame(33, 151, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st13b_yure);

    while (stage_CheckAnimationFinish(33) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(54);
    D_0063AA08 = 0;
}

void actSt13bSekizo2Chk(volatile int a0)
{
    float dir[4];

    while (scpTriggerBall(a0, D_00639EA4, 200.0f) == 0 || scpGameStat_BoyWeaponkind() != 5 ||
           ForMotionViewer_GetCurrentMotion(D_00639EA4) == 0x4B) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpAdpcmPlayRequestFunc(18, &sekizo13b2, 1, 1, 1);

    while (sekizo13b2 == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(34, 1, 0);

    st13b_yure = iosPadActRequest(D_00639EAC, 9);
    st13b_yure_vol = 0x80;
    iosPadActVolumeSet(st13b_yure, 0x80);

    scpPlayStart(D_00639EA4);
    scpPlayPosSet((void *)D_00639EA4, -1563.0f, 527.0f, 0.0f);
    _ACTWait(1);

    sceVu0SubVector(dir, test_CURRENTROOT(a0), test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);
    scpSekizouCheckPoint();
    scpPlayMot((void *)D_00639EA4, 251);
    scpPlayWaitMotEnd(D_00639EA4);
    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    gflagOn(11);

    while (stage_CheckAnimationFrame(34, 151, 0) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    iosPadActStop(st13b_yure);

    while (stage_CheckAnimationFinish(34) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    lt_switch_layout(54);
    D_0063AA08 = 0;
}

void actSt13bMeetAgain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(12) == 0) {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);

        meetAgain_mes[0].func = actSt13bMeetAgainChk;
        self->mail = meetAgain_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
    }
}

void actSt13bMeetAgainSub(volatile int a0)
{
    stage_SetAnimation(760, 1, 0);

    scpPlayMot((void *)D_00639EA4, 2);
    scpPlayMot(scpSearchGobj(2464), 971);
    scpPlayMot(scpSearchGobj(2465), 972);
    scpPlayMot(scpSearchGobj(2466), 973);
    scpPlayMot(scpSearchGobj(2467), 974);
    scpPlayMot(scpSearchGobj(2468), 975);
    scpPlayMot(scpSearchGobj(2469), 976);

    while (stage_ContinueAnimation(760, 761) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(761) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bMeetAgainChk(volatile int a0)
{
    int th;

    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayMot((void *)D_00639EA4, 0);
    gflagOn(12);
    scpAdpcmPlayRequestFunc(35, &meets_again, 1, 1, 1);

    while (meets_again == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actSt13bMeetAgainSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(760, 0, -1);
        scpFadeIn(3.0f);
    }

    scpPlayMot(scpSearchGobj(2464), 977);
    scpPlayMot(scpSearchGobj(2465), 978);
    scpPlayMot(scpSearchGobj(2466), 979);
    scpPlayMot(scpSearchGobj(2467), 980);
    scpPlayMot(scpSearchGobj(2468), 981);
    scpPlayMot(scpSearchGobj(2469), 982);

    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(54);
    scpAdpcmFadeCloseFunc(&meets_again, 0x80);
}

void actSt13bBoss(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    ScpCallCameraSetTarget(-1886.0f, 625.0f, -4.0f);
    fightSoundProcessRequestPause();

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    if (gflagChk(13) == 0) {
        scpSearchGobj(2470)->f16C = 0;
        boss_mes[0].func = actSt13bBossChk;
        self->mail = boss_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else if (gflagChk(14) == 0) {
        scpAdpcmPlayRequestFunc(37, &boss, 1, 0, 1);
        D_0063AA0C = 0.5f;
    }
}

void actSt13bBossChk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(13);
    scpAdpcmPlayRequestFunc(36, &sd, 1, 1, 1);

    while (sd == 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(37, &boss, 1, 0, 0);
    D_0063AA0C = 0.5f;

    scpSearchGobj(2470)->f16C = 1;
    scpPlayPosSet(scpSearchGobj(2470), 0.0f, -100.0f, 0.0f);

    scpPlayMot(scpSearchGobj(2464), 834);
    scpPlayMot(scpSearchGobj(2465), 834);
    scpPlayMot(scpSearchGobj(2466), 834);
    scpPlayMot(scpSearchGobj(2467), 834);
    scpPlayMot(scpSearchGobj(2468), 834);
    scpPlayMot(scpSearchGobj(2469), 834);

    CapsuleGhostBossStart();

    _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 6);

    while (boss == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(boss + 0x2C));
}

void actSt13bBossAfterChk(volatile int a0)
{
    int th;

    while (InqCapsuleGhostBossEnd() == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    gflagOn(14);
    scpAdpcmFadeCloseFunc(&boss, 0x80);

    while (scpAdpcmCloseChkFunc(&boss) != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(38, &boss_dead, 1, 1, 1);

    while (boss_dead == 0) {
        _ACTWait(1);
    }

    th = actCreateSubThread(actConte10c, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&boss_dead, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(763, 0, -1);
        stage_SetAnimation(35, 0, -1);
        scpFadeIn(3.0f);
    }

    scpPlayMot((void *)D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt13bElevDownSub(volatile int a0)
{
    stage_SetAnimation(40, 1, 0xEB);

    while (stage_CheckAnimationFrame(40, 321, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);

    while (stage_CheckAnimationFrame(40, 350, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063BFF4 = iosPadActRequest(D_00639EAC, 9);
    D_0063BFF8 = 0x80;
    iosPadActVolumeSet(D_0063BFF4, 0x80);

    while (stage_CheckAnimationFrame(40, 450, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bElevDown(volatile int a0)
{
    int th;

    lt_switch_layout(55);
    gflagOn(15);
    scpAdpcmPlayRequestFunc(79, &st13b_down, 0, 1, 1);

    while (st13b_down == 0) {
        _ACTWait(1);
    }

    preload(3);
    D_0063BFF4 = -1;
    th = actCreateSubThread(actSt13bElevDownSub, 21);
    demoEnd = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13b_down, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
    }

    if (D_0063BFF4 >= 0) {
        iosPadActStop(D_0063BFF4);
    }

    RequestStageChange(3, D_00639EA4, 0, 2.0f, 4.0f);
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt13bElevUp(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(325) != 0) {
        lt_switch_layout(55);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(40, 0, 0xEB);
        _ACTWait(10);
        D_0063AA08 = 1;
        stage_SetAnimation(40, 0, 0);
        elevUp_mes[0].func = actSt13bElevUpChk;
        self->mail = elevUp_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(40, 0, 0xEB);
    }
}

void actSt13bElevUpChk(volatile int a0)
{
    int th;

    scpAdpcmPlayRequestFunc(78, &st13b_up, 1, 1, 1);

    while (st13b_up == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);
    th = actCreateSubThread(actSt13bElevUpSub, 21);

    demoEnd = 0;
    D_0063BFF4 = -1;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        scpAdpcmFadeCloseFunc(&st13b_up, 0x200);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(40, 0, 0xEB);
        _ACTWait(2);
        scpPlayPosSet((void *)D_00639EA4, -772.0f, 527.0f, -226.0f);

        if (D_0063BFF4 >= 0) {
            iosPadActStop(D_0063BFF4);
        }

        scpFadeIn(3.0f);
    }

    D_0063AA08 = 0;
    lt_switch_layout(54);
    gflagOff(325);
}

void actSt13bDoorUp(volatile int a0)
{
    int th;

    lt_switch_layout(55);
    gflagOn(17);
    th = actCreateSubThread(actSt13bDoorUpSub, 21);

    demoEnd = 0;
    doorUpDone = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 0x24, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(43, 0, -1);
        scpFadeIn(3.0f);
    }

    if (doorUpDone == 0) {
        soundSeDefPlay(1222, 0, 0, 1);
    }

    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt13bElev2Chk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;

    if (gflagChk(16) != 0) {
        scpAdpcmPlayRequestFunc(100, &sekizo_13b_vol, 1, 1, 1);

        while (sekizo_13b_vol == 0) {
            _ACTWait(1);
        }

        _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
        stage_SetAnimation(42, 1, 0);

        while (stage_CheckAnimationFrame(42, 50, 0) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        iosPadActRequest(D_00639EAC, 0x10);

        while (stage_CheckAnimationFinish(42) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        gflagOff(16);
        D_0063AA08 = 0;
    } else {
        scpAdpcmPlayRequestFunc(99, &sekizo_13b, 0, 1, 1);

        while (sekizo_13b == 0) {
            _ACTWait(1);
        }

        _ACTWait((0x3C - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 0.15);
        stage_SetAnimation(41, 1, 0);

        while (stage_CheckAnimationFinish(41) == 0) {
            _ACTWait(1);
        }

        _ACTWait(1);
        gflagOn(16);
        RequestStageChange(2, D_00639EA4, 0, 2.0f, 8.0f);
        D_0063AA08 = 0;
    }

    lt_switch_layout(54);

    elev2chara_mes[0].func = actSt13bElev2CharaChk;
    sub->mail = elev2chara_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt13bSekizo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(10) == 0) {
        stage_SetAnimation(33, 0, 0);

        sekizo_mes[0].func = actSt13bSekizoChk;
        self->mail = sekizo_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(33, 0, -1);
    }
}

void actSt13bSekizo2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(11) == 0) {
        stage_SetAnimation(34, 0, 0);

        sekizo2_mes[0].func = actSt13bSekizo2Chk;
        self->mail = sekizo2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(34, 0, -1);
    }
}

void actSt13bBossAfter(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(14) == 0) {
        stage_SetAnimation(35, 0, 0);

        bossAfter_mes[0].func = actSt13bBossAfterChk;
        self->mail = bossAfter_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(35, 0, -1);
    }
}

void actSt13bStoneGirl(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (D_00639ED4 == 0x2E) {
        scpPlayMot(scpSearchGobj(2462), 808);
        scpSearchGobj(2462)->f16C = 1;
    }
}

void actSt13bElev(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    elev_mes[0].func = actSt13bElevMain;
    self->mail = elev_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt13bElev2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(16) != 0) {
        stage_SetAnimation(42, 0, 0);

        elev2Chk_mes[0].func = actSt13bElev2Chk;
        self->mail = elev2Chk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(41, 0, 0);

        elev2Chk2_mes[0].func = actSt13bElev2Chk;
        self->mail = elev2Chk2_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt13bDoor(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(17) == 0) {
        stage_SetAnimation(43, 0, 0);

        door_mes[0].func = actSt13bDoorMain;
        self->mail = door_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(43, 0, -1);
    }
}

void actBossTest(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(32, 0, -1);
    stage_SetAnimation(26, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(36, 0, 0);
    stage_SetAnimation(38, 0, 0);
}

void actSt13bConte02Jimaku(volatile int a0)
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
        case 1800:
            jimaku_msg.sub.unk2C = 1;
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
    } while (t < 2500.0f);
}

void actSt13bSekizo2Event(int x)
{
    volatile int local = x;
}

void actConte10c(volatile int a0)
{
    stage_SetAnimation(763, 1, 0);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(763, 300, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(35, 1, 0);

    while (stage_CheckAnimationFinish(763) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bElevMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = elevMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13bElevSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    elevSwitch_mes[0].func = actSt13bElevDown;
    sub->mail = elevSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt13bElevUpSub(volatile int a0)
{
    stage_SetAnimation(40, 1, 0);
    D_0063BFF4 = iosPadActRequest(D_00639EAC, 9);
    D_0063BFF8 = 0x80;
    iosPadActVolumeSet(D_0063BFF4, 0x80);
    while (stage_CheckAnimationFrame(40, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 0x11);
    iosPadActStop(D_0063BFF4);
    while (stage_CheckAnimationFrame(40, 234, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bDoorMain(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = doorMain_mes;
    while (1) {
        _ACTWait(1);
    }
}

void actSt13bDoorSwitch(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    sub->mainMail = 0;
    D_0063AA08 = 1;

    doorSwitch_mes[0].func = actSt13bDoorUp;
    sub->mail = doorSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt13bDoorUpSub(volatile int a0)
{
    _ACTWait(60);

    stage_SetAnimation(43, 1, 0);

    _ACTWait(120);

    soundSeDefPlay(1221, 0, doorUpSubPos, 1);

    _ACTWait(30);

    doorUpDone = 1;
    soundSeDefPlay(1222, 0, doorUpSubPos, 1);

    while (stage_CheckAnimationFinish(43) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt13bElev2CharaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) != 0) {
        _ACTWait(1);
    }

    elev2CharaChk_mes[0].func = actSt13bElev2Chk;
    sub->mail = elev2CharaChk_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
