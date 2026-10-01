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
#include "Matrix.h"
#include "script.h"
#include "jimaku.h"

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

/* kept local: char * here, GObj * in main.h */
extern char *boyGObj;
/* kept local: char * here, GObj * in main.h */
extern char *girlGObj;
/* kept local: agrees with main.h, which this TU does not include (boyGObj, girlGObj differ) */
extern int systemStatus[];

/* .data, owned by st04a.o, in the ROM's order ahead of model_on and model_off
   (MAIN.MAP sizes the member's run 0x160 in the January link): each action's
   mail pair, the check handler stored into its first entry at run time, and
   the matrix finishCallBackFunc writes into every joint. */
static ActMail gate_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open_mail[2] = {{430}, {429}}; /* derived name */

static Mtx44 jointMtxInit = {{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
                              1.0f, 0.0f, 0.0f, 0.0f, 1.0f}}; /* derived name */

static ActMail gate_open2_ready_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open2_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_open3_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_l_mail[2] = {{430}, {429}}; /* derived name */

static ActMail gate_r_mail[2] = {{430}, {429}}; /* derived name */

static ActMail torch1_mail[2] = {{430}, {429}}; /* derived name */

static ActMail girl_sit_mail[2] = {{430}, {429}}; /* derived name */

static ActMail torch_hint_mail[2] = {{430}, {429}}; /* derived name */

static ActMail model_mail[2] = {{430}, {429}}; /* derived name */

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

        gate_mail[0].func = actSt04aGateChk;
        self->mail = gate_mail;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetLoopFlag(555, 0);

        stage_SetAnimation(269, 0, -1);
        stage_SetAnimation(272, 0, 0);
    }
}

typedef struct AnimList28 {
    int v[28];
} AnimList28;

extern char streamMotion[];

/* .sdata, owned by st04a.o, the head of the run: the first gate's stream
   handle and gate1, which the retail code does not use (MAIN.MAP globals).
   actSt04aConte06's "!!\n" trace follows them. */
int gate1st = 0;

int gate1 = 0;

/* .sbss, owned by st04a.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by
   the subthread the wait loops below spin for, and a running flag set for the
   length of the conte09_3 cutscene that nothing in the ROM reads back. */
static int demoEnd;

static int conte09_3Running;

/* kept local: agrees with main.h, which this TU does not include (boyGObj, girlGObj differ) */
extern PadState pad[];

