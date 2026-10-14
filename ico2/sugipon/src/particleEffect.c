#include "debug.h"
#include "DisplayList.h"
#include "Primitive.h"
#include "quaternion.h"
#include <libvu0.h>
#include <string.h>
#include "memory.h"
#include "typedef.h"
#include "ios.h"
#include "Matrix.h"
#include "main.h"
#include "matrixDrive.h"
#include "DmaPacket.h"
#include "windField.h"
#include "particleEffect.h"
#include "include_asm.h"

static int setParticleEffect(struct PEGeo *self, struct PEPackage *pkg, struct IosMemPart *part);

/* one vertex of the particle primitive's buffers */
typedef struct PEVtx { /* field names derived */
    float pos[3];      /* 0x00 */
    float size;        /* 0x0C */
    float u;           /* 0x10 */
    float v;           /* 0x14 */
    float q;           /* 0x18 */
    float alpha;       /* 0x1C */
} PEVtx;               /* derived name */

typedef struct { /* field names derived */
    float v[4];
} PEVector; /* derived name */

typedef struct { /* field names derived */
    float v[4];
} PEQuaternion; /* derived name */

typedef struct {            /* field names derived */
    int used;               /* 0x00 */
    int geoCtrl;            /* 0x04 */
    int sensing;            /* 0x08 */
    PEVector *sensPos;      /* 0x0C */
    PEQuaternion *sensQuat; /* 0x10 */
    PEGeo *geo;             /* 0x14 */
} PEffect;                  /* derived name */

/* 128 effect slots of 0x18 bytes, then 53 parameter records of 160 bytes
   (the PE160 pool the effect slots index into) */
static PEffect particleEffects[128]; /* derived name */

static int particleParams[53 * 40]; /* derived name */

/* the free-slot search, inlined at its one call site */
static inline int searchFreeParticleEffect(void) /* derived name */
{
    int i;

    for (i = 0; i < 128; i++) {
        if (particleEffects[i].used == 0) {
            if (particleEffects[i].geo != 0) {
                debug_StdPrintfDummy("PARTICLE EFFECT WRONG\n");
                for (;;) {}
            }
            return i;
        }
    }
    return -1;
}

static void setParticleEffectGeometry(PEGeo *geo, void *pos, void *quat)
{
    CopyVector(geo->pos, pos);
    CopyQuaternion(geo->quat, quat);
}

/* the staging record makeParticle fills before copying it whole into the
   caller's slot, the blank particle peSetVtx writes for an unused vertex, and
   the cleared effect slot InitParticleEffects fills the table with */
static PEPartRec particleWork = {
    1,                        /* alive */
    0,                        /* spin */
    0,                        /* pad08 */
    {0.0f, 0.0f, 0.0f, 1.0f}, /* pos */
    {0.0f, 0.0f, 0.0f, 0.0f}, /* vel */
    0,
    0,    /* spinX, spinY */
    1.0f, /* size */
    0.1f, /* sizeStep */
    1.0f, /* alpha */
    1.0f, /* alphaStep */
    60,   /* life */
    {0},
    {128, 128, 128, 128}, /* col */
    0.0f,
    0.0f, /* u, v */
}; /* derived name */

