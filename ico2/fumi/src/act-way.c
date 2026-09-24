#include "common.h"

/* kept local: this TU's uses of ACTCheckCollis_WAY do not fit the prototype in act-game.h */
extern unsigned char ACTCheckCollis_WAY(void *a0, void *a1, float a2, void *a3, void *a4);

#include "act-way.h"
#include "act.h"
#include "gobj_process.h"
#include "way_sys.h"
#include "waySystemManager.h"
#include <libvu0.h>

/* kept local: this TU's uses of _DistxzSqGV do not fit the prototype in gv.h */
extern float _DistxzSqGV(void *a, void *b);

/* act + 0x438: the way-state word, which the ROM reads and writes both as one
   64-bit flag word and as the two status bytes at 0x438 and 0x439 */
typedef union {
    long long flags;
    unsigned char st[2];
} WayState;

/* the 0x80-byte way-walker work record, the same one ico2/fumi/src/way_kidnap
   carries as WayWork; the actor keeps its copy at act + 0x360 */
typedef struct {
    long long _00[7]; /* 0x00 */
    int _38;          /* 0x38 */
    int f3C;          /* 0x3C */
    long long _40[4]; /* 0x40 */
    int _60;          /* 0x60 */
    int f64;          /* 0x64 */
    long long _68[3]; /* 0x68 */
} WayWork;            /* 0x80 */

/* kept local: this TU's uses of test_CURRENTROOT do not fit the prototype in commonact.h */
extern float *test_CURRENTROOT();
/* the two-word playback-rate pair the wait counters are scaled by */
extern int D_0028F4C0[];

/* the three detour angles DetourCheck sweeps, in degrees, zero-terminated */
static int detourAngle[4] = {75, -75, 0, 0};

extern int D_0063B22C;
/* kept local: this TU's uses of GetSkeltonOrient do not fit the prototype in act-game.h */
extern void GetSkeltonOrient(float *dst, char *self, int node);
/* kept local: this TU's uses of _ApplyRyGV do not fit the prototype in gv.h */
extern void _ApplyRyGV(float *v, float ry);

void DetourCheck(char *self, float *out)
{
    float orient[4];
    float cur[4];
    float o2[4];
    float tmp[4];
    float dir[4];
    char *act = *(char **)(self + 0x164);
    int i;
    int wait = 0;
    int ok = 0;

    if (D_0063B22C == 0) {
        return;
    }
    GetSkeltonOrient(orient, self, 0x2C);
    if (*(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8E0) != 0) {
        out[0] = *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8F0);
        out[1] = *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8F4);
        out[2] = *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8F8);
        *(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8E0) -= 1;
        return;
    }
    /* two identical case bodies (listing 133-134 is the one jump2's cross
       jumping keeps); a shared `case 2: case 3:` body is a range test */
    switch (*(int *)(act + 0x34)) {
    case 2:
        ok = 1;
        wait = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 40 / 60;
        break;
    case 3:
        ok = 1;
        wait = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 40 / 60;
        break;
    }
    /* listing line 139: the four tests are one statement */
    if (ok == 0 || *(float *)(act + 0x34C) == 0.0f ||
        (*(int *)(*(char **)(self + 0x15C) + 0x484) & 2) == 0 ||
        ((*(unsigned long long *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x448) >> 33) &
         1) == 0) {
        return;
    }
    cur[0] = test_CURRENTROOT(self)[0];
    cur[1] = test_CURRENTROOT(self)[1];
    cur[2] = test_CURRENTROOT(self)[2];
    GetSkeltonOrient(o2, self, 0x2C);
    for (i = 0; detourAngle[i] != 0; i++) {
        dir[0] = o2[0];
        dir[1] = o2[1];
        dir[2] = o2[2];
        _ApplyRyGV(dir, (float)detourAngle[i] * 3.1415927f / 180.0f);
        sceVu0ScaleVector(tmp, dir, 100.0f);
        sceVu0AddVector(tmp, cur, tmp);
        if (ACTCheckCollis_WAY(cur, tmp, 10.0f, 0, 0) == 0) {
            *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8F0) = dir[0];
            *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8F4) = dir[1];
            *(float *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8F8) = dir[2];
            *(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8E0) = wait;
            return;
        }
    }
}

