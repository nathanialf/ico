#include "common.h"
#include "typedef.h"
#include "fieldCollision.h"
#include "debug.h"
#include "debug_exception.h"
#include "FileManager.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    char _0[0x10];
    int unk10;
    int unk14;
    short **unk18;
    short **unk1C;
    float *unk20;
} FuzioCtx;

typedef struct {
    unsigned int lo;
    unsigned char m[3];
    unsigned char hi;
} FcBlk8;

typedef union {
    unsigned char rgba[4];
    long long ll[2];
} FcColor;

typedef int (*FcFunc)(void *a0, int a1);
/* kept local: this TU's uses of isysGObjGetExist_begin do not fit the prototype in gobj.h */
extern void *isysGObjGetExist_begin(void);
/* kept local: this TU's uses of isysGObjGetExist_next do not fit the prototype in gobj.h */
extern void *isysGObjGetExist_next(void);
extern void __assert(char *file, int line, char *expr);
extern char D_00553750[];
extern char D_00553768[];
extern char D_0063A820[];
extern int D_0063A818;
extern void *D_006C0CC0[];

void MakeCollisionDependGObjList(void)
{
    char *g;
    char *sub;
    /* CRUTCH: zero-code frame reservation. ROM frame is 0x60 with only 0x30 of
     * register saves, so the function declares a ~0x30-byte buffer; the listing
     * shows lines 534..579 of this function emit no code at all (a compiled-out
     * debug block), which is where it was used.  Any size in 33..48 rounds to
     * the same frame.  Deleting it changes the object. See
     * docs/crutch_ledger.md. */
    char buf[0x30];

    D_0063A818 = 0;
    for (g = isysGObjGetExist_begin(); g != 0; g = isysGObjGetExist_next()) {
        sub = (char *)GOBJ_SUB(g);
        if (sub != 0 && *(int *)(sub + 0x70) != 0 && *(int *)(g + 0x16C) != 0 &&
            *(int *)(g + 0x4) == 1 && *(int *)(g + 0x8) >= 0 && *(int *)(sub + 0x74) != 0) {
            D_006C0CC0[D_0063A818] = g;
            D_0063A818 = D_0063A818 + 1;
        }
    }
    if (D_0063A818 >= 0x100) {
        debug_assertMessage(D_00553750, 533, D_00553768);
        __assert(D_00553750, 533, D_0063A820);
    }
}

extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);

void GetReflectionElement(char *a0, float arg0, float arg1)
{
    float buf0[4];
    float L10[4];
    float L20[4];
    float z;

    CopyVector(L10, a0 + 0xA0);
    *(int *)&L10[3] = 0;
    sceVu0SubVector(buf0, a0 + 0x10, a0);
    sceVu0ScaleVector(a0 + 0x30, L10, -GetDistanceFromPlane(L10, buf0));
    sceVu0AddVector(a0 + 0x40, buf0, a0 + 0x30);
    sceVu0ScaleVectorXYZ(a0 + 0x30, a0 + 0x30, arg1);
    sceVu0ScaleVectorXYZ(a0 + 0x40, a0 + 0x40, arg0);
    sceVu0AddVector(a0 + 0x60, a0 + 0x40, a0 + 0x30);
    {
        float *p20 = L20;
        z = GetPointDistance(a0 + 0x20, a0 + 0x10);
        sceVu0ScaleVector(p20, a0 + 0x60, z / GetPointDistance(a0, a0 + 0x10));
        sceVu0AddVector(a0 + 0x50, a0 + 0x20, p20);
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/fieldCollision", clip_wall_1);

extern void sceVu0CopyVector(int *dst, int *src);

typedef struct {
    float x, y, z, w;
} FcVec4;

typedef struct {
    FcVec4 v[4];            /* 0x00: polygon vertices */
    float nx, ny, nz, npad; /* 0x40: plane normal */
    float d;                /* 0x50: plane distance */
    int nex;                /* 0x54: vertices past the first three */
} FcFloorEnt;

static __inline__ int FloorPointInside(FcFloorEnt *e, float *pt)
{
    FcVec4 *v;
    FcVec4 *p2;
    float cp[4];
    float vx;
    int cross;
    int i;
    int n;

    cross = 0;
    n = e->nex + 2;
    v = e->v;
    p2 = v + n;
    for (i = 0; i <= n; i++) {
        vx = v->x;
        if ((vx < pt[0] && pt[0] <= p2->x) || (p2->x < pt[0] && pt[0] <= vx)) {
            cp[0] = pt[0];
            cp[2] = (v->z - p2->z) * (pt[0] - p2->x) / (vx - p2->x) + p2->z;
            if (pt[2] < cp[2]) {
                cross++;
            } else if (cp[0] == pt[0] && cp[2] == pt[2]) {
                return 1;
            }
        }
        p2 = v;
        v++;
    }

    return cross & 1;
}

int clip_floor_1(void *a0, int a1, int a2)
{
    float *ray = (float *)a0;
    FcFloorEnt *e = (FcFloorEnt *)a1;
    float hit[4];
    float nx = e->nx;
    float ex = ray[8];
    float ny = e->ny;
    float ey = ray[9];
    float nz = e->nz;
    float ez = ray[10];
    float pd = e->d;
    float sx;
    float sy;
    float sz;
    float de;
    float ds;
    float t;

    de = nx * ex + ny * ey + nz * ez + pd;
    if (a2 != 0) {
        if (de < 0.0f) {
            return 0;
        }
    } else {
        if (de >= 0.0f) {
            return 0;
        }
    }
    sx = ray[0];
    sy = ray[1];
    sz = ray[2];
    ds = nx * sx + ny * sy + nz * sz + pd;
    if (a2 != 0) {
        if (ds >= 0.0f) {
            return 0;
        }
    } else {
        if (ds < 0.0f) {
            return 0;
        }
    }
    t = 1.0f / (ds - de);
    hit[0] = (ex * ds - sx * de) * t;
    hit[1] = (ey * ds - sy * de) * t;
    hit[2] = (ez * ds - sz * de) * t;
    if (FloorPointInside(e, hit) == 0) {
        return 0;
    }
    sceVu0CopyVector((int *)(ray + 8), (int *)hit);
    return 1;
}

extern int game_pause;
extern int D_0063B13C;
extern int D_0063A064;
extern int D_0063A068;
extern int D_0063C210;
extern int D_0063C214;
extern int D_0063C218;
extern int D_0063C21C;
extern int D_0063C220;
extern int D_0063C224;
extern int D_0063C228;
extern int D_0063C22C;
extern int D_0063C230;
extern char D_005537A0[];
extern char D_005537B0[];
extern char D_005537C0[];
extern char D_005537D0[];
extern char D_006C0BC0[];

void DispCollisionPC(void)
{
    if (game_pause == 0) {
        return;
    }
    D_0063C220 = *(volatile int *)0x10000000 - D_0063C220;
    sprintf(D_006C0BC0, D_005537A0, D_0063C210, D_0063C224);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2, 0xFFFFFF00, D_006C0BC0);
    }
    sprintf(D_006C0BC0, D_005537B0, D_0063C214, D_0063C228);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2 + 8, 0xFFFFFF00, D_006C0BC0);
    }
    sprintf(D_006C0BC0, D_005537C0, D_0063C218, D_0063C22C);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2 + 0x10, 0xFFFFFF00, D_006C0BC0);
    }
    sprintf(D_006C0BC0, D_005537D0, D_0063C21C, D_0063C230);
    if (D_0063B13C & 1) {
        debug_Printf(D_0063A064 / 2, D_0063A068 / 2 + 0x18, 0xFFFFFF00, D_006C0BC0);
    }
}

