#include "common.h"
#include "ico/types.h"

typedef struct PEGeo PEGeo; /* the allocated per-effect geometry object */

typedef struct {
    float v[4];
} PEVector;

typedef struct {
    float v[4];
} PEQuaternion;

typedef struct {
    int used;               /* 0x00 */
    int pause;              /* 0x04 */
    int geoCtrl;            /* 0x08 */
    int sensing;            /* 0x0C */
    PEVector *sensPos;      /* 0x10 */
    PEQuaternion *sensQuat; /* 0x14 */
    PEGeo *geo;             /* 0x18 */
} PEffect;

extern PEffect D_00720220[];

typedef struct {
    long long q[20];
} PE160;

extern void CopyQuaternion();
extern void CopyVector();

void setParticleEffectGeometry(int a0, int a1, int a2)
{
    CopyVector(a0);
    CopyQuaternion(a0 + 0x10, a2);
}

/* The two file-static staging records this function fills before block-copying
   the finished particle into the caller's slot. D_004ECCF0 is the 0x70-byte
   particle record itself; D_004ECE90 is the scratch vector the spread offset is
   written into and the current matrix is applied to. Both still live in the
   uncarved .data blob. */
/* the 0x70-byte particle record this function fills and then copies whole */
typedef struct {
    int unk_00;
    int spin; /* 0x04 */
    long long unk_08;
    float pos[4];    /* 0x10 */
    float vel[4];    /* 0x20 */
    short spinX;     /* 0x30 */
    short spinY;     /* 0x32 */
    float size;      /* 0x34 */
    float sizeStep;  /* 0x38 */
    float alpha;     /* 0x3C */
    float alphaStep; /* 0x40 */
    int life;        /* 0x44 */
    int unk_48;
    int unk_4C;
    int col[4]; /* 0x50 */
    float u;    /* 0x60 */
    float v;    /* 0x64 */
    int unk_68;
    int unk_6C;
} PEPartRec;

extern PEPartRec D_004ECCF0;
extern float D_004ECE90[4];
extern float _GetRandom(void);
extern void CopyMatrix(void *dst, void *src);
extern void CopyIVector(void *dst, void *src);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_RotMatrixX(int angle);
extern void MatrixDrive_RotMatrixY(int angle);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);

/* sugiCommon.h:47 and :55 in the PAL listing: two nested static helpers, the
   inner one the raw 0..1 draw and the outer one the same draw mapped onto
   -1..1. Both are inlined at every site here. */
static inline float sugiRandom(void)
{
    return _GetRandom();
}

static inline float sugiSignedRandom(void)
{
    return sugiRandom() * 2.0f - 1.0f;
}

