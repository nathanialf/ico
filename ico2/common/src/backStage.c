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

void backStageProcessMain(void)
{
    gamesysAnotherStageTsuresari = 0;
    if (gflagChk(340) != 0) {
        return;
    }
    if (current_layout_id != 50) {
        return;
    }
    if (stage_no == gameSysObjInfo[1].stage) {
        return;
    }
    switch (kidnapState) {
    case 1:
        debug_PrintfDummy(350, 100, 0xFFFF00FF, "TSUKAMARI TIME %d",
                          kidnapTime / ((60 - systemStatus[0] * 10) / systemStatus[1]));
        if (kidnapTime-- < 0) {
            GamesysObjInfo *s = &gameSysObjInfo[kidnapObjIdx];

            kidnapState = 2;
            sceVu0CopyVector(s->pos, gameSysObjInfo[1].pos);
            s->work[0] = 4;
        }
        break;
    case 2:
        debug_PrintfDummy(350, 100, 0xFF000000, "TSURESARI %d",
                          carryTime / ((60 - systemStatus[0] * 10) / systemStatus[1]));
        gamesysAnotherStageTsuresari = 1;
        if (carryTime-- < 0) {
            int st = gameSysObjInfo[1].stage;

            if (gflagChk(342) == 0) {
                gflagOn(342);
                RequestStageChangeKidnapEnd(
                    st, eBrainGetTargetGeneratorFromLabel(gameSysObjInfo[kidnapObjIdx].no));
            }
        }
        break;
    }
}

static void routeSetPos(GObj *gobj0, GObj *gobj1, float *out, float ratio)
{
    Vec16 p0;
    Vec16 cur;
    Vec16 prev;
    Vec16 d;
    float len;
    float target;
    float sum;
    int i;
    int n;

    len = WayLengthOfGObj_GObj(gobj0, gobj1);
    GetRootPosition(p0.f, gobj0);
    n = NumOfWpPos();
    if (n != 0) {
        sum = 0.0f;
        memset(&prev, 0, sizeof(prev));
        target = len * ratio;
        for (i = 0; i < n; i++) {
            CopyWpPos(&cur.f, i, i);
            if (i == 0) {
                sum = 0.0f;
            } else {
                sceVu0SubVector(d.f, prev.f, cur.f);
                sum += FSqrt(_InnerProduct(d.f, d.f));
            }
            if (target < sum) {
                break;
            }
            sceVu0CopyVector(prev.f, cur.f);
        }
        if (i != 0) {
            i--;
        }
        CopyWpPos(&cur.f, i, i);
        sceVu0CopyVector(out, cur.f);
    } else {
        sceVu0CopyVector(out, p0.f);
    }
}

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

void backStageProcessInStage(float arg)
{
    float range;
    float limit;
    float rest;
    GObj *gobj;
    GObj *t;

    range = (float)((unsigned int)(gamesysTimeCount - gamesysStageExitTime[stage_no]) /
                    ((60 - systemStatus[0] * 10) / systemStatus[1])) *
            40.0f;
    if (arg != 0.0f) {
        range = arg;
        debug_StdPrintfDummy("%d\n", (int)(*(long long *)&gameSysObjInfo[1] >> 1) & 1);
    } else {
        if (gamesysStageExitTime[stage_no] == 0) {
            return;
        }
        if (gflagChk(340) != 0) {
            return;
        }
    }
    limit = 10000000.0f;
    if (limit < range) {
        range = limit;
    }
    if (backStageGirlTargetEnemyGop == 0 && IsGirlEscortedInCurrentStage() == 0 &&
        gflagChk(343) == 0 && gameSysObjInfo[1].stage == stage_no) {
        kidnapWarpToWaypoint(girlGObj, range);
    }
    gobj = isysGObjSearchFromObjKindID_begin(4);
    while (gobj != 0) {
        if (isEnemyKidnapEnable(gobj) != 0) {
            if (backStageGirlTargetEnemyGop != gobj) {
                kidnapWarpToWaypoint(gobj, range);
            } else {
                t = isysGObjSearchFromObjLayoutID(eBrainGetTargetGeneratorFromLabel(gobj->labelId));
                if (t != 0) {
                    Vec16 pos;
                    float ratio;

                    ratio = (float)carryTime /
                            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 100.0f;
                    rest = nestDist - ratio;
                    if (rest < 0.0f) {
                        rest = nestDist;
                    }
                    routeSetPos(backStageGirlTargetEnemyGop, t, pos.f, rest / nestDist);
                    pos.f[1] = pos.f[1] - GOBJ_SUB(backStageGirlTargetEnemyGop)->skel->pos[1];
                    SetDirectRootPosition(backStageGirlTargetEnemyGop, pos.f);
                }
            }
        }
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}

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