/* the 0x194-byte enemy parameter rows, the same record ico2/fumi/src/enemy_act
   reads the 0x18C flag word out of */
typedef struct {
    char pad00[0x18C];
    unsigned int flags18C; /* 0x18C */
    char pad190[4];
} EnemyParaRow;

extern EnemyParaRow D_0055FE58[];
extern void debug_NMarker(float *pos, int r, int g, int b, float size);
extern float GetDifferenceFromLastField(char *self, int a1);

int checkPositionIllegal(char *self, float *pos)
{
    float v[4];
    float r[4];
    float dy;
    char *act = *(char **)(self + 0x164);

    if (*(int *)(act + 0x34) == 0x70) {
        return 1;
    }
    if (*(int *)(act + 0x34) == 0x26 ||
        ((((EnemyParaRow *)((char *)D_0055FE58 +
                            *(int *)(*(char **)(self + 0x15C) + 0x4A0) * 0x194))
              ->flags18C >>
          12) &
         1)) {
        return 1;
    }
    v[0] = pos[0];
    v[1] = pos[1];
    v[2] = pos[2];
    debug_NMarker(v, 0, 255, 0, 100.0f);
    r[0] = test_CURRENTROOT(self)[0];
    r[1] = test_CURRENTROOT(self)[1];
    r[2] = test_CURRENTROOT(self)[2];
    r[1] = r[1] - GetDifferenceFromLastField(self, 0x2C);
    debug_NMarker(r, 0, 0, 255, 100.0f);
    dy = v[1] - r[1];
    if (dy < 0.0f) {
        if (-dy > 40.0f) {
            return 1;
        }
        return 0;
    }
    return dy > 40.0f;
}

inline unsigned char WayMove_CheckCollis(float *p0, float *p1, void *a2, void *a3)
{
    float a[4];
    float b[4];

    a[0] = p0[0];
    a[1] = p0[1];
    a[2] = p0[2];
    b[0] = p1[0];
    b[1] = p1[1];
    b[2] = p1[2];
    a[1] -= 50.0f;
    b[1] -= 50.0f;
    return ACTCheckCollis_WAY(a, b, 10.0f, a2, a3);
}

/* ico2/fumi/src/act-way.c lines 236 to 290: three helpers the January-2002
   listing inlines into ACTWayMove_BeginDetail and ACTWayMove_NextDetail.
   None of them carries a symbol of its own in MAIN.MAP, so the names here
   are ours; the bodies come from the listing's rows 239 to 287. */

/* kept local: girl_act defines this and no header of its own declares it */
extern void *FindGirlPullupFloorBoxGObj(void);
extern void *D_00639EA8;
extern void *D_0063C4C8;
extern int D_0063C4C4;

static inline void SuspendGirlPullupFloorBox(void)
{
    D_0063C4C8 = FindGirlPullupFloorBoxGObj();
    D_0063C4C4 = D_0063C4C8 != 0 ? *(int *)(*(char **)((char *)D_0063C4C8 + 0x15C) + 0x74) : 0;
    if (D_0063C4C4 != 0) {
        *(int *)(*(char **)((char *)D_0063C4C8 + 0x15C) + 0x74) = 0;
    }
}

static inline void ResumeGirlPullupFloorBox(void)
{
    if (D_0063C4C4 != 0) {
        *(int *)(*(char **)((char *)D_0063C4C8 + 0x15C) + 0x74) = 1;
    }
}

static inline int RequestWayBegin(char *self, float *goal, float *from, WayWork *way,
                                  unsigned char sub)
{
    char *req;
    char *ws;
    int w;

    if (sub) {
        req = *(char **)(*(char **)(self + 0x164) + 0x688);
        ws = req + 0x580;
        if (*(int *)(ws + 0xB0) != 0) {
            isysGObjProcRemove(*(int **)(ws + 0xB0));
            *(int *)(ws + 0xB0) = 0;
        }
        *(float *)(ws + 0x10) = from[0];
        *(float *)(ws + 0x14) = from[1];
        *(float *)(ws + 0x18) = from[2];
        *(WayWork *)(req + 0x5A0) = *way;
        *(float *)(ws + 0xA0) = goal[0];
        *(float *)(ws + 0xA4) = goal[1];
        *(float *)(ws + 0xA8) = goal[2];
        *(int *)(ws + 0xB0) = (int)RequestGetWayBegin((int *)ws);
        while (*(int *)ws == 0) {
            _ACTWait(1);
        }
        w = *(int *)(ws + 4);
        *way = *(WayWork *)(ws + 0x20);
        return w;
    }
    if (self == (char *)D_00639EA8) {
        SuspendGirlPullupFloorBox();
    }
    w = GetWay_begin(from, (int)way, (int)goal);
    if (self == (char *)D_00639EA8) {
        ResumeGirlPullupFloorBox();
    }
    return w;
}

