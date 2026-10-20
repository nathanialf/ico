#include "typedef.h"
#include "fieldCollision.h"
#include "gobj.h"
#include "debug.h"
#include "debug_exception.h"
#include "FileManager.h"
#include "lineManager.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include "sugiCommon.h"
#include <stdio.h>
#include <string.h>
#include "GsBase.h"
#include <eeregs.h>
#include "main.h"
#include "Matrix.h"
#include <libvu0.h>
#include "GifPacket.h"
#include <assert.h>
#include "include_asm.h"

typedef struct { /* field names derived */
    char pad0[16];
    FcWallEnt *walls; /* 0x10 */
    FcFloorEnt *fcl;  /* 0x14, the floor list (charFileManager.c's names) */
    short **wblk;     /* 0x18, per block, the walls' indices, ended by a negative one */
    short **fblk;     /* 0x1C, per block, the floors' indices */
    float *ofs;       /* 0x20, the origin the blocks are counted from */
} FuzioCtx;           /* derived name */

/* One line colour of the collision display: red, green, blue, alpha. */
typedef struct { /* field names derived */
    int rgba[4];
} FcColor; /* derived name */

typedef int (*FcFunc)(void *work, int mode);

/* fieldCollision.o's .sbss and .bss.  .sbss: the number of objects in the
   collision list, the nine collision statistics DispCollisionPC prints (a
   pair per format, wall, wall R, floor, floor R, with the timer between the
   two halves; the retail build only resets them), the number of block-table
   entries, the fuzio context the current object carries, the filter the list
   builder asks, and the number of exit-attribute slots in use. */
static int colObjNum; /* derived name */

static int pcWall0; /* derived name */

static int pcWallR0; /* derived name */

static int pcFloor0; /* derived name */

static int pcFloorR0; /* derived name */

static int pcTime; /* derived name */

static int pcWall1; /* derived name */

static int pcWallR1; /* derived name */

static int pcFloor1; /* derived name */

static int pcFloorR1; /* derived name */

static int blockNum; /* derived name */

static FuzioCtx *curFuzio; /* derived name */

static int (*colFilter)(void *obj);

static int exitAttrNum; /* derived name */

/* .bss: DispCollisionPC's line buffer, the collision object list, the block
   table and the exit-attribute slots. */
static char pcLine[256]; /* derived name */

static void *colObjList[256]; /* derived name */

static short blockTable[64]; /* derived name */

static void *exitAttr[16]; /* derived name */

/* .data: InitialColInfo here, the debug label table in
   MakeCollisionDependGObjList's disabled block, then the clip mode table, the
   clip work matrix and the plane point after the clip functions and the wall
   line colours before DrawGObjWallCollision.
   .sdata, in emission order: the four variables here, the assert text "e",
   the three labels, the two clip function pointers and the wall draw count,
   then GetEdgeOfFloor's three strings.  No code reads the word before
   collision_pick. */
WallCfg InitialColInfo = {{0, -1}, 0};

/* the debug label table of MakeCollisionDependGObjList's disabled block: three .sdata label pointers */
INCLUDE_ASM(D_0026AF20);

static int fcReserved = 0; /* derived name */

int collision_pick = 0;

ObjNode InitialObjPointer = {0, -1};

static int colObjListNum = 0; /* derived name */

INCLUDE_ASM(MakeCollisionDependGObjList);

INCLUDE_ASM(D_00679E28);

void GetReflectionElement(ClipWork *work, float arg0, float arg1)
{
    float buf0[4];
    float L10[4];
    float L20[4];
    float z;

    CopyVector(L10, &work->normal);
    *(int *)&L10[3] = 0;
    sceVu0SubVector(buf0, work->pt[1], work->pt[0]);
    sceVu0ScaleVector(work->reflect.bounce, L10, -GetDistanceFromPlane(L10, buf0));
    sceVu0AddVector(work->reflect.slide, buf0, work->reflect.bounce);
    sceVu0ScaleVectorXYZ(work->reflect.bounce, work->reflect.bounce, arg1);
    sceVu0ScaleVectorXYZ(work->reflect.slide, work->reflect.slide, arg0);
    sceVu0AddVector(work->reflect.dir, work->reflect.slide, work->reflect.bounce);
    {
        float *p20 = L20;
        z = GetPointDistance(work->pt[2], work->pt[1]);
        sceVu0ScaleVector(p20, work->reflect.dir, z / GetPointDistance(work->pt[0], work->pt[1]));
        sceVu0AddVector(work->reflect.pos, work->pt[2], p20);
    }
}

