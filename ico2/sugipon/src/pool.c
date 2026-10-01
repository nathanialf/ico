#include "sugiCommon.h"
#include "pool.h"
#include "memory.h"
#include "DisplayP2O.h"
#include "GsBase.h"
#include "Primitive.h"
#include "RegistPacket.h"
#include "clothAnimation.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "motionManager2.h"
#include "multiBgaManager.h"
#include "particleEffect.h"
#include "quaternion.h"
#include "StageAnimation.h"
#include "tableSin.h"
#include "debug.h"
#include <string.h>
#include "sceneManager.h"
#include "main.h"
#include "GifPacket.h"
#include "Matrix.h"
#include "ios.h"

typedef struct {
    char c[16];
} Blob16;

typedef struct {
    char c[4];
} Blob4;

void falldownSE(int a0)
{
    ExecuteSEPackage(a0, 0x56);
}

/* The whole drawing area as a sprite rectangle in GS primitive coordinates,
   {x0, y0, x1, y1}: copyToWork and flushWork blit the frame through it.  A
   quadword: the member's .rodata starts on a 16-byte boundary in both the
   retail link (8 bytes of fill after motionManager2's run) and MAIN.MAP. */
static const sceVu0IVECTOR workRect = {-2048, -2048, 4096, 4096};

/* The TU's .sdata opens with the two work-area VRAM addresses (MAIN.MAP names
   nothing in the run); the two colour constants after them are copyToWork's and
   flushWork's anonymous initialisers. */
static int workVram = 0; /* derived name */

static int work1Vram = 0; /* derived name */

/* kept local: agrees with Texture.h, which this TU does not include (tex_ResetVramPri differs) */
extern int tex_AllocVramAuto(int a0, int a1);
/* kept local: void (void) here, void (int) in Texture.h */
extern void tex_ResetVramPri(void);

void copyToWork(int pri)
{
    int rect[4];

    tex_ResetVramPri();
    workVram = tex_AllocVramAuto(0, 0x400);
    gif_SetGsReg(6, ((long long)(ScreenWidth / 64) << 14) | 0x664000800LL);
    gif_SetDrawEnviroment(workVram, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(0, 4, 0);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x14, 0x60);
    *(Blob16 *)rect = *(Blob16 *)workRect;
    /* The inner block is what the frame proves.  uv's initialiser is built in
       a 16-byte stack temp and block-copied into uv (safe_from_p rejects the
       array as the constructor target once its address is live), and col is
       declared after that statement so assign_temp hands it the freed temp
       slot.  That is why the ROM writes 8, 8, w and h at sp+0x20, copies them
       to sp+0x10, then overwrites sp+0x20 with the four colour bytes and
       passes sp+0x20 as the colour pointer, all inside a 0x40 frame. */
    {
        int uv[4] = {8, 8, ScreenWidth * 16, ScreenHeight * 16};
        Blob4 col = {128, 128, 128, 128};

        gif_SpriteSensitiveOrg(rect, 0, uv, &col, 0);
    }
    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_SetGsReg(0x47, 0x5000D);
}

