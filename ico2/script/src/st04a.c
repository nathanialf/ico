#include "common.h"
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
#include "streamMotionManager.h"
#include <libvu0.h>
#include "e3.h"
#include "typedef.h"

/* kept local: this TU's bytes only come out with its own view of Act, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct ActSt04A {
    char unk00[0x20];  /* 0x00 */
    ActStatus flags20; /* 0x20 */
    char unk28[0xC];   /* 0x28 */
    int unk34;         /* 0x34 */
    char unk38[0x98];  /* 0x38 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
    char unkD8[0x398]; /* 0xD8 */
    int unk470;        /* 0x470 */
    void *unk474;      /* 0x474 */
    int unk478;        /* 0x478 */
} ActSt04A;

/* kept local: this TU's bytes only come out with its own view of PObjGObj, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef struct PObjGObjSt04A {
    char pad00[0x15C]; /* 0x000 */
    char *f15C;        /* 0x15C */
    char pad160[0x4];  /* 0x160 */
    ActSt04A *act;     /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObjSt04A;

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObjSt04A *scpSearchGobj(int a0);
/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, void *a1, float radius);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(void *a0, int a1);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern char *D_00639EA4;
extern char *D_00639EA8;
extern int D_0028F4C0[];
extern float D_0063AA0C;
extern ActMail D_004F85D0[];

void actSt04aGate(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    scpSearchGobj(590)->f16C = 0;

    if (gflagChk(137) == 0) {
        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetLoopFlag(555, 0);

        stage_SetAnimation(269, 0, 0);
        stage_SetAnimation(272, 0, 0);

        gflagOff(390);

        D_004F85D0[0].func = actSt04aGateChk;
        self->mail = D_004F85D0;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(555, 0);

        stage_SetAnimation(269, 0, -1);
        stage_SetAnimation(272, 0, 0);
    }
}

extern JimakuArg jimaku_msg;
extern int jimakuOn;
/* kept local: this TU's uses of jimakuBegin do not fit the prototype in jimaku.h */
extern void jimakuBegin(int a0);
/* kept local: this TU's uses of jimakuJump do not fit the prototype in jimaku.h */
extern void jimakuJump(int a0);

typedef struct AnimList28 {
    int v[28];
} AnimList28;

extern AnimList28 D_00622878;
extern long long D_006228F0[];
extern long long D_00622900[];
extern char D_00618D80[];
extern char D_00622840[];
extern int D_0063BE98;

/* .sbss, owned by st04a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by
   the subthread the wait loops below spin for, and a running flag set for the
   length of the conte09_3 cutscene that nothing in the ROM reads back. */
static int demoEnd;

static int conte09_3Running;

extern int D_0063AA08;
extern int D_0028F8F4[];
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(char *a0);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(char *a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(void *o, int mot);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(void *a0, void *dir);
/* kept local: this TU's uses of scpDispOffAllWithKind do not fit the prototype in script.h */
extern void scpDispOffAllWithKind(int a0);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, void *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *handle, int mask);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float t);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of jimakuUndisp do not fit the prototype in jimaku.h */
extern void jimakuUndisp(JimakuArg *a0);