void actSt04aGateChk(volatile int a0)
{
    int *th0;
    int *th1;
    int *th2;
    int i;
    int n;

    stgmgrNextStagePreLoadForceStageSet(0);

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerBall(a0, boyGObj, 3000.0f) == 0) {
        _ACTWait(1);
    }

    th0 = (int *)actCreateSubThread(actSt04aEnvSe, 21);

    lt_switch_layout(55);

    scpBoyControlReadDisable = 1;

    scpPlayStart(boyGObj);

    scpDispOffAllWithKind(0x13);

    scpPlayMot(boyGObj, 0);

    StandbyStreamMotion(streamMotion);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", ++i);
        _ACTWait(1);
    }

    DisableStreamMotionManagerAutomaticDelete();

    scpPlayStart(girlGObj);

    reg_SetScissorSw(1);

    SetStaticBlur(0);

    scpAdpcmPlayRequestFunc(23, &gate1st, 1, 1, 0);
    while (gate1st == 0) {
        _ACTWait(1);
    }

    gflagOn(137);

    _ACTWait(1);

    th1 = (int *)actCreateSubThread(actSt04aConte06, 21);
    th2 = (int *)actCreateSubThread(actSt04aConte06Jimaku, 21);

    stage_SetAnimation(269, 1, 0);

    scpSearchGobj(590)->f16C = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion((char *)scpSearchGobj(590));

    PlayStreamMotion();

    scpFadeIn(6.0f);

    _ACTWait((int)((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 2.5));

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
        scpAdpcmFadeCloseFunc(&gate1st, 0xC0);

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
            /* the gate-open animations, in the order they start */
            static const AnimList28 gateOpenAnims = {{555, 489, 648, 649, 650, 651, 652, 653,
                                                      654, 655, 656, 657, 658, 659, 660, 661,
                                                      662, 663, 664, 665, 666, 667, 668, 669,
                                                      670, 671, 672, 673}}; /* derived name */
            AnimList28 anim;
            unsigned int j;

            anim = gateOpenAnims;
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
            /* the boy's and the girl's root positions after the gate opens */
            static const ConstVec boyRootPos __attribute__((aligned(16))) = {
                {1.635725f, -72.36407f, -1233.2648f, 0.0f}}; /* derived name */
            static const ConstVec girlRootPos __attribute__((aligned(16))) = {
                {7.660961f, -88.9936f, -1293.0424f, 0.0f}}; /* derived name */
            long long p1[2];
            long long p2[2];

            p1[0] = boyRootPos.d[0];
            p1[1] = boyRootPos.d[1];
            SetDirectRootPosition(boyGObj, p1);

            p2[0] = girlRootPos.d[0];
            p2[1] = girlRootPos.d[1];
            SetDirectRootPosition(girlGObj, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        float dir[4];

        scpSeEnvMasterVolRate = 1.0f;

        scpPlayMot(boyGObj, 0);
        scpPlayMot(girlGObj, 532);

        GOBJ_SUB(boyGObj)->f_514 =
            (int)((float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f * 0.0f);
        GOBJ_SUB(girlGObj)->f_514 =
            (int)((float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f * 0.0f);

        sceVu0SubVector(dir, test_CURRENTROOT((int)girlGObj), test_CURRENTROOT((int)boyGObj));
        scpPlayMotDir(boyGObj, dir);

        sceVu0SubVector(dir, test_CURRENTROOT((int)boyGObj), test_CURRENTROOT((int)girlGObj));
        scpPlayMotDir(girlGObj, dir);
    }

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    _ACTWait(1);

    iosOmSendMail(girlGObj, 0x3F, boyGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(54);

    SetStaticBlur(1);

    gflagOn(155);

    stgmgrNextStagePreLoadDistBoyMode();
}

/* kept local: agrees with main.h, which this TU does not include (boyGObj, girlGObj differ) */
extern int boyPad;

void actSt04aConte06(volatile int a0)
{
    stage_SetAnimation(648, 1, 0);

    AdpcmPlay(*(int *)(gate1st + 0x2C));

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

    gate_yure_low = iosPadActRequest(boyPad, 9);
    gate_yure_low_vol = 0x40;
    iosPadActVolumeSet(gate_yure_low, 0x40);

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

    iosPadActRequest(boyPad, 0xF);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(0x30, 0, 0x22B, 0);

    stage_SetLoopFlag(555, 1);
    stage_SetAnimation(555, 1, 0);

    debug_StdPrintfDummy("!!\n");

    stage_SetAnimation(489, 1, 0);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(656, 657) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(657, 658) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(gate_yure_low);

    while (stage_CheckAnimationFrame(658, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

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

    iosPadActRequest(boyPad, 0xF);

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

/* .sdata, the rest of st04a.o's run after actSt04aConte06's trace: the gate
   and torch stream handles (the first three are the retail object's own, the
   next three MAIN.MAP's globals), then the pad shakes and their volumes
   (MAIN.MAP globals, declared in st04a.h for actSt04aConte06). */
static int gate_open = 0; /* derived name */

static int gate_open2 = 0; /* derived name */

static int conte09_2 = 0; /* derived name */

int gate_ready_l = 0;

int gate_ready_r = 0;

int torch = 0;

int gate_yure_low = 0;

unsigned char gate_yure_low_vol = 0;

int yure1 = 0;

unsigned char vol1 = 0;

int yure2 = 0;

unsigned char vol2 = 0;

void actSt04aConte06Jimaku(volatile int a0)
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
        case 0xFA:
            jimaku_msg.sub.unk2C = 0x19;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x564:
            jimaku_msg.sub.unk2C = 0x1A;
            jimaku_msg.sub.unk38 = 0x3C;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x94C:
            jimaku_msg.sub.unk2C = 0x1F;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0xB2D:
            jimaku_msg.sub.unk2C = 0x22;
            jimaku_msg.sub.unk38 = 0x96;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0xC58:
            jimaku_msg.sub.unk2C = 0x23;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0xD84:
            jimaku_msg.sub.unk2C = 0x24;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0xEB0:
            jimaku_msg.sub.unk2C = 0x25;
            jimaku_msg.sub.unk38 = 0xAE;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x1054:
            jimaku_msg.sub.unk2C = 0x26;
            jimaku_msg.sub.unk38 = 0xAE;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x12C0:
            jimaku_msg.sub.unk2C = 0x2B;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x15CC:
            jimaku_msg.sub.unk2C = 0x1B;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x17A2:
            jimaku_msg.sub.unk2C = 0x1D;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x1A54:
            jimaku_msg.sub.unk2C = 0x30;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x1B44:
            jimaku_msg.sub.unk2C = 0x31;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 7300.0f);
    _ACTWait(0);
}

void actSt04aGateOpen(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(140) == 0) {
        stage_SetAnimation(270, 0, 0);

        scpSearchGobj(669)->f16C = 0;

        gate_open_mail[0].func = actSt04aGateOpenChk;
        self->mail = gate_open_mail;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        SetWayGroupActive(2, 1);

        stage_SetAnimation(270, 0, -1);
        stage_SetAnimation(272, 0, -1);
        stage_SetAnimation(275, 0, -1);

        scpSearchGobj(669)->f16C = 0;

        SetGirlHairDispSwitch(girlGObj, 1);
    }
}

typedef struct AnimList {
    int v[13];
} AnimList;

/* .rodata, used here and by actConte09_2 (MAIN.MAP names no symbol in
   st04a.o's run): the two lift offsets.  Declared ahead and defined after
   actSt04aGateOpenChk: the ROM emits them after that function's own block
   constants. */
static const ConstVec liftOfs1;

static const ConstVec liftOfs2;

extern char D_00618DB0[];

void actSt04aGateOpenChk(volatile int a0)
{
    int *th1;
    int *th2;
    int *th3;
    int i;
    int n;

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (1) {
        if ((((PObjGObjSt04A *)girlGObj)->act->unk34 != 0x6F &&
             scpTriggerBall(a0, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(a0, girlGObj, 200.0f) != 0 && gflagChk(174) != 0 &&
             gflagChk(243) != 0) ||
            (((PObjGObjSt04A *)girlGObj)->act->unk34 != 0x6F &&
             scpTriggerBall(a0, boyGObj, 200.0f) != 0 &&
             scpTriggerBall(a0, girlGObj, 200.0f) != 0)) {
            break;
        }
        _ACTWait(1);
    }

    lt_switch_layout(55);

    scpBoyControlReadDisable = 1;

    scpPlayStart(girlGObj);

    scpSleepEnemyAll();

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpPlayMot(girlGObj, 532);

    StandbyStreamMotion(D_00618DB0);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(31, &gate_open, 1, 1, 1);
    while (gate_open == 0) {
        _ACTWait(1);
    }

    scpDisActivateAllWithKind(0x13);

    th1 = (int *)actCreateSubThread(actConte09, 21);
    th2 = (int *)actCreateSubThread(actSt04aEnvSeWakare1, 21);
    th3 = (int *)actCreateSubThread(actConte09Jimaku, 21);

    demoEnd = 0;
    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    n = demoEnd ^ 1;

    if (n != 0) {
        scpAdpcmFadeCloseFunc(&gate_open, 0xC0);

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
            /* the second gate's animations, in the order they start */
            static const AnimList gateOpen2Anims = {{712, 713, 714, 715, 716, 717, 718, 719, 720,
                                                     721, 722, 723, 724}}; /* derived name */
            AnimList anim;
            unsigned int j;

            anim = gateOpen2Anims;
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

        SetGirlHairDispSwitch(girlGObj, 1);

        {
            /* the boy's and the girl's root positions after the second gate */
            static const ConstVec boyRootPos2 __attribute__((aligned(16))) = {
                {29.91216f, -71.98232f, -118.11676f, 0.0f}}; /* derived name */
            static const ConstVec girlRootPos2 __attribute__((aligned(16))) = {
                {-49.44171f, -76.71414f, -142.27318f, 0.0f}}; /* derived name */
            long long p1[2];
            long long p2[2];

            p1[0] = boyRootPos2.d[0];
            p1[1] = boyRootPos2.d[1];
            SetDirectRootPosition(boyGObj, p1);

            p2[0] = girlRootPos2.d[0];
            p2[1] = girlRootPos2.d[1];
            SetDirectRootPosition(girlGObj, p2);
        }

        _ACTWait(1);

        SetCameraFlag_GamecamCutBack();

        scpFadeIn(3.0f);
    }

    {
        long long ofs[2];
        float dir[4];

        scpSeEnvMasterVolRate = 1.0f;

        scpPlayStart(boyGObj);

        scpPlayMot(boyGObj, 0);

        ofs[0] = liftOfs1.d[0];
        ofs[1] = liftOfs1.d[1];
        sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)girlGObj));
        scpPlayMotDir(girlGObj, dir);
    }

    _ACTWait(1);

    scpPlayEnd(boyGObj);
    scpPlayEnd(girlGObj);

    scpBoyControlReadDisable = 0;

    lt_switch_layout(54);

    SetWayGroupActive(2, 1);

    scpSearchGobj(648)->f16C = 0;
}

static const ConstVec liftOfs1 __attribute__((aligned(16))) = {{0.0f, 0.0f, 6000.0f, 1.0f}};

static const ConstVec liftOfs2 __attribute__((aligned(16))) = {{-5000.0f, 0.0f, 5300.0f, 1.0f}};

void actConte09(volatile int a0)
{
    int th1;
    int th2;

    th1 = EntryStreamMotion(boyGObj);
    th2 = EntryStreamMotion(girlGObj);

    SetStreamMotionFinishCallBackFunc(th1, finishCallBackFunc);
    SetStreamMotionFinishCallBackFunc(th2, finishCallBackFunc);

    PlayStreamMotion();

    scpPlayMot(boyGObj, 0);

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

    iosPadActRequest(boyPad, 0xF);

    scpKillEnemyAll();

    while (stage_ContinueAnimation(714, 715) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(715, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 0x10);

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

    SetGirlHairDispSwitch(girlGObj, 1);

    while (stage_ContinueAnimation(718, 719) == 0) {
        _ACTWait(1);
    }

    _ACTWait(300);

    stage_SetAnimation(275, 1, 0);

    _ACTWait(120);

    yure1 = iosPadActRequest(boyPad, 0xA);
    vol1 = 0x80;
    iosPadActVolumeSet(yure1, 0x80);

    while (stage_ContinueAnimation(719, 720) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(272, 1, 0);

    while (stage_ContinueAnimation(720, 721) == 0) {
        _ACTWait(1);
    }

    iosPadActStop(yure1);

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

    GOBJ_SUB(boyGObj)->f_514 =
        (int)((float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f * 0.0f);
    GOBJ_SUB(girlGObj)->f_514 =
        (int)((float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f * 0.0f);

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
            jimakuBegin(&jimaku_msg);
            break;
        case 0x871:
            jimaku_msg.sub.unk2C = 0x58;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        case 0x97E:
            jimaku_msg.sub.unk2C = 0x56;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f;
        if (n != (int)tn) {
            _ACTWait(1);
            t = tn;
        } else {
            t = tn + 1.0f;
        }
    } while (t < 2700.0f);
    _ACTWait(0);
}

/* st04a.o's own .rodata: the gate-open exit direction vector. */

void actSt04aGateOpen2Chk(volatile int a0)
{
    long long ofs[2];
    float dir[4];

    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (scpTriggerFloorAttr(girlGObj, 0x1000000) == 0 || ACTGame_FLAG_TETSUNAGI() == 0) {
        _ACTWait(1);
    }

    ((PObjGObjSt04A *)girlGObj)->act->flags20.ll &= ~0x10000;
    scpPlayMotReq(girlGObj, 0x13B);

    scpPlayMot(boyGObj, 0);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)boyGObj));
    scpPlayMotDir(boyGObj, dir);

    lt_switch_layout(55);

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    scpDisActivateAllWithKind(0x13);

    while (gate_open2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(gate_open2 + 0x2C));

    actCreateSubThread(actConte09_2, 21);
}

extern char D_00618E10[];

/* st04a.o's own .rodata: the two demo exit direction vectors. */

void actConte09_2(volatile int a0)
{
    long long ofs[2];
    float dir[4];
    int i;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);

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

    iosPadActRequest(boyPad, 0xF);

    while (stage_ContinueAnimation(729, 730) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(730, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActRequest(boyPad, 0x10);

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

    yure2 = iosPadActRequest(boyPad, 0xA);
    vol2 = 0x80;
    iosPadActVolumeSet(yure2, 0x80);

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

    ClearStreamMotionEntry(girlGObj);

    scpPlayMotReq(girlGObj, 0x13B);

    scpPlayPosSet(girlGObj, 14.8948f, 210.136f, 4858.48f);

    ofs[0] = liftOfs1.d[0];
    ofs[1] = liftOfs1.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)girlGObj));
    scpPlayMotDir(girlGObj, dir);

    lt_switch_layout(54);

    while (stage_CheckAnimationFinish(741) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    iosPadActStop(yure2);

    ofs[0] = liftOfs2.d[0];
    ofs[1] = liftOfs2.d[1];
    sceVu0SubVector(dir, ofs, test_CURRENTROOT((int)boyGObj));
    scpPlayMotDir(boyGObj, dir);

    StandbyStreamMotion(D_00618E10);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(33, &conte09_2, 1, 1, 0);

    scpPlayEnd(boyGObj);

    scpBoyControlReadDisable = 0;

    gflagOn(141);
}

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

        gate_open3_mail[0].func = actSt04aGateOpen3Chk;
        self->mail = gate_open3_mail;
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
    if (girlGObj == 0) {
        _ACTWait(0);
    }

    while (gflagChk(141) == 0 || scpTriggerBall(a0, boyGObj, 450.0f) == 0) {
        _ACTWait(1);
    }

    gflagOn(142);

    lt_switch_layout(55);

    scpBoyControlReadDisable = 1;
    scpPlayStart(boyGObj);
    scpPlayStart(girlGObj);

    if (gate_open2 != 0) {
        scpAdpcmFadeCloseFunc(&gate_open2, 0x50);
    }

    while (conte09_2 == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(conte09_2 + 0x2C));

    actCreateSubThread(actSt04aEnvSeWakare2, 21);
    actCreateSubThread(actConte09_3, 21);
    actCreateSubThread(actConte09_3Jimaku, 21);
}