void flushWork(int pri)
{
    char buf[0x20];

    tex_ResetVramPri();
    workVram = tex_AllocVramAuto(0, 0x400);
    work1Vram = tex_AllocVramAuto(0, 0x400);
    gif_SetDrawEnviroment(workVram, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetGsReg(0x4E, 0x30000000 | (work1Vram / 32));
    gif_SetAlpha(0, 4, 0);
    *(Blob16 *)buf = *(Blob16 *)workRect;
    *(Blob4 *)(buf + 0x10) = (Blob4){255, 255, 255, 128};
    gif_SpriteSensitiveOrg(buf, 0, 0, buf + 0x10, 0);
    gif_SetZTest(1);
}

/* RECONSTRUCTION, read from the ROM.  One ripple of the pool's surface: the
   grid cell it started in and the remainder inside that cell on each of the
   two horizontal axes, its amplitude (negative when the slot is free) and its
   age.  InitPoolGeo clears five of them, SetFallDownSplash starts the next
   one in turn. */
typedef struct {
    int ix;    /* 0x00 */
    float fx;  /* 0x04 */
    int iz;    /* 0x08 */
    float fz;  /* 0x0C */
    float amp; /* 0x10 */
    float age; /* 0x14 */
} PoolRipple;

/* RECONSTRUCTION, read from the ROM.  The pool's work record, the 224 bytes
   InitPoolGeo allocates and leaves in the object's work word (Sub15C+0x830):
   the surface's position (its y is the water height every reader takes) and
   drain vector, the two splash managers, the height grid and its two meshes, the
   ripples, the wave phase and the reflected stage object.  The two multi-BGA
   managers are char *: InitPoolGeo's store of the second must share the
   char * alias set of the object-sub load after it, which the ROM keeps
   below the store (measured: BgaDisp *, void * and int all let sched1 lift
   the load and swap $a0/$v1 at the last store). */
typedef struct {
    float pos[4];         /* 0x00 */
    float drain[4];       /* 0x10, GetPoolGlobalDrainVector's vector: the
                               layout's x and z angles in degrees */
    int splashNo;         /* 0x20, the next slot of splash */
    char *splash;         /* 0x24, two splash animations */
    int f_28;             /* 0x28 */
    char *bga;            /* 0x2C, ten animations PoolDL draws */
    int hasGrid;          /* 0x30 */
    int nx;               /* 0x34 */
    int ny;               /* 0x38 */
    float step;           /* 0x3C, the grid spacing */
    Mesh3D *reflect;      /* 0x40, the mirrored surface */
    Mesh3D *surface;      /* 0x44, the refracting surface drawn into the work */
    Prim3DVec **wire;     /* 0x48, the rows of reflect's vertices */
    float **height;       /* 0x4C, the height grid, one row per x */
    PoolRipple ripple[5]; /* 0x50 */
    int rippleNo;         /* 0xC8 */
    short phase;          /* 0xCC */
    char *dobj;           /* 0xD0, the reflected stage object or 0 */
    int spin;             /* 0xD4 */
} PoolWork;

/* The listing gives this body rows 178 to 186 and attributes those rows to
   both SetFallDownSplash and InitPoolGeo, so it is a static of this file that
   the compiler inlines into each of them and it has no symbol of its own.  It
   plants one cell of the pool's ripple grid at a world position: the grid
   index and the in-cell remainder on each of the two horizontal axes, then
   the amplitude the caller asks for and a zero age.  The cell address, the
   cell step and the two grid counts arrive as parameters: in both callers
   the listing puts their loads and the cell arithmetic on row 178 with the
   amplitude, the row integrate.c gives an inline's parameter set-up. */
static inline void setWaveCell(PoolWork *w, float *pos, PoolRipple *cell, float step, int nx,
                               int ny, float amp)
{
    float d[4];

    _SubVector(d, pos, w->pos);
    cell->ix = (int)(d[0] / step) + (nx >> 1);
    cell->fx = d[0] - (float)(int)(d[0] / step) * step;
    cell->iz = (int)(d[2] / step) + (ny >> 1);
    cell->fz = d[2] - (float)(int)(d[2] / step) * step;
    cell->amp = amp;
    cell->age = 0.0f;
}

void setNodePursueParticleEffectWithUpperLimit(char *a0, char *a1, int a2, float f)
{
    int ret = GetSkeltonFocusNode(a1, a2);
    if (ret != -1) {
        Sub15C *p = GOBJ_SUB(a1);
        int r = SetParticleEffectActiveSensing((int)a0, p->f_C + ret * 0x40 + 0x30,
                                               (int)IdentityQuaternion);
        SetParticleEffectUpperLimit(r, f);
    }
}

void SetFallDownSplash(char *pool, char *self)
{
    float pos[4];
    float tmp[4];
    PoolWork *w = GOBJ_SUB(pool)->f_830;

    GetRootPosition(pos, self);
    _ScaleVectorXYZ(tmp, *(char **)(self + 0x15C) + 0x130, 2.0f);
    _AddVector(pos, pos, tmp);
    pos[1] = w->pos[1];

    if (*(int *)(*(char **)(self + 0x15C) + 0x8C) != 0) {
        setNodePursueParticleEffectWithUpperLimit((char *)48, self, 51, pos[1]);
        setNodePursueParticleEffectWithUpperLimit((char *)48, self, 47, pos[1]);
    }

    stage_SetLoopFlag(499, 0);
    stage_SetFrameStep(499, 1);

    EntryMultiBgaManagerNoKind(w->splash, w->splashNo, pos);
    w->splashNo = (w->splashNo + 1) % 2;

    if (w->hasGrid != 0) {
        setWaveCell(w, pos, &w->ripple[w->rippleNo], w->step, w->nx, w->ny, 0.5f);
        w->rippleNo = w->rippleNo + 1;
        if (w->rippleNo == 5) {
            w->rippleNo = 0;
        }
    }

    falldownSE((int)self);
}

void GetPoolGlobalDrainVector(void *dst, char *a0)
{
    CopyVector(dst, ((PoolWork *)GOBJ_SUB(a0)->f_830)->drain);
}

/* RECONSTRUCTION, read from the ROM.  The 64-byte record CSVSYSTEM_InitDObj
   takes as its layout: the position at 0x00, the rotation at 0x10, the scale
   at 0x20 and the object word at 0x30.  The copy out of InitialSObjSimpleSetting is ld/sd
   pairs, so the record is 8-aligned; ico2/sugipon/src/attackCheckBoundary.c
   carries the same record under its own name. */
typedef struct {
    float x;           /* 0x00 */
    float y;           /* 0x04 */
    float z;           /* 0x08 */
    float w;           /* 0x0C */
    long long f_10[6]; /* 0x10, the rest of the record this TU copies out of
                          the template and does not touch */
} PoolLayout;

typedef union {
    int i[4];
    float f[4];
} PoolQuad;

typedef struct {
    PoolQuad pos;   /* 0x00 */
    PoolQuad rot;   /* 0x10 */
    PoolQuad scale; /* 0x20 */
} PoolDisp;

/* RECONSTRUCTION, read from the ROM.  The stage's CSV object table, one
   40-byte record per stage entry: the object id at 0x00 and the three
   placement angles at 0x0C.  ico2/sugipon/src/puddle.c reaches the same
   table for the same id. */
typedef struct {
    int id;      /* 0x00 */
    int f_4;     /* 0x04 */
    int f_8;     /* 0x08 */
    float f_C;   /* 0x0C */
    float f_10;  /* 0x10 */
    float f_14;  /* 0x14 */
    int f_18[4]; /* 0x18 */
} StgCsvEnt;

extern StgCsvEnt D_002A79B8[];
int poolRideFunc(char **a0, char *a1);

char *InitPoolGeo(char *self, SObjSimpleSetting *lay)
{
    PoolWork *w = iosMallocDebug(ios_partition_sugipon, 224, "src/pool.c", 316);
    int i;
    int j;
    int k;

    CopyVector(w->pos, lay->pos);
    w->pos[3] = 1.0f;
    CopyVector(w->drain, ZeroVector);
    w->drain[0] = -lay->rot[0] * 180.0f / 3.1415927f;
    w->drain[2] = -lay->rot[2] * 180.0f / 3.1415927f;

    if (lay->obj != 0) {
        w->hasGrid = 1;
        w->nx = (int)lay->scale[0];
        w->ny = (int)lay->scale[2];
        w->step = lay->scale[1];

        w->height = iosMallocDebug(ios_partition_sugipon, w->nx * 4, "src/pool.c", 330);

        for (i = 0; i < w->nx; i++) {
            w->height[i] = iosMallocDebug(ios_partition_sugipon, w->ny * 4, "src/pool.c", 334);
        }

        w->surface = prim_InitMesh3D(w->ny, w->nx, 1, 0x1C, (lay->obj & 0xFFFFFF00) | 0x80, 1);

        w->reflect = prim_InitMesh3D(w->ny, w->nx, 1, 0x5C, 0x80808080, 1);

        w->phase = 0;
        w->wire = iosMallocDebug(ios_partition_sugipon, w->nx * 4, "src/pool.c", 357);

        for (j = 0; j < w->nx; j++) {
            w->wire[j] = w->reflect->pos + j * w->ny;
        }

        for (k = 0; k < 5; k++) {
            setWaveCell(w, w->pos, &w->ripple[k], w->step, w->nx, w->ny, 1.0f);
            w->ripple[k].amp = -1.0f;
        }

        w->rippleNo = 0;

        if (GOBJ_SUB(self)->f_844 != 26) {
            PoolLayout obj = *(PoolLayout *)&InitialSObjSimpleSetting;

            obj.x = -D_002A79B8[GOBJ_SUB(self)->f_844].f_C;
            obj.y = -D_002A79B8[GOBJ_SUB(self)->f_844].f_10;
            obj.z = -D_002A79B8[GOBJ_SUB(self)->f_844].f_14;
            w->dobj = CSVSYSTEM_InitDObj(D_002A79B8[GOBJ_SUB(self)->f_844].id, (float *)&obj);

            w->spin = 0;
        } else {
            w->dobj = 0;

            w->spin = 0;
        }
    } else {
        w->hasGrid = 0;
    }

    {
        PoolDisp *q = (PoolDisp *)GOBJ_SUB(self)->p_870;
        q->pos.i[0] = q->pos.i[1] = q->pos.i[2] = 0;
    }
    {
        PoolDisp *q = (PoolDisp *)GOBJ_SUB(self)->p_870;
        q->scale.f[0] = q->scale.f[1] = q->scale.f[2] = 1.0f;
    }
    {
        PoolDisp *q = (PoolDisp *)GOBJ_SUB(self)->p_870;
        q->rot.f[0] = q->rot.f[1] = q->rot.f[2] = 0.0f;
    }

    _UnitMatrix(&GOBJ_SUB(self)->f_20);
    _UnitMatrix((char *)GOBJ_SUB(self)->f_C);

    w->f_28 = 0;
    w->bga = InitMultiBgaManager(10);

    w->splashNo = 0;
    w->splash = InitMultiBgaManager(2);

    ((SubHandle *)(self + 0x15C))->sub->f_81C = (int)poolRideFunc;

    return (char *)w;
}

static inline void decayRipple(PoolRipple *c)
{
    if (c->amp < 0.0f) {
        return;
    }
    c->age += 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    c->amp -= 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.0005f;
}

static inline void addRippleToGrid(PoolWork *w, PoolRipple *c, float **grid)
{
    float step = w->step;
    int nx = w->nx;
    int ny = w->ny;
    float r;
    float inv;
    float dx;
    float dy;
    float t;
    float *row;
    int n;
    int x;
    int y;
    int ix;
    int iz;

    if (c->amp < 0.0f) {
        return;
    }

    {
        r = c->age * 3.0f;
        inv = 1.0f / r;
        n = (int)(r / step);

        for (x = -n; x <= n; x++) {
            dx = (float)x * step - c->fx;
            if (dx < 0.0f) {
                dx = -dx;
            }
            ix = c->ix + x;

            if (ix < 0) {
                continue;
            }
            if (ix >= nx) {
                continue;
            }
            row = grid[ix];

            for (y = -n; y <= n; y++) {
                dy = (float)y * step - c->fz;
                if (dy < 0.0f) {
                    dy = -dy;
                }
                iz = c->iz + y;
                if (dx < dy) {
                    t = dy * 0.9375f + dx * 0.359375f;
                } else {
                    t = dx * 0.9375f + dy * 0.359375f;
                }
                t = t * inv;
                if (t <= 1.0f) {
                    if (iz < 0) {
                        continue;
                    }
                    if (iz >= ny) {
                        continue;
                    }

                    row[iz] +=
                        GetTableCos((t - 1.0f) * r * 512.0f) * 80.0f / (c->age * 2.0f + 10.0f);
                }
            }
        }
    }
}

static inline void makeWaveGrid(PoolWork *w, float **grid, int ang)
{
    int i;
    int j;
    int nx = w->nx;
    int ny = w->ny;
    int nn = (int)w->step;
    float *row;

    for (i = 0; i < nx; i++) {
        row = grid[i];
        for (j = 0; j < ny; j++) {
            *row++ = GetTableSin((i * ny + j) * nn * 1000 + ang) * 0.05f;
        }
    }
}

/* The GS drawing-area origin, the centre of the 4096-unit primitive space. */
static const ConstVec screenOrigin = {{2048.0f, 2048.0f, 0.0f, 0.0f}};

void updatePoolGeo(char *self)
{
    ConstVec org;
    float out[4];
    float nrm[4];
    float eye[4];
    char mat[0x40];
    float ref[4];
    float dir[4];
    float tmp[4];
    float pos[4];
    float sub[4];
    PoolWork *w = GOBJ_SUB(self)->f_830;
    Mesh3D *mesh0 = w->reflect;
    Mesh3D *mesh1 = w->surface;
    float step = w->step;
    float **grid = w->height;
    float sx;
    float sy;
    float *pc;
    float *pa;
    float *pb;
    float *pd;
    int ang;
    float *row;
    Prim3DVec *q;
    Prim3DVec *uv;
    Prim3DVec *q2;
    float *row2;
    Prim3DVec *uv2;
    Prim3DVec *qq;
    float h;
    float iw;
    float usc;
    float vsc;
    int k;
    int i;
    int j;

    org = screenOrigin;
    sx = 1.0f / (float)ScreenWidth;
    sy = 1.0f / (float)ScreenHeight;

    pc = (float *)(matrixptr + 0x4C0);
    pa = (float *)(matrixptr + 0x400);
    pb = (float *)(matrixptr + 0x440);
    pd = (float *)(matrixptr + 0x480);

    CopyVector(pa, w->pos);
    CopyVector(pb, &org);
    CopyVector(pd, ZeroVector);

    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x100);

    if (systemStatus[5] == 0) {
        for (k = 0; k < 5; k++) {
            decayRipple(&w->ripple[k]);
        }
    }

    ang = w->phase;

    makeWaveGrid(w, grid, ang);

    for (k = 0; k < 5; k++) {
        addRippleToGrid(w, &w->ripple[k], grid);
    }

    for (i = 0; i < w->nx; i++) {
        q = mesh1->pos + i * w->ny;
        uv = mesh1->st + i * w->ny;
        row = grid[i];

        pd[0] = (float)(((1 - w->nx) >> 1) + i) * step;

        j = 0;

        for (; j < w->ny; j++, row++, q++, uv++) {
            h = *row;

            pd[1] = h * 30.0f;
            pd[2] = (float)(((1 - w->ny) >> 1) + j) * step;
            _AddVector(q, pa, pd);

            _ApplyCurrentMatrix(out, q);
            iw = 1.0f / out[3];
            _ScaleVector(pc, out, iw);
            _SubVector(out, pc, pb);
            uv->x = out[0] * sx + 0.5f + h * 30.0f * iw;
            uv->y = out[1] * sy + 0.5f + h * 30.0f * iw;
        }
    }

    memset(nrm, 0, 16);
    nrm[1] = -1.0f;

    usc = 1.0f / (float)ScreenWidth * 0.8f;
    vsc = 1.0f / (float)ScreenHeight * 0.8f;

    MatrixDrive_SetTransposeMatrix(mat, (char *)(matrixptr + 0x80));
    CopyVector(eye, mat + 0x30);

    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < w->nx; i++) {
        q2 = mesh1->pos + i * w->ny;
        qq = mesh0->pos + i * w->ny;
        uv2 = mesh0->st + i * w->ny;
        row2 = grid[i];

        for (j = 0; j < w->ny; j++, row2++, q2++, uv2++) {
            nrm[0] = nrm[2] = *row2 * 0.1f;

            CopyVector(qq, q2);

            _SubVector(dir, qq, eye);

            _NormalizeVector(dir, dir);
            _ScaleVector(tmp, nrm, _InnerProduct(dir, nrm) * -2.0f);

            _AddVectorXYZ(ref, dir, tmp);

            ref[1] = -ref[1];

            _ApplyCurrentMatrix(out, qq);
            _ScaleVectorXYZ(pc, out, 1.0f / out[3]);

            _AddVector(pos, qq, ref);
            qq++;
            _ApplyCurrentMatrix(pos, pos);
            _ScaleVectorXYZ(pos, pos, 1.0f / pos[3]);

            _SubVector(sub, pos, pc);

            _SubVector(out, pc, pb);

            uv2->x = (out[0] + sub[0] * 1000.0f) * usc + 0.5f;
            uv2->y = (out[1] + sub[1] * 1000.0f) * vsc + 0.5f;
        }
    }

    prim_UpdateMesh3D(mesh1, 9, buffer_ID);

    prim_UpdateMesh3D(mesh0, 9, buffer_ID);
}

