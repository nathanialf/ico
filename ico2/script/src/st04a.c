#include "st04a.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "obj_manager.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "act.h"
#include "gobj_process.h"
#include "boyact.h"
#include "commonact.h"
#include "way_llf.h"
#include "brain.h"
#include "camera-root.h"
#include "fightSound.h"
#include "lws_kyomi.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "geometryManager.h"
#include "girl.h"
#include "matrixDrive.h"
#include "staticBlur.h"
#include "windManager.h"
#include "streamMotionManager.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "Matrix.h"
#include "script.h"
#include "jimaku.h"
#include "main.h"

/* this file's own view of Act (the shared one is in typedef.h): the torch
   watcher's three words */
typedef struct ActSt04A { /* field names derived */
    char pad0[1128];      /* 0x000 */
    int torchAnim;        /* 0x468, the stage animation the lit torch plays */
    GObj *torchObj;       /* 0x46C, the torch the ball must reach */
    int torchFlag;        /* 0x470, the game flag raised once it is lit */
} ActSt04A;               /* derived name */

/* .data: each action's mail pair and the check handler stored into its first
   entry at run time. */
static ActMail gate_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open2_ready_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open2_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_open3_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_l_mail[2] = {{377}, {376}}; /* derived name */

static ActMail gate_r_mail[2] = {{377}, {376}}; /* derived name */

static ActMail torch1_mail[2] = {{377}, {376}}; /* derived name */

static ActMail girl_sit_mail[2] = {{377}, {376}}; /* derived name */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* .sdata: the first gate's stream handle */
SqEntry *gate1st = 0;

void actSt04aGate(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    scpSearchGobj(528)->active = 0;

    if (gflagChk(116) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(212, 0, 0);
        stage_SetAnimation(215, 0, 0);

        gate_mail[0].func = actSt04aGateChk;
        act->mail = gate_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        stage_SetAnimation(212, 0, -1);
        stage_SetAnimation(215, 0, 0);
    }
}

