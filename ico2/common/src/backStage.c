#include "common.h"
#include "debug.h"
#include "enemy_act.h"
#include "itou_boss.h"
#include "camera-root.h"
#include "ebrain.h"
#include "gflag.h"
#include "matrixDrive.h"
#include "motionManager2.h"
/* header prototypes (order fixes the inline tail) */
#include "backStage.h"
#include <libvu0.h>
#include <stdlib.h>
#include "boyact.h"
#include "geometryManager.h"

extern int D_0063ACF0;

/* .sbss, owned by backStage.o and reached only from this file (MAIN.MAP names
   no symbol in the run).  The off-stage kidnap state, in the ROM's run order,
   which is also the order backStageSave writes it to the memory card. */
static int kidnapState; /* 0 idle, 1 counting down to the grab, 2 carrying */

static int kidnapTime; /* frames left before the heroine is taken */

static int carryTime; /* frames left before the nest is reached */

static int kidnapObjIdx; /* index of the carrier in the gamesys object-info table */

static float enemyDist; /* distance from the heroine to the nearest enemy */

static float nestDist; /* route length from the carrier to the nest */

static float enemySec; /* enemyDist scaled to seconds */

static float nestSec; /* nestDist scaled to seconds */

/* kept local: this TU's uses of gamesysMemoryHandlerWrite do not fit the prototype in gamesys.h */
extern int gamesysMemoryHandlerWrite(void *, void *, int);
/* kept local: this TU's uses of gamesysMemoryHandlerRead do not fit the prototype in gamesys.h */
extern int gamesysMemoryHandlerRead(void *, void *, int);

static int pinchTold; /* the boy has already been told the heroine is in trouble */

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

/* the 0x194-byte per-stage record D_005F5D50; wayBits is a 9-bit field in the
   bitfield word at 0x18C, which is why it is read with an lhu at 0x18E */
typedef struct {
    char pad000[0x18C];
    unsigned int pad18C : 16;
    unsigned int wayBits : 9;
    unsigned int pad18E_hi : 7;
    char pad190[0x194 - 0x190];
} StageInfoRec;

extern char D_005F5D50[];

/* the actor work record a gobj carries at 0x164 (src/enemy_act.c reads the same
   0x444 member off the same 0x164 pointer) */
typedef struct {
    char pad000[0x444];
    int objNo; /* 0x444 */
} ActorWorkRec;

/* the 0x4C-byte generator-geometry record (src/ebrain.c GenGeo) */
typedef struct {
    float scale[3]; /* 0x00 */
    float rot[3];   /* 0x0C */
    char pad18[0x4C - 0x18];
} GenGeoRec;

extern GamesysObjInfoBackstage D_004DA980[];
extern GenGeoRec D_002C2DC8[];

/* .bss, owned by backStage.o and reached only from this file: the nest position
   the carrier walks to. */
static float nestPos[4];

extern int gamesysAnotherStageTsuresari;
extern int D_0063B60C;
extern int stage_no;

static int wayKidnap; /* the carrier walks the waypoint route instead of a generator */

extern void *memset(void *p, int c, int n);
/* kept local: this TU's uses of gamesysObjInfoPosNewStageSet do not fit the prototype in gamesys.h */
extern GamesysObjInfoBackstage *gamesysObjInfoPosNewStageSet(int no, int kind, int stage,
                                                             float *pos, float *rot);
/* kept local: this TU's uses of SetInfoSpKidnapGenerator do not fit the prototype in generator.h */
extern void SetInfoSpKidnapGenerator(int *work);
/* kept local: this TU's uses of SetInfoSpKidnapEnemy do not fit the prototype in generator.h */
extern void SetInfoSpKidnapEnemy(int *work);
/* kept local: this TU's uses of NearestEnemyFromGirl do not fit the prototype in way_kidnap.h */
extern int NearestEnemyFromGirl(float *dist);
/* kept local: this TU's uses of gamesysObjInfoPosSetStage do not fit the prototype in gamesys.h */
extern int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3);
/* kept local: this TU's uses of WayLengthOfPos_Pos do not fit the prototype in way_kidnap.h */
extern float WayLengthOfPos_Pos(float *a, float *b);
/* kept local: this TU's uses of WayPointWithRangeFromPos2 do not fit the prototype in way_kidnap.h */
extern int WayPointWithRangeFromPos2(float *pos, void *a1, float *out, int flag);
/* kept local: this TU's uses of gamesysObjInfoCls do not fit the prototype in gamesys.h */
extern void gamesysObjInfoCls(int kind, int no);
/* kept local: this TU's uses of WayLengthOfGObj_GObj do not fit the prototype in way_kidnap.h */
extern float WayLengthOfGObj_GObj(void *obj0, void *obj1);
/* kept local: this TU's uses of NumOfWpPos do not fit the prototype in way_kidnap.h */
extern int NumOfWpPos(void);
/* kept local: this TU's uses of CopyWpPos do not fit the prototype in way_kidnap.h */
extern void CopyWpPos(float *out, int i, int j);
/* kept local: this TU's uses of _InnerProduct do not fit the prototype in Matrix.h */
extern float _InnerProduct(float *a, float *b);
extern int D_0028F4C0[];
extern int D_004DA7D0[];
extern unsigned int gamesysTimeCount;
extern int D_00639EA8;
extern int warpGirlInStageSet;
extern char D_0063ACF8[];
/* kept local: this TU's uses of WayPointWithRangeFromPos do not fit the prototype in way_kidnap.h */
extern void WayPointWithRangeFromPos(float *pos, float range, int flag);
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_begin do not fit the prototype in gobj.h */
extern int isysGObjSearchFromObjKindID_begin(int kind);
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_next do not fit the prototype in gobj.h */
extern int isysGObjSearchFromObjKindID_next(int gobj);
/* kept local: this TU's uses of isysGObjSearchFromObjLayoutID do not fit the prototype in gobj.h */
extern int isysGObjSearchFromObjLayoutID(int id);

