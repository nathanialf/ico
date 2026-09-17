#include "common.h"
#include "st25a.h"
#include "StageManager.h"
#include "debug.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "adpcm_init.h"
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

/* kept local: this TU's uses of scpGameStat_BoyWeaponkind do not fit the prototype in script.h */
extern int scpGameStat_BoyWeaponkind(void);
/* kept local: this TU's uses of scpLinkBGAtoLayoutedTarget do not fit the prototype in script.h */
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);
extern int D_0063AA30;
extern int D_00639EA4;
extern JimakuArg jimaku_msg;
extern int jimakuOn;
/* kept local: this TU's uses of jimakuJump do not fit the prototype in jimaku.h */
extern void jimakuJump(int a0);
extern int D_0028F4C0[];
/* kept local: this TU's uses of jimakuBegin do not fit the prototype in jimaku.h */
extern void jimakuBegin(int a0);
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
extern int dead;
extern char D_00618ED0[];

/* st25a.o's whole .rodata run, in the order the object emits it; the 0.15
   double that closes the run is actSt25aElevChk's own constant-pool operand. */
/* kept local: this TU's bytes only come out with its own view of Vec4, so it
   keeps one under its own name; the shared view is in ico2/common/include/typedef.h. */
typedef union Vec4St25A {
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) Vec4St25A;

typedef struct AnimSet18 {
    int anim[18]; /* 0x00 */
} AnimSet18;

/* the two face-shadow textures ConteQueenDead scrolls the UVs of. */
const char faceShadowTex[] = "face_sadow_sd"; /* script.c scrolls it too */

const char faceShadowTex00[] = "face_sadow_sd_00";

/* The offset the sekika boy is dropped by. */
static const Vec4St25A sekikaOfs = {{2000.0f, 0.0f, 0.0f, 1.0f}};

static const char streamWaitFmt[] = "Now waiting for standby stream motion system... %d\n";

/* The eighteen stage animations the cancelled ending restores. */
static const AnimSet18 cancelAnimSet = {
    {784, 785, 786, 787, 788, 789, 790, 791, 792, 793, 794, 795, 796, 797, 798, 799, 800, 801}};

/* Where the boy is put back when the ending is cancelled. */
static const Vec4St25A cancelBoyPos = {{-1472.7711f, 928.20026f, -18.074427f, 0.0f}};

static const char queenBallScrTexture[] = "queen_ball_scr";

static const char sekikaBoyTexture[] = "sekika_boy";

/* st25a.o's whole .data run: ten actor mail records, in ROM order.  Each is
   the usual pair, the 430 entry whose handler the sender fills in and the 429
   terminator.  queen_appear_mes is the only one another TU sends, so it is the
   only global of the ten. */
static ActMail queen_before_mes[2] = {{430}, {429}};

ActMail queen_appear_mes[2] = {{430}, {429}};

static ActMail queen_talk_mes[2] = {{430}, {429}};

static ActMail queen_dead_ready_mes[2] = {{430}, {429}};

static ActMail queen_dead_mes[2] = {{430}, {429}};

static ActMail queen_attack_mes[2] = {{430}, {429}};

static ActMail elev_up_mes[2] = {{430}, {429}};

static ActMail elev_down_mes[2] = {{430}, {429}};

static ActMail elev_chara_mes[2] = {{430}, {429}};

static ActMail elev_end_mes[2] = {{430}, {429}};

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
void actSt25aQueenBeforeChk(volatile int a0);
void actSt25aQueenDeadReadyChk(volatile int a0);
void actItouQueenAttackChk(volatile int a0);
extern int enable_game_pause;
extern int D_0063AA08;
void actConte11(volatile int a0);
void actConte11Jimaku(volatile int a0);

void actSt25aQueenAppearChk(volatile int a0)
{
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0 || gflagChk(0x14B) == 0) {
        _ACTWait(1);
    }
    enable_game_pause = 0;
    gflagOn(0x14C);
    actCreateSubThread(actConte11Jimaku, 0x15);
    while (D_0063AA30 == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(D_0063AA30 + 0x2C));
    D_0063AA08 = 1;
    _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 3);
    actCreateSubThread(actConte11, 0x15);
}

