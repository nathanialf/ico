#include "common.h"
#include "typedef.h"
#include <stdlib.h>
#include <libvu0.h>
#include "sugiCommon.h"
#include "itou_common.h"

typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} StructB;

typedef union {
    float f[4];
    int i[4];
    unsigned long long w[2];
} LightningVtx;

typedef struct {
    LightningVtx v[4];
} StructC;

typedef float LightningMtx[4][4] __attribute__((aligned(16)));

/* one entry of the caller's node array: a 16-byte position and the sort key
   `cmpr` compares at +0x10 */
typedef struct {
    LightningVtx v; /* 0x00 */
    int key;        /* 0x10 */
    int unk14;      /* 0x14 */
    int unk18;      /* 0x18 */
    int unk1C;      /* 0x1C */
} LightningNode;

/* prototypes: their order is the inline tail's emission order */
void apply_m34(void *out, void *m, void *in);

void DrawLightning(void *p0, void *p1, void *a2, float f0, float f1, float f2, float f3, float f4,
                   float f5, float f6, float f7, float f8, float f9, int a3);

void lightning_test(void);
inline int cmpr(int *self, int *other);
/* kept local: the declaration in lightning.h changes this TU codegen */
extern void DrawLightning2(int n, LightningVtx *a, StructB *b, float f0, float f1, float f2,
                           float f3, float f4, float f5, float f6, float f7, float f8, float f9,
                           int c);

/* the display-list packet cursor record, with the write cursor seen as a
 * union of the pointer widths the packet code writes through */
typedef struct {
    int cur;
    int *buf[2];
    char *dma;

    union {
        unsigned long long *d;
        char *c;
    } ptr;

    char *tail;
    char *gif;
    char *end;
} LightningDpk;

extern LightningDpk D_004EE6F0;

/* one strip vertex as the three GS register payloads it is sent as */
typedef struct {
    unsigned long long rgbaq;
    unsigned long long uv;
    unsigned long long xyz;
} LightningGsVtx;

extern LightningGsVtx D_006EA7C0[2];
extern int D_0063C2F4;

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

extern char *D_0063C2F8;
extern int D_0063C2FC;
extern char *matrixptr;
extern void apply_matrix_w1(void *dst, void *m, void *src);
extern void sceVu0FTOI4Vector(void *dst, void *src);

/* the GS RGBAQ register carries Q as the raw float word in bits 63..32 */
static __inline__ int fbits(float f)
{
    return *(int *)&f;
}

/* VU0's clipping flags for one w-homogeneous point */
static __inline__ int clip_flags(LightningVtx *p)
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
static __inline__ void close_strip(void)
{
    int n;
    unsigned long long *e;

    if (D_0063C2F8 != 0) {
        e = D_004EE6F0.ptr.d - 2;
        n = e - (unsigned long long *)D_0063C2F8;
        if (n & 1) {
            *D_004EE6F0.ptr.d++ = 0;
        }
        ((sceGifTag *)D_0063C2F8)->NLOOP = n / 3;
    }
}

void set_vertex(LightningVtx *dir, LightningVtx *pos, float u, int *col, float half)
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
    int i = 0; /* dead initialiser: see the note after close_strip() below */

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
            D_0063C2F4 = 0;
        } else if (D_0063C2F4 == 0 && D_0063C2FC >= 2) {
            close_strip();
            /* The strip-state reset DrawLightning2 opens with, left dead here:
               close_strip() has already used the tag pointer and this block
               reopens the strip at the two stores below, so flow deletes both
               and they emit no bytes (with the `i = 0` initialiser above).
               What the bytes pin: 248 to 259 real insns at gcse entry, which
               gives a 125 to 129 bucket expression table and orders the PRE
               reaching registers of &t and &xyz into the ROM's spill slots
               0xA0 and 0xA4; at 245 insns the two slots swap. What they cannot
               pin: the text, the number or the lines of the dead statements
               (SRCFILE.TXT line 168 is code-free, as any deleted one is). */
            D_0063C2F4 = 0;
            D_0063C2F8 = 0;
            *D_004EE6F0.ptr.d++ = 0x1400000000008001LL;
            *D_004EE6F0.ptr.d++ = 0;
            *D_004EE6F0.ptr.d++ = 84;

            *D_004EE6F0.ptr.d++ = 0;

            D_0063C2F8 = D_004EE6F0.ptr.c;
            *D_004EE6F0.ptr.d++ = 0x3400000000008000LL;
            *D_004EE6F0.ptr.d++ = 1313;

            *D_004EE6F0.ptr.d++ = D_006EA7C0[0].rgbaq;
            *D_004EE6F0.ptr.d++ = D_006EA7C0[0].uv;
            *D_004EE6F0.ptr.d++ = D_006EA7C0[0].xyz;
            *D_004EE6F0.ptr.d++ = D_006EA7C0[1].rgbaq;
            *D_004EE6F0.ptr.d++ = D_006EA7C0[1].uv;
            *D_004EE6F0.ptr.d++ = D_006EA7C0[1].xyz;

            D_0063C2F4 = 1;
        }

        D_006EA7C0[0] = D_006EA7C0[1];
        D_006EA7C0[1].rgbaq = ((long long)col[0] | ((long long)col[1] << 8) |
                               ((long long)col[2] << 16) | ((long long)col[3] << 24)) |
                              ((long long)fbits(q) << 32);
        D_006EA7C0[1].uv = (long long)t.i[0] | ((long long)t.i[1] << 32);
        D_006EA7C0[1].xyz =
            (long long)xyz.i[0] | ((long long)xyz.i[1] << 16) | ((long long)xyz.i[2] << 32);

        if (D_0063C2F4) {
            *D_004EE6F0.ptr.d++ = D_006EA7C0[1].rgbaq;
            *D_004EE6F0.ptr.d++ = D_006EA7C0[1].uv;
            *D_004EE6F0.ptr.d++ = D_006EA7C0[1].xyz;
        }
        D_0063C2FC++;
    }
}