/* the absolute value clip_wall_1 inlines five times */
static __inline__ float FcAbsF(float v) /* derived name */
{
    if (v < 0.0f) {
        v = -v;
    }
    return v;
}

static int clip_wall_1(ClipWork *ray, FcWallEnt *wall, int flip, int useh);

INCLUDE_ASM(clip_wall_1);

static __inline__ int FloorPointInside(FcFloorEnt *e, float *pt) /* derived name */
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
    /* indexed, not walked: every expansion rebuilds &e->v[i] each pass */
    p2 = &e->v[n];
    for (i = 0; i <= n; i++) {
        v = &e->v[i];
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
    }

    return cross & 1;
}

static int clip_floor_1(ClipWork *ray, FcFloorEnt *e, int backFace)
{
    float hit[4];
    float nx = e->nx;
    float ex = ray->pt[2][0];
    float ny = e->ny;
    float ey = ray->pt[2][1];
    float nz = e->nz;
    float ez = ray->pt[2][2];
    float pd = e->d;
    float sx;
    float sy;
    float sz;
    float de;
    float ds;
    float t;

    de = nx * ex + ny * ey + nz * ez + pd;
    if (backFace != 0) {
        if (de < 0.0f) {
            return 0;
        }
    } else {
        if (de >= 0.0f) {
            return 0;
        }
    }
    sx = ray->pt[0][0];
    sy = ray->pt[0][1];
    sz = ray->pt[0][2];
    ds = nx * sx + ny * sy + nz * sz + pd;
    if (backFace != 0) {
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
    sceVu0CopyVector((int *)ray->pt[2], (int *)hit);
    return 1;
}

void DispCollisionPC(void)
{
    if (game_pause == 0) {
        return;
    }
    pcTime = *T0_COUNT - pcTime;
    sprintf(pcLine, "W :%4d %2d", pcWall0, pcWall1);
    if (debug_font_flag & 1) {
        debug_Printf(ScreenWidth / 2, ScreenHeight / 2, 0xFFFFFF00, pcLine);
    }
    sprintf(pcLine, "WR:%4d %2d", pcWallR0, pcWallR1);
    if (debug_font_flag & 1) {
        debug_Printf(ScreenWidth / 2, ScreenHeight / 2 + 8, 0xFFFFFF00, pcLine);
    }
    sprintf(pcLine, "F :%4d %2d", pcFloor0, pcFloor1);
    if (debug_font_flag & 1) {
        debug_Printf(ScreenWidth / 2, ScreenHeight / 2 + 0x10, 0xFFFFFF00, pcLine);
    }
    sprintf(pcLine, "FR:%4d %2d", pcFloorR0, pcFloorR1);
    if (debug_font_flag & 1) {
        debug_Printf(ScreenWidth / 2, ScreenHeight / 2 + 0x18, 0xFFFFFF00, pcLine);
    }
}

static void makeCollisionBlockTable(float *ray)
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

    blockNum = 0;
    x0 = (int)(ray[0] - curFuzio->ofs[0]);
    x1 = (int)(ray[8] - curFuzio->ofs[0]);
    z0 = (int)(ray[2] - curFuzio->ofs[2]);
    z1 = (int)(ray[10] - curFuzio->ofs[2]);
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
                blockTable[blockNum] = (bz << 5) + bx;
                blockNum = blockNum + 1;
            }
            while (err >= 0) {
                if (swap == 1) {
                    bx += sx;
                } else {
                    bz += sz;
                }
                if (bx >= 0 && bx < 32 && bz >= 0 && bz < 32) {
                    blockTable[blockNum] = (bz << 5) + bx;
                    blockNum = blockNum + 1;
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
            blockTable[blockNum] = (bz << 5) + bx;
            blockNum = blockNum + 1;
        }
    }
}

