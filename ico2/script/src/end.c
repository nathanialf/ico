#include "end.h"
#include "mcard.h"
#include "layout_texture.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "boyact.h"
#include "commonact.h"
#include "jimaku.h"
#include "camera-root.h"
#include "gflag.h"
#include "RegistPacket.h"
#include "StageAnimation.h"
#include "boy.h"
#include "girl.h"
#include "item.h"
#include "staticBlur.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"
#include "layout_action.h"
#include "GsBase.h"
#include "main.h"
#include "script.h"
#include "staffroll.h"

/* .sdata: the ending scenes' stream handles, then the fourteenth demo's and
   the st27a ending's. */
SqEntry *ed1 = 0;

SqEntry *ed2 = 0;

SqEntry *ed3 = 0;

SqEntry *ed4 = 0;

SqEntry *ed5 = 0;

SqEntry *ed6 = 0;

static SqEntry *endDemo14 = 0; /* derived name */

static SqEntry *st27aEnd = 0; /* derived name */

static ActMail demo01_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo02_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo03_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo04_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo05_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo06_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo07_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo10_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo11_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo12_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo13_mes[2] = {{397}, {396}}; /* derived name */

static ActMail staff1_mes[2] = {{397}, {396}}; /* derived name */

static ActMail staff2_mes[2] = {{397}, {396}}; /* derived name */

static ActMail staff3_mes[2] = {{397}, {396}}; /* derived name */

static ActMail demo14_mes[2] = {{397}, {396}}; /* derived name */

static ActMail st27aEnd_mes[2] = {{397}, {396}}; /* derived name */

static ActMail logo_mes[2] = {{397}, {396}}; /* derived name */

void actEndDemo01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(308) == 0 && gflagChk(312) == 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(766, 0, 0);
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(33, 0, -1);
        demo01_mes[0].func = actEndDemo01Chk;
        act->mail = demo01_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actConte14_1(GObj *volatile self)
{
    scpPlayStart(boyGObj);

    stage_SetAnimation(740, 1, 0);

    scpPlayMot(scpSearchGobj(2307), 764);

    scpSearchGobj(2307)->active = 1;

    while (stage_ContinueAnimation(740, 741) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(741, 742) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(52, 1, 0);

    while (stage_ContinueAnimation(742, 743) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(743, 744) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(744, 745) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2307), 765);

    while (stage_ContinueAnimation(745, 746) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(2307)->active = 0;

    scpPlayMot(scpSearchGobj(2308), 766);

    scpSearchGobj(2308)->active = 1;

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2308, 0, 483, 0);

    stage_SetLoopFlag(483, 1);

    stage_SetAnimation(483, 1, 0);

    while (stage_ContinueAnimation(746, 747) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2308), 767);

    while (stage_ContinueAnimation(747, 748) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2308), 768);

    while (stage_ContinueAnimation(748, 749) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2308), 769);

    while (stage_CheckAnimationFinish(749) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, 0, 1.0f, 8.0f);
}

void actEndDemo02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 483, 0);
    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);
    stage_SetAnimation(751, 0, 0);
    stage_SetAnimation(485, 0, -1);
    stage_SetAnimation(486, 0, -1);
    stage_SetAnimation(488, 0, -1);
    stage_SetAnimation(489, 0, -1);
    stage_SetAnimation(490, 0, -1);
    SelectBoyCrown(boyGObj, 2);
    demo02_mes[0].func = actEndDemo02Chk;
    act->mail = demo02_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actConte14_2(GObj *volatile self)
{
    scpPlayStart(boyGObj);

    stage_SetAnimation(750, 1, 0);

    scpPlayMot(boyGObj, 435);

    while (stage_ContinueAnimation(750, 751) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(751, 752) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2470), 770);

    scpSearchGobj(2470)->active = 1;

    _ACTWait(1);

    stage_SetAnimation(753, 1, 0);

    while (stage_ContinueAnimation(752, 754) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 436);

    scpPlayMot(scpSearchGobj(2470), 771);

    while (stage_ContinueAnimation(754, 755) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 437);

    scpPlayMot(scpSearchGobj(2470), 772);

    while (stage_ContinueAnimation(755, 756) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 438);

    scpPlayMot(scpSearchGobj(2470), 773);

    while (stage_ContinueAnimation(756, 757) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 439);

    scpPlayMot(scpSearchGobj(2470), 774);

    _ACTWait(1);

    stage_SetAnimation(758, 1, 0);

    while (stage_CheckAnimationFinish(757) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(boyGObj);

    lt_switch_layout(50);

    RequestStageChange(3, boyGObj, 0, 1.0f, 8.0f);
}