extern int D_0063C234;
extern FuzioCtx *D_0063C238;
extern short D_006C10C0[];

void makeCollisionBlockTable(float *ray)
{
    int x0;
    int x1;
    int z0;
    int z1;
    int bx;
    int bz;
    int bx1;
    int bz1;
    int dx;
    int dz;
    int cx;
    int cz;
    int sx;
    int sz;
    int d;
    int err;
    int swap;
    int i;
    int t;
    int px;
    int pz;

    D_0063C234 = 0;
    x0 = (int)(ray[0] - D_0063C238->unk20[0]);
    x1 = (int)(ray[8] - D_0063C238->unk20[0]);
    z0 = (int)(ray[2] - D_0063C238->unk20[2]);
    z1 = (int)(ray[10] - D_0063C238->unk20[2]);
    bx = x0 >> 9;
    bz = z0 >> 9;
    dx = x1 - x0;
    dz = z1 - z0;
    if (dx != 0 || dz != 0) {
        bx1 = x1 >> 9;
        bz1 = z1 >> 9;
        cx = abs(bx1 - bx);
        cz = abs(bz1 - bz);
        sx = dx > 0 ? 1 : -1;
        sz = dz > 0 ? 1 : (dz < 0 ? -1 : 0);
        px = x0 - 256;
        pz = z0 - 256;
        d = (sx * sz * (dz * ((bx << 9) - px) - dx * ((bz << 9) - pz))) >> 8;
        dx = dx < 0 ? -dx : dx;
        dz = dz < 0 ? -dz : dz;
        swap = 0;
        if (dx < dz) {
            t = dx;
            dx = dz;
            dz = t;
            cx = cz;
            d = -d;
            swap = 1;
        }
        err = dz - dx + d;
        if (dx > 100000) {
            return;
        }
        for (i = 0; i <= cx; i++) {
            if (bx >= 0 && bx < 32 && bz >= 0 && bz < 32) {
                D_006C10C0[D_0063C234] = (bz << 5) + bx;
                D_0063C234 = D_0063C234 + 1;
            }
            while (err >= 0) {
                if (swap == 1) {
                    bx += sx;
                } else {
                    bz += sz;
                }
                if (bx >= 0 && bx < 32 && bz >= 0 && bz < 32) {
                    D_006C10C0[D_0063C234] = (bz << 5) + bx;
                    D_0063C234 = D_0063C234 + 1;
                }
                err -= dx * 2;
            }
            if (swap == 1) {
                bz += sz;
            } else {
                bx += sx;
            }
            err += dz * 2;
        }
    } else {
        if (bx >= 0 && bx < 32 && bz >= 0 && bz < 32) {
            D_006C10C0[D_0063C234] = (bz << 5) + bx;
            D_0063C234 = D_0063C234 + 1;
        }
    }
}

/* The clip-mode table the ClipWall/ClipFloor wrappers index by mode: modes
 * 0..11 are the wall entries, 12 on the floor ones (ClipFloor passes 0xC).
 * VMA 0x0029D200, 16-byte records, func at +0xC. splat splits the blob at
 * entry 12's func word (D_0029D2CC) because ClipFloorByGObj's load is the only
 * reference into the table's middle; D_0029D200 + 0xCC links to the same
 * address. */
typedef struct {
    int f_0;
    int f_4;
    int f_8;
    int (*func)(void *p, void *gobj, int mode);
} FcClipMode;

extern FcClipMode D_0029D200[];
extern float D_0029D310[16];
extern float D_0029D340[4];
extern float D_0029D350[4];
extern int D_0063C20C;
extern int (*D_0063C23C)(void *obj);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern float sceVu0InnerProduct(int a0, int a1);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *buf);

typedef union {
    float f[4];
    int i[4];
    long long ll[2];
} FcPlane;