static inline int _clipWDebug(ClipWork *work, GObj *obj, int node);
static inline int _clipW(ClipWork *work, GObj *obj, int node);
static inline int _clipWE(ClipWork *work, GObj *obj, int node);
static inline int _clipWEField(ClipWork *work, GObj *obj, int node);
static inline int _clipWR(ClipWork *work, GObj *obj, int node);
static inline int _clipWField(ClipWork *work, GObj *obj, int node);
static inline int _clipWDitchHangWalkStop(ClipWork *work, GObj *obj, int node);
static inline int _clipWWaveForce(ClipWork *work, GObj *obj, int node);
static inline int _clipWBoxStop(ClipWork *work, GObj *obj, int node);
static inline int _clipWAdjustPos(ClipWork *work, GObj *obj, int node);
static inline int _clipF(ClipWork *work, GObj *obj, int node);
static inline int _clipFE(ClipWork *work, GObj *obj, int node);
static inline int _clipFIH(ClipWork *work, GObj *obj, int node);
static inline int _clipFR(ClipWork *work, GObj *obj, int node);

/* The clip-mode table the ClipWall/ClipFloor wrappers index by mode: modes
 * 0..11 are the wall entries, 12 on the floor ones (ClipFloor passes 0xC).
 * 16-byte records, func at +0xC (ClipFloorByGObj reads entry 12's
 * directly). */
typedef struct {      /* field names derived */
    int wall;         /* the wall-hit arm runs after the walk (modes 0..11) */
    int skipFilter;   /* skip the work's filter object and node */
    int useColFilter; /* only objects colFilter passes */
    int (*func)(ClipWork *work, GObj *obj, int node);
} FcClipMode; /* derived name */

/* The clip modes, then the work matrix whose translation row _Clip sets for
   an unrotated object, and the plane point of the wall hit arm. */
static FcClipMode clipMode[17] = {
    /* derived name */
    {1, 0, 0, _clipWDebug},     {1, 0, 0, _clipW},
    {1, 0, 0, _clipWR},         {1, 0, 0, _clipWField},
    {1, 1, 0, _clipWE},         {1, 1, 0, _clipWEField},
    {1, 0, 0, _clipWWaveForce}, {1, 0, 0, _clipWDitchHangWalkStop},
    {1, 0, 1, _clipW},          {1, 0, 1, _clipWField},
    {1, 0, 0, _clipWBoxStop},   {1, 0, 0, _clipWAdjustPos},
    {0, 0, 0, _clipF},          {0, 1, 0, _clipFE},
    {0, 0, 0, _clipFR},         {0, 0, 0, _clipFIH},
    {0, 0, 1, _clipF},
}; /* derived name */

static float clipMatrix[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}; /* derived name */

static float clipPlanePos[4] = {0}; /* derived name */

typedef union { /* field names derived */
    float f[4];
    int i[4];
    long long ll[2];
} FcPlane; /* derived name */

/* one static inline expanded in both tail arms */
static __inline__ void setClipPlane(ClipWork *self, void *m, void *v) /* derived name */
{
    Vec16 *n = &self->normal;

    sceVu0ApplyMatrix(n, m, v);
    n->f[3] = -sceVu0InnerProduct(n, self->pt[2]);
}

/* a gobj's display-object slot read through a union: the ROM orders the
 * wall arm's read of it behind the float stores to clipPlanePos, as an
 * access through a union is ordered; a plain GObj.dobj read is scheduled
 * ahead of them (measured) */
typedef union { /* field names derived */
    Sub15C *dobj;
} FcSubSlot; /* derived name */

