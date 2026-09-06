#include "common.h"

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

extern void debug_StdPrintfDummy(char *fmt, ...);
extern void fzShowV(float *v);
extern void sceVu0CopyVector(float *dst, float *src);

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


extern WayPoint *visible_waypoint_of_all(float *pos);
extern WayPoint *WayPoint_begin(void);
extern WayPoint *WayPoint_next(WayPoint *wp);
extern WayPoint *GetWay_begin(float *dst, WayWork *w, float *cur);
extern WayPoint *GetWay_next(WayWork *w, float *cur);
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
extern int func_00215C68(float *a, float *b);
extern void qsort(void *base, int n, int size, int (*cmp)());

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

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayPointWithRangeFromPos);
extern WpNode D_004F31E0[];
extern char D_004F1EC0[];
extern char D_004F1EC8[];
extern char D_004F1ED8[];
extern char D_004F1EE0[];
extern char D_004F1EE8[];
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
extern void _SubVector(float *dst, float *a, float *b);
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

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", WayPointWithRangeFromPos2);
extern char D_00621D58[];


extern void GetRootPosition(void *buf, void *obj);
extern float WayLengthOfPos_Pos(float *p0, float *p1);




extern int WayPointWithRangeFromPos(float *pos, int zero, float f);


extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern int isEnemyKidnapEnable(void *gobj);
extern void *D_00639EA8;
extern float D_00639860;
INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", NearestEnemyFromGirl);

int NumOfWpPos(void) {
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

static inline float wayLengthOfGObj_Pos(void *obj, float *pos) {
    float buf[4];
    if (obj == 0) {
        return -1.0f;
    }
    GetRootPosition(buf, obj);
    return WayLengthOfPos_Pos(buf, pos);
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * WayLengthOfGObj_Pos into WayLengthOfGObj_GObj, so it is a public `inline` of
 * the deferred tail; until the tail's asm members are C the copy is emitted
 * here as a plain function at its ROM position and the caller inlines the
 * static stand-in wayLengthOfGObj_Pos, which collapses at layout. */
float WayLengthOfGObj_Pos(void *obj, float *pos) {
    float buf[4];
    if (obj == 0) {
        return -1.0f;
    }
    GetRootPosition(buf, obj);
    return WayLengthOfPos_Pos(buf, pos);
}

float WayLengthOfGObj_GObj(void *obj0, void *obj1) {
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

int func_00215C68(float *a, float *b)
{
    if (a[1] < b[1]) return -1;
    if (b[1] < a[1]) return 1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/way_kidnap", func_00215CA0);
