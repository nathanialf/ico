#include "main.h"
#include "camera-editor.h"
#include "motionManager2.h"
#include "act-game.h"
#include "act-way.h"
#include "act.h"
#include "gobj_process.h"
#include "way_sys.h"
#include "waySystemManager.h"
#include <libvu0.h>
#include "debug.h"
#include "girl_act.h"
#include "box.h"
#include "commonact.h"
#include "gv.h"
#include "motionOrientManager.h"

static inline unsigned char WayMove_CheckCollis(float *p0, float *p1, void *actor, void *posout)
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
    return ACTCheckCollis_WAY(10.0f, a, b, actor, posout);
}

inline int ACTWayMove_BeginDetail(GObj *self, float *goal, float *from, void *tgt, void *e)
{
    WVTObj way;
    Act *act = GOBJ_ACT(self);
    WVTObj *home;
    WVTObj *wp;
    int ret = 0;

    home = &act->way;
    way = *home;
    wp = &way;
    act->wayFlags &= ~0x10000;
    if (GetWay_begin(from, wp, goal) != 0) {
        act->wayState.w.st[1] = 0;
        if (wp->flag3C == 0) {
            if (WayMove_CheckCollis(goal, from, tgt, e) == 0) {
                act->wayState.w.st[1] = 1;
                DeleteGuideWay(wp);
                ret = 3;
            } else {
                ret = 2;
            }
        } else {
            ret = 1;
        }
        *home = way;
        act->wayLast = 0;
        *(int *)((char *)act + 0x3F4) = (int)tgt;
        *(float *)((char *)act + 0x400) = from[0];
        *(float *)((char *)act + 0x404) = from[1];
        *(float *)((char *)act + 0x408) = from[2];
        act->wayState.w.st[0] = 1;
    } else {
        act->wayState.w.st[0] = 0;
    }
    act->wayState.flags &= ~0x1000000000000LL;
    act->wayState.flags &= ~0x1E000000000000LL;
    act->wayState.w.wait = 0;
    return ret;
}

/* the 0x20-byte way-step record the actor keeps at act + 0x3D0: the step
   direction, the 64-bit way state word and the two distances to the goal */
typedef struct {     /* field names derived */
    float dir[4];    /* 0x00 */
    long long state; /* 0x10 */
    float dist;      /* 0x18 */
    float dy;        /* 0x1C */
} WayStep;           /* derived name */

/* the one template act-way.o keeps in .data in this build: the cleared
   way-step record (its two distances start at the largest float) */
static WayStep wayStepClear = {
    {0.0f, 0.0f, 0.0f, 0.0f}, 0, 3.4028235e38f, 3.4028235e38f}; /* derived name */

