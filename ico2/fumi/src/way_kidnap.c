#include "common.h"
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

extern int D_0063BD64;
extern int D_0063BD60;
extern int D_0063BD68;

static inline void ClearWpPos(void)
{
    if (D_0063BD64 == 0) {
        D_0063BD60 = 0;
    }
}

typedef struct WayPoint {
    char unk00[0x10];
    float pos[4];
    char unk20[0x10];
    int f30;
} WayPoint;

typedef struct WpPosEntry {
    WayPoint *wp;
    float len;
} WpPosEntry;

/* .bss, owned by way_kidnap.o and reached only from this file (MAIN.MAP line
   7761 gives the member, 0x11E8 in its January link, and names no symbol in
   it), in the ROM's run order 0x728610..0x729B60.  The names are ours.
   searchNodes is the node list WayPointWithRangeFromPos2 grows while it walks
   the way graph and edgeDone its per-edge visited flags, each sized by the
   count the search clears; wpPosVec and wpPosInfo are the positions and the
   (waypoint, length) pairs add_wp_pos appends, CopyWpPos reading at most 128.
   WHAT THE BYTES PIN: the four start offsets (0x0, 0x450, 0x4B0, 0xCB0) and
   the run's end to 8 bytes; 275 or 276 node slots and 94 or 96 flags lay
   out the same, but the entry table's count is pinned by the run's end (see
   its own comment). */
static struct WpNode *searchNodes[275];

static char edgeDone[94];

static float wpPosVec[128][4];

/* 276 entries, not the loops' 275: the ROM's run ends at 0x729B60 where
   way_tool's .bss begins, and 275 leaves it 8 bytes early (measured at the
   SHA-1 gate, 2026-09-25). */
static WpPosEntry wpPosInfo[276];

void add_wp_pos(WayPoint *wp, float *pos, float len)
{
    if (D_0063BD64) {
        return;
    }
    fzShowV(pos);

    wpPosInfo[D_0063BD60].wp = wp;
    wpPosInfo[D_0063BD60].len = len;
    sceVu0CopyVector(wpPosVec[D_0063BD60++], pos);
}

/* way_kidnap.c:109 and 117-127 in the listing: public inlines, so gcc defers
   their bodies to the end of the object (the ROM has them after
   NearestEnemyFromGirl, in the order way_kidnap.h declares them) while the
   string CopyWpPos prints is entered here, first in the TU's .rodata. */