/* listing lines 1470-1472: one static inline expanded in both tail arms */
static __inline__ void setClipPlane(char *self, void *m, void *v)
{
    FcPlane *n = (FcPlane *)(self + 0xA0);

    sceVu0ApplyMatrix(n, m, v);
    n->f[3] = -sceVu0InnerProduct((int)n, (int)(self + 0x20));
}

/* RECONSTRUCTION: the 0x15C sub-object slot of a gobj, read as the union of
 * its pointer and int-handle views. _Clip's wall-hit arm is the proof: the
 * ROM keeps the slot read behind both float stores to D_0029D350 while the
 * int reads of the ClipWork fields move ahead of them. Only an alias-set-0
 * read does that (a union member access, c_get_alias_set), where
 * typedef.h's int-typed GOBJ_SUB read or a plain pointer read lets the
 * scheduler hoist the chase and rotates the arm's registers. */
typedef union {
    char *sub;
    int handle;
} FcSubSlot;

void _Clip(char *self, int mode)
{
    float sv0[4];
    float sv1[4];
    float m0[16];
    float keep[4];
    float m1[16];
    FcPlane keep2;
    int (*func)(void *, void *, int);
    char *obj;
    char *sub;
    char *m;
    int cnt;
    int i;

    func = D_0029D200[mode].func;
    {
        int x = D_0029D200[mode].f_4;
        int y = D_0029D200[mode].f_8;

        sceVu0CopyVector((int *)sv0, (int *)self);
        sceVu0CopyVector((int *)sv1, (int *)(self + 0x10));
        sceVu0CopyVector((int *)(self + 0x20), (int *)(self + 0x10));
        D_0063C20C = 0;
        obj = (char *)D_006C0CC0[0];
        if (D_0063A818 > 0) {
            do {
                m = (char *)D_0029D310;
                sub = ((FcSubSlot *)(obj + 0x15C))->sub;
                if (*(int *)(sub + 0x74) != 0) {
                    if (x != 0) {
                        if (obj == *(char **)(self + 0x74)) {
                            if (*(int *)(self + 0x78) < 0) {
                                goto next_gobj;
                            }
                        }
                    }
                    if (y != 0) {
                        if (D_0063C23C(obj) == 0) {
                            goto next_gobj;
                        }
                    }
                    sub = ((FcSubSlot *)(obj + 0x15C))->sub;
                    cnt = 1;
                    if (*(int *)(sub + 0x80) != 0) {
                        cnt = *(int *)(sub + 0x8);
                    }
                    D_0063C238 = (FuzioCtx *)*(int *)(sub + 0x70);
                    for (i = 0; i < cnt; i++) {
                        if (x != 0) {
                            if (obj == *(char **)(self + 0x74) && i == *(int *)(self + 0x78) &&
                                *(int *)(self + 0x7C) == 0) {
                                continue;
                            }
                        }
                        CopyVector(keep, self + 0x20);
                        CopyVector(self, sv0);
                        if (*(int *)(((FcSubSlot *)(obj + 0x15C))->sub + 0x78) == 0) {
                            CopyVector(D_0029D340,
                                       *(char **)(((FcSubSlot *)(obj + 0x15C))->sub + 0xC) +
                                           (i << 6) + 0x30);
                        } else {
                            m = *(char **)(((FcSubSlot *)(obj + 0x15C))->sub + 0xC) + (i << 6);
                        }
                        MatrixDrive_SetTransposeMatrix(m0, m);
                        *(float *)(self + 0xC) = *(float *)(self + 0x2C) = 1.0f;
                        _ApplyMatrix(self, m0, self);
                        _ApplyMatrix(self + 0x20, m0, self + 0x20);
                        makeCollisionBlockTable((float *)self);
                        if (func(self, obj, i)) {
                            *(float *)(self + 0x2C) = 1.0f;
                            _ApplyMatrix(self + 0x20, m, self + 0x20);
                        } else {
                            CopyVector(self + 0x20, keep);
                        }
                    }
                }
            next_gobj:
                D_0063C20C = D_0063C20C + 1;
                obj = (char *)D_006C0CC0[D_0063C20C];
            } while (D_0063C20C < D_0063A818);
        }
        if (D_0029D200[mode].f_0 != 0) {
            if (*(int *)(self + 0x88) != 0) {
                D_0029D350[0] = (*(float **)(*(char **)(self + 0x88) + 0x4C))[0];
                D_0029D350[2] = (*(float **)(*(char **)(self + 0x88) + 0x4C))[1];
                CopyMatrix(m1,
                           *(char **)(((FcSubSlot *)(*(char **)(self + 0x80) + 0x15C))->sub + 0xC) +
                               (*(int *)(self + 0x84) << 6));
                if (*(int *)(((FcSubSlot *)(*(char **)(self + 0x80) + 0x15C))->sub + 0x78) == 0) {
                    UnitRotation(m1);
                }
                setClipPlane(self, m1, D_0029D350);
                *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x88) + 0x48);
            } else {
                sceVu0CopyVector((int *)(self + 0x20), (int *)sv1);
            }
        } else {
            if (*(int *)(self + 0x94) != 0) {
                CopyVector(&keep2, *(char **)(self + 0x94) + 0x40);
                keep2.i[3] = 0;
                CopyMatrix(m1,
                           *(char **)(((FcSubSlot *)(*(char **)(self + 0x8C) + 0x15C))->sub + 0xC) +
                               (*(int *)(self + 0x90) << 6));
                if (*(int *)(((FcSubSlot *)(*(char **)(self + 0x8C) + 0x15C))->sub + 0x78) == 0) {
                    UnitRotation(m1);
                }
                setClipPlane(self, m1, &keep2);
                *(int *)(self + 0x98) = *(int *)(*(char **)(self + 0x94) + 0x60);
            }
        }
        sceVu0CopyVector((int *)self, (int *)sv0);
        sceVu0CopyVector((int *)(self + 0x10), (int *)sv1);
    }
}