/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpPlayMotDir do not fit the prototype in script.h */
extern void scpPlayMotDir(int a0, void *dir);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag do not fit the prototype in script.h */
extern void scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(int a0, int a1, int a2, int a3);
/* kept local: this TU's uses of scpSekizouCheckPoint do not fit the prototype in script.h */
extern void scpSekizouCheckPoint(void);

void actConte11(volatile int a0)
{
    Vec4St25A ofs;
    float dir[4];

    lt_switch_layout(0x37);
    scpPlayStart(D_00639EA4);

    stage_SetAnimation(0x2FC, 1, 0);

    scpPlayMot(D_00639EA4, 0x190);
    scpSearchGobj(0x865)->f16C = 1;
    scpPlayMot((int)scpSearchGobj(0x865), 0x450);

    _ACTWait(1);
    stage_SetAnimation(0x9C, 1, 0);

    scpLinkBGAtoKindTargetSkeltonWithLocalRotationFlag(0x2F, 0, 0x22B, 0);

    stage_SetLoopFlag(0x22B, 1);
    stage_SetAnimation(0x22B, 1, 0);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.99f, 0.99f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.1f, 0.1f, 1);

    while (stage_ContinueAnimation(0x2FC, 0x2FD) == 0) {
        _ACTWait(1);
    }
    while (stage_CheckAnimationFrame(0x2FD, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    tex_SetUVScroll(faceShadowTex, 0.0f, 0.0f, 0.25f, 0.0625f, 0.8f, 0.8f, 1);
    tex_SetUVScroll(faceShadowTex00, 0.0f, 0.0f, 0.25f, 0.0625f, 0.45f, 0.45f, 1);

    scpPlayMot((int)scpSearchGobj(0x865), 0x451);

    scpPlayMot(D_00639EA4, 0);
    ofs = sekikaOfs;
    sceVu0SubVector(dir, &ofs, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir);

    SetCameraFlag_LwsCutBack();
    while (stage_CheckAnimationFinish(0x2FD) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    scpSekizouCheckPoint();

    lt_switch_layout(0x36);

    _ACTWait(0x3C);

    scpPlayEnd(D_00639EA4);

    D_0063AA08 = 0;
    enable_game_pause = 1;
}

typedef union QueenWork {
    AnimSet18 a;
    Vec4St25A v[3];
} QueenWork;

extern char D_00618E70[];
extern int D_0028F8F4[];
extern int conte12;
extern int sd2;

/* .sbss, owned by st25a.o and reached only from this file (MAIN.MAP names no
   symbol in the run), in the ROM's run order: the flag the demo raises when it
   is over, and the one its inner event raises when that has run. */
static int demoEnd;

static int eventDone;

/* kept local: this TU's uses of scpPlayMotReq do not fit the prototype in script.h */
extern void scpPlayMotReq(int a0, int mot);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(int *a0, int a1);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float f);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of ScpCallCameraTargetOff do not fit the prototype in script.h */
extern void ScpCallCameraTargetOff(void);
/* kept local: this TU's uses of jimakuUndisp do not fit the prototype in jimaku.h */
extern void jimakuUndisp(int a0);

void actSt25aQueenTalkChk(volatile int a0)
{
    QueenWork w;
    unsigned int i;
    unsigned int n;
    int cancel;
    int th1;
    int th2;

    conte12 = sd2 = 0;

    while (scpTriggerFloorAttr(D_00639EA4, 0x3000000) == 0 || gflagChk(0x14C) == 0) {
        _ACTWait(1);
    }

    iosPadActStopAll();

    lt_switch_layout(0x37);
    D_0063AA08 = 1;

    scpPlayMotReq(D_00639EA4, 1);

    StandbyStreamMotion((int)D_00618E70);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }

    gflagOn(0x14D);

    scpAdpcmPlayRequestFunc(0x28, &conte12, 1, 1, 1);
    while (conte12 == 0) {
        _ACTWait(1);
    }

    th1 = actCreateSubThread(actConte12, 0x15);
    th2 = actCreateSubThread(actConte12Jimaku, 0x15);

    demoEnd = 0;
    eventDone = 0;

    while (demoEnd == 0 && ((D_0028F8F4[0] & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }

    cancel = demoEnd ^ 1;

    if (cancel != 0) {
        scpAdpcmFadeCloseFunc(&conte12, 0x100);

        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }

    DeleteStreamMotionManager();
    iosPadActStopAll();
    iosThreadSetPri((int *)(th1 + 0x24), 0x22);
    iosThreadSetPri((int *)(th2 + 0x24), 0x22);

    if (cancel != 0) {
        w.a = cancelAnimSet;
        for (n = 0; n < 18; n++) {
            stage_SetAnimation(w.a.anim[n], 1, -1);
            _ACTWait(1);
        }

        ScpCallCameraTargetOff();
        DeleteBoyWeapon();
        scpLinkBGAtoLayoutedTarget(0x86E, 0x1E7);

        scpSearchGobj(0x86E)->f16C = 1;
        stage_SetAnimation(0x9D, -1, -2);
        SelectBoyCrown(D_00639EA4, 1);

        stage_SetAnimation(0x22C, 0, -1);
        stage_SetAnimation(0x230, 0, -1);
        stage_SetAnimation(0x231, 0, -1);

        stage_SetAnimation(0x321, 1, -1);
        jimakuUndisp((int)&jimaku_msg);

        w.v[0] = cancelBoyPos;
        SetDirectRootPosition(D_00639EA4, &w.v[0]);

        if (eventDone == 0) {
            QueenStartAttack();
            gflagOn(0x14E);
        }

        _ACTWait(1);
        SetCameraFlag_GamecamCutBack();
        scpFadeIn(3.0f);
    }

    gflagOn(0x14F);

    scpPlayMot((int)scpSearchGobj(0x865), 0x430);
    scpPlayPosSet((int)scpSearchGobj(0x865), 1650.0f, 625.0f, 0.0f);

    memset(w.v[1].f, 0, 16);
    w.v[1].f[3] = 1.0f;
    sceVu0SubVector(w.v[2].f, w.v[1].f, test_CURRENTROOT((int)scpSearchGobj(0x865)));
    scpPlayMotDir((int)scpSearchGobj(0x865), w.v[2].f);
    scpPlayEnd((int)scpSearchGobj(0x865));

    scpPlayMot(D_00639EA4, 0);
    scpPlayEnd(D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);

    CameraSetCameraSet(0x33);

    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }

    scpAdpcmPlayRequestFunc(0x29, &sd2, 1, 0, 1);

    stage_SetAnimation(0x9F, -1, -2);

    stage_SetLoopFlag(0xA0, 1);

    stage_SetAnimation(0xA0, 1, 0);
}

extern int D_00639EAC;
extern int D_0063AA3C;

void actConte12(volatile int a0)
{
    D_0063AA3C = 0;

    scpSearchGobj(0x865)->f16C = 1;
    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion((int)scpSearchGobj(0x865));
    PlayStreamMotion();

    stage_SetAnimation(0x310, 1, 0);
    while (stage_ContinueAnimation(0x310, 0x311) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x311, 0x312) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x312, 0x313) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x313, 0x314) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x314, 0x315) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x315, 0x316) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x316, 0x317) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x317, 0x318) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x318, 0x319) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x319, 0x31A) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x31A, 0x31B) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x1DA, 1, 0);

    while (stage_ContinueAnimation(0x31B, 0x31C) == 0) {
        _ACTWait(1);
    }

    DeleteBoyWeapon();
    SelectBoyCrown(D_00639EA4, 1);
    stage_SetAnimation(0x9D, 1, 0);
    stage_SetAnimation(0x22C, 1, 0);

    scpLinkBGAtoLayoutedTarget(0x868, 0x1E7);

    iosPadActRequest(D_00639EAC, 15);
    while (stage_CheckAnimationFrame(0x31C, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 16);
    while (stage_CheckAnimationFrame(0x31C, 30, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 16);
    while (stage_CheckAnimationFrame(0x31C, 50, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 17);
    while (stage_CheckAnimationFrame(0x31C, 60, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 16);

    while (stage_ContinueAnimation(0x31C, 0x31D) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x230, 1, 0);

    while (stage_ContinueAnimation(0x31D, 0x31E) == 0) {
        _ACTWait(1);
    }

    scpLinkBGAtoLayoutedTarget(0x86E, 0x1E7);

    scpSearchGobj(0x86E)->f16C = 1;

    _ACTWait(1);
    stage_SetAnimation(0x231, 1, 0);

    stage_SetAnimation(0x9D, -1, -2);

    while (stage_ContinueAnimation(0x31E, 0x31F) == 0) {
        _ACTWait(1);
    }

    while (stage_ContinueAnimation(0x31F, 0x320) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x320, 0x321) == 0) {
        _ACTWait(1);
    }

    eventDone = 1;
    QueenStartAttack();
    gflagOn(0x14E);

    ScpCallCameraTargetOff();

    while (stage_CheckAnimationFinish(0x321) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    demoEnd = 1;
    _ACTWait(0);
}

void actConte12Jimaku(volatile int a0)
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
        case 341:
            jimaku_msg.sub.unk2C = 96;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 521:
            jimaku_msg.sub.unk2C = 97;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 801:
            jimaku_msg.sub.unk2C = 98;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1031:
            jimaku_msg.sub.unk2C = 99;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1301:
            jimaku_msg.sub.unk2C = 100;
            jimaku_msg.sub.unk38 = 200;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1781:
            jimaku_msg.sub.unk2C = 104;
            jimaku_msg.sub.unk38 = 200;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 2261:
            jimaku_msg.sub.unk2C = 105;
            jimaku_msg.sub.unk38 = 150;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 2561:
            jimaku_msg.sub.unk2C = 106;
            jimaku_msg.sub.unk38 = -1;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 3780:
            jimaku_msg.sub.unk2C = 109;
            jimaku_msg.sub.unk38 = 180;
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
    } while (t < 4200.0f);
    _ACTWait(0);
}

/* kept local: st25a's bytes only come out with its own view of the stage
   preload record, so it keeps one under its own name; the shared view lives in
   ico2/common/include/typedef.h as StgPre. */
typedef struct StgPreSt25a {
    unsigned char _0[0xA0];   /* 0x000 */
    short ent[0x18];          /* 0x0A0 */
    unsigned char _d0[0x80];  /* 0x0D0 */
    void (*endproc)(void);    /* 0x150 */
    unsigned char _154[0x38]; /* 0x154 */
    unsigned int attr;        /* 0x18C */
    unsigned char _190[0x4];  /* 0x190 */
} StgPreSt25a;

extern const StgPreSt25a D_005F5D50[];
extern const ExitData D_0055C518[];
extern int stage_no;
/* kept local: this TU's uses of scpKillEnemyAll do not fit the prototype in script.h */
extern void scpKillEnemyAll(void);
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern void RequestStageChange(int a0, int gobj, float f12, float f13, int a2);

void actSt25aQueenDeadChk(volatile int a0)
{
    while (QueenInqDead() == 0) {
        _ACTWait(1);
    }

    iosPadActRequest(D_00639EAC, 16);

    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    scpPlayStart((int)scpSearchGobj(0x865));

    if (sd2 != 0) {
        scpAdpcmFadeCloseFunc(&sd2, 0x100);
    }

    scpKillEnemyAll();

    gflagOn(0x152);
    gflagOn(5);

    while (dead == 0) {
        _ACTWait(1);
    }
    AdpcmPlay(*(int *)(dead + 0x2C));

    stgmgrNextStagePreLoadForceStageSet(D_0055C518[D_005F5D50[stage_no].ent[3]].f_24);
    stgmgrNextStagePreLoadForceNoCancel(1);

    scpSearchGobj(0x865)->f16C = 1;
    EntryStreamMotion(D_00639EA4);
    EntryStreamMotion((int)scpSearchGobj(0x865));
    PlayStreamMotion();

    actCreateSubThread(actConte13Jimaku, 0x15);

    stage_SetAnimation(0x322, 1, 0);

    scpSearchGobj(0x8B3)->f16C = 0;
    scpSearchGobj(0x8B4)->f16C = 0;

    while (stage_ContinueAnimation(0x322, 0x323) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x323, 0x324) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x324, 0x325) == 0) {
        _ACTWait(1);
    }

    *(int *)(*(int *)((char *)scpSearchGobj(0x865) + 0x15C) + 0x660) = 0;
    while (stage_ContinueAnimation(0x325, 0x326) == 0) {
        _ACTWait(1);
    }

    *(int *)(*(int *)((char *)scpSearchGobj(0x865) + 0x15C) + 0x660) = 1;
    while (stage_ContinueAnimation(0x326, 0x327) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x327, 0x328) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x1DE, 1, 0);
    iosPadActRequest(D_00639EAC, 15);
    DeleteBoyWeapon();
    stage_SetAnimation(0x1E7, -1, -2);
    stage_SetAnimation(0x9E, 1, 0);

    while (stage_ContinueAnimation(0x328, 0x329) == 0) {
        _ACTWait(1);
    }
    while (stage_ContinueAnimation(0x329, 0x32A) == 0) {
        _ACTWait(1);
    }

    SelectBoyCrown(D_00639EA4, 2);
    stage_SetAnimation(0x22D, 1, 0);

    while (stage_CheckAnimationFrame(0x32A, 15, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 17);

    while (stage_ContinueAnimation(0x32A, 0x32B) == 0) {
        _ACTWait(1);
    }

    stage_SetAnimation(0x22E, 1, 0);

    while (stage_CheckAnimationFrame(0x32B, 10, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadActRequest(D_00639EAC, 15);

    scpSearchGobj(0x865)->f16C = 0;
    stage_SetLoopFlag(0x22B, 0);

    while (stage_ContinueAnimation(0x32B, 0x32D) == 0) {
        _ACTWait(1);
    }

    while (stage_CheckAnimationFinish(0x32D) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    DeleteStreamMotionManager();

    RequestStageChange(4, D_00639EA4, 1.0f, 8.0f, 0);
}

void actConte13Jimaku(volatile int a0)
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
        case 600:
            jimaku_msg.sub.unk2C = 110;
            jimaku_msg.sub.unk38 = 400;
            jimakuOn = 1;
            jimakuJump((int)&jimaku_msg);
            break;
        case 1320:
            jimaku_msg.sub.unk2C = 111;
            jimaku_msg.sub.unk38 = 200;
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
    } while (t < 3100.0f);
}

void BoySekikaTexScroll(void)
{
    tex_SetUVScroll(sekikaBoyTexture, 0.0f, 0.0f, 0.0f, 0.01f, 0.0f, 0.5f, 1);
}

extern int D_0063AA44;
extern int D_0063AA48;
extern int D_00639EAC;
/* kept local: this TU's uses of RequestStageChange do not fit the prototype in script.h */
extern void RequestStageChange(int a0, int gobj, float f12, float f13, int a2);

void actSt25aElevChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    D_0063AA08 = 1;
    if (gflagChk(0x151) == 0) {
        scpAdpcmPlayRequestFunc(100, &D_0063AA48, 1, 1, 1);
        while (D_0063AA48 == 0) {
            _ACTWait(1);
        }
        _ACTWait((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]);
        stage_SetAnimation(0xA1, 1, 0);
        while (stage_CheckAnimationFrame(0xA1, 50, 0) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        iosPadActRequest(D_00639EAC, 16);
        while (stage_CheckAnimationFinish(0xA1) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        gflagOn(0x151);
    } else {
        scpAdpcmPlayRequestFunc(99, &D_0063AA44, 0, 1, 1);
        while (D_0063AA44 == 0) {
            _ACTWait(1);
        }
        _ACTWait((int)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1] * 0.15));
        stage_SetAnimation(0xA2, 1, 0);
        while (stage_CheckAnimationFinish(0xA2) == 0) {
            _ACTWait(1);
        }
        _ACTWait(1);
        gflagOff(0x151);
        RequestStageChange(1, D_00639EA4, 2.0f, 8.0f, 0);
    }
    D_0063AA08 = 0;
    lt_switch_layout(54);
    elev_chara_mes[0].func = actSt25aElevCharaChk;
    sub->mail = elev_chara_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt25aGenerator(volatile unsigned int a0)
{
    Generator_Mask(a0);
}

void actSt25aQueenBefore(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    MallocStreamMotionBuffer();

    if (gflagChk(0x14B) == 0) {
        queen_before_mes[0].func = actSt25aQueenBeforeChk;
        sub->mail = queen_before_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt25aQueenTalk(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    fightSoundProcessRequestPause();

    if (gflagChk(0x14D) == 0) {
        scpSearchGobj(0x86E)->f16C = 0;
        queen_talk_mes[0].func = actSt25aQueenTalkChk;
        sub->mail = queen_talk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt25aQueenDeadReady(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    queen_dead_ready_mes[0].func = actSt25aQueenDeadReadyChk;
    sub->mail = queen_dead_ready_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt25aQueenDead(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    queen_dead_mes[0].func = actSt25aQueenDeadChk;
    sub->mail = queen_dead_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actItouQueenAttack(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    queen_attack_mes[0].func = actItouQueenAttackChk;
    sub->mail = queen_attack_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt25aElev(volatile int a0)
{
    int x = a0;
    Act *sub = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x151) != 0) {
        stage_SetAnimation(0xA2, 0, 0);
        elev_up_mes[0].func = actSt25aElevChk;
        sub->mail = elev_up_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0xA1, 0, 0);
        elev_down_mes[0].func = actSt25aElevChk;
        sub->mail = elev_down_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSwordEff(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    scpLinkBGAtoLayoutedTarget(0x832, 0x1E7);
}

void actSwordEffXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (scpGameStat_BoyWeaponkind() == 5) {
        scpLinkBGAtoLayoutedTarget(0x832, 0x1E7);
    } else {
        stage_SetAnimation(0x1E7, -1, -2);
    }
}

void actSt25aQueenBeforeChk(volatile int a0)
{
    D_0063AA30 = 0;
    while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
        _ACTWait(1);
    }
    gflagOn(0x14B);
    jimakuBegin((int)&jimaku_msg);
    scpAdpcmPlayRequestFunc(0x27, &D_0063AA30, 1, 1, 0);
}

void actConte11Jimaku(volatile int a0)
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
            jimaku_msg.sub.unk2C = 0x5D;
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
    } while (t < 1500.0f);
}

void actSt25aQueenDeadReadyChk(volatile int a0)
{
    int i;

    dead = 0;
    while (InqQueenBarrierExist() != 0 || gflagChk(0x14E) == 0) {
        _ACTWait(1);
    }
    StandbyStreamMotion((int)D_00618ED0);
    i = 0;
    while (CheckReadyStreamMotion() == 0) {
        i++;
        debug_StdPrintfDummy(streamWaitFmt, i);
        _ACTWait(1);
    }
    scpAdpcmPlayRequestFunc(0x2A, &dead, 0, 1, 0);
}

void actSt25aQueenDeadEvent(int x)
{
    volatile int local = x;
}

void actItouQueenAttackChk(volatile int a0)
{
    while (1) {
        while (ForMotionViewer_GetCurrentMotion((char *)scpSearchGobj(0xDC6)) != 0x436) {
            _ACTWait(1);
        }
        tex_SetUVScroll(queenBallScrTexture, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 1);
        _ACTWait(1);
    }
}

void actSt25aElevCharaChk(volatile int a0)
{
    Act *sub = ((PObjGObj *)a0)->act;

    while (scpTriggerFloorAttr(D_00639EA4, 0x4000000) != 0) {
        _ACTWait(1);
    }

    elev_end_mes[0].func = actSt25aElevChk;
    sub->mail = elev_end_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}