void _setParticleEffect(char *out, char *pkg, char *m, float k)
{
    PEPartRec *w;
    int n;
    float span;

    w = &D_004ECCF0;
    CopyVector(w->pos, m + 0x30);
    D_004ECE90[2] = *(float *)(pkg + 0x10) * (*(float *)(pkg + 0x14) * sugiSignedRandom() + 1.0f);
    CopyMatrix(MatrixDrive_GetMatrix(), m);
    if (*(unsigned short *)(pkg + 0xC) != 0) {
        MatrixDrive_RotMatrixY(
            (short)((float)*(unsigned short *)(pkg + 0xC) * (sugiRandom() - 0.5f) * 182.04445f));
        MatrixDrive_RotMatrixX(
            (short)((float)*(unsigned short *)(pkg + 0xC) * (sugiRandom() - 0.5f) * 182.04445f));
    }
    sceVu0ApplyMatrix(w->vel, MatrixDrive_GetMatrix(), D_004ECE90);
    n = (int)((float)(unsigned int)*(int *)(pkg + 0x44) *
              (*(float *)(pkg + 0x48) * sugiSignedRandom() + 1.0f));
    w->life = (float)n * k;
    w->size = *(float *)(pkg + 0x2C) * (*(float *)(pkg + 0x30) * sugiSignedRandom() + 1.0f);
    w->alpha = *(float *)(pkg + 0x50) * (*(float *)(pkg + 0x54) * sugiSignedRandom() + 1.0f) * k;
    w->sizeStep = *(float *)(pkg + 0x34) * (*(float *)(pkg + 0x38) * sugiSignedRandom() + 1.0f);
    if (*(short *)(pkg + 0x20) != 0) {
        w->spin = 1;
        w->spinX = (short)((float)*(short *)(pkg + 0x88) *
                           (*(float *)(pkg + 0x8C) * sugiSignedRandom() + 1.0f));
        w->spinY = (short)((float)*(short *)(pkg + 0x20) *
                           (*(float *)(pkg + 0x24) * sugiSignedRandom() + 1.0f));
    } else {
        w->spin = 0;
    }
    span = (float)*(int *)(pkg + 0x58) * (*(float *)(pkg + 0x5C) * sugiSignedRandom() + 1.0f);
    w->alphaStep = w->alpha / span;
    if ((float)w->life < span) {
        w->alpha = w->alpha - (span - (float)w->life) * w->alphaStep;
    }
    CopyIVector(w->col, pkg + 0x70);
    w->u = (float)*(int *)(pkg + 0x80) * 0.25f;
    w->v = (float)*(int *)(pkg + 0x84) * 0.25f;
    *(PEPartRec *)out = D_004ECCF0;
}

INCLUDE_ASM("asm/nonmatchings/src/particleEffect", setParticleEffect);

extern char *matrixptr;
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float k);
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *p);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);

/* particleEffect.c:358-367 in the PAL listing, rows outside dispParticleEffect's
   own span (443-484): a static helper with no out-of-line copy, inlined at the
   one call site. It projects the effect's origin through the current camera
   matrix and reports whether the result falls outside the screen box. */
static inline int particleEffectOffScreen(char *geo)
{
    float v[4];

    if (*(int *)(geo + 0x34) != 0) {
        sceVu0ApplyMatrix(v, matrixptr + 0x100, geo);
        sceVu0ScaleVectorXYZ(v, v, 1.0f / v[3]);
        if (v[2] < 0.0f || v[0] < 0.0f || 4095.0f < v[0] || v[1] < 0.0f || 4095.0f < v[1]) {
            return 1;
        }
    }
    return 0;
}

/* particleEffect.c:159-164: the vertex writer, a static helper with no
   out-of-line copy, inlined at every site in this TU. */
static inline void peSetVtx(char *dst, char *pt)
{
    CopyVector(dst, pt + 0x10);
    *(float *)(dst + 0xC) = *(float *)(pt + 0x34);
    *(float *)(dst + 0x1C) = *(float *)(pt + 0x3C) * 128.0f;
    *(float *)(dst + 0x10) = *(float *)(pt + 0x60);
    *(float *)(dst + 0x14) = *(float *)(pt + 0x64);
    *(float *)(dst + 0x18) = 128.0f;
}

/* the blank particle template, the 0x70-byte record that follows D_004ECCF0 */
extern char D_004ECD60[];
extern void *GetWindVector(int a0, void *v);
extern void sceVu0ScaleVector(void *dst, void *src, float k);
extern void sceVu0AddVector(void *dst, void *a, void *b);
extern void _ScaleVectorXYZ(void *dst, void *src, float k);
extern void _AddVectorXYZ(void *dst, void *a, void *b);

/* the EE scratchpad holds the particle being updated */
#define PEWORK (*(PEPartRec *)0x70000000)

/* particleEffect.c:217-276 in the PAL listing, rows outside execParticleEffect's
   own span (383-427): the per-particle integrator, inlined at its one call site.
   It returns 0 for a slot that is already dead and 1 otherwise. */
