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

#ifndef VERSION_JUN26
/* .bss: the nest position the carrier walks to */
static float nestPos[4]; /* derived name */

/* the carrier walks the waypoint route instead of a generator */
static int wayKidnap; /* derived name */
#endif

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

#ifndef VERSION_JUN26
inline void backStageDebugTimeZero(void)
{
    kidnapTime = 0;
}
#endif

#ifdef VERSION_NTSC
void backStageProcessOutStage(void)
{
    Vec16 a;
    Vec16 b;
    int done;
    int i;
    int gen;
    void *p;
    GObj *o;

    done = 0;
    if (gflagChk(361) != 0) {
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
            GObj *e = NearestEnemyFromGirl(&enemyDist);

            if (e != 0) {
                Act *m;

                kidnapState = 1;
                enemySec = enemyDist / 160.0f;
                kidnapTime =
                    (int)(enemySec * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
                m = GOBJ_ACT(e);
                kidnapObjIdx =
                    (unsigned int)((char *)gamesysObjInfoPosSetStage(e, m->infoPos, 0, stage_no) -
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
            if (WayPointWithRangeFromPos2(a.f, &GOBJ_ACT(girlGObj)->way, nestPos, 1) == 0) {
                /* no ACTIVE connection was found */
                debug_StdPrintfDummy("繋がりACTIVEでみつからなかった");
                if (WayPointWithRangeFromPos2(a.f, &GOBJ_ACT(girlGObj)->way, nestPos, 0) == 0) {
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
            if (o->labelId == 3453) {
                gamesysObjInfoCls(4, 3453);
            }
            o = isysGObjSearchFromObjKindID_next(o);
        }
        o = isysGObjSearchFromObjKindID_begin(33);
        while (o != 0) {
            if (o->labelId == 3454) {
                gamesysObjInfoCls(33, 3454);
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
    GamesysObjInfo *g1;
    GamesysObjInfo *g2;

    gamesysAnotherStageTsuresari = 0;
    if (gflagChk(357) != 0) {
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
        if (kidnapTime-- < 0) {
            kidnapState = 2;
            if (wayKidnap == 0) {
                GamesysObjInfo *s = &gameSysObjInfo[kidnapObjIdx];
                sceVu0CopyVector(s->pos, gameSysObjInfo[1].pos);
                s->work[0] = 4;
            } else {
                memset(&tmp, 0, sizeof(tmp));
                tmp.f[0] = objLayout[3454].rot[0];
                tmp.f[1] = objLayout[3454].rot[1];
                tmp.f[2] = objLayout[3454].rot[2];
                rot = tmp;
                g1 = gamesysObjInfoPosNewStageSet(3453, 4, gameSysObjInfo[1].stage,
                                                  gameSysObjInfo[1].pos, gameSysObjInfo[1].rot);
                kidnapObjIdx = (unsigned int)((char *)g1 - (char *)gameSysObjInfo) >> 6;
                pos.f[0] = nestPos[0];
                pos.f[2] = nestPos[2];
                pos.f[1] = nestPos[1] - 10.0f;
                g2 = gamesysObjInfoPosNewStageSet(3454, 33, gameSysObjInfo[1].stage, pos.f, rot.f);
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
#else
void backStageProcessOutStage(void)
{
    Vec16 a;
    Vec16 b;
#if !defined(VERSION_AUG6) && !defined(VERSION_JUN26)
    int done;
#endif
    int i;
    int gen;
    void *p;
#ifdef VERSION_JUN26
    GamesysObjInfo *g;

    if (gflagChk(343) != 0) {
        return;
    }
    if (gameSysObjInfo[1].stage == stage_no) {
#else
    GObj *o;

#ifdef VERSION_AUG6
    if (gflagChk(360) != 0) {
        kidnapState = 0;
        return;
    }
    if (gameSysObjInfo[1].stage == stage_no) {
#else
    done = 0;
    if (gflagChk(394) != 0) {
        kidnapState = 0;
        done = 1;
    }
    if (gameSysObjInfo[1].stage == stage_no && done == 0) {
#endif
#endif
        debug_StdPrintfDummy("girl nokori");
        pinchTold = 0;
        kidnapObjIdx = -1;
        for (i = 2; i < 22; i++) {
#ifdef VERSION_JUN26
            g = gameSysObjInfo;
            if (g[i].no == 0) {
                continue;
            }
            if (g[i].work[0] == 4) {
#else
            if (gameSysObjInfo[i].no == 0) {
                continue;
            }
            if (gameSysObjInfo[i].stage != stage_no) {
                continue;
            }
            if (gameSysObjInfo[i].work[0] == 4) {
#endif
                kidnapObjIdx = i;
                break;
            }
        }
        kidnapState = 0;
#ifndef VERSION_JUN26
        wayKidnap = 0;
#endif
        if (kidnapObjIdx < 0) {
            GObj *e = NearestEnemyFromGirl(&enemyDist);

            if (e != 0) {
                Act *m;

                kidnapState = 1;
                enemySec = enemyDist / 160.0f;
                kidnapTime =
                    (int)(enemySec * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
                m = GOBJ_ACT(e);
                kidnapObjIdx =
                    (unsigned int)((char *)gamesysObjInfoPosSetStage(e, m->infoPos, 0, stage_no) -
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
#ifndef VERSION_JUN26
        } else if (stageData[stage_no].kidnapSeconds != 0) {
            GetRootProjectionPosOfGObj(a.f, girlGObj);
            wayKidnap = 1;
            kidnapState = 1;
            enemySec = (float)stageData[stage_no].kidnapSeconds;
            kidnapTime = (int)(enemySec * (float)((60 - systemStatus[0] * 10) / systemStatus[1]));
            if (WayPointWithRangeFromPos2(a.f, &GOBJ_ACT(girlGObj)->way, nestPos, 1) == 0) {
                /* no ACTIVE connection was found */
                debug_StdPrintfDummy("繋がりACTIVEでみつからなかった");
                if (WayPointWithRangeFromPos2(a.f, &GOBJ_ACT(girlGObj)->way, nestPos, 0) == 0) {
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
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            if (o->labelId == 3734) {
                gamesysObjInfoCls(4, 3734);
#else
#ifdef VERSION_AUG6
            if (o->labelId == 3415) {
                gamesysObjInfoCls(4, 3415);
#else
            if (o->labelId == 3757) {
                gamesysObjInfoCls(4, 3757);
#endif
#endif
            }
            o = isysGObjSearchFromObjKindID_next(o);
        }
        o = isysGObjSearchFromObjKindID_begin(33);
        while (o != 0) {
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
            if (o->labelId == 3735) {
                gamesysObjInfoCls(33, 3735);
#else
#ifdef VERSION_AUG6
            if (o->labelId == 3416) {
                gamesysObjInfoCls(33, 3416);
#else
            if (o->labelId == 3758) {
                gamesysObjInfoCls(33, 3758);
#endif
#endif
            }
            o = isysGObjSearchFromObjKindID_next(o);
#endif
        }
    }
}

void backStageProcessMain(void)
{
#ifdef VERSION_JUN26
    gamesysAnotherStageTsuresari = 0;
    if (gflagChk(340) != 0) {
        return;
    }
    if (current_layout_id != 50) {
#else
    Vec16 pos;
    Vec16 rot;
    Vec16 tmp;
    GamesysObjInfo *g1;
    GamesysObjInfo *g2;

    gamesysAnotherStageTsuresari = 0;
#ifdef VERSION_AUG6
    if (gflagChk(356) != 0) {
        return;
    }
    if (current_layout_id != 50) {
#else
    if (gflagChk(390) != 0) {
        return;
    }
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
    if (current_layout_id != 51) {
#else
    if (current_layout_id != 54) {
#endif
#endif
#endif
        return;
    }
    if (stage_no == gameSysObjInfo[1].stage) {
        return;
    }
    switch (kidnapState) {
    case 1:
#ifdef VERSION_JUN26
        debug_PrintfDummy(350, 100, 0xFFFF00FF, "TSUKAMARI TIME %d",
                          kidnapTime / ((60 - systemStatus[0] * 10) / systemStatus[1]));
        if (kidnapTime-- < 0) {
            GamesysObjInfo *s = &gameSysObjInfo[kidnapObjIdx];

            kidnapState = 2;
            sceVu0CopyVector(s->pos, gameSysObjInfo[1].pos);
            s->work[0] = 4;
#else
        if (kidnapTime-- < 0) {
            kidnapState = 2;
            if (wayKidnap == 0) {
                GamesysObjInfo *s = &gameSysObjInfo[kidnapObjIdx];
                sceVu0CopyVector(s->pos, gameSysObjInfo[1].pos);
                s->work[0] = 4;
            } else {
                memset(&tmp, 0, sizeof(tmp));
#ifdef VERSION_AUG6
                tmp.f[0] = objLayout[3416].rot[0];
                tmp.f[1] = objLayout[3416].rot[1];
                tmp.f[2] = objLayout[3416].rot[2];
                rot = tmp;
                g1 = gamesysObjInfoPosNewStageSet(3415, 4, gameSysObjInfo[1].stage,
                                                  gameSysObjInfo[1].pos, gameSysObjInfo[1].rot);
#else
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                tmp.f[0] = objLayout[3735].rot[0];
                tmp.f[1] = objLayout[3735].rot[1];
                tmp.f[2] = objLayout[3735].rot[2];
#else
                tmp.f[0] = objLayout[3758].rot[0];
                tmp.f[1] = objLayout[3758].rot[1];
                tmp.f[2] = objLayout[3758].rot[2];
#endif
                rot = tmp;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                g1 = gamesysObjInfoPosNewStageSet(3734, 4, gameSysObjInfo[1].stage,
                                                  gameSysObjInfo[1].pos, gameSysObjInfo[1].rot);
#else
                g1 = gamesysObjInfoPosNewStageSet(0xEAD, 4, gameSysObjInfo[1].stage,
                                                  gameSysObjInfo[1].pos, gameSysObjInfo[1].rot);
#endif
#endif
                kidnapObjIdx = (unsigned int)((char *)g1 - (char *)gameSysObjInfo) >> 6;
                pos.f[0] = nestPos[0];
                pos.f[2] = nestPos[2];
                pos.f[1] = nestPos[1] - 10.0f;
#if defined(VERSION_JPN) || defined(VERSION_KOR) || defined(VERSION_CN)
                g2 = gamesysObjInfoPosNewStageSet(3735, 33, gameSysObjInfo[1].stage, pos.f, rot.f);
#else
#ifdef VERSION_AUG6
                g2 = gamesysObjInfoPosNewStageSet(3416, 33, gameSysObjInfo[1].stage, pos.f, rot.f);
#else
                g2 = gamesysObjInfoPosNewStageSet(0xEAE, 0x21, gameSysObjInfo[1].stage, pos.f,
                                                  rot.f);
#endif
#endif
                SetInfoSpKidnapGenerator(g2->work);
                SetInfoSpKidnapEnemy(g1->work);
                if (g1 != 0 && g2 != 0) {
                    g1->work[0] = 4;
                } else {
                    debug_StdPrintfDummy("backstage timeLimit gamesys area error\n");
                    kidnapState = 1;
                }
            }
#endif
        }
        break;
    case 2:
#ifdef VERSION_JUN26
        debug_PrintfDummy(350, 100, 0xFF000000, "TSURESARI %d",
                          carryTime / ((60 - systemStatus[0] * 10) / systemStatus[1]));
        gamesysAnotherStageTsuresari = 1;
        if (carryTime-- < 0) {
            int st = gameSysObjInfo[1].stage;

            if (gflagChk(342) == 0) {
                gflagOn(342);
#else
        if (CameraGetMode() != 4) {
            if (pinchTold == 0) {
                SetStatusBoy_OtherStageGirlPinch();
                pinchTold = 1;
            }
            gamesysAnotherStageTsuresari = 1;
            if (carryTime-- < 0) {
                int st = gameSysObjInfo[1].stage;
#endif
                RequestStageChangeKidnapEnd(
                    st, eBrainGetTargetGeneratorFromLabel(gameSysObjInfo[kidnapObjIdx].no));
            }
        }
        break;
    }
}
#endif

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
#ifndef VERSION_JUN26
    if (1.0f <= ratio) {
        GetRootPosition(out, gobj1);
        return;
    }
#endif
    n = NumOfWpPos();
    if (n != 0) {
        sum = 0.0f;
        memset(&prev, 0, sizeof(prev));
        target = len * ratio;
#ifndef VERSION_JUN26
        debug_StdPrintfDummy("way num %d\n", n);
#endif
        for (i = 0; i < n; i++) {
            CopyWpPos(&cur.f, i, i);
            if (i == 0) {
                sum = 0.0f;
            } else {
                sceVu0SubVector(d.f, prev.f, cur.f);
                sum += FSqrt(_InnerProduct(d.f, d.f));
            }
#ifndef VERSION_JUN26
            debug_StdPrintfDummy("%d %d:dist %f calcdist %f\n", i, n, target, sum);
#endif
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
#ifdef VERSION_JUN26
    } else {
#else
        debug_StdPrintfDummy("set pos_table %f %f %f\n", out[0], out[1], out[2]);
    } else {
        /* no WAY candidate */
        debug_StdPrintfDummy("WAY候補無し");
#endif
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

#ifdef VERSION_NTSC
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
        if (gflagChk(357) != 0) {
            return;
        }
    }
    limit = 10000000.0f;
    if (limit < range) {
        range = limit;
    }
    if (backStageGirlTargetEnemyGop == 0 && IsGirlEscortedInCurrentStage() == 0 &&
        gflagChk(361) == 0 && gameSysObjInfo[1].stage == stage_no && warpGirlInStageSet == 0) {
        /* the heroine is not held, so the position is changed at random */
        debug_StdPrintfDummy("ヒロイン捕まっていないのでランダムで位置変更");
        if (gflagChk(358) == 0) {
            kidnapWarpToWaypoint(girlGObj, range);
        }
    }
    gobj = isysGObjSearchFromObjKindID_begin(4);
    while (gobj != 0) {
        if (isEnemyKidnapEnable(gobj) != 0) {
            if (backStageGirlTargetEnemyGop != gobj) {
                /* the heroine is not held */
                debug_StdPrintfDummy("ヒロイン捕まってない");
                if (gflagChk(358) == 0 && InqCapsuleGhostBossStage() == 0) {
                    kidnapWarpToWaypoint(gobj, range);
                }
            } else {
                t = isysGObjSearchFromObjLayoutID(eBrainGetTargetGeneratorFromLabel(gobj->labelId));
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
                    pos.f[1] = pos.f[1] - GOBJ_SUB(backStageGirlTargetEnemyGop)->skel->pos[1];
                    SetDirectRootPosition(backStageGirlTargetEnemyGop, pos.f);
                }
            }
        }
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}
#else
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
#ifdef VERSION_AUG6
        if (gflagChk(356) != 0) {
#else
#ifdef VERSION_JUN26
        if (gflagChk(340) != 0) {
#else
        if (gflagChk(390) != 0) {
#endif
#endif
            return;
        }
    }
    limit = 10000000.0f;
    if (limit < range) {
        range = limit;
    }
#ifdef VERSION_JUN26
    if (backStageGirlTargetEnemyGop == 0 && IsGirlEscortedInCurrentStage() == 0 &&
        gflagChk(343) == 0 && gameSysObjInfo[1].stage == stage_no) {
        kidnapWarpToWaypoint(girlGObj, range);
#else
#ifdef VERSION_AUG6
    if (backStageGirlTargetEnemyGop == 0 && IsGirlEscortedInCurrentStage() == 0 &&
        gflagChk(360) == 0 && gameSysObjInfo[1].stage == stage_no && warpGirlInStageSet == 0) {
        /* the heroine is not held, so the position is changed at random */
        debug_StdPrintfDummy("ヒロイン捕まっていないのでランダムで位置変更");
        if (gflagChk(357) == 0) {
#else
    if (backStageGirlTargetEnemyGop == 0 && IsGirlEscortedInCurrentStage() == 0 &&
        gflagChk(394) == 0 && gameSysObjInfo[1].stage == stage_no && warpGirlInStageSet == 0) {
        /* the heroine is not held, so the position is changed at random */
        debug_StdPrintfDummy("ヒロイン捕まっていないのでランダムで位置変更");
        if (gflagChk(391) == 0) {
#endif
            kidnapWarpToWaypoint(girlGObj, range);
        }
#endif
    }
    gobj = isysGObjSearchFromObjKindID_begin(4);
    while (gobj != 0) {
        if (isEnemyKidnapEnable(gobj) != 0) {
            if (backStageGirlTargetEnemyGop != gobj) {
#ifdef VERSION_JUN26
                kidnapWarpToWaypoint(gobj, range);
#else
                /* the heroine is not held */
                debug_StdPrintfDummy("ヒロイン捕まってない");
#ifdef VERSION_AUG6
                if (gflagChk(357) == 0 && InqCapsuleGhostBossStage() == 0) {
#else
                if (gflagChk(391) == 0 && InqCapsuleGhostBossStage() == 0) {
#endif
                    kidnapWarpToWaypoint(gobj, range);
                }
#endif
            } else {
                t = isysGObjSearchFromObjLayoutID(eBrainGetTargetGeneratorFromLabel(gobj->labelId));
                if (t != 0) {
                    Vec16 pos;
#ifdef VERSION_JUN26
                    float ratio;

                    ratio = (float)carryTime /
                            (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 100.0f;
                    rest = nestDist - ratio;
                    if (rest < 0.0f) {
                        rest = nestDist;
                    }
                    routeSetPos(backStageGirlTargetEnemyGop, t, pos.f, rest / nestDist);
#else
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
#endif
                    pos.f[1] = pos.f[1] - GOBJ_SUB(backStageGirlTargetEnemyGop)->skel->pos[1];
                    SetDirectRootPosition(backStageGirlTargetEnemyGop, pos.f);
                }
            }
        }
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}
#endif

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
