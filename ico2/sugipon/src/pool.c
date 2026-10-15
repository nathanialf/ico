#include "sugiCommon.h"
#include "box.h"
#include "pool.h"
#include "memory.h"
#include "DisplayP2O.h"
#include "DObj.h"
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
#include "Texture.h"
#include "include_asm.h"

static void copyToWork(int pri);

static void falldownSE(GObj *self)
{
    ExecuteSEPackage(self, 81);
}

/* The whole drawing area as a sprite rectangle in GS primitive coordinates,
   a corner and a size: copyToWork and flushWork blit the frame through it. */
static const GifRect workRect = {-2048, -2048, 4096, 4096}; /* derived name */

/* the two work-area VRAM addresses */
static int workVram = 0; /* derived name */

static int work1Vram = 0; /* derived name */

static void copyToWork(int pri)
{
    GifRect rect;

    tex_ResetVramPri(pri);
    workVram = tex_AllocVramAuto(0, 0x400);
    gif_SetGsReg(6, ((long long)(ScreenWidth / 64) << 14) | 0x664000800LL);
    gif_SetDrawEnviroment(workVram, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetZWrite(0);
    gif_SetAlpha(0, 4, 0);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x14, 0x60);
    rect = workRect;
    /* the frame, through the work rectangle, at full colour */
    {
        GifRect uv = {8, 8, ScreenWidth * 16, ScreenHeight * 16};
        GifColor col = {128, 128, 128, 128};

        gif_SpriteSensitiveOrg(&rect, 0, &uv, &col, 0);
    }
    gif_SetZWrite(1);
    gif_SetZTest(1);
    gif_SetGsReg(0x47, 0x5000D);
}

static void flushWork(int pri)
{
    GifRect rect;
    GifColor col;

    tex_ResetVramPri(pri);
    workVram = tex_AllocVramAuto(0, 0x400);
    work1Vram = tex_AllocVramAuto(0, 0x400);
    gif_SetDrawEnviroment(workVram, 0, 0x100, 0x100, 0, 0);
    gif_SetZTest(0);
    gif_SetGsReg(0x4E, 0x30000000 | (work1Vram / 32));
    gif_SetAlpha(0, 4, 0);
    rect = workRect;
    col = (GifColor){255, 255, 255, 128};
    gif_SpriteSensitiveOrg(&rect, 0, 0, &col, 0);
    gif_SetZTest(1);
}

/* One ripple of the pool's surface: the grid cell it started in and the
   remainder inside that cell on each of the two horizontal axes, its
   amplitude (negative when the slot is free) and its age.  InitPoolGeo
   clears five of them, SetFallDownSplash starts the next one in turn. */
typedef struct { /* field names derived */
    int ix;      /* 0x00 */
    float fx;    /* 0x04 */
    int iz;      /* 0x08 */
    float fz;    /* 0x0C */
    float amp;   /* 0x10 */
    float age;   /* 0x14 */
} PoolRipple;    /* derived name */

/* The pool's work record, the 224 bytes InitPoolGeo allocates and leaves in
   the object's work word (Sub15C+0x830): the surface's position (its y is
   the water height every reader takes) and drain vector, the two splash
   managers, the height grid and its two meshes, the ripples, the wave phase
   and the reflected stage object. */
typedef struct {          /* field names derived */
    float pos[4];         /* 0x00 */
    float drain[4];       /* 0x10, GetPoolGlobalDrainVector's vector: the
                               layout's x and z angles in degrees */
    int splashNo;         /* 0x20, the next slot of splash */
    BgaDisp *splash;      /* 0x24, two splash animations */
    int word28;           /* 0x28 */
    BgaDisp *bga;         /* 0x2C, ten animations PoolDL draws */
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
    Sub15C *dobj;         /* 0xD0, the reflected stage object or 0 */
    int spin;             /* 0xD4 */
} PoolWork;               /* derived name */

/* Plant one cell of the pool's ripple grid at a world position: the grid
   index and the in-cell remainder on each of the two horizontal axes, then
   the amplitude the caller asks for and a zero age.  SetFallDownSplash and
   InitPoolGeo use it. */
static inline void setWaveCell(PoolWork *w, float *pos, PoolRipple *cell, float step, int nx,
                               int ny, float amp) /* derived name */
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

static void setNodePursueParticleEffectWithUpperLimit(int id, GObj *obj, int focus, float limit)
{
    int ret = GetSkeltonFocusNode(obj, focus);
    if (ret != -1) {
        Sub15C *p = GOBJ_SUB(obj);
        int r = SetParticleEffectActiveSensing(id, p->nodeMtx + ret * 64 + 48, IdentityQuaternion);
        SetParticleEffectUpperLimit(r, limit);
    }
}

INCLUDE_ASM(SetFallDownSplash);