static inline int updateParticle(char *self, float *m)
{
    float wv[4];
    char *pkg;
    void *wind;

    pkg = *(char **)(self + 0x20);
    if (PEWORK.unk_00 == 0) {
        return 0;
    }
    wind = GetWindVector(0, PEWORK.pos);
    PEWORK.vel[0] = PEWORK.vel[0] + (sugiRandom() - 0.5f) * 0.2f;
    PEWORK.vel[1] = PEWORK.vel[1] + *(float *)(pkg + 0x1C);
    PEWORK.vel[2] = PEWORK.vel[2] + (sugiRandom() - 0.5f) * 0.2f;
    sceVu0ScaleVector(PEWORK.vel, PEWORK.vel, *(float *)(pkg + 0x18));
    sceVu0AddVector(PEWORK.pos, PEWORK.pos, PEWORK.vel);
    _ScaleVectorXYZ(wv, wind, *(float *)(pkg + 0x90));
    _AddVectorXYZ(PEWORK.pos, PEWORK.pos, wv);
    if (*(int *)(self + 0x38) != 0) {
        if (*(float *)(self + 0x3C) > PEWORK.pos[1]) {
            PEWORK.pos[1] = *(float *)(self + 0x3C);
            PEWORK.vel[1] = 0.0f;
        }
    }
    if (PEWORK.life < *(int *)(pkg + 0x58)) {
        PEWORK.alpha = PEWORK.alpha - PEWORK.alphaStep;
    }
    if (PEWORK.alpha < 0.0f) {
        PEWORK.alpha = 0.0f;
    }
    PEWORK.size = PEWORK.size + PEWORK.sizeStep;
    if (PEWORK.size < 0.0f) {
        PEWORK.size = 0.0f;
    }
    PEWORK.sizeStep = PEWORK.sizeStep * *(float *)(pkg + 0x3C);
    if (PEWORK.spin != 0) {
        PEWORK.spinX = PEWORK.spinX + PEWORK.spinY;
        PEWORK.spinY = (short)((float)PEWORK.spinY * *(float *)(pkg + 0x28));
    }
    PEWORK.life = PEWORK.life - 1;
    if (PEWORK.life < 0) {
        if (*(int *)(pkg + 0x4) == 1) {
            MatrixDrive_PushMatrix();
            _setParticleEffect((char *)0x70000000, pkg, (char *)m, *(float *)(self + 0x40));
            MatrixDrive_PopMatrix();
        } else {
            PEWORK.unk_00 = 0;
        }
    }
    return 1;
}

int execParticleEffect(void *a0)
{
    float m[16];
    char *self;
    char *part;
    char *base;
    char *d0;
    char *v0;
    char *v1;
    int flags;
    int i;
    int n;
    float last;
    float total;
    float next;

    self = (char *)a0;
    d0 = *(char **)(*(int *)(self + 0x28) + 0x190);
    flags = 0;
    if (particleEffectOffScreen(self)) {
        return *(int *)(*(int *)(self + 0x20) + 0x4) == 1;
    }
    GetMatrixFromQuaternionPos(m, self + 0x10, self);
    part = *(char **)(self + 0x24);
    for (i = 0; i < *(int *)(self + 0x30); i++, part += 0x70, d0 += 0x20) {
        if ((float)i < *(float *)(self + 0x2C)) {
            PEWORK = *(PEPartRec *)part;
            flags |= updateParticle(self, m);
            peSetVtx(d0, (char *)0x70000000);
            *(PEPartRec *)part = PEWORK;
        } else {
            peSetVtx(d0, D_004ECD60);
            flags |= 1;
        }
    }
    total = (float)*(int *)(self + 0x30);
    last = *(float *)(self + 0x2C);
    if (last < total) {
        v0 = *(char **)(*(int *)(self + 0x28) + 0x190);
        v1 = *(char **)(*(int *)(self + 0x28) + 0x194);
        base = *(char **)(self + 0x24);
        next = last + *(float *)(*(char **)(self + 0x20) + 0x4C);
        n = (int)next;
        if (total < next) {
            n = (int)total;
        }
        for (i = (int)last; i < n; i++) {
            _setParticleEffect(base + i * 0x70, *(char **)(self + 0x20), (char *)m, 1.0f);
            peSetVtx(v0 + i * 0x20, base + i * 0x70);
            peSetVtx(v1 + i * 0x20, base + i * 0x70);
        }
        *(float *)(self + 0x2C) = next;
    }
    return flags;
}