/* .data, owned by pool.o and read only here (MAIN.MAP names no symbol in the
   run).  The fixed lighting the pool surface is drawn under, in the two
   matrices light_MakeLightMatrix otherwise builds at +0x40 and +0x00 of the
   object's light work: a colour matrix (a row per colour channel, a column per
   light) and a normal matrix (a column per light direction).  The first pair
   goes straight to prim_DispMesh3D, the second is copied into the work. */
static float dispLightColor[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
};

static float dispLightNormal[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};

static float workLightColor[4][4] = {
    {0.707f, 0.707f, 0.0f, 0.0f},
    {0.707f, 0.707f, 0.0f, 0.0f},
    {0.707f, 0.707f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
};

static float workLightNormal[4][4] = {
    {1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};

void dispPool(char *self)
{
    char m0[0x40];
    char m1[0x40];
    char m2[0x40];
    char m3[0x40];
    char m4[0x40];
    PoolWork *w = GOBJ_SUB(self)->f_830;

    gif_StartPacketPri(4);
    copyToWork(4);
    gif_SetGsReg(6, workVram | 0x20010000 | 0x600000000LL);

    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);

    gif_EndPacket();

    _SetCurrentMatrix(matrixptr + 0x100);

    prim_DispMesh3D(w->surface, dispLightColor, dispLightNormal, -1);

    CopyMatrix((char *)GOBJ_SUB(self)->p_874 + 0x40, workLightColor);
    CopyMatrix((char *)GOBJ_SUB(self)->p_874, workLightNormal);

    gif_StartPacketPri(4);
    flushWork(4);

    CopyMatrix(m0, (char *)(matrixptr + 0xC0));

    CopyMatrix(m1, (char *)(matrixptr + 0x1C0));
    CopyMatrix(m2, (char *)(matrixptr + 0x100));
    CopyMatrix(m3, (char *)(matrixptr + 0x200));
    CopyMatrix(m4, (char *)(matrixptr + 0x340));

    gsb_SetVSMatrix(0xCC, 0xCC, (float)currentFocusDistance);

    _MulMatrix((char *)(matrixptr + 0x100), (char *)(matrixptr + 0xC0), (char *)(matrixptr + 0x80));
    _MulMatrix((char *)(matrixptr + 0x200), (char *)(matrixptr + 0x1C0),
               (char *)(matrixptr + 0x80));

    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    gif_EndPacket();

    _UnitMatrix(MatrixDrive_GetMatrix());
    CopyMatrix((char *)GOBJ_SUB(self)->f_C, MatrixDrive_GetMatrix());
    reg_RenderReflection(GOBJ_SUB(self), 4);

    if (w->dobj != 0) {
        CopyMatrix(MatrixDrive_GetMatrix(), w->dobj + 0x20);
        switch (stage_no) {
        case 101:
            MatrixDrive_RotMatrixZ((w->spin << 16) / 1600);
            break;
        case 15:
            MatrixDrive_RotMatrixZ(-(w->spin << 16) / 1600);
        }

        CopyMatrix(*(char **)(w->dobj + 0xC), MatrixDrive_GetMatrix());

        reg_RenderReflection((Sub15C *)w->dobj, 4);

        if (systemStatus[5] == 0) {
            if (++w->spin > 1600) {
                w->spin = 0;
            }
        }
    }

    gif_StartPacketPri(4);
    gif_SetZWrite(0);
    gif_SetZTest(0);
    gif_SetAlpha(0, 4, 0x80);

    CopyMatrix((char *)(matrixptr + 0xC0), m0);
    CopyMatrix((char *)(matrixptr + 0x1C0), m1);
    CopyMatrix((char *)(matrixptr + 0x340), m4);
    CopyMatrix((char *)(matrixptr + 0x100), m2);
    CopyMatrix((char *)(matrixptr + 0x200), m3);
    vsWidth = ScreenWidth;
    vsHeight = ScreenHeight;

    gif_SetGsReg(6, workVram | 0x20010000 | 0x600000000LL);

    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(1, 0, 0x40);

    gif_EndPacket();

    _SetCurrentMatrix(matrixptr + 0x100);

    prim_DispMesh3D(w->reflect, dispLightColor, dispLightNormal, -1);

    gif_StartPacketPri(4);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);

    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(1, 0, 0x40);

    gif_EndPacket();

    if (debug_skel_flag != 0) {
        DispMeshWire(w->wire, w->nx, w->ny);
    }
}

