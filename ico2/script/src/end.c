#include "common.h"
#include "end.h"
#include "layout_texture.h"
#include "adpcm_init.h"
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

/* kept local: this TU's bytes only come out with its own view of PObjGObj, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PObjGObjEnd {
    char pad00[0x15C]; /* 0x000 */
    char *f15C;        /* 0x15C */
    char pad160[0x4];  /* 0x160 */
    Act *act;          /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObjEnd;

/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);

static ActMail demo01_mes[2] = {{430}, {429}};

static ActMail demo02_mes[2] = {{430}, {429}};

static ActMail demo03_mes[2] = {{430}, {429}};

static ActMail demo04_mes[2] = {{430}, {429}};

static ActMail demo05_mes[2] = {{430}, {429}};

static ActMail demo06_mes[2] = {{430}, {429}};

static ActMail demo07_mes[2] = {{430}, {429}};

static ActMail demo10_mes[2] = {{430}, {429}};

static ActMail demo11_mes[2] = {{430}, {429}};

static ActMail demo12_mes[2] = {{430}, {429}};

static ActMail demo13_mes[2] = {{430}, {429}};

static ActMail staff1_mes[2] = {{430}, {429}};

static ActMail staff2_mes[2] = {{430}, {429}};

static ActMail staff3_mes[2] = {{430}, {429}};

static ActMail ed_demo14_mes[2] = {{430}, {429}};

static ActMail st27aEnd_mes[2] = {{430}, {429}};

static ActMail logo_mes[2] = {{430}, {429}};

static ActMail end_mes[2] = {{430}, {429}};

extern int D_0063AA08;

void actEndDemo01(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(339) == 0 && gflagChk(343) == 0) {
        lt_switch_layout(55);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(840, 0, 0);
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, -1);
        stage_SetAnimation(33, 0, -1);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
        demo01_mes[0].func = actEndDemo01Chk;
        self->mail = demo01_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObjEnd *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern int D_00639EA4;

