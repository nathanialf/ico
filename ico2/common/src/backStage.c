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

/* the enemy the heroine is carried off by */
int backStageGirlTargetEnemyGop = 0;

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

/* as in gamesys.h, which this TU does not include */
extern void gamesysMemoryHandlerWrite(int *self, void *src, int size);
/* as in gamesys.h, which this TU does not include */
extern void gamesysMemoryHandlerRead(int *self, void *dst, int size);

/* the boy has already been told the heroine is in trouble */
static int pinchTold; /* derived name */

/* --- su-b sweep decls --- */

/* the 0x40-byte gamesys object-info record (src/gamesys.c GamesysObjInfoBackstage) */
typedef struct {
    short flag;           /* 0x00 */
    unsigned short no;    /* 0x02 */
    unsigned short stage; /* 0x04 */
    short pad06;          /* 0x06 */
    int time;             /* 0x08 */
    int uniq;             /* 0x0C */
    Vec16 pos;            /* 0x10 */
    Vec16 rot;            /* 0x20 */
    int work[4];          /* 0x30 */
} GamesysObjInfoBackstage;

/* typedef.h carries StgPre but declares no stageData */
extern const StgPre stageData[];

/* the actor work record a gobj carries at 0x164 (src/enemy_act.c reads the same
   0x444 member off the same 0x164 pointer) */
typedef struct {
    char pad000[1092];
    int objNo; /* 0x444 */
} ActorWorkRec;

/* gamesys.c's object-info records, read here as GamesysObjInfoBackstage;
   gamesys.h, which this TU does not include, declares GamesysObjInfo [] */
extern GamesysObjInfoBackstage gameSysObjInfo[];
/* as in gamesys.h */
extern GenGeo objLayout[];

/* .bss: the nest position the carrier walks to */
static float nestPos[4]; /* derived name */

/* as in gamesys.h, which this TU does not include */
extern int gamesysAnotherStageTsuresari;

/* the carrier walks the waypoint route instead of a generator */
static int wayKidnap; /* derived name */

/* as in gamesys.h, which this TU does not include */
extern GamesysObjInfo *gamesysObjInfoPosNewStageSet(int no, int kind, int stage, float *pos,
                                                    float *rot);
/* as in generator.h, which this TU does not include */
extern void SetInfoSpKidnapGenerator(short *a0);
/* this TU passes an int *; generator.h declares a short * */
extern void SetInfoSpKidnapEnemy(int *work);
/* as in gamesys.h, which this TU does not include */
extern int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3);
/* as in gamesys.h, which this TU does not include */
extern void gamesysObjInfoCls(int kind, int no);
/* as in gamesys.h, which this TU does not include */
extern int gamesysStageExitTime[];
/* read here as unsigned; gamesys.h declares an int */
extern unsigned int gamesysTimeCount;

inline void backStageProcessInit(void)
{
    backStageGirlTargetEnemyGop = 0;
    kidnapObjIdx = -1;
    kidnapState = 0;
    pinchTold = 0;
}

inline void backStageDebugTimeZero(void)
{
    kidnapTime = 0;
}

