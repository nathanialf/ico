#include "debug.h"
#include "enemy_act.h"
#include "itou_boss.h"
#include "camera-root.h"
#include "ebrain.h"
#include "gflag.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include <string.h>
#include "warpGirl.h"
/* header prototypes (order fixes the inline tail) */
#include "backStage.h"
#include <libvu0.h>
#include <stdlib.h>
#include "boyact.h"
#include "geometryManager.h"
#include "layout_texture.h"
#include "Matrix.h"
#include "gobj.h"
#include "way_kidnap.h"
#include "main.h"
#include "gamesys.h"
#include "include_asm.h"

/* the enemy the heroine is carried off by */
GObj *backStageGirlTargetEnemyGop = 0;

/* .sbss: the off-stage kidnap state, in the order backStageSave writes it to
   the memory card. */
static int kidnapState; /* derived name */ /* 0 idle, 1 counting down to the grab, 2 carrying */

static int kidnapTime; /* derived name */ /* frames left before the heroine is taken */

static int carryTime; /* derived name */ /* frames left before the nest is reached */

/* index of the carrier in the gamesys object-info table */
static int kidnapObjIdx; /* derived name */

static float enemyDist; /* derived name */ /* distance from the heroine to the nearest enemy */

static float nestDist; /* derived name */ /* route length from the carrier to the nest */

static float enemySec; /* derived name */ /* enemyDist scaled to seconds */

static float nestSec; /* derived name */ /* nestDist scaled to seconds */

/* the boy has already been told the heroine is in trouble */
static int pinchTold; /* derived name */

/* generator.h, which this TU does not include, declares both with a
   short *; this TU passes the int * work words of a GamesysObjInfo */
extern void SetInfoSpKidnapGenerator(int *info);
extern void SetInfoSpKidnapEnemy(int *work);

inline void backStageProcessInit(void)
{
    backStageGirlTargetEnemyGop = 0;
    kidnapObjIdx = -1;
    kidnapState = 0;
    pinchTold = 0;
}

INCLUDE_ASM(backStageProcessOutStage);

INCLUDE_ASM(backStageProcessMain);

INCLUDE_ASM(routeSetPos);

/* inlined at both of its call sites */
static inline void kidnapWarpToWaypoint(GObj *gobj, float range) /* derived name */
{
    Vec16 p;
    Vec16 wp;
    int n;
    int k;

    GetRootPosition(p.f, gobj);
    WayPointWithRangeFromPos(p.f, range, 0);
    n = NumOfWpPos();
    if (n == 0) {
        return;
    }
    k = (n * (rand() & 0xFFFF)) >> 16;
    CopyWpPos(&wp.f, k, k);
    wp.f[1] = wp.f[1] - GOBJ_SUB(gobj)->skel->pos[1];
    SetDirectRootPosition(gobj, wp.f);
}

INCLUDE_ASM(backStageProcessInStage);

void backStageSave(GamesysMemCursor *h)
{
    gamesysMemoryHandlerWrite(h, &backStageGirlTargetEnemyGop, 4);
    gamesysMemoryHandlerWrite(h, &kidnapState, 4);
    gamesysMemoryHandlerWrite(h, &kidnapTime, 4);
    gamesysMemoryHandlerWrite(h, &carryTime, 4);
    gamesysMemoryHandlerWrite(h, &kidnapObjIdx, 4);
    gamesysMemoryHandlerWrite(h, &enemyDist, 4);
    gamesysMemoryHandlerWrite(h, &nestDist, 4);
    gamesysMemoryHandlerWrite(h, &enemySec, 4);
    gamesysMemoryHandlerWrite(h, &nestSec, 4);
}

void backStageLoad(GamesysMemCursor *h)
{
    gamesysMemoryHandlerRead(h, &backStageGirlTargetEnemyGop, 4);
    gamesysMemoryHandlerRead(h, &kidnapState, 4);
    gamesysMemoryHandlerRead(h, &kidnapTime, 4);
    gamesysMemoryHandlerRead(h, &carryTime, 4);
    gamesysMemoryHandlerRead(h, &kidnapObjIdx, 4);
    gamesysMemoryHandlerRead(h, &enemyDist, 4);
    gamesysMemoryHandlerRead(h, &nestDist, 4);
    gamesysMemoryHandlerRead(h, &enemySec, 4);
    gamesysMemoryHandlerRead(h, &nestSec, 4);
}

inline void backStageTsuresariReturn(void) {}