void PoolDL(char *self)
{
    PoolWork *w = GOBJ_SUB(self)->f_830;

    DispMultiBgaManagerWithKind(498, w->bga, 10);
    DispMultiBgaManagerWithKind(499, w->splash, 2);
    if (systemStatus[5] == 0) {
        w->phase =
            (short)((float)w->phase +
                    60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 2000.0f);
    }
    if (w->hasGrid != 0) {
        updatePoolGeo(self);
        dispPool(self);
    } else {
        p2o_DispVU1(self);
    }
}

void InitLimitedPoolReflactionMesh(PoolMesh *a0)
{
    int i;
    int j;

    a0->mesh = prim_InitMesh3D(a0->ncol, a0->nrow, 1, 0x1C, a0->color, 1);
    a0->height = iosMallocDebug(ios_partition_sugipon, a0->nrow * 4, "src/pool.c", 884);
    a0->row = iosMallocDebug(ios_partition_sugipon, a0->nrow * 4, "src/pool.c", 885);
    for (i = 0; i < a0->nrow; i++) {
        a0->row[i] = a0->mesh->pos + i * a0->ncol;
        a0->height[i] = iosMallocDebug(ios_partition_sugipon, a0->ncol * 4, "src/pool.c", 890);
        for (j = 0; j < a0->ncol; j++) {
            a0->height[i][j] = 0.0f;
        }
    }
}

