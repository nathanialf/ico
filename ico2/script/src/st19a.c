#include "common.h"
#include "st19a.h"
#include "layout_texture.h"
#include "thread.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act.h"
#include "commonact.h"
#include "camera-root.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "motionManager2.h"

typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD0];  /* 0x00 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
} Act;

typedef struct PObjGObj {
    char pad00[0x164]; /* 0x000 */
    int act;           /* 0x164 */
    char pad168[0x4];  /* 0x168 */
    int f16C;          /* 0x16C */
} PObjGObj;

/* kept local: this TU's uses of scpSearchGobj do not fit the prototype in script.h */
extern PObjGObj *scpSearchGobj(int a0);
/* kept local: this TU's uses of ScpCallCameraSetTarget do not fit the prototype in script.h */
extern void ScpCallCameraSetTarget(float x, float y, float z);
extern int D_0063AA08;
extern char *pipe19a;
extern int D_0063C5A4;

/* st19a.o's own .data run (no MAIN.MAP symbols): actor mail packets. */

static ActMail oriMain_mes[2] = {{407, actSt19aOriSwitch}, {429}};

static ActMail ori_mes[2] = {{430}, {429}};

static ActMail oriSwitch_mes[2] = {{430}, {429}};

static float oriXLPos[4] = {-642.0f, 2132.0f, -2861.0f, 0.0f};

static float haguruma2Pos[4] = {486.0f, 2386.0f, -2917.0f, 0.0f};

static ActMail hagurumaChk_mes[2] = {{430}, {429}};

static ActMail pipe_mes[2] = {{430}, {429}};

static ActMail chainMain_mes[2] = {{406, actSt19aChainSwitch}, {429}};

static ActMail chain_mes[2] = {{430}, {429}};

static ActMail chainSwitch_mes[2] = {{430}, {429}};

/* kept local: this TU's uses of scpTriggerBall do not fit the prototype in script.h */
extern int scpTriggerBall(int a0, int a1, float r);

typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

extern PadState D_0028F8F0[];
extern int D_00639EA4;
/* kept local: this TU's uses of scpTriggerFloorAttr do not fit the prototype in script.h */
extern int scpTriggerFloorAttr(int a0, int a1);
/* kept local: this TU's uses of scpAdpcmPlayRequestNum do not fit the prototype in script.h */
extern int scpAdpcmPlayRequestNum(void);
/* kept local: this TU's uses of scpFadeOut do not fit the prototype in script.h */
extern void scpFadeOut(float t, int a1, int a2, int a3);
/* kept local: this TU's uses of scpFadeChk do not fit the prototype in script.h */
extern int scpFadeChk(void);
/* kept local: this TU's uses of scpFadeIn do not fit the prototype in script.h */
extern void scpFadeIn(float t);
extern char *fence_up_19a;
/* kept local: this TU's uses of scpAdpcmPlayRequestFunc do not fit the prototype in script.h */
extern void scpAdpcmPlayRequestFunc(int a0, char **a1, int a2, int a3, int a4);
/* kept local: this TU's uses of scpAdpcmFadeCloseFunc do not fit the prototype in script.h */
extern void scpAdpcmFadeCloseFunc(char **a0, int a1);

void actSt19aOriUp(volatile int a0)
{
    int skip = 0;
    int i;

    lt_switch_layout(55);
    _ACTWait(0x3C);
    scpAdpcmPlayRequestFunc(0x4A, &fence_up_19a, 1, 1, 1);
    while (fence_up_19a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x8E, 1, 0);
    gflagOn(0x136);
    while (stage_CheckAnimationFrame(0x8E, 0x59, 1) == 0) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&fence_up_19a, 0x200);
            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }
            stage_SetAnimation(0x8E, 0, 0x59);
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }
    for (i = 120; i-- > 0 && skip == 0;) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
    }
    if (skip == 0) {
        scpAdpcmFadeCloseFunc(&fence_up_19a, 0x100);
    }
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads, which is what makes gcc
   emit the ld/sd pair the ROM has. */
typedef union {
    float f[4];
    long long d[2];
} ConstVec;

static const ConstVec hagurumaPos = {{-642.0f, 2132.0f, -2861.0f, 0.0f}};

