#include "common.h"
#include "debug.h"
#include "way_llf.h"
#include "way_sys.h"
#include <libvu0.h>
#include "typedef.h"

typedef struct {
    int pad[8];
    int f20;
    int pad2[7];
} WVTElem;

typedef struct Nd {
    /* 0x00 */ int _0;
    /* 0x04 */ int f4;
    /* 0x08 */ struct Nd *f8;
    /* 0x0C */ struct Nd *fC;
    /* 0x10 */ float pos[4];
    /* 0x20 */ int f20;
    /* 0x24 */ int f24;
    /* 0x28 */ int f28;
    /* 0x2C */ char pad2C[0x14];
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
    debug_StdPrintfDummy("GetWay_begin\n");
    debug_StdPrintfDummy("gid t:%d m:%d\n", *(int *)(wp0 + 0x20), *(int *)(wp + 0x20));

    w->w60 = *(int *)(wp + 0x20);
    sceVu0CopyVector(w->pos, a0);

    g0 = *(int *)(wp0 + 0x20);
    g1 = *(int *)(wp + 0x20);

    w->w44 = 0;
    w->w64 = -1;
    w->w6C = 0;
    w->w70 = 0;
    if (g0 == g1) {
        debug_StdPrintfDummy("same_group\n");
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

    debug_StdPrintfDummy("other_group\n");
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
            /* RECONSTRUCTION: a compiled-out print, see the note at the
               `r < 0` test below. */
            if (0) {
                debug_StdPrintfDummy("gid:%d = tgid:%d, mgid:%d\n", gid, g1, g0);
            }
            wpn = nearest_waypoint_of_group(a0, gid);

            g0 = gid;
            wp0 = wpn;
            sceVu0CopyVector(w->pos, wp0 + 0x10);
            if (g0 == g1) {
                debug_StdPrintfDummy("same_group\n");
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
        /* RECONSTRUCTION: two strings of the ROM's pool, "gid:%d = tgid:%d,
           mgid:%d\n" and "!!cant reach!!\n", sit between "other_group\n" and
           "wp:%p %p\n" with no word of the ROM referencing them: prints the
           build compiled out, whose literals gcc 2.95 still emitted when it
           expanded the call.  What the bytes pin: the two strings and their
           order in the pool.  What they cannot pin: the statements' text,
           their condition and their arguments; an if (0) arm, as
           src/fieldCollision.c's compiled-out dump, is the form measured to
           give the literal and no code, and its place here is the one the
           format reads as. */
        if (0) {
            debug_StdPrintfDummy("!!cant reach!!\n");
        }
        goto out;
    }
    set_check_wp(&w->w20, r, g1);
    w->w20 = wp;

    debug_StdPrintfDummy("wp:%p %p\n", w->w24, wp);
    debug_StdPrintfDummy("gid:%d %d\n", *(int *)(w->w24 + 0x20), *(int *)(wp + 0x20));
    w->w34 = short_direction_between_wp(w->w24, wp);
    debug_StdPrintfDummy("direction:%d\n", w->w34);
    ret = w->w20;

out:
    WayUtilWorkFree(work);
    return (int)ret;
}

inline int GetWay_begin(void *a0, int a1, int a2)
{
    return _FUNC_GetWay_begin(a0, a1, a2, 0);
}

/* The collision query ClipWall / ClipFloorR fill in: 192 bytes, 16-aligned. */
/* kept local: this TU's bytes only come out with its own view of the record,
   named apart from typedef.h's ClipWork as act.c names its ActClipWork. */
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
} __attribute__((aligned(16))) WayClipWork;

typedef float WayVec[4] __attribute__((aligned(16)));

extern void GetRootPosition(void *out, void *gobj);
extern float GetTableCos(int ang);
extern float GetTableSin(int ang);
extern void ClipWall(void *cc);
extern void ClipFloorR(void *cc);
extern void set_bridge(int group);

/* The scene's generated-geometry record, 0x4C bytes; this TU reads only the
   kind byte at 0x46 (the same record ico2/common/src/sceneManager.c carves). */
typedef struct {
    char pad00[0x46];   /* 0x00 */
    unsigned char kind; /* 0x46 */
    char pad47[0x5];    /* 0x47 */
} GenGeoKind;

extern GenGeoKind D_002C2DC8[];
extern int CreateTempWayGroup(void);
extern float _GetLength(void *a, void *b);