void actSt04aGateChk(volatile int a0)
{
    int *th0;
    int *th1;
    int *th2;
    int i;
    int n;

    stgmgrNextStagePreLoadForceStageSet(0);

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, D_00639EA4, 3000.0f) == 0) {
        _ACTWait(1);
    }

    th0 = (int *)actCreateSubThread(actSt04aEnvSe, 21);

    lt_switch_layout(55);

    D_0063AA08 = 1;

    scpPlayStart(D_00639EA4);

    scpDispOffAllWithKind(0x13);

    scpPlayMot(D_00639EA4, 0);

    StandbyStreamMotion(D_00618D80);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        debug_StdPrintfDummy(D_00622840, ++i);
        _ACTWait(1);
    }

    DisableStreamMotionManagerAutomaticDelete();

    scpPlayStart(D_00639EA8);

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(23, &D_0063BE98, 1, 1, 0);
    while (D_0063BE98 == 0) {
        _ACTWait(1);
    }

    gflagOn(137);

    _ACTWait(1);

    th1 = (int *)actCreateSubThread(actSt04aConte06, 21);
    th2 = (int *)actCreateSubThread(actSt04aConte06Jimaku, 21);

    stage_SetAnimation(269, 1, 0);

    scpSearchGobj(590)->f16C = 1;

    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion(D_00639EA8);
    EntryStreamMotion((char *)scpSearchGobj(590));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    _ACTWait((int)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 2.5));

    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BE98, 0xC0);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();

    iosPadActStopAll();

    iosThreadSetPri(th1 + 9, 34);
    iosThreadSetPri(th2 + 9, 34);
    iosThreadSetPri(th0 + 9, 34);

    if (n != 0) {
        {
            AnimList28 anim;
            unsigned int j;

            anim = D_00622878;
            for (j = 0; j < 28; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

        stage_SetAnimation(269, 0, -1);
        stage_SetAnimation(673, 1, -1);
        stage_SetAnimation(475, -1, -2);
        stage_SetAnimation(477, -1, -2);

        scpSearchGobj(590)->f16C = 0;

        stage_SetLoopFlag(555, 0);
        stage_SetAnimation(555, -1, -2);

        reg_SetScissorSw(0);

        {
            long long p1[2];
            long long p2[2];

            p1[0] = D_006228F0[0];
            p1[1] = D_006228F0[1];
            SetDirectRootPosition(D_00639EA4, p1);

            p2[0] = D_00622900[0];
            p2[1] = D_00622900[1];
            SetDirectRootPosition(D_00639EA8, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        float dir[4];

        D_0063AA0C = 1.0f;

        scpPlayMot(D_00639EA4, 0);
        scpPlayMot(D_00639EA8, 532);

        *(int *)(*(int *)(D_00639EA4 + 0x15C) + 0x514) =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);
        *(int *)(*(int *)(D_00639EA8 + 0x15C) + 0x514) =
            (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);

        sceVu0SubVector(dir, test_CURRENTROOT((int)D_00639EA8), test_CURRENTROOT((int)D_00639EA4));
        scpPlayMotDir(D_00639EA4, dir);

        sceVu0SubVector(dir, test_CURRENTROOT((int)D_00639EA4), test_CURRENTROOT((int)D_00639EA8));
        scpPlayMotDir(D_00639EA8, dir);
    }

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    _ACTWait(1);

    iosOmSendMail(D_00639EA8, 0x3F, D_00639EA4);

    D_0063AA08 = 0;

    lt_switch_layout(54);

    SetStaticBlur(1);

    gflagOn(155);

    stgmgrNextStagePreLoadDistBoyMode();
}

/* kept local: this TU's uses of scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
extern int D_00639EAC;
extern int D_0063BEBC;
extern unsigned char D_0063BEC0;
extern char D_0063BEA0[];
extern char D_00622910[];
extern char D_00622920[];

void actSt04aConte06(volatile int a0)
{
    stage_SetAnimation(648, 1, 0);

    AdpcmPlay(*(int *)(D_0063BE98 + 0x2C));

    while (stage_ContinueAnimation(648, 649) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(649, 650) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(650, 651) == 0) {
        _ACTWait(1);
    }

    _ACTWait(240);

    D_0063BEBC = iosPadActRequest(D_00639EAC, 9);
    D_0063BEC0 = 0x40;
    iosPadActVolumeSet(D_0063BEBC, 0x40);

    while (stage_ContinueAnimation(651, 652) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(652, 653) == 0) {
        _ACTWait(1);
    }

    reg_SetScissorSw(0);

    while (stage_ContinueAnimation(653, 654) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(654, 655) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(655, 656) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(475, 1, 0);

    iosPadActRequest(D_00639EAC, 0xF);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(0x30, 0, 0x22B, 0);

    stage_SetLoopFlag(555, 1);
    stage_SetAnimation(555, 1, 0);

    debug_StdPrintfDummy(D_0063BEA0);

    stage_SetAnimation(489, 1, 0);

    tex_SetUVScroll(D_00622910, 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll(D_00622920, 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(656, 657) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(657, 658) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(D_0063BEBC);

    while (stage_CheckAnimationFrame(658, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll(D_00622910, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(D_00622920, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(658, 659) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(659, 660) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(660, 661) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(661, 662) == 0) {
        _ACTWait(1);
    }
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

    _ACTWait(120);

    stage_SetAnimation(477, 1, 0);

    iosPadActRequest(D_00639EAC, 0xF);

    while (stage_ContinueAnimation(668, 669) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(590)->f16C = 0;

    stage_SetLoopFlag(555, 0);
    stage_SetAnimation(555, -1, -2);

    while (stage_ContinueAnimation(669, 670) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(670, 671) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(671, 672) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(672, 673) == 0) {
        _ACTWait(1);
    }

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFinish(673) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actSt04aConte06Jimaku(volatile int a0)
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
        case 0xFA:
            jimaku_msg.sub.unk2C = 0x19;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x564:
            jimaku_msg.sub.unk2C = 0x1A;
            jimaku_msg.sub.unk38 = 0x3C;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x94C:
            jimaku_msg.sub.unk2C = 0x1F;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xB2D:
            jimaku_msg.sub.unk2C = 0x22;
            jimaku_msg.sub.unk38 = 0x96;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xC58:
            jimaku_msg.sub.unk2C = 0x23;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xD84:
            jimaku_msg.sub.unk2C = 0x24;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0xEB0:
            jimaku_msg.sub.unk2C = 0x25;
            jimaku_msg.sub.unk38 = 0xAE;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x1054:
            jimaku_msg.sub.unk2C = 0x26;
            jimaku_msg.sub.unk38 = 0xAE;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x12C0:
            jimaku_msg.sub.unk2C = 0x2B;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x15CC:
            jimaku_msg.sub.unk2C = 0x1B;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x17A2:
            jimaku_msg.sub.unk2C = 0x1D;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x1A54:
            jimaku_msg.sub.unk2C = 0x30;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x1B44:
            jimaku_msg.sub.unk2C = 0x31;
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
    } while (t < 7300.0f);
    _ACTWait(0);
}

extern ActMail D_004F85F0[];

void actSt04aGateOpen(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(140) == 0) {
        stage_SetAnimation(270, 0, 0);

        scpSearchGobj(669)->f16C = 0;

        D_004F85F0[0].func = actSt04aGateOpenChk;
        self->mail = D_004F85F0;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

        stage_SetAnimation(270, 0, -1);
        stage_SetAnimation(272, 0, -1);
        stage_SetAnimation(275, 0, -1);

        scpSearchGobj(669)->f16C = 0;

        SetGirlHairDispSwitch(D_00639EA8, 1);
    }
}

typedef struct AnimList {
    int v[13];
} AnimList;

extern AnimList D_00622938;
extern long long D_00622970[];
extern long long D_00622980[];
extern long long D_00622990[];
extern char D_00618DB0[];
extern int D_0063BEA4;
/* kept local: this TU's uses of scpSleepEnemyAll do not fit the prototype in script.h */
extern void scpSleepEnemyAll(void);
/* kept local: this TU's uses of scpKillEnemyAll do not fit the prototype in script.h */
extern void scpKillEnemyAll(void);
/* kept local: this TU's uses of scpDispOnAllWithKind do not fit the prototype in script.h */
extern void scpDispOnAllWithKind(int a0);
/* kept local: this TU's uses of scpDisActivateAllWithKind do not fit the prototype in script.h */
extern void scpDisActivateAllWithKind(int a0);

void actSt04aGateOpenChk(volatile int a0)
{
    int *th1;
    int *th2;
    int *th3;
    int i;
    int n;

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((((PObjGObjSt04A *)D_00639EA8)->act->unk34 != 0x6F &&
             scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 &&
             scpTriggerBall(a0, D_00639EA8, 200.0f) != 0 && gflagChk(174) != 0 &&
             gflagChk(243) != 0) ||
            (((PObjGObjSt04A *)D_00639EA8)->act->unk34 != 0x6F &&
             scpTriggerBall(a0, D_00639EA4, 200.0f) != 0 &&
             scpTriggerBall(a0, D_00639EA8, 200.0f) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;

    scpPlayStart(D_00639EA8);

    scpSleepEnemyAll();

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpPlayMot(D_00639EA8, 532);

    StandbyStreamMotion(D_00618DB0);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_00622840, i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(31, &D_0063BEA4, 1, 1, 1);
    while (D_0063BEA4 == 0) {
        _ACTWait(1);
    }

    scpDisActivateAllWithKind(0x13);

    th1 = (int *)actCreateSubThread(actConte09, 21);
    th2 = (int *)actCreateSubThread(actSt04aEnvSeWakare1, 21);
    th3 = (int *)actCreateSubThread(actConte09Jimaku, 21);

    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BEA4, 0xC0);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();

    iosPadActStopAll();

    iosThreadSetPri(th1 + 9, 34);
    iosThreadSetPri(th3 + 9, 34);
    iosThreadSetPri(th2 + 9, 34);

    if (n != 0) {
        {
            AnimList anim;
            unsigned int j;

            anim = D_00622938;
            for (j = 0; j < 13; j++) {
                stage_SetAnimation(anim.v[j], 1, -1);
                _ACTWait(1);
            }
        }

        jimakuUndisp(&jimaku_msg);

        stage_SetAnimation(724, 1, -1);
        stage_SetAnimation(275, 0, -1);
        stage_SetAnimation(272, 0, -1);
        stage_SetAnimation(280, 0, -1);
        stage_SetAnimation(270, 0, -1);

        scpKillEnemyAll();

        scpDispOnAllWithKind(0x13);

        gflagOn(140);

        SetGirlHairDispSwitch(D_00639EA8, 1);

        {
            long long p1[2];
            long long p2[2];

            p1[0] = D_00622970[0];
            p1[1] = D_00622970[1];
            SetDirectRootPosition(D_00639EA4, p1);

            p2[0] = D_00622980[0];
            p2[1] = D_00622980[1];
            SetDirectRootPosition(D_00639EA8, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        long long ofs[2];
        float dir[4];

        D_0063AA0C = 1.0f;

        scpPlayStart(D_00639EA4);

        scpPlayMot(D_00639EA4, 0);

        ofs[0] = D_00622990[0];
        ofs[1] = D_00622990[1];
        sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)D_00639EA8));
        scpPlayMotDir(D_00639EA8, dir);
    }

    _ACTWait(1);

    scpPlayEnd(D_00639EA4);
    scpPlayEnd(D_00639EA8);

    D_0063AA08 = 0;

    lt_switch_layout(54);

    SetWayGroupActive(2, 1);

    scpSearchGobj(648)->f16C = 0;
}

extern int D_0063BEC4;
extern unsigned char D_0063BEC8;

void actConte09(volatile int a0)
{
    int th1;
    int th2;

    th1 = EntryStreamMotion(D_00639EA4);
    th2 = EntryStreamMotion(D_00639EA8);

    SetStreamMotionFinishCallBackFunc(th1, finishCallBackFunc);
    SetStreamMotionFinishCallBackFunc(th2, finishCallBackFunc);

    PlayStreamMotion();

    scpPlayMot(D_00639EA4, 0);

    scpSearchGobj(648)->f16C = 1;

    stage_SetAnimation(712, 1, 0);

    while (stage_ContinueAnimation(712, 713) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(713, 714) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(280, 1, 0);

    while (stage_CheckAnimationFrame(714, 125, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0xF);

    scpKillEnemyAll();

    while (stage_ContinueAnimation(714, 715) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(715, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_ContinueAnimation(715, 716) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(270, 1, 0);

    while (stage_ContinueAnimation(716, 717) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(717, 718) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(718, 70, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    SetGirlHairDispSwitch(D_00639EA8, 1);

    while (stage_ContinueAnimation(718, 719) == 0) {
        _ACTWait(1);
    }

    _ACTWait(300);

    stage_SetAnimation(275, 1, 0);

    _ACTWait(120);

    D_0063BEC4 = iosPadActRequest(D_00639EAC, 0xA);
    D_0063BEC8 = 0x80;
    iosPadActVolumeSet(D_0063BEC4, 0x80);

    while (stage_ContinueAnimation(719, 720) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(272, 1, 0);

    while (stage_ContinueAnimation(720, 721) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(D_0063BEC4);

    while (stage_ContinueAnimation(721, 722) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(722, 723) == 0) {
        _ACTWait(1);
    }

    scpDispOnAllWithKind(0x13);

    gflagOn(140);

    while (stage_ContinueAnimation(723, 724) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFinish(724) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    *(int *)(*(int *)(D_00639EA4 + 0x15C) + 0x514) =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);
    *(int *)(*(int *)(D_00639EA8 + 0x15C) + 0x514) =
        (int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f * 0.0f);

    demoEnd = 1;

    _ACTWait(0);
}

void actConte09Jimaku(volatile int a0)
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
        case 0x871:
            jimaku_msg.sub.unk2C = 0x58;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 0x97E:
            jimaku_msg.sub.unk2C = 0x56;
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
    } while (t < 2700.0f);
    _ACTWait(0);
}

extern int D_0063BEA8;
/* kept local: this TU's uses of scpPlayMotReq do not fit the prototype in script.h */
extern void scpPlayMotReq(void *a0, int mot);
/* st04a.o's own .rodata: the gate-open exit direction vector. */
extern long long D_006229A0[];

void actSt04aGateOpen2Chk(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(D_00639EA8, 0x1000000) == 0 || ACTGame_FLAG_TETSUNAGI() == 0) {
        _ACTWait(1);
    }

    ((PObjGObjSt04A *)D_00639EA8)->act->flags20.ll &= ~0x10000;
    scpPlayMotReq(D_00639EA8, 0x13B);

    scpPlayMot(D_00639EA4, 0);

    ofs[0] = D_006229A0[0];
    ofs[1] = D_006229A0[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    lt_switch_layout(55);

    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    scpDisActivateAllWithKind(0x13);

    while (D_0063BEA8 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(D_0063BEA8 + 0x2C));

    actCreateSubThread(actConte09_2, 21);
}

/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(char *a0, float x, float y, float z);
extern char D_00618E10[];
/* st04a.o's own .rodata: the two demo exit direction vectors. */
extern int D_0063BEAC;
extern int D_0063BECC;
extern unsigned char D_0063BED0;

void actConte09_2(volatile int a0)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion(D_00639EA8);

    PlayStreamMotion();

    stage_SetAnimation(728, 1, 0);
    stage_SetAnimation(281, 1, 0);

    while (stage_ContinueAnimation(728, 729) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(729, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0xF);

    while (stage_ContinueAnimation(729, 730) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(730, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(D_00639EAC, 0x10);

    while (stage_ContinueAnimation(730, 731) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(731, 732) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(732, 733) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(733, 734) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(734, 735) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(735, 736) == 0) {
        _ACTWait(1);
    }

    D_0063BECC = iosPadActRequest(D_00639EAC, 0xA);
    D_0063BED0 = 0x80;
    iosPadActVolumeSet(D_0063BECC, 0x80);

    stage_SetAnimation(273, 1, 0);

    while (stage_ContinueAnimation(736, 737) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(737, 738) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(738, 739) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(739, 740) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(740, 741) == 0) {
        _ACTWait(1);
    }

    ClearStreamMotionEntry(D_00639EA8);

    scpPlayMotReq(D_00639EA8, 0x13B);

    scpPlayPosSet(D_00639EA8, 14.8948f, 210.136f, 4858.48f);

    ofs[0] = D_00622990[0];
    ofs[1] = D_00622990[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)D_00639EA8));
    scpPlayMotDir(D_00639EA8, dir);

    lt_switch_layout(54);

    while (stage_CheckAnimationFinish(741) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(D_0063BECC);

    ofs[0] = D_006229A0[0];
    ofs[1] = D_006229A0[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    StandbyStreamMotion(D_00618E10);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_00622840, i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(33, &D_0063BEAC, 1, 1, 0);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;

    gflagOn(141);
}

extern ActMail D_004F8690[];

void actSt04aGateOpen3(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(142) == 0) {
        stage_SetLoopFlag(555, 0);

        while (stage_CheckAnimationFrame(555, 1, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);

        D_004F8690[0].func = actSt04aGateOpen3Chk;
        self->mail = D_004F8690;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(555, 0);

        while (stage_CheckAnimationFrame(555, 1, 1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
    }
}

void actSt04aGateOpen3Chk(volatile int a0)
{
    if (D_00639EA8 == 0) {
        _ACTWait(0);
    }

    while (gflagChk(141) == 0 || scpTriggerBall(a0, D_00639EA4, 450.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(142);

    lt_switch_layout(55);

    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayStart(D_00639EA8);

    if (D_0063BEA8 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BEA8, 0x50);
    }

    while (D_0063BEAC == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(D_0063BEAC + 0x2C));

    actCreateSubThread(actSt04aEnvSeWakare2, 21);
    actCreateSubThread(actConte09_3, 21);
    actCreateSubThread(actConte09_3Jimaku, 21);
}

/* kept local: this TU's uses of scpSetStreamMotionRootOffset do not fit the prototype in script.h */
extern void scpSetStreamMotionRootOffset(char *o, float x, float y, float z);
/* kept local: this TU's uses of scpTorchLightOff do not fit the prototype in script.h */
extern void scpTorchLightOff(int a0);
/* kept local: this TU's uses of scpGameStat_BoyWeaponkind do not fit the prototype in script.h */
extern int scpGameStat_BoyWeaponkind(void);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern int RequestStageChange(int a0, char *a1, int a2, float a3, float a4);

void actConte09_3(volatile int a0)
{
    conte09_3Running = 1;

    actCreateSubThread(actConte09_3_demoCancel, 21);

    scpSearchGobj(669)->f16C = 1;

    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion(D_00639EA8);
    EntryStreamMotion((char *)scpSearchGobj(669));

    PlayStreamMotion();

    scpSetStreamMotionRootOffset(D_00639EA4, 0.0f, 0.0f, 1.0f);
    scpSetStreamMotionRootOffset(D_00639EA8, 0.0f, 0.0f, 1.0f);

    scpTorchLightOff(571);
    scpTorchLightOff(572);
    scpTorchLightOff(573);
    scpTorchLightOff(574);
    scpTorchLightOff(575);
    scpTorchLightOff(576);
    scpTorchLightOff(577);
    scpTorchLightOff(578);
    scpTorchLightOff(579);
    scpTorchLightOff(580);

    stage_SetAnimation(280, -1, -2);
    stage_SetAnimation(281, -1, -2);
    stage_SetAnimation(712, -1, -2);
    stage_SetAnimation(713, -1, -2);
    stage_SetAnimation(714, -1, -2);
    stage_SetAnimation(715, -1, -2);
    stage_SetAnimation(716, -1, -2);
    stage_SetAnimation(717, -1, -2);
    stage_SetAnimation(718, -1, -2);
    stage_SetAnimation(719, -1, -2);
    stage_SetAnimation(720, -1, -2);
    stage_SetAnimation(721, -1, -2);
    stage_SetAnimation(722, -1, -2);
    stage_SetAnimation(723, -1, -2);
    stage_SetAnimation(724, -1, -2);
    stage_SetAnimation(728, -1, -2);
    stage_SetAnimation(729, -1, -2);
    stage_SetAnimation(730, -1, -2);
    stage_SetAnimation(731, -1, -2);
    stage_SetAnimation(732, -1, -2);
    stage_SetAnimation(733, -1, -2);
    stage_SetAnimation(734, -1, -2);
    stage_SetAnimation(735, -1, -2);
    stage_SetAnimation(736, -1, -2);
    stage_SetAnimation(737, -1, -2);
    stage_SetAnimation(738, -1, -2);
    stage_SetAnimation(739, -1, -2);
    stage_SetAnimation(740, -1, -2);
    stage_SetAnimation(741, -1, -2);

    stage_SetAnimation(742, 1, 0);

    _ACTWait(1);

    stage_SetAnimation(273, 1, 0x1F6);

    while (stage_ContinueAnimation(742, 743) == 0) {
        _ACTWait(1);
    }

    if (scpGameStat_BoyWeaponkind() == 1) {
        stage_SetAnimation(276, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 4 || scpGameStat_BoyWeaponkind() == 5) {
        stage_SetAnimation(277, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 6) {
        stage_SetAnimation(278, 1, 0);
    }
    if (scpGameStat_BoyWeaponkind() == 9) {
        stage_SetAnimation(279, 1, 0);
    }

    DeleteBoyWeapon();

    while (stage_ContinueAnimation(743, 744) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(744, 745) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(276, -1, -2);
    stage_SetAnimation(277, -1, -2);
    stage_SetAnimation(278, -1, -2);
    stage_SetAnimation(279, -1, -2);

    while (stage_ContinueAnimation(745, 746) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(746, 747) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(747, 748) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(273, 1, 0x371);

    while (stage_ContinueAnimation(748, 749) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(749, 750) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(725, 1, 0);

    while (stage_ContinueAnimation(750, 751) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(273, 1, 0x4D9);

    shadow_SetLength((int)((PObjGObjSt04A *)D_00639EA8)->f15C, 20.0f);

    while (stage_ContinueAnimation(751, 752) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(273, 1, 0x835);
    stage_SetAnimation(725, -1, -2);
    stage_SetAnimation(726, 1, 0);

    while (stage_ContinueAnimation(752, 753) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(273, 1, 0x8AD);

    shadow_DispCancel(71, 1);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(0x30, 0, 0x22B, 0);

    stage_SetLoopFlag(555, 1);
    stage_SetAnimation(555, 1, 0);

    tex_SetUVScroll(D_00622910, 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll(D_00622920, 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    _ACTWait(1);

    scpSearchGobj(649)->f16C = 0;

    SetStaticBlur(0);

    while (stage_CheckAnimationFrame(753, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll(D_00622910, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(D_00622920, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    while (stage_ContinueAnimation(753, 754) == 0) {
        _ACTWait(1);
    }

    _ACTWait(1);

    scpSearchGobj(649)->f16C = 1;

    while (stage_CheckAnimationFrame(754, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    while (stage_ContinueAnimation(754, 755) == 0) {
        _ACTWait(1);
    }

    shadow_SetLength((int)((PObjGObjSt04A *)D_00639EA8)->f15C, 0.0f);

    while (stage_ContinueAnimation(755, 756) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(726, -1, -2);
    stage_SetAnimation(727, 1, 0);

    SetGirlClothDispSwitch(D_00639EA8, 1, 0);
    SetGirlClothDispSwitch(D_00639EA8, 0, 0);
    SetGirlClothDispSwitch(D_00639EA8, 2, 0);

    _ACTWait(1);

    scpSearchGobj(54)->f16C = 0;
    scpSearchGobj(649)->f16C = 0;

    shadow_DispCancel(0, 1);
    shadow_DispCancel(4, 1);

    while (stage_ContinueAnimation(756, 757) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(727, -1, -2);

    conte09_3Running = 0;

    _ACTWait(1);

    scpSearchGobj(54)->f16C = 1;
    scpSearchGobj(649)->f16C = 1;

    gflagOn(144);
    gflagOn(390);

    stage_SetLoopFlag(555, 0);

    shadow_DispCancel(71, 0);
    shadow_DispCancel(0, 0);
    shadow_DispCancel(4, 0);

    SetStaticBlur(1);

    while (stage_CheckAnimationFrame(757, 90, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpFadeOut(3.0f, 0, 0, 0);

    while (scpFadeChk() != 0) {
        _ACTWait(45);
    }

    RequestStageChange(3, D_00639EA4, 0, 16.0f, 16.0f);
}

extern PadState D_0028F8F0[];
/* kept local: this TU's uses of preload do not fit the prototype in script.h */
extern void preload(int idx);
extern int D_0063BEB0;

void actSt04aGateLChk(volatile int a0)
{
    int *th;

    while (gflagChk(174) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;
    gflagOn(138);

    scpAdpcmPlayRequestFunc(29, &D_0063BEB0, 1, 1, 1);
    while (D_0063BEB0 == 0) {
        _ACTWait(1);
    }

    preload(4);

    scpFadeIn(16.0f);

    th = (int *)actCreateSubThread(actSt04aGateLSub, 21);

    demoEnd = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 9, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&D_0063BEB0, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(293, 0, -1);

        scpFadeIn(3.0f);
    }

    RequestStageChange(4, D_00639EA4, 0, 1.0f, 8.0f);
}

extern int D_0063BEB4;

void actSt04aGateRChk(volatile int a0)
{
    int *th;
    int stage;

    while (gflagChk(234) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    D_0063AA08 = 1;
    gflagOn(139);

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(30, &D_0063BEB4, 1, 1, 1);
    while (D_0063BEB4 == 0) {
        _ACTWait(1);
    }

    if (gflagChk(246) != 0) {
        stage = 5;
    } else if (gflagChk(247) != 0) {
        stage = 6;
    } else if (gflagChk(248) != 0) {
        stage = 9;
    } else if (gflagChk(249) != 0) {
        stage = 7;
    } else if (gflagChk(233) != 0) {
        stage = 8;
    } else {
        stage = 0;
    }

    preload(stage);

    scpFadeIn(16.0f);

    th = (int *)actCreateSubThread(actSt04aGateRSub, 21);

    demoEnd = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 9, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&D_0063BEB4, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(295, 0, -1);

        scpFadeIn(3.0f);
    }

    RequestStageChange(stage, D_00639EA4, 0, 1.0f, 8.0f);
}

/* kept local: this TU's uses of scpTorchLightOn do not fit the prototype in script.h */
extern void scpTorchLightOn(int a0);
extern ActMail D_004F86F0[];

void actSt04aTorch1(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        SleepHint(6);
        SleepHint(4);

        if (gflagChk(145) != 0) {
            scpSearchGobj(563)->f16C = 0;
            stage_SetAnimation(283, 0, -1);
        }

        if (gflagChk(146) != 0) {
            scpSearchGobj(564)->f16C = 0;
            stage_SetAnimation(284, 0, -1);
        }

        if (gflagChk(147) != 0) {
            scpSearchGobj(565)->f16C = 0;
            stage_SetAnimation(285, 0, -1);
        }

        if (gflagChk(148) != 0) {
            scpSearchGobj(566)->f16C = 0;
            stage_SetAnimation(286, 0, -1);
        }

        if (gflagChk(149) != 0) {
            scpSearchGobj(567)->f16C = 0;
            stage_SetAnimation(287, 0, -1);
        }

        if (gflagChk(150) != 0) {
            scpSearchGobj(568)->f16C = 0;
            stage_SetAnimation(288, 0, -1);
        }

        if (gflagChk(151) != 0) {
            scpSearchGobj(569)->f16C = 0;
            stage_SetAnimation(289, 0, -1);
        }

        if (gflagChk(152) != 0) {
            scpSearchGobj(570)->f16C = 0;
            stage_SetAnimation(290, 0, -1);
        }

        D_004F86F0[0].func = actSt04aTorch1Chk;
        self->mail = D_004F86F0;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        scpSearchGobj(563)->f16C = 0;
        scpSearchGobj(564)->f16C = 0;
        scpSearchGobj(565)->f16C = 0;
        scpSearchGobj(566)->f16C = 0;
        scpSearchGobj(567)->f16C = 0;
        scpSearchGobj(568)->f16C = 0;
        scpSearchGobj(569)->f16C = 0;
        scpSearchGobj(570)->f16C = 0;

        stage_SetAnimation(283, 0, -1);
        stage_SetAnimation(284, 0, -1);
        stage_SetAnimation(285, 0, -1);
        stage_SetAnimation(286, 0, -1);
        stage_SetAnimation(287, 0, -1);
        stage_SetAnimation(288, 0, -1);
        stage_SetAnimation(289, 0, -1);
        stage_SetAnimation(290, 0, -1);

        scpTorchLightOn(571);
        scpTorchLightOn(572);
        scpTorchLightOn(573);
        scpTorchLightOn(574);
        scpTorchLightOn(575);
        scpTorchLightOn(576);
        scpTorchLightOn(577);
        scpTorchLightOn(578);
        scpTorchLightOn(579);
        scpTorchLightOn(580);
    }
}

void actSt04aTorch1Chk(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    switch (*(int *)(a0 + 8)) {
    case 0x22B:
        self->unk478 = 0x91;
        self->unk474 = scpSearchGobj(563);
        self->unk470 = 0x11B;
        actCreateSubThread(actSt04aTorchAllFlagfChk, 21);
        break;
    case 0x22C:
        self->unk478 = 0x92;
        self->unk474 = scpSearchGobj(564);
        self->unk470 = 0x11C;
        break;
    case 0x22D:
        self->unk478 = 0x93;
        self->unk474 = scpSearchGobj(565);
        self->unk470 = 0x11D;
        break;
    case 0x22E:
        self->unk478 = 0x94;
        self->unk474 = scpSearchGobj(566);
        self->unk470 = 0x11E;
        break;
    case 0x22F:
        self->unk478 = 0x95;
        self->unk474 = scpSearchGobj(567);
        self->unk470 = 0x11F;
        break;
    case 0x230:
        self->unk478 = 0x96;
        self->unk474 = scpSearchGobj(568);
        self->unk470 = 0x120;
        break;
    case 0x231:
        self->unk478 = 0x97;
        self->unk474 = scpSearchGobj(569);
        self->unk470 = 0x121;
        break;
    case 0x232:
        self->unk478 = 0x98;
        self->unk474 = scpSearchGobj(570);
        self->unk470 = 0x122;
        break;
    }

    while (1) {
        if (scpTriggerBall(a0, self->unk474, 5.0f) != 0) {
            D_0063AA08 = 1;

            ((PObjGObjSt04A *)self->unk474)->f16C = 0;

            stage_SetAnimation(self->unk470, 1, 0);

            while (stage_CheckAnimationFrame(self->unk470, 2, 0) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            soundSeDefPlay(1363, 0, 0, 1);

            while (stage_CheckAnimationFinish(self->unk470) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);

            gflagOn(self->unk478);

            D_0063AA08 = 0;
            break;
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/script/src/st04a", actSt04aTorchAllFlagfChk);

extern int D_002A5580[];

void actSt04aTorchHintChk(volatile int a0)
{
    while (gflagChk(155) == 0) {
        _ACTWait(1);
    }

    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(563), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(564), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(565), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(566), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(567), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(568), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(569), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(570), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(591), 1.0f, 0.001f, 1.0f);

    if (gflagChk(156) == 0) {
        _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0x14);
    }

    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(563), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(564), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(565), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(566), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(567), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(568), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(569), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(570), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(D_002A5580, scpSearchGobj(591), 2.0f, 0.01f, 1.0f);

    gflagOn(156);
}

extern ActMail D_004F86B0[];

void actSt04aGateL(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(138) == 0) {
        gflagOn(389);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(295, 0, 0);

        D_004F86B0[0].func = actSt04aGateLChk;
        self->mail = D_004F86B0;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern ActMail D_004F86D0[];

void actSt04aGateR(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        gflagOn(389);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(293, 0, -1);

        D_004F86D0[0].func = actSt04aGateRChk;
        self->mail = D_004F86D0;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04aTorchXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    stage_SetAnimation(291, 0, 0);
}

void actSt04aDeadCam(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    while (gflagChk(141) == 0 || scpTriggerBall(a0, D_00639EA4, 600.0f) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFrame(273, 1400, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    stage_SetAnimation(274, 1, 0);

    while (stage_CheckAnimationFinish(274) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

extern ActMail D_004F8670[];

void actSt04aGateOpen2(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(141) == 0) {
        scpSearchGobj(669)->f16C = 0;

        D_004F8670[0].func = actSt04aGateOpen2Chk;
        self->mail = D_004F8670;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern ActMail D_004F8650[];

void actSt04aGateOpen2Ready(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    D_004F8650[0].func = actSt04aGateOpen2ReadyChk;
    self->mail = D_004F8650;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern ActMail D_004F8710[];

void actSt04aGirlSit(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    D_004F8710[0].func = actSt04aGirlSitChk;
    self->mail = D_004F8710;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

extern ActMail D_004F8730[];

void actSt04aTorchHint(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        D_004F8730[0].func = actSt04aTorchHintChk;
        self->mail = D_004F8730;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

extern ActMail D_004F8750[];

void actSt04aModel(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    scpSearchGobj(648)->f16C = 0;

    D_004F8750[0].func = actSt04aModelOnChk;
    self->mail = D_004F8750;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04aEnvSe(volatile int a0)
{
    float f = 0.0f;

    D_0063AA0C = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 5401) {
            D_0063AA0C += 1.0f / 1800.0f;
            if (D_0063AA0C > 1.0f) {
                D_0063AA0C = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actSt04aEnvSeWakare1(volatile int a0)
{
    float f = 0.0f;

    D_0063AA0C = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2201) {
            D_0063AA0C += 1.0f / 3800.0f;
            if (D_0063AA0C > 1.0f) {
                D_0063AA0C = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

typedef struct {
    float m[4];
} Vec4St04A;

/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(int dst, int m, int src);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(int dst, int src);
extern Mtx44 D_004F8610;

void finishCallBackFunc(int a0)
{
    Vec4St04A v;
    int i;

    _ApplyMatrix((int)&v, *(int *)(*(int *)(a0 + 0x15C) + 0xC), (int)YUnitVector);
    v.m[1] = 0.0f;
    _NormalizeVector(*(int *)(a0 + 0x15C) + 0x520, (int)&v);

    for (i = 0; i < *(int *)(*(int *)(a0 + 0x15C) + 0x88); i++) {
        *(Mtx44 *)(*(int *)(*(int *)(a0 + 0x15C) + 0x80C) + i * 64) = D_004F8610;
    }
}

extern char D_00618DE0[];

void actSt04aGateOpen2ReadyChk(volatile int a0)
{
    int x = a0;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    while (D_00639EA8 == 0 || scpTriggerFloorAttr(D_00639EA8, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(D_00618DE0);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(D_00622840, i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(32, &D_0063BEA8, 1, 0, 0);
}

void actSt04aEnvSeWakare2(volatile int a0)
{
    float f = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2351) {
            D_0063AA0C -= 1.0f / 720.0f;
            if (D_0063AA0C < 0.0f) {
                D_0063AA0C = 0.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actConte09_3Jimaku(volatile int a0)
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
        case 2470:
            jimaku_msg.sub.unk2C = 91;
            jimaku_msg.sub.unk38 = 300;
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
    } while (t < 3000.0f);
}

void actConte09_3_demoCancel(volatile int a0)
{
    while (1) {
        _ACTWait(1);
    }
}

void actSt04aGateLSub(volatile int a0)
{
    stage_SetAnimation(293, 1, 0);
    while (stage_CheckAnimationFinish(293) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04aGateRSub(volatile int a0)
{
    stage_SetAnimation(295, 1, 0);
    while (stage_CheckAnimationFinish(295) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    demoEnd = 1;
    _ACTWait(0);
}

void actSt04aGirlSitChk(volatile int a0)
{
    int n;

    while (gflagChk(140) == 0) {
        _ACTWait(1);
    }
    ((ActStatus *)(*(char **)(D_00639EA8 + 0x164) + 0x20))->ll |= 0x10000;
    n = 0;
    for (;;) {
        if ((int)(*(unsigned long long *)(*(char **)(D_00639EA8 + 0x164) + 0x20) >> 20) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 3 < n) {
            iosOmSendMail(D_00639EA8, 0x6D, D_00639EA8);
            n = 0;
        }
        _ACTWait(1);
    }
}

/* The model-on watcher's mail record: it installs actSt04aModelOffChk here
   and posts it. Word 0 of each entry is the mail id the entry answers (430
   the actor post, 429 the trailing entry); .func is filled in at run time.
   Named for the thread that owns and posts it. */
static ActMail model_on[2] = {{430}, {429}};

void actSt04aModelOnChk(volatile int a0)
{
    ActSt04A *sub = ((PObjGObjSt04A *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) != 0) {
        _ACTWait(1);
    }

    scpSearchGobj(648)->f16C = 1;

    model_on[0].func = actSt04aModelOffChk;
    sub->mail = model_on;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

/* The model-off watcher's own mail record (installs actSt04aModelOnChk). */
static ActMail model_off[2] = {{430}, {429}};

void actSt04aModelOffChk(volatile int a0)
{
    ActSt04A *sub = ((PObjGObjSt04A *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(648)->f16C = 0;

    model_off[0].func = actSt04aModelOnChk;
    sub->mail = model_off;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
