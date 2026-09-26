#include "common.h"
#include "debug.h"
#include "way_llf.h"
#include "way_sys.h"
#include <libvu0.h>

typedef struct {
    int pad[8];
    int f20;
    int pad2[7];
} WVTElem;

typedef struct Nd {
    int pad[2];
    struct Nd *f8;
    struct Nd *fC;
    char pad2[0x40 - 16];
} Nd;

/* One way group record, 52 bytes; only the words this TU reads or writes are
   named. */
typedef struct {
    char pad00[0x8]; /* 0x00 */
    char *f8;        /* 0x08 */
    char *fC;        /* 0x0C */
    int f10;         /* 0x10 */
    int f14;         /* 0x14 */
    int f18;         /* 0x18 */
    int f1C;         /* 0x1C */
    int f20;         /* 0x20 */
    int f24;         /* 0x24 */
    int f28;         /* 0x28 */
    char pad2C[0x8]; /* 0x2C */
} WayGroup;

extern WayGroup D_004F1EC0[];
extern Nd D_004F31E0[];
extern char D_00554220[];

typedef struct WgAll2 {
    int f0, f4, f8, fC, f10, f14, f18;
} WgAll2;

extern int lock_execIcoMisc;
extern char *visible_waypoint_of_all_except_temp(void *pos, int gid);
extern char *visible_waypoint_of_all_except_temp_ThreadVersion(void *pos, int gid);
extern char *visible_waypoint_of_all_except_gid(void *pos, int gid);
extern char *visible_waypoint_of_all_except_gid_ThreadVersion(void *pos, int gid);
extern int shortest_path(int from, int to, WgAll2 *w);
extern int shortest_path_ThreadVersion(int from, int to, WgAll2 *w);
extern int GetWgAll(int from, int to, WgAll2 *w);
extern int NearestWgFromTarget(int cur, int end, WgAll2 *w);
extern char *nearest_waypoint_of_group(void *pos, int handle);
extern void set_check_wp(void *out, int wp, int gid);
extern int short_direction_between_wp(char *from, char *to);
extern void *WayUtilWorkAlloc(void);
extern void WayUtilWorkFree(void *self);
extern char D_00554120[];
extern char D_00554130[];
extern char D_00554140[];
extern char D_00554150[];
extern char D_00554190[];
extern char D_005541A0[];
extern char D_005541B0[];