int ACTWayMove_BeginDetail(char *self, float *goal, float *from, void *tgt, void *e,
                           unsigned char sub)
{
    WayWork way;
    char *act = *(char **)(self + 0x164);
    WayWork *home;
    WayWork *wp;
    int ret = 0;
    int w;

    home = (WayWork *)(act + 0x360);
    way = *home;
    wp = &way;
    *(long long *)(act + 0x3F0) &= ~0x20000;
    *(long long *)(act + 0x3F0) &= ~0x40000;
    ((WayState *)(act + 0x438))->flags = (((WayState *)(act + 0x438))->flags & ~0x200000) |
                                         ((long long)(checkPositionIllegal(self, goal) & 1) << 21);
    *(float *)(act + 0x434) = goal[1];
    w = RequestWayBegin(self, goal, from, wp, sub);
    if (w != 0) {
        ((WayState *)(act + 0x438))->st[1] = 0;
        if (wp->f3C == 0) {
            if (WayMove_CheckCollis(goal, from, tgt, e) == 0) {
                ((WayState *)(act + 0x438))->st[1] = 1;
                DeleteGuideWay((WVTObj *)wp);
                ret = 3;
            } else {
                ret = 2;
            }
        } else {
            ret = 1;
        }
        *home = way;
        *(int *)(act + 0x400) = 0;
        *(int *)(act + 0x404) = (int)tgt;
        *(float *)(act + 0x410) = from[0];
        *(float *)(act + 0x414) = from[1];
        *(float *)(act + 0x418) = from[2];
        ((WayState *)(act + 0x438))->st[0] = 1;
    } else {
        ((WayState *)(act + 0x438))->st[0] = 0;
    }
    ((WayState *)(act + 0x438))->flags &= ~0x10000;
    ((WayState *)(act + 0x438))->flags &= ~0x1E0000;
    *(int *)(act + 0x430) = 0;
    *(int *)(*(char **)(*(char **)(self + 0x164) + 0x688) + 0x8E0) = 0;
    if (*(char **)(act + 0x384) != 0 && *(int *)(act + 0x388) == 0) {
        if (_DistxzSqGV(*(char **)(act + 0x384) + 0x10, goal) < 40000.0f) {
            *(long long *)(act + 0x3F0) |= 0x40000;
        }
    }
    return ret;
}

/* the 0x20-byte way-step record the actor keeps at act + 0x3E0: the step
   direction, the 64-bit way state word and the two distances to the goal */
typedef struct {
    float dir[4];    /* 0x00 */
    long long state; /* 0x10 */
    float dist;      /* 0x18 */
    float dy;        /* 0x1C */
} WayStep;

/* the two templates act-way.o keeps in .data: the cleared way-walker record
   (its waypoint id starts at -1) and the cleared way-step record (its two
   distances start at the largest float) */
static WayWork wayWorkClear = {{0}, 0, 0, {0}, 0, -1};

static WayStep wayStepClear = {{0.0f, 0.0f, 0.0f, 0.0f}, 0, 3.4028235e38f, 3.4028235e38f};

extern void *D_00639EA4;
extern void *D_0063A6B4;
extern int stage_no;
/* kept local: this TU's uses of the gv distance helpers do not fit the void
   returns gv.h carries, and its GetRootProjectionPosOfGObj / IsThisBoxTruck
   call forms do not fit motionManager2.h and box.h */
extern float _DistGV(void *a, void *b);
extern float _DistSqGV(void *a, void *b);
extern float _DistxzGV(void *a, void *b);
extern void _OrientXZGV(float *dst, float *a, float *b);
extern void GetRootProjectionPosOfGObj(float *dst, void *self);
extern int IsThisBoxTruck(char *box);

