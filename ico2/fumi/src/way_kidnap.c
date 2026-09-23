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

extern WpPosEntry D_007292C0[];
extern float D_00728AC0[][4];

void add_wp_pos(WayPoint *wp, float *pos, float len)
{
    if (D_0063BD64) {
        return;
    }
    fzShowV(pos);

    D_007292C0[D_0063BD60].wp = wp;
    D_007292C0[D_0063BD60].len = len;
    sceVu0CopyVector(D_00728AC0[D_0063BD60++], pos);
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

static int wpsort_compfnc(float *a, float *b);

/* INTERIM: the PAL listing inlines the public NumOfWpPos into
 * WayPointWithRangeFromPos.  Its out-of-line definition keeps its own ROM slot
 * further down this TU (the tail still has asm members), so the call sites here
 * go through a stand-in with the identical body. */
static inline int numOfWpPos(void)
{
    return D_0063BD60;
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

        n = numOfWpPos();
        qsort(D_007292C0, n, 8, wpsort_compfnc);
        for (i = 0; i < n; i++) {
            sceVu0CopyVector(D_00728AC0[i], D_007292C0[i].wp->pos);
        }
        break;

    case 2:
        WayRangeSearch(pos, range, &e, 1, 0);
        break;

    case 3:
        WayRangeSearch(pos, range, &e, 1, 1);

        n = numOfWpPos();
        qsort(D_007292C0, n, 8, wpsort_compfnc);
        for (i = 0; i < n; i++) {
            sceVu0CopyVector(D_00728AC0[i], D_007292C0[i].wp->pos);
        }
        break;
    }

    return numOfWpPos();
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
extern WpNode *D_00728610[];
extern char D_00728A60[];
extern float D_0063BD6C[];
extern char D_00621D68[];
extern char D_00621D88[];
extern char D_00621DA8[];
extern char D_00621DB8[];
extern char D_00621DD8[];
extern char D_00621DF0[];
extern char D_00621E48[];
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
       forgets edge's base and the char store D_00728A60[k] = 1 kills the
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
        D_00728610[i] = 0;
    }
    for (k = 0; k < 94; k++) {
        D_00728A60[k] = 0;
    }
    GetWay_begin(pos, w, pos);
    found = 0;
    cur = w->f2C;
    if (cur == 0) {
        debug_StdPrintfDummy(D_00621D68);
        goto ret;
    }
    D_00728A60[cur->f20] = 1;
    D_00728610[n++] = cur;

    while (1) {
        for (i = 0; i < n; i++) {
            if (D_00728610[i] != 0) {
                goto found;
            }
        }
        break;
    found:
        cur = D_00728610[i];
        edge = &D_004F1EC0[cur->f20];
        debug_StdPrintfDummy(D_00621D88, cur, cur->f20, i);
        D_00728610[i] = 0;
        debug_StdPrintfDummy(D_00621DA8, edge->f28);
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
                    if (D_00728A60[k] != 0) {
                        continue;
                    }
                    D_00728A60[k] = 1;
                    if (chk && D_004F1EC0[k].f28 == 0) {
                        continue;
                    }
                    if (j == 0) {
                        D_00728610[n++] = D_004F1EC0[k].f8;
                    } else {
                        D_00728610[n++] = D_004F1EC0[k].fC;
                    }
                    debug_StdPrintfDummy(D_00621DB8, D_00728610[n - 1], j, k);
                }
            }
        } else {
            for (j = 0; j < 2; j++) {
                k = ((WpNode *)D_004F31E0)[edge->f20[j]].f20;
                if (D_00728A60[k] != 0) {
                    continue;
                }
                D_00728A60[k] = 1;
                if (chk && D_004F1EC0[k].f28 == 0) {
                    continue;
                }
                D_00728610[n++] = &D_004F31E0[edge->f20[j]];
                debug_StdPrintfDummy(D_00621DD8, D_00728610[n - 1], j, k);
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
        debug_StdPrintfDummy(D_00621DF0);
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
        debug_StdPrintfDummy(D_00621E48);
        return 0;
    }
    sceVu0CopyVector(dst, found->pos);
    return 1;
}

extern char D_00621D58[];
extern void *D_00639EA8;

static inline float wayLengthOfGObj_Pos(void *obj, float *pos)
{
    float buf[4];
    if (obj == 0) {
        return -1.0f;
    }
    GetRootPosition(buf, obj);
    return WayLengthOfPos_Pos(buf, pos);
}

/* INTERIM: the listing inlines WayLengthOfGObj_GObj (and through it
 * WayLengthOfGObj_Pos) into NearestEnemyFromGirl.  Both are public functions of
 * the TU's deferred-`inline` tail, so their plain definitions stay at their ROM
 * slots below and these static stand-ins carry the inlined copies. */
static inline float wayLengthOfGObj_GObj(void *obj0, void *obj1)
{
    float pos[4];
    if (obj1 == 0) {
        return -1.0f;
    }
    GetRootPosition(pos, obj1);
    return wayLengthOfGObj_Pos(obj0, pos);
}

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
        d = wayLengthOfGObj_GObj(D_00639EA8, obj);

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

int NumOfWpPos(void)
{
    return D_0063BD60;
}

int CopyWpPos(float dst[][4], int from, int to)
{
    int j = 0;
    if (from < 0) {
        return 1;
    }

    for (; from <= to && from < 128; from++, j++) {
        debug_StdPrintfDummy(D_00621D58, j);
        sceVu0CopyVector(dst[j], D_00728AC0[from]);
    }

    return 0;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * WayLengthOfGObj_Pos into WayLengthOfGObj_GObj, so it is a public `inline` of
 * the deferred tail; until the tail's asm members are C the copy is emitted
 * here as a plain function at its ROM position and the caller inlines the
 * static stand-in wayLengthOfGObj_Pos, which collapses at layout. */
float WayLengthOfGObj_Pos(void *obj, float *pos)
{
    float buf[4];
    if (obj == 0) {
        return -1.0f;
    }
    GetRootPosition(buf, obj);
    return WayLengthOfPos_Pos(buf, pos);
}

float WayLengthOfGObj_GObj(void *obj0, void *obj1)
{
    float pos[4];
    if (obj1 == 0) {
        return -1.0f;
    }
    GetRootPosition(pos, obj1);
    return wayLengthOfGObj_Pos(obj0, pos);
}

int WayPointWithRangeFromGObj(void *obj, float f)
{
    float pos[4];
    if (obj == 0) {
        return -1;
    }
    GetRootPosition(pos, obj);
    return WayPointWithRangeFromPos(pos, 0, f);
}

/* census wpsort_compfnc, a file static, `static` keeps its ELF symbol local so it
   cannot collide with the ico2/fumi/src/way_util global of the same name */
static int wpsort_compfnc(float *a, float *b)
{
    if (a[1] < b[1])
        return -1;
    if (b[1] < a[1])
        return 1;
    return 0;
}