void actConte14_1(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(814, 1, 0);

    scpPlayMot((int)scpSearchGobj(2515), 809);

    scpSearchGobj(2515)->f16C = 1;

    while (stage_ContinueAnimation(814, 815) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(815, 816) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(55, 1, 0);

    while (stage_ContinueAnimation(816, 817) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(817, 818) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(818, 819) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(2515), 810);

    while (stage_ContinueAnimation(819, 820) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(2515)->f16C = 0;

    scpPlayMot((int)scpSearchGobj(2516), 811);

    scpSearchGobj(2516)->f16C = 1;

    scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0x9D4, 0, 0x22A, 0);

    stage_SetLoopFlag(554, 1);

    stage_SetAnimation(554, 1, 0);

    while (stage_ContinueAnimation(820, 821) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(2516), 812);

    while (stage_ContinueAnimation(821, 822) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(2516), 813);

    while (stage_ContinueAnimation(822, 823) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(2516), 814);

    while (stage_CheckAnimationFinish(823) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, D_00639EA4, 0, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);

void actEndDemo02(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 0x22A, 0);
    stage_SetLoopFlag(554, 1);
    stage_SetAnimation(554, 1, 0);
    stage_SetAnimation(825, 0, 0);
    stage_SetAnimation(556, 0, -1);
    stage_SetAnimation(557, 0, -1);
    stage_SetAnimation(559, 0, -1);
    stage_SetAnimation(560, 0, -1);
    stage_SetAnimation(561, 0, -1);
    SelectBoyCrown(D_00639EA4, 2);
    demo02_mes[0].func = actEndDemo02Chk;
    self->mail = demo02_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);

void actConte14_2(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(824, 1, 0);

    scpPlayMot(D_00639EA4, 441);

    while (stage_ContinueAnimation(824, 825) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(825, 826) == 0) {
        _ACTWait(1);
    }

    scpPlayMot((int)scpSearchGobj(2686), 815);

    scpSearchGobj(2686)->f16C = 1;

    _ACTWait(1);

    stage_SetAnimation(827, 1, 0);

    while (stage_ContinueAnimation(826, 828) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 442);

    scpPlayMot((int)scpSearchGobj(2686), 816);

    while (stage_ContinueAnimation(828, 829) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 443);

    scpPlayMot((int)scpSearchGobj(2686), 817);

    while (stage_ContinueAnimation(829, 830) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 444);

    scpPlayMot((int)scpSearchGobj(2686), 818);

    while (stage_ContinueAnimation(830, 831) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 445);

    scpPlayMot((int)scpSearchGobj(2686), 819);

    _ACTWait(1);

    stage_SetAnimation(832, 1, 0);

    while (stage_CheckAnimationFinish(831) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(D_00639EA4);

    lt_switch_layout(54);

    RequestStageChange(3, D_00639EA4, 0, 1.0f, 8.0f);
}

void actEndDemo06(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(344) == 0 && gflagChk(343) != 0) {
        lt_switch_layout(55);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        scpLinkBGAtoLayoutedTargetSkeltonWithLocalRotationFlag(0x9D4, 0, 0x22A, 0);
        stage_SetLoopFlag(554, 1);
        stage_SetAnimation(554, 1, 0);
        stage_SetAnimation(840, 0, 0);
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, 0);
        stage_SetAnimation(35, 0, -1);
        stage_SetAnimation(33, 0, -1);
        stage_SetAnimation(34, 0, -1);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
        SelectBoyCrown(D_00639EA4, 2);
        demo06_mes[0].func = actEndDemo06Chk;
        self->mail = demo06_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
extern int D_00639EA8;

void actConte14_6(volatile int a0)
{
    preload(3);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(838, 1, 0);

    stage_SetAnimation(840, 1, 0);

    stage_SetAnimation(841, 1, 0);

    scpPlayMot(D_00639EA4, 446);

    scpPlayMot((int)scpSearchGobj(2516), 820);

    scpSearchGobj(2516)->f16C = 1;

    while (stage_ContinueAnimation(838, 839) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 447);

    scpPlayMot((int)scpSearchGobj(2516), 821);

    while (stage_CheckAnimationFinish(839) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

void actEndDemo07(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 0x22A, 0);
    stage_SetAnimation(173, 0, 0);
    stage_SetLoopFlag(554, 1);
    stage_SetAnimation(554, 1, 0);

    if (gflagChk(345) == 0) {
        SelectBoyCrown(D_00639EA4, 2);
        demo07_mes[0].func = actEndDemo07Chk;
        self->mail = demo07_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpPlayMotNode do not fit the prototype in script.h */
extern void scpPlayMotNode(int a0, int mot, int node, int a3);

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */

static const ConstVec conte14_7Pos = {{-4743.0f, -661.0f, 2503.0f, 1.0f}};

static const ConstVec staff3DemoPos = {{-800.0f, 0.0f, -1000.0f, 1.0f}};

static const ConstVec conte14_14Pos = {{16975.0f, 71.0f, -4332.0f, 1.0f}};

void actConte14_7(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    preload(6);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(842, 1, 0);

    stage_SetAnimation(173, 1, 0x1D7);

    _ACTWait(1);

    scpPlayPosSet(D_00639EA4, -4757.0f, -660.0f, 2646.0f);

    scpPlayPosSet((int)scpSearchGobj(2388), -4757.0f, -664.0f, 2646.0f);

    _ACTWait(1);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    ofs[0] = conte14_7Pos.d[0];
    ofs[1] = conte14_7Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)scpSearchGobj(2388)));
    scpPlayMotDir((int)scpSearchGobj(2388), dir);

    scpPlayMotNode(D_00639EA4, 0x1C0, (int)scpSearchGobj(2388), 0x2C);

    scpPlayMot((int)scpSearchGobj(2388), 822);

    scpSearchGobj(2388)->f16C = 1;

    while (stage_CheckAnimationFinish(842) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

void actEndDemo10(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0, 0x22A, 0);
    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(3, 0x34, 0x3A, 0);
    stage_SetLoopFlag(554, 1);
    stage_SetAnimation(554, 1, 0);
    SelectBoyCrown(D_00639EA4, 2);
    stage_SetAnimation(850, 0, 0);
    demo10_mes[0].func = actEndDemo10Chk;
    self->mail = demo10_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int ed6;

void actConte14_10(volatile int a0)
{
    preload(3);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(843, 1, 0);

    scpPlayMot(D_00639EA4, 449);

    scpPlayMot((int)scpSearchGobj(2122), 823);

    scpSearchGobj(2122)->f16C = 1;

    _ACTWait(1);

    stage_SetAnimation(45, 1, 0);

    stage_SetAnimation(844, 1, 0);

    while (stage_ContinueAnimation(843, 845) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 450);

    scpPlayMot((int)scpSearchGobj(2122), 824);

    _ACTWait(1);

    stage_SetAnimation(46, 1, 0);

    while (stage_ContinueAnimation(845, 846) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 451);

    scpPlayMot((int)scpSearchGobj(2122), 825);

    _ACTWait(1);

    stage_SetAnimation(47, 1, 0);

    while (stage_ContinueAnimation(846, 847) == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(ed6 + 0x2C));

    scpPlayMot(D_00639EA4, 452);

    scpPlayMot((int)scpSearchGobj(2122), 826);

    _ACTWait(1);

    stage_SetAnimation(48, 1, 0);

    while (stage_ContinueAnimation(847, 848) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 453);

    scpPlayMot((int)scpSearchGobj(2122), 827);

    _ACTWait(1);

    stage_SetAnimation(49, 1, 0);

    while (stage_ContinueAnimation(848, 849) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 454);

    _ACTWait(1);

    stage_SetAnimation(50, 1, 0);

    stage_SetAnimation(56, 1, 0);

    stage_SetAnimation(850, 1, 0);

    while (stage_ContinueAnimation(849, 851) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 455);

    _ACTWait(1);

    stage_SetAnimation(51, 1, 0);

    stage_SetAnimation(57, 1, 0);

    while (stage_CheckAnimationFinish(851) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(3, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);

void actConte14_13(volatile int a0)
{
    scpPlayStart(D_00639EA4);

    scpFadeIn(3.0f);

    preload(6);

    stage_SetAnimation(854, 1, 0);

    scpPlayMot(D_00639EA4, 456);

    while (stage_ContinueAnimation(854, 855) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(53, 1, 0);

    stage_SetAnimation(465, 1, 0);

    scpPlayMot(D_00639EA4, 456);

    while (stage_CheckAnimationFinish(855) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpPlayEnd(D_00639EA4);

    RequestStageChange(6, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

void actStaff1(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    stage_SetAnimation(30, 0, -1);
    stage_SetAnimation(26, 0, 0);
    stage_SetAnimation(33, 0, 0);
    stage_SetAnimation(34, 0, 0);
    stage_SetAnimation(36, 0, 0);
    stage_SetAnimation(38, 0, 0);
    stage_SetAnimation(35, 0, 0);
    staff1_mes[0].func = actStaff1Chk;
    self->mail = staff1_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: the declaration in staffroll.h changes this TU codegen */
extern void staffRollStart(int a0, float a1);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);

void actStaff1Demo(volatile int a0)
{
    preload(1);

    staffRollStart(0xFF, 1.0f);

    stage_SetAnimation(870, 1, 0);

    while (stage_ContinueAnimation(870, 871) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(26, 1, 0);

    scpPlayMot(D_00639EA4, 288);

    while (stage_ContinueAnimation(871, 873) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(873, 874) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 289);

    _ACTWait(130);

    stage_SetAnimation(32, 1, 0);

    while (stage_ContinueAnimation(874, 875) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(875, 876) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 290);

    while (stage_ContinueAnimation(876, 877) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(877, 878) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 292);

    _ACTWait(1);

    stage_SetAnimation(32, 1, 0xD0);

    while (stage_ContinueAnimation(878, 879) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 293);

    while (stage_ContinueAnimation(879, 880) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 294);

    while (stage_ContinueAnimation(880, 881) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 295);

    while (stage_ContinueAnimation(881, 882) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 296);

    while (stage_ContinueAnimation(882, 883) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 297);

    while (stage_CheckAnimationFrame(883, 100, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(8.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, D_00639EA8, 0.0f, 8.0f);
}

void actStaff2Demo(volatile int a0)
{
    preload(1);

    stage_SetAnimation(907, 1, 0);

    stage_SetAnimation(269, 1, 0);

    scpPlayMot(D_00639EA4, 327);

    scpPlayMot((int)scpSearchGobj(2789), 737);

    scpSearchGobj(2789)->f16C = 1;

    while (stage_ContinueAnimation(907, 908) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 328);

    scpPlayMot((int)scpSearchGobj(2789), 738);

    while (stage_ContinueAnimation(908, 909) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 329);

    scpPlayMot((int)scpSearchGobj(2789), 739);

    while (stage_ContinueAnimation(909, 910) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(910, 911) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 330);

    scpPlayMot((int)scpSearchGobj(2789), 740);

    while (stage_ContinueAnimation(911, 912) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 331);

    scpPlayMot((int)scpSearchGobj(2789), 741);

    while (stage_ContinueAnimation(912, 913) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 332);

    scpPlayMot((int)scpSearchGobj(2789), 742);

    while (stage_ContinueAnimation(913, 914) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 333);

    while (stage_ContinueAnimation(914, 929) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 341);

    scpPlayMot((int)scpSearchGobj(2789), 748);

    while (stage_ContinueAnimation(929, 930) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 342);

    scpPlayMot((int)scpSearchGobj(2789), 749);

    while (stage_ContinueAnimation(930, 931) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 343);

    scpPlayMot((int)scpSearchGobj(2789), 750);

    while (stage_ContinueAnimation(931, 932) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 344);

    scpPlayMot((int)scpSearchGobj(2789), 751);

    while (stage_CheckAnimationFrame(932, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    reg_SetScissorSw(0);

    SetStaticBlur(1);

    scpFadeOut(8.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    RequestStageChange(1, D_00639EA4, D_00639EA8, 0.0f, 8.0f);
}

void actStaff3Demo(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    stage_SetAnimation(884, 1, 0);

    scpPlayPosSet((int)scpSearchGobj(2841), -7.0f, -5725.0f, 18.0f);

    ofs[0] = staff3DemoPos.d[0];
    ofs[1] = staff3DemoPos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)scpSearchGobj(2841)));
    scpPlayMotDir((int)scpSearchGobj(2841), dir);

    scpPlayMot((int)scpSearchGobj(2841), 551);

    scpSearchGobj(2841)->f16C = 1;

    scpPlayMot(D_00639EA4, 308);

    while (stage_ContinueAnimation(884, 885) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 309);

    while (stage_ContinueAnimation(885, 886) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 310);

    while (stage_ContinueAnimation(886, 887) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 311);

    while (stage_ContinueAnimation(887, 895) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(74, 0, -1);

    scpPlayMot(D_00639EA4, 318);

    scpPlayMot((int)scpSearchGobj(2841), 728);

    while (stage_ContinueAnimation(895, 896) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 318);

    scpPlayMot((int)scpSearchGobj(2841), 729);

    while (stage_ContinueAnimation(896, 897) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 318);

    scpPlayMot((int)scpSearchGobj(2841), 730);

    while (stage_ContinueAnimation(897, 898) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 319);

    scpPlayMot((int)scpSearchGobj(2841), 731);

    while (stage_ContinueAnimation(898, 900) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 320);

    scpPlayMot((int)scpSearchGobj(2841), 732);

    while (stage_CheckAnimationFrame(900, 200, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(6.0f, 0, 0, 0);
}

/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);

/* Demo 14's mail record: the actor installs actEndDemo14Chk in it and posts
   it. Word 0 of each entry is the mail id the entry answers (430 the actor
   post, 429 the trailing entry); .func is filled in at run time. Named in
   this TU's own terse snake_case house style (its MAIN.MAP globals are
   ed1..ed6, sea, happy_end) for the ending demo it belongs to. */

extern int fbKeep;
extern int D_0063BE34;

void actEndDemo14(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    fbKeep = 1;
    scpFadeOut(3.0f, 0xFF, 0xFF, 0xFF);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    fbKeep = 0;
    ScpCallCameraSetTarget(7046.0f, -77.0f, 1678.0f);

    scpAdpcmPlayRequestFunc(95, &D_0063BE34, 1, 0, 1);

    while (D_0063BE34 == 0) {
        _ACTWait(1);
    }

    SelectBoyCrown(D_00639EA4, 2);
    SetGirlClothDispSwitch(scpSearchGobj(2253), 1, 2);
    ed_demo14_mes[0].func = actEndDemo14Chk;
    self->mail = ed_demo14_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actConte14_14(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    scpPlayStart(D_00639EA4);

    scpFadeIn(6.0f);

    stage_SetAnimation(860, 1, 0);

    scpPlayMot(D_00639EA4, 461);

    while (stage_ContinueAnimation(860, 861) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 462);

    while (stage_ContinueAnimation(861, 862) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 463);

    _ACTWait(1);

    stage_SetAnimation(54, 1, 0);

    while (stage_ContinueAnimation(862, 863) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 464);

    while (stage_ContinueAnimation(863, 864) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 465);

    while (stage_ContinueAnimation(864, 865) == 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA4, 466);

    scpPlayMot((int)scpSearchGobj(2253), 829);

    scpSearchGobj(2253)->f16C = 1;

    while (stage_CheckAnimationFinish(865) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    _ACTWait(180);

    scpPlayMot(D_00639EA4, 0);

    ofs[0] = conte14_14Pos.d[0];
    ofs[1] = conte14_14Pos.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    lt_switch_layout(54);

    gflagOff(338);
}

extern int D_0063AA00;

void actSt27aEnd(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_0063AA00 == 0) {
        scpSearchGobj(2256)->f16C = 0;
        scpSearchGobj(2257)->f16C = 0;
        scpSearchGobj(2258)->f16C = 0;
        scpSearchGobj(2259)->f16C = 0;
        scpSearchGobj(2260)->f16C = 0;
        scpSearchGobj(2261)->f16C = 0;
        scpSearchGobj(2262)->f16C = 0;
        scpSearchGobj(2263)->f16C = 0;
    }

    if (gflagChk(355) == 0) {
        st27aEnd_mes[0].func = actSt27aEndChk;
        self->mail = st27aEnd_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern float D_0063AA0C;
extern int D_0063BE38;
extern int D_0028F4C0[];
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int gobj, int attr);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *h, int a2, int a3, int a4);

/* listing lines 2614-2661 */
void actSt27aEndChk(volatile int a0)
{
    float max;
    float t;

    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;

    if (GetCharHeldItem(D_00639EA4) == 3) {
        gflagOn(354);
        scpPlayMot(D_00639EA4, 157);
    }

    if (D_0063BE34 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BE34, 0x1B);
    }
    scpAdpcmPlayRequestFunc(51, &D_0063BE38, 0, 1, 1);
    while (D_0063BE38 == 0) {
        _ACTWait(1);
    }

    gflagOn(355);

    actCreateSubThread(actSt27aEndDemo, 21);

    max = (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 20);
    t = (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 20);
    while (t > 0.0f) {
        D_0063AA0C = t / max;
        t -= 1.0f;
        _ACTWait(1);
    }
    D_0063AA0C = 0;
}

/* kept local: this TU's uses of scpDisActivateAllWithKind do not fit the prototype in script.h */
extern void scpDisActivateAllWithKind(int a0);

void actSt27aEndDemo(volatile int a0)
{
    stage_SetAnimation(866, 1, 0);

    if (gflagChk(354) == 0) {
        scpPlayMot(D_00639EA4, 467);
    } else {
        scpPlayMot(D_00639EA4, 470);
    }

    scpPlayMot((int)scpSearchGobj(2253), 830);

    scpSearchGobj(2253)->f16C = 1;

    while (stage_ContinueAnimation(866, 867) == 0) {
        _ACTWait(1);
    }

    if (gflagChk(354) == 0) {
        scpPlayMot(D_00639EA4, 468);
    } else {
        scpPlayMot(D_00639EA4, 471);
    }

    scpPlayMot((int)scpSearchGobj(2253), 831);

    while (stage_ContinueAnimation(867, 868) == 0) {
        _ACTWait(1);
    }

    SetHandCameraLimitInDemo(0xA, 0xA);

    SetZoomMaxValInDemo(0x1E);

    if (gflagChk(354) == 0) {
        scpPlayMot(D_00639EA4, 469);
    } else {
        scpPlayMot(D_00639EA4, 472);
    }

    scpPlayMot((int)scpSearchGobj(2253), 832);

    if (gflagChk(354) == 0) {
        while (stage_CheckAnimationFinish(868) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        ResetHandCameraLimitInDemo();

        ResetZoomMaxValInDemo();

        RequestStageChange(1, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
    } else {
        if (D_0063BE38 != 0) {
            scpAdpcmFadeCloseFunc(&D_0063BE38, 0x50);
        }

        while (stage_CheckAnimationFrame(868, 390, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        ResetHandCameraLimitInDemo();

        ResetZoomMaxValInDemo();

        scpFadeOut(6.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        scpDisActivateAllWithKind(0x13);

        scpFadeIn(1.5f);

        stage_SetAnimation(869, 1, 0);

        stage_SetAnimation(198, 1, 0);

        scpPlayMot(D_00639EA4, 473);

        scpPlayMot((int)scpSearchGobj(2253), 833);

        while (stage_CheckAnimationFrame(869, 390, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        scpFadeOut(3.0f, 0, 0, 0);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        _ACTWait(10);

        scpPlayMot(D_00639EA4, 0);

        _ACTWait(10);

        RequestStageChange(1, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
    }
}

/* The ending's save hand-off mail record: the logo watcher installs
   actEndingSave in it and posts it. Word 0 of each entry is the mail id the
   entry answers (430 the actor post, 429 the trailing entry); .func is
   filled in at run time. Named in this TU's own terse snake_case house style
   (its MAIN.MAP globals are ed1..ed6, sea, happy_end) for the sequence it
   belongs to; among the role-plausible spellings this is one that also puts
   the record ahead of the handler in gcc's expression-hash order. */

extern int NonLinearCameraMove;
extern int enable_game_pause;

void actEndLogoChk(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    int id = 0x3C;

    _ACTWait(1);

    D_0063AA08 = 1;
    enable_game_pause = 0;

    switch (NonLinearCameraMove) {
    case 3:
        id = 0x3D;
        break;
    case 4:
        id = 0x3E;
        break;
    case 6:
        id = 0x40;
        break;
    case 5:
        id = 0x3F;
        break;
    }

    stage_SetLoopFlag(id, 1);

    stage_SetAnimation(id, 1, 0);

    SetHandCameraLimitInDemo(0, 0);

    SetZoomMaxValInDemo(0);

    preload(1);

    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x1E);

    scpFadeOut(6.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(id, -1, -2);

    scpFadeIn(6.0f);

    end_mes[0].func = actEndingSave;
    self->mail = end_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndDemo03(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    stage_SetAnimation(74, 0, -1);
    stage_SetAnimation(75, 0, -1);
    stage_SetAnimation(77, 0, -1);
    demo03_mes[0].func = actEndDemo03Chk;
    self->mail = demo03_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndDemo04(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (D_00639EA4 != 0) {
        scpPlayMot(D_00639EA4, 0);
    }

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    demo04_mes[0].func = actEndDemo04Chk;
    self->mail = demo04_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndDemo05(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    demo05_mes[0].func = actEndDemo05Chk;
    self->mail = demo05_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndDemo11(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    SelectBoyCrown(D_00639EA4, 2);
    demo11_mes[0].func = actEndDemo11Chk;
    self->mail = demo11_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndDemo12(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    stage_SetAnimation(80, 0, -1);
    demo12_mes[0].func = actEndDemo12Chk;
    self->mail = demo12_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndDemo13(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0xFF, 0xFF, 0xFF);
    SelectBoyCrown(D_00639EA4, 2);
    demo13_mes[0].func = actEndDemo13Chk;
    self->mail = demo13_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* kept local: this TU's uses of scpSetBoyWeaponGObj do not fit the prototype in script.h */
extern void scpSetBoyWeaponGObj(PObjGObjEnd *gobj);

void actStaff2(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpSetBoyWeaponGObj(scpSearchGobj(2795));
    *(int *)(scpSearchGobj(2793)->f15C + 0x658) = 1;
    *(int *)(scpSearchGobj(2794)->f15C + 0x658) = 1;
    stage_SetAnimation(269, 0, 0);
    staff2_mes[0].func = actStaff2Chk;
    self->mail = staff2_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actStaff3(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpFadeOut(255.0f, 0, 0, 0);
    DeleteBoyWeapon();
    stage_SetAnimation(72, 0, 0);
    stage_SetAnimation(77, 0, 0);
    staff3_mes[0].func = actStaff3Chk;
    self->mail = staff3_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actEndLogo(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    logo_mes[0].func = actEndLogoChk;
    self->mail = logo_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern int ed1;

void actEndDemo01Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(43, &ed1, 0, 1, 1);

    while (ed1 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(2);

    gflagOn(3);

    gflagOn(4);

    gflagOn(339);

    actCreateSubThread(actConte14_1, 21);
}

extern int ed2;

void actEndDemo02Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(44, &ed2, 0, 1, 1);

    while (ed2 == 0) {
        _ACTWait(1);
    }

    preload(3);

    scpFadeIn(6.0f);

    gflagOn(340);

    actCreateSubThread(actConte14_2, 21);
}

extern int ed3;

void actEndDemo03Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(45, &ed3, 0, 1, 1);

    while (ed3 == 0) {
        _ACTWait(1);
    }

    preload(2);

    scpFadeIn(6.0f);

    gflagOn(341);

    actCreateSubThread(actConte14_3, 21);
}

void actConte14_3(volatile int a0)
{
    stage_SetAnimation(833, 1, 0);

    while (stage_CheckAnimationFinish(833) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, D_00639EA4, 0, 1.0f, 8.0f);
}

extern int ed4;

void actEndDemo04Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(46, &ed4, 0, 1, 1);

    while (ed4 == 0) {
        _ACTWait(1);
    }

    preload(5);

    scpFadeIn(6.0f);

    gflagOn(342);

    actCreateSubThread(actConte14_4, 21);
}

void actConte14_4(volatile int a0)
{
    stage_SetAnimation(834, 1, 0);

    while (stage_CheckAnimationFinish(834) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(5, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

void actEndDemo05Chk(volatile int a0)
{
    gflagOn(343);

    actCreateSubThread(actConte14_5, 21);
}

void actConte14_5(volatile int a0)
{
    preload(6);

    stage_SetAnimation(835, 1, 0);

    while (stage_CheckAnimationFinish(835) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(6, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

extern int sea;

void actEndDemo06Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(47, &sea, 0, 1, 1);

    while (sea == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOff(339);

    gflagOff(343);

    actCreateSubThread(actConte14_6, 21);
}

void actEndDemo07Chk(volatile int a0)
{
    _ACTWait(30);

    scpFadeIn(6.0f);

    gflagOn(345);

    actCreateSubThread(actConte14_7, 21);
}

void actEndDemo10Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(48, &ed6, 0, 1, 0);

    while (ed6 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    gflagOn(348);

    actCreateSubThread(actConte14_10, 21);

    actCreateSubThread(actConte14_10_Jimaku, 21);
}

extern JimakuArg jimaku_msg;
extern int jimakuOn;

void actConte14_10_Jimaku(volatile int a0)
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
        case 1500:
            jimaku_msg.sub.unk2C = 0x70;
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
    } while (t < 1800.0f);
}

void actEndDemo11Chk(volatile int a0)
{
    gflagOn(349);

    actCreateSubThread(actConte14_11, 21);
}

void actConte14_11(volatile int a0)
{
    preload(2);

    scpPlayStart(D_00639EA4);

    stage_SetAnimation(852, 1, 0);

    while (stage_CheckAnimationFinish(852) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChange(2, D_00639EA4, D_00639EA8, 1.0f, 8.0f);
}

void actEndDemo12Chk(volatile int a0)
{
    gflagOn(350);

    actCreateSubThread(actConte14_12, 21);
}

/* kept local: this TU's uses of RequestStageChangeWithColor do not fit the prototype in script.h */
extern int RequestStageChangeWithColor(int a0, int a1, int a2, float a3, float a4, int r, int g,
                                       int b);

void actConte14_12(volatile int a0)
{
    stage_SetAnimation(853, 1, 0);

    preload(4);

    while (stage_CheckAnimationFinish(853) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    RequestStageChangeWithColor(4, D_00639EA4, D_00639EA8, 16.0f, 16.0f, 0xFF, 0xFF, 0xFF);
}

void actEndDemo13Chk(volatile int a0)
{
    gflagOn(351);

    actCreateSubThread(actConte14_13, 21);
}

void actStaff1Chk(volatile int a0)
{
    actCreateSubThread(actStaff1Demo, 21);
}

void actStaff2Chk(volatile int a0)
{
    reg_SetScissorSw(1);

    SetStaticBlur(0);

    actCreateSubThread(actStaff2Demo, 21);
}

extern int D_0063BE30;

void actStaff3Chk(volatile int a0)
{
    scpAdpcmPlayRequestFunc(49, &D_0063BE30, 0, 1, 1);

    while (D_0063BE30 == 0) {
        _ACTWait(1);
    }

    scpFadeIn(6.0f);

    actCreateSubThread(actStaff3Demo, 21);

    actCreateSubThread(actStaff3RollChk, 21);
}

extern int staffRollStartFlag;

void actStaff3RollChk(volatile int a0)
{
    preload(1);

    while (staffRollStartFlag != 0) {
        _ACTWait(1);
    }

    if (ed6 != 0) {
        scpAdpcmFadeCloseFunc(&ed6, 0x50);
    }

    RequestStageChange(1, D_00639EA4, 0, 16.0f, 0.001f);
}

void actEndDemo14Chk(volatile int a0)
{
    gflagOn(352);

    actCreateSubThread(actConte14_14, 21);
}

extern int D_0029B9D0[];
extern int D_0063B60C;
extern int CurrentTargetGObjSub;

void actEndingSave(volatile int a0)
{
    if (D_0063AA00 == 0) {
        int save;

        D_0063AA00 = 1;
        save = D_0029B9D0[2];
        gflagInit();
        D_0029B9D0[2] = save;
        gflagOn(395);
        lt_switch_layout(28);
        _ACTWait(60);

        while (D_0063B60C != 0x36) {
            _ACTWait(1);
        }
        D_0063AA00 = 0;
    }

    scpFadeOut(255.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    CurrentTargetGObjSub = 0;
    RequestStageChange(1, D_00639EA4, 0, 255.0f, 8.0f);
}