int _FUNC_GetWay_begin(void *a0, WVTObj *w, int a2, int a3)
{
    char *(*findTemp)(void *, int);
    char *(*findGid)(void *, int);
    int (*findPath)(int, int, WgAll2 *);
    char *ret;
    WgAll2 *work;
    char *wp0;
    char *wp;
    int g0;
    int g1;
    int r;
    int gid;
    char *wpn;

    ret = 0;
    work = (WgAll2 *)WayUtilWorkAlloc();
    if (a3) {
        findTemp = visible_waypoint_of_all_except_temp_ThreadVersion;

        findGid = visible_waypoint_of_all_except_gid_ThreadVersion;

        findPath = shortest_path_ThreadVersion;
    } else {
        findTemp = visible_waypoint_of_all_except_temp;
        findGid = visible_waypoint_of_all_except_gid;
        findPath = shortest_path;
    }

    wp0 = findTemp(a0, -1);
    if (wp0 == 0) {
        goto out;
    }

    if ((unsigned int)w->w30 < (unsigned int)(lock_execIcoMisc - 1) || w->w2C == 0) {
        if (w->w64 >= 0) {
            wp = findTemp((void *)a2, ((WVTElem *)D_004F31E0)[w->w64].f20);
        } else {
            wp = findTemp((void *)a2, -1);
        }

        w->w2C = wp;
    } else {
        if (w->w64 >= 0) {
            wp = findTemp(w->w2C + 0x10, ((WVTElem *)D_004F31E0)[w->w64].f20);
        } else {
            wp = findTemp(w->w2C + 0x10, -1);
        }
    }

    if (wp == 0) {
        goto out;
    }

    if (D_004F1EC0[*(int *)(wp + 0x20)].f28 == 0) {
        wp = findGid((void *)a2, *(int *)(wp + 0x20));
        if (wp == 0) {
            goto out;
        }
    }

    w->w2C = wp;
    w->w74 = wp0;
    w->w30 = lock_execIcoMisc;
    DeleteGuideWay(w);
    debug_StdPrintfDummy(D_00554120);
    debug_StdPrintfDummy(D_00554130, *(int *)(wp0 + 0x20), *(int *)(wp + 0x20));

    w->w60 = *(int *)(wp + 0x20);
    sceVu0CopyVector(w->pos, a0);

    g0 = *(int *)(wp0 + 0x20);
    g1 = *(int *)(wp + 0x20);

    w->w44 = 0;
    w->w64 = -1;
    w->w6C = 0;
    w->w70 = 0;
    if (g0 == g1) {
        debug_StdPrintfDummy(D_00554140);
        w->w38 = 0;
        w->w3C = 0;
        w->w34 = short_direction_between_wp(wp0, wp);
        if (w->w34 == -2) {
            goto out;
        }
        w->w20 = wp;
        w->w24 = wp0;
        w->w28 = 0;

        ret = wp;
        goto out;
    }

    debug_StdPrintfDummy(D_00554150);
    r = findPath(g0, g1, work);
    if (r == -1) {
        w->w70 = 1;

        if (D_004F1EC0[g1].f28 == 0) {
            goto out;
        }
        r = GetWgAll(g0, g1, work);
        if (r == -1) {
            w->w70 = 2;
        } else {
            gid = NearestWgFromTarget(g0, g1, work);
            wpn = nearest_waypoint_of_group(a0, gid);

            g0 = gid;
            wp0 = wpn;
            sceVu0CopyVector(w->pos, wp0 + 0x10);
            if (g0 == g1) {
                debug_StdPrintfDummy(D_00554140);
                w->w38 = 0;
                w->w3C = 0;
                w->w34 = short_direction_between_wp(wp0, wp);
                if (w->w34 == -2) {
                    goto out;
                }
                w->w20 = wp;
                w->w24 = wp0;
                w->w28 = 0;

                w->w6C = 1;

                ret = wp;
                goto out;
            }
        }
    }

    w->w38 = 1;
    w->w3C = 1;
    if (r == g0) {
        WayGroup *a = &D_004F1EC0[*(int *)(wp + 0x20)];
        WayGroup *b = &D_004F1EC0[*(int *)(wp0 + 0x20)];

        switch (a->f18) {
        case 1:
            if (wp == a->f8) {
                if (((WVTElem *)D_004F31E0)[a->f20].f20 == r) {
                    w->w3C = 0;
                }
            } else if (wp == a->fC) {
                if (((WVTElem *)D_004F31E0)[a->f24].f20 == r) {
                    w->w3C = 0;
                }
            }
            break;

        case 0:
            if (*(int *)(wp + 4) == b->f20) {
                w->w3C = 0;
            } else if (*(int *)(wp + 4) == b->f24) {
                w->w3C = 0;
            }
            break;
        }
    }

    if (r < 0) {
        goto out;
    }
    set_check_wp(&w->w20, r, g1);
    w->w20 = wp;

    debug_StdPrintfDummy(D_00554190, w->w24, wp);
    debug_StdPrintfDummy(D_005541A0, *(int *)(w->w24 + 0x20), *(int *)(wp + 0x20));
    w->w34 = short_direction_between_wp(w->w24, wp);
    debug_StdPrintfDummy(D_005541B0, w->w34);
    ret = w->w20;

out:
    WayUtilWorkFree(work);
    return (int)ret;
}