INCLUDE_ASM(GetPoolGlobalDrainVector);

typedef union { /* field names derived */
    int i[4];
    float f[4];
} PoolQuad; /* derived name */

typedef struct {    /* field names derived */
    PoolQuad pos;   /* 0x00 */
    PoolQuad rot;   /* 0x10 */
    PoolQuad scale; /* 0x20 */
} PoolDisp;         /* derived name */

static int poolRideFunc(ObjNode *on, GObj *rider);

INCLUDE_ASM(InitPoolGeo);

static inline void decayRipple(PoolRipple *c) /* derived name */
{
    if (c->amp < 0.0f) {
        return;
    }
    c->age += 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]);
    c->amp -= 60.0f / (float)((60 - systemStatus[0] * 10) / systemStatus[1]) * 0.0005f;
}

static inline void addRippleToGrid(PoolWork *w, PoolRipple *c, float **grid) /* derived name */
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

static inline void makeWaveGrid(PoolWork *w, float **grid, int ang) /* derived name */
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
static const ConstVec screenOrigin = {{2048.0f, 2048.0f, 0.0f, 0.0f}}; /* derived name */

INCLUDE_ASM(updatePoolGeo);

/* The fixed lighting the pool surface is drawn under, in the two matrices
   light_MakeLightMatrix otherwise builds at +0x40 and +0x00 of the object's
   light work: a colour matrix (a row per colour channel, a column per light)
   and a normal matrix (a column per light direction).  The first pair goes
   straight to prim_DispMesh3D, the second is copied into the work. */
static float dispLightColor[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 0.0f, 0.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
}; /* derived name */

static float dispLightNormal[4][4] = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
}; /* derived name */

static float workLightColor[4][4] = {
    {0.707f, 0.707f, 0.0f, 0.0f},
    {0.707f, 0.707f, 0.0f, 0.0f},
    {0.707f, 0.707f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
}; /* derived name */

static float workLightNormal[4][4] = {
    {1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, 1.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
}; /* derived name */

INCLUDE_ASM(dispPool);

INCLUDE_ASM(PoolDL);

void InitLimitedPoolReflactionMesh(PoolMesh *refl);

INCLUDE_ASM(InitLimitedPoolReflactionMesh);

void SetLayoutedPoolReflactionMesh(PoolMesh *refl)
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
        for (i = 0; i < refl->nrow; i++) {
            refl->height[i][0] -= (refl->height[i][0] - random_signed() * 0.1f) * 0.8f;
            for (j = refl->ncol - 1; j > 0; j--) {
                refl->height[i][j] -= (refl->height[i][j] - refl->height[i][j - 1] * 1.15f) * 0.8f;
            }
        }
    }

    mesh = refl->mesh;
    vec = screenOrigin;
    sx = 1.0f / (float)ScreenWidth;
    sy = 1.0f / (float)ScreenHeight;
    tmp = (char *)(matrixptr + 0x4C0);
    base = (char *)(matrixptr + 0x440);

    CopyVector(base, &vec);

    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 0x100);

    for (i = 0; i < refl->nrow; i++) {
        q = mesh->pos + i * refl->ncol;
        uv = mesh->st + i * refl->ncol;
        for (j = 0; j < refl->ncol; j++) {
            h = refl->height[i][j];
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

INCLUDE_ASM(SetLimitedPoolReflactionMesh);

INCLUDE_ASM(DispLimitedPoolReflactionMesh);

void PoolGeo(void) {}

INCLUDE_ASM(GetPoolGlobalHeight);

INCLUDE_ASM(GetPoolGlobalHeightDetail);

INCLUDE_ASM(CheckPoolHasGridMesh);

void InitLayoutedPoolReflactionMesh(PoolMesh *refl, PoolMeshQuad *quad)
{
    float v0[4];
    float v1[4];
    int i;
    int j;

    InitLimitedPoolReflactionMesh(refl);
    for (i = 0; i < refl->nrow; i++) {
        _InterVectorXYZ(v0, &quad->corner[0], &quad->corner[2], (float)i / (float)(refl->nrow - 1));
        _InterVectorXYZ(v1, &quad->corner[1], &quad->corner[3], (float)i / (float)(refl->nrow - 1));
        for (j = 0; j < refl->ncol; j++) {
            _InterVectorXYZ(&refl->mesh->pos[i * refl->ncol + j], v0, v1,
                            (float)j / (float)(refl->ncol - 1));
            refl->mesh->pos[i * refl->ncol + j].w = 1.0f;
        }
    }
}

INCLUDE_ASM(poolRideFunc);

float getWave(float t)
{
    t += 50.0f;
    t -= (float)(int)(t * 0.005f) * 200.0f;
    if (t < 100.0f) {
        return t * 0.01f - 0.5f;
    }
    return -(t - 100.0f) * 0.01f + 0.5f;
}