static void _Clip(ClipWork *self, int mode)
{
    float sv0[4];
    float sv1[4];
    float m0[16];
    float keep[4];
    float m1[16];
    FcPlane keep2;
    int (*func)(ClipWork *, GObj *, int);
    GObj *obj;
    Sub15C *sub;
    char *m;
    int cnt;
    int i;

    func = clipMode[mode].func;
    {
        int x = clipMode[mode].skipFilter;
        int y = clipMode[mode].useColFilter;

        sceVu0CopyVector(sv0, self->pt[0]);
        sceVu0CopyVector(sv1, self->pt[1]);
        sceVu0CopyVector(self->pt[2], self->pt[1]);
        colObjNum = 0;
        obj = colObjList[0];
        if (colObjListNum > 0) {
            do {
                m = (char *)clipMatrix;
                sub = obj->dobj;
                if (sub->disp != 0) {
                    if (x != 0) {
                        if (obj == self->filter.o.obj) {
                            if (self->filter.o.node < 0) {
                                goto next_gobj;
                            }
                        }
                    }
                    if (y != 0) {
                        if (colFilter(obj) == 0) {
                            goto next_gobj;
                        }
                    }
                    sub = obj->dobj;
                    cnt = 1;
                    if (sub->colPerNode != 0) {
                        cnt = sub->nodeNum;
                    }
                    curFuzio = (FuzioCtx *)sub->colData;
                    for (i = 0; i < cnt; i++) {
                        if (x != 0) {
                            if (obj == self->filter.o.obj && i == self->filter.o.node &&
                                self->filter.elem == 0) {
                                continue;
                            }
                        }
                        CopyVector(keep, self->pt[2]);
                        CopyVector(self->pt[0], sv0);
                        if (obj->dobj->colRotate == 0) {
                            CopyVector(&clipMatrix[12],
                                       (char *)obj->dobj->nodeMtx + (i << 6) + 0x30);
                        } else {
                            m = (char *)obj->dobj->nodeMtx + (i << 6);
                        }
                        MatrixDrive_SetTransposeMatrix(m0, m);
                        self->pt[0][3] = self->pt[2][3] = 1.0f;
                        _ApplyMatrix(self->pt[0], m0, self->pt[0]);
                        _ApplyMatrix(self->pt[2], m0, self->pt[2]);
                        makeCollisionBlockTable(self->pt[0]);
                        if (func(self, obj, i)) {
                            self->pt[2][3] = 1.0f;
                            _ApplyMatrix(self->pt[2], m, self->pt[2]);
                        } else {
                            CopyVector(self->pt[2], keep);
                        }
                    }
                }
            next_gobj:
                colObjNum = colObjNum + 1;
                obj = colObjList[colObjNum];
            } while (colObjNum < colObjListNum);
        }
        if (clipMode[mode].wall != 0) {
            if (self->wall.elem != 0) {
                clipPlanePos[0] = ((FcWallEnt *)self->wall.elem)->normal[0];
                clipPlanePos[2] = ((FcWallEnt *)self->wall.elem)->normal[1];
                CopyMatrix(m1, (char *)((FcSubSlot *)&self->wall.o.obj->dobj)->dobj->nodeMtx +
                                   (self->wall.o.node << 6));
                if (self->wall.o.obj->dobj->colRotate == 0) {
                    UnitRotation(m1);
                }
                setClipPlane(self, m1, clipPlanePos);
                self->attr = ((FcWallEnt *)self->wall.elem)->attr;
            } else {
                sceVu0CopyVector(self->pt[2], sv1);
            }
        } else {
            if (self->floor.elem != 0) {
                CopyVector(&keep2, &((FcFloorEnt *)self->floor.elem)->nx);
                keep2.i[3] = 0;
                CopyMatrix(m1,
                           (char *)self->floor.o.obj->dobj->nodeMtx + (self->floor.o.node << 6));
                if (self->floor.o.obj->dobj->colRotate == 0) {
                    UnitRotation(m1);
                }
                setClipPlane(self, m1, &keep2);
                self->attr = ((FcFloorEnt *)self->floor.elem)->attr;
            }
        }
        sceVu0CopyVector(self->pt[0], sv0);
        sceVu0CopyVector(self->pt[1], sv1);
    }
}

static void __ClipWall(ClipWork *work, int mode)
{
    work->slideCount = 0;
    work->floor.elem = 0;
    work->wall.elem = 0;
    work->wall.o = InitialObjPointer;
    _Clip(work, mode);
}

INCLUDE_ASM_LIT(__ClipWallWithDrawRay);

static void __ClipFloor(ClipWork *work, int mode)
{
    work->floor.elem = 0;
    work->floor.o = InitialObjPointer;
    _Clip(work, mode);
}

INCLUDE_ASM_LIT(__ClipFloorWithDrawRay);

/* global in this build: debug.c's debug_CollisionTest calls it ($gp) */
void (*clipWallFunc)(ClipWork *work, int mode) = __ClipWall; /* derived name */

/* global in this build: the ClipFloor callers load it ($gp) */
void (*clipFloorFunc)(ClipWork *work, int mode) = __ClipFloor; /* derived name */

typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} FcVec; /* derived name */

inline void MapCollisionData(void *data)
{
    int *p = (int *)data;
    p[4] = (int)data + p[4];
    p[5] = (int)data + p[5];
}

static int wallDrawCnt = 0; /* derived name */

/* The wall edge and rim colours for a plain wall, an attributed one and the
   two exit kinds (this build has no unit matrix after them). */
