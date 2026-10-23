#include "way_kidnap.h"
#include "debug.h"
#include "gobj.h"
#include "enemy_act.h"
#include "fuzio.h"
#include "way_llf.h"
#include "way_sys.h"
#include "way_util.h"
#include "geometryManager.h"
#include <libvu0.h>
#include <stdlib.h>
#include "Matrix.h"
#include "main.h"
#include "include_asm.h"

/* a zero word first in the TU's .sdata in this build, which no word of
   .text addresses (the stub-owned row D_0067B250) */
INCLUDE_ASM(D_0067B250);

/* the count of positions add_wp_pos has collected, the flag that stops it
   while WayRangeSearch measures a path, and the range search's limit mode */
static int wpPosCount = 0; /* derived name */

static int wpPosLock = 0; /* derived name */

static int wayRangeLimit = 0; /* derived name */

static inline void ClearWpPos(void) /* derived name */
{
    if (wpPosLock == 0) {
        wpPosCount = 0;
    }
}

typedef struct WpPosEntry { /* field names derived */
    WayPoint *wp;
    float len;
} WpPosEntry; /* derived name */

/* wpPosVec and wpPosInfo are the positions and the (waypoint, length) pairs
   add_wp_pos appends, CopyWpPos reading at most 128 (the positions are VU0
   vectors: the run opens 16-aligned at 0x75F3E0).  This build has no search
   node list or edge flags before them. */
static sceVu0FVECTOR wpPosVec[128]; /* derived name */

/* one entry per way point (this build's 192: the run ends at 0x7601E0) */
static WpPosEntry wpPosInfo[192]; /* derived name */

/* The DEBUG build checks the goal entry before the sorted copy (below);
   retail builds the check as 0, as enemy_act.c's ENEMY_DEBUG_HOLD. */
#ifdef DEBUG
#define WP_GOAL_CHECK 1 /* derived name */
#else
#define WP_GOAL_CHECK 0 /* derived name */
#endif

static void add_wp_pos(WayPoint *wp, float *pos, float len)
{
    if (wpPosLock) {
        return;
    }
    fzShowV(pos);

    wpPosInfo[wpPosCount].wp = wp;
    sceVu0CopyVector(wpPosVec[wpPosCount++], pos);
}

/* public inlines, deferred to the end of the object in the order
   way_kidnap.h declares them; the string CopyWpPos prints comes first in the
   TU's .rodata. */
inline int NumOfWpPos(void)
{
    return wpPosCount;
}

inline int CopyWpPos(float dst[][4], int from, int to)
{
    int j = 0;
    if (from < 0) {
        return 1;
    }

    for (; from <= to && from < 128; from++, j++) {
        debug_StdPrintfDummy("index %d\n", j);
        sceVu0CopyVector(dst[j], wpPosVec[from]);
    }

    return 0;
}

float WayLengthOfPos_Pos(float *pos0, float *pos1)
{
    float cur[4];
    float dst[4];
    WVTObj w;
    WayPoint *wp;
    WayPoint *wp0;
    WayPoint *wp1;
    float len;
    int i;

    len = 0.0f;

    w.guideFirst = -1;
    w.nearWp = 0;
    sceVu0CopyVector(cur, pos0);
    sceVu0CopyVector(dst, pos1);
    wp0 = visible_waypoint_of_all(cur);
    wp1 = visible_waypoint_of_all(dst);

    ClearWpPos();
    add_wp_pos(0, cur, len);

    wp = GetWay_begin(dst, &w, cur);
    if (wp == 0) {
        goto fail;
    }
    if (w.pathKind == 2) {
        goto fail;
    }
    if (wayRangeLimit == 0 && w.pathKind == 1) {
        goto fail;
    }

    len += _GetLength(cur, wp->pos);
    add_wp_pos(wp0, wp0->pos, len);

    sceVu0CopyVector(cur, wp->pos);

    for (i = 0;;) {
        if (++i >= 101) {
            goto fail;
        }
        if (wp == wp1) {
            goto found;
        }
        wp = GetWay_next(&w, cur);

        if (w.reached != 0) {
            wp = GetWay_begin(dst, &w, cur);
            if (wp == 0) {
                goto fail;
            }

            sceVu0CopyVector(cur, wp->pos);
        } else {
            len += _GetLength(cur, wp->pos);

            add_wp_pos(wp, wp->pos, len);
            sceVu0CopyVector(cur, wp->pos);
        }
    }

fail:
    ClearWpPos();

    return -1.0f;

found:
    len += _GetLength(pos1, wp1->pos);
    add_wp_pos(0, dst, len);
    if (dst[0] < -200.0f) {
        debug_StdPrintfDummy("cannot_reach:%d\n", w.flag6C);
        debug_StdPrintfDummy("cannot_reach_kidnap:%d\n", w.pathKind);
    }

    return len;
}

