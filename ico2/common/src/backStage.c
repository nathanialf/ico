#include "common.h"

/* header prototypes (order fixes the inline tail) */
/* prototypes: their order is the inline tail's emission order */
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);
void backStageProcessInit(void);
void backStageDebugTimeZero(void);
void backStageTsuresariReturn(void);
extern int D_0063ACF0;
extern int D_0063C350;
extern int D_0063C354;
extern int D_0063C358;
extern int D_0063C35C;
extern float D_0063C360;
extern float D_0063C364;
extern float D_0063C368;
extern float D_0063C36C;
extern int func_001B6CA0(void *, void *, int);
extern int gamesysMemoryHandlerRead(void *, void *, int);
extern int D_0063C370;

/* --- su-b sweep decls --- */
typedef union {
    float f[4];
    long long q[2];
} Vec16;

/* the 0x40-byte gamesys object-info record (src/gamesys.c GamesysObjInfo) */
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
} GamesysObjInfo;

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

extern GamesysObjInfo D_004DA980[];
extern GenGeoRec D_002C2DC8[];
extern float D_006FACF0[4];
extern int gamesysAnotherStageTsuresari;
extern int D_0063B60C;
extern int stage_no;
extern int D_0063C374;
extern char D_00619238[];
extern int gflagChk(int flag);
extern void sceVu0CopyVector(void *dst, void *src);
extern void *memset(void *p, int c, int n);
extern GamesysObjInfo *gamesysObjInfoPosNewStageSet(int no, int kind, int stage, float *pos,
                                                    float *rot);
extern void SetInfoSpKidnapGenerator(int *work);
extern void SetInfoSpKidnapEnemy(int *work);
extern int CameraGetMode(void);
extern void SetStatusBoy_OtherStageGirlPinch(void);
extern int eBrainGetTargetGeneratorFromLabel(int label);
extern void RequestStageChangeKidnapEnd(int stage, int gen);
extern void debug_StdPrintfDummy(char *fmt, ...);
extern char D_006191D0[];
extern char D_006191E0[];
extern char D_00619200[];
extern float D_006FACF0[4];
extern int NearestEnemyFromGirl(float *dist);
extern void *gamesysObjInfoPosSetStage(int gobj, int a1, int a2, int stage);
extern float WayLengthOfPos_Pos(float *a, float *b);
extern void GetRootProjectionPosOfGObj(float *out, int gobj);
extern int WayPointWithRangeFromPos2(float *pos, void *a1, float *out, int flag);
extern void gamesysObjInfoCls(int kind, int no);
extern char D_00619260[];
extern char D_00619270[];
extern char D_00619290[];
extern char D_006192A8[];
extern float WayLengthOfGObj_GObj(int gobj0, int gobj1);
extern void GetRootPosition(float *out, int gobj);
extern int NumOfWpPos(void);
extern void CopyWpPos(float *out, int i, int j);
extern void sceVu0SubVector(float *dst, float *a, float *b);
extern float _InnerProduct(float *a, float *b);
extern float FSqrt(float x);
extern int D_0028F4C0[];
extern int D_004DA7D0[];
extern unsigned int gamesysTimeCount;
extern long long D_004DA9C0;
extern unsigned short D_004DA9C4;
extern int D_00639EA8;
extern int warpGirlInStageSet;
extern char D_0063ACF8[];
extern char D_006192B8[];
extern char D_006192E8[];
extern char D_00619300[];
extern char D_00619330[];
extern int IsGirlEscortedInCurrentStage(void);
extern void WayPointWithRangeFromPos(float *pos, float range, int flag);
extern int rand(void);
extern void SetDirectRootPosition(int gobj, float *pos);
extern int isysGObjSearchFromObjKindID_begin(int kind);
extern int isysGObjSearchFromObjKindID_next(int gobj);
extern int isEnemyKidnapEnable(int gobj);
extern int InqCapsuleGhostBossStage(void);
extern int isysGObjSearchFromObjLayoutID(int id);
extern void routeSetPos(int gobj0, int gobj1, float *out, float ratio);

