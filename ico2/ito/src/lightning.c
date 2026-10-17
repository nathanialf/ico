#include "typedef.h"
#include <stdlib.h>
#include <libvu0.h>
#include "sugiCommon.h"
#include "itou_common.h"
#include "GifPacket.h"
#include "Texture.h"
#include "Matrix.h"
#include "tableSin.h"
#include "main.h"
#include "itou_sub.h"
#include "lightning.h"
#include "DisplayList.h"
#include "DmaPacket.h"
#include "include_asm.h"

/* the four control points lightning_test draws through */
typedef struct { /* field names derived */
    LightningVtx v[4];
} LightningPath; /* derived name */

typedef float LightningMtx[4][4] __attribute__((aligned(16)));

/* one strip vertex as the three GS register payloads it is sent as */
typedef struct { /* field names derived */
    unsigned long long rgbaq;
    unsigned long long uv;
    unsigned long long xyz;
} LightningGsVtx; /* derived name */

/* the strip's last two vertices, resent when a clipped strip reopens */
static LightningGsVtx lastVtx[2]; /* derived name */

/* nonzero while the open strip is being written */
static int stripOn; /* derived name */

typedef struct {
    unsigned long long NLOOP : 15;
    unsigned long long EOP : 1;
    unsigned long long pad16 : 16;
    unsigned long long id : 14;
    unsigned long long PRE : 1;
    unsigned long long PRIM : 11;
    unsigned long long FLG : 2;
    unsigned long long NREG : 4;
    unsigned long long REGS0 : 4;
    unsigned long long REGS1 : 60;
} sceGifTag;

/* the GIFtag that opened the current strip, whose NLOOP close_strip fills */
static char *stripTag; /* derived name */

/* vertices set since the draw began */
static int vtxCount; /* derived name */

/* the GS RGBAQ register carries Q as the raw float word in bits 63..32 */
static __inline__ int fbits(float f) /* derived name */
{
    return *(int *)&f;
}

/* VU0's clipping flags for one w-homogeneous point */
static __inline__ int clip_flags(LightningVtx *p) /* derived name */
{
    int flags;

    __asm__ __volatile__(".set noreorder\n\t"
                         "lqc2 $vf1, 0(%1)\n\t"
                         "vclipw.xyzw $vf1, $vf1w\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "cfc2.ni %0, $vi18\n\t"
                         ".set reorder"
                         : "=r"(flags)
                         : "r"(p)
                         : "memory");
    return flags;
}

/* pad the open strip to a whole triangle count and write its vertex count
 * back into the GIFtag that opened it */
static __inline__ void close_strip(void) /* derived name */
{
    int n;
    unsigned long long *e;

    if (stripTag != 0) {
        e = PacketBufferStruct.ptr.d - 2;
        n = e - (unsigned long long *)stripTag;
        if (n & 1) {
            *PacketBufferStruct.ptr.d++ = 0;
        }
        ((sceGifTag *)stripTag)->NLOOP = n / 3;
    }
}