void actConte09_3(volatile int a0)
{
    conte09_3Running = 1;

    actCreateSubThread(actConte09_3_demoCancel, 21);

    scpSearchGobj(669)->f16C = 1;

    EntryStreamMotion(boyGObj);
    EntryStreamMotion(girlGObj);
    EntryStreamMotion((char *)scpSearchGobj(669));

    PlayStreamMotion();

    scpSetStreamMotionRootOffset(boyGObj, 0.0f, 0.0f, 1.0f);
    scpSetStreamMotionRootOffset(girlGObj, 0.0f, 0.0f, 1.0f);

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

    shadow_SetLength((int)((PObjGObjSt04A *)girlGObj)->f15C, 20.0f);

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

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    _ACTWait(1);

    scpSearchGobj(649)->f16C = 0;

    SetStaticBlur(0);

    while (stage_CheckAnimationFrame(753, 150, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll("face_sadow_sd", 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll("face_sadow_sd_00", 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

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

    shadow_SetLength((int)((PObjGObjSt04A *)girlGObj)->f15C, 0.0f);

    while (stage_ContinueAnimation(755, 756) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(726, -1, -2);
    stage_SetAnimation(727, 1, 0);

    SetGirlClothDispSwitch(girlGObj, 1, 0);
    SetGirlClothDispSwitch(girlGObj, 0, 0);
    SetGirlClothDispSwitch(girlGObj, 2, 0);

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

    RequestStageChange(3, boyGObj, 0, 16.0f, 16.0f);
}

void actSt04aGateLChk(volatile int a0)
{
    int *th;

    while (gflagChk(174) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    scpBoyControlReadDisable = 1;
    gflagOn(138);

    scpAdpcmPlayRequestFunc(29, &gate_ready_l, 1, 1, 1);
    while (gate_ready_l == 0) {
        _ACTWait(1);
    }

    preload(4);

    scpFadeIn(16.0f);

    th = (int *)actCreateSubThread(actSt04aGateLSub, 21);

    demoEnd = 0;

    while (scpFadeChk() != 0) {
        _ACTWait(1);
    }

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 9, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&gate_ready_l, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(293, 0, -1);

        scpFadeIn(3.0f);
    }

    RequestStageChange(4, boyGObj, 0, 1.0f, 8.0f);
}

void actSt04aGateRChk(volatile int a0)
{
    int *th;
    int stage;

    while (gflagChk(234) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);

    scpBoyControlReadDisable = 1;
    gflagOn(139);

    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(30, &gate_ready_r, 1, 1, 1);
    while (gate_ready_r == 0) {
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

    while (demoEnd == 0 && ((pad[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    iosThreadSetPri(th + 9, 34);

    if (demoEnd == 0) {
        scpFadeOut(16.0f, 0, 0, 0);

        scpAdpcmFadeCloseFunc(&gate_ready_r, 0x100);

        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }

        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }

        stage_SetAnimation(295, 0, -1);

        scpFadeIn(3.0f);
    }

    RequestStageChange(stage, boyGObj, 0, 1.0f, 8.0f);
}

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

        torch1_mail[0].func = actSt04aTorch1Chk;
        self->mail = torch1_mail;
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
            scpBoyControlReadDisable = 1;

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

            scpBoyControlReadDisable = 0;
            break;
        }
        _ACTWait(1);
    }
}

void actSt04aTorchAllFlagfChk(volatile int a0)
{
    int i;
    int skip = 0;

    while (gflagChk(145) == 0 || gflagChk(146) == 0 || gflagChk(147) == 0 || gflagChk(148) == 0 ||
           gflagChk(149) == 0 || gflagChk(150) == 0 || gflagChk(151) == 0 || gflagChk(152) == 0) {
        _ACTWait(1);
    }

    lt_switch_layout(55);
    scpBoyControlReadDisable = 1;
    scpSleepEnemyAll();
    gflagOn(153);
    WakeupHint(6);
    WakeupHint(4);
    scpAdpcmPlayRequestFunc(85, &torch, 1, 1, 1);
    while (torch == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(282, 1, 0);
    while (stage_CheckAnimationFrame(282, 60, 0) == 0 && skip == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
        _ACTWait(1);
    }

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

    while (stage_CheckAnimationFinish(282) == 0 && skip == 0) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
        _ACTWait(1);
    }

    for (i = 60; i-- > 0 && skip == 0;) {
        if ((pad[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
        _ACTWait(1);
    }

    if (skip != 0) {
        scpAdpcmFadeCloseFunc(&torch, 0xC0);
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        stage_SetAnimation(282, 0, -1);
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }
    scpBoyControlReadDisable = 0;
    lt_switch_layout(54);
    scpWakeupEnemyAll();
}

void actSt04aTorchHintChk(volatile int a0)
{
    while (gflagChk(155) == 0) {
        _ACTWait(1);
    }

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(563), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(564), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(565), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(566), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(567), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(568), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(569), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(570), 1.0f, 0.001f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(591), 1.0f, 0.001f, 1.0f);

    if (gflagChk(156) == 0) {
        _ACTWait((0x3C - systemStatus[0] * 0xA) / systemStatus[1] * 0x14);
    }

    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(563), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(564), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(565), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(566), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(567), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(568), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(569), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(570), 10.0f, 0.01f, 1.0f);
    OverrideBrainStatusByGObj(&brainGirl, scpSearchGobj(591), 2.0f, 0.01f, 1.0f);

    gflagOn(156);
}

void actSt04aGateL(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(138) == 0) {
        gflagOn(389);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(295, 0, 0);

        gate_l_mail[0].func = actSt04aGateLChk;
        self->mail = gate_l_mail;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04aGateR(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(139) == 0) {
        gflagOn(389);

        scpFadeOut(255.0f, 0, 0, 0);

        stage_SetAnimation(293, 0, -1);

        gate_r_mail[0].func = actSt04aGateRChk;
        self->mail = gate_r_mail;
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

    while (gflagChk(141) == 0 || scpTriggerBall(a0, boyGObj, 600.0f) == 0) {
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

void actSt04aGateOpen2(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(141) == 0) {
        scpSearchGobj(669)->f16C = 0;

        gate_open2_mail[0].func = actSt04aGateOpen2Chk;
        self->mail = gate_open2_mail;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04aGateOpen2Ready(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    gate_open2_ready_mail[0].func = actSt04aGateOpen2ReadyChk;
    self->mail = gate_open2_ready_mail;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04aGirlSit(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    girl_sit_mail[0].func = actSt04aGirlSitChk;
    self->mail = girl_sit_mail;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04aTorchHint(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(153) == 0) {
        torch_hint_mail[0].func = actSt04aTorchHintChk;
        self->mail = torch_hint_mail;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt04aModel(volatile int a0)
{
    int x = a0;
    ActSt04A *self = actInitialize(a0);
    _ACTWait(1);

    scpSearchGobj(648)->f16C = 0;

    model_mail[0].func = actSt04aModelOnChk;
    self->mail = model_mail;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt04aEnvSe(volatile int a0)
{
    float f = 0.0f;

    scpSeEnvMasterVolRate = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 5401) {
            scpSeEnvMasterVolRate += 1.0f / 1800.0f;
            if (scpSeEnvMasterVolRate > 1.0f) {
                scpSeEnvMasterVolRate = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

void actSt04aEnvSeWakare1(volatile int a0)
{
    float f = 0.0f;

    scpSeEnvMasterVolRate = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2201) {
            scpSeEnvMasterVolRate += 1.0f / 3800.0f;
            if (scpSeEnvMasterVolRate > 1.0f) {
                scpSeEnvMasterVolRate = 1.0f;
                break;
            }
        }
    }
    _ACTWait(0);
}

typedef struct {
    float m[4];
} Vec4St04A;

void finishCallBackFunc(int a0)
{
    Vec4St04A v;
    int i;

    _ApplyMatrix((int)&v, GOBJ_SUB(a0)->f_C, (int)YUnitVector);
    v.m[1] = 0.0f;
    _NormalizeVector((int)GOBJ_SUB(a0) + 0x520, (int)&v);

    for (i = 0; i < GOBJ_SUB(a0)->f_88; i++) {
        *(Mtx44 *)(*(int *)((int)GOBJ_SUB(a0) + 0x80C) + i * 64) = jointMtxInit;
    }
}

extern char D_00618DE0[];

void actSt04aGateOpen2ReadyChk(volatile int a0)
{
    int x = a0;
    int i;

    actInitialize(a0);
    _ACTWait(1);

    while (girlGObj == 0 || scpTriggerFloorAttr(girlGObj, 0x2000000) == 0) {
        _ACTWait(1);
    }

    StandbyStreamMotion(D_00618DE0);

    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy("Now waiting for standby stream motion system... %d\n", i);
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(32, &gate_open2, 1, 0, 0);
}

void actSt04aEnvSeWakare2(volatile int a0)
{
    float f = 0.0f;

    for (;;) {
        float nf = f + (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f;
        if ((int)f != (int)nf) {
            _ACTWait(1);
            f = nf;
        } else {
            f = nf + 1.0f;
        }
        if ((int)f >= 2351) {
            scpSeEnvMasterVolRate -= 1.0f / 720.0f;
            if (scpSeEnvMasterVolRate < 0.0f) {
                scpSeEnvMasterVolRate = 0.0f;
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
            jimakuBegin(&jimaku_msg);
            break;
        case 2470:
            jimaku_msg.sub.unk2C = 91;
            jimaku_msg.sub.unk38 = 300;
            jimakuOn = 1;
            jimakuJump(&jimaku_msg);
            break;
        }

        n = (int)t;
        tn = t + (float)((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) / 60.0f;
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
    ((ActStatus *)(*(char **)(girlGObj + 0x164) + 0x20))->ll |= 0x10000;
    n = 0;
    for (;;) {
        if ((int)(GOBJ_ACT(girlGObj)->flags20.ll >> 20) & 1) {
            n++;
        } else {
            n = 0;
        }
        if (((0x3C - systemStatus[0] * 0xA) / systemStatus[1]) * 3 < n) {
            iosOmSendMail(girlGObj, 0x6D, girlGObj);
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

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) != 0) {
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

    while (scpTriggerFloorAttr(boyGObj, 0x3000000) == 0) {
        _ACTWait(1);
    }

    scpSearchGobj(648)->f16C = 0;

    model_off[0].func = actSt04aModelOnChk;
    sub->mail = model_off;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