void backStageProcessOutStage(void)
{
    Vec16 a;
    Vec16 b;
    int done;
    int i;
    int gen;
    void *p;
    char *o;

    done = 0;
    if (gflagChk(394) != 0) {
        kidnapState = 0;
        done = 1;
    }
    if (gameSysObjInfo[1].stage == stage_no && done == 0) {
        debug_StdPrintfDummy("girl nokori");
        pinchTold = 0;
        kidnapObjIdx = -1;
        for (i = 2; i < 22; i++) {
            if (gameSysObjInfo[i].no == 0) {
                continue;
            }
            if (gameSysObjInfo[i].stage != stage_no) {
                continue;
            }
            if (gameSysObjInfo[i].work[0] == 4) {
                kidnapObjIdx = i;
                break;
            }
        }
        kidnapState = 0;
        wayKidnap = 0;
        if (kidnapObjIdx < 0) {
            char *e = NearestEnemyFromGirl(&enemyDist);

            if (e != 0) {
                ActorWorkRec *m;

                kidnapState = 1;
                enemySec = enemyDist / 160.0f;
                kidnapTime =
                    (int)(enemySec * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
                m = *(ActorWorkRec **)(e + 0x164);
                kidnapObjIdx = (unsigned int)((char *)gamesysObjInfoPosSetStage((int *)e, m->objNo,
                                                                                0, stage_no) -
                                              (char *)gameSysObjInfo) >>
                               6;
            }
        } else {
            kidnapState = 2;
            pinchTold = 1;
        }
        if (kidnapState == 1 || kidnapState == 2) {
            gen = eBrainGetTargetGeneratorFromLabel(gameSysObjInfo[kidnapObjIdx].no);
            p = isysGObjSearchFromObjLayoutID(gen);
            if (p == 0) {
                kidnapState = 0;
            } else {
                GetRootPosition(a.f, p);
                GetRootPosition(b.f, girlGObj);
                nestDist = WayLengthOfPos_Pos(a.f, b.f);
                nestSec = nestDist / 100.0f;
                carryTime = (int)(nestSec * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
            }
        } else if (stageData[stage_no].kidnapSeconds != 0) {
            GetRootProjectionPosOfGObj(a.f, girlGObj);
            wayKidnap = 1;
            kidnapState = 1;
            enemySec = (float)stageData[stage_no].kidnapSeconds;
            kidnapTime = (int)(enemySec * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
            if (WayPointWithRangeFromPos2(a.f, (char *)GOBJ_ACT(girlGObj) + 0x360, nestPos, 1) ==
                0) {
                /* no ACTIVE connection was found */
                debug_StdPrintfDummy("繋がりACTIVEでみつからなかった");
                if (WayPointWithRangeFromPos2(a.f, (char *)GOBJ_ACT(girlGObj) + 0x360, nestPos,
                                              0) == 0) {
                    /* no connection was found, so the nest is placed at the heroine */
                    debug_StdPrintfDummy("繋がりみつからなかったのでヒロインの位置に巣を配置");
                    sceVu0CopyVector(nestPos, a.f);
                }
            }
            nestDist = WayLengthOfPos_Pos(nestPos, a.f);
            nestSec = nestDist / 100.0f;
            carryTime = (int)(nestSec * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
            if ((float)carryTime < (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f) {
                carryTime = (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 30.0f);
            }
        }
        if ((float)carryTime < (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 10.0f) {
            carryTime = (int)((float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 10.0f);
        }
    } else {
        o = isysGObjSearchFromObjKindID_begin(4);
        while (o != 0) {
            if (*(int *)(o + 8) == 0xEAD) {
                gamesysObjInfoCls(4, 0xEAD);
            }
            o = isysGObjSearchFromObjKindID_next(o);
        }
        o = isysGObjSearchFromObjKindID_begin(33);
        while (o != 0) {
            if (*(int *)(o + 8) == 0xEAE) {
                gamesysObjInfoCls(0x21, 0xEAE);
            }
            o = isysGObjSearchFromObjKindID_next(o);
        }
    }
}

void backStageProcessMain(void)
{
    Vec16 pos;
    Vec16 rot;
    Vec16 tmp;
    GamesysObjInfoBackstage *g1;
    GamesysObjInfo *g2;

    gamesysAnotherStageTsuresari = 0;
    if (gflagChk(390) != 0) {
        return;
    }
    if (current_layout_id != 0x36) {
        return;
    }
    if (stage_no == gameSysObjInfo[1].stage) {
        return;
    }
    switch (kidnapState) {
    case 1:
        if (kidnapTime-- < 0) {
            kidnapState = 2;
            if (wayKidnap == 0) {
                GamesysObjInfoBackstage *s = &gameSysObjInfo[kidnapObjIdx];
                sceVu0CopyVector(&s->pos, &gameSysObjInfo[1].pos);
                s->work[0] = 4;
            } else {
                memset(&tmp, 0, sizeof(tmp));
                tmp.f[0] = objLayout[3758].rot[0];
                tmp.f[1] = objLayout[3758].rot[1];
                tmp.f[2] = objLayout[3758].rot[2];
                rot = tmp;
                g1 = gamesysObjInfoPosNewStageSet(0xEAD, 4, gameSysObjInfo[1].stage,
                                                  gameSysObjInfo[1].pos.f, gameSysObjInfo[1].rot.f);
                kidnapObjIdx = (unsigned int)((char *)g1 - (char *)gameSysObjInfo) >> 6;
                pos.f[0] = nestPos[0];
                pos.f[2] = nestPos[2];
                pos.f[1] = nestPos[1] - 10.0f;
                g2 = gamesysObjInfoPosNewStageSet(0xEAE, 0x21, gameSysObjInfo[1].stage, pos.f,
                                                  rot.f);
                SetInfoSpKidnapGenerator(g2->work);
                SetInfoSpKidnapEnemy(g1->work);
                if (g1 != 0 && g2 != 0) {
                    g1->work[0] = 4;
                } else {
                    debug_StdPrintfDummy("backstage timeLimit gamesys area error\n");
                    kidnapState = 1;
                }
            }
        }
        break;
    case 2:
        if (CameraGetMode() != 4) {
            if (pinchTold == 0) {
                SetStatusBoy_OtherStageGirlPinch();
                pinchTold = 1;
            }
            gamesysAnotherStageTsuresari = 1;
            if (carryTime-- < 0) {
                int st = gameSysObjInfo[1].stage;
                RequestStageChangeKidnapEnd(
                    st, eBrainGetTargetGeneratorFromLabel(gameSysObjInfo[kidnapObjIdx].no));
            }
        }
        break;
    }
}

void routeSetPos(int gobj0, int gobj1, float *out, float ratio)
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

    len = WayLengthOfGObj_GObj((void *)gobj0, (void *)gobj1);
    GetRootPosition(p0.f, gobj0);
    if (1.0f <= ratio) {
        GetRootPosition(out, gobj1);
        return;
    }
    n = NumOfWpPos();
    if (n != 0) {
        sum = 0.0f;
        memset(&prev, 0, sizeof(prev));
        target = len * ratio;
        debug_StdPrintfDummy("way num %d\n", n);
        for (i = 0; i < n; i++) {
            CopyWpPos(cur.f, i, i);
            if (i == 0) {
                sum = 0.0f;
            } else {
                sceVu0SubVector(d.f, prev.f, cur.f);
                sum += FSqrt(_InnerProduct(d.f, d.f));
            }
            debug_StdPrintfDummy("%d %d:dist %f calcdist %f\n", i, n, target, sum);
            if (target < sum) {
                break;
            }
            sceVu0CopyVector(prev.f, cur.f);
        }
        if (i != 0) {
            i--;
        }
        CopyWpPos(cur.f, i, i);
        sceVu0CopyVector(out, cur.f);
        debug_StdPrintfDummy("set pos_table %f %f %f\n", out[0], out[1], out[2]);
    } else {
        /* no WAY candidate */
        debug_StdPrintfDummy("WAY候補無し");
        sceVu0CopyVector(out, p0.f);
    }
}

/* inlined at both of its call sites */
static inline void kidnapWarpToWaypoint(int gobj, float range) /* derived name */
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
    CopyWpPos(wp.f, k, k);
    wp.f[1] = wp.f[1] - *(float *)(GOBJ_SUB(gobj)->skel + 0x14);
    SetDirectRootPosition(gobj, wp.f);
}

void backStageProcessInStage(float arg)
{
    float range;
    float limit;
    float rest;
    int gobj;
    int t;

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
        if (gflagChk(390) != 0) {
            return;
        }
    }
    limit = 10000000.0f;
    if (limit < range) {
        range = limit;
    }
    if (backStageGirlTargetEnemyGop == 0 && IsGirlEscortedInCurrentStage() == 0 &&
        gflagChk(394) == 0 && gameSysObjInfo[1].stage == stage_no && warpGirlInStageSet == 0) {
        /* the heroine is not held, so the position is changed at random */
        debug_StdPrintfDummy("ヒロイン捕まっていないのでランダムで位置変更");
        if (gflagChk(391) == 0) {
            kidnapWarpToWaypoint(girlGObj, range);
        }
    }
    gobj = isysGObjSearchFromObjKindID_begin(4);
    while (gobj != 0) {
        if (isEnemyKidnapEnable(gobj) != 0) {
            if (backStageGirlTargetEnemyGop != gobj) {
                /* the heroine is not held */
                debug_StdPrintfDummy("ヒロイン捕まってない");
                if (gflagChk(391) == 0 && InqCapsuleGhostBossStage() == 0) {
                    kidnapWarpToWaypoint(gobj, range);
                }
            } else {
                t = isysGObjSearchFromObjLayoutID(
                    eBrainGetTargetGeneratorFromLabel(*(int *)(gobj + 8)));
                if (t != 0) {
                    Vec16 pos;
                    Vec16 root;
                    float ratio;

                    if (carryTime > 0) {
                        ratio = (float)carryTime /
                                (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 100.0f;
                    } else {
                        ratio = 0.0f;
                    }
                    rest = 0.0f;
                    if (ratio <= nestDist) {
                        rest = nestDist - ratio;
                    }
                    GetRootPosition(root.f, girlGObj);
                    SetDirectRootPosition(backStageGirlTargetEnemyGop, root.f);
                    if (0.0f < nestDist) {
                        routeSetPos(backStageGirlTargetEnemyGop, t, pos.f, rest / nestDist);
                    } else {
                        /* no route to the nest was found, so it is placed at the nest directly */
                        debug_StdPrintfDummy("巣までの経路がみつからないので直接巣に配置");
                        routeSetPos(backStageGirlTargetEnemyGop, t, pos.f, 1.0f);
                    }
                    debug_StdPrintfDummy("set pos %f %f %f\n", pos.f[0], pos.f[1], pos.f[2]);
                    pos.f[1] =
                        pos.f[1] - *(float *)(GOBJ_SUB(backStageGirlTargetEnemyGop)->skel + 0x14);
                    SetDirectRootPosition(backStageGirlTargetEnemyGop, pos.f);
                }
            }
        }
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}

void backStageSave(void *a0)
{
    gamesysMemoryHandlerWrite(a0, &backStageGirlTargetEnemyGop, 4);
    gamesysMemoryHandlerWrite(a0, &kidnapState, 4);
    gamesysMemoryHandlerWrite(a0, &kidnapTime, 4);
    gamesysMemoryHandlerWrite(a0, &carryTime, 4);
    gamesysMemoryHandlerWrite(a0, &kidnapObjIdx, 4);
    gamesysMemoryHandlerWrite(a0, &enemyDist, 4);
    gamesysMemoryHandlerWrite(a0, &nestDist, 4);
    gamesysMemoryHandlerWrite(a0, &enemySec, 4);
    gamesysMemoryHandlerWrite(a0, &nestSec, 4);
}

void backStageLoad(void *a0)
{
    gamesysMemoryHandlerRead(a0, &backStageGirlTargetEnemyGop, 4);
    gamesysMemoryHandlerRead(a0, &kidnapState, 4);
    gamesysMemoryHandlerRead(a0, &kidnapTime, 4);
    gamesysMemoryHandlerRead(a0, &carryTime, 4);
    gamesysMemoryHandlerRead(a0, &kidnapObjIdx, 4);
    gamesysMemoryHandlerRead(a0, &enemyDist, 4);
    gamesysMemoryHandlerRead(a0, &nestDist, 4);
    gamesysMemoryHandlerRead(a0, &enemySec, 4);
    gamesysMemoryHandlerRead(a0, &nestSec, 4);
}

inline void backStageTsuresariReturn(void) {}