inline int NumOfWpPos(void)
{
    return D_0063BD60;
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

typedef struct WpNode {
    int f0;
    int _4;
    struct WpNode *f8;
    struct WpNode *fC;
    float pos[4];
    int f20;
    int f24;
    int _28;
    int _2C;
    int f30;
    int _34[3];
} WpNode;

typedef struct WayWork {
    char unk00[0x2C];
    WpNode *f2C;
    char unk30[0x14];
    int f44;
    char unk48[0x1C];
    int f64;
    char unk68[0x8];
    int f70;
    char unk74[0xC];
} WayWork;

/* kept local: this TU's uses of _GetLength do not fit the prototype in Matrix.h */
extern float _GetLength(float *a, float *b);

float WayLengthOfPos_Pos(float *pos0, float *pos1)
{
    float cur[4];
    float dst[4];
    WayWork w;
    WayPoint *wp;
    WayPoint *wp0;
    WayPoint *wp1;
    float len;
    int i;

    len = 0.0f;

    w.f64 = -1;
    w.f2C = 0;
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
    if (wp == wp1) {
        goto found;
    }
    if (w.f70 == 2) {
        goto fail;
    }
    if (D_0063BD68 == 0 && w.f70 == 1) {
        goto fail;
    }

    len += _GetLength(cur, wp->pos);
    add_wp_pos(wp0, wp0->pos, len);

    sceVu0CopyVector(cur, wp->pos);

    for (i = 0;;) {
        if (++i >= 101) {
            goto fail;
        }
        wp = GetWay_next(&w, cur);

        if (w.f44 != 0) {
            if (wp == wp1) {
                goto found;
            }
            wp = GetWay_begin(dst, &w, cur);
            if (wp == 0) {
                goto fail;
            }
            if (wp == wp1) {
                goto found;
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

    return len;
}

/* way_kidnap.c:207-212 and 215-219: public inlines, deferred to the end of the
   object like NumOfWpPos; NearestEnemyFromGirl inlines the pair. */
inline float WayLengthOfGObj_Pos(void *obj, float *pos)
{
    float buf[4];
    if (obj == 0) {
        return -1.0f;
    }
    GetRootPosition(buf, obj);
    return WayLengthOfPos_Pos(buf, pos);
}

inline float WayLengthOfGObj_GObj(void *obj0, void *obj1)
{
    float pos[4];
    if (obj1 == 0) {
        return -1.0f;
    }
    GetRootPosition(pos, obj1);
    return WayLengthOfGObj_Pos(obj0, pos);
}

/* census wpsort_compfnc (way_kidnap.c:226-228), a file static: `static` keeps
   its ELF symbol local so it cannot collide with the ico2/fumi/src/way_util
   global of the same name.  Only qsort takes its address, so gcc defers the
   inline body and emits it last, after the header's public inlines. */
static inline int wpsort_compfnc(float *a, float *b)
{
    if (a[1] < b[1])
        return -1;
    if (b[1] < a[1])
        return 1;
    return 0;
}

static inline void WayRangeSearch(float *pos, float range, WpPosEntry *e, int limit, int chk)
{
    D_0063BD68 = limit;
    ClearWpPos();

    for (e->wp = WayPoint_begin(); e->wp != 0; e->wp = WayPoint_next(e->wp)) {
        if (range <= _GetLength(pos, e->wp->pos)) {
            continue;
        }
        D_0063BD64 = 1;
        e->len = WayLengthOfPos_Pos(pos, e->wp->pos);
        D_0063BD64 = 0;
        if (e->len < 0.0f) {
            continue;
        }
        if (chk && e->wp->f30 != 0) {
            continue;
        }
        add_wp_pos(e->wp, e->wp->pos, e->len);
    }
    D_0063BD68 = 0;
}

int WayPointWithRangeFromPos(float *pos, int mode, float range)
{
    WpPosEntry e;
    int n;
    int i;

    switch (mode) {
    case 0:
    default:
        WayRangeSearch(pos, range, &e, 0, 0);
        break;

    case 1:
        WayRangeSearch(pos, range, &e, 0, 1);

        n = NumOfWpPos();
        qsort(wpPosInfo, n, 8, wpsort_compfnc);
        for (i = 0; i < n; i++) {
            sceVu0CopyVector(wpPosVec[i], wpPosInfo[i].wp->pos);
        }
        break;

    case 2:
        WayRangeSearch(pos, range, &e, 1, 0);
        break;

    case 3:
        WayRangeSearch(pos, range, &e, 1, 1);

        n = NumOfWpPos();
        qsort(wpPosInfo, n, 8, wpsort_compfnc);
        for (i = 0; i < n; i++) {
            sceVu0CopyVector(wpPosVec[i], wpPosInfo[i].wp->pos);
        }
        break;
    }

    return NumOfWpPos();
}

extern WpNode D_004F31E0[];

/* One entry of the way-edge table: the pair of waypoint nodes an edge joins
   (f8/fC), the two node indices it spans (f20[]) and its enable flags. */
typedef struct WayEdge {
    int f0;
    int _4;
    WpNode *f8;
    WpNode *fC;
    int _10[2];
    int f18;
    int _1C;
    int f20[2];
    int f28;
    int _2C[2];
} WayEdge;

extern WayEdge D_004F1EC0[];
extern float D_0063BD6C[];
/* kept local: this TU's uses of _SubVector do not fit the prototype in Matrix.h */
extern void _SubVector(float *dst, float *a, float *b);
/* kept local: this TU's uses of _InnerProduct do not fit the prototype in Matrix.h */
extern float _InnerProduct(float *a, float *b);

static inline WpNode *SearchOpenNode(WpNode *start)
{
    WpNode *p;
    int wrapped;
    int hit;

    wrapped = 0;
    hit = 0;

    p = start;
    while (p != 0) {
        if (p->f30 == 0) {
            hit = 1;
            break;
        }
        p = p->fC;
        if (p == start) {
            wrapped = 1;
            break;
        }
    }
    if (hit == 0 && wrapped == 0) {
        p = start;
        while (p != 0) {
            if (p->f30 == 0) {
                hit = 1;
                break;
            }
            p = p->f8;
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

int WayPointWithRangeFromPos2(float *pos, WayWork *w, float *dst, int chk)
{
    float v[4];
    WpNode *found;
    WpNode *cur;
    /* RULING-VESTIGIAL-EXCEPTION (supervisor 2026-09-24, under the user's
       2026-09-21 standard for dead assignments the ROM proves).
       Deleted-code window (c3p75/c3p76, for the landing audit): the
       initialiser is dead (edge is set at the top of every pass of the
       loop before any read) and flow deletes it. What the bytes pin: a
       second set of edge before cse1, since alias.c record_set then
       forgets edge's base and the char store edgeDone[k] = 1 kills the
       edge->f20[j] load, which the bridge arm reloads at 0x2157E0; without
       it the function is 354 words. What they cannot pin: the statement.
       The declaration form follows this programmer's pointer locals
       initialised to 0 (`void *nearest = 0;` in NearestEnemyFromGirl here,
       `HandModeCmd *hmc = 0;` in act-game.c, `char *gen = 0;` in
       commonact.c). */
    WayEdge *edge = 0;
    WpNode *nearest;
    float best;
    float d;
    int n = 0;
    int i;
    int j;
    int k;

    for (i = 0; i < 275; i++) {
        searchNodes[i] = 0;
    }
    for (k = 0; k < 94; k++) {
        edgeDone[k] = 0;
    }
    GetWay_begin(pos, w, pos);
    found = 0;
    cur = w->f2C;
    if (cur == 0) {
        /* my own WAY was not found */
        debug_StdPrintfDummy("自分のWAYが見付からなかった");
        goto ret;
    }
    edgeDone[cur->f20] = 1;
    searchNodes[n++] = cur;

    while (1) {
        for (i = 0; i < n; i++) {
            if (searchNodes[i] != 0) {
                goto found;
            }
        }
        break;
    found:
        cur = searchNodes[i];
        edge = &D_004F1EC0[cur->f20];
        debug_StdPrintfDummy("srh wp %p group id %d %d\n", cur, cur->f20, i);
        searchNodes[i] = 0;
        debug_StdPrintfDummy("active %d\n", edge->f28);
        if (edge->f28 != 0) {
            /* RULING-VESTIGIAL-EXCEPTION (supervisor 2026-09-24, under the
               user's 2026-09-21 standard for dead assignments the ROM proves).
               Deleted-code window (c3p76): k is the
               index of this edge in the table, as everywhere below, and the
               value is dead (the next read of k follows its reassignment in
               both loops) so flow deletes it; listing rows 427-429 carry no
               code. What the bytes pin: a read of the table base in this arm,
               on cse1's path from the found block, so the base register row
               419 builds is used outside its block when loop.c runs; the
               second loop pass then leaves that lo_sum in the block (scan_loop's
               maybe_never guard) and hoists only the high part, local-alloc
               cannot tie the two, and combine keeps mult + addu where a
               hoisted base gives an EE madd (r5900_madd_profitable_p). What
               they cannot pin: the statement's text. */
            k = edge - D_004F1EC0;
            found = SearchOpenNode(cur);
        }
        if (found != 0) {
            break;
        }
        if (edge->f18 == 0) {
            for (k = 0; k < 94; k++) {
                if (D_004F1EC0[k].f0 == 0) {
                    continue;
                }
                if (D_004F1EC0[k].f18 == 0) {
                    continue;
                }
                for (j = 0; j < 2; j++) {
                    if (cur->f20 != ((WpNode *)D_004F31E0)[D_004F1EC0[k].f20[j]].f20) {
                        continue;
                    }
                    if (edgeDone[k] != 0) {
                        continue;
                    }
                    edgeDone[k] = 1;
                    if (chk && D_004F1EC0[k].f28 == 0) {
                        continue;
                    }
                    if (j == 0) {
                        searchNodes[n++] = D_004F1EC0[k].f8;
                    } else {
                        searchNodes[n++] = D_004F1EC0[k].fC;
                    }
                    debug_StdPrintfDummy("add no bridge wp %p %d %d\n", searchNodes[n - 1], j, k);
                }
            }
        } else {
            for (j = 0; j < 2; j++) {
                k = ((WpNode *)D_004F31E0)[edge->f20[j]].f20;
                if (edgeDone[k] != 0) {
                    continue;
                }
                edgeDone[k] = 1;
                if (chk && D_004F1EC0[k].f28 == 0) {
                    continue;
                }
                searchNodes[n++] = &D_004F31E0[edge->f20[j]];
                debug_StdPrintfDummy("add bridge wp %p %d %d\n", searchNodes[n - 1], j, k);
            }
        }
    }

ret:
    if (found == 0 && chk) {
        return 0;
    }
    if (found == 0) {
        nearest = 0;
        best = D_0063BD6C[0];
        /* not found, so search every WAYPOOINT for the nearest point of the
           active group that allows a nest */
        debug_StdPrintfDummy(
            "見付からないので全WAYPOOINTから アクティブグループで巣許可の一番近いポイントを検索");
        for (i = 0; i < 275; i++) {
            cur = &D_004F31E0[i];
            if (cur->f0 == 0 || cur->f30 != 0 || D_004F1EC0[cur->f20].f28 == 0) {
                continue;
            }
            _SubVector(v, pos, cur->pos);
            d = _InnerProduct(v, v);
            if (d < best) {
                nearest = cur;
                best = d;
            }
        }
        if (nearest != 0) {
            sceVu0CopyVector(dst, cur->pos);
            return 1;
        }
        /* no point of the active group allows a nest */
        debug_StdPrintfDummy("アクティブグループの巣許可のポイントがみつかりません");
        return 0;
    }
    sceVu0CopyVector(dst, found->pos);
    return 1;
}

/* way_kidnap.c:522-526: a public inline, deferred like the others. */
inline int WayPointWithRangeFromGObj(void *obj, float f)
{
    float pos[4];
    if (obj == 0) {
        return -1;
    }
    GetRootPosition(pos, obj);
    return WayPointWithRangeFromPos(pos, 0, f);
}

extern void *D_00639EA8;

void *NearestEnemyFromGirl(float *len)
{
    float min;
    void *nearest = 0;
    void *obj;
    float d;

    obj = isysGObjSearchFromObjKindID_begin(4);
    min = 1.0e10f;

    while (obj != 0 && !isEnemyKidnapEnable(obj))
        obj = isysGObjSearchFromObjKindID_next(obj);

    while (obj != 0) {
        d = WayLengthOfGObj_GObj(D_00639EA8, obj);

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
