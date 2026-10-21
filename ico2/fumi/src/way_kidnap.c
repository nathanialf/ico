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
INCLUDE_ASM_LIT(CopyWpPos);

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
/* a file-static wpsort_compfnc, distinct from the way_util global of the same
   name; only qsort takes its address, so its body is emitted last, after the
   header's public inlines. */
static inline void WayRangeSearch(float *pos, float range, WpPosEntry *e, int limit,
                                  int chk) /* derived name */
{
    wayRangeLimit = limit;
    ClearWpPos();

    for (e->wp = WayPoint_begin(); e->wp != 0; e->wp = WayPoint_next(e->wp)) {
        if (range <= _GetLength(pos, e->wp->pos)) {
            continue;
        }
        wpPosLock = 1;
        e->len = WayLengthOfPos_Pos(pos, e->wp->pos);
        wpPosLock = 0;
        if (e->len < 0.0f) {
            continue;
        }
        if (chk && e->wp->bridgeEnd != 0) {
            continue;
        }
        add_wp_pos(e->wp, e->wp->pos, e->len);
    }
    wayRangeLimit = 0;
}

int WayPointWithRangeFromPos(float *pos, float range, int mode);

INCLUDE_ASM(WayPointWithRangeFromPos);

/* a public inline, deferred like the others */
INCLUDE_ASM(NearestEnemyFromGirl);

INCLUDE_ASM(NumOfWpPos);

INCLUDE_ASM(CopyWpPos);

INCLUDE_ASM(WayLengthOfGObj_Pos);

INCLUDE_ASM(WayLengthOfGObj_GObj);

INCLUDE_ASM(WayPointWithRangeFromGObj);

INCLUDE_ASM(wpsort_compfnc_way_kidnap);
