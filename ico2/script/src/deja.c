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
        lt_switch_layout(55);
        D_0063AA08 = 1;
        scpFadeOut(255.0f, 0, 0, 0);
        stage_SetAnimation(72, 0, 0);
        _mes[0].func = actDejaChk;
        self->mail = _mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    }
}

void actDejaChk(volatile int a0)
{
    gflagOn(6);
    *(int *)(scpSearchGobj(2548) + 0x16C) = 0;
    *(int *)(scpSearchGobj(2549) + 0x16C) = 0;
    actCreateSubThread(actEnemySleep, 21);
    scpAdpcmPlayRequestFunc(12, &deja, 0, 1, 1);
    while (deja == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
    actCreateSubThread(actDejaDemo, 21);
    fightSoundProcessRequestPause();
    while (fightSoundPlayChk() != 0) {
        _ACTWait(1);
    }
    demoEnd = 0;
    while (demoEnd == 0 && ((D_0028F8F0[0].flags & 0x800) == 0 || scpAdpcmPlayRequestNum() != 0)) {
        _ACTWait(1);
    }
    if (demoEnd == 0 && deja != 0) {
        shadow_DispCancel(74, 0);
        scpAdpcmFadeCloseFunc(&deja, 0x80);
        deja = 0;
    }
    RequestStageChange(1, D_00639EA4, 0, 0.025f, 1.0f);
}

void actDejaDemo(volatile int a0)
{
    stgmgrNextStagePreLoadForceStageSet(D_0055C518[D_005F5D50[stage_no].nextStage].preload);
    scpPlayStart((int)D_00639EA4);
    stage_SetAnimation(608, 1, 0);
    scpPlayMot(D_00639EA4, 298);
    while (stage_ContinueAnimation(608, 609) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 299);
    while (stage_ContinueAnimation(609, 610) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 300);
    while (stage_ContinueAnimation(610, 611) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 301);
    while (stage_ContinueAnimation(611, 612) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 302);
    _ACTWait(1);
    stage_SetAnimation(619, 1, 0);
    while (stage_CheckAnimationFrame(612, 120, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    *(int *)(scpSearchGobj(54) + 0x16C) = 0;
    while (stage_ContinueAnimation(612, 613) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    stage_SetAnimation(619, -1, -2);
    stage_SetAnimation(620, 1, 0);
    while (stage_ContinueAnimation(613, 614) == 0) {
        _ACTWait(1);
    }
    scpPlayMot((char *)scpSearchGobj(2548), 724);
    *(int *)(scpSearchGobj(2548) + 0x16C) = 1;
    _ACTWait(1);
    stage_SetAnimation(620, -1, -2);
    stage_SetAnimation(621, 1, 0);
    shadow_DispCancel(74, 1);
    while (stage_ContinueAnimation(614, 615) == 0) {
        _ACTWait(1);
    }
    *(int *)(scpSearchGobj(54) + 0x16C) = 1;
    scpPlayMot(D_00639EA4, 303);
    _ACTWait(1);
    stage_SetAnimation(621, -1, -2);
    while (stage_ContinueAnimation(615, 616) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 304);
    scpPlayMot((char *)scpSearchGobj(2548), 725);
    _ACTWait(1);
    stage_SetAnimation(622, 1, 0);
    while (stage_ContinueAnimation(616, 617) == 0) {
        _ACTWait(1);
    }
    *(int *)(scpSearchGobj(2549) + 0x16C) = 1;
    scpPlayMot(D_00639EA4, 305);
    scpPlayStart(scpSearchGobj(2549));
    scpPlayMot((char *)scpSearchGobj(2549), 962);
    _ACTWait(1);
    stage_SetAnimation(622, -1, -2);
    stage_SetAnimation(623, 1, 0);
    while (stage_ContinueAnimation(617, 618) == 0) {
        _ACTWait(1);
    }
    scpPlayMot(D_00639EA4, 306);
    scpPlayMot((char *)scpSearchGobj(2549), 963);
    shadow_DispCancel(74, 0);
    while (stage_CheckAnimationFrame(618, 125, 0) == 0) {
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
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
        after_mes[0].func = actDejaAfterChk;
        self->mail = after_mes;
        ACTSendMailCorrect(a0, 430);
        _ACTWait(0);
    } else {
        stage_SetAnimation(32, 0, -1);
        stage_SetAnimation(26, 0, -1);
        stage_SetAnimation(35, 0, 0);
        stage_SetAnimation(33, 0, 0);
        stage_SetAnimation(36, 0, 0);
        stage_SetAnimation(38, 0, 0);
    }
}

void actDejaAfterChk(volatile int a0)
{
    Vec16 target;
    Vec16 dir;

    CheckPoint();
    gflagOn(7);
    lt_switch_layout(55);
    D_0063AA08 = 1;
    scpPlayStart((int)D_00639EA4);
    stage_SetAnimation(624, 1, 0);
    scpPlayMot(D_00639EA4, 307);
    while (stage_CheckAnimationFinish(624) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpPlayMot(D_00639EA4, 0);
    target = afterChkPos;
    sceVu0SubVector(dir.f, target.f, test_CURRENTROOT(D_00639EA4));
    scpPlayMotDir(D_00639EA4, dir.f);
    scpPlayEnd((int)D_00639EA4);
    D_0063AA08 = 0;
    lt_switch_layout(54);
    _ACTWait(60);
    if (deja != 0) {
        scpAdpcmFadeCloseFunc(&deja, 0x50);
    }
    deja = 0;
    _ACTWait(0);
}
