#include "common.h"
#include "deja.h"
#include "StageManager.h"
#include "layout_texture.h"
#include "act.h"
#include "commonact.h"
#include "fightSound.h"
#include "gflag.h"
#include "script.h"
#include "Shadow.h"
#include "StageAnimation.h"
#include <libvu0.h>
#include "typedef.h"

/* PAL listing rows: every instruction of actDeja is attributed to
 * script/src/deja.c lines 170-189 -- no inlined helper bodies.
 *
 * actDejaChk is this TU's own first function (the PAL listing names it
 * actDejaChk, deja.c:196); actDeja installs it as the actor's next mail
 * handler.  _mes is the 2-entry mail table that lives in the shared
 * src/cod .data carve, so it stays extern here. */
extern int D_0063AA08;

static ActMail _mes[2] = {{430}, {429}};

static ActMail after_mes[2] = {{430}, {429}};

/* --- su-b sweep decls --- */

extern char *D_00639EA4;
extern PadState D_0028F8F0[];

/* .sbss, owned by deja.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the demo's own end flag, raised by the handler the wait
   loop below is spinning for. */
static int demoEnd;

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
void actDejaAfterChk(volatile int a0);
extern char *deja;

static const Vec16 afterChkPos = {{-1000.0f, 0.0f, -2200.0f, 1.0f}};

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
        _mes[0].func = actDejaChk;
        self->mail = _mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actDejaChk(volatile int a0)
{
    gflagOn(6);
    *(int *)(scpSearchGobj(0x9F4) + 0x16C) = 0;
    *(int *)(scpSearchGobj(0x9F5) + 0x16C) = 0;
    actCreateSubThread(actEnemySleep, 0x15);
    scpAdpcmPlayRequestFunc(0xC, &deja, 0, 1, 1);
    while (deja == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
    actCreateSubThread(actDejaDemo, 0x15);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    if (demoEnd == 0 && deja != 0) {
        shadow_DispCancel(0x4A, 0);
        scpAdpcmFadeCloseFunc(&deja, 0x80);
        deja = 0;
    }
    RequestStageChange(1, D_00639EA4, 0, 0.025f, 1.0f);
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
    demoEnd = 1;
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
        after_mes[0].func = actDejaAfterChk;
        self->mail = after_mes;
        ACTSendMailCorrect(a0, 430);
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
    target = afterChkPos;
    sceVu0SubVector(dir.f, target.f, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir.f);
    scpPlayEnd((int)D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(0x36);
    _ACTWait(0x3C);
    if (deja != 0) {
        scpAdpcmFadeCloseFunc(&deja, 0x50);
    }
    deja = 0;
    _ACTWait(0);
}
