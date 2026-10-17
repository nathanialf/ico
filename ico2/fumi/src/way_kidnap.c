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

static void add_wp_pos(WayPoint *wp, float *pos, float len);

INCLUDE_ASM(add_wp_pos);

/* public inlines, deferred to the end of the object in the order
   way_kidnap.h declares them; the string CopyWpPos prints comes first in the
   TU's .rodata. */
INCLUDE_ASM_LIT(CopyWpPos);

float WayLengthOfPos_Pos(float *pos0, float *pos1);

INCLUDE_ASM(WayLengthOfPos_Pos);

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

static inline WayPoint *SearchOpenNode(WayPoint *start) /* derived name */
{
    WayPoint *p;
    int wrapped;
    int hit;

    wrapped = 0;
    hit = 0;

    p = start;
    while (p != 0) {
        if (p->bridgeEnd == 0) {
            hit = 1;
            break;
        }
        p = p->next;
        if (p == start) {
            wrapped = 1;
            break;
        }
    }
    if (hit == 0 && wrapped == 0) {
        p = start;
        while (p != 0) {
            if (p->bridgeEnd == 0) {
                hit = 1;
                break;
            }
            p = p->prev;
            if (p == start) {
                break;
            }
        }
    }
    if (hit == 0) {
        p = 0;
    }
    return p;
}

/* the DEBUG build's trace of the edge the search opens, by its table index */
static __inline__ void wayKidnapDebugEdge(int k) /* derived name */
{
#ifdef DEBUG
    scePrintf("open edge %d\n", k);
#endif
}

/* a public inline, deferred like the others */
INCLUDE_ASM(NearestEnemyFromGirl);

INCLUDE_ASM(NumOfWpPos);

INCLUDE_ASM(CopyWpPos);

INCLUDE_ASM(WayLengthOfGObj_Pos);

INCLUDE_ASM(WayLengthOfGObj_GObj);

INCLUDE_ASM(WayPointWithRangeFromGObj);

INCLUDE_ASM(wpsort_compfnc_way_kidnap);
