#include "common.h"

/* PAL listing rows: every instruction of actDeja is attributed to
 * script/src/deja.c lines 170-189 -- no inlined helper bodies.
 *
 * actDejaChk is this TU's own first function (the PAL listing names it
 * actDejaChk, deja.c:196); actDeja installs it as the actor's next mail
 * handler.  D_004F7988 is the 2-entry mail table that lives in the shared
 * src/cod .data carve, so it stays extern here. */
extern void _ACTWait(int a0);
extern int gflagChk(int a0);
extern void lt_switch_layout(int a0);
extern void scpFadeOut(float a0, int a1, int a2, int a3);
extern void stage_SetAnimation(int a0, int a1, int a2);
extern void actDejaChk(int a0);
extern int D_0063AA08;

typedef struct ActMail {
    int mail;          /* 0x00 */
    void (*func)(int); /* 0x04 */
    int unk08;         /* 0x08 */
    int unk0C;         /* 0x0C */
} ActMail;

typedef struct Act {
    char unk00[0xD4]; /* 0x00 */
    ActMail *mail;    /* 0xD4 */
} Act;

extern ActMail D_004F7988[];
extern Act *actInitialize(int a0);
extern void ACTSendMailCorrect(int a0, int mail);
extern void scpSleepEnemyAll(void);

/* --- su-b sweep decls --- */
typedef union {
    float f[4];
    long long w[2];
} Vec16;

extern char *D_00639EA4;
extern void ScpCallCameraOff(void);

typedef struct PadState {
    int unk00; /* 0x00 */
    int flags; /* 0x04 */
} PadState;

extern PadState D_0028F8F0[];
extern int D_0063C4DC;
extern float D_0063986C;
extern int scpSearchGobj(int id);
extern void actCreateSubThread(void *entry, int prio);
extern void scpAdpcmPlayRequestFunc(int kind, char **id, int a2, int a3, int a4);
extern void scpFadeIn(float f);
extern void fightSoundProcessRequestPause(void);
extern int fightSoundPlayChk(void);
extern int scpAdpcmPlayRequestNum(void);
extern void shadow_DispCancel(int a0, int a1);
extern int RequestStageChange(int no, char *g, int flag, float speed, float wait);
void actDejaDemo(volatile int a0);
extern int stage_no;

/* the 0x194-byte per-stage record; the demo reads its next-stage index at
   0xA0.  The record is 4-byte aligned (its padding is spelled `int` for that
   reason): with a 2-byte alignment gcc folds the 0xA0 into the array base
   before the index add, which reverses which of the two values ends up in
   $a1 and which in $a2. */
typedef struct {
    int pad000[0x28];
    short nextStage; /* 0xA0 */
    char pad0A2[0xF2];
} StageRec;

/* the 0x28-byte stage-manager table entry */
typedef struct {
    char pad00[0x24];
    int preload; /* 0x24 */
} StgEntry;

/* Both tables are in the ELF's .rodata run (0x54D380..0x638A98), so `const`
   is what they are.  It is also load-bearing on D_005F5D50: only a reference
   rooted at a const object makes the `nextStage` load unchanging, and only
   then is it free of the `volatile int a0` parameter home's memory
   dependence, which is what lets the home store issue two slots later. */
extern const StageRec D_005F5D50[];
extern const StgEntry D_0055C518[];
extern void stgmgrNextStagePreLoadForceStageSet(int val);
extern int stage_ContinueAnimation(int a0, int a1);
extern int stage_CheckAnimationFrame(int a0, int a1, int a2);
extern ActMail D_004F79A8[];
void actDejaAfterChk(volatile int a0);
extern char *D_0063BDF0;
extern void CheckPoint(void);
extern void gflagOn(int flag);
extern void scpPlayStart(int a0);
extern int stage_CheckAnimationFinish(int anim);
extern void scpPlayMot(char *self, int mot);
extern void *test_CURRENTROOT(void *self);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void scpPlayMotDir(char *self, float *dir);
extern void scpPlayEnd(int a0);
extern int scpAdpcmFadeCloseFunc(char **h, short fade);
extern Vec16 D_006224E0;
/* prototypes: their order is the inline tail's emission order */
void actDeja(volatile int a0);
void actEnemySleep(volatile int a0);

inline void actEnemySleep(volatile int a0)
{
    while (1) {
        scpSleepEnemyAll();
        _ACTWait(1);
    }
}

inline void actDeja(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    if (gflagChk(6) == 0) {
        lt_switch_layout(0x37);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(0x48, 0, 0);
        D_004F7988[0].func = actDejaChk;
        self->mail = D_004F7988;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    }
}

