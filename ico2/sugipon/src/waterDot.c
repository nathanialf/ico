#include "common.h"
#include "typedef.h"
#include "sugiCommon.h"
#include "memory.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "waterDot.h"

/* One dot of the splash: 0x30 bytes, sized by AllocWaterDot's `mult ,0x30`. */
/* 0x30 */

/* The per-emitter work AllocWaterDot mallocs (0x1C bytes) and registers in
 * D_00724BC0[D_0063BC48++]. */
/* 0x1C */

extern WaterDotWork *D_00724BC0[]; /* the registered emitters */
extern int D_0063BC48;             /* how many are registered */
/* kept local: this TU's uses of _AddVectorXYZ do not fit the prototype in Matrix.h */
extern void _AddVectorXYZ(VECTOR *dst, VECTOR *a, VECTOR *b);
extern void setWaterDot(WaterDot *dot, VECTOR *pos, VECTOR *vel);

inline void InitializeWaterDot(void)
{
    int i;

    D_0063BC48 = 0;
    for (i = 4; i >= 0; i--) {
        D_00724BC0[i] = 0;
    }
}

extern void *D_0063A438; /* the heap partition every waterDot record comes from */

/* The three .data templates AllocWaterDot block-copies, in ROM order at
   0x4ED170, 0x4ED190 and 0x4ED1C0. Each is an explicit initialiser, which is
   why the all-zero first one sits in .data rather than .bss. */
static WaterDotWork initWaterDotWork = {0, 0, 0, 0, 0, 0, 0};

static WaterDot initWaterDot = {
    0, 0, 128, 1.0f, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}};

static WaterDot initWaterDot2 = {0, 0, 0, 0.0f, {0.0f, 0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f, 0.0f}};

/* waterDot.c:27-47 in the PAL listing. The line numbers the three
   iosMallocDebug calls carry ARE their source lines, 29, 33 and 38. */
WaterDotWork *AllocWaterDot(int gobj, int num, int num2)
{
    WaterDotWork *w;
    int i;

    w = iosMallocDebug(D_0063A438, sizeof(WaterDotWork), "src/waterDot.c", 29);
    *w = initWaterDotWork;

    w->num = num;
    w->dot = iosMallocDebug(D_0063A438, num * sizeof(WaterDot), "src/waterDot.c", 33);
    for (i = 0; i < num; i++)
        w->dot[i] = initWaterDot;

    w->num2 = num2;
    w->dot2 = iosMallocDebug(D_0063A438, num2 * sizeof(WaterDot), "src/waterDot.c", 38);
    for (i = 0; i < num2; i++)
        w->dot2[i] = initWaterDot2;

    w->gobj = gobj;

    D_00724BC0[D_0063BC48] = w;
    D_0063BC48++;

    return w;
}

void setWaterDot(WaterDot *dot, VECTOR *pos, VECTOR *vel)
{
    int n;

    dot->used = 1;
    dot->frame = 0;
    n = (int)(crt_random_unit() * 64.0f + 32.0f);
    dot->life = n;
    dot->scale = 1.0 - (256 - n) * 0.00078125;
    CopyVector(&dot->pos, pos);
    CopyVector(&dot->vel, vel);
}

inline void EntryWaterDot(WaterDotWork *w, VECTOR *pos, VECTOR *vel, float range)
{
    VECTOR v = {random_signed_b() * range, random_signed_b() * range, random_signed_b() * range,
                1.0f};

    _AddVectorXYZ(&v, &v, pos);
    setWaterDot(&w->dot[w->cur], &v, vel);
    if (++w->cur == w->num)
        w->cur = 0;
}

extern int D_0028F4C0[];
/* kept local: this TU's uses of GetWindVector do not fit the prototype in windField.h */
extern void *GetWindVector(int a0, void *pos);
/* kept local: this TU's uses of _ScaleVectorXYZ do not fit the prototype in Matrix.h */
extern void _ScaleVectorXYZ(void *dst, void *src, float k);

/* waterDot.c:71-78 in the PAL listing, rows inside ExecWaterDot's span but
   above its def line: a static helper with no out-of-line copy, inlined at
   its one call site. It ages one dot and reports whether it has expired. */