int ACTWayMove_NextDetail(GObj *self, float *node, float *goal)
{
    float pos[4];
    Act *act = GOBJ_ACT(self);
    WVTObj *way;
    int w;
    WayPoint *wp;
    int r;
    unsigned char ok;
    int n;

    *(WayStep *)((char *)act + 0x3D0) = wayStepClear;
    act->wayNodeX = node[0];
    act->wayNodeY = node[1];
    act->wayNodeZ = node[2];
    if (act->wayState.w.st[0] == 0) {
        /* EUC-JP, "there is no route" */
        debug_StdPrintfDummy("ルートがありません\n");
    }
    GetRootProjectionPosOfGObj(pos, self);
    if (((int)(act->wayState.flags >> 48) & 1) == 0) {
        if (_DistGV(goal, (char *)act + 0x400) > 300.0f) {
            if (((int)(act->wayState.flags >> 49) & 0xF) == 0) {
                if (act->actMode != 38) {
                    w = ACTWayMove_BeginDetail(self, pos, goal, *(void **)((char *)act + 0x3F4), 0);
                    act->wayFlags |= 0x20000;
                    if (w == 0) {
                        return 0;
                    }
                }
            }
        }
    }
    if (act->way.flag6C != 0) {
        if (act->way.chk.start != 0 && _DistSqGV(act->way.chk.start->pos, pos) < 10000.0f) {
            float d = pos[1] - act->way.chk.start->pos[1];

            if (d < 0.0f ? -d < 150.0f : d < 150.0f) {
                act->wayFlags |= 0x10000;
            }
        }
    }
    if (act->actMode == 38) {
        float v0[4];
        float v1[4];

        {
            sceVu0CopyVector(v0, act->way.nrm);
            sceVu0CopyVector(v1, (float *)((char *)act + 0x520));
            v0[1] = v1[1] = 0.0f;
            if (sceVu0InnerProduct(v0, v1) > 0.0f) {
                act->stick.y = 255;
            } else {
                act->stick.y = 0;
            }
            act->stick.mag = 1.0f;
            act->wayState.w.st[1] = 0;
            if (self == girlGObj && goal[1] - *(float *)((char *)act + 0x404) > 150.0f &&
                pos[1] < goal[1]) {
                if (((int)(act->wayState.flags >> 49) & 0xF) == 0) {
                    act->wayState.w.wait = (60 - systemStatus[0] * 10) / systemStatus[1] * 90 / 60;
                }
                act->wayState.flags =
                    (act->wayState.flags & ~0x1E000000000000LL) | 0x4000000000000LL;
                act->wayDetailX = *(float *)((char *)act + 0x520);
                act->wayDetailY = *(float *)((char *)act + 0x524);
                act->wayDetailZ = *(float *)((char *)act + 0x528);
            }
            if (act->wayState.w.wait-- > 0) {
                act->stick.y = 128;
            } else if (((int)(act->wayState.flags >> 49) & 0xF) != 0) {
                act->stick.y = 255;
            }
        }
    } else {
        n = (int)(act->wayState.flags >> 49) & 0xF;
        if (n > 0) {
            act->wayState.flags =
                (act->wayState.flags & ~0x1E000000000000LL) | ((long long)((n - 1) & 0xF) << 49);
            if (((int)(act->wayState.flags >> 49) & 0xF) == 0) {
                goto restart;
            }
            act->stick.mag = 1.0f;
            act->wayNodeX = act->wayDetailX;
            act->wayNodeY = act->wayDetailY;
            act->wayNodeZ = act->wayDetailZ;
            node[0] = act->wayNodeX;
            node[1] = act->wayNodeY;
            node[2] = act->wayNodeZ;
            return 1;
        }
    }
    switch (act->wayState.w.st[1]) {
    case 0:
        *(short *)((char *)act + 0x3E0) = 1;
        way = &act->way;
        wp = GetWay_next(way, pos);
        if (wp != 0) {
            if (act->wayLast != wp) {
                if (act->wayLast != 0) {
                    if (act->way.guideFirst <= 0) {
                        *(short *)((char *)act + 0x3E0) = 1;
                    }
                }
                act->wayLast = wp;
            }
        }
        act->wayNodeX = act->way.nrm[0];
        act->wayNodeY = act->way.nrm[1];
        act->wayNodeZ = act->way.nrm[2];
        if (act->way.flag3C == 0 &&
            WayMove_CheckCollis(pos, goal, *(void **)((char *)act + 0x3F4), 0) == 0 &&
            act->actMode != 38) {
            act->wayState.w.st[1] = 1;
            DeleteGuideWay(way);
            *(short *)((char *)act + 0x3E0) = 2;
        }
        break;
    case 1:
        *(short *)((char *)act + 0x3E0) = 2;
        ok = WayMove_CheckCollis(pos, goal, *(void **)((char *)act + 0x3F4), 0);
        if (stage_no == 8) {
            if (self == girlGObj && wallGObj_ACTCheckCollis_WAY != 0 &&
                *(int *)((char *)wallGObj_ACTCheckCollis_WAY + 0xC) == 17 &&
                IsThisBoxTruck(wallGObj_ACTCheckCollis_WAY) != 7 &&
                _DistSqGV(goal, test_CURRENTROOT(wallGObj_ACTCheckCollis_WAY)) < 40000.0f &&
                _DistxzSqGV(pos, test_CURRENTROOT(wallGObj_ACTCheckCollis_WAY)) < 40000.0f) {
                ok = 0;
            }
        }
        if (ok != 0) {
            goto restart;
        }
        _OrientXZGV((float *)((char *)act + 0x3D0), goal, pos);
        act->wayGoalDist = _DistxzGV(goal, pos);
        act->wayGoalHeight = goal[1] - pos[1];
        break;
    }
    if (act->way.reached == 0) {
        goto done;
    }
restart:
    *(short *)((char *)act + 0x3E0) = 3;
    r = ACTWayMove_BeginDetail(self, pos, goal, *(void **)((char *)act + 0x3F4), 0);
    if (r == 0) {
        return 0;
    }
done:
    return 1;
}

int ACTWayExec_Position(GObj *self, int tgt, float *dir, float speed, int flags)
{
    /* an inline function nested in the body: whether flags has the mask's bits */
    inline unsigned char way_flag(int mask) /* derived name */
    {
        if (flags & mask) {
            return 1;
        }
        return 0;
    }

    Act *w = GOBJ_ACT(self);
    char *node;
    float d2[4];
    float p2[4];
    float v[4];
    float f;

    if (way_flag(1)) {
        sceVu0ScaleVector(v, dir, -1.0f);
    } else {
        v[0] = dir[0];
        v[1] = dir[1];
        v[2] = dir[2];
    }
    d2[0] = v[0];
    d2[1] = v[1];
    d2[2] = v[2];
    GetRootProjectionPosOfGObj(p2, self);
    if (ACTWayMove_BeginDetail(self, p2, d2, (void *)tgt, 0) == 0) {
        return 0;
    }
    node = (char *)w + 0x100;
    for (;;) {
        d2[0] = v[0];
        d2[1] = v[1];
        d2[2] = v[2];
        GetRootProjectionPosOfGObj(p2, self);
        if (ACTWayMove_NextDetail(self, (float *)node, d2) == 0) {
            return 0;
        }
        f = w->wayGoalDist;
        w->dir[0] = w->wayNodeX;
        w->dir[1] = w->wayNodeY;
        w->dir[2] = w->wayNodeZ;
        if (f < speed) {
            if (w->wayGoalHeight < 100.0f) {
                return 1;
            }
        }
        if (f < 200.0f || way_flag(2)) {
            w->stick.mag = 0.5f;
        } else {
            w->stick.mag = 1.0f;
        }
        _ACTWait(1);
    }
}

inline int ACTWay_IsMustWalkFromWay(GObj *self)
{
    WayPoint *w = GOBJ_ACT(self)->way.chk.cur;
    float d;

    d = w->float2C;
    if (d != 0.0f) {
        return _DistxzSqGV(w->pos, test_CURRENTROOT(self)) < d * d;
    }
    return 0;
}