void actDejaChk(volatile int a0)
{
    gflagOn(6);
    *(int *)(scpSearchGobj(0x9F4) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x9F5) + 0x16C) = 0;
    actCreateSubThread(actEnemySleep, 0x15);
    scpAdpcmPlayRequestFunc(0xC, &D_0063BDF0, 0, 1, 1);
    while (D_0063BDF0 == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
    actCreateSubThread(actDejaDemo, 0x15);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    D_0063C4DC = 0;
    while (D_0063C4DC == 0 &&
           ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    if (D_0063C4DC == 0 && D_0063BDF0 != 0) {
        shadow_DispCancel(0x4A, 0);
        scpAdpcmFadeCloseFunc(&D_0063BDF0, 0x80);
        D_0063BDF0 = 0;
    }
    RequestStageChange(1, D_00639EA4, 0, D_0063986C, 1.0f);
}

void actDejaDemo(volatile int a0)
{
    stgmgrNextStagePreLoadForceStageSet(D_0055C518[D_005F5D50[stage_no].nextStage].preload);
    scpPlayStart((int)D_00639EA4);
    stage_SetAnimation(0x260, 1, 0);
    scpPlayMot(D_00639EA4, 0x12A);
    while (stage_ContinueAnimation(0x260, 0x261) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x12B);
    while (stage_ContinueAnimation(0x261, 0x262) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x12C);
    while (stage_ContinueAnimation(0x262, 0x263) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x12D);
    while (stage_ContinueAnimation(0x263, 0x264) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x12E);
    _ACTWait(1);
    stage_SetAnimation(0x26B, 1, 0);
    while (stage_CheckAnimationFrame(0x264, 0x78, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(0x36) + 0x16C) = 0;
    while (stage_ContinueAnimation(0x264, 0x265) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(0x26B, -1, -2);
    stage_SetAnimation(0x26C, 1, 0);
    while (stage_ContinueAnimation(0x265, 0x266) == 0) {
        _ACTWait(1);
    }
    scpPlayMot((char *)scpSearchGobj(0x9F4), 0x2D4);
    *(int *)(scpSearchGobj(0x9F4) + 0x16C) = 1;
    _ACTWait(1);
    stage_SetAnimation(0x26C, -1, -2);
    stage_SetAnimation(0x26D, 1, 0);
    shadow_DispCancel(0x4A, 1);
    while (stage_ContinueAnimation(0x266, 0x267) == 0) {
        _ACTWait(1);
    }
    *(int *)(scpSearchGobj(0x36) + 0x16C) = 1;
    scpPlayMot(D_00639EA4, 0x12F);
    _ACTWait(1);
    stage_SetAnimation(0x26D, -1, -2);
    while (stage_ContinueAnimation(0x267, 0x268) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x130);
    scpPlayMot((char *)scpSearchGobj(0x9F4), 0x2D5);
    _ACTWait(1);
    stage_SetAnimation(0x26E, 1, 0);
    while (stage_ContinueAnimation(0x268, 0x269) == 0) {
        _ACTWait(1);
    }
    *(int *)(scpSearchGobj(0x9F5) + 0x16C) = 1;
    scpPlayMot(D_00639EA4, 0x131);
    scpPlayStart(scpSearchGobj(0x9F5));
    scpPlayMot((char *)scpSearchGobj(0x9F5), 0x3C2);
    _ACTWait(1);
    stage_SetAnimation(0x26E, -1, -2);
    stage_SetAnimation(0x26F, 1, 0);
    while (stage_ContinueAnimation(0x269, 0x26A) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 0x132);
    scpPlayMot((char *)scpSearchGobj(0x9F5), 0x3C3);
    shadow_DispCancel(0x4A, 0);
    while (stage_CheckAnimationFrame(0x26A, 0x7D, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0063C4DC = 1;
}

void actDejaAfter(volatile int a0)
{
    int x = a0;
    Act *self = actInitialize(a0);
    _ACTWait(1);

    ScpCallCameraOff();
    if (gflagChk(7) == 0 && gflagChk(6) != 0) {
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, -1);
        stage_SetAnimation(0x23, 0, 0);
        stage_SetAnimation(0x21, 0, 0);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
        D_004F79A8[0].func = actDejaAfterChk;
        self->mail = D_004F79A8;
        ACTSendMailCorrect(a0, 0x1AE);
        _ACTWait(0);
    } else {
        stage_SetAnimation(0x20, 0, -1);
        stage_SetAnimation(0x1A, 0, -1);
        stage_SetAnimation(0x23, 0, 0);
        stage_SetAnimation(0x21, 0, 0);
        stage_SetAnimation(0x24, 0, 0);
        stage_SetAnimation(0x26, 0, 0);
    }
}

void actDejaAfterChk(volatile int a0)
{
    Vec16 target;
    Vec16 dir;

    CheckPoint();
    gflagOn(7);
    lt_switch_layout(0x37);
    D_0063AA08 = 1;
    scpPlayStart((int)D_00639EA4);
    stage_SetAnimation(0x270, 1, 0);
    scpPlayMot(D_00639EA4, 0x133);
    while (stage_CheckAnimationFinish(0x270) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(D_00639EA4, 0);
    target = D_006224E0;
    sceVu0SubVector(dir.f, target.f, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir.f);
    scpPlayEnd((int)D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    _ACTWait(0x3C);
    if (D_0063BDF0 != 0) {
        scpAdpcmFadeCloseFunc(&D_0063BDF0, 0x50);
    }
    D_0063BDF0 = 0;
    _ACTWait(0);
}