extern FcBlk8 D_0063A810;

void __ClipWall(ClipWork *a0, int a1)
{
    a0->f_B0 = 0;
    a0->floorHit = 0;
    a0->wallHit = 0;
    *(FcBlk8 *)a0->wallSrc = D_0063A810;
    _Clip(a0, a1);
}

void __ClipFloor(ClipWork *a0, int a1)
{
    a0->floorHit = 0;
    *(FcBlk8 *)a0->floorSrc = D_0063A810;
    _Clip(a0, a1);
}

/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void sceVu0UnitMatrix(void *m);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
extern int D_0063A848;
extern const FcColor D_0029D360;
extern const FcColor D_0029D370;
extern const FcColor D_0029D380;
extern const FcColor D_0029D390;
extern const FcColor D_0029D3A0;
extern const FcColor D_0029D3B0;
extern const FcColor D_0029D3C0;
extern const FcColor D_0029D3D0;

typedef struct {
    char _0[0x8];
    int nobj;  /* 0x8  */
    char *mtx; /* 0xC  */
    char _10[0x60];
    char *coll; /* 0x70 */
    char _74[0x4];
    int norot; /* 0x78 */
    char _7C[0x4];
    int multi; /* 0x80 */
} FcWallSub;

typedef struct {
    char _0[0x15C];
    FcWallSub *sub; /* 0x15C */
} FcWallObj;

typedef struct {
    char _0[0x8];
    int nwall; /* 0x8  */
    char _c[0x4];
    char *walls; /* 0x10 */
} FcWallSet;

void DrawGObjWallCollision(char *gobj, int col)
{
    FcWallObj *g = (FcWallObj *)gobj;
    FcWallSet *cd;
    char *e;
    const FcColor *c0;
    const FcColor *c1;
    int n;
    int i;
    int j;
    int attr;

    D_0063A848 = D_0063A848 + 1;
    n = 1;
    if (g->sub->multi != 0) {
        n = g->sub->nobj;
    }
    cd = (FcWallSet *)g->sub->coll;
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    gif_SetAlpha(1, 5, 0);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < n; i++) {
        CopyMatrix(MatrixDrive_GetMatrix(), g->sub->mtx + (i << 6));
        if (g->sub->norot == 0) {
            UnitRotation(MatrixDrive_GetMatrix());
        }
        for (j = 0; j < cd->nwall; j++) {
            e = cd->walls + j * 0x50;
            c0 = &D_0029D360;
            c1 = &D_0029D3A0;
            attr = *(int *)(e + 0x48);
            if ((attr & 0xF0000000) != 0) {
                c0 = &D_0029D380;
                c1 = &D_0029D3C0;
                if ((attr & 0x10000000) != 0) {
                    c0 = &D_0029D390;
                    c1 = &D_0029D3D0;
                }
            } else if (attr != 0) {
                c0 = &D_0029D370;
                c1 = &D_0029D3B0;
            }
            DrawLineG(e, (void *)c0, e + 0x10, (void *)c0, col);
            DrawLineG(e + 0x10, (void *)c0, e + 0x30, (void *)c0, col);
            DrawLineG(e + 0x30, (void *)c0, e + 0x20, (void *)c0, col);
            DrawLineG(e + 0x20, (void *)c0, e, (void *)c0, col);
            DrawLineG(e, (void *)c1, e + 0x10, (void *)c1, -1);
            DrawLineG(e + 0x10, (void *)c1, e + 0x30, (void *)c1, -1);
            DrawLineG(e + 0x30, (void *)c1, e + 0x20, (void *)c1, -1);
            DrawLineG(e + 0x20, (void *)c1, e, (void *)c1, -1);
        }
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

extern const FcColor D_00553820;

void DrawGObjFloorCollision(char *gobj, int col)
{
    FcColor c;
    int n;
    char *cd;
    char *e;
    int i;
    int j;

    n = 1;
    if (GOBJ_SUB(gobj)->f_80 != 0) {
        n = GOBJ_SUB(gobj)->f_8;
    }
    cd = *(char **)((char *)GOBJ_SUB(gobj) + 0x70);
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    gif_SetAlpha(1, 5, 0);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < n; i++) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(char **)((char *)GOBJ_SUB(gobj) + 0xC) + (i << 6));
        if (GOBJ_SUB(gobj)->f_78 == 0) {
            UnitRotation(MatrixDrive_GetMatrix());
        }
        for (j = 0; j < *(int *)(cd + 0xC); j++) {
            e = *(char **)(cd + 0x14) + j * 0x70;
            c = D_00553820;
            DrawLineG(e, &c, e + 0x10, &c, col);
            if (*(int *)(e + 0x54) == 0) {
                DrawLineG(e + 0x10, &c, e + 0x20, &c, col);
                DrawLineG(e + 0x20, &c, e, &c, col);
            } else {
                DrawLineG(e + 0x10, &c, e + 0x20, &c, col);
                DrawLineG(e + 0x20, &c, e + 0x30, &c, col);
                DrawLineG(e + 0x30, &c, e, &c, col);
            }
        }
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

extern char D_00553830[];

void DBG_VECTOR(float *vec)
{
    return debug_StdPrintfDummy(D_00553830, vec[0], vec[1], vec[2]);
}

INCLUDE_ASM("asm/nonmatchings/ico2/fumi/src/fieldCollision", GetEdgeOfFloor);

extern void sceVu0SubVector(void *dst, void *a, void *b);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int a0);
extern const FcColor D_00553940;
extern const FcColor D_00553950;

