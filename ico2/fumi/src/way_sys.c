#include "debug.h"
#include "way_llf.h"
#include "way_sys.h"
#include <libvu0.h>
#include "typedef.h"
#include "Matrix.h"
#include "main.h"
#include "matrixDrive.h"
#include "geometryManager.h"
#include "tableSin.h"
#include "fuzio.h"
#include "way_util.h"
#include "fieldCollision.h"
#include "gamesys.h"
#include "include_asm.h"

INCLUDE_ASM(_FUNC_GetWay_begin);

/* the object whose wall collision GetWay_next draws, for debugging; first in the
   demo's .sdata of the TU (0x679FA0) */
static void *wayDebugWallGObj = 0; /* derived name */

INCLUDE_ASM(func_0016DF10);

typedef float WayVec[4] __attribute__((aligned(16))); /* derived name */

/* a wall probe between two points, both lifted 75 units */
static inline struct FcWallEnt *way_probe(float *a, float *b) /* derived name */
{
    ClipWork cc;
    WayVec off;

    off[0] = 0.0f;
    off[1] = -75.0f;
    off[2] = 0.0f;
    off[3] = 0.0f;

    cc.radius = 0;
    sceVu0AddVector(cc.pt[0], a, off);
    sceVu0AddVector(cc.pt[1], b, off);
    ClipWall(&cc);
    return cc.wall.elem;
}

INCLUDE_ASM(avoid_obstacle2);

INCLUDE_ASM(create_box_bridge);

inline void BridgeBox(void) {}

/* a wall probe between `pos` and a way point, both lifted 75 units, with a
   30-unit radius */
static __inline__ struct FcWallEnt *way_wall_between(float *pos, WayPoint *wp) /* derived name */
{
    ClipWork cc;
    WayVec off;
    float *p = (float *)(wp->pos);

    off[0] = 0.0f;
    off[1] = -75.0f;
    off[2] = 0.0f;
    off[3] = 0.0f;
    cc.radius = 30.0f;
    sceVu0AddVector(cc.pt[0], pos, off);
    sceVu0AddVector(cc.pt[1], p, off);
    ClipWall(&cc);
    if (cc.wall.elem == 0) {
        ClipWallField(&cc);
    }
    return cc.wall.elem;
}

inline void DeleteGuideWay(WVTObj *o)
{
    if (o->guideFirst >= 0) {
        debug_StdPrintfDummy("delete guide point group:%d\n", o->guideFirst);
        {
            WayPoint *e = &way_point[o->guideFirst];
            DeleteWayGroup(e->group);
        }
        o->guideFirst = -1;
    }
}

INCLUDE_ASM(GetWay_next);

/* One candidate escape point: the way point id and the path length to it. */
typedef struct NigeEnt { /* field names derived */
    int id;
    float d;
} NigeEnt; /* derived name */

/* The TU's whole .bss: one entry per way point (this build's 192), which
   GetNearNigePointN fills and sorts by path length. */
static NigeEnt nigePointTbl[192]; /* derived name */

int GetNearNigePointN(void *out, int num, WVTObj *w, float *pos)
{
    WayPoint *n;
    WayGroup *gb;
    WayPoint *m;
    WayPoint *a;
    float *bp;
    float d;
    float da;
    int i;
    int j;

    int cnt = 0;

    WayPoint *base = visible_waypoint_of_all_except_temp(pos, -1);
    WayGroup *ga = &way_group[base->group];

    __inline__ void nige_swap(NigeEnt * tbl, int a, int b) /* derived name */
    {
        NigeEnt t = tbl[a];

        tbl[a] = tbl[b];
        tbl[b] = t;
    }

    __inline__ int nige_add(NigeEnt * tbl, int n, WayPoint *e, float d) /* derived name */
    {
        if (e->escape != 0) {
            tbl[n].id = e->index;
            tbl[n].d = d;
            n++;
        }
        return n;
    }

    w->escapeFound = 0;

    gb = &way_group[base->group];
    if (gb->bridge != 0) {
        n = base;
        d = _GetLength(pos, base->pos);
        while (n != 0) {
            if (n->prev != 0) {
                d += _GetLength(n->pos, n->prev->pos);
            }
            n = n->prev;
        }

        m = &way_point[gb->end[0]];
        d += _GetLength(gb->first->pos, m->pos);
        cnt = nige_add(nigePointTbl, cnt, m, d);

        n = base;
        bp = base->pos;
        d = _GetLength(pos, bp);
        if (n != 0) {
            d += _GetLength(pos, base->pos);
        }
        while (n != 0) {
            if (n->next != 0) {
                d += _GetLength(n->pos, n->next->pos);
            }
            n = n->next;
        }

        m = &way_point[gb->end[1]];
        d += _GetLength(gb->last->pos, m->pos);
        cnt = nige_add(nigePointTbl, cnt, m, d);
    } else {
        switch (ga->closed) {
        case 0:
            n = base;
            d = _GetLength(pos, base->pos);
            while (n != 0) {
                cnt = nige_add(nigePointTbl, cnt, n, d);
                if (n->prev != 0) {
                    d += _GetLength(n->pos, n->prev->pos);
                }
                n = n->prev;
            }

            bp = base->pos;
            d = _GetLength(pos, bp);
            if (base != 0) {
                if (base->next != 0) {
                    d += _GetLength(base->pos, base->next->pos);
                }
            }
            n = base->next;
            while (n != 0) {
                cnt = nige_add(nigePointTbl, cnt, n, d);
                if (n->next != 0) {
                    d += _GetLength(n->pos, n->next->pos);
                }
                n = n->next;
            }
            break;

        case 1:
            a = base;
            n = base;
            da = _GetLength(pos, base->pos);
            d = da;
            do {
                if (da <= d) {
                    da += _GetLength(a->pos, a->prev->pos);
                    a = a->prev;
                    cnt = nige_add(nigePointTbl, cnt, a, da);
                } else {
                    d += _GetLength(n->pos, n->next->pos);
                    n = n->next;
                    cnt = nige_add(nigePointTbl, cnt, n, d);
                }
            } while (a != n);
            break;
        }

        for (gb = WayBridge_begin(); gb != 0; gb = WayBridge_next(gb)) {
            if (gb->end[0] == base->index || gb->end[1] == base->index) {
                d = _GetLength(base->pos, gb->first->pos);
                m = gb->first;
                while (m->next != 0) {
                    d += _GetLength(m->pos, m->next->pos);
                    m = m->next;
                }
                d += _GetLength(gb->last->pos, way_point[gb->end[1]].pos);
                if (gb->end[0] == base->index) {
                    cnt = nige_add(nigePointTbl, cnt, &way_point[gb->end[1]], d);
                } else {
                    cnt = nige_add(nigePointTbl, cnt, &way_point[gb->end[0]], d);
                }
                w->escapeFound = 1;
            }
        }

        cnt = nige_add(nigePointTbl, cnt, base, 0.0f);
    }

    for (i = 0; i < num; i++) {
        for (j = cnt - 1; j > i; j--) {
            if (nigePointTbl[j].d < nigePointTbl[j - 1].d) {
                nige_swap(nigePointTbl, j, j - 1);
            }
        }
        CopyVector((char *)out + i * 16, way_point[nigePointTbl[i].id].pos);
    }
    return cnt;
}