inline int GetWay_begin(void *a0, int a1, int a2)
{
    return _FUNC_GetWay_begin(a0, a1, a2, 0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/way_sys", avoid_obstacle2);

/* The collision query ClipWall / ClipFloorR fill in: 192 bytes, 16-aligned. */
/* kept local: this TU's bytes only come out with its own view of ClipWork. */
typedef struct {
    float p0[4];      /* 0x00 segment start */
    float p1[4];      /* 0x10 segment end */
    float hit[4];     /* 0x20 the clipped point */
    char pad30[0x40]; /* 0x30 */
    float f70;        /* 0x70 */
    char pad74[0xC];  /* 0x74 */
    char *f80;        /* 0x80 */
    int f84;          /* 0x84 */
    int wall;         /* 0x88 */
    char pad8C[0x8];  /* 0x8C */
    int floor;        /* 0x94 */
    char pad98[0x28]; /* 0x98 */
} __attribute__((aligned(16))) ClipWork;

typedef float WayVec[4] __attribute__((aligned(16)));

extern void GetRootPosition(void *out, void *gobj);
extern float GetTableCos(int ang);
extern float GetTableSin(int ang);
extern void ClipWall(void *cc);
extern void ClipFloorR(void *cc);
extern void set_bridge(int group);

void create_box_bridge(char *g)
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

    GetRootPosition(pos, g);
    for (i = 0; i < 4; i++) {
        sceVu0CopyVector(start, pos);
        off[0] = GetTableCos((short)(i * 0x4000)) * 75.0f;
        off[2] = -GetTableSin((short)(i * 0x4000)) * 75.0f;
        off[1] = 0.0f;
        sceVu0AddVector(end, pos, off);

        sceVu0CopyVector(cc.p0, start);
        sceVu0CopyVector(cc.p1, end);
        cc.f70 = 0;
        ClipWall(&cc);
        if (cc.wall == 0) {
            continue;
        }

        sceVu0CopyVector(cc.p0, cc.p1);
        cc.p1[1] = cc.p1[1] - 175.0f;
        ClipFloorR(&cc);
        sceVu0CopyVector(wp[0], cc.hit);
        if (cc.floor == 0) {
            continue;
        }

        sceVu0CopyVector(cc.p0, start);
        sceVu0SubVector(cc.p1, pos, off);
        ClipWall(&cc);
        sceVu0CopyVector(wp[2], cc.hit);
        wp[2][1] = pos[1] + 50.0f;
        if (cc.wall != 0) {
            continue;
        }

        sceVu0CopyVector(wp[1], pos);
        wp[1][1] = wp[1][1] - 50.0f;

        id = CreateWayGroup();
        for (j = 0; j < 3; j++) {
            AddWayPoint(id, CreateWayPoint(wp[j]));
        }
        set_bridge(id);
        D_004F1EC0[id].f1C = 1;
        if (D_004F1EC0[id].f18 == 0) {
            DeleteWayGroup(id);
        } else {
            WVTElem *a = &((WVTElem *)D_004F31E0)[D_004F1EC0[id].f20];
            WVTElem *b = &((WVTElem *)D_004F31E0)[D_004F1EC0[id].f24];

            if (a->f20 == b->f20) {
                DeleteWayGroup(id);
            }
        }
    }
}

inline void BridgeBox(void) {}

extern void ClipWallField(void *cc);

/* census rows 853-867: a wall probe between `pos` and a way point, both lifted
   75 units, with a 30-unit radius.  Only ever inlined, so it has no MAIN.MAP
   symbol and the name is ours. */
static __inline__ int way_wall_between(float *pos, char *wp)
{
    ClipWork cc;
    WayVec off;
    float *p = (float *)(wp + 0x10);

    off[0] = 0.0f;
    off[1] = -75.0f;
    off[2] = 0.0f;
    off[3] = 0.0f;
    cc.f70 = 30.0f;
    sceVu0AddVector(cc.p0, pos, off);
    sceVu0AddVector(cc.p1, p, off);
    ClipWall(&cc);
    if (cc.wall == 0) {
        ClipWallField(&cc);
    }
    return cc.wall;
}

inline void DeleteGuideWay(WVTObj *o)
{
    if (o->w64 >= 0) {
        debug_StdPrintfDummy(D_00554220, o->w64);
        {
            WVTElem *e = &((WVTElem *)D_004F31E0)[o->w64];
            DeleteWayGroup(e->f20);
        }
        o->w64 = -1;
    }
}

extern void ez_line(void *a, void *b, unsigned int col);
extern void ez_circle(void *pos, void *base, unsigned int col, float r);
extern void DrawGObjWallCollision(void *gobj, int col);
extern char *waypoint_bidirectional_list(char *wp, int dir);
extern float fzMagnitudefv(void *v);
extern void *D_0063A9A0;
extern char D_00554240[];
extern char D_00554268[];
extern char D_00554278[];
extern char D_00554290[];
extern char D_005542E0[];
extern char D_005542F0[];

int GetWay_next(WVTObj *w, float *pos)
{
    WayVec dv;
    char *cur;
    char *nxt;
    char *p;
    int blocked;
    float lim;

    w->w30 = lock_execIcoMisc;
    if (w->w20 == 0 || *(int *)w->w20 == 0) {
        debug_StdPrintfDummy(D_00554240);
        return 0;
    }
    ez_circle(w->w2C + 0x10, pos, 0x80800000, 30.0f);

    if (D_0063A9A0 != 0) {
        DrawGObjWallCollision(D_0063A9A0, 0x800000);
    }

    if (w->w20 != 0) {
        ez_line(pos, w->w20 + 0x10, 0);
        ez_circle(w->w20 + 0x10, pos, 0x80000080, *(float *)(w->w20 + 0x24));
    }

    if (w->w24 != 0) {
        ez_line(pos, w->w24 + 0x10, 1);
        ez_circle(w->w24 + 0x10, pos, 0x80008000, *(float *)(w->w24 + 0x24));
    }

    if (w->w28 != 0) {
        ez_line(pos, w->w28 + 0x10, 2);
        ez_circle(w->w28 + 0x10, pos, 0x80800000, *(float *)(w->w28 + 0x24));
    }

    blocked = avoid_obstacle2(pos, w->w20 + 0x10, w);

    switch (w->w38) {
    case 1:
        if (w->w20 != w->w28 && D_004F1EC0[*(int *)(w->w20 + 0x20)].f18 == 0) {
            if (way_wall_between(pos, w->w28) == 0) {
                w->w20 = w->w28;
                blocked = 0;
                debug_StdPrintfDummy(D_00554268, w->w20);
                if (w->w64 >= 0) {
                    debug_StdPrintfDummy(D_00554278);
                    DeleteWayGroup(((WVTElem *)D_004F31E0)[w->w64].f20);
                    w->w64 = -1;
                }
                break;
            }
            nxt = w->w24;
            while (nxt != w->w20 && w->w64 < 0) {
                if (way_wall_between(pos, nxt) == 0) {
                    w->w20 = nxt;
                    blocked = 0;
                    debug_StdPrintfDummy(D_00554290, nxt);
                    break;
                }
                nxt = waypoint_bidirectional_list(nxt, w->w34 ^ 1);
            }
        }
        break;

    case 0:
        nxt = w->w24;
        while (nxt != w->w20) {
            if (way_wall_between(pos, nxt) == 0) {
                w->w20 = nxt;
                blocked = 0;
                debug_StdPrintfDummy(D_00554290, nxt);
                break;
            }
            nxt = waypoint_bidirectional_list(nxt, w->w34 ^ 1);
            if (nxt == 0) {
                nxt = w->w20;
            }
        }
        break;
    }

    cur = w->w20;
    p = cur + 0x10;
    ez_line(p, pos, 0xFF000080);
    ez_line(p, w->w24 + 0x10, 0xFF80);

    sceVu0SubVector(dv, p, pos);
    sceVu0Normalize(w->nrm, dv);

    if (*(float *)(cur + 0x24) == 0.0f) {
        lim = 50.0f;
    } else {
        lim = *(float *)(cur + 0x24) * 1.5f;
    }

    if (blocked == 0 && lim < fzMagnitudefv(dv)) {
        return (int)cur;
    }

    switch (w->w38) {
    case 0:
        if (cur == w->w24) {
            w->w44 = 1;
            DeleteGuideWay(w);
            return (int)cur;
        }
        break;

    case 1:
        if (cur == w->w28) {
            w->w44 = 1;
            DeleteGuideWay(w);
            w->w2C = w->w28;
            return (int)cur;
        }
        if (cur == w->w24) {
            debug_StdPrintfDummy(D_005542E0);
            w->w20 = w->w28;
            if (w->w64 >= 0) {
                debug_StdPrintfDummy(D_00554278);
                DeleteWayGroup(((WVTElem *)D_004F31E0)[w->w64].f20);
                w->w64 = -1;
            }
            w->w2C = w->w24;
            return (int)w->w20;
        }
        break;
    }

    w->w20 = waypoint_bidirectional_list(cur, w->w34);
    debug_StdPrintfDummy(D_005542F0, w->w20);
    w->w2C = w->w20;
    return (int)w->w2C;
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/way_sys", GetNearNigePointN);