void actSt19aHaguruma(volatile int a0)
{
    long long pos[2];
    Act *sub;
    int x = a0;

    sub = actInitialize(a0);
    _ACTWait(1);
    pos[0] = hagurumaPos.d[0];
    pos[1] = hagurumaPos.d[1];
    soundSeDefPlay(0x545, 0, (float *)pos, 1);
    if (gflagChk(0x137) == 0) {
        scpSearchGobj(0x7A8)->f16C = 0;
        stage_SetAnimation(0x8B, 0, 0);
        stage_SetAnimation(0x8C, -1, -2);
        hagurumaChk_mes[0].func = actSt19aHagurumaChk;
        sub->mail = hagurumaChk_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        soundSeDefPlay(0x546, 0, haguruma2Pos, 1);
        soundSeDefPlay(0x547, 0, haguruma2Pos, 1);
        soundSeDefPlay(0x548, 0, haguruma2Pos, 1);
        scpSearchGobj(0x7A9)->f16C = 0;
        stage_SetAnimation(0x8B, 1, 0);
        stage_SetLoopFlag(0x8B, 1);
        stage_SetLoopFlag(0x8C, 1);
    }
}

extern char *fence_down_19a;

void actSt19aHagurumaChk(volatile int a0)
{
    int skip = 0;
    int i;

    while (scpTriggerBall(a0, (int)scpSearchGobj(0x7A9), 220.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    D_0063AA08 = 1;
    gflagOn(0x137);
    scpAdpcmPlayRequestFunc(0x4C, &fence_down_19a, 1, 1, 1);
    while (fence_down_19a == 0) {
        _ACTWait(1);
    }
    for (i = 60; i-- > 0 && skip == 0;) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
    }
    stage_SetAnimation(0x8D, 1, 0);
    for (i = 90; i-- > 0 && skip == 0;) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            skip = 1;
        }
    }
    _ACTWait(1);
    stage_SetAnimation(0x8B, 1, 0);
    stage_SetAnimation(0x8C, 1, 0);
    scpSearchGobj(0x7A9)->f16C = 0;
    scpSearchGobj(0x7A8)->f16C = 1;
    stage_SetLoopFlag(0x8B, 1);
    stage_SetLoopFlag(0x8C, 1);
    soundSeDefPlay(0x546, 0, haguruma2Pos, 1);
    soundSeDefPlay(0x547, 0, haguruma2Pos, 1);
    soundSeDefPlay(0x548, 0, haguruma2Pos, 1);
    while (stage_CheckAnimationFinish(0x8D) == 0) {
        if (((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) || skip != 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&fence_down_19a, 0x200);
            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }
            stage_SetAnimation(0x8D, 0, -1);
            scpFadeIn(3.0f);
            D_0063AA08 = 0;
            goto done;
        }
        _ACTWait(1);
    }
    D_0063AA08 = 0;
done:
    lt_switch_layout(54);
}

extern char *hgrm_19a;
/* kept local: this TU's uses of scpPlayStart do not fit the prototype in script.h */
extern void scpPlayStart(int a0);
/* kept local: this TU's uses of scpPlayMot do not fit the prototype in script.h */
extern void scpPlayMot(int a0, int mot);
/* kept local: this TU's uses of scpPlayEnd do not fit the prototype in script.h */
extern void scpPlayEnd(int a0);
/* kept local: this TU's uses of scpPlayPosSet do not fit the prototype in script.h */
extern void scpPlayPosSet(int a0, float x, float y, float z);

void actSt19aPipeChk(volatile int a0)
{
    int i;

    while (scpTriggerBall(a0, D_00639EA4, 50.0f) == 0) {
        _ACTWait(1);
    }
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpPlayStart(D_00639EA4);
    gflagOn(0x138);
    scpSearchGobj(0x7A6)->f16C = 0;
    _ACTWait(1);
    scpAdpcmPlayRequestFunc(0x54, &hgrm_19a, 1, 1, 1);
    while (hgrm_19a == 0) {
        _ACTWait(1);
    }
    stage_SetAnimation(0x8F, 1, 0);
    FeedbackWallWorkInfoToBrainSystem(D_00639EA4);
    scpPlayMot(D_00639EA4, 78);
    for (i = 300; i-- > 0;) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            scpFadeOut(16.0f, 0, 0, 0);
            scpAdpcmFadeCloseFunc(&hgrm_19a, 0x200);
            while (scpFadeChk() != 0) {
                _ACTWait(1);
            }
            while (lt_fade_status() != 2) {
                _ACTWait(1);
            }
            stage_SetAnimation(0x8F, 0, -1);
            scpPlayPosSet(D_00639EA4, 336.0f, 3933.0f, -402.0f);
            _ACTWait(4);
            scpFadeIn(3.0f);
            break;
        }
        _ACTWait(1);
    }
    scpSearchGobj(0x7A7)->f16C = 1;
    scpPlayEnd(D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt19aChainDown(volatile int a0)
{
    int *th;

    lt_switch_layout(55);
    scpAdpcmPlayRequestFunc(0x61, &pipe19a, 1, 1, 0);
    th = actCreateSubThread(actSt19aChainDownSub, 0x15);
    D_0063C5A4 = 0;
    while (D_0063C5A4 == 0) {
        if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
            break;
        }
        _ACTWait(1);
    }
    iosThreadSetPri(th + 9, 0x22);
    if (D_0063C5A4 == 0) {
        scpFadeOut(16.0f, 0, 0, 0);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
        while (lt_fade_status() != 2) {
            _ACTWait(1);
        }
        SetCameraFlag_LwsCutBack();
        scpFadeIn(3.0f);
    }
    scpSearchGobj(0x7AB)->f16C = 1;
    stage_SetAnimation(0x90, 0, 0x169);
    if (pipe19a != 0) {
        scpAdpcmFadeCloseFunc(&pipe19a, 0x100);
    }
    D_0063AA08 = 0;
    lt_switch_layout(54);
}