/* The display-list packet builder state, the same record src/GifPacket.c
   carries: `ptr` is the write cursor and `dma`, `tail`, `gif` and `end` are
   the back-pointers the end-of-packet patch fills in once the size is known. */
typedef struct {
    int cur;
    int *buf[2];
    char *dma;
    unsigned long long *ptr;
    char *tail;
    char *gif;
    char *end;
} GifDpk;

/* One 64-bit slot of a DMA/GIF packet, written either whole or as one half. */
typedef union {
    long long d;
    int w[2];
} GifPkWord;

extern GifDpk D_004EE6F0;
extern char *matrixptr;
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float k);
extern void dl_SetDLPriority(int pri);
extern void dl_OpenDma(int chan, void *dma, int flag);
extern void dl_CloseDma(void);
extern void prim_DispParticle(int prim, void *m);

/* INTERIM (the same construct src/GifPacket.c uses for its own gif_SetGsReg):
   the listing inlines the GS-register writer at every site in this TU, so it is
   `inline` in the dev's TU; the out-of-line copy lives in src/GifPacket.c and
   stays at its own ROM slot. */
static inline void peSetGsReg(long long a0, long long a1)
{
    *D_004EE6F0.ptr++ = a1;
    *D_004EE6F0.ptr++ = a0;
}

void dispParticleEffect(PEGeo *geo)
{
    char *c;
    char *p;
    char *q;

    if (particleEffectOffScreen((char *)geo)) {
        return;
    }
    dl_SetDLPriority(6);
    c = (char *)D_004EE6F0.ptr;
    D_004EE6F0.gif = 0;
    D_004EE6F0.end = 0;
    D_004EE6F0.dma = c;
    D_004EE6F0.tail = c;
    D_004EE6F0.ptr = (unsigned long long *)(c + 8);
    ((GifPkWord *)(c + 8))->w[0] = 0x11000000;
    D_004EE6F0.gif = c + 0xC;
    D_004EE6F0.end = c + 0x10;
    D_004EE6F0.ptr = (unsigned long long *)(c + 0x18);
    ((GifPkWord *)(c + 0x18))->d = 0xE;
    D_004EE6F0.ptr = (unsigned long long *)(c + 0x20);
    switch (*(unsigned int *)(*(int *)((char *)geo + 0x20) + 0x8)) {
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
    ((GifPkWord *)D_004EE6F0.end)->d =
        (unsigned int)(((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.end) >> 4) - 1) |
        0x1000000000008000LL;
    ((GifPkWord *)D_004EE6F0.gif)->w[0] =
        (((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.gif) >> 4) << 16) | 0x6C008000;
    p = (char *)D_004EE6F0.ptr;
    ((GifPkWord *)p)->w[0] = 0x15000000;
    p += 4;
    D_004EE6F0.ptr = (unsigned long long *)p;
    ((GifPkWord *)p)->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 4);
    ((GifPkWord *)(p + 4))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 8);
    ((GifPkWord *)(p + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 0xC);
    ((GifPkWord *)D_004EE6F0.tail)->d =
        (unsigned int)((((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.tail) >> 4) - 1) |
                       0x10000000);
    q = (char *)D_004EE6F0.ptr;
    D_004EE6F0.tail = q;
    ((GifPkWord *)q)->d = 0x60000000;
    D_004EE6F0.ptr = (unsigned long long *)(q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(q + 0x10);
    dl_OpenDma(5, D_004EE6F0.dma, 0);
    dl_CloseDma();
    prim_DispParticle(*(int *)((char *)geo + 0x28), matrixptr + 0x100);
}

extern char D_006208E0[];
extern char D_00620920[];
extern char D_00620908[];
extern int D_00721020[];
extern void debug_StdPrintfDummy();
extern int iosMallocDebugNoAssert(int heap, int size, char *file, int line);
extern void *iosFree(void *ptr);
extern int setParticleEffect(int geo, int *pkg, int part);

/* the listing's lines 129-137: a static free-slot search with no out-of-line
 * copy, inlined here. */
static inline int searchFreeParticleEffect(void)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used == 0) {
            if (D_00720220[i].geo != 0) {
                debug_StdPrintfDummy(D_006208E0);
                for (;;) {}
            }
            return i;
        }
    }
    return -1;
}