/* out = the 3x4 part of m applied to in */
inline void apply_m34(void *out, void *m, void *in)
{
    __asm__ __volatile__(".set noreorder\n\t"
                         "lqc2 $vf8, 0x0(%2)\n\t"
                         "lqc2 $vf4, 0x0(%1)\n\t"
                         "lqc2 $vf5, 0x10(%1)\n\t"
                         "lqc2 $vf6, 0x20(%1)\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                         "vmaddz.xyzw $vf12, $vf6, $vf8z\n\t"
                         "sqc2 $vf12, 0x0(%0)\n\t"
                         ".set reorder"
                         :
                         : "r"(out), "r"(m), "r"(in)
                         : "memory");
}

/* a random value between lo and hi */
static __inline__ float random_range(float lo, float hi)
{
    return _GetRandom() * (hi - lo) + lo;
}

/* x with a random sign */
static __inline__ float random_sign(float x)
{
    if (_GetRandom() <= 0.5f) {
        x = -x;
    }
    return x;
}

/* kept local: the TU's callees, spelled the way this function calls them */
extern int tex_GetTextureNo(char *name);
extern int tex_TransTexture(int no, int pri);
extern void gif_StartPacketPri(int pri);
extern unsigned int dpk_CheckBufferSize(void);
extern void gif_SetAlpha(long long a0, long long a1, long long a2);
extern void gif_SetGsReg(long long a0, long long a1);
extern void gif_EndPacket(void);
extern void dl_SetDLPriority(int pri);
extern int dl_GetPri(void);
extern void dl_OpenDma(int chan, void *dma, int flag);
extern void dl_CloseDma(void);
extern float _GetLength(void *a, void *b);
extern float _GetNorm(void *v);
extern float GetTableSin(short a);
extern float GetTableCos(short a);
extern void set_vertex(LightningVtx *dir, LightningVtx *pos, float u, int *col, float half);
extern LightningVtx D_002A6070[4];