void actEndDemo06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(313) == 0 && gflagChk(312) != 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2308, 0, 483, 0);
        stage_SetLoopFlag(483, 1);
        stage_SetAnimation(483, 1, 0);
        stage_SetAnimation(766, 0, 0);
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(33, 0, -1);
        SelectBoyCrown(boyGObj, 2);
        demo06_mes[0].func = actEndDemo06Chk;
        act->mail = demo06_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actConte14_6(GObj *volatile self)
{
    preload(3);

    scpPlayStart(boyGObj);

    stage_SetAnimation(764, 1, 0);

    stage_SetAnimation(766, 1, 0);

    stage_SetAnimation(767, 1, 0);

    scpPlayMot(boyGObj, 440);

    scpPlayMot(scpSearchGobj(2308), 775);

    scpSearchGobj(2308)->active = 1;

    while (stage_ContinueAnimation(764, 765) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 441);

    scpPlayMot(scpSearchGobj(2308), 776);

    while (stage_CheckAnimationFinish(765) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 483, 0);
    stage_SetAnimation(152, 0, 0);
    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);

    if (gflagChk(314) == 0) {
        SelectBoyCrown(boyGObj, 2);
        demo07_mes[0].func = actEndDemo07Chk;
        act->mail = demo07_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

/* 16-byte constant vector templates: the float view carries the values, the
   long long view is the one the copy reads. */

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}}; /* derived name */

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

static const ConstVec conte14_14Pos = {{16975.0f, 71.0f, -4332.0f, 1.0f}}; /* derived name */