void SetLayoutedPoolReflactionMesh(PoolMesh *a0)
{
    ConstVec vec;
    float out[4];
    Mesh3D *mesh;
    char *tmp;
    char *base;
    Prim3DVec *q;
    Prim3DVec *uv;
    float sx;
    float sy;
    float iw;
    float h;
    float t;
    int i;
    int j;

    if (systemStatus[5] == 0) {
        for (i = 0; i < a0->nrow; i++) {
            a0->height[i][0] -= (a0->height[i][0] - random_signed() * 0.1f) * 0.8f;
            for (j = a0->ncol - 1; j > 0; j--) {
                a0->height[i][j] -= (a0->height[i][j] - a0->height[i][j - 1] * 1.15f) * 0.8f;
            }
        }
    }

    mesh = a0->mesh;
    vec = screenOrigin;
    sx = 1.0f / (float)ScreenWidth;
    sy = 1.0f / (float)ScreenHeight;
    tmp = (char *)(matrixptr + 0x4C0);
    base = (char *)(matrixptr + 0x440);

    CopyVector(base, &vec);

    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < a0->nrow; i++) {
        q = mesh->pos + i * a0->ncol;
        uv = mesh->st + i * a0->ncol;
        for (j = 0; j < a0->ncol; j++) {
            h = a0->height[i][j];
            _ApplyCurrentMatrix(out, q);
            iw = 1.0f / out[3];
            _ScaleVector(tmp, out, iw);
            _SubVector(out, tmp, base);
            t = out[0] * sx + 0.5f + h * 50.0f * iw;
            uv->x = t < 0.0f ? 0.0f : t;
            t = out[1] * sy + 0.5f + h * 50.0f * iw;
            uv->y = 1.0f < t ? 1.0f : t;
            q++;
            uv++;
        }
    }
    prim_UpdateMesh3D(mesh, 9, buffer_ID);
}

