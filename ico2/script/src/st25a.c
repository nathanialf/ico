#include "st25a.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "gobj_process.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "queen.h"
#include "camera-ico2.h"
#include "camera-root.h"
#include "fightSound.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "Texture.h"
#include "boy.h"
#include "geometryManager.h"
#include "motionManager2.h"
#include "streamMotionManager.h"
#include <libvu0.h>
#include <string.h>
#include "e3.h"
#include "typedef.h"
#include "layout_action.h"
#include "main.h"
#include "script.h"
#include "jimaku.h"

/* .sdata: the texture script.c's scpObj1882 scrolls (the TU's .sdata opens
   with it, 8-aligned, at the demo's 0x67A020), then the ADPCM request slots
   the scenes hand scpAdpcmPlayRequestFunc and wait on. */
const char wall01Tex[] = "wall01"; /* derived name */

static SqEntry *conte11 = 0; /* derived name */

SqEntry *conte12 = 0;

SqEntry *sd2 = 0;

/* the second half of conte12's stream: actSt25aObj1881 (or its check)
   requests it, actSt25aObj1896Chk plays it */
static SqEntry *conte12b = 0; /* derived name */

SqEntry *dead = 0;

/* five words in this build: the demo's .sdata of the TU has no room for PAL's
   two elevator slots (elevAgain, elevFirst) */

/* stream-motion-def's table; streamMotionManager.h, which defines the
   record, does not declare it */
extern StreamMotionFile streamMotion[];

/* this file's own view of Vec4 (the shared one is in typedef.h) */
typedef union Vec4St25A { /* derived name */ /* field names derived */
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) Vec4St25A; /* derived name */

/* the two face-shadow textures actConte11 and actSt25aObj1881 scroll the UVs
   of. */
const char faceShadowTex[] = "face_sadow_sd";

const char faceShadowTex00[] = "face_sadow_sd_00";