int ACTWayMove_NextDetail(char *self, float *node, float *goal, unsigned char d, unsigned char e)
{
    float pos[4];
    char *act = *(char **)(self + 0x164);
    char *way;
    int again = 0;
    int w;
    int r;
    unsigned char ok;
    float dy;
    int n;

    *(WayStep *)(act + 0x3E0) = wayStepClear;
    *(float *)(act + 0x3E0) = node[0];
    *(float *)(act + 0x3E4) = node[1];
    *(float *)(act + 0x3E8) = node[2];
    if (((WayState *)(act + 0x438))->st[0] == 0) {
        /* EUC-JP, "there is no route" */
        debug_StdPrintfDummy("ルートがありません\n");
    }
    GetRootProjectionPosOfGObj(pos, self);
    dy = pos[1] - *(float *)(act + 0x434);
    if (dy < 0.0f ? -dy > 120.0f : dy > 120.0f) {
        ACTWay_SetBeginPositionIllegal(self);
    }
    *(float *)(act + 0x434) = pos[1];
    if (((int)(((WayState *)(act + 0x438))->flags >> 21) & 1) != 0) {
        if (checkPositionIllegal(self, pos) == 0) {
            ((WayState *)(act + 0x438))->flags &= ~0x200000;
            DeleteGuideWay((WVTObj *)(act + 0x360));
            *(WayWork *)(act + 0x360) = wayWorkClear;
            again = 1;
        }
    }
    if (((int)(((WayState *)(act + 0x438))->flags >> 16) & 1) == 0) {
        if (_DistGV(goal, act + 0x410) > 300.0f) {
            if (((int)(((WayState *)(act + 0x438))->flags >> 17) & 0xF) == 0) {
                if (*(int *)(act + 0x34) != 0x26) {
                    again = 1;
                }
            }
        }
    }
    if (again != 0) {
        w = ACTWayMove_BeginDetail(self, pos, goal, *(void **)(act + 0x404), 0, d);
        *(long long *)(act + 0x3F0) |= 0x10000;
        if (w == 0) {
            return 0;
        }
    }
    if (*(int *)(act + 0x3CC) != 0) {
        if (*(char **)(act + 0x384) != 0 && *(int *)(act + 0x388) == 0 &&
            _DistSqGV(*(char **)(act + 0x384) + 0x10, pos) < 10000.0f) {
            float d = pos[1] - *(float *)(*(char **)(act + 0x384) + 0x14);

            if (d < 0.0f ? -d < 150.0f : d < 150.0f) {
                *(long long *)(act + 0x3F0) |= 0x20000;
            }
        }
    }
    if (*(char **)(act + 0x384) != 0 && *(int *)(act + 0x388) == 0 &&
        _DistxzSqGV(*(char **)(act + 0x384) + 0x10, pos) < 40000.0f) {
        *(long long *)(act + 0x3F0) |= 0x40000;
    }
    if (*(int *)(act + 0x34) == 0x26) {
        float v0[4];
        float v1[4];

        {
            sceVu0CopyVector(v0, (float *)(act + 0x3B0));
            sceVu0CopyVector(v1, (float *)(act + 0x550));
            v0[1] = v1[1] = 0.0f;
            if (sceVu0InnerProduct(v0, v1) > 0.0f) {
                *(int *)(act + 0x33C) = 255;
            } else {
                *(int *)(act + 0x33C) = 0;
            }
            *(float *)(act + 0x34C) = 1.0f;
            ((WayState *)(act + 0x438))->st[1] = 0;
            if (self == (char *)D_00639EA8 && goal[1] - *(float *)(act + 0x414) > 150.0f &&
                pos[1] < goal[1]) {
                if (((int)(((WayState *)(act + 0x438))->flags >> 17) & 0xF) == 0) {
                    *(int *)(act + 0x430) = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 90 / 60;
                }
                ((WayState *)(act + 0x438))->flags =
                    (((WayState *)(act + 0x438))->flags & ~0x1E0000) | 0x40000;
                *(float *)(act + 0x420) = *(float *)(act + 0x550);
                *(float *)(act + 0x424) = *(float *)(act + 0x554);
                *(float *)(act + 0x428) = *(float *)(act + 0x558);
            }
            if ((*(int *)(act + 0x430))-- > 0) {
                *(int *)(act + 0x33C) = 128;
            } else if (((int)(((WayState *)(act + 0x438))->flags >> 17) & 0xF) != 0) {
                *(int *)(act + 0x33C) = 255;
            }
        }
    } else {
        n = (int)(((WayState *)(act + 0x438))->flags >> 17) & 0xF;
        if (n > 0) {
            ((WayState *)(act + 0x438))->flags = (((WayState *)(act + 0x438))->flags & ~0x1E0000) |
                                                 ((long long)((n - 1) & 0xF) << 17);
            if (((int)(((WayState *)(act + 0x438))->flags >> 17) & 0xF) == 0) {
                goto restart;
            }
            *(float *)(act + 0x34C) = 1.0f;
            *(float *)(act + 0x3E0) = *(float *)(act + 0x420);
            *(float *)(act + 0x3E4) = *(float *)(act + 0x424);
            *(float *)(act + 0x3E8) = *(float *)(act + 0x428);
            node[0] = *(float *)(act + 0x3E0);
            node[1] = *(float *)(act + 0x3E4);
            node[2] = *(float *)(act + 0x3E8);
            return 1;
        }
    }
    switch (((WayState *)(act + 0x438))->st[1]) {
    case 0:
        if (self == (char *)D_00639EA8) {
            SuspendGirlPullupFloorBox();
        }
        *(short *)(act + 0x3F0) = 1;
        way = act + 0x360;
        w = GetWay_next(way, pos);
        if (w != 0) {
            if (*(int *)(act + 0x400) != w) {
                if (*(int *)(act + 0x400) != 0) {
                    if (*(int *)(act + 0x3C4) <= 0) {
                        *(short *)(act + 0x3F0) = 1;
                    }
                }
                *(int *)(act + 0x400) = w;
            }
        }
        if (self == (char *)D_00639EA8) {
            ResumeGirlPullupFloorBox();
        }
        *(float *)(act + 0x3E0) = *(float *)(act + 0x3B0);
        *(float *)(act + 0x3E4) = *(float *)(act + 0x3B4);
        *(float *)(act + 0x3E8) = *(float *)(act + 0x3B8);
        if (self == (char *)D_00639EA4 || self == (char *)D_00639EA8) {
            DetourCheck(self, (float *)(act + 0x3E0));
        }
        if (*(int *)(act + 0x39C) == 0 &&
            WayMove_CheckCollis(pos, goal, *(void **)(act + 0x404), 0) == 0 &&
            *(int *)(act + 0x34) != 0x26) {
            ((WayState *)(act + 0x438))->st[1] = 1;
            DeleteGuideWay((WVTObj *)way);
            *(short *)(act + 0x3F0) = 2;
        }
        break;
    case 1: {
        int chk = 1;

        *(short *)(act + 0x3F0) = 2;
        ok = WayMove_CheckCollis(pos, goal, *(void **)(act + 0x404), 0);
        if (stage_no != 22) {
            chk = 0;
        }
        if (stage_no == 8 || chk != 0) {
            if (self == (char *)D_00639EA8 && D_0063A6B4 != 0 &&
                *(int *)((char *)D_0063A6B4 + 0xC) == 17 &&
                IsThisBoxTruck((char *)D_0063A6B4) != 7 &&
                _DistSqGV(goal, test_CURRENTROOT(D_0063A6B4)) < 40000.0f &&
                _DistxzSqGV(pos, test_CURRENTROOT(D_0063A6B4)) < 40000.0f) {
                ok = 0;
            }
        }
        if (e != 0 && ok != 0) {
            float d = pos[1] - goal[1];

            if (d < 0.0f ? -d > 100.0f : d > 100.0f) {
                if (goal[1] < pos[1]) {
                    float p0[4];
                    float p1[4];
                    float dir[4];

                    p0[0] = pos[0];
                    p0[2] = pos[2];
                    p0[1] = pos[1] - 150.0f;
                    _OrientXZGV(dir, goal, pos);
                    sceVu0ScaleVector(dir, dir, 200.0f);
                    sceVu0AddVector(p1, p0, dir);
                    if (ACTCheckCollis_WAY(p0, p1, 10.0f, 0, 0) == 0) {
                        ok = 0;
                    }
                }
            }
        }
        if (ok != 0) {
            goto restart;
        }
        _OrientXZGV((float *)(act + 0x3E0), goal, pos);
        if (self == (char *)D_00639EA4 || self == (char *)D_00639EA8) {
            DetourCheck(self, (float *)(act + 0x3E0));
        }
        *(float *)(act + 0x3F8) = _DistxzGV(goal, pos);
        *(float *)(act + 0x3FC) = goal[1] - pos[1];
        if (*(float *)(act + 0x3F8) < 200.0f) {
            *(long long *)(act + 0x3F0) |= 0x40000;
        }
        break;
    }
    }
    if (*(int *)(act + 0x3A4) == 0 || (stage_no == 22 && *(int *)(self + 0xC) == 4 &&
                                       ((int)(*(long long *)(act + 0x3F0) >> 17) & 1) != 0)) {
        goto done;
    }
restart:
    *(short *)(act + 0x3F0) = 3;
    r = ACTWayMove_BeginDetail(self, pos, goal, *(void **)(act + 0x404), 0, d);
    if (r == 0) {
        return 0;
    }
done:
    return 1;
}

