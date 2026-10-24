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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
static void actEndLogoChk(GObj *volatile self);
#else
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
static void actEndingSave(GObj *volatile self);
#endif
#endif

/* .sdata: the ending scenes' stream handles (ed5 and happy_end unused), then
   the staff roll's, the fourteenth demo's and the st27a ending's. */
SqEntry *ed1 = 0;

SqEntry *ed2 = 0;

SqEntry *ed3 = 0;

SqEntry *ed4 = 0;

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
SqEntry *ed5 = 0;
#else
int ed5 = 0;
#endif

SqEntry *ed6 = 0;

SqEntry *sea = 0;

#ifdef VERSION_NTSC
SqEntry *happy_end = 0;

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
#else
#ifdef VERSION_AUG6
SqEntry *happy_end = 0;

static ActMail demo01_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo02_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo03_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo04_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo05_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo06_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo07_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo10_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo11_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo12_mes[2] = {{393}, {392}}; /* derived name */

static ActMail demo13_mes[2] = {{393}, {392}}; /* derived name */

static ActMail staff1_mes[2] = {{393}, {392}}; /* derived name */

static ActMail staff2_mes[2] = {{393}, {392}}; /* derived name */

static ActMail staff3_mes[2] = {{393}, {392}}; /* derived name */

static ActMail ed_demo14_mes[2] = {{393}, {392}}; /* derived name */

static ActMail st27aEnd_mes[2] = {{393}, {392}}; /* derived name */

static ActMail logo_mes[2] = {{393}, {392}}; /* derived name */
#else
int happy_end = 0;

static SqEntry *staff3 = 0; /* derived name */

static SqEntry *endDemo14 = 0; /* derived name */

static SqEntry *st27aEnd = 0; /* derived name */

static ActMail demo01_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo02_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo03_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo04_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo05_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo06_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo07_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo10_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo11_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo12_mes[2] = {{430}, {429}}; /* derived name */

static ActMail demo13_mes[2] = {{430}, {429}}; /* derived name */

static ActMail staff1_mes[2] = {{430}, {429}}; /* derived name */

static ActMail staff2_mes[2] = {{430}, {429}}; /* derived name */

static ActMail staff3_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ed_demo14_mes[2] = {{430}, {429}}; /* derived name */

static ActMail st27aEnd_mes[2] = {{430}, {429}}; /* derived name */

static ActMail logo_mes[2] = {{430}, {429}}; /* derived name */

static ActMail end_mes[2] = {{430}, {429}}; /* derived name */
#endif