void SetLimitedPoolReflactionMesh(PoolMesh *a0, char *a1, char *a2)
{
    PoolWork *w = GOBJ_SUB(a1)->f_830;
    float pos[4];
    float v1[4];
    float v2[4];
    ConstVec vec;
    float out[4];
    Mesh3D *mesh;
    char *tmp;
    char *base;
    Prim3DVec *q;
    Prim3DVec *uv;
    float dist;
    float dz;
    float sx;
    float sy;
    float iw;
    float h;
    int i;
    int j;

    if (systemStatus[5] == 0) {
        for (i = 0; i < a0->nrow; i++) {
            for (j = 0; j < a0->ncol; j++) {
                a0->height[i][j] -= (a0->height[i][j] - random_signed() * 0.3f) * 0.5f;
            }
        }
    }
    GetRootPosition(pos, a2);
    CopyVector(v1, pos);
    v1[1] = w->pos[1];
    CopyVector(v2, pos);
    v2[1] += GOBJ_SUB(a2)->f_270;

    pos[1] = (v1[1] + v2[1]) * 0.5f;
    _InterVectorXYZ(pos, pos, (char *)(matrixptr + 944),
                    (v1[1] - *(float *)(matrixptr + 948)) / (pos[1] - *(float *)(matrixptr + 948)));

    _InterVectorXYZ(v2, v2, (char *)(matrixptr + 944),
                    (v1[1] - *(float *)(matrixptr + 948)) / (v2[1] - *(float *)(matrixptr + 948)));

    dist = GetPointDistance(v1, v2) + 100.0f;

    pos[0] -= dist * 0.5f;
    pos[2] -= dist * 0.5f;

    mesh = a0->mesh;
    vec = screenOrigin;
    sx = 1.0f / (float)ScreenWidth;
    sy = 1.0f / (float)ScreenHeight;
    tmp = (char *)(matrixptr + 0x4C0);
    base = (char *)(matrixptr + 0x440);

    dz = dist / (float)a0->nrow;

    CopyVector(base, &vec);

    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < a0->nrow; i++) {
        q = mesh->pos + i * a0->ncol;
        uv = mesh->st + i * a0->ncol;
        for (j = 0; j < a0->ncol; j++) {
            h = a0->height[i][j];
            q->x = pos[0] + (float)i * dz;
            q->y = pos[1];
            q->z = pos[2] + (float)j * dz;
            q->w = 1.0f;
            _ApplyCurrentMatrix(out, q);
            iw = 1.0f / out[3];
            _ScaleVector(tmp, out, iw);
            _SubVector(out, tmp, base);
            uv->x = out[0] * sx + 0.5f + h * 50.0f * iw;
            uv->y = out[1] * sy + 0.5f + h * 50.0f * iw;
            q++;
            uv++;
        }
    }
    prim_UpdateMesh3D(mesh, 9, buffer_ID);
}

