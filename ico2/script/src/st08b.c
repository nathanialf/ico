#include "st08b.h"
#include "layout_texture.h"
#include "pad.h"
#include "thread.h"
#include "s_init.h"
#include "act.h"
#include "gobj_process.h"
#include "commonact.h"
#include "generator.h"
#include "gflag.h"
#include "StageAnimation.h"
#include "cage.h"
#include "geometryManager.h"
#include "item.h"
#include "typedef.h"
#include "main.h"
#include "script.h"
#include "include_asm.h"

static ActMail kurenMain_mes[2] = {{406, actSt08bKurenSwitch}, {429}}; /* derived name */

static ActMail kuren_mes[2] = {{430}, {429}}; /* derived name */

static ActMail kurenSwitch_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDown_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorUp_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorUpChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail doorDownChk_mes[2] = {{430}, {429}}; /* derived name */

static ActMail ene_mes[2] = {{430}, {429}}; /* derived name */

/* A 16-byte constant vector template: the float view carries the values,
   the long long view is the one the copy reads. */

static const ConstVec kurenSwitchPos = {{248.0f, -2626.0f, 705.0f, 1.0f}}; /* derived name */

static const ConstVec kurenSwitch2Pos = {{280.0f, -3748.0f, 2416.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpChkPos = {{-1319.0f, -2429.0f, -405.0f, 0.0f}}; /* derived name */

static const ConstVec doorUpEffectPos = {{-505.0f, -1200.0f, -5671.0f, 1.0f}}; /* derived name */

static const ConstVec doorUpEffect2Pos = {{-505.0f, -1447.0f, -5671.0f, 1.0f}}; /* derived name */

typedef union Pos { /* field names derived */
    long long ll[2];
    float f[4];
} Pos; /* derived name */

void actSt08bKurenLeft(GObj *volatile self);
void actSt08bKurenRight(GObj *volatile self);
void actSt08bDoorUpChk(GObj *volatile self);
void actSt08bDoorDownChk(GObj *volatile self);

/* .sbss: the demo's own end flag, raised by the subthreads the wait loop below
   spins for. */
static int demoEnd;

INCLUDE_ASM(actSt08bKurenSwitch);

INCLUDE_ASM(actSt08bKurenLeft);

INCLUDE_ASM(actSt08bKurenRight);

INCLUDE_ASM(actSt08bDoor);

INCLUDE_ASM(actSt08bDoorUpChk);

INCLUDE_ASM(actSt08bDoorDownChk);

INCLUDE_ASM(actSt08bKuren);

INCLUDE_ASM(actSt08bEne);

INCLUDE_ASM(actSt08bEnemy1);

INCLUDE_ASM(actSt08bEnemy2);

INCLUDE_ASM(actSt08bKurenMain);

INCLUDE_ASM(actSt08aGirlYoro);

INCLUDE_ASM(actSt08bDoorEvent);

INCLUDE_ASM(actSt08bDoorUpEffect);

INCLUDE_ASM(actSt08bDoorDownEffect);

INCLUDE_ASM(actSt08bEneChk);