void actSt04aGateChk(GObj *volatile self)
{
    int i;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(self, boyGObj, 3000.0f) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    scpPlayMot(boyGObj, 0);

    StandbyStreamMotion(streamMotion[1].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", ++i);
        _ACTWait(1);
    }

    SetWindManager(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f, 5.0f, 0.0f);

    scpPlayStart(girlGObj);

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(25, &gate1st, 1, 1, 1);
    while (gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(116);

    _ACTWait(1);

    actCreateSubThread(actSt04aConte06, 21);
    actCreateSubThread(actSt04aConte06Jimaku, 21);

    stage_SetAnimation(212, 1, 0);
}

void actSt04aConte06(GObj *volatile self)
{
    float dir[4];

    scpSearchGobj(528)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(528));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    stage_SetAnimation(527, 1, 0);

    while (stage_ContinueAnimation(527, 528) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(528, 529) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }

    _ACTWait(240);

    gate_yure_low = iosPadActRequest(boyPad, 9);
    gate_yure_low_vol = 64;
    iosPadActVolumeSet(gate_yure_low, 64);

    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(531, 532) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(532, 533) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(533, 534) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(534, 535) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(375, 1, 0);

    iosPadActRequest(boyPad, 15);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(535, 536) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(536, 537) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(gate_yure_low);

    while (stage_CheckAnimationFrame(537, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(537, 538) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(538, 539) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(539, 540) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(540, 541) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(541, 542) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(542, 543) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(543, 544) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(544, 545) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(545, 546) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(546, 547) == 0) {
        _ACTWait(1);
    }

    _ACTWait(120);

    stage_SetAnimation(377, 1, 0);

    iosPadActRequest(boyPad, 15);

    while (stage_ContinueAnimation(547, 548) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(528)->active = 0;

    while (stage_ContinueAnimation(548, 549) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(549, 550) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(550, 551) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(551, 552) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(552) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);
    scpPlayMot(girlGObj, 521);

    sceVu0SubVector(dir, test_CURRENTROOT(girlGObj), test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    sceVu0SubVector(dir, test_CURRENTROOT(boyGObj), test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    _ACTWait(1);

    iosOmSendMail(girlGObj, 58, boyGObj);

    scpBoyControlReadDisable = 0;

    ReinitWindManager();

    lt_switch_layout(50);

    SetStaticBlur(1);
}

/* .sdata: the other gate and torch stream handles, then the pad shakes and
   their volumes (declared in st04a.h for actSt04aConte06). */
static SqEntry *gate_open = 0; /* derived name */

static SqEntry *gate_open2 = 0; /* derived name */

static SqEntry *conte09_2 = 0; /* derived name */

SqEntry *torch = 0;

int gate_yure_low = 0;

unsigned char gate_yure_low_vol = 0;

int yure1 = 0;

unsigned char vol1 = 0;

void actSt04aConte06Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 250:
            jimaku_msg.sub.block = 25;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1400:
            jimaku_msg.sub.block = 26;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2380:
            jimaku_msg.sub.block = 31;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2861:
            jimaku_msg.sub.block = 34;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3160:
            jimaku_msg.sub.block = 35;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3460:
            jimaku_msg.sub.block = 36;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 3760:
            jimaku_msg.sub.block = 37;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4180:
            jimaku_msg.sub.block = 38;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 4800:
            jimaku_msg.sub.block = 43;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 5576:
            jimaku_msg.sub.block = 27;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6080:
            jimaku_msg.sub.block = 29;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6740:
            jimaku_msg.sub.block = 48;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 6980:
            jimaku_msg.sub.block = 49;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 7300.0f);
}

void actSt04aGateOpen(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(119) == 0) {
        stage_SetAnimation(213, 0, 0);

        scpSearchGobj(599)->active = 0;

        gate_open_mail[0].func = actSt04aGateOpenChk;
        act->mail = gate_open_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

        stage_SetAnimation(213, 0, -1);
        stage_SetAnimation(215, 0, -1);
        stage_SetAnimation(217, 0, -1);

        scpSearchGobj(599)->active = 0;
    }
}

void actSt04aGateOpenChk(GObj *volatile self)
{
    int i;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0 && gflagChk(148) != 0 &&
             gflagChk(209) != 0) ||
            (scpTriggerBall(self, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(self, girlGObj, 200.0f) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;

    StandbyStreamMotion(streamMotion[2].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(33, &gate_open, 1, 1, 1);
    while (gate_open == 0) {
        _ACTWait(1);
    }

    scpDispOffAllWithKind(19);

    actCreateSubThread(actConte09, 21);
    actCreateSubThread(actConte09Jimaku, 21);
}

static const ConstVec liftOfs1 = {{0.0f, 0.0f, 6000.0f, 1.0f}}; /* derived name */

static const ConstVec liftOfs2 = {{-5000.0f, 0.0f, 5300.0f, 1.0f}}; /* derived name */

void actConte09(GObj *volatile self)
{
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

    PlayStreamMotion();

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    stage_SetAnimation(591, 1, 0);

    while (stage_ContinueAnimation(591, 592) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(592, 593) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(220, 1, 0);

    while (stage_ContinueAnimation(593, 594) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(594, 595) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(213, 1, 0);

    while (stage_ContinueAnimation(595, 596) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(596, 597) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(597, 598) == 0) {
        _ACTWait(1);
    }

    _ACTWait(300);

    stage_SetAnimation(217, 1, 0);

    _ACTWait(120);

    yure1 = iosPadActRequest(boyPad, 10);
    vol1 = 128;
    iosPadActVolumeSet(yure1, 128);

    while (stage_ContinueAnimation(598, 599) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(215, 1, 0);

    while (stage_ContinueAnimation(599, 600) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(yure1);

    while (stage_ContinueAnimation(600, 601) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(601, 602) == 0) {
        _ACTWait(1);
    }

    scpDispOnAllWithKind(19);

    gflagOn(119);

    while (stage_ContinueAnimation(602, 603) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFinish(603) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);

    _ACTWait(1);

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    SetWayGroupActive(2, 1);
}

void actConte09Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 2161:
            jimaku_msg.sub.block = 88;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2550:
            jimaku_msg.sub.block = 86;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 2700.0f);
}

void actConte09_2(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

    PlayStreamMotion();

    stage_SetAnimation(604, 1, 0);
    stage_SetAnimation(221, 1, 0);

    while (stage_ContinueAnimation(604, 605) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(605, 606) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(606, 607) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(607, 608) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(608, 609) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(609, 610) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(610, 611) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(611, 612) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(612, 613) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(216, 1, 0);

    while (stage_ContinueAnimation(613, 614) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(614, 615) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(615, 616) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(616, 617) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(617, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMotReq(girlGObj, 270);

    scpPlayPosSet(girlGObj, -14.0f, 238.0f, 4843.0f);

    ofs[0] = liftOfs1.d[0];
    ofs[1] = liftOfs1.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(girlGObj));
    scpPlayMotDir(girlGObj, dir);

    while (stage_CheckAnimationFinish(617) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    StandbyStreamMotion(streamMotion[4].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(35, &conte09_2, 1, 1, 0);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOn(120);
}

void actSt04aGateOpen3Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(120) == 0 || scpTriggerBall(self, boyGObj, 450.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(121);

    lt_switch_layout(51);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    if (gate_open2 != 0) {
        scpAdpcmFadeClose(gate_open2, 80);
    }

    while (conte09_2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(conte09_2->stream);

    actCreateSubThread(actConte09_3, 21);
    actCreateSubThread(actConte09_3Jimaku, 21);
}

void actConte09_3(GObj *volatile self)
{
    scpSearchGobj(599)->active = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion(scpSearchGobj(599));

    PlayStreamMotion();

    stage_SetAnimation(618, 1, 0);

    stage_SetAnimation(216, 1, 501);

    while (stage_ContinueAnimation(618, 619) == 0) {
        _ACTWait(1);
    }

    if (scpGameStat_BoyWeaponkind() == 1) {
        stage_SetAnimation(218, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 4 || scpGameStat_BoyWeaponkind() == 5) {
        stage_SetAnimation(219, 1, 0);
    }

    DeleteBoyWeapon();

    while (stage_ContinueAnimation(619, 620) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(620, 621) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(621, 622) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(622, 623) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(623, 624) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(624, 625) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(625, 626) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.35f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(626, 627) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(627, 628) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(216, 1, 2101);

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.4f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(628, 629) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.5f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_CheckAnimationFrame(629, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(629, 630) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(630, 631) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.55f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(631, 632) == 0) {
        _ACTWait(1);
    }

    tex_SetUVScroll("bridge_shadow", 0.0f, -0.6f, 0.0f, -0.001f, 0.0f, -0.7f, 1);

    while (stage_ContinueAnimation(632, 633) == 0) {
        _ACTWait(1);
    }

    gflagOn(123);
    gflagOn(340);

    _ACTWait(120);

    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

void actSt04aGateRChk(GObj *volatile self)
{
    while (gflagChk(200) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(118);

    scpAdpcmPlayRequestFunc(32, 0, 1, 1, 1);

    stage_SetAnimation(235, 1, 0);
    while (stage_CheckAnimationFinish(235) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    if (gflagChk(212) != 0) {
        RequestStageChange(5, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(213) != 0) {
        RequestStageChange(6, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(214) != 0) {
        RequestStageChange(9, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(215) != 0) {
        RequestStageChange(7, boyGObj, girlGObj, 16.0f, 16.0f);
    }
    if (gflagChk(199) != 0) {
        RequestStageChange(8, boyGObj, girlGObj, 16.0f, 16.0f);
    }
}

void actSt04aTorch1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(132) == 0) {
        if (gflagChk(124) != 0) {
            scpSearchGobj(501)->active = 0;
            stage_SetAnimation(223, 0, -1);
        }

        if (gflagChk(125) != 0) {
            scpSearchGobj(502)->active = 0;
            stage_SetAnimation(224, 0, -1);
        }

        if (gflagChk(126) != 0) {
            scpSearchGobj(503)->active = 0;
            stage_SetAnimation(225, 0, -1);
        }

        if (gflagChk(127) != 0) {
            scpSearchGobj(504)->active = 0;
            stage_SetAnimation(226, 0, -1);
        }

        if (gflagChk(128) != 0) {
            scpSearchGobj(505)->active = 0;
            stage_SetAnimation(227, 0, -1);
        }

        if (gflagChk(129) != 0) {
            scpSearchGobj(506)->active = 0;
            stage_SetAnimation(228, 0, -1);
        }

        if (gflagChk(130) != 0) {
            scpSearchGobj(507)->active = 0;
            stage_SetAnimation(229, 0, -1);
        }

        if (gflagChk(131) != 0) {
            scpSearchGobj(508)->active = 0;
            stage_SetAnimation(230, 0, -1);
        }

        torch1_mail[0].func = actSt04aTorch1Chk;
        act->mail = torch1_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    } else {
        scpSearchGobj(501)->active = 0;
        scpSearchGobj(502)->active = 0;
        scpSearchGobj(503)->active = 0;
        scpSearchGobj(504)->active = 0;
        scpSearchGobj(505)->active = 0;
        scpSearchGobj(506)->active = 0;
        scpSearchGobj(507)->active = 0;
        scpSearchGobj(508)->active = 0;

        stage_SetAnimation(223, 0, -1);
        stage_SetAnimation(224, 0, -1);
        stage_SetAnimation(225, 0, -1);
        stage_SetAnimation(226, 0, -1);
        stage_SetAnimation(227, 0, -1);
        stage_SetAnimation(228, 0, -1);
        stage_SetAnimation(229, 0, -1);
        stage_SetAnimation(230, 0, -1);

        scpTorchLightOn(509);
        scpTorchLightOn(510);
        scpTorchLightOn(511);
        scpTorchLightOn(512);
        scpTorchLightOn(513);
        scpTorchLightOn(514);
        scpTorchLightOn(515);
        scpTorchLightOn(516);
        scpTorchLightOn(517);
        scpTorchLightOn(518);
    }
}

void actSt04aTorch1Chk(GObj *volatile self)
{
    GObj *x = self;
    ActSt04A *act = (ActSt04A *)actInitialize(self);
    _ACTWait(1);

    switch (self->labelId) {
    case 493:
        act->torchFlag = 124;
        act->torchObj = scpSearchGobj(501);
        act->torchAnim = 223;
        actCreateSubThread(actSt04aTorchAllFlagfChk, 21);
        break;
    case 494:
        act->torchFlag = 125;
        act->torchObj = scpSearchGobj(502);
        act->torchAnim = 224;
        break;
    case 495:
        act->torchFlag = 126;
        act->torchObj = scpSearchGobj(503);
        act->torchAnim = 225;
        break;
    case 496:
        act->torchFlag = 127;
        act->torchObj = scpSearchGobj(504);
        act->torchAnim = 226;
        break;
    case 497:
        act->torchFlag = 128;
        act->torchObj = scpSearchGobj(505);
        act->torchAnim = 227;
        break;
    case 498:
        act->torchFlag = 129;
        act->torchObj = scpSearchGobj(506);
        act->torchAnim = 228;
        break;
    case 499:
        act->torchFlag = 130;
        act->torchObj = scpSearchGobj(507);
        act->torchAnim = 229;
        break;
    case 500:
        act->torchFlag = 131;
        act->torchObj = scpSearchGobj(508);
        act->torchAnim = 230;
        break;
    }

    while (1) {
        if (scpTriggerBall(self, act->torchObj, 5.0f) != 0) {
            scpBoyControlReadDisable = 1;

            act->torchObj->active = 0;

            stage_SetAnimation(act->torchAnim, 1, 0);

            while (stage_CheckAnimationFinish(act->torchAnim) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            gflagOn(act->torchFlag);

            scpBoyControlReadDisable = 0;
            break;
        }
        _ACTWait(1);
    }
}

void actSt04aTorchAllFlagfChk(GObj *volatile self)
{
    while (gflagChk(124) == 0 || gflagChk(125) == 0 || gflagChk(126) == 0 || gflagChk(127) == 0 ||
           gflagChk(128) == 0 || gflagChk(129) == 0 || gflagChk(130) == 0 || gflagChk(131) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    gflagOn(132);
    scpAdpcmPlayRequestFunc(78, &torch, 1, 1, 1);
    while (torch == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(222, 1, 0);
    while (stage_CheckAnimationFrame(222, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpTorchLightOn(509);
    scpTorchLightOn(510);
    scpTorchLightOn(511);
    scpTorchLightOn(512);
    scpTorchLightOn(513);
    scpTorchLightOn(514);
    scpTorchLightOn(515);
    scpTorchLightOn(516);
    scpTorchLightOn(517);
    scpTorchLightOn(518);

    while (stage_CheckAnimationFinish(222) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(60);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt04aGateL(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(117) == 0) {
        stage_SetAnimation(235, 0, 0);

        gate_l_mail[0].func = actSt04aGateLChk;
        act->mail = gate_l_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04aGateR(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(118) == 0) {
        stage_SetAnimation(233, 0, -1);

        gate_r_mail[0].func = actSt04aGateRChk;
        act->mail = gate_r_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04aTorchXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    stage_SetAnimation(231, 0, 0);
}

void actSt04aGateOpen2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(120) == 0) {
        scpSearchGobj(599)->active = 0;

        gate_open2_mail[0].func = actSt04aGateOpen2Chk;
        act->mail = gate_open2_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04aGateOpen3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    if (gflagChk(121) == 0) {
        stage_SetAnimation(218, 0, -1);
        stage_SetAnimation(219, 0, -1);

        gate_open3_mail[0].func = actSt04aGateOpen3Chk;
        act->mail = gate_open3_mail;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt04aGateOpen2Ready(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    gate_open2_ready_mail[0].func = actSt04aGateOpen2ReadyChk;
    act->mail = gate_open2_ready_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04aGirlSit(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);
    _ACTWait(1);

    girl_sit_mail[0].func = actSt04aGirlSitChk;
    act->mail = girl_sit_mail;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt04aGateOpen2ReadyChk(GObj *volatile self)
{
    GObj *x = self;
    int i;

    actInitialize(self);
    _ACTWait(1);

    while (scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(streamMotion[3].path);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(34, &gate_open2, 1, 1, 0);
}

void actSt04aGateOpen2Chk(GObj *volatile self)
{
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || ACTGame_FLAG_TETSUNAGI() == 0) {
        _ACTWait(1);
    }

    GOBJ_ACT(girlGObj)->flags20.ll &= ~2;
    scpPlayMotReq(girlGObj, 270);

    lt_switch_layout(51);

    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpDisActivateAllWithKind(19);

    while (gate_open2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(gate_open2->stream);

    actCreateSubThread(actConte09_2, 21);
}

void actConte09_3Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            jimakuBegin(&jimaku_msg);
            break;
        case 2530:
            jimaku_msg.sub.block = 91;
            jimaku_msg.sub.jump = 300;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((60 - systemStatus[0] * 10) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 3000.0f);
}

void actSt04aGateLChk(GObj *volatile self)
{
    while (gflagChk(148) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);

    scpBoyControlReadDisable = 1;
    gflagOn(117);

    scpAdpcmPlayRequestFunc(31, 0, 1, 1, 1);

    stage_SetAnimation(233, 1, 0);
    while (stage_CheckAnimationFinish(233) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actSt04aGirlSitChk(GObj *volatile self)
{
    int n;

    while (gflagChk(119) == 0) {
        _ACTWait(1);
    }
    GOBJ_ACT(girlGObj)->flags20.ll |= 2;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 4) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((60 - systemStatus[0] * 10) / systemStatus[1]) * 3 < n) {
            iosOmSendMail(girlGObj, 100, girlGObj);
            n = 0;
        }
        _ACTWait(1);
    }
}