void actConte14_7(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    preload(6);

    scpPlayStart(boyGObj);

    stage_SetAnimation(768, 1, 0);

    stage_SetAnimation(152, 1, 471);

    _ACTWait(1);

    scpPlayPosSet(boyGObj, -4757.0f, -660.0f, 2646.0f);

    scpPlayPosSet(scpSearchGobj(2181), -4757.0f, -664.0f, 2646.0f);

    _ACTWait(1);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2181)));
    scpPlayMotDir(scpSearchGobj(2181), dir);

    scpPlayMotNode(boyGObj, 442, scpSearchGobj(2181), 44);

    scpPlayMot(scpSearchGobj(2181), 777);

    scpSearchGobj(2181)->active = 1;

    while (stage_CheckAnimationFinish(768) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo10(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 483, 0);
    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);
    SelectBoyCrown(boyGObj, 2);
    stage_SetAnimation(776, 0, 0);
    demo10_mes[0].func = actEndDemo10Chk;
    act->mail = demo10_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actConte14_10(GObj *volatile self)
{
    preload(3);

    scpPlayStart(boyGObj);

    stage_SetAnimation(769, 1, 0);

    scpPlayMot(boyGObj, 443);

    scpPlayMot(scpSearchGobj(1940), 778);

    scpSearchGobj(1940)->active = 1;

    _ACTWait(1);

    stage_SetAnimation(42, 1, 0);

    stage_SetAnimation(770, 1, 0);

    while (stage_ContinueAnimation(769, 771) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 444);

    scpPlayMot(scpSearchGobj(1940), 779);

    _ACTWait(1);

    stage_SetAnimation(43, 1, 0);

    while (stage_ContinueAnimation(771, 772) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 445);

    scpPlayMot(scpSearchGobj(1940), 780);

    _ACTWait(1);

    stage_SetAnimation(44, 1, 0);

    while (stage_ContinueAnimation(772, 773) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 446);

    scpPlayMot(scpSearchGobj(1940), 781);

    _ACTWait(1);

    stage_SetAnimation(45, 1, 0);

    while (stage_ContinueAnimation(773, 774) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 447);

    scpPlayMot(scpSearchGobj(1940), 782);

    _ACTWait(1);

    stage_SetAnimation(46, 1, 0);

    while (stage_ContinueAnimation(774, 775) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 448);

    _ACTWait(1);

    stage_SetAnimation(47, 1, 0);

    stage_SetAnimation(53, 1, 0);

    stage_SetAnimation(776, 1, 0);

    while (stage_ContinueAnimation(775, 777) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 449);

    _ACTWait(1);

    stage_SetAnimation(48, 1, 0);

    stage_SetAnimation(54, 1, 0);

    while (stage_CheckAnimationFinish(777) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actConte14_13(GObj *volatile self)
{
    scpPlayStart(boyGObj);

    scpFadeIn(3.0f);

    preload(6);

    stage_SetAnimation(780, 1, 0);

    scpPlayMot(boyGObj, 450);

    while (stage_ContinueAnimation(780, 781) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(50, 1, 0);

    stage_SetAnimation(402, 1, 0);

    scpPlayMot(boyGObj, 450);

    while (stage_CheckAnimationFinish(781) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(boyGObj);

    RequestStageChange(6, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actStaff1Demo(GObj *volatile self)
{
    preload(1);

    staffRollStart(1.0f, 255);

    stage_SetAnimation(523, 1, 0);

    while (stage_ContinueAnimation(523, 524) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(25, 1, 0);

    scpPlayMot(boyGObj, 282);

    while (stage_ContinueAnimation(524, 526) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(526, 527) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 283);

    _ACTWait(130);

    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(527, 528) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(528, 529) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 284);

    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 286);

    while (stage_ContinueAnimation(531, 532) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 287);

    while (stage_ContinueAnimation(532, 533) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 288);

    while (stage_ContinueAnimation(533, 534) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 289);

    while (stage_ContinueAnimation(534, 535) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 290);

    while (stage_ContinueAnimation(535, 536) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 291);

    while (stage_CheckAnimationFrame(536, 100, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(8.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, girlGObj, 0.0f, 8.0f);
}

void actStaff2Demo(GObj *volatile self)
{
    preload(1);

    stage_SetAnimation(577, 1, 0);

    stage_SetAnimation(238, 1, 0);

    scpPlayMot(boyGObj, 321);

    scpPlayMot(scpSearchGobj(2585), 692);

    scpSearchGobj(2585)->active = 1;

    while (stage_ContinueAnimation(577, 578) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 322);

    scpPlayMot(scpSearchGobj(2585), 693);

    while (stage_ContinueAnimation(578, 579) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 323);

    scpPlayMot(scpSearchGobj(2585), 694);

    while (stage_ContinueAnimation(579, 580) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(580, 581) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 324);

    scpPlayMot(scpSearchGobj(2585), 695);

    while (stage_ContinueAnimation(581, 582) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 325);

    scpPlayMot(scpSearchGobj(2585), 696);

    while (stage_ContinueAnimation(582, 583) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 326);

    scpPlayMot(scpSearchGobj(2585), 697);

    while (stage_ContinueAnimation(583, 584) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 327);

    while (stage_ContinueAnimation(584, 599) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 335);

    scpPlayMot(scpSearchGobj(2585), 703);

    while (stage_ContinueAnimation(599, 600) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 336);

    scpPlayMot(scpSearchGobj(2585), 704);

    while (stage_ContinueAnimation(600, 601) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 337);

    scpPlayMot(scpSearchGobj(2585), 705);

    while (stage_ContinueAnimation(601, 602) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 338);

    scpPlayMot(scpSearchGobj(2585), 706);

    while (stage_CheckAnimationFrame(602, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    reg_SetScissorSw(0);

    SetStaticBlur(1);

    scpFadeOut(8.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, girlGObj, 0.0f, 8.0f);
}

void actStaff3Demo(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    stage_SetAnimation(554, 1, 0);

    scpPlayPosSet(scpSearchGobj(2637), -7.0f, -5725.0f, 18.0f);

    ofs[0] = staff3DemoPos.d[0];
    ofs[1] = staff3DemoPos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2637)));
    scpPlayMotDir(scpSearchGobj(2637), dir);

    scpPlayMot(scpSearchGobj(2637), 633);

    scpSearchGobj(2637)->active = 1;

    scpPlayMot(boyGObj, 302);

    while (stage_ContinueAnimation(554, 555) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 303);

    while (stage_ContinueAnimation(555, 556) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 304);

    while (stage_ContinueAnimation(556, 557) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 305);

    while (stage_ContinueAnimation(557, 565) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(61, 0, -1);

    scpPlayMot(scpSearchGobj(2637), 683);

    while (stage_ContinueAnimation(565, 566) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2637), 684);

    while (stage_ContinueAnimation(566, 567) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 312);

    scpPlayMot(scpSearchGobj(2637), 685);

    while (stage_ContinueAnimation(567, 568) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 313);

    scpPlayMot(scpSearchGobj(2637), 686);

    while (stage_ContinueAnimation(568, 570) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 314);

    scpPlayMot(scpSearchGobj(2637), 687);

    while (stage_CheckAnimationFrame(570, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(6.0f, 0, 0, 0);
}

void actEndDemo14(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    fbKeep = 1;
    scpFadeOut(3.0f, 255, 255, 255);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    fbKeep = 0;
    ScpCallCameraSetTarget(7046.0f, -77.0f, 1678.0f);

    scpAdpcmPlayRequestFunc(93, &endDemo14, 1, 0, 1);

    while (endDemo14 == 0) {
        _ACTWait(1);
    }

    SelectBoyCrown(boyGObj, 2);
    demo14_mes[0].func = actEndDemo14Chk;
    act->mail = demo14_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actConte14_14(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    scpPlayStart(boyGObj);

    scpFadeIn(6.0f);

    stage_SetAnimation(786, 1, 0);

    scpPlayMot(boyGObj, 455);

    while (stage_ContinueAnimation(786, 787) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 456);

    while (stage_ContinueAnimation(787, 788) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 457);

    _ACTWait(1);

    stage_SetAnimation(51, 1, 0);

    while (stage_ContinueAnimation(788, 789) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 458);

    while (stage_ContinueAnimation(789, 790) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 459);

    while (stage_ContinueAnimation(790, 791) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 460);

    scpPlayMot(scpSearchGobj(2067), 784);

    scpSearchGobj(2067)->active = 1;

    while (stage_CheckAnimationFinish(791) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(180);

    scpPlayMot(boyGObj, 0);

    ofs[0] = conte14_14Pos.d[0];
    ofs[1] = conte14_14Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOff(307);
}

void actSt27aEndChk(GObj *volatile self)
{
    float max;
    float t;

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);

    if (endDemo14 != 0) {
        scpAdpcmFadeCloseFunc(endDemo14, 27);
    }
    scpAdpcmPlayRequestFunc(49, &st27aEnd, 0, 1, 1);
    while (st27aEnd == 0) {
        _ACTWait(1);
    }

    gflagOn(323);

    actCreateSubThread(actSt27aEndDemo, 21);

    max = (float)((60 - systemStatus[0] * 10) / systemStatus[1] * 20);
    t = (float)((60 - systemStatus[0] * 10) / systemStatus[1] * 20);
    while (t > 0.0f) {
        scpSeEnvMasterVolRate = t / max;
        t -= 1.0f;
        _ACTWait(1);
    }
    scpSeEnvMasterVolRate = 0;
}

void actSt27aEndDemo(GObj *volatile self)
{
    stage_SetAnimation(792, 1, 0);

    scpPlayMot(boyGObj, 461);

    scpPlayMot(scpSearchGobj(2067), 785);

    scpSearchGobj(2067)->active = 1;

    while (stage_ContinueAnimation(792, 793) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 462);

    scpPlayMot(scpSearchGobj(2067), 786);

    while (stage_ContinueAnimation(793, 794) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 463);

    scpPlayMot(scpSearchGobj(2067), 787);

    while (stage_CheckAnimationFinish(794) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(1, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    demo03_mes[0].func = actEndDemo03Chk;
    act->mail = demo03_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actEndDemo04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    demo04_mes[0].func = actEndDemo04Chk;
    act->mail = demo04_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actEndDemo05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    demo05_mes[0].func = actEndDemo05Chk;
    act->mail = demo05_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actEndDemo11(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    SelectBoyCrown(boyGObj, 2);
    demo11_mes[0].func = actEndDemo11Chk;
    act->mail = demo11_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actEndDemo12(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    stage_SetAnimation(67, 0, -1);
    demo12_mes[0].func = actEndDemo12Chk;
    act->mail = demo12_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actEndDemo13(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 255, 255, 255);
    SelectBoyCrown(boyGObj, 2);
    demo13_mes[0].func = actEndDemo13Chk;
    act->mail = demo13_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actStaff1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    stage_SetAnimation(29, 0, 0);
    stage_SetAnimation(25, 0, 0);
    stage_SetAnimation(32, 0, 0);
    stage_SetAnimation(33, 0, 0);
    stage_SetAnimation(35, 0, 0);
    stage_SetAnimation(37, 0, 0);
    staff1_mes[0].func = actStaff1Chk;
    act->mail = staff1_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actStaff2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSetBoyWeaponGObj(scpSearchGobj(2591));
    stage_SetAnimation(238, 0, 0);
    stage_SetAnimation(258, 0, 0);
    staff2_mes[0].func = actStaff2Chk;
    act->mail = staff2_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actStaff3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    DeleteBoyWeapon();
    stage_SetAnimation(59, 0, 0);
    stage_SetAnimation(64, 0, 0);
    staff3_mes[0].func = actStaff3Chk;
    act->mail = staff3_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actSt27aEnd(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(323) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        act->mail = st27aEnd_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
}

void actEndLogo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    logo_mes[0].func = actEndLogoChk;
    act->mail = logo_mes;
    ACTSendMailCorrect(self, 397);
    _ACTWait(0);
}

void actEndDemo01Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(42, &ed1, 0, 1, 1);

    while (ed1 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(2);

    gflagOn(3);

    gflagOn(4);

    gflagOn(308);

    actCreateSubThread(actConte14_1, 21);
}

void actEndDemo02Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(43, &ed2, 0, 1, 1);

    while (ed2 == 0) {
        _ACTWait(1);
    }

    preload(3);

    scpFadeIn(6.0f);

    gflagOn(309);

    actCreateSubThread(actConte14_2, 21);
}

void actEndDemo03Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(44, &ed3, 0, 1, 1);

    while (ed3 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(310);

    actCreateSubThread(actConte14_3, 21);
}

void actConte14_3(GObj *volatile self)
{
    stage_SetAnimation(759, 1, 0);

    while (stage_CheckAnimationFinish(759) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, 0, 1.0f, 8.0f);
}

void actEndDemo04Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(45, &ed4, 0, 1, 1);

    while (ed4 == 0) {
        _ACTWait(1);
    }

    preload(5);

    scpFadeIn(6.0f);

    gflagOn(311);

    actCreateSubThread(actConte14_4, 21);
}

void actConte14_4(GObj *volatile self)
{
    stage_SetAnimation(760, 1, 0);

    while (stage_CheckAnimationFinish(760) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(5, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo05Chk(GObj *volatile self)
{
    gflagOn(312);

    actCreateSubThread(actConte14_5, 21);
}

void actConte14_5(GObj *volatile self)
{
    preload(6);

    stage_SetAnimation(761, 1, 0);

    while (stage_CheckAnimationFinish(761) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo06Chk(GObj *volatile self)
{
    gflagOff(308);

    gflagOff(312);

    actCreateSubThread(actConte14_6, 21);
}

void actEndDemo07Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(46, &ed5, 0, 1, 1);

    while (ed5 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOn(314);

    actCreateSubThread(actConte14_7, 21);
}

void actEndDemo10Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(47, &ed6, 0, 1, 1);

    while (ed6 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOn(317);

    actCreateSubThread(actConte14_10, 21);

    actCreateSubThread(actConte14_10_Jimaku, 21);
}

void actConte14_10_Jimaku(GObj *volatile self)
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
        case 1500:
            jimaku_msg.sub.block = 112;
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
    } while (t < 1800.0f);
}

void actEndDemo11Chk(GObj *volatile self)
{
    gflagOn(318);

    actCreateSubThread(actConte14_11, 21);
}

void actConte14_11(GObj *volatile self)
{
    preload(2);

    scpPlayStart(boyGObj);

    stage_SetAnimation(778, 1, 0);

    while (stage_CheckAnimationFinish(778) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo12Chk(GObj *volatile self)
{
    gflagOn(319);

    actCreateSubThread(actConte14_12, 21);
}

void actConte14_12(GObj *volatile self)
{
    stage_SetAnimation(779, 1, 0);

    preload(4);

    while (stage_CheckAnimationFinish(779) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChangeWithColor(4, boyGObj, girlGObj, 16.0f, 16.0f, 255, 255, 255);
}

void actEndDemo13Chk(GObj *volatile self)
{
    gflagOn(320);

    actCreateSubThread(actConte14_13, 21);
}

void actStaff1Chk(GObj *volatile self)
{
    actCreateSubThread(actStaff1Demo, 21);
}

void actStaff2Chk(GObj *volatile self)
{
    reg_SetScissorSw(1);

    SetStaticBlur(0);

    actCreateSubThread(actStaff2Demo, 21);
}

void actStaff3Chk(GObj *volatile self)
{
    actCreateSubThread(actStaff3Demo, 21);

    actCreateSubThread(actStaff3RollChk, 21);
}

void actStaff3RollChk(GObj *volatile self)
{
    preload(1);

    while (staffRollStartFlag != 0) {
        _ACTWait(1);
    }

    if (ed6 != 0) {
        scpAdpcmFadeCloseFunc(ed6, 80);
    }

    RequestStageChange(1, boyGObj, 0, 16.0f, 0.001f);
}

void actEndDemo14Chk(GObj *volatile self)
{
    gflagOn(321);

    actCreateSubThread(actConte14_14, 21);
}

void actEndLogoChk(GObj *volatile self)
{
    scpBoyControlReadDisable = 1;
    enable_game_pause = 0;
    preload(1);
    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 30);

    scpFadeOut(6.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, boyGObj, 0, 255.0f, 8.0f);
}