int SetParticleEffectByPartition(int no, PEVector *pos, PEQuaternion *quat, int part)
{
    int id;

    id = searchFreeParticleEffect();
    if (id < 0) {
        debug_StdPrintfDummy(D_00620920);
        return -1;
    }
    D_00720220[id].used = 1;
    D_00720220[id].geoCtrl = 1;
    D_00720220[id].geo = (PEGeo *)iosMallocDebugNoAssert(part, 0x80, D_00620908, 501);
    D_00720220[id].sensing = 0;
    D_00720220[id].sensPos = 0;
    D_00720220[id].sensQuat = 0;
    if (D_00720220[id].geo != 0) {
        setParticleEffectGeometry((int)D_00720220[id].geo, (int)pos, (int)quat);
        if (setParticleEffect((int)D_00720220[id].geo, (int *)((char *)D_00721020 + no * 0xA0),
                              part) == 0) {
            iosFree(D_00720220[id].geo);
            D_00720220[id].geo = 0;
            D_00720220[id].used = 0;
            id = -1;
        }
    } else {
        D_00720220[id].used = 0;
        id = -1;
    }
    return id;
}

extern char D_00620940[];
extern void prim_DeleteParticle(int a0);
extern void *iosFree(void *ptr);

/* INTERIM: the listing's lines 430-435 (a static helper with no out-of-line
 * copy) are inlined into every deleter in this TU. */
static inline void deleteParticleEffectGeo(int no)
{
    prim_DeleteParticle(*(int *)((char *)D_00720220[no].geo + 0x28));
    *(int *)((char *)D_00720220[no].geo + 0x28) = 0;
    iosFree(*(void **)((char *)D_00720220[no].geo + 0x24));
    iosFree(D_00720220[no].geo);
    D_00720220[no].geo = 0;
}

void SetParticleEffectGeometry(int a0, int a1, int a2)
{
    if (a0 >= 0) {
        if (D_00720220[a0].used == 0) {
            debug_StdPrintfDummy(D_00620940);
        } else {
            setParticleEffectGeometry((int)D_00720220[a0].geo, a1, a2);
        }
    }
}

extern int execParticleEffect(void *a0);

void SetParticleEffectUpperLimit(int no, float f)
{
    char *o;
    if (no >= 0) {
        o = (char *)D_00720220[no].geo;
        *(int *)(o + 0x38) = 1;
        *(float *)(o + 0x3C) = f;
        execParticleEffect(o);
    }
}

/* the listing's lines 159-164: the per-particle vector setup, a static helper
 * with no out-of-line copy shared by setParticleEffect / execParticleEffect /
 * ExecParticleEffect. */
static inline void setParticleVector(char *d, char *s)
{
    CopyVector(d, s + 0x10);
    *(float *)(d + 0x0C) = *(float *)(s + 0x34);
    *(float *)(d + 0x1C) = *(float *)(s + 0x3C) * 128.0f;
    *(float *)(d + 0x10) = *(float *)(s + 0x60);
    *(float *)(d + 0x14) = *(float *)(s + 0x64);
    *(float *)(d + 0x18) = 128.0f;
}