static PEPartRec blankParticle = {
    1,
    0,
    0,
    {0.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    0,
    0,
    0.0f,
    0.1f,
    1.0f,
    1.0f,
    60,
    {0},
    {0, 0, 0, 0},
    0.0f,
    0.0f,
}; /* derived name */

static PEffect emptyEffect = {0, 0, 1, 0, 0, 0, 0}; /* derived name */

/* The scratch vector the spread offset is written into and the current
   matrix is applied to; its definition follows the default package. */
static sceVu0FVECTOR spreadVector; /* derived name */

/* the 0..1 draw and the same draw mapped onto -1..1, as sugiCommon.h's
   random_unit and random_signed */
static inline float sugiRandom(void) /* derived name */
{
    return _GetRandom();
}

static inline float sugiSignedRandom(void) /* derived name */
{
    return sugiRandom() * 2.0f - 1.0f;
}

static void _setParticleEffect(PEPartRec *out, PEPackage *pkg, char *m, float k);

/* Project the effect's origin through the current camera matrix and report
   whether the result falls outside the screen box. */
static inline int particleEffectOffScreen(PEGeo *geo) /* derived name */
{
    float v[4];

    if (geo->clip != 0) {
        sceVu0ApplyMatrix(v, matrixptr + 0x100, geo->pos);
        sceVu0ScaleVectorXYZ(v, v, 1.0f / v[3]);
        if (v[2] < 0.0f || v[0] < 0.0f || 4095.0f < v[0] || v[1] < 0.0f || 4095.0f < v[1]) {
            return 1;
        }
    }
    return 0;
}

/* the vertex writer */
static inline void peSetVtx(PEVtx *dst, PEPartRec *pt) /* derived name */
{
    CopyVector(dst, pt->pos);
    dst->size = pt->size;
    dst->alpha = pt->alpha * 128.0f;
    dst->u = pt->u;
    dst->v = pt->v;
    dst->q = 128.0f;
}

/* The statements follow the developer's line order (287 self->pkg, 289,
   291, 292, 293, 295, 296, 299, 300, 303). */
INCLUDE_ASM(setParticleEffect);

/* the EE scratchpad holds the particle being updated */
#define PEWORK (*(PEPartRec *)0x70000000) /* derived name */

/* the per-particle integrator: 0 for a slot that is already dead, 1
   otherwise */
static inline int updateParticle(PEGeo *self, float *m) /* derived name */
{
    float wv[4];
    PEPackage *pkg;
    void *wind;

    pkg = self->pkg;
    if (PEWORK.alive == 0) {
        return 0;
    }
    wind = GetWindVector(0, PEWORK.pos);
    PEWORK.vel[0] = PEWORK.vel[0] + (sugiRandom() - 0.5f) * 0.2f;
    PEWORK.vel[1] = PEWORK.vel[1] + pkg->gravity;
    PEWORK.vel[2] = PEWORK.vel[2] + (sugiRandom() - 0.5f) * 0.2f;
    sceVu0ScaleVector(PEWORK.vel, PEWORK.vel, pkg->drag);
    sceVu0AddVector(PEWORK.pos, PEWORK.pos, PEWORK.vel);
    _ScaleVectorXYZ(wv, wind, pkg->wind);
    _AddVectorXYZ(PEWORK.pos, PEWORK.pos, wv);
    if (self->floorOn != 0) {
        if (self->floor > PEWORK.pos[1]) {
            PEWORK.pos[1] = self->floor;
            PEWORK.vel[1] = 0.0f;
        }
    }
    if (PEWORK.life < pkg->life) {
        PEWORK.alpha = PEWORK.alpha - PEWORK.alphaStep;
    }
    if (PEWORK.alpha < 0.0f) {
        PEWORK.alpha = 0.0f;
    }
    PEWORK.size = PEWORK.size + PEWORK.sizeStep;
    if (PEWORK.size < 0.0f) {
        PEWORK.size = 0.0f;
    }
    PEWORK.sizeStep = PEWORK.sizeStep * pkg->sizeStepDecay;
    if (PEWORK.spin != 0) {
        PEWORK.spinX = PEWORK.spinX + PEWORK.spinY;
        PEWORK.spinY = (short)((float)PEWORK.spinY * pkg->spinYDecay);
    }
    PEWORK.life = PEWORK.life - 1;
    if (PEWORK.life < 0) {
        if (pkg->mode == 1) {
            MatrixDrive_PushMatrix();
            _setParticleEffect(&PEWORK, pkg, (char *)m, self->rate);
            MatrixDrive_PopMatrix();
        } else {
            PEWORK.alive = 0;
        }
    }
    return 1;
}

INCLUDE_ASM(execParticleEffect);

/* The display-list packet builder state, the same record src/GifPacket.c
   carries: `ptr` is the write cursor and `dma`, `tail`, `gif` and `end` are
   the back-pointers the end-of-packet patch fills in once the size is known. */

/* One 64-bit slot of a DMA/GIF packet, written either whole or as one half. */

/* the GS-register writer, a file-static copy of gif_SetGsReg (the same
   construct src/GifPacket.c uses); the out-of-line copy is in src/GifPacket.c */
static inline void peSetGsReg(long long reg, long long data) /* derived name */
{
    *PacketBufferStruct.ptr.d++ = data;
    *PacketBufferStruct.ptr.d++ = reg;
}

static void dispParticleEffect(PEGeo *geo)
{
    char *c;
    char *p;
    char *q;

    if (particleEffectOffScreen(geo)) {
        return;
    }
    dl_SetDLPriority(6);
    c = PacketBufferStruct.ptr.c;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.end.c = 0;
    PacketBufferStruct.dma.c = c;
    PacketBufferStruct.tail.c = c;
    PacketBufferStruct.ptr.c = c + 8;
    ((GifPkWord *)(c + 8))->w[0] = 0x11000000;
    PacketBufferStruct.gif.c = c + 0xC;
    PacketBufferStruct.end.c = c + 0x10;
    PacketBufferStruct.ptr.c = c + 0x18;
    ((GifPkWord *)(c + 0x18))->d = 0xE;
    PacketBufferStruct.ptr.c = c + 0x20;
    switch (geo->pkg->alphaMode) {
    case 1:
        peSetGsReg(0x49, 0);
        peSetGsReg(0x42, 0x48);
        break;
    case 2:
        peSetGsReg(0x49, 0);
        peSetGsReg(0x42, 0x42);
        break;
    case 0:
    default:
        peSetGsReg(0x49, 0);
        peSetGsReg(0x42, 0x44);
        break;
    }
    ((GifPkWord *)PacketBufferStruct.end.c)->d =
        (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >> 4) -
                       1) |
        0x1000000000008000LL;
    ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
        (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
        0x6C008000;
    p = PacketBufferStruct.ptr.c;
    ((GifPkWord *)p)->w[0] = 0x15000000;
    p += 4;
    PacketBufferStruct.ptr.d = (unsigned long long *)p;
    ((GifPkWord *)p)->w[0] = 0;
    PacketBufferStruct.ptr.c = p + 4;
    ((GifPkWord *)(p + 4))->w[0] = 0;
    PacketBufferStruct.ptr.c = p + 8;
    ((GifPkWord *)(p + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = p + 0xC;
    ((GifPkWord *)PacketBufferStruct.tail.c)->d =
        (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.tail.c) >>
                         4) -
                        1) |
                       0x10000000);
    q = PacketBufferStruct.ptr.c;
    PacketBufferStruct.tail.c = q;
    ((GifPkWord *)q)->d = 0x60000000;
    PacketBufferStruct.ptr.c = q + 8;
    ((GifPkWord *)(q + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = q + 0xC;
    ((GifPkWord *)(q + 8))->w[1] = 0;
    PacketBufferStruct.ptr.c = q + 0x10;
    dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
    dl_CloseDma();
    prim_DispParticle(geo->prim, matrixptr + 0x100);
}

int SetParticleEffectByPartition(int no, void *pos, void *quat, struct IosMemPart *part);

/* free one effect's geometry; every deleter in this file inlines it */
static inline void deleteParticleEffectGeo(int no) /* derived name */
{
    prim_DeleteParticle(particleEffects[no].geo->prim);
    *(int *)((char *)particleEffects[no].geo + 0x28) = 0;
    iosFree(particleEffects[no].geo->parts);
    iosFree(particleEffects[no].geo);
    particleEffects[no].geo = 0;
}

INCLUDE_ASM(SetParticleEffect);

INCLUDE_ASM(SetParticleEffectGeometry);

INCLUDE_ASM(SetParticleEffectUpperLimit);

/* the per-particle vector setup, shared by setParticleEffect,
 * execParticleEffect and ExecParticleEffect */
static inline void setParticleVector(PEVtx *d, PEPartRec *s) /* derived name */
{
    CopyVector(d, s->pos);
    d->size = s->size;
    d->alpha = s->alpha * 128.0f;
    d->u = s->u;
    d->v = s->v;
    d->q = 128.0f;
}

static inline void updateParticleVectors(int no) /* derived name */
{
    PEGeo *g;
    PEVtx *d;
    PEPartRec *s;
    int i;

    g = particleEffects[no].geo;
    d = (PEVtx *)g->prim->vtx;
    s = g->parts;
    for (i = 0; i < g->n; i++) {
        setParticleVector(d, s);
        s++;
        d++;
    }
}

INCLUDE_ASM(ExecParticleEffect);

INCLUDE_ASM(ResetParticleEffectPackages);

/* the default package a file's record is laid over, then the spread
   vector */
static PEPackage defaultPackage = {
    11,                          /* version */
    1,                           /* mode */
    1,                           /* alphaMode */
    360,                         /* spread */
    {0},   2.0f,                 /* speed */
    0.1f,                        /* speedRand */
    0.95f,                       /* drag */
    -0.1f,                       /* gravity */
    0,                           /* spinY */
    {0},   0.1f,                 /* spinYRand */
    0.95f,                       /* spinYDecay */
    10.0f,                       /* size */
    0.1f,                        /* sizeRand */
    0.3f,                        /* sizeStep */
    0.01f,                       /* sizeStepRand */
    1.0f,                        /* sizeStepDecay */
    80,                          /* count */
    80,                          /* emit */
    0.1f,                        /* emitRand */
    1.0f,                        /* emitStep */
    0.2f,                        /* alpha */
    0.1f,                        /* alphaRand */
    80,                          /* life */
    0.1f,                        /* lifeRand */
    {0},   {128, 128, 128, 128}, /* col */
    0,                           /* u */
    0,                           /* v */
    0,                           /* spinX */
    {0},   0.1f,                 /* spinXRand */
    1.0f,                        /* wind */
    0,                           /* floorOn */
    0,                           /* floorDepth */
}; /* derived name */

static sceVu0FVECTOR spreadVector = {0.0f, 0.0f, 1.0f, 0.0f}; /* derived name */

void SetParticleEffectPackage(int no, int *data, int size)
{
    *(PEPackage *)((unsigned char *)particleParams + no * 160) = defaultPackage;
    if (*(int *)&defaultPackage != *data) {
        debug_StdPrintfDummy("\033[36mThis is old version(%d) file. May be an error occur.\033[m\n",
                             *data);
    }
    memcpy(((unsigned char *)particleParams + no * 160), data, size);
}

INCLUDE_ASM(InitParticleEffects);

INCLUDE_ASM(DispParticleEffects);

INCLUDE_ASM(DeleteParticleEffect);

/* the body of SetParticleEffect, which SetParticleEffectActiveSensing
 * inlines and SetParticleEffect calls */
static inline int SetParticleEffect_inl(int no, void *pos, void *quat) /* derived name */
{
    return SetParticleEffectByPartition(no, pos, quat, ios_partition_oomori);
}

INCLUDE_ASM(SetParticleEffectActiveSensing);

/* the bodies of GetParticleEffectPackage and DeleteParticleEffectsByPackage,
 * which DeleteParticleEffectsByID inlines and the two exported functions
 * call */
static inline int *GetParticleEffectPackage_inl(int idx) /* derived name */
{
    return (int *)((char *)particleParams + idx * 160);
}

static inline void DeleteParticleEffectsByPackage_inl(int *pkg) /* derived name */
{
    int i;

    for (i = 0; i < 128; i++) {
        if (particleEffects[i].used != 0 && particleEffects[i].geo->pkg == (PEPackage *)pkg) {
            deleteParticleEffectGeo(i);
            particleEffects[i].used = 0;
        }
    }
}

int *GetParticleEffectPackage(int idx)
{
    return GetParticleEffectPackage_inl(idx);
}

INCLUDE_ASM(DeleteParticleEffectsByPackage);

INCLUDE_ASM(DeleteParticleEffectsByID);

INCLUDE_ASM(GetParticleEffectData);

INCLUDE_ASM(DisableParticleEffectGeometryControl);

INCLUDE_ASM(GetParticleIDWithName);

int GetParticleLoopFlag(int id)
{
    int *p;
    if (id < 0) {
        return -1;
    }
    p = (int *)((char *)particleParams + id * 160);
    return p[1] == 1;
}

INCLUDE_ASM(ParticleEffects_SetAllGoal);

INCLUDE_ASM(SetParticleEffectClipEnableFlag);
