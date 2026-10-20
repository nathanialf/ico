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

WayPoint *GetWay_begin(float *from, WVTObj *w, float *goal)
{
    WayPoint *wp0;
    WayPoint *wp;
    int g0;
    int g1;
    int r;
    int gid;
    WayPoint *wpn;

    wp0 = visible_waypoint_of_all_except_temp(from, -1);
    if (wp0 == 0) {
        return 0;
    }

    if ((unsigned int)w->stampFrame < (unsigned int)(GlobalTimer - 1) || w->nearWp == 0) {
        if (w->guideFirst >= 0) {
            wp = visible_waypoint_of_all_except_temp(goal, way_point[w->guideFirst].group);
        } else {
            wp = visible_waypoint_of_all_except_temp(goal, -1);
        }

        w->nearWp = wp;
    } else {
        if (w->guideFirst >= 0) {
            wp =
                visible_waypoint_of_all_except_temp(w->nearWp->pos, way_point[w->guideFirst].group);
        } else {
            wp = visible_waypoint_of_all_except_temp(w->nearWp->pos, -1);
        }
    }

    if (wp == 0) {
        return 0;
    }

    if (way_group[wp->group].active == 0) {
        wp = visible_waypoint_of_all_except_gid(goal, wp->group);
        if (wp == 0) {
            return 0;
        }
    }

    w->nearWp = wp;
    w->fromWp = wp0;
    w->stampFrame = GlobalTimer;
    DeleteGuideWay(w);
    debug_StdPrintfDummy("GetWay_begin\n");
    debug_StdPrintfDummy("gid t:%d m:%d\n", wp0->group, wp->group);

    w->group = wp->group;
    sceVu0CopyVector(w->pos, from);

    g0 = wp0->group;
    g1 = wp->group;

    w->reached = 0;
    w->guideFirst = -1;
    w->flag6C = 0;
    w->pathKind = 0;
    if (g0 == g1) {
        debug_StdPrintfDummy("same_group\n");
        w->avoiding = 0;
        w->flag3C = 0;
        w->direction = short_direction_between_wp(wp0, wp);
        if (w->direction == -2) {
            return 0;
        }
        w->chk.cur = wp;
        w->chk.start = wp0;
        w->chk.cross = 0;

        return wp;
    }

    debug_StdPrintfDummy("other_group\n");
    r = func_001703D8(g0, g1); /* shortest_path, way_util.c's row */
    if (r == -1) {
        w->pathKind = 1;

        if (way_group[g1].active == 0) {
            return 0;
        }
        r = func_001706C8(g0, g1); /* GetWgAll, way_util.c's row */
        if (r == -1) {
            w->pathKind = 2;
        } else {
            gid = NearestWgFromTarget(g0, g1);
            /* a compiled-out print, see the note at the `r < 0` test below */
            if (0) {
                debug_StdPrintfDummy("gid:%d = tgid:%d, mgid:%d\n", gid, g1, g0);
            }
            wpn = nearest_waypoint_of_group(from, gid);

            g0 = gid;
            wp0 = wpn;
            sceVu0CopyVector(w->pos, wp0->pos);
            if (g0 == g1) {
                debug_StdPrintfDummy("same_group\n");
                w->avoiding = 0;
                w->flag3C = 0;
                w->direction = short_direction_between_wp(wp0, wp);
                if (w->direction == -2) {
                    return 0;
                }
                w->chk.cur = wp;
                w->chk.start = wp0;
                w->chk.cross = 0;

                w->flag6C = 1;

                return wp;
            }
        }
    }

    w->avoiding = 1;
    w->flag3C = 1;
    if (r == g0) {
        WayGroup *a = &way_group[wp->group];
        WayGroup *b = &way_group[wp0->group];

        switch (a->bridge) {
        case 1:
            if (wp == a->first) {
                if (way_point[a->end[0]].group == r) {
                    w->flag3C = 0;
                }
            } else if (wp == a->last) {
                if (way_point[a->end[1]].group == r) {
                    w->flag3C = 0;
                }
            }
            break;

        case 0:
            if (wp->index == b->end[0]) {
                w->flag3C = 0;
            } else if (wp->index == b->end[1]) {
                w->flag3C = 0;
            }
            break;
        }
    }

    if (r < 0) {
        /* prints compiled out of the retail build; their strings stay in
           .rodata */
        if (0) {
            debug_StdPrintfDummy("!!cant reach!!\n");
        }
        return 0;
    }
    set_check_wp(&w->chk, r, g1);
    w->chk.cur = wp;

    debug_StdPrintfDummy("wp:%p %p\n", w->chk.start, wp);
    debug_StdPrintfDummy("gid:%d %d\n", w->chk.start->group, wp->group);
    w->direction = short_direction_between_wp(w->chk.start, wp);
    debug_StdPrintfDummy("direction:%d\n", w->direction);
    return w->chk.cur;
}

/* the object whose wall collision GetWay_next draws, for debugging; first in the
   demo's .sdata of the TU (0x679FA0) */
static void *wayDebugWallGObj = 0; /* derived name */

typedef float WayVec[4] __attribute__((aligned(16))); /* derived name */

INCLUDE_ASM(func_0016DF10);

INCLUDE_ASM(avoid_obstacle2);

static void create_box_bridge(char *g)
{
    ClipWork cc;
    WayVec pos;
    WayVec start;
    WayVec end;
    WayVec off;
    WayVec wp[3];
    int i;
    int j;
    int id;

    GetRootPosition(pos, (GObj *)g);
    for (i = 0; i < 4; i++) {
        sceVu0CopyVector(start, pos);
        off[0] = GetTableCos((short)(i * 0x4000)) * 75.0f;
        off[2] = -GetTableSin((short)(i * 0x4000)) * 75.0f;
        off[1] = 0.0f;
        sceVu0AddVector(end, pos, off);

        sceVu0CopyVector(cc.pt[0], start);
        sceVu0CopyVector(cc.pt[1], end);
        cc.radius = 0;
        ClipWall(&cc);
        if (cc.wall.elem == 0) {
            continue;
        }

        sceVu0CopyVector(cc.pt[0], cc.pt[1]);
        cc.pt[1][1] = cc.pt[1][1] - 175.0f;
        ClipFloorR(&cc);
        sceVu0CopyVector(wp[0], cc.pt[2]);
        if (cc.floor.elem == 0) {
            continue;
        }

        sceVu0CopyVector(cc.pt[0], start);
        sceVu0SubVector(cc.pt[1], pos, off);
        ClipWall(&cc);
        sceVu0CopyVector(wp[2], cc.pt[2]);
        wp[2][1] = pos[1] + 50.0f;
        if (cc.wall.elem != 0) {
            continue;
        }

        sceVu0CopyVector(wp[1], pos);
        wp[1][1] = wp[1][1] - 50.0f;

        id = CreateWayGroup();
        for (j = 0; j < 3; j++) {
            AddWayPoint(id, CreateWayPoint(wp[j]));
        }
        set_bridge(id);
        way_group[id].boxBridge = 1;
        if (way_group[id].bridge == 0) {
            DeleteWayGroup(id);
        } else {
            WayPoint *a = &way_point[way_group[id].end[0]];
            WayPoint *b = &way_point[way_group[id].end[1]];

            if (a->group == b->group) {
                DeleteWayGroup(id);
            }
        }
    }
}

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