/* The offset the sekika boy is dropped by. */
static const Vec4St25A sekikaOfs = {{2000.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static const char streamWaitFmt[] =
    "Now waiting for standby stream motion system... %d\n"; /* derived name */

static const char queenBallScrTexture[] = "queen_ball_scr"; /* derived name */

static const char sekikaBoyTexture[] = "sekika_boy"; /* derived name */

/* .data: eight actor mail records.  Each is the usual pair, the 377 entry
   whose handler the sender fills in and the 376 terminator (this build's mail
   numbers).  queen_before_mes is the only one another TU sends (script.c's
   scpObj1882), so it is the only global of the eight; the three objN_mes are
   the records of obj-layout rows 1881, 1880 and 1896's processes. */
ActMail queen_before_mes[2] = {{377}, {376}};

static ActMail queen_appear_mes[2] = {{377}, {376}}; /* derived name */

static ActMail queen_talk_mes[2] = {{377}, {376}}; /* derived name */

static ActMail obj1881_mes[2] = {{377}, {376}}; /* derived name */

static ActMail obj1880_mes[2] = {{377}, {376}}; /* derived name */

static ActMail obj1896_mes[2] = {{377}, {376}}; /* derived name */

static ActMail queen_dead_mes[2] = {{377}, {376}}; /* derived name */

static ActMail queen_attack_mes[2] = {{377}, {376}}; /* derived name */

void actItouQueenAttackChk(GObj *volatile self);
void actConte11Jimaku(GObj *volatile self);
void actSt25aObj1881Chk(GObj *volatile self);
void actSt25aObj1880Chk(GObj *volatile self);
void actConte12Jimaku2(GObj *volatile self);

void actConte11(GObj *volatile self)
{
    Vec4St25A ofs;
    float dir[4];

    lt_switch_layout(51);
    scpPlayStart(boyGObj);

    stage_SetAnimation(642, 1, 0);
    stage_SetAnimation(121, 1, 0);

    scpPlayMot(boyGObj, 405);
    scpSearchGobj(1863)->active = 1;
    scpPlayMot(scpSearchGobj(1863), 1123);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(642, 643) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(643, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    scpPlayMot(scpSearchGobj(1863), 1124);

    scpPlayMot(boyGObj, 0);
    ofs = sekikaOfs;
    sceVu0SubVector(dir, &ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(643) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actSt25aQueenTalkChk(GObj *volatile self)
{
    unsigned int i;

    conte12 = sd2 = 0;

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0 || gflagChk(287) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayMot(boyGObj, 0);

    StandbyStreamMotion(streamMotion[6].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }

    gflagOn(288);

    scpAdpcmPlayRequestFunc(42, &conte12, 1, 1, 1);
    while (conte12 == 0) {
        _ACTWait(1);
    }

    actCreateSubThread(actConte12, 21);
    actCreateSubThread(actConte12Jimaku, 21);
}

void actConte12(GObj *volatile self)
{
    conte12b = 0;

    scpSearchGobj(1863)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1863));
    PlayStreamMotion();

    stage_SetAnimation(662, 1, 0);
    while (stage_ContinueAnimation(662, 663) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(663, 664) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(664, 665) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(665, 666) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(666, 667) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(667, 668) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(668, 669) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(669, 670) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(670, 671) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(671, 672) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFinish(672) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    gflagOn(290);

    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);
}

void actConte12Jimaku(GObj *volatile self)
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
        case 341:
            jimaku_msg.sub.block = 96;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 521:
            jimaku_msg.sub.block = 97;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 801:
            jimaku_msg.sub.block = 98;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1031:
            jimaku_msg.sub.block = 99;
            jimaku_msg.sub.jump = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1301:
            jimaku_msg.sub.block = 100;
            jimaku_msg.sub.jump = 200;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1781:
            jimaku_msg.sub.block = 104;
            jimaku_msg.sub.jump = 200;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2261:
            jimaku_msg.sub.block = 105;
            jimaku_msg.sub.jump = 150;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 2561:
            jimaku_msg.sub.block = 106;
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
    } while (t < 3000.0f);
}

/* obj-layout row 1881's process: until flag 290 is set (the end of
   actConte12) it hands the actor obj1881_mes; after it, it puts the scene
   back as the first half of the conte left it and readies the second. */
void actSt25aObj1881(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *sub = actInitialize(self);
    unsigned int i;

    _ACTWait(1);

    conte12b = 0;

    if (gflagChk(290) == 0) {
        obj1881_mes[0].func = actSt25aObj1881Chk;
        sub->mail = obj1881_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
        return;
    }

    stage_SetAnimation(121, 0, -1);
    scpSearchGobj(1872)->active = 0;
    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    scpPlayPosSet(scpSearchGobj(1934), 100.0f, 850.0f, -400.0f);
    scpPlayPosSet(scpSearchGobj(1935), 100.0f, 850.0f, 400.0f);
    scpPlayMot(scpSearchGobj(1863), 1123);

    StandbyStreamMotion(streamMotion[7].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        debug_StdPrintfDummy(streamWaitFmt, ++i);
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(43, &conte12b, 1, 1, 0);

    gflagOn(291);
    jimakuBegin(&jimaku_msg);
}

/* the second half of conte12, posted by obj-layout row 1896's process: when
   flag 291 is raised (actSt25aObj1880Chk) it plays the scene to the queen's
   attack, then hands the boy back. */
void actSt25aObj1896Chk(GObj *volatile self) /* derived name */
{
    Vec4St25A pos;
    Vec4St25A dir;

    while (gflagChk(291) == 0) {
        _ACTWait(1);
    }
    gflagOn(332);
    gflagOff(291);
    CheckPoint();
    gflagOff(332);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayMot(boyGObj, 0);
    scpPlayStart(boyGObj);
    scpPlayStart(scpSearchGobj(1863));

    while (conte12b == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(conte12b->stream);

    scpSearchGobj(1863)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1863));
    PlayStreamMotion();

    actCreateSubThread(actConte12Jimaku2, 21);

    stage_SetAnimation(673, 1, 0);
    while (stage_ContinueAnimation(673, 674) == 0) {
        _ACTWait(1);
    }

    DeleteBoyWeapon();
    stage_SetAnimation(122, 1, 0);

    iosPadActRequest(boyPad, 15);
    while (stage_CheckAnimationFrame(674, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(674, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);
    while (stage_CheckAnimationFrame(674, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);
    while (stage_CheckAnimationFrame(674, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 16);

    while (stage_ContinueAnimation(674, 675) == 0) {
        _ACTWait(1);
    }

    scpLinkBGAtoLayoutedTarget(1872, 387);

    while (stage_ContinueAnimation(675, 676) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(676, 677) == 0) {
        _ACTWait(1);
    }

    _ACTWait(15);
    scpSearchGobj(1872)->active = 1;
    stage_SetAnimation(122, -1, -2);

    while (stage_ContinueAnimation(677, 678) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(678, 679) == 0) {
        _ACTWait(1);
    }

    QueenStartAttack();
    gflagOn(289);

    while (stage_CheckAnimationFinish(679) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(scpSearchGobj(1863), 1091);
    scpPlayPosSet(scpSearchGobj(1863), 1650.0f, 625.0f, 0.0f);

    memset(pos.f, 0, 16);
    pos.f[3] = 1.0f;
    sceVu0SubVector(dir.f, pos.f, test_CURRENTROOT(scpSearchGobj(1863)));
    scpPlayMotDir(scpSearchGobj(1863), dir.f);
    scpPlayEnd(scpSearchGobj(1863));

    scpPlayMot(boyGObj, 0);
    scpPlayEnd(boyGObj);
    scpBoyControlReadDisable = 0;
    lt_switch_layout(50);

    CameraSetCameraSet(51);

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(44, &sd2, 1, 0, 1);

    stage_SetAnimation(124, -1, -2);

    stage_SetLoopFlag(125, 1);

    stage_SetAnimation(125, 1, 0);
}

void actSt25aQueenDeadChk(GObj *volatile self)
{
    unsigned int i;

    dead = 0;
    while (1) {
        if (gflagChk(289) != 0 && scpGameStat_BoyWeaponkind() == 5 &&
            scpTriggerBall(self, boyGObj, 150.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 51 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 52 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 53 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 54 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 62)) {
            break;
        }
        _ACTWait(1);
    }

    iosPadActRequest(boyPad, 16);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(scpSearchGobj(1863));

    StandbyStreamMotion(streamMotion[8].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }

    if (sd2 != 0) {
        scpAdpcmFadeClose(sd2, 256);
    }

    scpKillEnemyAll();

    gflagOn(292);
    gflagOn(5);

    scpAdpcmPlayRequestFunc(45, &dead, 1, 1, 1);
    while (dead == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(1863)->active = 1;
    EntryStreamMotion(boyGObj);
    EntryStreamMotion(scpSearchGobj(1863));
    PlayStreamMotion();

    actCreateSubThread(actConte13Jimaku, 21);

    stage_SetAnimation(680, 1, 0);

    scpSearchGobj(1934)->active = 0;
    scpSearchGobj(1935)->active = 0;

    while (stage_ContinueAnimation(680, 681) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(681, 682) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(682, 683) == 0) {
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(1863))->streamScale = 0;
    while (stage_ContinueAnimation(683, 684) == 0) {
        _ACTWait(1);
    }

    GOBJ_SUB(scpSearchGobj(1863))->streamScale = 1;
    while (stage_ContinueAnimation(684, 685) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(685, 686) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(378, 1, 0);
    iosPadActRequest(boyPad, 15);
    DeleteBoyWeapon();
    stage_SetAnimation(123, 1, 0);

    while (stage_ContinueAnimation(686, 687) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(687, 688) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(688, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 17);

    while (stage_ContinueAnimation(688, 689) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(689, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(boyPad, 15);

    scpSearchGobj(1863)->active = 0;

    while (stage_ContinueAnimation(689, 691) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFinish(691) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, 0, 16.0f, 16.0f);
}

void actConte13Jimaku(GObj *volatile self)
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
        case 600:
            jimaku_msg.sub.block = 110;
            jimaku_msg.sub.jump = 400;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 1320:
            jimaku_msg.sub.block = 111;
            jimaku_msg.sub.jump = 200;
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
    } while (t < 3100.0f);
}

void BoySekikaTexScroll(void)
{
    tex_SetUVScroll(sekikaBoyTexture, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.5f, 1);
}

/* obj-layout row 1880's process: hands the actor obj1880_mes */
void actSt25aObj1880(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    obj1880_mes[0].func = actSt25aObj1880Chk;
    sub->mail = obj1880_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt25aGenerator(GObj *volatile self)
{
    Generator_Mask(self);
}

void actSt25aQueenAppear(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(287) == 0) {
        scpSearchGobj(1863)->active = 0;
        queen_appear_mes[0].func = actSt25aQueenAppearChk;
        sub->mail = queen_appear_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt25aQueenTalk(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(288) == 0) {
        scpSearchGobj(1872)->active = 0;
        queen_talk_mes[0].func = actSt25aQueenTalkChk;
        sub->mail = queen_talk_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actSt25aQueenDead(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    queen_dead_mes[0].func = actSt25aQueenDeadChk;
    sub->mail = queen_dead_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

/* obj-layout row 1896's process: pauses the fight sound and hands the actor
   obj1896_mes */
void actSt25aObj1896(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    fightSoundProcessRequestPause();

    obj1896_mes[0].func = actSt25aObj1896Chk;
    sub->mail = obj1896_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actItouQueenAttack(GObj *volatile self)
{
    GObj *x = self;
    Act *sub = actInitialize(self);

    _ACTWait(1);

    queen_attack_mes[0].func = actItouQueenAttackChk;
    sub->mail = queen_attack_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSwordEff(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTarget(1826, 387);
}

void actSwordEffXL(GObj *volatile self)
{
    GObj *x = self;

    actInitialize(self);
    _ACTWait(1);

    if (scpGameStat_BoyWeaponkind() == 5) {
        scpLinkBGAtoLayoutedTarget(1826, 387);
    } else {
        stage_SetAnimation(387, -1, -2);
    }
}

void actSt25aQueenBeforeChk(GObj *volatile self)
{
    conte11 = 0;
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(286);
    jimakuBegin(&jimaku_msg);
    scpAdpcmPlayRequestFunc(41, &conte11, 1, 1, 0);
}

void actSt25aQueenAppearChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x2000000) == 0 || gflagChk(286) == 0) {
        _ACTWait(1);
    }
    gflagOn(287);
    actCreateSubThread(actConte11Jimaku, 21);
    while (conte11 == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(conte11->stream);
    scpBoyControlReadDisable = 1;
    _ACTWait(120);
    actCreateSubThread(actConte11, 21);
}

void actConte11Jimaku(GObj *volatile self)
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 1:
            break;
        case 10:
            jimaku_msg.sub.block = 93;
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
    } while (t < 1500.0f);
}

/* obj-layout row 1881's check: when actConte12 has run (flag 290) it readies
   the second half's stream motion and requests its stream */
void actSt25aObj1881Chk(GObj *volatile self) /* derived name */
{
    unsigned int i;

    while (gflagChk(290) == 0) {
        _ACTWait(1);
    }
    StandbyStreamMotion(streamMotion[7].path);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(43, &conte12b, 1, 1, 0);
}

/* obj-layout row 1880's check: the boy swinging the sword (weapon kind 5)
   within reach of the object after flag 287 raises flag 291 */
void actSt25aObj1880Chk(GObj *volatile self) /* derived name */
{
    while (1) {
        if (gflagChk(287) != 0 && scpGameStat_BoyWeaponkind() == 5 &&
            scpTriggerBall(self, boyGObj, 150.0f) != 0 &&
            (ForMotionViewer_GetCurrentMotion(boyGObj) == 51 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 52 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 53 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 54 ||
             ForMotionViewer_GetCurrentMotion(boyGObj) == 62)) {
            break;
        }
        _ACTWait(1);
    }
    gflagOn(291);
}

/* the subtitles of conte12's second half */
void actConte12Jimaku2(GObj *volatile self) /* derived name */
{
    float t;
    float tn;
    int n;

    t = 0.0f;
    do {
        switch ((int)t) {
        case 575:
            jimaku_msg.sub.block = 109;
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
    } while (t < 3100.0f);
}

void actSt25aQueenDeadEvent(int x)
{
    volatile int local = x;
}

void actItouQueenAttackChk(GObj *volatile self)
{
    while (1) {
        while (ForMotionViewer_GetCurrentMotion(scpSearchGobj(3064)) != 1097) {
            _ACTWait(1);
        }
        tex_SetUVScroll(queenBallScrTexture, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 1);
        _ACTWait(1);
    }
}