inline void backStageProcessInit(void)
{
    D_0063ACF0 = 0;
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
    int p;
    int o;

    done = 0;
    if (gflagChk(0x18A) != 0) {
        kidnapState = 0;
        done = 1;
    }
    if (D_004DA980[1].stage == stage_no && done == 0) {
        debug_StdPrintfDummy("girl nokori");
        pinchTold = 0;
        kidnapObjIdx = -1;
        for (i = 2; i < 22; i++) {
            if (D_004DA980[i].no == 0) {
                continue;
            }
            if (D_004DA980[i].stage != stage_no) {
                continue;
            }
            if (D_004DA980[i].work[0] == 4) {
                kidnapObjIdx = i;
                break;
            }
        }
        kidnapState = 0;
        wayKidnap = 0;
        if (kidnapObjIdx < 0) {
            int e = NearestEnemyFromGirl(&enemyDist);

            if (e != 0) {
                ActorWorkRec *m;

                kidnapState = 1;
                enemySec = enemyDist / 160.0f;
                kidnapTime = (int)(enemySec * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
                m = *(ActorWorkRec **)(e + 0x164);
                kidnapObjIdx = (unsigned int)((char *)gamesysObjInfoPosSetStage((int *)e, m->objNo,
                                                                                0, stage_no) -
                                              (char *)D_004DA980) >>
                               6;
            }
        } else {
            kidnapState = 2;
            pinchTold = 1;
        }
        if (kidnapState == 1 || kidnapState == 2) {
            gen = eBrainGetTargetGeneratorFromLabel(D_004DA980[kidnapObjIdx].no);
            p = isysGObjSearchFromObjLayoutID(gen);
            if (p == 0) {
                kidnapState = 0;
            } else {
                GetRootPosition(a.f, p);
                GetRootPosition(b.f, D_00639EA8);
                nestDist = WayLengthOfPos_Pos(a.f, b.f);
                nestSec = nestDist / 100.0f;
                carryTime = (int)(nestSec * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
            }
        } else if (((StageInfoRec *)(D_005F5D50 + stage_no * 0x194))->wayBits != 0) {
            GetRootProjectionPosOfGObj(a.f, D_00639EA8);
            wayKidnap = 1;
            kidnapState = 1;
            enemySec = (float)((StageInfoRec *)(D_005F5D50 + stage_no * 0x194))->wayBits;
            kidnapTime = (int)(enemySec * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
            if (WayPointWithRangeFromPos2(a.f, *(char **)(D_00639EA8 + 0x164) + 0x360, nestPos,
                                          1) == 0) {
                /* no ACTIVE connection was found */
                debug_StdPrintfDummy("繋がりACTIVEでみつからなかった");
                if (WayPointWithRangeFromPos2(a.f, *(char **)(D_00639EA8 + 0x164) + 0x360, nestPos,
                                              0) == 0) {
                    /* no connection was found, so the nest is placed at the heroine */
                    debug_StdPrintfDummy("繋がりみつからなかったのでヒロインの位置に巣を配置");
                    sceVu0CopyVector(nestPos, a.f);
                }
            }
            nestDist = WayLengthOfPos_Pos(nestPos, a.f);
            nestSec = nestDist / 100.0f;
            carryTime = (int)(nestSec * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
            if ((float)carryTime < (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 30.0f) {
                carryTime = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 30.0f);
            }
        }
        if ((float)carryTime < (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10.0f) {
            carryTime = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10.0f);
        }
    } else {
        o = isysGObjSearchFromObjKindID_begin(4);
        while (o != 0) {
            if (*(int *)(o + 8) == 0xEAD) {
                gamesysObjInfoCls(4, 0xEAD);
            }
            o = isysGObjSearchFromObjKindID_next(o);
        }
        o = isysGObjSearchFromObjKindID_begin(0x21);
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
    GamesysObjInfoBackstage *g2;

    gamesysAnotherStageTsuresari = 0;
    if (gflagChk(0x186) != 0) {
        return;
    }
    if (D_0063B60C != 0x36) {
        return;
    }
    if (stage_no == D_004DA980[1].stage) {
        return;
    }
    switch (kidnapState) {
    case 1:
        if (kidnapTime-- < 0) {
            kidnapState = 2;
            if (wayKidnap == 0) {
                GamesysObjInfoBackstage *s = &D_004DA980[kidnapObjIdx];
                sceVu0CopyVector(&s->pos, &D_004DA980[1].pos);
                s->work[0] = 4;
            } else {
                memset(&tmp, 0, sizeof(tmp));
                tmp.f[0] = D_002C2DC8[0xEAE].rot[0];
                tmp.f[1] = D_002C2DC8[0xEAE].rot[1];
                tmp.f[2] = D_002C2DC8[0xEAE].rot[2];
                rot = tmp;
                g1 = gamesysObjInfoPosNewStageSet(0xEAD, 4, D_004DA980[1].stage,
                                                  D_004DA980[1].pos.f, D_004DA980[1].rot.f);
                kidnapObjIdx = (unsigned int)((char *)g1 - (char *)D_004DA980) >> 6;
                pos.f[0] = nestPos[0];
                pos.f[2] = nestPos[2];
                pos.f[1] = nestPos[1] - 10.0f;
                g2 = gamesysObjInfoPosNewStageSet(0xEAE, 0x21, D_004DA980[1].stage, pos.f, rot.f);
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
                int st = D_004DA980[1].stage;
                RequestStageChangeKidnapEnd(
                    st, eBrainGetTargetGeneratorFromLabel(D_004DA980[kidnapObjIdx].no));
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

/* common/src/backStage.c:772-796, inlined at both of its call sites */
static inline void kidnapWarpToWaypoint(int gobj, float range)
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
    wp.f[1] = wp.f[1] - *(float *)(*(int *)(*(int *)(gobj + 0x15C) + 0x8C) + 0x14);
    SetDirectRootPosition(gobj, wp.f);
}

void backStageProcessInStage(float arg)
{
    float range;
    float limit;
    float rest;
    int gobj;
    int t;

    range = (float)((unsigned int)(gamesysTimeCount - D_004DA7D0[stage_no]) /
                    ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1])) *
            40.0f;
    if (arg != 0.0f) {
        range = arg;
        debug_StdPrintfDummy(D_0063ACF8, (int)(*(long long *)&D_004DA980[1] >> 1) & 1);
    } else {
        if (D_004DA7D0[stage_no] == 0) {
            return;
        }
        if (gflagChk(0x186) != 0) {
            return;
        }
    }
    limit = 10000000.0f;
    if (limit < range) {
        range = limit;
    }
    if (D_0063ACF0 == 0 && IsGirlEscortedInCurrentStage() == 0 && gflagChk(0x18A) == 0 &&
        D_004DA980[1].stage == stage_no && warpGirlInStageSet == 0) {
        /* the heroine is not held, so the position is changed at random */
        debug_StdPrintfDummy("ヒロイン捕まっていないのでランダムで位置変更");
        if (gflagChk(0x187) == 0) {
            kidnapWarpToWaypoint(D_00639EA8, range);
        }
    }
    gobj = isysGObjSearchFromObjKindID_begin(4);
    while (gobj != 0) {
        if (isEnemyKidnapEnable(gobj) != 0) {
            if (D_0063ACF0 != gobj) {
                /* the heroine is not held */
                debug_StdPrintfDummy("ヒロイン捕まってない");
                if (gflagChk(0x187) == 0 && InqCapsuleGhostBossStage() == 0) {
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
                                (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 100.0f;
                    } else {
                        ratio = 0.0f;
                    }
                    rest = 0.0f;
                    if (ratio <= nestDist) {
                        rest = nestDist - ratio;
                    }
                    GetRootPosition(root.f, D_00639EA8);
                    SetDirectRootPosition(D_0063ACF0, root.f);
                    if (0.0f < nestDist) {
                        routeSetPos(D_0063ACF0, t, pos.f, rest / nestDist);
                    } else {
                        /* no route to the nest was found, so it is placed at the nest directly */
                        debug_StdPrintfDummy("巣までの経路がみつからないので直接巣に配置");
                        routeSetPos(D_0063ACF0, t, pos.f, 1.0f);
                    }
                    debug_StdPrintfDummy("set pos %f %f %f\n", pos.f[0], pos.f[1], pos.f[2]);
                    pos.f[1] =
                        pos.f[1] - *(float *)(*(int *)(*(int *)(D_0063ACF0 + 0x15C) + 0x8C) + 0x14);
                    SetDirectRootPosition(D_0063ACF0, pos.f);
                }
            }
        }
        gobj = isysGObjSearchFromObjKindID_next(gobj);
    }
}

void backStageSave(void *a0)
{
    gamesysMemoryHandlerWrite(a0, &D_0063ACF0, 4);
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
    gamesysMemoryHandlerRead(a0, &D_0063ACF0, 4);
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
