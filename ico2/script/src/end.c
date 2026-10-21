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

/* .sdata: two stream handles in this build, the ending demo's and the sea's
   (actEndDemo14 plays 88 into it as September plays 93: the same call). */
SqEntry *ed1 = 0;

SqEntry *sea = 0;

/* One mail table per ending process: demo01..08 and 10..13 (this build has
   an eighth demo and no ninth), staff1 and staff3 (no staff2), the
   fourteenth demo's, the st27a ending's and the logo's. */
static ActMail demo01_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo02_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo03_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo04_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo05_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo06_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo07_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo08_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo10_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo11_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo12_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo13_mes[2] = {{377}, {376}}; /* derived name */

static ActMail staff1_mes[2] = {{377}, {376}}; /* derived name */

static ActMail staff3_mes[2] = {{377}, {376}}; /* derived name */

static ActMail demo14_mes[2] = {{377}, {376}}; /* derived name */

static ActMail st27aEnd_mes[2] = {{377}, {376}}; /* derived name */

static ActMail logo_mes[2] = {{377}, {376}}; /* derived name */

void actConte14_1(GObj *volatile self)
{
    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    stage_SetAnimation(692, 1, 0);

    scpPlayMot(scpSearchGobj(2175), 793);

    scpSearchGobj(2175)->active = 1;

    while (stage_ContinueAnimation(692, 693) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2175), 794);

    while (stage_ContinueAnimation(693, 694) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(46, 1, 0);

    while (stage_ContinueAnimation(694, 695) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2175), 795);

    while (stage_ContinueAnimation(695, 696) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2175), 796);

    while (stage_ContinueAnimation(696, 697) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2175), 797);

    while (stage_ContinueAnimation(697, 698) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(2175)->active = 0;

    scpPlayMot(scpSearchGobj(2176), 798);

    scpSearchGobj(2176)->active = 1;

    while (stage_ContinueAnimation(698, 699) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2176), 799);

    while (stage_ContinueAnimation(699, 700) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2176), 800);

    while (stage_ContinueAnimation(700, 701) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2176), 801);

    while (stage_CheckAnimationFinish(701) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, 0, 16.0f, 16.0f);
}

void actConte14_2(GObj *volatile self)
{
    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    stage_SetAnimation(702, 1, 0);

    scpPlayMot(boyGObj, 446);

    while (stage_ContinueAnimation(702, 703) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(703, 704) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2363), 802);

    scpSearchGobj(2363)->active = 1;

    while (stage_ContinueAnimation(704, 705) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 447);

    scpPlayMot(scpSearchGobj(2363), 803);

    while (stage_ContinueAnimation(705, 706) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 448);

    scpPlayMot(scpSearchGobj(2363), 804);

    while (stage_ContinueAnimation(706, 707) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 449);

    scpPlayMot(scpSearchGobj(2363), 805);

    while (stage_ContinueAnimation(707, 708) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 450);

    scpPlayMot(scpSearchGobj(2363), 806);

    while (stage_CheckAnimationFinish(708) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(boyGObj);

    lt_switch_layout(50);

    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

void actConte14_6(GObj *volatile self)
{
    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    stage_SetAnimation(714, 1, 0);

    stage_SetAnimation(716, 1, 0);

    scpPlayMot(boyGObj, 451);

    scpPlayMot(scpSearchGobj(2176), 807);

    scpSearchGobj(2176)->active = 1;

    while (stage_ContinueAnimation(714, 715) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 452);

    scpPlayMot(scpSearchGobj(2176), 808);

    while (stage_CheckAnimationFinish(715) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, boyGObj, girlGObj, 16.0f, 16.0f);
}

/* 16-byte constant vector templates: the float view carries the values, the
   long long view is the one the copy reads. */

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}}; /* derived name */

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

/* this build's position (actConte14_14 reads it) */
static const ConstVec conte14_14Pos = {{17430.0f, 3.0f, -4384.0f, 1.0f}}; /* derived name */