/* census rows 582-593: a wall probe between two points, both lifted 75 units. */
static inline int way_probe(float *a, float *b)
{
    WayClipWork cc;
    WayVec off;

    off[0] = 0.0f;
    off[1] = -75.0f;
    off[2] = 0.0f;
    off[3] = 0.0f;

    cc.f70 = 0;
    sceVu0AddVector(cc.p0, a, off);
    sceVu0AddVector(cc.p1, b, off);
    ClipWall(&cc);
    return cc.wall;
}

int avoid_obstacle2(float *pos, float *wp, WVTObj *w)
{
    WayClipWork cc;
    WayVec box[4];
    WayVec rp;
    WayVec off;
    int ids[3];
    int hold;
    char *obj;
    int g;
    int i;
    int k;
    int ofs = 0;
    float best;
    float d;

    hold = 0;
    sceVu0CopyVector(cc.p0, pos);
    sceVu0CopyVector(cc.p1, w->w20 + 0x10);
    cc.f70 = 20.0f;
    ClipWall(&cc);
    if (cc.wall == 0) {
        return 0;
    }
    obj = cc.f80;
    if (((GenGeoKind *)D_002C2DC8)[*(int *)(obj + 8)].kind != 0x11) {
        return 0;
    }

    GetRootPosition(rp, obj);

    if (absf(rp[0] - wp[0]) <= 100.0f) {
        if (absf(rp[2] - wp[2]) <= 100.0f) {
            if (rp[1] + 50.0f - wp[1] > 95.0f) {
                return 0;
            }
            debug_StdPrintfDummy("skip wp\n");

            if (w->w20 != w->w24 || w->w38 != 0) {
                return 1;
            }

            hold = 1;
        }
    }

    if (w->w64 >= 0) {
        debug_StdPrintfDummy("delete guide point at avoid\n");

        DeleteWayGroup(((WVTElem *)D_004F31E0)[w->w64].f20);
        w->w64 = -1;
    }

    best = 10000.0f;
    GetRootPosition(rp, obj);
    k = 0;
    off[0] = 100.0f;
    off[1] = 50.0f;
    off[2] = 100.0f;
    off[3] = 0.0f;
    sceVu0AddVector(box[0], rp, off);
    off[0] = 100.0f;
    off[1] = 50.0f;
    off[2] = -100.0f;
    off[3] = 0.0f;
    sceVu0AddVector(box[1], rp, off);
    off[0] = -100.0f;
    off[1] = 50.0f;
    off[2] = -100.0f;
    off[3] = 0.0f;
    sceVu0AddVector(box[2], rp, off);
    off[0] = -100.0f;
    off[1] = 50.0f;
    off[2] = 100.0f;
    off[3] = 0.0f;
    sceVu0AddVector(box[3], rp, off);

    for (i = 0; i < 4; i++) {
        d = _GetLength(box[i], pos);
        if (d < best) {
            best = d;

            k = i;
        }
    }

    /* RECONSTRUCTION: the right-hand chain's first probe reads its second
       corner as box[k += ofs], ofs a zero corner offset.  What the bytes pin:
       in gcse's RTL a set of k's own pseudo between that probe's first-corner
       index and its second-corner address, in this chain only (the same set in
       every probe breaks the left chain's corner reuse), not a register copy
       (cprop would rewrite it away) and not a self-copy cse1 can see; gcse's
       constant propagation turns it into k = k, delete_trivially_dead_insns
       removes it and no instruction is left, while gcse's PRE no longer
       shares k + 1 and k + 4 into this chain.  What they cannot pin: the text,
       the variable's role and its name, which are ours. */
    if (way_probe(box[(k + 3) % 4], box[k]) == 0 && way_probe(box[k], box[(k + 1) % 4]) == 0 &&
        way_probe(box[(k + 1) % 4], box[(k + 2) % 4]) == 0) {
        int j;

        g = CreateTempWayGroup();
        for (j = 0; j < 3; j++) {
            ids[j] = CreateWayPoint((int)box[(k + j) % 4]);
            AddWayPoint(g, ids[j]);
        }
        debug_StdPrintfDummy("left way %d\n", g);

    } else if (way_probe(box[(k + 1) % 4], box[k += ofs]) == 0 &&
               way_probe(box[k], box[(k + 3) % 4]) == 0 &&
               way_probe(box[(k + 3) % 4], box[(k + 2) % 4]) == 0) {
        int j;

        g = CreateTempWayGroup();
        for (j = 0; j < 3; j++) {
            ids[j] = CreateWayPoint((int)box[(k + 4 - j) % 4]);
            AddWayPoint(g, ids[j]);
        }
        debug_StdPrintfDummy("right way %d\n", g);

    } else {
        off[0] = 0.0f;
        off[1] = -50.0f;
        off[2] = 0.0f;
        off[3] = 0.0f;
        sceVu0AddVector(off, off, rp);
        g = CreateTempWayGroup();
        ids[0] = CreateWayPoint((int)off);
        AddWayPoint(g, ids[0]);
        ids[2] = ids[0];
        debug_StdPrintfDummy("up way %d\n", g);
    }

    w->w64 = ids[0];
    w->w28 = w->w20;
    w->w24 = (char *)&D_004F31E0[ids[2]];
    w->w20 = (char *)&D_004F31E0[ids[0]];

    w->w38 = 1;
    w->w34 = 1;

    if (hold == 1) {
        w->w28 = 0;
        w->w38 = 0;
    }

    return 0;
}

