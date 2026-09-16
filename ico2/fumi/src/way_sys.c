#include "common.h"
#include "debug.h"
#include "way_llf.h"

typedef struct {
    int pad[8];
    int f20;
    int pad2[7];
} WVTElem;

typedef struct {
    char pad[0x64];
    int w64;
} WVTObj;

typedef struct Nd {
    int pad[2];
    struct Nd *f8;
    struct Nd *fC;
    char pad2[0x40 - 16];
} Nd;

/* kept local: this TU's uses of _FUNC_GetWay_begin do not fit the prototype in way_sys.h */
extern int _FUNC_GetWay_begin(void *a0, int a1, int a2, int a3);
extern Nd D_004F31E0[];
extern char D_00554220[];
/* prototypes: their order is the inline tail's emission order */
int GetWay_begin(void *a0, int a1, int a2);
void BridgeBox(void);
void DeleteGuideWay(WVTObj *o);

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/way_sys", _FUNC_GetWay_begin);

inline int GetWay_begin(void *a0, int a1, int a2)
{
    return _FUNC_GetWay_begin(a0, a1, a2, 0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/way_sys", avoid_obstacle2);

/* The collision query ClipWall / ClipFloorR fill in: 192 bytes, 16-aligned. */
typedef struct {
    float p0[4];      /* 0x00 segment start */
    float p1[4];      /* 0x10 segment end */
    float hit[4];     /* 0x20 the clipped point */
    char pad30[0x40]; /* 0x30 */
    int f70;          /* 0x70 */
    char pad74[0x14]; /* 0x74 */
    int wall;         /* 0x88 */
    char pad8C[0x8];  /* 0x8C */
    int floor;        /* 0x94 */
    char pad98[0x28]; /* 0x98 */
} __attribute__((aligned(16))) ClipWork;

typedef float WayVec[4] __attribute__((aligned(16)));

/* One way group record, 52 bytes; only the four words this function reads or
   writes are named. */
typedef struct {
    char pad00[0x18]; /* 0x00 */
    int f18;          /* 0x18 */
    int f1C;          /* 0x1C */
    int f20;          /* 0x20 */
    int f24;          /* 0x24 */
    char pad28[0xC];  /* 0x28 */
} WayGroup;

extern WayGroup D_004F1EC0[];
extern void GetRootPosition(void *out, void *gobj);
extern void sceVu0CopyVector(void *dst, void *src);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern float GetTableCos(int ang);
extern float GetTableSin(int ang);
extern void ClipWall(void *cc);
extern void ClipFloorR(void *cc);
extern int CreateWayGroup(void);
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

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/way_sys", GetWay_next);
INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/way_sys", GetNearNigePointN);