void DrawCollisionRay(char *ray)
{
    FcColor c0;
    FcColor c1;
    float d[4];
    float p1[4];
    float p0[4];
    float v[4];
    float len;

    c0 = D_00553940;
    c1 = D_00553950;
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    memset(v, 0, 16);
    v[3] = 1.0f;
    gif_SetAlpha(1, 5, 128);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(ray, &c0, ray + 0x10, &c0, 0);
    DrawLineG(ray, &c1, ray + 0x10, &c1, -1);
    sceVu0SubVector(d, ray + 0x10, ray);
    MatrixDrive_TransMatrixV(ray + 0x10);
    MatrixDrive_TurnYObjectMatrixXZ(d[0], d[1], d[2]);
    len = FSqrt(sceVu0InnerProduct((int)d, (int)d));
    v[0] = len * 0.05f;
    v[1] = len * 0.3f;
    sceVu0ApplyMatrix(p0, MatrixDrive_GetMatrix(), v);
    v[0] = -len * 0.05f;
    sceVu0ApplyMatrix(p1, MatrixDrive_GetMatrix(), v);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(p0, &c0, ray + 0x10, &c0, 0);
    DrawLineG(p1, &c0, ray + 0x10, &c0, 0);
    DrawLineG(p0, &c1, ray + 0x10, &c1, -1);
    DrawLineG(p1, &c1, ray + 0x10, &c1, -1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(ray + 0x20);
    MatrixDrive_TurnYObjectMatrixXZ(d[0], d[1], d[2]);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

extern char D_00553960[];
extern char D_00553980[];
extern int frame_count;
extern int D_0063C240;
extern void *D_006C1140[];

void MakeExitAttributeIndex(void)
{
    int i;
    char *entry;
    int j;
    int n;
    int *p70;
    void *obj;
    int slot;

    debug_StdPrintfDummy(D_00553960, frame_count);
    D_0063C240 = 0;
    i = 0xF;
    do {
        D_006C1140[i] = 0;
        i--;
    } while (i >= 0);
    D_0063C20C = 0;
    obj = D_006C0CC0[0];
    if (D_0063A818 > 0) {
        do {
            p70 = (int *)GOBJ_SUB(obj)->f_70;
            for (j = 0; j < p70[0xC / 4]; j++) {
                entry = (char *)p70[0x14 / 4] + j * 0x70;
                slot = *(int *)(entry + 0x60) & 0xF;
                if (slot != 0) {
                    if (D_006C1140[slot] == 0) {
                        debug_StdPrintfDummy(D_00553980, slot);
                        D_0063C240 = D_0063C240 + 1;
                        D_006C1140[slot] = entry;
                    }
                }
            }
            D_0063C20C = D_0063C20C + 1;
            obj = D_006C0CC0[D_0063C20C];
        } while (D_0063C20C < D_0063A818);
    }
}

void ClipFloorByGObj(char *p, char *gobj)
{
    float buf0[4];
    float buf1[4];
    float mtx[16];
    FcPlane keep;
    int (*clip)(void *, void *, int);
    char *m;
    char *ep;
    char *pos;

    clip = D_0029D200[12].func;
    sceVu0CopyVector((int *)buf0, (int *)p);
    sceVu0CopyVector((int *)buf1, (int *)(p + 0x10));
    pos = p + 0x20;
    sceVu0CopyVector((int *)pos, (int *)(p + 0x10));
    D_0063C238 = (FuzioCtx *)*(int *)(((FcSubSlot *)(gobj + 0x15C))->sub + 0x70);
    ep = pos;
    CopyVector(&keep, ep);
    CopyVector(p, buf0);
    /* Dead reset of the scratch pointer (flow deletes it; SRCFILE.TXT line
     * 2244 has no instructions). What the bytes pin: some set of pos after
     * the ep copy and before the clip call, because otherwise gcse records
     * `ep = pos` as an available copy and propagates pos into the if arms.
     * pos then lives past block 0 and local-alloc no longer puts it in $16
     * ahead of gobj ($17) and clip ($18). What they cannot pin: the value,
     * the spelling or the line of that set. */
    pos = 0;
    m = *(char **)(((FcSubSlot *)(gobj + 0x15C))->sub + 0xC);
    MatrixDrive_SetTransposeMatrix(mtx, (float *)m);
    *(float *)(p + 0xC) = *(float *)(p + 0x2C) = 1.0f;
    _ApplyMatrix(p, mtx, p);
    _ApplyMatrix(ep, mtx, ep);
    makeCollisionBlockTable((float *)p);
    if (clip(p, gobj, 0)) {
        *(float *)(p + 0x2C) = 1.0f;
        _ApplyMatrix(ep, m, ep);
    } else {
        CopyVector(ep, &keep);
    }
    if (*(int *)(p + 0x94) != 0) {
        FcPlane *n;

        CopyVector(&keep, *(char **)(p + 0x94) + 0x40);
        keep.i[3] = 0;
        CopyMatrix(mtx, *(char **)(((FcSubSlot *)(*(char **)(p + 0x8C) + 0x15C))->sub + 0xC) +
                            (*(int *)(p + 0x90) << 6));
        if (*(int *)(((FcSubSlot *)(*(char **)(p + 0x8C) + 0x15C))->sub + 0x78) == 0) {
            UnitRotation(mtx);
        }
        n = (FcPlane *)(p + 0xA0);
        sceVu0ApplyMatrix(n, mtx, &keep);
        n->f[3] = -sceVu0InnerProduct((int)n, (int)ep);
        *(int *)(p + 0x98) = *(int *)(*(char **)(p + 0x94) + 0x60);
    }
    sceVu0CopyVector((int *)p, (int *)buf0);
    sceVu0CopyVector((int *)(p + 0x10), (int *)buf1);
}

extern int (*D_0063A840)(void *a0, int a1);

int ClipWallDebug(void *a0)
{
    return D_0063A840(a0, 0);
}

int ClipWall(void *a0)
{
    return D_0063A840(a0, 0x1);
}

int ClipWallR(void *a0)
{
    return D_0063A840(a0, 0x2);
}

int ClipWallWaveForce(void *a0)
{
    return D_0063A840(a0, 0x6);
}

int ClipWallFuchiHangWalkStop(void *a0)
{
    return D_0063A840(a0, 0x7);
}

int ClipWallField(void *a0)
{
    return D_0063A840(a0, 0x3);
}

int ClipWallEField(void *a0)
{
    return D_0063A840(a0, 0x5);
}

int ClipWallBoxStop(void *a0)
{
    return D_0063A840(a0, 0xA);
}

int ClipWallAdjustPos(void *a0)
{
    return D_0063A840(a0, 0xB);
}

int ClipWallE(void *a0)
{
    return D_0063A840(a0, 0x4);
}

void ClipWallCheckCB(void *a0, int a1)
{
    D_0063C23C = (int (*)(void *))a1;
    D_0063A840(a0, 8);
}

void ClipWallFieldCheckCB(void *a0, int a1)
{
    D_0063C23C = (int (*)(void *))a1;
    D_0063A840(a0, 9);
}

extern int (*D_0063A844)(void *a0, int a1);

int ClipFloor(void *a0)
{
    return D_0063A844(a0, 0xC);
}

int ClipFloorE(void *a0)
{
    return D_0063A844(a0, 0xD);
}

int ClipFloorR(void *a0)
{
    return D_0063A844(a0, 0xE);
}

int ClipFloorIH(void *a0)
{
    return D_0063A844(a0, 0xF);
}

void ClipFloorCheckCB(void *a0, int a1)
{
    D_0063C23C = (int (*)(void *))a1;
    D_0063A844(a0, 0x10);
}

void ClipCollision(int *self)
{
    int buf[4];
    int *p10 = self + 4;
    sceVu0CopyVector(buf, p10);
    D_0063A840((int)self, 1);
    sceVu0CopyVector(p10, self + 8);
    D_0063A844((int)self, 0xC);
    sceVu0CopyVector(p10, buf);
}

int ChangeFieldCollisionDebugMode(int a0)
{
    D_0063A840 = (int (*)(void *, int))__ClipWall;
    D_0063A844 = (int (*)(void *, int))__ClipFloor;
    if (a0 != 0) {
        D_0063A840 = (int (*)(void *, int))__ClipWallWithDrawRay;
        D_0063A844 = (int (*)(void *, int))__ClipFloorWithDrawRay;
    }
    return 0;
}

void LoadCollision(int *self, int a1)
{
    int new_var;
    int *p;
    file_LoadFile((int)self, a1, 0);
    p = (int *)self[0];
    new_var = 0x14 / 4;
    p[0x10 / 4] = (int)(((char *)p) + p[0x10 / 4]);
    p[0x14 / 4] = (int)(((char *)p) + p[new_var]);
}

void DrawCollision(int a0)
{
    int n = a0;
    void *obj;

    if (n > 0) {
        n = -1;
    }
    gif_StartPacketPri(11);
    gif_SetZTest(1);
    gif_EndPacket();
    D_0063C20C = 0;
    obj = D_006C0CC0[0];
    if (D_0063A818 > 0) {
        do {
            DrawGObjWallCollision(obj, n);
            D_0063C20C = D_0063C20C + 1;
            obj = D_006C0CC0[D_0063C20C];
        } while (D_0063C20C < D_0063A818);
    }
    D_0063C20C = 0;
    obj = D_006C0CC0[0];
    if (D_0063A818 > 0) {
        do {
            DrawGObjFloorCollision(obj, n);
            D_0063C20C = D_0063C20C + 1;
            obj = D_006C0CC0[D_0063C20C];
        } while (D_0063C20C < D_0063A818);
    }
}

int ClipPlane(int a0)
{
    float *p = (float *)a0;
    char *q = (char *)(a0 + 0xA0);
    float t0, t1, d;

    sceVu0CopyVector((int *)(a0 + 0x20), (int *)(a0 + 0x10));
    t0 = sceVu0InnerProduct((int)q, a0 + 0x10) + *(float *)(q + 0xC);
    if (t0 >= 0.0f) {
        return 0;
    }
    t1 = sceVu0InnerProduct((int)q, a0) + *(float *)(q + 0xC);
    if (t1 < 0.0f) {
        if (t0 < 0.0f) {
            return 0;
        }
    }
    d = t1 - t0;
    p[8] = (p[4] * t1 - p[0] * t0) / d;
    p[9] = (p[5] * t1 - p[1] * t0) / d;
    p[10] = (p[6] * t1 - p[2] * t0) / d;
    return 1;
}

extern char D_005538C8[];
extern char D_005538F8[];

void GetOrientOfWall(void *a0, void *a1, int *a2)
{
    float buf[4];
    int *var_19;
    void *obj = (void *)a2[0];

    if (a1 == 0) {
        buf[1] = 0.0f;
        buf[2] = 1.0f;
        var_19 = 0;
        buf[0] = 0.0f;
        debug_StdPrintfDummy(D_005538C8);
    } else {
        var_19 = (int *)1;
        buf[0] = -GetTableSin((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[1] = 0.0f;
        buf[2] = GetTableCos((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[3] = 1.0f;
    }
    if (var_19 == 0) {
        CopyVector((void *)a0, (void *)buf);
        *var_19 = 0;
        return;
    }
    *(int *)&buf[3] = 0;
    {
        int *temp_3 = (int *)(int)GOBJ_SUB(obj);
        if (temp_3 != 0 && *(int *)((char *)temp_3 + 0xC) != 0) {
            if (*(int *)((char *)temp_3 + 0x78) != 0) {
                int *p5 = (int *)a2[0];
                int idx = a2[1];
                int *o3 = (int *)(int)GOBJ_SUB(p5);
                sceVu0ApplyMatrix(a0, (void *)(*(int *)((char *)o3 + 0xC) + (idx << 6)), buf);
                return;
            }
            CopyVector((void *)a0, (void *)buf);
            return;
        }
        debug_StdPrintfDummy(D_005538F8);
    }
}

void SetSimplePlane(float *self, float a, float b, float c, float d)
{
    self[0] = a;
    self[1] = b;
    self[2] = c;
    self[3] = d;
}

int GetWallAttribute(int a0)
{
    if (*(int *)(a0 + 0x88) == 0)
        return 0;
    return *(int *)(a0 + 0x98);
}

int GetFloorAttribute(int a0)
{
    if (*(int *)(a0 + 0x94) == 0)
        return 0;
    return *(int *)(a0 + 0x98);
}

int CompareAttribute(unsigned int a, unsigned int b)
{
    int i;
    if ((a & b) == 0)
        return 0;
    for (i = 0; i < 8; i++) {
        unsigned int da = (a >> (i * 4)) & 0xF;
        unsigned int db = (b >> (i * 4)) & 0xF;
        if (da != 0 && db != 0 && da == db)
            return 1;
    }
    return 0;
}

typedef union {
    float f[4];
    long long ll[2];
} FcVec;

static inline void getWallGlobalInfo(char *pts, void *nrm, char *w, void *m)
{
    FcVec vec = {
        {GetTableSin(*(short *)(w + 0x44)), 0.0f, GetTableCos(*(short *)(w + 0x44)), 0.0f}};
    int i;

    if (pts != 0) {
        char *src = w;
        char *dst = pts;
        for (i = 3; i >= 0; i--) {
            sceVu0ApplyMatrix(dst, m, src);
            src += 0x10;
            dst += 0x10;
        }
    }
    sceVu0ApplyMatrix(nrm, m, &vec);
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
   GetWallGlobalInfo into DrawGObjWallCollision, so it is `inline` in the dev's TU;
   while this tail still has asm members the public body stays a plain definition
   at its ROM slot (before GetDistanceFromPlane) and the caller uses the static
   stand-in getWallGlobalInfo. Collapses to one `inline` definition at layout. */
void GetWallGlobalInfo(char *pts, void *nrm, char *w, void *m)
{
    FcVec vec = {
        {GetTableSin(*(short *)(w + 0x44)), 0.0f, GetTableCos(*(short *)(w + 0x44)), 0.0f}};
    int i;

    if (pts != 0) {
        char *src = w;
        char *dst = pts;
        for (i = 3; i >= 0; i--) {
            sceVu0ApplyMatrix(dst, m, src);
            src += 0x10;
            dst += 0x10;
        }
    }
    sceVu0ApplyMatrix(nrm, m, &vec);
}

float GetDistanceFromPlane(void *a0, void *a1)
{
    return sceVu0InnerProduct((int)a0, (int)a1) + ((float *)a0)[3];
}

float GetYDistanceFromPlane(float *a0, float *a1)
{
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}

float GetYProjectionOfPlane(float *a0, float *a1)
{
    return -(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1];
}

void ResetCollisionPC(void)
{
    int tmp;
    D_0063C210 = 0;
    tmp = *(volatile int *)0x10000000;
    D_0063C214 = 0;
    D_0063C220 = tmp;

    D_0063C218 = 0;
    D_0063C21C = 0;
    D_0063C224 = 0;
    D_0063C228 = 0;
    D_0063C22C = 0;
    D_0063C230 = 0;
}

int PositionOfExit(int a0, int a1)
{
    int v = (int)D_006C1140[a1 & 0xF];
    if (v != 0) {
        CopyVector(a0, v);
        return 0;
    }
    return 1;
}

void GetGlobalWallPlane(float *plane, int *r)
{
    FcVec pts[4];

    getWallGlobalInfo((char *)pts, plane, (char *)r[2],
                      (void *)((r[1] << 6) + *(int *)(*(int *)(r[0] + 0x15C) + 0xC)));
    plane[3] = -sceVu0InnerProduct((int)plane, (int)pts);
}

int _clipWDebug(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                if (clip_wall_1(arg0, e, 0, 1) != 0) {
                    arg0->wallHit = e;
                    ret = 1;
                    arg0->wallSrc[0] = arg1;
                    arg0->wallSrc[1] = arg2;
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipW(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0xF0000000) == 0) {
                    if ((val & 0xF0000) != 0x10000) {
                        if (clip_wall_1(arg0, e, 0, 1) != 0) {
                            arg0->wallHit = e;
                            ret = 1;
                            arg0->wallSrc[0] = arg1;
                            arg0->wallSrc[1] = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipWE(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0xF0000000) == 0) {
                    if ((val & 0xF0000) != 0x10000) {
                        if (arg1 != arg0->skipSrc[0] || arg2 != arg0->skipSrc[1] ||
                            e != arg0->skipElem) {
                            if (clip_wall_1(arg0, e, 0, 0) != 0) {
                                arg0->wallHit = e;
                                ret = 1;
                                arg0->wallSrc[0] = arg1;
                                arg0->wallSrc[1] = arg2;
                            }
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipWEField(ClipWork *arg0, int arg1, int arg2)
{
    int found = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                if ((*(int *)(e + 0x48) & 0xF0000000) == 0) {
                    if (arg1 != arg0->skipSrc[0] || arg2 != arg0->skipSrc[1] ||
                        e != arg0->skipElem) {
                        if (clip_wall_1(arg0, e, 0, 0) != 0) {
                            arg0->wallHit = e;
                            found = 1;
                            arg0->wallSrc[0] = arg1;
                            arg0->wallSrc[1] = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return found;
}

int _clipWR(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0xF0000000) == 0) {
                    if ((val & 0xF0000) != 0x10000) {
                        if (clip_wall_1(arg0, e, 1, 1) != 0) {
                            arg0->wallHit = e;
                            ret = 1;
                            arg0->wallSrc[0] = arg1;
                            arg0->wallSrc[1] = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipWField(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                if ((*(int *)(e + 0x48) & 0xF0000000) == 0) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        arg0->wallHit = e;
                        ret = 1;
                        arg0->wallSrc[0] = arg1;
                        arg0->wallSrc[1] = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipWDitchHangWalkStop(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                if ((*(int *)(e + 0x48) & 0x30000000) != 0) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        arg0->wallHit = e;
                        ret = 1;
                        arg0->wallSrc[0] = arg1;
                        arg0->wallSrc[1] = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipWWaveForce(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                if ((*(int *)(e + 0x48) & 0xC0000000) == 0x40000000) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        arg0->wallHit = e;
                        ret = 1;
                        arg0->wallSrc[0] = arg1;
                        arg0->wallSrc[1] = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipWBoxStop(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                int val = *(int *)(e + 0x48);
                if ((val & 0x70000000) == 0) {
                    if ((val & 0xF0000) != 0x10000 || (val & 0xC0000000) == 0x80000000) {
                        if (clip_wall_1(arg0, e, 0, 1) != 0) {
                            arg0->wallHit = e;
                            ret = 1;
                            arg0->wallSrc[0] = arg1;
                            arg0->wallSrc[1] = arg2;
                        }
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipWAdjustPos(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk18[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk10 + (int)*p * 0x50;
                if ((*(int *)(e + 0x48) & 0xC0000000) == 0xC0000000) {
                    if (clip_wall_1(arg0, e, 0, 1) != 0) {
                        arg0->wallHit = e;
                        ret = 1;
                        arg0->wallSrc[0] = arg1;
                        arg0->wallSrc[1] = arg2;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipF(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int)*p * 0x70;
                if (clip_floor_1(arg0, e, 0) != 0) {
                    arg0->floorHit = e;
                    ret = 1;
                    arg0->floorSrc[0] = arg1;
                    arg0->floorSrc[1] = arg2;
                    arg0->wallHit = 0;
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipFE(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int)*p * 0x70;
                if (arg1 != arg0->skipSrc[0] || arg2 != arg0->skipSrc[1] || e != arg0->skipElem) {
                    if (clip_floor_1(arg0, e, 0) != 0) {
                        arg0->floorHit = e;
                        ret = 1;
                        arg0->floorSrc[0] = arg1;
                        arg0->floorSrc[1] = arg2;
                        arg0->wallHit = 0;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipFIH(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int)*p * 0x70;
                if ((*(int *)(e + 0x60) & 0xF0000) != 0x20000) {
                    if (clip_floor_1(arg0, e, 0) != 0) {
                        arg0->floorHit = e;
                        ret = 1;
                        arg0->floorSrc[0] = arg1;
                        arg0->floorSrc[1] = arg2;
                        arg0->wallHit = 0;
                    }
                }
                p++;
            }
        }
    }
    return ret;
}

int _clipFR(ClipWork *arg0, int arg1, int arg2)
{
    int ret = 0;
    int i;

    for (i = 0; i < D_0063C234; i++) {
        short *p = D_0063C238->unk1C[D_006C10C0[i]];
        if (p != 0) {
            while (*p >= 0) {
                int e = D_0063C238->unk14 + (int)*p * 0x70;
                if (clip_floor_1(arg0, e, 1) != 0) {
                    arg0->floorHit = e;
                    ret = 1;
                    arg0->floorSrc[0] = arg1;
                    arg0->floorSrc[1] = arg2;
                    arg0->wallHit = 0;
                }
                p++;
            }
        }
    }
    return ret;
}

extern const FcColor D_005537E0;
extern const FcColor D_005537F0;

void __ClipWallWithDrawRay(char *w, int a1)
{
    FcColor c0;
    FcColor c1;

    __ClipWall(w, a1);
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    c0 = D_005537E0;
    c1 = D_005537F0;
    gif_SetAlpha(1, 5, 0x80);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(w, &c0, w + 0x10, &c0, 0);
    DrawLineG(w, &c1, w + 0x10, &c1, -1);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

extern const FcColor D_00553800;
extern const FcColor D_00553810;

void __ClipFloorWithDrawRay(char *w, int a1)
{
    FcColor c0;
    FcColor c1;

    __ClipFloor(w, a1);
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    c0 = D_00553800;
    c1 = D_00553810;
    gif_SetAlpha(1, 5, 0x80);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(w, &c0, w + 0x10, &c0, 0);
    DrawLineG(w, &c1, w + 0x10, &c1, -1);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

extern int collision_pick;

void ClipWallRD(void)
{
    collision_pick = 1;
    /* Cast away the (int) prototype so gcc doesn't emit `daddu $a0,$0,$0`
     * to set up an arg the original call didn't pass. The implementation
     * happens to read $a0 but the original cross-TU caller didn't bother
     * to clear it. */
    ((void (*)(void))ClipWall)();
    collision_pick = 0;
}

int ClipWallVector(int *a0, int *a1)
{
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    sceVu0CopyVector(buf, a0);
    sceVu0CopyVector(buf + 4, a1);
    D_0063A840(buf, 1);
    return buf[34];
}

void MapCollisionData(void *a0)
{
    int *p = (int *)a0;
    p[4] = (int)a0 + p[4];
    p[5] = (int)a0 + p[5];
}