void create_box_bridge(char *g)
{
    WayClipWork cc;
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
    WayClipWork cc;
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
        debug_StdPrintfDummy("delete guide point group:%d\n", o->w64);
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
        debug_StdPrintfDummy("illigal way ");
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
        /* RECONSTRUCTION: compiled-out prints, see the note before the second
           switch below. */
        if (0) {
            debug_StdPrintfDummy("WGROUP STAT OTHER\n");
        }
        if (w->w20 != w->w28 && D_004F1EC0[*(int *)(w->w20 + 0x20)].f18 == 0) {
            if (way_wall_between(pos, w->w28) == 0) {
                w->w20 = w->w28;
                blocked = 0;
                debug_StdPrintfDummy("short cut 2:%p\n", w->w20);
                if (w->w64 >= 0) {
                    debug_StdPrintfDummy("delete guide point\n");
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
                    debug_StdPrintfDummy("short cut 1:%p\n", nxt);
                    break;
                }
                nxt = waypoint_bidirectional_list(nxt, w->w34 ^ 1);
            }
        }
        break;

    case 0:
        if (0) {
            debug_StdPrintfDummy("WGROUP STAT SAME\n");
        }
        nxt = w->w24;
        while (nxt != w->w20) {
            if (way_wall_between(pos, nxt) == 0) {
                w->w20 = nxt;
                blocked = 0;
                debug_StdPrintfDummy("short cut 1:%p\n", nxt);
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

    /* RECONSTRUCTION: four strings of the ROM's pool have no word of the ROM
       referencing them: "WGROUP STAT OTHER\n" between "illigal way " and
       "short cut 2:%p\n", "WGROUP STAT SAME\n", "wp %p myway %p pos %p\n"
       and "wgroup stat:%d\n" between "short cut 1:%p\n" and "goal wp1\n".
       They are prints the build compiled out, whose literals gcc 2.95 still
       emitted when it expanded the calls.  What the bytes pin: the strings
       and their order in the pool.  What they cannot pin: the statements'
       text, their condition and their arguments; the two state prints open
       the first switch's arms (w38 1 is the other-group state, 0 the
       same-group one), and the if (0) form is src/fieldCollision.c's. */
    if (0) {
        debug_StdPrintfDummy("wp %p myway %p pos %p\n", cur, w->w24, pos);
        debug_StdPrintfDummy("wgroup stat:%d\n", w->w38);
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
            debug_StdPrintfDummy("goal wp1\n");
            w->w20 = w->w28;
            if (w->w64 >= 0) {
                debug_StdPrintfDummy("delete guide point\n");
                DeleteWayGroup(((WVTElem *)D_004F31E0)[w->w64].f20);
                w->w64 = -1;
            }
            w->w2C = w->w24;
            return (int)w->w20;
        }
        break;
    }

    w->w20 = waypoint_bidirectional_list(cur, w->w34);
    debug_StdPrintfDummy("bilist:%p\n", w->w20);
    w->w2C = w->w20;
    return (int)w->w2C;
}

/* One candidate escape point: the way point id and the path length to it. */
typedef struct NigeEnt {
    int id;
    float d;
} NigeEnt;

/* The TU's whole .bss: one entry per way point (way_llf's 275), which
   GetNearNigePointN fills and sorts by path length. */
static NigeEnt nigePointTbl[275];

extern Nd D_004F31F0[];
extern WayGroup *WayBridge_begin(void);
extern WayGroup *WayBridge_next(WayGroup *g);
extern float _GetLength(void *a, void *b);
extern void CopyVector(void *dst, void *src);

int GetNearNigePointN(void *out, int num, WVTObj *w, float *pos)
{
    Nd *n;
    WayGroup *gb;
    Nd *m;
    Nd *a;
    float *bp;
    float d;
    float da;
    int i;
    int j;

    int cnt = 0;

    Nd *base = (Nd *)visible_waypoint_of_all_except_temp(pos, -1);
    WayGroup *ga = &D_004F1EC0[base->f20];

    /* census rows 1146-1150 */
    __inline__ void nige_swap(NigeEnt * tbl, int a, int b)
    {
        NigeEnt t = tbl[a];

        tbl[a] = tbl[b];
        tbl[b] = t;
    }

    /* census rows 1152-1160 */
    __inline__ int nige_add(NigeEnt * tbl, int n, Nd *e, float d)
    {
        if (e->f28 != 0) {
            tbl[n].id = e->f4;
            tbl[n].d = d;
            n++;
        }
        return n;
    }

    w->w68 = 0;

    gb = &D_004F1EC0[base->f20];
    if (gb->f18 != 0) {
        n = base;
        d = _GetLength(pos, base->pos);
        while (n != 0) {
            if (n->f8 != 0) {
                d += _GetLength(n->pos, n->f8->pos);
            }
            n = n->f8;
        }

        m = &D_004F31E0[gb->f20];
        d += _GetLength((char *)gb->f8 + 0x10, m->pos);
        cnt = nige_add(nigePointTbl, cnt, m, d);

        n = base;
        bp = base->pos;
        d = _GetLength(pos, bp);
        if (n != 0) {
            d += _GetLength(pos, base->pos);
        }
        while (n != 0) {
            if (n->fC != 0) {
                d += _GetLength(n->pos, n->fC->pos);
            }
            n = n->fC;
        }

        m = &D_004F31E0[gb->f24];
        d += _GetLength((char *)gb->fC + 0x10, m->pos);
        cnt = nige_add(nigePointTbl, cnt, m, d);
    } else {
        switch (ga->f14) {
        case 0:
            n = base;
            d = _GetLength(pos, base->pos);
            while (n != 0) {
                cnt = nige_add(nigePointTbl, cnt, n, d);
                if (n->f8 != 0) {
                    d += _GetLength(n->pos, n->f8->pos);
                }
                n = n->f8;
            }

            bp = base->pos;
            d = _GetLength(pos, bp);
            if (base != 0) {
                if (base->fC != 0) {
                    d += _GetLength(base->pos, base->fC->pos);
                }
            }
            n = base->fC;
            while (n != 0) {
                cnt = nige_add(nigePointTbl, cnt, n, d);
                if (n->fC != 0) {
                    d += _GetLength(n->pos, n->fC->pos);
                }
                n = n->fC;
            }
            break;

        case 1:
            a = base;
            n = base;
            da = _GetLength(pos, base->pos);
            d = da;
            do {
                if (da <= d) {
                    da += _GetLength(a->pos, a->f8->pos);
                    a = a->f8;
                    cnt = nige_add(nigePointTbl, cnt, a, da);
                } else {
                    d += _GetLength(n->pos, n->fC->pos);
                    n = n->fC;
                    cnt = nige_add(nigePointTbl, cnt, n, d);
                }
            } while (a != n);
            break;
        }

        for (gb = WayBridge_begin(); gb != 0; gb = WayBridge_next(gb)) {
            if (gb->f20 == base->f4 || gb->f24 == base->f4) {
                d = _GetLength(base->pos, gb->f8 + 0x10);
                m = (Nd *)gb->f8;
                while (m->fC != 0) {
                    d += _GetLength(m->pos, m->fC->pos);
                    m = m->fC;
                }
                d += _GetLength(gb->fC + 0x10, (float *)&D_004F31F0[gb->f24]);
                if (gb->f20 == base->f4) {
                    cnt = nige_add(nigePointTbl, cnt, &D_004F31E0[gb->f24], d);
                } else {
                    cnt = nige_add(nigePointTbl, cnt, &D_004F31E0[gb->f20], d);
                }
                w->w68 = 1;
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
        CopyVector((char *)out + i * 16, (float *)&D_004F31F0[nigePointTbl[i].id]);
    }
    return cnt;
}