void actConte14_7(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    stage_SetAnimation(717, 1, 0);

    stage_SetAnimation(138, 1, 471);

    _ACTWait(1);

    scpPlayPosSet(boyGObj, -4757.0f, -660.0f, 2646.0f);

    scpPlayPosSet(scpSearchGobj(2066), -4757.0f, -664.0f, 2646.0f);

    _ACTWait(1);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2066)));
    scpPlayMotDir(scpSearchGobj(2066), dir);

    scpPlayMotNode(boyGObj, 453, scpSearchGobj(2066), 44);

    scpPlayMot(scpSearchGobj(2066), 809);

    scpSearchGobj(2066)->active = 1;

    while (stage_CheckAnimationFinish(717) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actConte14_10(GObj *volatile self)
{
    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    stage_SetAnimation(718, 1, 0);

    stage_SetAnimation(38, 1, 0);

    scpPlayMot(boyGObj, 454);

    scpPlayMot(scpSearchGobj(1841), 810);

    scpSearchGobj(1841)->active = 1;

    while (stage_ContinueAnimation(718, 719) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(39, 1, 0);

    scpPlayMot(boyGObj, 455);

    scpPlayMot(scpSearchGobj(1841), 811);

    while (stage_ContinueAnimation(719, 720) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(40, 1, 0);

    scpPlayMot(boyGObj, 456);

    scpPlayMot(scpSearchGobj(1841), 812);

    while (stage_ContinueAnimation(720, 721) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(41, 1, 0);

    scpPlayMot(boyGObj, 457);

    scpPlayMot(scpSearchGobj(1841), 813);

    while (stage_ContinueAnimation(721, 722) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(42, 1, 0);

    scpPlayMot(boyGObj, 458);

    scpPlayMot(scpSearchGobj(1841), 814);

    while (stage_ContinueAnimation(722, 723) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(43, 1, 0);

    stage_SetAnimation(47, 1, 0);

    scpPlayMot(boyGObj, 459);

    while (stage_ContinueAnimation(723, 724) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(44, 1, 0);

    stage_SetAnimation(48, 1, 0);

    scpPlayMot(boyGObj, 460);

    while (stage_CheckAnimationFinish(724) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actStaff1Demo(GObj *volatile self)
{
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    staffRollStart(1.0f, 255);

    stage_SetAnimation(473, 1, 0);

    while (stage_ContinueAnimation(473, 474) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(21, 1, 0);

    scpPlayMot(boyGObj, 291);

    while (stage_ContinueAnimation(474, 476) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(476, 477) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 292);

    _ACTWait(130);

    stage_SetAnimation(27, 1, 0);

    while (stage_ContinueAnimation(477, 478) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(478, 479) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 293);

    while (stage_ContinueAnimation(479, 480) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 294);

    while (stage_ContinueAnimation(480, 481) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 295);

    while (stage_ContinueAnimation(481, 482) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 296);

    while (stage_ContinueAnimation(482, 483) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 297);

    while (stage_ContinueAnimation(483, 485) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 299);

    while (stage_CheckAnimationFinish(485) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(1, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actStaff3Demo(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    stage_SetAnimation(504, 1, 0);

    scpPlayPosSet(scpSearchGobj(2459), -7.0f, -5725.0f, 18.0f);

    ofs[0] = staff3DemoPos.d[0];
    ofs[1] = staff3DemoPos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2459)));
    scpPlayMotDir(scpSearchGobj(2459), dir);

    scpPlayMot(scpSearchGobj(2459), 656);

    scpSearchGobj(2459)->active = 1;

    scpPlayMot(boyGObj, 311);

    while (stage_ContinueAnimation(504, 506) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 313);

    while (stage_ContinueAnimation(506, 507) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 314);

    while (stage_ContinueAnimation(507, 515) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(55, 0, -1);

    scpPlayMot(scpSearchGobj(2459), 709);

    while (stage_ContinueAnimation(515, 516) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(scpSearchGobj(2459), 710);

    while (stage_ContinueAnimation(516, 517) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 321);

    scpPlayMot(scpSearchGobj(2459), 711);

    while (stage_ContinueAnimation(517, 518) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 322);

    scpPlayMot(scpSearchGobj(2459), 712);

    while (stage_ContinueAnimation(518, 520) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 323);

    scpPlayMot(scpSearchGobj(2459), 713);

    while (stage_CheckAnimationFinish(520) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void actConte14_14(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    scpFadeIn(6.0f);

    stage_SetAnimation(734, 1, 0);

    scpPlayMot(boyGObj, 466);

    while (stage_ContinueAnimation(734, 735) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 467);

    while (stage_ContinueAnimation(735, 736) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 468);

    while (stage_ContinueAnimation(736, 737) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 469);

    while (stage_ContinueAnimation(737, 738) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 470);

    while (stage_ContinueAnimation(738, 739) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 471);

    scpPlayMot(scpSearchGobj(1956), 816);

    scpSearchGobj(1956)->active = 1;

    while (stage_CheckAnimationFinish(739) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayMot(boyGObj, 0);

    ofs[0] = conte14_14Pos.d[0];
    ofs[1] = conte14_14Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(50);

    gflagOff(292);
}

void actSt27aEndDemo(GObj *volatile self)
{
    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    stage_SetAnimation(740, 1, 0);

    scpPlayMot(boyGObj, 472);

    scpPlayMot(scpSearchGobj(1956), 817);

    scpSearchGobj(1956)->active = 1;

    while (stage_ContinueAnimation(740, 741) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 473);

    scpPlayMot(scpSearchGobj(1956), 818);

    while (stage_ContinueAnimation(741, 742) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 474);

    scpPlayMot(scpSearchGobj(1956), 819);

    while (stage_CheckAnimationFinish(742) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(1, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actEndDemo01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(293) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(716, 0, 0);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(30, 0, -1);
        demo01_mes[0].func = actEndDemo01Chk;
        act->mail = demo01_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actEndDemo02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    stage_SetAnimation(703, 0, 0);
    demo02_mes[0].func = actEndDemo02Chk;
    act->mail = demo02_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actEndDemo03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    demo03_mes[0].func = actEndDemo03Chk;
    act->mail = demo03_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actEndDemo04(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    demo04_mes[0].func = actEndDemo04Chk;
    act->mail = demo04_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actEndDemo05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    demo05_mes[0].func = actEndDemo05Chk;
    act->mail = demo05_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actEndDemo06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(297) != 0) {
        stage_SetAnimation(716, 0, 0);
        stage_SetAnimation(21, 0, 0);
        stage_SetAnimation(30, 0, -1);
        demo06_mes[0].func = actEndDemo06Chk;
        act->mail = demo06_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actEndDemo07(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(299) == 0) {
        demo07_mes[0].func = actEndDemo07Chk;
        act->mail = demo07_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actEndDemo08(GObj *volatile self) /* derived name */
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(300) == 0) {
        demo08_mes[0].func = actEndDemo08Chk;
        act->mail = demo08_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actEndDemo10(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(302) == 0) {
        demo10_mes[0].func = actEndDemo10Chk;
        act->mail = demo10_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actEndDemo11(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    demo11_mes[0].func = actEndDemo11Chk;
    act->mail = demo11_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actEndDemo12(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(304) == 0 && gflagChk(303) != 0) {
        demo12_mes[0].func = actEndDemo12Chk;
        act->mail = demo12_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actEndDemo13(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    demo13_mes[0].func = actEndDemo13Chk;
    act->mail = demo13_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actEndDemo14(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    scpFadeOut(255.0f, 255, 255, 255);

    scpAdpcmPlayRequestFunc(88, &sea, 1, 0, 1);

    if (gflagChk(306) == 0) {
        demo14_mes[0].func = actEndDemo14Chk;
        act->mail = demo14_mes;
        ACTSendMailCorrect(self, 377);
        _ACTWait(0);
    }
}

void actStaff1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    stage_SetAnimation(25, 0, 0);
    stage_SetAnimation(21, 0, 0);
    stage_SetAnimation(28, 0, 0);
    stage_SetAnimation(29, 0, 0);
    stage_SetAnimation(31, 0, 0);
    stage_SetAnimation(33, 0, 0);
    staff1_mes[0].func = actStaff1Chk;
    act->mail = staff1_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actStaff3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    stage_SetAnimation(53, 0, 0);
    stage_SetAnimation(58, 0, 0);
    staff3_mes[0].func = actStaff3Chk;
    act->mail = staff3_mes;
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actSt27aEnd(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gflagChk(308) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        act->mail = st27aEnd_mes;
        ACTSendMailCorrect(self, 377);
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
    ACTSendMailCorrect(self, 377);
    _ACTWait(0);
}

void actEndDemo01Chk(GObj *volatile self)
{
    scpAdpcmPlayRequestFunc(46, &ed1, 0, 1, 1);

    while (ed1 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOn(2);

    gflagOn(3);

    gflagOn(4);

    gflagOn(293);

    actCreateSubThread(actConte14_1, 21);
}

void actEndDemo02Chk(GObj *volatile self)
{
    gflagOn(294);

    actCreateSubThread(actConte14_2, 21);
}

void actEndDemo03Chk(GObj *volatile self)
{
    gflagOn(295);

    actCreateSubThread(actConte14_3, 21);
}

void actConte14_3(GObj *volatile self)
{
    lt_switch_layout(51);

    stage_SetAnimation(709, 1, 0);

    while (stage_CheckAnimationFinish(709) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, 0, 16.0f, 16.0f);
}

void actEndDemo04Chk(GObj *volatile self)
{
    gflagOn(296);

    actCreateSubThread(actConte14_4, 21);
}

void actConte14_4(GObj *volatile self)
{
    lt_switch_layout(51);

    stage_SetAnimation(710, 1, 0);

    while (stage_CheckAnimationFinish(710) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(5, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actEndDemo05Chk(GObj *volatile self)
{
    gflagOn(297);

    actCreateSubThread(actConte14_5, 21);
}

void actConte14_5(GObj *volatile self)
{
    lt_switch_layout(51);

    stage_SetAnimation(711, 1, 0);

    while (stage_CheckAnimationFinish(711) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actEndDemo06Chk(GObj *volatile self)
{
    actCreateSubThread(actConte14_6, 21);
}

void actEndDemo07Chk(GObj *volatile self)
{
    gflagOn(299);

    actCreateSubThread(actConte14_7, 21);
}

void actEndDemo08Chk(GObj *volatile self) /* derived name */
{
    gflagOn(300);

    actCreateSubThread(actConte14_8, 21);
}

void actConte14_8(GObj *volatile self) /* derived name */
{
    lt_switch_layout(51);

    stage_SetAnimation(712, 1, 0);

    stage_SetAnimation(37, 1, 0);

    while (stage_ContinueAnimation(712, 713) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFinish(713) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actEndDemo10Chk(GObj *volatile self)
{
    gflagOn(302);

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
        case 1320:
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
    } while (t < 1500.0f);
}

void actEndDemo11Chk(GObj *volatile self)
{
    gflagOn(303);

    actCreateSubThread(actConte14_11, 21);
}

void actConte14_11(GObj *volatile self)
{
    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    stage_SetAnimation(725, 1, 0);

    stage_SetAnimation(45, 1, 0);

    while (stage_CheckAnimationFinish(725) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actEndDemo12Chk(GObj *volatile self)
{
    gflagOn(304);

    actCreateSubThread(actConte14_12, 21);
}

void actConte14_12(GObj *volatile self)
{
    lt_switch_layout(51);

    stage_SetAnimation(726, 1, 0);

    while (stage_ContinueAnimation(726, 727) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFinish(727) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(4, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actEndDemo13Chk(GObj *volatile self)
{
    gflagOn(305);

    actCreateSubThread(actConte14_13, 21);
}

void actConte14_13(GObj *volatile self)
{
    lt_switch_layout(51);

    scpPlayStart(boyGObj);

    stage_SetAnimation(728, 1, 0);

    scpPlayMot(boyGObj, 461);

    while (stage_ContinueAnimation(728, 729) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 461);

    while (stage_CheckAnimationFinish(729) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(boyGObj);

    RequestStageChange(6, boyGObj, girlGObj, 16.0f, 16.0f);
}

void actStaff1Chk(GObj *volatile self)
{
    actCreateSubThread(actStaff1Demo, 21);
}

void actStaff3Chk(GObj *volatile self)
{
    actCreateSubThread(actStaff3Demo, 21);

    actCreateSubThread(actStaff3RollChk, 21);
}

void actStaff3RollChk(GObj *volatile self)
{
    while (staffRollStartFlag != 0) {
        _ACTWait(1);
    }

    if (ed1 != 0) {
        scpAdpcmFadeClose(ed1, 80);
    }

    RequestStageChange(1, boyGObj, 0, 16.0f, 16.0f);
}

void actEndDemo14Chk(GObj *volatile self)
{
    gflagOn(306);

    actCreateSubThread(actConte14_14, 21);
}

void actSt27aEndChk(GObj *volatile self)
{
    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

    gflagOn(308);

    actCreateSubThread(actSt27aEndDemo, 21);
}

void actEndLogoChk(GObj *volatile self)
{
    _ACTWait(800);

    RequestStageChange(1, boyGObj, 0, 16.0f, 16.0f);
}