static void set_vertex(LightningVtx *dir, LightningVtx *pos, float u, int *col, float half)
{
    VECTOR uv[2] = {{0.0f, u, 1.0f, 0.0f}, {1.0f, u, 1.0f, 0.0f}};
    LightningVtx v;
    LightningVtx e[2];
    LightningVtx n;
    LightningVtx pt;
    LightningVtx t;
    LightningVtx xyz;
    LightningVtx clip;
    float q;
    int i;
    int restrip = 1; /* local debug switch, see the reopen below */

    apply_matrix_w1(&v, matrixptr + 0x80, pos);
    sceVu0OuterProduct(&n, &v, dir);
    n.f[2] = 0.0f;
    sceVu0Normalize(&n, &n);
    sceVu0ScaleVectorXYZ(&n, &n, half);
    sceVu0SubVector(&e[0], &v, &n);
    sceVu0AddVector(&e[1], &v, &n);

    for (i = 0; i < 2; i++) {
        apply_matrix_w1(&pt, matrixptr + 0xC0, &e[i]);
        q = 1.0f / pt.f[3];
        sceVu0ScaleVectorXYZ(&pt, &pt, q);
        sceVu0ScaleVectorXYZ(&t, &uv[i], q);
        sceVu0FTOI4Vector(&xyz, &pt);
        apply_matrix_w1(&clip, matrixptr + 0x1C0, &e[i]);
        if (clip_flags(&clip) & 0x3FFFF) {
            stripOn = 0;
        } else if (stripOn == 0 && vtxCount >= 2) {
            close_strip();
            /* The strip-state reset DrawLightning2 opens with, then the
               reopened strip unless restrip was cleared from the debugger
               (the strip then stays closed: close_strip() finds no tag and
               nothing more is written).  The code never clears restrip. */
            stripOn = 0;
            stripTag = 0;
            if (restrip) {
                *PacketBufferStruct.ptr.d++ = 0x1400000000008001LL;
                *PacketBufferStruct.ptr.d++ = 0;
                *PacketBufferStruct.ptr.d++ = 84;

                *PacketBufferStruct.ptr.d++ = 0;

                stripTag = PacketBufferStruct.ptr.c;
                *PacketBufferStruct.ptr.d++ = 0x3400000000008000LL;
                *PacketBufferStruct.ptr.d++ = 1313;

                *PacketBufferStruct.ptr.d++ = lastVtx[0].rgbaq;
                *PacketBufferStruct.ptr.d++ = lastVtx[0].uv;
                *PacketBufferStruct.ptr.d++ = lastVtx[0].xyz;
                *PacketBufferStruct.ptr.d++ = lastVtx[1].rgbaq;
                *PacketBufferStruct.ptr.d++ = lastVtx[1].uv;
                *PacketBufferStruct.ptr.d++ = lastVtx[1].xyz;

                stripOn = 1;
            }
        }

        lastVtx[0] = lastVtx[1];
        lastVtx[1].rgbaq = ((long long)col[0] | ((long long)col[1] << 8) |
                            ((long long)col[2] << 16) | ((long long)col[3] << 24)) |
                           ((long long)fbits(q) << 32);
        lastVtx[1].uv = (long long)t.i[0] | ((long long)t.i[1] << 32);
        lastVtx[1].xyz =
            (long long)xyz.i[0] | ((long long)xyz.i[1] << 16) | ((long long)xyz.i[2] << 32);

        if (stripOn) {
            *PacketBufferStruct.ptr.d++ = lastVtx[1].rgbaq;
            *PacketBufferStruct.ptr.d++ = lastVtx[1].uv;
            *PacketBufferStruct.ptr.d++ = lastVtx[1].xyz;
        }
        vtxCount++;
    }
}

/* out = the 3x4 part of m applied to in */
/* a random value between lo and hi */
static __inline__ float random_range(float lo, float hi) /* derived name */
{
    return _GetRandom() * (hi - lo) + lo;
}

/* x with a random sign */
static __inline__ float random_sign(float x) /* derived name */
{
    if (_GetRandom() <= 0.5f) {
        x = -x;
    }
    return x;
}

/* the Catmull-Rom basis, halved, that turns four control points into the
   segment's cubic coefficients */
static LightningMtx catmullRom = {
    /* derived name */
    {-0.5f, 1.5f, -1.5f, 0.5f},
    {1.0f, -2.5f, 2.0f, -0.5f},
    {-0.5f, 0.0f, 0.5f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
};

void DrawLightning2(int num, LightningVtx *v, LightningColor *col, float stepMin, float stepMax,
                    float swayStepMin, float swayStepMax, float turnMin, float turnMax,
                    float swayLimit, float width, float texLen, float seed, int c);

INCLUDE_ASM(DrawLightning2);

static inline int cmpr(LightningNode *self, LightningNode *other);

void DrawLightningN(int num, LightningNode *v, void *col, float stepMin, float stepMax,
                    float swayStepMin, float swayStepMax, float turnMin, float turnMax,
                    float swayLimit, float width, float texLen, float seed, int c)
{
    LightningVtx buf[num];
    int i;

    if (num >= 3) {
        qsort(&v[1], num - 1, sizeof(LightningNode), cmpr);
    }
    for (i = 0; i < num; i++) {
        sceVu0CopyVector(&buf[i], &v[i]);
    }
    DrawLightning2(num, buf, col, stepMin, stepMax, swayStepMin, swayStepMax, turnMin, turnMax,
                   swayLimit, width, texLen, seed, c);
}

static inline int cmpr(LightningNode *self, LightningNode *other)
{
    return self->key - other->key;
}

INCLUDE_ASM(apply_m34);

INCLUDE_ASM(DrawLightning);

INCLUDE_ASM(lightning_test);