void DrawLightning2(int num, LightningVtx *v, StructB *col, float f0, float f1, float f2, float f3,
                    float f4, float f5, float f6, float f7, float f8, float f9, int c)
{
    LightningMtx m[num - 1];
    float half = 0.5f;
    float wa = f7 * half;
    float wb = f7 - wa;
    float one = 1.0f;
    float two = 2.0f;
    LightningVtx ccol;
    LightningVtx a;
    LightningVtx b;
    LightningVtx dir;
    LightningVtx cur;
    LightningVtx prev;
    LightningVtx t;
    LightningVtx q;
    LightningVtx dv;
    LightningVtx tmp;
    LightningVtx basis;
    LightningVtx pos;
    LightningVtx sa;
    LightningVtx sb;
    LightningVtx delta;
    LightningVtx nrm;
    LightningVtx avg;
    LightningVtx out;
    LightningVtx ccol2;
    LightningVtx icol;
    float s;
    float f;
    float u;
    float nu;
    float sc;
    float lim;
    float last;
    float sway;
    float d;
    float ang;
    float amp;
    float wd;
    float ui;
    float ni;
    int no;
    int n;
    int i;
    int seg;
    int first;
    int done;
    char *pk;
    char *p;
    unsigned long long *top;

    no = tex_GetTextureNo("lightning_test");
    if (no >= 0) {
        tex_TransTexture(no, 6);
    }
    if (num < 2) {
        return;
    }
    gif_StartPacketPri(6);
    if (dpk_CheckBufferSize() >= 64) {
        gif_SetAlpha(1, c, 128);
        gif_SetGsReg(78, 0x1300000C0LL);
        gif_SetGsReg(8, 1);
        gif_SetGsReg(0, 84);
    }
    gif_EndPacket();
    dl_SetDLPriority(6);
    pk = D_004EE6F0.ptr.c;
    top = (unsigned long long *)(pk + 16);
    D_004EE6F0.gif = 0;
    D_004EE6F0.dma = pk;
    D_004EE6F0.ptr.c = pk + 8;
    D_004EE6F0.end = 0;
    D_004EE6F0.tail = pk;
    ((GifPkWord *)(pk + 8))->w[0] = 0x11000000;
    D_004EE6F0.gif = pk + 12;
    D_004EE6F0.ptr.d = top;
    D_0063C2F4 = 0;
    D_0063C2F8 = 0;
    D_0063C2FC = 0;
    if (f9 != 0.0f) {
        f9 = __builtin_fabsf(f9);
        f9 = f9 - (int)f9 + one;
        if (f9 == one) {
            f9 = 1.5f;
        }
        __asm__ __volatile__("ctc2.ni %0, $vi20\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop"
                             :
                             : "r"(f9));
    }
    if (f0 < 15.0f) {
        f0 = 15.0f;
    }
    sceVu0SubVector(&dir, &v[1], &v[0]);
    sceVu0Normalize(&dir, &dir);
    a.f[0] = random_unit();
    a.f[1] = random_unit();
    a.f[2] = random_unit();
    a.f[3] = 1.0f;
    sceVu0OuterProduct(&b, &dir, &a);
    sceVu0Normalize(&b, &b);
    sceVu0OuterProduct(&a, &b, &dir);
    {
        int np = num + 2;
        LightningVtx w[np + 2];

        sceVu0SubVector(&t, &v[0], &v[1]);
        sceVu0AddVector(&w[0], &v[0], &t);
        for (i = 0; i < num; i++) {
            sceVu0CopyVector(&w[i + 1], &v[i]);
        }
        sceVu0SubVector(&t, &v[num - 1], &v[num - 2]);
        sceVu0AddVector(&w[num + 1], &v[num - 1], &t);
        for (i = 0; i < np - 3; i++) {
            sceVu0MulMatrix(m[i], &w[i], D_002A6070);
        }
    }
    sceVu0CopyVector(&cur, &v[0]);
    sceVu0ITOF0Vector(&ccol, col);
    last = (float)(num - 1);
    u = 0.0f;
    s = u;
    done = 0;
    first = 1;
    sway = 0.0f;
    ang = random_range(0.0f, 6.2831855f);
    for (;;) {
        seg = (int)s;
        f = s - (float)seg;
        if (dpk_CheckBufferSize() < 64) {
            goto end;
        }
        tmp.f[0] = 3.0f * f * f;
        tmp.f[1] = 2.0f * f;
        tmp.f[2] = 1.0f;
        tmp.f[3] = 0.0f;
        dv = tmp;
        sceVu0ApplyMatrix(&dir, m[seg], &dv);
        sceVu0Normalize(&dir, &dir);
        sceVu0ScaleVectorXYZ(&tmp, &a, sceVu0InnerProduct(&dir, &a));
        sceVu0SubVector(&a, &a, &tmp);
        sceVu0Normalize(&a, &a);
        sceVu0OuterProduct(&b, &dir, &a);
        s += random_range(f0, f1) / _GetLength(&v[seg + 1], &v[seg]);
        seg = (int)s;
        f = s - (float)seg;
        lim = (float)(num - 1) - half;
        if (s < half) {
            sc = GetTableSin((short)(s * two * 1.5707964f * 10430.378f));
        } else if (lim <= s) {
            sc = GetTableSin((short)((1.0f - (s - lim) * two) * 1.5707964f * 10430.378f));
        } else {
            sc = 1.0f;
        }
        if (last <= s) {
            sceVu0CopyVector(&q, &v[num - 1]);
            done = 1;
        } else {
            basis = (LightningVtx){{f * f * f, f * f, f, 1.0f}};
            sceVu0ApplyMatrix(&pos, m[seg], &basis);
            d = random_sign(random_range(f2, f3));
            if (__builtin_fabsf(sway + d) > f6) {
                d = -d;
            }
            sway += d;
            amp = sway * sc;
            ang += random_sign(random_range(degrees_to_radians(f4), degrees_to_radians(f5)));
            sceVu0ScaleVectorXYZ(&sa, &a, GetTableCos((short)(ang * 10430.378f)) * amp);
            sceVu0ScaleVectorXYZ(&sb, &b, GetTableSin((short)(ang * 10430.378f)) * amp);
            sceVu0AddVector(&q, &pos, &sa);
            sceVu0AddVector(&q, &q, &sb);
        }
        sceVu0SubVector(&delta, &q, &cur);
        sceVu0Normalize(&nrm, &delta);
        if (first) {
            sceVu0CopyVector(&prev, &nrm);
        }
        sceVu0AddVector(&avg, &nrm, &prev);
        sceVu0ScaleVectorXYZ(&avg, &avg, 0.5f);
        sceVu0CopyVector(&prev, &nrm);
        apply_m34(&out, matrixptr + 0x80, &avg);
        sceVu0ScaleVectorXYZ(&ccol2, &ccol, sc * (1.0f - half) + half);
        sceVu0FTOI0Vector(&icol, &ccol2);
        wd = (sc * wb + wa) * (1.0f - _GetRandom() * half);
        set_vertex(&out, &cur, u, icol.i, wd);
        nu = u + _GetNorm(&delta) / f8;
        if (2048.0f <= nu * 32.0f) {
            ui = (int)u;
            ni = (int)nu;
            set_vertex(&out, &cur, u - ui, icol.i, wd);
            nu -= ni;
        }
        u = nu;
        if (done) {
            set_vertex(&out, &q, u, icol.i, 0.0f);
            break;
        }
        sceVu0CopyVector(&cur, &q);
        first = 0;
    }
end:
    close_strip();
    n = D_004EE6F0.ptr.d - top;
    if (n & 1) {
        *D_004EE6F0.ptr.d++ = 0;
    }
    ((GifPkWord *)D_004EE6F0.tail)->d =
        (unsigned int)((((unsigned int)(D_004EE6F0.ptr.c - D_004EE6F0.tail) >> 4) - 1) |
                       0x10000000);
    ((GifPkWord *)D_004EE6F0.gif)->w[0] =
        ((unsigned int)(D_004EE6F0.ptr.c - D_004EE6F0.gif) >> 4) | 0x50000000;
    p = D_004EE6F0.ptr.c;
    D_004EE6F0.tail = p;
    ((GifPkWord *)p)->d = 0x60000000;
    D_004EE6F0.ptr.c = p + 8;
    ((GifPkWord *)(p + 8))->w[0] = 0;
    D_004EE6F0.ptr.c = p + 0xC;
    ((GifPkWord *)(p + 8))->w[1] = 0;
    D_004EE6F0.ptr.c = p + 0x10;
    if (n > 0) {
        dl_SetDLPriority(dl_GetPri());
        dl_OpenDma(5, D_004EE6F0.dma, 0);
        dl_CloseDma();
    }
}