static FcColor wallEdgeColor = {0, 56, 255, 128}; /* derived name */

static FcColor wallEdgeColorAttr = {0, 0, 255, 128}; /* derived name */

static FcColor wallEdgeColorExit = {0, 255, 192, 128}; /* derived name */

static FcColor wallEdgeColorExit1 = {255, 0, 192, 128}; /* derived name */

static FcColor wallRimColor = {0, 5, 25, 32}; /* derived name */

static FcColor wallRimColorAttr = {0, 0, 25, 32}; /* derived name */

static FcColor wallRimColorExit = {0, 25, 19, 32}; /* derived name */

static FcColor wallRimColorExit1 = {25, 0, 19, 32}; /* derived name */

typedef struct { /* field names derived */
    char pad0[8];
    int nobj;  /* 0x8  */
    char *mtx; /* 0xC  */
    char pad10[96];
    char *coll; /* 0x70 */
    char pad74[4];
    int norot; /* 0x78 */
    char pad7C[4];
    int multi; /* 0x80 */
} FcWallSub;   /* derived name */

typedef struct { /* field names derived */
    char pad0[348];
    FcWallSub *sub; /* 0x15C */
} FcWallObj;        /* derived name */

typedef struct { /* field names derived */
    char pad0[8];
    int nwall; /* 0x8  */
    char padC[4];
    char *walls; /* 0x10 */
} FcWallSet;     /* derived name */