/* the listing's lines 374-378. */
static inline void updateParticleVectors(int no)
{
    char *g;
    char *d;
    char *s;
    int i;

    g = (char *)D_00720220[no].geo;
    d = *(char **)(*(char **)(g + 0x28) + 0x190);
    s = *(char **)(g + 0x24);
    for (i = 0; i < *(int *)(g + 0x30); i++) {
        setParticleVector(d, s);
        s += 0x70;
        d += 0x20;
    }
}

void ExecParticleEffect(int no)
{
    int (*proc)(void *);

    if (D_00720220[no].used == 0) {
        return;
    }
    if (D_00720220[no].pause != 0) {
        return;
    }
    if (D_00720220[no].geoCtrl != 0) {
        if (D_00720220[no].sensing != 0) {
            SetParticleEffectGeometry(no, (int)D_00720220[no].sensPos,
                                      (int)D_00720220[no].sensQuat);
        }
        if (execParticleEffect(D_00720220[no].geo) == 0) {
            deleteParticleEffectGeo(no);
            D_00720220[no].used = 0;
        }
    } else {
        updateParticleVectors(no);
        proc = *(int (**)(void *))((char *)D_00720220[no].geo + 0x64);
        if (proc != 0) {
            if (proc(D_00720220[no].geo) == 0) {
                deleteParticleEffectGeo(no);
                D_00720220[no].used = 0;
            }
        }
    }
}

extern int D_0063A450;
extern char D_00620908[];
extern int iosMallocDebugNoAssert(int heap, int size, char *file, int line);
extern int setParticleEffect(int geo, int *pkg, int part);

void ResetParticleEffectPackages(int *pkg)
{
    PEVector pos;
    PEQuaternion quat;
    int part;
    int i;

    part = D_0063A450;
    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0 && *(int **)((char *)D_00720220[i].geo + 0x20) == pkg) {
            CopyVector(&pos, D_00720220[i].geo);
            CopyQuaternion(&quat, (char *)D_00720220[i].geo + 0x10);
            deleteParticleEffectGeo(i);
            D_00720220[i].geo = (PEGeo *)iosMallocDebugNoAssert(part, 0x80, D_00620908, 663);
            D_00720220[i].used = 1;
            setParticleEffectGeometry((int)D_00720220[i].geo, (int)&pos, (int)&quat);
            setParticleEffect((int)D_00720220[i].geo, pkg, part);
        }
    }
}

extern PE160 D_004ECDF0;
extern char D_00620980[];
extern int D_00721020[];
extern void debug_StdPrintfDummy();
extern void memcpy(void *dst, int *a1, int a2);

void SetParticleEffectPackage(int a0, int *a1, int a2)
{
    *(PE160 *)((unsigned char *)D_00721020 + a0 * 0xA0) = D_004ECDF0;
    if (*(int *)&D_004ECDF0 != *a1) {
        debug_StdPrintfDummy(D_00620980, *a1);
    }
    memcpy(((unsigned char *)D_00721020 + a0 * 0xA0), a1, a2);
}

extern PEffect D_004ECDD0;

void InitParticleEffects(void)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        D_00720220[i] = D_004ECDD0;
    }
}

void ExecParticleEffects(void)
{
    int i;
    for (i = 0; i < 0x80; i++) {
        ExecParticleEffect(i);
    }
}

extern void dispParticleEffect(PEGeo *geo);

void DispParticleEffects(void)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0) {
            dispParticleEffect(D_00720220[i].geo);
        }
    }
}

void DeleteParticleEffect(int no)
{
    if (D_00720220[no].used != 0 || D_00720220[no].geo != 0) {
        deleteParticleEffectGeo(no);
        D_00720220[no].used = 0;
    }
}

void SetParticleEffectPauseFlag(int a0, int a1)
{
    D_00720220[a0].pause = a1;
}