void DrawLightningN(int num, LightningNode *v, void *col, float f0, float f1, float f2, float f3,
                    float f4, float f5, float f6, float f7, float f8, float f9, int c)
{
    StructB buf[num];
    int i;

    if (num >= 3) {
        qsort(&v[1], num - 1, sizeof(LightningNode), cmpr);
    }
    for (i = 0; i < num; i++) {
        sceVu0CopyVector(&buf[i], &v[i]);
    }
    DrawLightning2(num, (LightningVtx *)buf, col, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, c);
}

inline int cmpr(int *self, int *other)
{
    return *(int *)((char *)self + 0x10) - *(int *)((char *)other + 0x10);
}

inline void DrawLightning(void *p0, void *p1, void *a2, float f0, float f1, float f2, float f3,
                          float f4, float f5, float f6, float f7, float f8, float f9, int a3)
{
    StructB buf[2];
    sceVu0CopyVector(&buf[0], p0);
    sceVu0CopyVector(&buf[1], p1);
    DrawLightning2(2, (LightningVtx *)&buf[0], a2, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, a3);
}

inline void lightning_test(void)
{
    StructB col = {{0x80, 0xFF, 0xFF, 0x80}};
    StructC vtx = {{
        {{0.0f, 750.0f, 0.0f, 1.0f}},
        {{0.0f, 500.0f, -200.0f, 1.0f}},
        {{0.0f, 250.0f, 200.0f, 1.0f}},
        {{0.0f, 0.0f, 0.0f, 1.0f}},
    }};
    DrawLightning2(4, (LightningVtx *)&vtx, &col, 5.0f, 25.0f, 5.0f, 25.0f, 5.0f, 10.0f, 70.0f,
                   8.0f, 20.0f, 0.0f, 0);
}