inline void backStageProcessInit(void)
{
    D_0063ACF0 = 0;
    D_0063C35C = -1;
    D_0063C350 = 0;
    D_0063C370 = 0;
}

inline void backStageDebugTimeZero(void)
{
    D_0063C354 = 0;
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
        D_0063C350 = 0;
        done = 1;
    }
    if (D_004DA980[1].stage == stage_no && done == 0) {
        debug_StdPrintfDummy(D_006191D0);
        D_0063C370 = 0;
        D_0063C35C = -1;
        for (i = 2; i < 22; i++) {
            if (D_004DA980[i].no == 0) {
                continue;
            }
            if (D_004DA980[i].stage != stage_no) {
                continue;
            }
            if (D_004DA980[i].work[0] == 4) {
                D_0063C35C = i;
                break;
            }
        }
        D_0063C350 = 0;
        D_0063C374 = 0;
        if (D_0063C35C < 0) {
            int e = NearestEnemyFromGirl(&D_0063C360);

            if (e != 0) {
                ActorWorkRec *m;

                D_0063C350 = 1;
                D_0063C368 = D_0063C360 / 160.0f;
                D_0063C354 = (int)(D_0063C368 * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
                m = *(ActorWorkRec **)(e + 0x164);
                D_0063C35C =
                    (unsigned int)((char *)gamesysObjInfoPosSetStage(e, m->objNo, 0, stage_no) -
                                   (char *)D_004DA980) >>
                    6;
            }
        } else {
            D_0063C350 = 2;
            D_0063C370 = 1;
        }
        if (D_0063C350 == 1 || D_0063C350 == 2) {
            gen = eBrainGetTargetGeneratorFromLabel(D_004DA980[D_0063C35C].no);
            p = isysGObjSearchFromObjLayoutID(gen);
            if (p == 0) {
                D_0063C350 = 0;
            } else {
                GetRootPosition(a.f, p);
                GetRootPosition(b.f, D_00639EA8);
                D_0063C364 = WayLengthOfPos_Pos(a.f, b.f);
                D_0063C36C = D_0063C364 / 100.0f;
                D_0063C358 = (int)(D_0063C36C * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
            }
        } else if (((StageInfoRec *)(D_005F5D50 + stage_no * 0x194))->wayBits != 0) {
            GetRootProjectionPosOfGObj(a.f, D_00639EA8);
            D_0063C374 = 1;
            D_0063C350 = 1;
            D_0063C368 = (float)((StageInfoRec *)(D_005F5D50 + stage_no * 0x194))->wayBits;
            D_0063C354 = (int)(D_0063C368 * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
            if (WayPointWithRangeFromPos2(a.f, *(char **)(D_00639EA8 + 0x164) + 0x360, D_006FACF0,
                                          1) == 0) {
                debug_StdPrintfDummy(D_006191E0);
                if (WayPointWithRangeFromPos2(a.f, *(char **)(D_00639EA8 + 0x164) + 0x360,
                                              D_006FACF0, 0) == 0) {
                    debug_StdPrintfDummy(D_00619200);
                    sceVu0CopyVector(D_006FACF0, a.f);
                }
            }
            D_0063C364 = WayLengthOfPos_Pos(D_006FACF0, a.f);
            D_0063C36C = D_0063C364 / 100.0f;
            D_0063C358 = (int)(D_0063C36C * (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
            if ((float)D_0063C358 < (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 30.0f) {
                D_0063C358 = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 30.0f);
            }
        }
        if ((float)D_0063C358 < (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10.0f) {
            D_0063C358 = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10.0f);
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
    GamesysObjInfo *g1;
    GamesysObjInfo *g2;

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
    switch (D_0063C350) {
    case 1:
        if (D_0063C354-- < 0) {
            D_0063C350 = 2;
            if (D_0063C374 == 0) {
                GamesysObjInfo *s = &D_004DA980[D_0063C35C];
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
                D_0063C35C = (unsigned int)((char *)g1 - (char *)D_004DA980) >> 6;
                pos.f[0] = D_006FACF0[0];
                pos.f[2] = D_006FACF0[2];
                pos.f[1] = D_006FACF0[1] - 10.0f;
                g2 = gamesysObjInfoPosNewStageSet(0xEAE, 0x21, D_004DA980[1].stage, pos.f, rot.f);
                SetInfoSpKidnapGenerator(g2->work);
                SetInfoSpKidnapEnemy(g1->work);
                if (g1 != 0 && g2 != 0) {
                    g1->work[0] = 4;
                } else {
                    debug_StdPrintfDummy(D_00619238);
                    D_0063C350 = 1;
                }
            }
        }
        break;
    case 2:
        if (CameraGetMode() != 4) {
            if (D_0063C370 == 0) {
                SetStatusBoy_OtherStageGirlPinch();
                D_0063C370 = 1;
            }
            gamesysAnotherStageTsuresari = 1;
            if (D_0063C358-- < 0) {
                int st = D_004DA980[1].stage;
                RequestStageChangeKidnapEnd(
                    st, eBrainGetTargetGeneratorFromLabel(D_004DA980[D_0063C35C].no));
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

    len = WayLengthOfGObj_GObj(gobj0, gobj1);
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
        debug_StdPrintfDummy(D_00619260, n);
        for (i = 0; i < n; i++) {
            CopyWpPos(cur.f, i, i);
            if (i == 0) {
                sum = 0.0f;
            } else {
                sceVu0SubVector(d.f, prev.f, cur.f);
                sum += FSqrt(_InnerProduct(d.f, d.f));
            }
            debug_StdPrintfDummy(D_00619270, i, n, target, sum);
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
        debug_StdPrintfDummy(D_00619290, out[0], out[1], out[2]);
    } else {
        debug_StdPrintfDummy(D_006192A8);
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
        debug_StdPrintfDummy(D_006192B8);
        if (gflagChk(0x187) == 0) {
            kidnapWarpToWaypoint(D_00639EA8, range);
        }
    }
    gobj = isysGObjSearchFromObjKindID_begin(4);
    while (gobj != 0) {
        if (isEnemyKidnapEnable(gobj) != 0) {
            if (D_0063ACF0 != gobj) {
                debug_StdPrintfDummy(D_006192E8);
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

                    if (D_0063C358 > 0) {
                        ratio = (float)D_0063C358 /
                                (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 100.0f;
                    } else {
                        ratio = 0.0f;
                    }
                    rest = 0.0f;
                    if (ratio <= D_0063C364) {
                        rest = D_0063C364 - ratio;
                    }
                    GetRootPosition(root.f, D_00639EA8);
                    SetDirectRootPosition(D_0063ACF0, root.f);
                    if (0.0f < D_0063C364) {
                        routeSetPos(D_0063ACF0, t, pos.f, rest / D_0063C364);
                    } else {
                        debug_StdPrintfDummy(D_00619300);
                        routeSetPos(D_0063ACF0, t, pos.f, 1.0f);
                    }
                    debug_StdPrintfDummy(D_00619330, pos.f[0], pos.f[1], pos.f[2]);
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
    func_001B6CA0(a0, &D_0063ACF0, 4);
    func_001B6CA0(a0, &D_0063C350, 4);
    func_001B6CA0(a0, &D_0063C354, 4);
    func_001B6CA0(a0, &D_0063C358, 4);
    func_001B6CA0(a0, &D_0063C35C, 4);
    func_001B6CA0(a0, &D_0063C360, 4);
    func_001B6CA0(a0, &D_0063C364, 4);
    func_001B6CA0(a0, &D_0063C368, 4);
    func_001B6CA0(a0, &D_0063C36C, 4);
}

void backStageLoad(void *a0)
{
    gamesysMemoryHandlerRead(a0, &D_0063ACF0, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C350, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C354, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C358, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C35C, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C360, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C364, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C368, 4);
    gamesysMemoryHandlerRead(a0, &D_0063C36C, 4);
}

inline void backStageTsuresariReturn(void) {}