int ACTWayExec_Position(char *self, int a1, float *dir, float speed, int a3)
{
    /* listing lines 677/678 carry every flag test inside this function's own
       span: an inline function nested in the body, reading the enclosing a3
       (which is what gives a3 its frame home at sp+0 and the two reloads) */
    inline unsigned char way_flag(int mask)
    {
        if (a3 & mask) {
            return 1;
        }
        return 0;
    }

    char *w = *(char **)(self + 0x164);
    char *node;
    float d2[4];
    float p2[4];
    float v[4];
    float pos[4];
    float f;

    if (way_flag(1)) {
        sceVu0ScaleVector(v, dir, -1.0f);
    } else {
        v[0] = dir[0];
        v[1] = dir[1];
        v[2] = dir[2];
    }
    if (way_flag(4)) {
        GetRootProjectionPosOfGObj(pos, (void *)a1);
        if (WayMove_CheckCollis(pos, v, 0, 0)) {
            v[0] = pos[0];
            v[1] = pos[1];
            v[2] = pos[2];
        }
    }
    d2[0] = v[0];
    d2[1] = v[1];
    d2[2] = v[2];
    GetRootProjectionPosOfGObj(p2, self);
    if (ACTWayMove_BeginDetail(self, p2, d2, (void *)a1, 0, 0) == 0) {
        return 0;
    }
    node = w + 0x120;
    for (;;) {
        d2[0] = v[0];
        d2[1] = v[1];
        d2[2] = v[2];
        GetRootProjectionPosOfGObj(p2, self);
        if (ACTWayMove_NextDetail(self, (float *)node, d2, 0, 0) == 0) {
            return 0;
        }
        f = *(float *)(w + 0x3F8);
        *(float *)(w + 0x120) = *(float *)(w + 0x3E0);
        *(float *)(w + 0x124) = *(float *)(w + 0x3E4);
        *(float *)(w + 0x128) = *(float *)(w + 0x3E8);
        if (f < speed) {
            if (*(float *)(w + 0x3FC) < 100.0f) {
                return 1;
            }
        }
        if (f < 200.0f || way_flag(2)) {
            *(float *)(w + 0x34C) = 0.5f;
        } else {
            *(float *)(w + 0x34C) = 1.0f;
        }
        _ACTWait(1);
    }
}

int ACTWay_IsMustWalkFromWay(char *a0)
{
    char *w = *(char **)(*(char **)(a0 + 0x164) + 0x380);
    float d;

    if (w == 0) {
        return 0;
    }
    d = *(float *)(w + 0x2C);
    if (d != 0.0f) {
        return _DistxzSqGV(w + 0x10, test_CURRENTROOT()) < d * d;
    }
    return 0;
}

void ACTWay_SetBeginPositionIllegal(char *a0)
{
    char *p = *(char **)(a0 + 0x164);
    *(long long *)(p + 0x438) |= 0x200000;
}