void DrawGObjWallCollision(GObj *gobj, int col)
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

    wallDrawCnt = wallDrawCnt + 1;
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
            c0 = &wallEdgeColor;
            c1 = &wallRimColor;
            attr = *(int *)(e + 0x48);
            if ((attr & 0xF0000000) != 0) {
                c0 = &wallEdgeColorExit;
                c1 = &wallRimColorExit;
                if ((attr & 0x10000000) != 0) {
                    c0 = &wallEdgeColorExit1;
                    c1 = &wallRimColorExit1;
                }
            } else if (attr != 0) {
                c0 = &wallEdgeColorAttr;
                c1 = &wallRimColorAttr;
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

void DrawGObjFloorCollision(GObj *gobj, int col)
{
    int n;
    char *cd;
    int i;
    int j;

    n = 1;
    if (GOBJ_SUB(gobj)->colPerNode != 0) {
        n = GOBJ_SUB(gobj)->nodeNum;
    }
    cd = (char *)GOBJ_SUB(gobj)->colData;
    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    gif_SetAlpha(1, 5, 0);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    for (i = 0; i < n; i++) {
        CopyMatrix(MatrixDrive_GetMatrix(), (char *)GOBJ_SUB(gobj)->nodeMtx + (i << 6));
        if (GOBJ_SUB(gobj)->colRotate == 0) {
            UnitRotation(MatrixDrive_GetMatrix());
        }
        for (j = 0; j < *(int *)(cd + 0xC); j++) {
            char *e = *(char **)(cd + 0x14) + j * 0x70;
            sceVu0IVECTOR c = {56, 0, 8, 128};

            DrawLineG(e, c, e + 0x10, c, col);
            if (*(int *)(e + 0x54) == 0) {
                DrawLineG(e + 0x10, c, e + 0x20, c, col);
                DrawLineG(e + 0x20, c, e, c, col);
            } else {
                DrawLineG(e + 0x10, c, e + 0x20, c, col);
                DrawLineG(e + 0x20, c, e + 0x30, c, col);
                DrawLineG(e + 0x30, c, e, c, col);
            }
        }
    }
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void DBG_VECTOR(float *vec)
{
    return debug_StdPrintfDummy("%8f %8f %8f", vec[0], vec[1], vec[2]);
}

INCLUDE_ASM(GetEdgeOfFloor);

INCLUDE_ASM_LIT(GetOrientOfWall);

void DrawCollisionRay(ClipWork *ray)
{
    sceVu0IVECTOR c0 = {64, 64, 64, 128};
    sceVu0IVECTOR c1 = {8, 16, 32, 128};
    float d[4];
    float p1[4];
    float p0[4];
    float v[4];
    float len;

    gif_StartPacketPri(11);
    MatrixDrive_PushMatrix();
    memset(v, 0, 16);
    v[3] = 1.0f;
    gif_SetAlpha(1, 5, 128);
    gif_SetZTest(1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(ray->pt[0], c0, ray->pt[1], c0, 0);
    DrawLineG(ray->pt[0], c1, ray->pt[1], c1, -1);
    sceVu0SubVector(d, ray->pt[1], ray->pt[0]);
    MatrixDrive_TransMatrixV(ray->pt[1]);
    MatrixDrive_TurnYObjectMatrixXZ(d[0], d[1], d[2]);
    len = FSqrt(sceVu0InnerProduct(d, d));
    v[0] = len * 0.05f;
    v[1] = len * 0.3f;
    sceVu0ApplyMatrix(p0, MatrixDrive_GetMatrix(), v);
    v[0] = -len * 0.05f;
    sceVu0ApplyMatrix(p1, MatrixDrive_GetMatrix(), v);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    DrawLineG(p0, c0, ray->pt[1], c0, 0);
    DrawLineG(p1, c0, ray->pt[1], c0, 0);
    DrawLineG(p0, c1, ray->pt[1], c1, -1);
    DrawLineG(p1, c1, ray->pt[1], c1, -1);
    sceVu0UnitMatrix(MatrixDrive_GetMatrix());
    MatrixDrive_TransMatrixV(ray->pt[2]);
    MatrixDrive_TurnYObjectMatrixXZ(d[0], d[1], d[2]);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}

void MakeExitAttributeIndex(void)
{
    int i;
    char *entry;
    int j;
    int *p70;
    void *obj;
    int slot;

    debug_StdPrintfDummy("MakeExitAttributeIndex() %d\n", frame_count);
    exitAttrNum = 0;
    i = 0xF;
    do {
        exitAttr[i] = 0;
        i--;
    } while (i >= 0);
    colObjNum = 0;
    obj = colObjList[0];
    if (colObjListNum > 0) {
        do {
            p70 = (int *)GOBJ_SUB(obj)->colData;
            for (j = 0; j < p70[0xC / 4]; j++) {
                entry = (char *)p70[0x14 / 4] + j * 0x70;
                slot = *(int *)(entry + 0x60) & 0xF;
                if (slot != 0) {
                    if (exitAttr[slot] == 0) {
                        debug_StdPrintfDummy("attr EXIT%2d\n", slot);
                        exitAttrNum = exitAttrNum + 1;
                        exitAttr[slot] = entry;
                    }
                }
            }
            colObjNum = colObjNum + 1;
            obj = colObjList[colObjNum];
        } while (colObjNum < colObjListNum);
    }
}

INCLUDE_ASM(ClipCollision);

INCLUDE_ASM(ChangeFieldCollisionDebugMode);

INCLUDE_ASM(func_00160B58);

INCLUDE_ASM(LoadCollision);

INCLUDE_ASM(DrawCollision);

INCLUDE_ASM(ClipPlane);

INCLUDE_ASM(GetOrientOfWall);

INCLUDE_ASM(SetSimplePlane);

INCLUDE_ASM(GetWallAttribute);

INCLUDE_ASM(GetFloorAttribute);

INCLUDE_ASM(CompareAttribute);

INCLUDE_ASM(GetWallGlobalInfo);

INCLUDE_ASM(GetDistanceFromPlane);

INCLUDE_ASM(GetYDistanceFromPlane);

INCLUDE_ASM(GetYProjectionOfPlane);

INCLUDE_ASM(ResetCollisionPC);

INCLUDE_ASM(PositionOfExit);

INCLUDE_ASM(GetGlobalWallPlane);

INCLUDE_ASM(_clipWDebug);

INCLUDE_ASM(_clipW);

INCLUDE_ASM(_clipWE);

INCLUDE_ASM(_clipWEField);

INCLUDE_ASM(_clipWR);

INCLUDE_ASM(_clipWField);

INCLUDE_ASM(_clipWDitchHangWalkStop);

INCLUDE_ASM(_clipWWaveForce);

INCLUDE_ASM(_clipWBoxStop);

INCLUDE_ASM(_clipWAdjustPos);

INCLUDE_ASM(_clipF);

INCLUDE_ASM(_clipFE);

INCLUDE_ASM(_clipFIH);

INCLUDE_ASM(_clipFR);

INCLUDE_ASM(__ClipWallWithDrawRay);

INCLUDE_ASM(__ClipFloorWithDrawRay);

INCLUDE_ASM(ClipWallRD);

INCLUDE_ASM(ClipWallVector);