void actEndDemo01(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(307) == 0 && gflagChk(311) == 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(765, 0, 0);
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(33, 0, -1);
        demo01_mes[0].func = actEndDemo01Chk;
        act->mail = demo01_mes;
        ACTSendMailCorrect(self, 393);
#else
    if (gflagChk(339) == 0 && gflagChk(343) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(836, 0, 0);
#else
        stage_SetAnimation(840, 0, 0);
#endif
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, -1);
        stage_SetAnimation(33, 0, -1);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
        demo01_mes[0].func = actEndDemo01Chk;
        act->mail = demo01_mes;
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actConte14_1(GObj *volatile self)
{
    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(739, 1, 0);

    scpPlayMot(scpSearchGobj(2278), 766);

    scpSearchGobj(2278)->active = 1;

    while (stage_ContinueAnimation(739, 740) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(810, 1, 0);
#else
    stage_SetAnimation(814, 1, 0);
#endif

    scpPlayMot(scpSearchGobj(2515), 809);

    scpSearchGobj(2515)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(810, 811) == 0) {
#else
    while (stage_ContinueAnimation(814, 815) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(811, 812) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(740, 741) == 0) {
#else
    while (stage_ContinueAnimation(815, 816) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(52, 1, 0);

    while (stage_ContinueAnimation(741, 742) == 0) {
#else
    stage_SetAnimation(55, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(812, 813) == 0) {
#else
    while (stage_ContinueAnimation(816, 817) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(813, 814) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(742, 743) == 0) {
#else
    while (stage_ContinueAnimation(817, 818) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(814, 815) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(743, 744) == 0) {
#else
    while (stage_ContinueAnimation(818, 819) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(2278), 767);

    while (stage_ContinueAnimation(744, 745) == 0) {
#else
    scpPlayMot(scpSearchGobj(2515), 810);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(815, 816) == 0) {
#else
    while (stage_ContinueAnimation(819, 820) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpSearchGobj(2278)->active = 0;

    scpPlayMot(scpSearchGobj(2279), 768);

    scpSearchGobj(2279)->active = 1;

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2279, 0, 482, 0);

    stage_SetLoopFlag(482, 1);

    stage_SetAnimation(482, 1, 0);

    while (stage_ContinueAnimation(745, 746) == 0) {
#else
    scpSearchGobj(2515)->active = 0;

    scpPlayMot(scpSearchGobj(2516), 811);

    scpSearchGobj(2516)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2516, 0, 550, 0);
#else
    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2516, 0, 554, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(550, 1);
#else
    stage_SetLoopFlag(554, 1);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(550, 1, 0);
#else
    stage_SetAnimation(554, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(816, 817) == 0) {
#else
    while (stage_ContinueAnimation(820, 821) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(2279), 769);

    while (stage_ContinueAnimation(746, 747) == 0) {
#else
    scpPlayMot(scpSearchGobj(2516), 812);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(817, 818) == 0) {
#else
    while (stage_ContinueAnimation(821, 822) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(2279), 770);

    while (stage_ContinueAnimation(747, 748) == 0) {
#else
    scpPlayMot(scpSearchGobj(2516), 813);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(818, 819) == 0) {
#else
    while (stage_ContinueAnimation(822, 823) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(2279), 771);

    while (stage_CheckAnimationFinish(748) == 0) {
#else
    scpPlayMot(scpSearchGobj(2516), 814);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(819) == 0) {
#else
    while (stage_CheckAnimationFinish(823) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, 0, 1.0f, 8.0f);
}
#endif

void actEndDemo02(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

#ifdef VERSION_NTSC
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
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 482, 0);
    stage_SetLoopFlag(482, 1);
    stage_SetAnimation(482, 1, 0);
    stage_SetAnimation(750, 0, 0);
    stage_SetAnimation(484, 0, -1);
    stage_SetAnimation(485, 0, -1);
    stage_SetAnimation(487, 0, -1);
    stage_SetAnimation(488, 0, -1);
    stage_SetAnimation(489, 0, -1);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 550, 0);
    stage_SetLoopFlag(550, 1);
    stage_SetAnimation(550, 1, 0);
    stage_SetAnimation(821, 0, 0);
    stage_SetAnimation(552, 0, -1);
    stage_SetAnimation(553, 0, -1);
    stage_SetAnimation(555, 0, -1);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 554, 0);
    stage_SetLoopFlag(554, 1);
    stage_SetAnimation(554, 1, 0);
    stage_SetAnimation(825, 0, 0);
#endif
    stage_SetAnimation(556, 0, -1);
    stage_SetAnimation(557, 0, -1);
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    stage_SetAnimation(559, 0, -1);
    stage_SetAnimation(560, 0, -1);
    stage_SetAnimation(561, 0, -1);
#endif
#endif
#endif
    SelectBoyCrown(boyGObj, 2);
    demo02_mes[0].func = actEndDemo02Chk;
    act->mail = demo02_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

#ifdef VERSION_NTSC
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
#else
void actConte14_2(GObj *volatile self)
{
    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(749, 1, 0);

    scpPlayMot(boyGObj, 435);

    while (stage_ContinueAnimation(749, 750) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(820, 1, 0);
#else
    stage_SetAnimation(824, 1, 0);
#endif

    scpPlayMot(boyGObj, 441);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(820, 821) == 0) {
#else
    while (stage_ContinueAnimation(824, 825) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(821, 822) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(750, 751) == 0) {
#else
    while (stage_ContinueAnimation(825, 826) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(2441), 772);

    scpSearchGobj(2441)->active = 1;
#else
    scpPlayMot(scpSearchGobj(2686), 815);

    scpSearchGobj(2686)->active = 1;
#endif

    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(752, 1, 0);

    while (stage_ContinueAnimation(751, 753) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(823, 1, 0);
#else
    stage_SetAnimation(827, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(822, 824) == 0) {
#else
    while (stage_ContinueAnimation(826, 828) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 436);

    scpPlayMot(scpSearchGobj(2441), 773);

    while (stage_ContinueAnimation(753, 754) == 0) {
#else
    scpPlayMot(boyGObj, 442);

    scpPlayMot(scpSearchGobj(2686), 816);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(824, 825) == 0) {
#else
    while (stage_ContinueAnimation(828, 829) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 437);

    scpPlayMot(scpSearchGobj(2441), 774);

    while (stage_ContinueAnimation(754, 755) == 0) {
#else
    scpPlayMot(boyGObj, 443);

    scpPlayMot(scpSearchGobj(2686), 817);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(825, 826) == 0) {
#else
    while (stage_ContinueAnimation(829, 830) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 438);

    scpPlayMot(scpSearchGobj(2441), 775);

    while (stage_ContinueAnimation(755, 756) == 0) {
#else
    scpPlayMot(boyGObj, 444);

    scpPlayMot(scpSearchGobj(2686), 818);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(826, 827) == 0) {
#else
    while (stage_ContinueAnimation(830, 831) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 439);

    scpPlayMot(scpSearchGobj(2441), 776);
#else
    scpPlayMot(boyGObj, 445);

    scpPlayMot(scpSearchGobj(2686), 819);
#endif

    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(757, 1, 0);

    while (stage_CheckAnimationFinish(756) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(828, 1, 0);
#else
    stage_SetAnimation(832, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(827) == 0) {
#else
    while (stage_CheckAnimationFinish(831) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(boyGObj);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(50);
#else
    lt_switch_layout(54);
#endif
#endif

    RequestStageChange(3, boyGObj, 0, 1.0f, 8.0f);
}

void actEndDemo06(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(312) == 0 && gflagChk(311) != 0) {
        lt_switch_layout(51);
        scpBoyControlReadDisable = 1;
        scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2279, 0, 482, 0);
        stage_SetLoopFlag(482, 1);
        stage_SetAnimation(482, 1, 0);
        stage_SetAnimation(765, 0, 0);
        stage_SetAnimation(31, 0, -1);
        stage_SetAnimation(25, 0, 0);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(33, 0, -1);
#else
    if (gflagChk(344) == 0 && gflagChk(343) != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(52);
#else
        lt_switch_layout(55);
#endif
        scpBoyControlReadDisable = 1;
        scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2516, 0, 550, 0);
        stage_SetLoopFlag(550, 1);
        stage_SetAnimation(550, 1, 0);
        stage_SetAnimation(836, 0, 0);
#else
        scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(2516, 0, 554, 0);
        stage_SetLoopFlag(554, 1);
        stage_SetAnimation(554, 1, 0);
        stage_SetAnimation(840, 0, 0);
#endif
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, -1);
        stage_SetAnimation(33, 0, -1);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
#endif
        SelectBoyCrown(boyGObj, 2);
        demo06_mes[0].func = actEndDemo06Chk;
        act->mail = demo06_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}

void actConte14_6(GObj *volatile self)
{
    preload(3);

    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(763, 1, 0);

    stage_SetAnimation(765, 1, 0);

    stage_SetAnimation(766, 1, 0);

    scpPlayMot(boyGObj, 440);

    scpPlayMot(scpSearchGobj(2279), 777);

    scpSearchGobj(2279)->active = 1;

    while (stage_ContinueAnimation(763, 764) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(834, 1, 0);
#else
    stage_SetAnimation(838, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(836, 1, 0);
#else
    stage_SetAnimation(840, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(837, 1, 0);
#else
    stage_SetAnimation(841, 1, 0);
#endif

    scpPlayMot(boyGObj, 446);

    scpPlayMot(scpSearchGobj(2516), 820);

    scpSearchGobj(2516)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(834, 835) == 0) {
#else
    while (stage_ContinueAnimation(838, 839) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 441);

    scpPlayMot(scpSearchGobj(2279), 778);

    while (stage_CheckAnimationFinish(764) == 0) {
#else
    scpPlayMot(boyGObj, 447);

    scpPlayMot(scpSearchGobj(2516), 821);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(835) == 0) {
#else
    while (stage_CheckAnimationFinish(839) == 0) {
#endif
#endif
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

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 482, 0);
    stage_SetAnimation(151, 0, 0);
    stage_SetLoopFlag(482, 1);
    stage_SetAnimation(482, 1, 0);

    if (gflagChk(313) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 550, 0);
    stage_SetAnimation(169, 0, 0);
    stage_SetLoopFlag(550, 1);
    stage_SetAnimation(550, 1, 0);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 554, 0);
    stage_SetAnimation(173, 0, 0);
    stage_SetLoopFlag(554, 1);
    stage_SetAnimation(554, 1, 0);
#endif

    if (gflagChk(345) == 0) {
#endif
        SelectBoyCrown(boyGObj, 2);
        demo07_mes[0].func = actEndDemo07Chk;
        act->mail = demo07_mes;
#ifdef VERSION_AUG6
        ACTSendMailCorrect(self, 393);
#else
        ACTSendMailCorrect(self, 430);
#endif
        _ACTWait(0);
    }
}
#endif

/* 16-byte constant vector templates: the float view carries the values, the
   long long view is the one the copy reads. */

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}}; /* derived name */

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}}; /* derived name */

static const ConstVec conte14_14Pos = {{16975.0f, 71.0f, -4332.0f, 1.0f}}; /* derived name */

#ifdef VERSION_NTSC
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
#else
void actConte14_7(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    preload(6);

    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(767, 1, 0);

    stage_SetAnimation(151, 1, 471);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(838, 1, 0);
#else
    stage_SetAnimation(842, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(169, 1, 471);
#else
    stage_SetAnimation(173, 1, 471);
#endif
#endif

    _ACTWait(1);

    scpPlayPosSet(boyGObj, -4757.0f, -660.0f, 2646.0f);

#ifdef VERSION_AUG6
    scpPlayPosSet(scpSearchGobj(2156), -4757.0f, -664.0f, 2646.0f);
#else
    scpPlayPosSet(scpSearchGobj(2388), -4757.0f, -664.0f, 2646.0f);
#endif

    _ACTWait(1);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(boyGObj));
    scpPlayMotDir(boyGObj, dir);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
#ifdef VERSION_AUG6
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2156)));
    scpPlayMotDir(scpSearchGobj(2156), dir);

    scpPlayMotNode(boyGObj, 442, scpSearchGobj(2156), 44);

    scpPlayMot(scpSearchGobj(2156), 779);

    scpSearchGobj(2156)->active = 1;

    while (stage_CheckAnimationFinish(767) == 0) {
#else
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2388)));
    scpPlayMotDir(scpSearchGobj(2388), dir);

    scpPlayMotNode(boyGObj, 448, scpSearchGobj(2388), 44);

    scpPlayMot(scpSearchGobj(2388), 822);

    scpSearchGobj(2388)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(838) == 0) {
#else
    while (stage_CheckAnimationFinish(842) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, boyGObj, girlGObj, 1.0f, 8.0f);
}
#endif

void actEndDemo10(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
#ifdef VERSION_AUG6
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 482, 0);
    stage_SetLoopFlag(482, 1);
    stage_SetAnimation(482, 1, 0);
    SelectBoyCrown(boyGObj, 2);
    stage_SetAnimation(775, 0, 0);
    demo10_mes[0].func = actEndDemo10Chk;
    act->mail = demo10_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 483, 0);
    stage_SetLoopFlag(483, 1);
    stage_SetAnimation(483, 1, 0);
    SelectBoyCrown(boyGObj, 2);
    stage_SetAnimation(776, 0, 0);
    demo10_mes[0].func = actEndDemo10Chk;
    act->mail = demo10_mes;
    ACTSendMailCorrect(self, 397);
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 550, 0);
#else
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 554, 0);
#endif
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 52, 58, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetLoopFlag(550, 1);
    stage_SetAnimation(550, 1, 0);
#else
    stage_SetLoopFlag(554, 1);
    stage_SetAnimation(554, 1, 0);
#endif
    SelectBoyCrown(boyGObj, 2);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(846, 0, 0);
#else
    stage_SetAnimation(850, 0, 0);
#endif
    demo10_mes[0].func = actEndDemo10Chk;
    act->mail = demo10_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

#ifdef VERSION_NTSC
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

    scpAdpcmPlayRequestFunc(93, &sea, 1, 0, 1);

    while (sea == 0) {
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

    if (sea != 0) {
        scpAdpcmFadeClose(sea, 27);
    }
    scpAdpcmPlayRequestFunc(49, &happy_end, 0, 1, 1);
    while (happy_end == 0) {
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
#else
void actConte14_10(GObj *volatile self)
{
    preload(3);

    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(768, 1, 0);

    scpPlayMot(boyGObj, 443);

    scpPlayMot(scpSearchGobj(1916), 780);

    scpSearchGobj(1916)->active = 1;

    _ACTWait(1);

    stage_SetAnimation(42, 1, 0);

    stage_SetAnimation(769, 1, 0);

    while (stage_ContinueAnimation(768, 770) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 444);

    scpPlayMot(scpSearchGobj(1916), 781);

    _ACTWait(1);

    stage_SetAnimation(43, 1, 0);

    while (stage_ContinueAnimation(770, 771) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 445);

    scpPlayMot(scpSearchGobj(1916), 782);

    _ACTWait(1);

    stage_SetAnimation(44, 1, 0);

    while (stage_ContinueAnimation(771, 772) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 446);

    scpPlayMot(scpSearchGobj(1916), 783);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(839, 1, 0);
#else
    stage_SetAnimation(843, 1, 0);
#endif

    scpPlayMot(boyGObj, 449);

    scpPlayMot(scpSearchGobj(2122), 823);

    scpSearchGobj(2122)->active = 1;
#endif

    _ACTWait(1);

    stage_SetAnimation(45, 1, 0);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(772, 773) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(840, 1, 0);
#else
    stage_SetAnimation(844, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(839, 841) == 0) {
#else
    while (stage_ContinueAnimation(843, 845) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 447);

    scpPlayMot(scpSearchGobj(1916), 784);
#else
    scpPlayMot(boyGObj, 450);

    scpPlayMot(scpSearchGobj(2122), 824);
#endif

    _ACTWait(1);

    stage_SetAnimation(46, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(841, 842) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(773, 774) == 0) {
#else
    while (stage_ContinueAnimation(845, 846) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 448);
#else
    scpPlayMot(boyGObj, 451);

    scpPlayMot(scpSearchGobj(2122), 825);
#endif

    _ACTWait(1);

    stage_SetAnimation(47, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(842, 843) == 0) {
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(53, 1, 0);

    stage_SetAnimation(775, 1, 0);

    while (stage_ContinueAnimation(774, 776) == 0) {
#else
    while (stage_ContinueAnimation(846, 847) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 449);
#else
    AdpcmPlay(ed6->stream);

    scpPlayMot(boyGObj, 452);

    scpPlayMot(scpSearchGobj(2122), 826);
#endif

    _ACTWait(1);

    stage_SetAnimation(48, 1, 0);

#ifdef VERSION_AUG6
    stage_SetAnimation(54, 1, 0);

    while (stage_CheckAnimationFinish(776) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(843, 844) == 0) {
#else
    while (stage_ContinueAnimation(847, 848) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 453);

    scpPlayMot(scpSearchGobj(2122), 827);

    _ACTWait(1);

    stage_SetAnimation(49, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(844, 845) == 0) {
#else
    while (stage_ContinueAnimation(848, 849) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 454);

    _ACTWait(1);

    stage_SetAnimation(50, 1, 0);

    stage_SetAnimation(56, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(846, 1, 0);
#else
    stage_SetAnimation(850, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(845, 847) == 0) {
#else
    while (stage_ContinueAnimation(849, 851) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 455);

    _ACTWait(1);

    stage_SetAnimation(51, 1, 0);

    stage_SetAnimation(57, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(847) == 0) {
#else
    while (stage_CheckAnimationFinish(851) == 0) {
#endif
#endif
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

#ifdef VERSION_AUG6
    stage_SetAnimation(779, 1, 0);

    scpPlayMot(boyGObj, 450);

    while (stage_ContinueAnimation(779, 780) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(850, 1, 0);
#else
    stage_SetAnimation(854, 1, 0);
#endif

    scpPlayMot(boyGObj, 456);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(850, 851) == 0) {
#else
    while (stage_ContinueAnimation(854, 855) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(50, 1, 0);

    stage_SetAnimation(401, 1, 0);

    scpPlayMot(boyGObj, 450);

    while (stage_CheckAnimationFinish(780) == 0) {
#else
    stage_SetAnimation(53, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(461, 1, 0);
#else
    stage_SetAnimation(465, 1, 0);
#endif

    scpPlayMot(boyGObj, 456);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(851) == 0) {
#else
    while (stage_CheckAnimationFinish(855) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(boyGObj);

    RequestStageChange(6, boyGObj, girlGObj, 1.0f, 8.0f);
}

#ifndef VERSION_AUG6
void actStaff1(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    stage_SetAnimation(30, 0, -1);
    stage_SetAnimation(26, 0, 0);
    stage_SetAnimation(33, 0, 0);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(36, 0, 0);
    stage_SetAnimation(38, 0, 0);
    stage_SetAnimation(35, 0, 0);
    staff1_mes[0].func = actStaff1Chk;
    act->mail = staff1_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
}
#endif

void actStaff1Demo(GObj *volatile self)
{
    preload(1);

    staffRollStart(1.0f, 255);

#ifdef VERSION_AUG6
    stage_SetAnimation(522, 1, 0);

    while (stage_ContinueAnimation(522, 523) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(866, 1, 0);
#else
    stage_SetAnimation(870, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(866, 867) == 0) {
#else
    while (stage_ContinueAnimation(870, 871) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(25, 1, 0);

    scpPlayMot(boyGObj, 282);

    while (stage_ContinueAnimation(523, 525) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(525, 526) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 283);

    _ACTWait(130);

    stage_SetAnimation(31, 1, 0);

    while (stage_ContinueAnimation(526, 527) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(527, 528) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 284);

    while (stage_ContinueAnimation(528, 529) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(529, 530) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 286);

    while (stage_ContinueAnimation(530, 531) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 287);

    while (stage_ContinueAnimation(531, 532) == 0) {
        _ACTWait(1);
    }
#else
    stage_SetAnimation(26, 1, 0);
#endif

    scpPlayMot(boyGObj, 288);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(532, 533) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(867, 869) == 0) {
#else
    while (stage_ContinueAnimation(871, 873) == 0) {
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(869, 870) == 0) {
#else
    while (stage_ContinueAnimation(873, 874) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 289);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(533, 534) == 0) {
#else
    _ACTWait(130);

    stage_SetAnimation(32, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(870, 871) == 0) {
#else
    while (stage_ContinueAnimation(874, 875) == 0) {
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(871, 872) == 0) {
#else
    while (stage_ContinueAnimation(875, 876) == 0) {
#endif
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 290);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(872, 873) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(534, 535) == 0) {
#else
    while (stage_ContinueAnimation(876, 877) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 291);

    while (stage_CheckAnimationFrame(535, 100, 0) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(873, 874) == 0) {
#else
    while (stage_ContinueAnimation(877, 878) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 292);

    _ACTWait(1);

    stage_SetAnimation(32, 1, 208);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(874, 875) == 0) {
#else
    while (stage_ContinueAnimation(878, 879) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 293);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(875, 876) == 0) {
#else
    while (stage_ContinueAnimation(879, 880) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 294);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(876, 877) == 0) {
#else
    while (stage_ContinueAnimation(880, 881) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 295);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(877, 878) == 0) {
#else
    while (stage_ContinueAnimation(881, 882) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 296);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(878, 879) == 0) {
#else
    while (stage_ContinueAnimation(882, 883) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 297);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(879, 100, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(883, 100, 0) == 0) {
#endif
#endif
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

#ifdef VERSION_AUG6
    stage_SetAnimation(576, 1, 0);

    stage_SetAnimation(237, 1, 0);

    scpPlayMot(boyGObj, 321);

    scpPlayMot(scpSearchGobj(2556), 694);

    scpSearchGobj(2556)->active = 1;

    while (stage_ContinueAnimation(576, 577) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 322);

    scpPlayMot(scpSearchGobj(2556), 695);

    while (stage_ContinueAnimation(577, 578) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 323);

    scpPlayMot(scpSearchGobj(2556), 696);

    while (stage_ContinueAnimation(578, 579) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(579, 580) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 324);

    scpPlayMot(scpSearchGobj(2556), 697);

    while (stage_ContinueAnimation(580, 581) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 325);

    scpPlayMot(scpSearchGobj(2556), 698);

    while (stage_ContinueAnimation(581, 582) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 326);

    scpPlayMot(scpSearchGobj(2556), 699);

    while (stage_ContinueAnimation(582, 583) == 0) {
        _ACTWait(1);
    }
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(903, 1, 0);
#else
    stage_SetAnimation(907, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(265, 1, 0);
#else
    stage_SetAnimation(269, 1, 0);
#endif
#endif

    scpPlayMot(boyGObj, 327);

#ifdef VERSION_AUG6
    while (stage_ContinueAnimation(583, 598) == 0) {
#else
    scpPlayMot(scpSearchGobj(2789), 737);

    scpSearchGobj(2789)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(903, 904) == 0) {
#else
    while (stage_ContinueAnimation(907, 908) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 335);

    scpPlayMot(scpSearchGobj(2556), 705);

    while (stage_ContinueAnimation(598, 599) == 0) {
#else
    scpPlayMot(boyGObj, 328);

    scpPlayMot(scpSearchGobj(2789), 738);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(904, 905) == 0) {
#else
    while (stage_ContinueAnimation(908, 909) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 336);

    scpPlayMot(scpSearchGobj(2556), 706);

    while (stage_ContinueAnimation(599, 600) == 0) {
#else
    scpPlayMot(boyGObj, 329);

    scpPlayMot(scpSearchGobj(2789), 739);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(905, 906) == 0) {
#else
    while (stage_ContinueAnimation(909, 910) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(906, 907) == 0) {
#else
#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 337);

    scpPlayMot(scpSearchGobj(2556), 707);

    while (stage_ContinueAnimation(600, 601) == 0) {
#else
    while (stage_ContinueAnimation(910, 911) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 338);

    scpPlayMot(scpSearchGobj(2556), 708);

    while (stage_CheckAnimationFrame(601, 200, 0) == 0) {
#else
    scpPlayMot(boyGObj, 330);

    scpPlayMot(scpSearchGobj(2789), 740);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(907, 908) == 0) {
#else
    while (stage_ContinueAnimation(911, 912) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 331);

    scpPlayMot(scpSearchGobj(2789), 741);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(908, 909) == 0) {
#else
    while (stage_ContinueAnimation(912, 913) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 332);

    scpPlayMot(scpSearchGobj(2789), 742);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(909, 910) == 0) {
#else
    while (stage_ContinueAnimation(913, 914) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 333);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(910, 925) == 0) {
#else
    while (stage_ContinueAnimation(914, 929) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 341);

    scpPlayMot(scpSearchGobj(2789), 748);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(925, 926) == 0) {
#else
    while (stage_ContinueAnimation(929, 930) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 342);

    scpPlayMot(scpSearchGobj(2789), 749);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(926, 927) == 0) {
#else
    while (stage_ContinueAnimation(930, 931) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 343);

    scpPlayMot(scpSearchGobj(2789), 750);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(927, 928) == 0) {
#else
    while (stage_ContinueAnimation(931, 932) == 0) {
#endif
        _ACTWait(1);
    }

    scpPlayMot(boyGObj, 344);

    scpPlayMot(scpSearchGobj(2789), 751);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(928, 200, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(932, 200, 0) == 0) {
#endif
#endif
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

#ifdef VERSION_AUG6
    stage_SetAnimation(553, 1, 0);

    scpPlayPosSet(scpSearchGobj(2607), -7.0f, -5725.0f, 18.0f);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(880, 1, 0);
#else
    stage_SetAnimation(884, 1, 0);
#endif

    scpPlayPosSet(scpSearchGobj(2841), -7.0f, -5725.0f, 18.0f);
#endif

    ofs[0] = staff3DemoPos.d[0];
    ofs[1] = staff3DemoPos.d[1];
#ifdef VERSION_AUG6
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2607)));
    scpPlayMotDir(scpSearchGobj(2607), dir);

    scpPlayMot(scpSearchGobj(2607), 635);

    scpSearchGobj(2607)->active = 1;

    scpPlayMot(boyGObj, 302);

    while (stage_ContinueAnimation(553, 554) == 0) {
#else
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(scpSearchGobj(2841)));
    scpPlayMotDir(scpSearchGobj(2841), dir);

    scpPlayMot(scpSearchGobj(2841), 551);

    scpSearchGobj(2841)->active = 1;

    scpPlayMot(boyGObj, 308);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(880, 881) == 0) {
#else
    while (stage_ContinueAnimation(884, 885) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 303);

    while (stage_ContinueAnimation(554, 555) == 0) {
#else
    scpPlayMot(boyGObj, 309);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(881, 882) == 0) {
#else
    while (stage_ContinueAnimation(885, 886) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 304);

    while (stage_ContinueAnimation(555, 556) == 0) {
#else
    scpPlayMot(boyGObj, 310);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(882, 883) == 0) {
#else
    while (stage_ContinueAnimation(886, 887) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 305);

    while (stage_ContinueAnimation(556, 564) == 0) {
#else
    scpPlayMot(boyGObj, 311);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(883, 891) == 0) {
#else
    while (stage_ContinueAnimation(887, 895) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    stage_SetAnimation(61, 0, -1);

    scpPlayMot(scpSearchGobj(2607), 685);

    while (stage_ContinueAnimation(564, 565) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(70, 0, -1);
#else
    stage_SetAnimation(74, 0, -1);
#endif

    scpPlayMot(boyGObj, 318);

    scpPlayMot(scpSearchGobj(2841), 728);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(891, 892) == 0) {
#else
    while (stage_ContinueAnimation(895, 896) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(scpSearchGobj(2607), 686);

    while (stage_ContinueAnimation(565, 566) == 0) {
#else
    scpPlayMot(boyGObj, 318);

    scpPlayMot(scpSearchGobj(2841), 729);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(892, 893) == 0) {
#else
    while (stage_ContinueAnimation(896, 897) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 312);

    scpPlayMot(scpSearchGobj(2607), 687);

    while (stage_ContinueAnimation(566, 567) == 0) {
#else
    scpPlayMot(boyGObj, 318);

    scpPlayMot(scpSearchGobj(2841), 730);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(893, 894) == 0) {
#else
    while (stage_ContinueAnimation(897, 898) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 313);

    scpPlayMot(scpSearchGobj(2607), 688);

    while (stage_ContinueAnimation(567, 569) == 0) {
#else
    scpPlayMot(boyGObj, 319);

    scpPlayMot(scpSearchGobj(2841), 731);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(894, 896) == 0) {
#else
    while (stage_ContinueAnimation(898, 900) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 314);

    scpPlayMot(scpSearchGobj(2607), 689);

    while (stage_CheckAnimationFrame(569, 200, 0) == 0) {
#else
    scpPlayMot(boyGObj, 320);

    scpPlayMot(scpSearchGobj(2841), 732);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFrame(896, 200, 0) == 0) {
#else
    while (stage_CheckAnimationFrame(900, 200, 0) == 0) {
#endif
#endif
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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    fbKeep = 1;
    scpFadeOut(3.0f, 255, 255, 255);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    fbKeep = 0;
    ScpCallCameraSetTarget(7046.0f, -77.0f, 1678.0f);

#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(93, &sea, 1, 0, 1);

    SelectBoyCrown(boyGObj, 2);
    ed_demo14_mes[0].func = actEndDemo14Chk;
    act->mail = ed_demo14_mes;
    ACTSendMailCorrect(self, 393);
#else
    scpAdpcmPlayRequestFunc(95, &endDemo14, 1, 0, 1);

    while (endDemo14 == 0) {
        _ACTWait(1);
    }

    SelectBoyCrown(boyGObj, 2);
    SetGirlClothDispSwitch(scpSearchGobj(2253), 1, 2);
    ed_demo14_mes[0].func = actEndDemo14Chk;
    act->mail = ed_demo14_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actConte14_14(GObj *volatile self)
{
    long long ofs[2];
    float dir[4];

    scpPlayStart(boyGObj);

    scpFadeIn(6.0f);

#ifdef VERSION_AUG6
    stage_SetAnimation(785, 1, 0);

    scpPlayMot(boyGObj, 455);

    while (stage_ContinueAnimation(785, 786) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(856, 1, 0);
#else
    stage_SetAnimation(860, 1, 0);
#endif

    scpPlayMot(boyGObj, 461);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(856, 857) == 0) {
#else
    while (stage_ContinueAnimation(860, 861) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 456);

    while (stage_ContinueAnimation(786, 787) == 0) {
#else
    scpPlayMot(boyGObj, 462);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(857, 858) == 0) {
#else
    while (stage_ContinueAnimation(861, 862) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 457);
#else
    scpPlayMot(boyGObj, 463);
#endif

    _ACTWait(1);

#ifdef VERSION_AUG6
    stage_SetAnimation(51, 1, 0);

    while (stage_ContinueAnimation(787, 788) == 0) {
#else
    stage_SetAnimation(54, 1, 0);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(858, 859) == 0) {
#else
    while (stage_ContinueAnimation(862, 863) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 458);

    while (stage_ContinueAnimation(788, 789) == 0) {
#else
    scpPlayMot(boyGObj, 464);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(859, 860) == 0) {
#else
    while (stage_ContinueAnimation(863, 864) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 459);

    while (stage_ContinueAnimation(789, 790) == 0) {
#else
    scpPlayMot(boyGObj, 465);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(860, 861) == 0) {
#else
    while (stage_ContinueAnimation(864, 865) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 460);

    scpPlayMot(scpSearchGobj(2042), 786);

    scpSearchGobj(2042)->active = 1;

    while (stage_CheckAnimationFinish(790) == 0) {
#else
    scpPlayMot(boyGObj, 466);

    scpPlayMot(scpSearchGobj(2253), 829);

    scpSearchGobj(2253)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(861) == 0) {
#else
    while (stage_CheckAnimationFinish(865) == 0) {
#endif
#endif
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

#ifdef VERSION_AUG6
    lt_switch_layout(50);

    gflagOff(306);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(51);
#else
    lt_switch_layout(54);
#endif

    gflagOff(338);
}

void actSt27aEnd(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (gFlagGameClear == 0) {
        scpSearchGobj(2256)->active = 0;
        scpSearchGobj(2257)->active = 0;
        scpSearchGobj(2258)->active = 0;
        scpSearchGobj(2259)->active = 0;
        scpSearchGobj(2260)->active = 0;
        scpSearchGobj(2261)->active = 0;
        scpSearchGobj(2262)->active = 0;
        scpSearchGobj(2263)->active = 0;
    }

    if (gflagChk(355) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        act->mail = st27aEnd_mes;
        ACTSendMailCorrect(self, 430);
        _ACTWait(0);
    }
#endif
}

void actSt27aEndChk(GObj *volatile self)
{
    float max;
    float t;

    while (scpTriggerFloorAttr(boyGObj, 0x1000000) == 0) {
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);
    scpPlayMot(boyGObj, 0);

    if (sea != 0) {
        scpAdpcmFadeClose(sea, 27);
    }
    scpAdpcmPlayRequestFunc(49, &happy_end, 0, 1, 1);
    while (happy_end == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;

    if (GetCharHeldItem(boyGObj) == 3) {
        gflagOn(354);
        scpPlayMot(boyGObj, 157);
    }

    if (endDemo14 != 0) {
        scpAdpcmFadeCloseFunc(&endDemo14, 27);
    }
    scpAdpcmPlayRequestFunc(51, &st27aEnd, 0, 1, 1);
    while (st27aEnd == 0) {
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    gflagOn(322);
#else
    gflagOn(355);
#endif

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
#ifdef VERSION_AUG6
    stage_SetAnimation(791, 1, 0);

    scpPlayMot(boyGObj, 461);

    scpPlayMot(scpSearchGobj(2042), 787);

    scpSearchGobj(2042)->active = 1;

    while (stage_ContinueAnimation(791, 792) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(862, 1, 0);
#else
    stage_SetAnimation(866, 1, 0);
#endif

    if (gflagChk(354) == 0) {
        scpPlayMot(boyGObj, 467);
    } else {
        scpPlayMot(boyGObj, 470);
    }

    scpPlayMot(scpSearchGobj(2253), 830);

    scpSearchGobj(2253)->active = 1;

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(862, 863) == 0) {
#else
    while (stage_ContinueAnimation(866, 867) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 462);

    scpPlayMot(scpSearchGobj(2042), 788);

    while (stage_ContinueAnimation(792, 793) == 0) {
#else
    if (gflagChk(354) == 0) {
        scpPlayMot(boyGObj, 468);
    } else {
        scpPlayMot(boyGObj, 471);
    }

    scpPlayMot(scpSearchGobj(2253), 831);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_ContinueAnimation(863, 864) == 0) {
#else
    while (stage_ContinueAnimation(867, 868) == 0) {
#endif
#endif
        _ACTWait(1);
    }

#ifdef VERSION_AUG6
    scpPlayMot(boyGObj, 463);

    scpPlayMot(scpSearchGobj(2042), 789);

    while (stage_CheckAnimationFinish(793) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(1, boyGObj, girlGObj, 1.0f, 8.0f);
#else
    SetHandCameraLimitInDemo(10, 10);

    SetZoomMaxValInDemo(30);

    if (gflagChk(354) == 0) {
        scpPlayMot(boyGObj, 469);
    } else {
        scpPlayMot(boyGObj, 472);
    }

    scpPlayMot(scpSearchGobj(2253), 832);

    if (gflagChk(354) == 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFinish(864) == 0) {
#else
        while (stage_CheckAnimationFinish(868) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

        ResetHandCameraLimitInDemo();

        ResetZoomMaxValInDemo();

        RequestStageChange(1, boyGObj, girlGObj, 1.0f, 8.0f);
    } else {
        if (st27aEnd != 0) {
            scpAdpcmFadeCloseFunc(&st27aEnd, 80);
        }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(864, 390, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(868, 390, 0) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

        ResetHandCameraLimitInDemo();

        ResetZoomMaxValInDemo();

        scpFadeOut(6.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        scpDisActivateAllWithKind(19);

        scpFadeIn(1.5f);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(865, 1, 0);
#else
        stage_SetAnimation(869, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        stage_SetAnimation(194, 1, 0);
#else
        stage_SetAnimation(198, 1, 0);
#endif

        scpPlayMot(boyGObj, 473);

        scpPlayMot(scpSearchGobj(2253), 833);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (stage_CheckAnimationFrame(865, 390, 0) == 0) {
#else
        while (stage_CheckAnimationFrame(869, 390, 0) == 0) {
#endif
            _ACTWait(1);
        }
        _ACTWait(1);

        scpFadeOut(3.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        _ACTWait(10);

        scpPlayMot(boyGObj, 0);

        _ACTWait(10);

        RequestStageChange(1, boyGObj, girlGObj, 1.0f, 8.0f);
    }
}

#if defined(VERSION_JPN) || defined(VERSION_KOR)
/* The step between the logo and the save in the JPN and KOR builds; PAL's
   build named it actEndLogoChk and added the per-language logo animation
   before the wait. */
void actEndLogoFade(GObj *volatile self) /* derived name */
{
#else
void actEndLogoChk(GObj *volatile self)
{
#endif
    GObj *x = self;
    Act *act = actInitialize(self);
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)
    int id = 60;
#endif

    _ACTWait(1);

    scpBoyControlReadDisable = 1;
    enable_game_pause = 0;
#if !defined(VERSION_JPN) && !defined(VERSION_KOR)

    switch (NonLinearCameraMove) {
    case 3:
        id = 61;
        break;
    case 4:
        id = 62;
        break;
    case 6:
        id = 64;
        break;
    case 5:
        id = 63;
        break;
    }

    stage_SetLoopFlag(id, 1);

    stage_SetAnimation(id, 1, 0);
#endif

    SetHandCameraLimitInDemo(0, 0);

    SetZoomMaxValInDemo(0);

    preload(1);

    _ACTWait((60 - systemStatus[0] * 10) / systemStatus[1] * 30);

    scpFadeOut(6.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(60, -1, -2);
#else
    stage_SetAnimation(id, -1, -2);
#endif

    scpFadeIn(6.0f);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    end_mes[0].func = actEndLogoChk;
#else
    end_mes[0].func = actEndingSave;
#endif
    act->mail = end_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
#endif
}
#endif

void actEndDemo03(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

    if (boyGObj != 0) {
        scpPlayMot(boyGObj, 0);
    }

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    demo03_mes[0].func = actEndDemo03Chk;
    act->mail = demo03_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(70, 0, -1);
    stage_SetAnimation(71, 0, -1);
    stage_SetAnimation(73, 0, -1);
#else
    stage_SetAnimation(74, 0, -1);
    stage_SetAnimation(75, 0, -1);
    stage_SetAnimation(77, 0, -1);
#endif
    demo03_mes[0].func = actEndDemo03Chk;
    act->mail = demo03_mes;
    ACTSendMailCorrect(self, 430);
#endif
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

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    demo04_mes[0].func = actEndDemo04Chk;
    act->mail = demo04_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actEndDemo05(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    demo05_mes[0].func = actEndDemo05Chk;
    act->mail = demo05_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actEndDemo11(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    SelectBoyCrown(boyGObj, 2);
    demo11_mes[0].func = actEndDemo11Chk;
    act->mail = demo11_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actEndDemo12(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    stage_SetAnimation(67, 0, -1);
    demo12_mes[0].func = actEndDemo12Chk;
    act->mail = demo12_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(76, 0, -1);
#else
    stage_SetAnimation(80, 0, -1);
#endif
    demo12_mes[0].func = actEndDemo12Chk;
    act->mail = demo12_mes;
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actEndDemo13(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
#else
    lt_switch_layout(55);
#endif
#endif
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 255, 255, 255);
    SelectBoyCrown(boyGObj, 2);
    demo13_mes[0].func = actEndDemo13Chk;
    act->mail = demo13_mes;
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
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
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
#else
    ACTSendMailCorrect(self, 430);
#endif
    _ACTWait(0);
}

void actStaff2(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_NTSC
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    scpSetBoyWeaponGObj(scpSearchGobj(2591));
    stage_SetAnimation(238, 0, 0);
    stage_SetAnimation(258, 0, 0);
    staff2_mes[0].func = actStaff2Chk;
    act->mail = staff2_mes;
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
    stage_SetAnimation(237, 0, 0);
    stage_SetAnimation(257, 0, 0);
    staff2_mes[0].func = actStaff2Chk;
    act->mail = staff2_mes;
    ACTSendMailCorrect(self, 393);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpSetBoyWeaponGObj(scpSearchGobj(2795));
    scpSearchGobj(2793)->dobj->ctrl.seMute = 1;
    scpSearchGobj(2794)->dobj->ctrl.seMute = 1;
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(265, 0, 0);
#else
    stage_SetAnimation(269, 0, 0);
#endif
    staff2_mes[0].func = actStaff2Chk;
    act->mail = staff2_mes;
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actStaff3(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    lt_switch_layout(51);
    scpBoyControlReadDisable = 1;
#ifndef VERSION_AUG6
    DeleteBoyWeapon();
#endif
    stage_SetAnimation(59, 0, 0);
    stage_SetAnimation(64, 0, 0);
    staff3_mes[0].func = actStaff3Chk;
    act->mail = staff3_mes;
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 397);
#endif
    _ACTWait(0);
}

void actSt27aEnd(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#ifdef VERSION_AUG6
    if (gflagChk(322) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        act->mail = st27aEnd_mes;
        ACTSendMailCorrect(self, 393);
        _ACTWait(0);
    }
#else
    if (gflagChk(323) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        act->mail = st27aEnd_mes;
        ACTSendMailCorrect(self, 397);
        _ACTWait(0);
    }
#endif
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    lt_switch_layout(52);
#else
    lt_switch_layout(55);
#endif
    scpBoyControlReadDisable = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    DeleteBoyWeapon();
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(68, 0, 0);
    stage_SetAnimation(73, 0, 0);
#else
    stage_SetAnimation(72, 0, 0);
    stage_SetAnimation(77, 0, 0);
#endif
    staff3_mes[0].func = actStaff3Chk;
    act->mail = staff3_mes;
    ACTSendMailCorrect(self, 430);
    _ACTWait(0);
#endif
}

void actEndLogo(GObj *volatile self)
{
    GObj *x = self;
    Act *act = actInitialize(self);

    _ACTWait(1);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    logo_mes[0].func = actEndLogoFade;
#else
    logo_mes[0].func = actEndLogoChk;
#endif
    act->mail = logo_mes;
#ifdef VERSION_NTSC
    ACTSendMailCorrect(self, 397);
#else
#ifdef VERSION_AUG6
    ACTSendMailCorrect(self, 393);
#else
    ACTSendMailCorrect(self, 430);
#endif
#endif
    _ACTWait(0);
}

void actEndDemo01Chk(GObj *volatile self)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    scpAdpcmPlayRequestFunc(42, &ed1, 0, 1, 1);
#else
    scpAdpcmPlayRequestFunc(43, &ed1, 0, 1, 1);
#endif

    while (ed1 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(2);

    gflagOn(3);

    gflagOn(4);

#ifdef VERSION_NTSC
    gflagOn(308);
#else
#ifdef VERSION_AUG6
    gflagOn(307);
#else
    gflagOn(339);
#endif
#endif

    actCreateSubThread(actConte14_1, 21);
}

void actEndDemo02Chk(GObj *volatile self)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    scpAdpcmPlayRequestFunc(43, &ed2, 0, 1, 1);
#else
    scpAdpcmPlayRequestFunc(44, &ed2, 0, 1, 1);
#endif

    while (ed2 == 0) {
        _ACTWait(1);
    }

    preload(3);

    scpFadeIn(6.0f);

#ifdef VERSION_NTSC
    gflagOn(309);
#else
#ifdef VERSION_AUG6
    gflagOn(308);
#else
    gflagOn(340);
#endif
#endif

    actCreateSubThread(actConte14_2, 21);
}

void actEndDemo03Chk(GObj *volatile self)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    scpAdpcmPlayRequestFunc(44, &ed3, 0, 1, 1);
#else
    scpAdpcmPlayRequestFunc(45, &ed3, 0, 1, 1);
#endif

    while (ed3 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

#ifdef VERSION_NTSC
    gflagOn(310);
#else
#ifdef VERSION_AUG6
    gflagOn(309);
#else
    gflagOn(341);
#endif
#endif

    actCreateSubThread(actConte14_3, 21);
}

#ifdef VERSION_NTSC
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
#else
void actConte14_3(GObj *volatile self)
{
#ifdef VERSION_AUG6
    stage_SetAnimation(758, 1, 0);

    while (stage_CheckAnimationFinish(758) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(829, 1, 0);
#else
    stage_SetAnimation(833, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(829) == 0) {
#else
    while (stage_CheckAnimationFinish(833) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, 0, 1.0f, 8.0f);
}

void actEndDemo04Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(45, &ed4, 0, 1, 1);
#else
    scpAdpcmPlayRequestFunc(46, &ed4, 0, 1, 1);
#endif

    while (ed4 == 0) {
        _ACTWait(1);
    }

    preload(5);

    scpFadeIn(6.0f);

#ifdef VERSION_AUG6
    gflagOn(310);
#else
    gflagOn(342);
#endif

    actCreateSubThread(actConte14_4, 21);
}

void actConte14_4(GObj *volatile self)
{
#ifdef VERSION_AUG6
    stage_SetAnimation(759, 1, 0);

    while (stage_CheckAnimationFinish(759) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(830, 1, 0);
#else
    stage_SetAnimation(834, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(830) == 0) {
#else
    while (stage_CheckAnimationFinish(834) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(5, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo05Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    gflagOn(311);
#else
    gflagOn(343);
#endif

    actCreateSubThread(actConte14_5, 21);
}

void actConte14_5(GObj *volatile self)
{
    preload(6);

#ifdef VERSION_AUG6
    stage_SetAnimation(760, 1, 0);

    while (stage_CheckAnimationFinish(760) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(831, 1, 0);
#else
    stage_SetAnimation(835, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(831) == 0) {
#else
    while (stage_CheckAnimationFinish(835) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo06Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    gflagOff(307);

    gflagOff(311);
#else
    scpAdpcmPlayRequestFunc(47, &sea, 0, 1, 1);

    while (sea == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOff(339);

    gflagOff(343);
#endif

    actCreateSubThread(actConte14_6, 21);
}

void actEndDemo07Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(46, &ed5, 0, 1, 1);

    while (ed5 == 0) {
        _ACTWait(1);
    }
#else
    _ACTWait(30);
#endif

    scpFadeIn(6.0f);

#ifdef VERSION_AUG6
    gflagOn(313);
#else
    gflagOn(345);
#endif

    actCreateSubThread(actConte14_7, 21);
}

void actEndDemo10Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    scpAdpcmPlayRequestFunc(47, &ed6, 0, 1, 1);
#else
    scpAdpcmPlayRequestFunc(48, &ed6, 0, 1, 0);
#endif

    while (ed6 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

#ifdef VERSION_AUG6
    gflagOn(316);
#else
    gflagOn(348);
#endif

    actCreateSubThread(actConte14_10, 21);

    actCreateSubThread(actConte14_10_Jimaku, 21);
}
#endif

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
#ifdef VERSION_NTSC
    gflagOn(318);
#else
#ifdef VERSION_AUG6
    gflagOn(317);
#else
    gflagOn(349);
#endif
#endif

    actCreateSubThread(actConte14_11, 21);
}

#ifdef VERSION_NTSC
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
#else
void actConte14_11(GObj *volatile self)
{
    preload(2);

    scpPlayStart(boyGObj);

#ifdef VERSION_AUG6
    stage_SetAnimation(777, 1, 0);

    while (stage_CheckAnimationFinish(777) == 0) {
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(848, 1, 0);
#else
    stage_SetAnimation(852, 1, 0);
#endif

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(848) == 0) {
#else
    while (stage_CheckAnimationFinish(852) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, boyGObj, girlGObj, 1.0f, 8.0f);
}

void actEndDemo12Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    gflagOn(318);
#else
    gflagOn(350);
#endif

    actCreateSubThread(actConte14_12, 21);
}

void actConte14_12(GObj *volatile self)
{
#if defined(VERSION_JPN) || defined(VERSION_KOR)
    stage_SetAnimation(849, 1, 0);
#else
#ifdef VERSION_AUG6
    stage_SetAnimation(778, 1, 0);
#else
    stage_SetAnimation(853, 1, 0);
#endif
#endif

    preload(4);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    while (stage_CheckAnimationFinish(849) == 0) {
#else
#ifdef VERSION_AUG6
    while (stage_CheckAnimationFinish(778) == 0) {
#else
    while (stage_CheckAnimationFinish(853) == 0) {
#endif
#endif
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChangeWithColor(4, boyGObj, girlGObj, 16.0f, 16.0f, 255, 255, 255);
}

void actEndDemo13Chk(GObj *volatile self)
{
#ifdef VERSION_AUG6
    gflagOn(319);
#else
    gflagOn(351);
#endif

    actCreateSubThread(actConte14_13, 21);
}
#endif

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
#if !defined(VERSION_NTSC) && !defined(VERSION_AUG6)
    scpAdpcmPlayRequestFunc(49, &staff3, 0, 1, 1);

    while (staff3 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);
#endif

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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        scpAdpcmFadeClose(ed6, 80);
#else
        scpAdpcmFadeCloseFunc(&ed6, 80);
#endif
    }

    RequestStageChange(1, boyGObj, 0, 16.0f, 0.001f);
}

void actEndDemo14Chk(GObj *volatile self)
{
#ifdef VERSION_NTSC
    gflagOn(321);
#else
#ifdef VERSION_AUG6
    gflagOn(320);
#else
    gflagOn(352);
#endif
#endif

    actCreateSubThread(actConte14_14, 21);
}

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
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
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR)
/* The ending's save step.  The JPN and KOR builds still call it actEndLogoChk,
   its name in the Aug-6 disc's TRFILE (the last function of end.c there too);
   PAL's build renamed it actEndingSave and gave the name to the step before
   it. The bytes show the older name: actEndLogoFade hoists the %hi parts of
   end_mes and of this function above its fade loop, and gcse numbers them
   in hash-bucket order (31 buckets), which puts this one in s0 only when
   its name hashes before end_mes's, as actEndLogoChk does and actEndingSave
   (the last bucket) cannot. */
static void actEndLogoChk(GObj *volatile self)
{
#else
static void actEndingSave(GObj *volatile self)
{
#endif
    if (gFlagGameClear == 0) {
        int save;

        gFlagGameClear = 1;
        save = IosMcPreviewInfo[2];
        gflagInit();
        IosMcPreviewInfo[2] = save;
        gflagOn(395);
#if defined(VERSION_JPN) || defined(VERSION_KOR)
        lt_switch_layout(25);
#else
        lt_switch_layout(28);
#endif
        _ACTWait(60);

#if defined(VERSION_JPN) || defined(VERSION_KOR)
        while (current_layout_id != 51) {
#else
        while (current_layout_id != 54) {
#endif
            _ACTWait(1);
        }
        gFlagGameClear = 0;
    }

#if defined(VERSION_JPN) || defined(VERSION_KOR)
    scpFadeOut(6.0f, 0, 0, 0);
#else
    scpFadeOut(255.0f, 0, 0, 0);
#endif

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    optionScreenMode = 0;
    RequestStageChange(1, boyGObj, 0, 255.0f, 8.0f);
}
#endif