void actSt19bIntro(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);
    if (gflagChk(0x13A) == 0) {
        while (scpTriggerFloorAttr(D_00639EA4, 0x1000000) == 0) {
            _ACTWait(1);
        }
        lt_switch_layout(55);
        D_0063AA08 = 1;
        gflagOn(0x13A);
        stage_SetAnimation(0x89, 1, 0);
        while (stage_CheckAnimationFinish(0x89) == 0) {
            if ((D_0028F8F0[0].flags & 0x800) && scpAdpcmPlayRequestNum() == 0) {
                scpFadeOut(16.0f, 0, 0, 0);
                while (scpFadeChk() != 0) {
                    _ACTWait(1);
                }
                while (lt_fade_status() != 2) {
                    _ACTWait(1);
                }
                stage_SetAnimation(0x89, 0, -1);
                scpFadeIn(3.0f);
                break;
            }
            _ACTWait(1);
        }
        lt_switch_layout(54);
        D_0063AA08 = 0;
    }
}

void actSt19aOri(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    ScpCallCameraSetTarget(4298.0f, -2342.0f, 1331.0f);

    if (gflagChk(0x136) == 0) {
        stage_SetAnimation(0x8E, 0, 0);

        ori_mes[0].func = actSt19aOriMain;
        self->mail = ori_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x8E, 0, 0x59);
    }
}

void actSt19aOriXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    soundSeDefPlay(0x545, 0, oriXLPos, 1);

    stage_SetAnimation(0x8E, 0, 0);
}

void actSt19aPipe(volatile int a0)
{
    int x = a0;

    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x138) == 0) {
        scpSearchGobj(0x7A7)->f16C = 0;
        stage_SetAnimation(0x8F, 0, 0);

        pipe_mes[0].func = actSt19aPipeChk;
        self->mail = pipe_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);

    } else {
        scpSearchGobj(0x7A6)->f16C = 0;
        stage_SetAnimation(0x8F, 0, -1);
    }
}

void actSt19aPipeXL(volatile int a0)
{
    int x = a0;

    actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(0x138) == 0) {
        stage_SetAnimation(0x8F, 0, 0);
    } else {
        stage_SetAnimation(0x8F, 0, -1);
    }
}

void actSt19aChain(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);

    _ACTWait(1);

    if (gflagChk(0x139) == 0) {
        scpSearchGobj(0x7AB)->f16C = 0;

        stage_SetAnimation(0x90, 0, 0);

        chain_mes[0].func = actSt19aChainMain;
        self->mail = chain_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt19aOriMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = oriMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt19aOriSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;
    oriSwitch_mes[0].func = actSt19aOriUp;
    sub->mail = oriSwitch_mes;
    ACTSendMailCorrect(a0, 430);
    _ACTWait(0);
}

void actSt19aChainMain(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 0;

    sub->mainMail = chainMain_mes;

    while (1) {
        _ACTWait(1);
    }
}

void actSt19aChainSwitch(volatile int a0)
{
    Act *sub = (Act *)((PObjGObj *)a0)->act;

    D_0063AA08 = 1;

    sub->mainMail = 0;

    if (gflagChk(0x139) == 0) {
        chainSwitch_mes[0].func = actSt19aChainDown;
        sub->mail = chainSwitch_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actSt19aChainDownSub(volatile int a0)
{
    _ACTWait(0x3C);

    while (pipe19a == 0) {
        _ACTWait(1);
    }

    AdpcmPlay(*(int *)(pipe19a + 0x2C));

    stage_SetAnimation(0x90, 1, 0);

    gflagOn(0x139);

    SetCameraFlag_LwsCutBack();

    while (stage_CheckAnimationFrame(0x90, 0xF0, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);

    D_0063C5A4 = 1;
    _ACTWait(0x3C);
}