extern int D_0063A450;
extern int SetParticleEffectByPartition(int no, PEVector *pos, PEQuaternion *quat, int part);

int SetParticleEffect(int no, PEVector *pos, PEQuaternion *quat)
{
    return SetParticleEffectByPartition(no, pos, quat, D_0063A450);
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * SetParticleEffect's line 532 into SetParticleEffectActiveSensing, so it is a
 * public `inline` of the deferred tail; until the tail's asm members are C its
 * out-of-line copy stays the plain definition above and this caller inlines the
 * static stand-in SetParticleEffect_inl, which collapses at layout. */
static inline int SetParticleEffect_inl(int no, PEVector *pos, PEQuaternion *quat)
{
    return SetParticleEffectByPartition(no, pos, quat, D_0063A450);
}

int SetParticleEffectActiveSensing(int no, PEVector *pos, PEQuaternion *quat)
{
    int id;

    id = SetParticleEffect_inl(no, pos, quat);
    if (id != -1) {
        D_00720220[id].sensing = 1;
        D_00720220[id].sensPos = pos;
        D_00720220[id].sensQuat = quat;
    }
    return id;
}

int *GetParticleEffectPackage(int idx)
{
    return (int *)((char *)D_00721020 + idx * 0xA0);
}

void DeleteParticleEffectsByPackage(int *pkg)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0 && *(int **)((char *)D_00720220[i].geo + 0x20) == pkg) {
            deleteParticleEffectGeo(i);
            D_00720220[i].used = 0;
        }
    }
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * GetParticleEffectPackage's line 118 and DeleteParticleEffectsByPackage's
 * lines 673-676 into DeleteParticleEffectsByID, so both are public `inline`s of
 * the deferred tail; until the tail's asm members are C their out-of-line copies
 * stay the plain definitions above and this caller inlines the static stand-ins,
 * which collapse at layout. */
static inline int *GetParticleEffectPackage_inl(int idx)
{
    return (int *)((char *)D_00721020 + idx * 0xA0);
}

static inline void DeleteParticleEffectsByPackage_inl(int *pkg)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0 && *(int **)((char *)D_00720220[i].geo + 0x20) == pkg) {
            deleteParticleEffectGeo(i);
            D_00720220[i].used = 0;
        }
    }
}

void DeleteParticleEffectsByID(int id)
{
    DeleteParticleEffectsByPackage_inl(GetParticleEffectPackage_inl(id));
}

int GetParticleEffectData(int a0)
{
    return (int)D_00720220[a0].geo;
}

void DisableParticleEffectGeometryControl(int a0)
{
    D_00720220[a0].geoCtrl = 0;
}

extern char D_0062A278[];

int GetParticleIDWithName(char *name)
{
    int i;
    for (i = 0; i < 0x3D; i++) {
        if (strcmp(D_0062A278 + i * 0x50, name) == 0) {
            return i;
        }
    }
    return -1;
}

int GetParticleLoopFlag(int a0)
{
    int *p;
    if (a0 < 0) {
        return -1;
    }
    p = (int *)((char *)D_00721020 + a0 * 0xA0);
    return p[1] == 1;
}

extern void sceVu0CopyVector(void *dst, void *src);

void ParticleEffects_SetAllGoal(void *goal)
{
    int i;

    for (i = 0; i < 0x80; i++) {
        if (D_00720220[i].used != 0) {
            char *v = (char *)D_00720220[i].geo;
            if (v != 0) {
                sceVu0CopyVector(v + 0x50, goal);
            }
        }
    }
}

void SetParticleEffectClipEnableFlag(int a0, int a1)
{
    if (a0 >= 0) {
        *(int *)((char *)D_00720220[a0].geo + 0x34) = a1;
    }
}

void SetParticleEffectDrainLevel(int a0, float f)
{
    if (a0 >= 0) {
        *(float *)((char *)D_00720220[a0].geo + 0x40) = f;
    }
}