void DispLimitedPoolReflactionMesh(PoolMesh *a0)
{
    gif_StartPacketPri(4);
    copyToWork(4);
    gif_SetGsReg(6, workVram | 0x20010000 | 0x600000000LL);
    gif_SetDrawEnviroment(0x800, 0, ScreenWidth, ScreenHeight, 1, 0);
    gif_SetGsReg(0x14, 0x60);
    gif_SetZWrite(0);
    gif_SetZTest(1);
    gif_SetAlpha(0, 4, 0x80);
    gif_EndPacket();
    _SetCurrentMatrix(matrixptr + 0x100);
    prim_DispMesh3D(a0->mesh, dispLightColor, dispLightNormal, -1);
    if (debug_skel_flag != 0) {
        DispMeshWire(a0->row, a0->nrow, a0->ncol);
    }
}

void PoolGeo(void) {}

float GetPoolGlobalHeight(char *a0)
{
    return ((PoolWork *)GOBJ_SUB(a0)->f_830)->pos[1];
}

float GetPoolGlobalHeightDetail(char *a0, float *pos)
{
    PoolWork *p = GOBJ_SUB(a0)->f_830;
    float inv;
    int ix;
    int iz;

    if (p->hasGrid != 0) {
        inv = 1.0f / p->step;
        ix = (int)((pos[0] - p->pos[0]) * inv + (float)(p->nx >> 1));
        iz = (int)((pos[2] - p->pos[2]) * inv + (float)(p->ny >> 1));
        ix = ix >= 0 ? (ix < p->nx ? ix : p->nx - 1) : 0;
        iz = iz >= 0 ? (iz < p->ny ? iz : p->ny - 1) : 0;
        return p->height[ix][iz] * 100.0f + p->pos[1];
    }
    return p->pos[1];
}