static inline int stepWaterDot(WaterDot *p)
{
    if (p->frame++ < 30) {
        /* The gravity step is the frame-rate quotient written out TWICE rather
           than held in a local, the same spelling src/clothAnimation.c uses for
           the identical term. cse collapses the second copy, but expanding it
           moves the p->scale argument load one issue slot later, which is the
           ROM's order. */
        p->vel.y += 60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 0.5f *
                    (60.0f / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]));
        _ScaleVectorXYZ(&p->vel, &p->vel, p->scale);
        _AddVectorXYZ(&p->pos, &p->pos, &p->vel);

        return 0;
    }
    return 1;
}

void ExecWaterDot(WaterDotWork *w)
{
    VECTOR wind;
    VECTOR pos;
    WaterDot *p;
    WaterDot *q;
    int i;

    GetRootPosition(&pos, w->gobj);
    _ScaleVectorXYZ(&wind, GetWindVector(0, &pos), 0.2f);

    p = w->dot;
    for (i = 0; i < w->num; i++) {
        if (p->used != 0) {
            if (stepWaterDot(p) != 0) {
                p->used = 0;
            }
        }
        p++;
    }

    q = w->dot2;
    for (i = 0; i < w->num2; i++) {
        if (q->used != 0) {
            q->used = 0;
        }
        q++;
    }
}

extern int matrixptr;
extern int D_0063BC4C; /* the PRIM register value the splash packet draws with */
/* kept local: this TU's uses of gif_StartPacketPri do not fit the prototype in GifPacket.h */
extern void gif_StartPacketPri(int a0);
/* kept local: this TU's uses of gif_SetGsReg do not fit the prototype in GifPacket.h */
extern void gif_SetGsReg(long long a0, long long a1);
/* kept local: this TU's uses of gif_SetZTest do not fit the prototype in GifPacket.h */
extern void gif_SetZTest(int a0);
/* kept local: this TU's uses of gif_SetZWrite do not fit the prototype in GifPacket.h */
extern void gif_SetZWrite(int a0);
/* kept local: this TU's uses of gif_SetAlpha do not fit the prototype in GifPacket.h */
extern void gif_SetAlpha(int a0, int a1, int a2);
/* kept local: this TU's uses of gif_EndPacket do not fit the prototype in GifPacket.h */
extern void gif_EndPacket(void);
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(void *dst, int m, void *src);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *dst, void *src, float k);
/* kept local: this TU's uses of _FTOI4Vector do not fit the prototype in Matrix.h */
extern void _FTOI4Vector(void *dst, void *src);

/* waterDot.c:121-126 in the PAL listing, rows inside DispWaterDot's span but
   above its def line: a static helper with no out-of-line copy, inlined at its
   one call site. It projects one dot into GS fixed-point screen space. */
static inline void getWaterDotScreenPos(int *out, VECTOR *pos)
{
    VECTOR v;
    float q;

    _ApplyMatrix(&v, matrixptr + 0x100, pos);
    q = v.w;
    _ScaleVector(&v, &v, 1.0f / q);
    _FTOI4Vector(out, &v);
}

void DispWaterDot(WaterDotWork *w)
{
    int ip[4];
    WaterDot *p;
    int i;

    gif_StartPacketPri(0xB);

    p = w->dot;
    gif_SetGsReg(0, D_0063BC4C);
    gif_SetZTest(1);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 5, 0x80);

    for (i = 0; i < w->num; i++, p++) {
        if (p->used != 0) {
            getWaterDotScreenPos(ip, &p->pos);

            if (ip[0] >= 0x6700 && ip[0] <= 0x9900) {
                if (ip[1] >= 0x7380 && ip[1] <= 0x8C80) {
                    gif_SetGsReg(1, 0x80LL | (0x80LL << 8) | (0x80LL << 16) |
                                        ((long long)p->life << 24) | (0x3F800000LL << 32));
                    gif_SetGsReg(5, (long long)ip[0] | ((long long)ip[1] << 16) |
                                        ((long long)ip[2] << 32));
                }
            }
        }
    }

    gif_EndPacket();

    for (i = 0; i < w->num2; i++) {}
}