/* public inlines, deferred to the end of the object like NumOfWpPos;
   NearestEnemyFromGirl inlines the pair. */
inline float WayLengthOfGObj_Pos(GObj *obj, float *pos)
{
    float buf[4];
    if (obj == 0) {
        return -1.0f;
    }
    GetRootPosition(buf, obj);
    return WayLengthOfPos_Pos(buf, pos);
}

inline float WayLengthOfGObj_GObj(GObj *obj0, GObj *obj1)
{
    float pos[4];
    if (obj1 == 0) {
        return -1.0f;
    }
    GetRootPosition(pos, obj1);
    return WayLengthOfGObj_Pos(obj0, pos);
}

/* a file-static wpsort_compfnc, distinct from the way_util global of the same
   name; only qsort takes its address, so its body is emitted last, after the
   header's public inlines. */
static inline int wpsort_compfnc(const void *a, const void *b)
{
    const WpPosEntry *ea = a;
    const WpPosEntry *eb = b;

    if (ea->len < eb->len)
        return -1;
    if (eb->len < ea->len)
        return 1;
    return 0;
}

int WayPointWithRangeFromPos(float *pos, float range, int mode)
{
    WpPosEntry e;
    int n;
    int i;

    inline void WayRangeSearch(float *pos, float range, int limit, int chk) /* derived name */
    {
        wayRangeLimit = limit;
        ClearWpPos();

        for (e.wp = WayPoint_begin(); e.wp != 0; e.wp = WayPoint_next(e.wp)) {
            if (range <= _GetLength(pos, e.wp->pos)) {
                continue;
            }
            wpPosLock = 1;
            e.len = WayLengthOfPos_Pos(pos, e.wp->pos);
            wpPosLock = 0;
            if (e.len < 0.0f) {
                continue;
            }
            if (chk && e.wp->bridgeEnd != 0) {
                continue;
            }
            add_wp_pos(e.wp, e.wp->pos, e.len);
        }
        wayRangeLimit = 0;
    }

    switch (mode) {
    case 0:
    default:
        WayRangeSearch(pos, range, 0, 0);
        break;

    case 1:
        WayRangeSearch(pos, range, 0, 1);

        n = NumOfWpPos();
        qsort(&wpPosInfo[1], n - 2, sizeof(WpPosEntry), wpsort_compfnc);
        i = 1;
        /* Drop the goal, the last entry, which has no way point (the start,
           entry 0, has none either: hence 1..n-2). The DEBUG build walks
           back to it past any entry after it; retail drops one entry. What
           the bytes pin: the decrement inside a loop with no exit test and
           no back edge (the loop notes weight n's allocation over i's, as
           the demo's s0/s1). What they cannot pin: the DEBUG test's text. */
        do {
            n--;
        } while (WP_GOAL_CHECK && n > 0 && wpPosInfo[n].wp != 0);
        for (; i < n; i++) {
            sceVu0CopyVector(wpPosVec[i], wpPosInfo[i].wp->pos);
        }
        break;

    case 2:
        WayRangeSearch(pos, range, 1, 0);
        break;

    case 3:
        WayRangeSearch(pos, range, 1, 1);

        n = NumOfWpPos();
        qsort(&wpPosInfo[1], n - 2, sizeof(WpPosEntry), wpsort_compfnc);
        i = 1;
        /* the goal, as in case 1 */
        do {
            n--;
        } while (WP_GOAL_CHECK && n > 0 && wpPosInfo[n].wp != 0);
        for (; i < n; i++) {
            sceVu0CopyVector(wpPosVec[i], wpPosInfo[i].wp->pos);
        }
        break;
    }

    return NumOfWpPos();
}

/* a public inline, deferred like the others */
inline int WayPointWithRangeFromGObj(GObj *obj, float f)
{
    float pos[4];
    if (obj == 0) {
        return -1;
    }
    GetRootPosition(pos, obj);
    return WayPointWithRangeFromPos(pos, f, 0);
}

GObj *NearestEnemyFromGirl(float *len)
{
    float min;
    GObj *nearest = 0;
    GObj *obj;
    float d;

    obj = isysGObjSearchFromObjKindID_begin(4);
    min = 1.0e10f;

    while (obj != 0 && !isEnemyKidnapEnable(obj))
        obj = isysGObjSearchFromObjKindID_next(obj);

    while (obj != 0) {
        d = WayLengthOfGObj_GObj(girlGObj, obj);

        if (d >= 0.0f && d < min) {
            min = d;
            nearest = obj;
        }

        do {
            obj = isysGObjSearchFromObjKindID_next(obj);
        } while (obj != 0 && !isEnemyKidnapEnable(obj));
    }
    *len = min;
    return nearest;
}