int CheckPoolHasGridMesh(char *a0)
{
    return ((PoolWork *)GOBJ_SUB(a0)->f_830)->hasGrid != 0;
}

void InitLayoutedPoolReflactionMesh(PoolMesh *a0, PoolMeshQuad *a1)
{
    float v0[4];
    float v1[4];
    int i;
    int j;

    InitLimitedPoolReflactionMesh(a0);
    for (i = 0; i < a0->nrow; i++) {
        _InterVectorXYZ(v0, &a1->corner[0], &a1->corner[2], (float)i / (float)(a0->nrow - 1));
        _InterVectorXYZ(v1, &a1->corner[1], &a1->corner[3], (float)i / (float)(a0->nrow - 1));
        for (j = 0; j < a0->ncol; j++) {
            _InterVectorXYZ(&a0->mesh->pos[i * a0->ncol + j], v0, v1,
                            (float)j / (float)(a0->ncol - 1));
            a0->mesh->pos[i * a0->ncol + j].w = 1.0f;
        }
    }
}

int poolRideFunc(char **a0, char *a1)
{
    Sub15C *e = GOBJ_SUB(a1);
    PoolWork *p = GOBJ_SUB(a0[0])->f_830;
    e->f_644 = e->f_A4 - p->pos[1];
    return 1;
}

float getWave(float t)
{
    t += 50.0f;
    t -= (float)(int)(t * 0.005f) * 200.0f;
    if (t < 100.0f) {
        return t * 0.01f - 0.5f;
    }
    return -(t - 100.0f) * 0.01f + 0.5f;
}
