#include "common.h"

#include "vu0.h"

typedef struct {
    int a, b, c, d;
} GsAlphaEnt;

/* The display-list packet builder state.  `ptr` is the write cursor; `dma`,
   `tail`, `gif` and `end` are the back-pointers into the packet that
   gif_EndPacket patches once the packet's size is known (DMA tag, source
   chain tail, VIF DIRECT code and GIF tag respectively). */
typedef struct {
    int cur;
    int *buf[2];
    char *dma;
    unsigned long long *ptr;
    char *tail;
    char *gif;
    char *end;
} GifDpk;
extern GifDpk D_004EE6F0;
/* One 64-bit slot of a DMA/GIF packet: written either as the whole qword
   (DMA tag, GIF tag, A+D data) or as one of its two 32-bit halves. */
typedef union {
    long long d;
    int w[2];
} GifPkWord;
/* INTERIM (same construct as getSkeltonFocusNode in src/motionManager2.c):
   the listing inlines gif_SetGsReg (body line 233, parameter line 224) into
   most of this TU, so it is `inline` in the dev's TU; while this tail still
   has asm members a deferred inline would be emitted at the object end
   instead of at its ROM slot, so the public body stays a plain definition
   there and every C caller the listing shows inlining it calls this static
   stand-in.  Collapses to one `inline` definition at layout. */
static inline void setGsReg(long long a0, long long a1)
{
    *D_004EE6F0.ptr++ = a1;
    *D_004EE6F0.ptr++ = a0;
}

/* The two GS register payloads this file packs over and over: RGBAQ from a
   4-byte colour, and XYZ2 from a 2D screen point plus a 64-bit Z.  The GS
   window origin is 2048.0 pixels, i.e. 0x8000 in 1/16-pixel units. */
#define GIF_RGBA(c)                                                                                \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
/* the same packed XYZ2 word with the window origin already folded into the
   coordinates (the sprite family offsets its size once, then adds the corner) */
#define GIF_XY0(x, y, z) ((long long)(x) | ((long long)(y) << 16) | ((z) << 32))
/* the ST/UV pair the textured-sprite family packs into the UV register */
#define GIF_UV(u, v) ((long long)(u) | ((long long)(v) << 16))
#define GIF_XY(x, y, z)                                                                            \
    ((long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16) | ((z) << 32))
#define GIF_XYZ(v, z) GIF_XY((v)[0], (v)[1], z)

/* The textured-sprite UV rectangle: two GS UV corners, in 1/16-texel units
   like the screen rect beside it. */
typedef struct {
    int u0, v0, u1, v1;
} GifUvRect;
extern int D_0063A064;
extern int D_0063A068;
extern float D_0063A05C;
extern float D_0063A060;
/* The "Offset" family adds the float draw origin (in 1/16-pixel units) instead
   of the fixed 2048.0-pixel window origin. */
#define GIF_OX ((int)D_0063A05C * 16)
#define GIF_OY ((int)D_0063A060 * 16)
#define GIF_XYZOFF(v, z) GIF_XY0(GIF_OX + (v)[0], GIF_OY + (v)[1], z)

void gif_StartPacket(void)
{
    char *c;

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
}
extern int D_00639F60;
extern void dl_OpenDma(int chan, void *dma, int flag);
extern void dl_CloseDma(void);

void gif_EndPacket(void)
{
    char *p;

    ((GifPkWord *)D_004EE6F0.end)->d =
        (unsigned int)(((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.end) >> 4) - 1) |
        0x1000000000008000LL;
    ((GifPkWord *)D_004EE6F0.gif)->w[0] =
        ((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.gif) >> 4) | 0x50000000;
    ((GifPkWord *)D_004EE6F0.tail)->d =
        (unsigned int)((((unsigned int)((char *)D_004EE6F0.ptr - D_004EE6F0.tail) >> 4) - 1) |
                       0x10000000);
    p = (char *)D_004EE6F0.ptr;
    D_004EE6F0.tail = p;
    ((GifPkWord *)p)->d = 0x60000000;
    D_004EE6F0.ptr = (unsigned long long *)(p + 8);
    ((GifPkWord *)(p + 8))->w[0] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 0xC);
    ((GifPkWord *)(p + 8))->w[1] = 0;
    D_004EE6F0.ptr = (unsigned long long *)(p + 0x10);
    dl_OpenDma(5, D_004EE6F0.dma, 0);
    dl_CloseDma();
    D_00639F60 = 0;
}
void gif_StartPacketPath1(void)
{
    char *c;

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
}
void gif_EndPacketPath1(void)
{
    char *p;
    char *q;

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
    D_00639F60 = 0;
}
void gif_MakeLine2DOffset(int *v0, int *v1, long long z0, long long z1, unsigned char *col,
                          int prim)
{
    setGsReg(0x00, ((long long)prim << 6) | 0xA);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZOFF(v0, z0));
    setGsReg(0x05, GIF_XYZOFF(v1, z1));
}
void gif_MakeSprite(int x, int y, int w, int h, long long z, int *uv, unsigned char *col, int prim)
{
    int fx = w + 0x8000;
    int fy = h + 0x8000;

    setGsReg(0x00, (prim << 6) | 0x116);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x03, GIF_UV(uv[0], uv[1]));
    setGsReg(0x05, GIF_XY(x, y, z));
    setGsReg(0x03, GIF_UV(uv[0] + uv[2], uv[1] + uv[3]));
    setGsReg(0x05, GIF_XY0(x + fx, y + fy, z));
}
void gif_MakeSpriteOffset(int x, int y, int w, int h, long long z, int *uv, unsigned char *col,
                          int prim)
{
    setGsReg(0x00, (prim << 6) | 0x116);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x03, GIF_UV(uv[0], uv[1]));
    setGsReg(0x05, GIF_XY0(GIF_OX + x, GIF_OY + y, z));
    setGsReg(0x03, GIF_UV(uv[0] + uv[2], uv[1] + uv[3]));
    setGsReg(0x05, GIF_XY0(GIF_OX + x + w, GIF_OY + y + h, z));
}
void gif_MakeSpriteWithStrip(int *r, long long z, int *uv, unsigned char *col, int prim)
{
    setGsReg(0x00, (prim << 6) | 0x114);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x03, GIF_UV(uv[0], uv[1]));
    setGsReg(0x0D, GIF_XY(r[0], r[1], z));
    setGsReg(0x03, GIF_UV(uv[0], uv[1] + uv[3]));
    setGsReg(0x0D, GIF_XY(r[2], r[3], z));
    setGsReg(0x03, GIF_UV(uv[0] + uv[2], uv[1]));
    setGsReg(0x05, GIF_XY(r[4], r[5], z));
    setGsReg(0x03, GIF_UV(uv[0] + uv[2], uv[1] + uv[3]));
    setGsReg(0x05, GIF_XY(r[6], r[7], z));
}
/* gif_MakePoint2DOffset is `inline` too (its lines appear inside gif_PointOffset);
   same interim stand-in as makePoint2D. */
static inline void makePoint2DOffset(int *v, long long z, unsigned char *col, int prim)
{
    setGsReg(0x00, 0x100 | ((long long)prim << 6));
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZOFF(v, z));
}

void gif_PointOffset(int *v, long long z, unsigned char *col, int prim)
{
    int p[4];

    p[0] = v[0] * D_0063A064 / 640;
    p[1] = v[1] * D_0063A068 / 224;
    makePoint2DOffset(p, z, col, prim);
}
/* gif_MakeLine2D is `inline` (its lines appear inside gif_Line); interim stand-in. */
static inline void makeLine2D(int *v0, int *v1, long long z0, long long z1, unsigned char *col,
                              int prim)
{
    setGsReg(0x00, ((long long)prim << 6) | 0xA);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZ(v0, z0));
    setGsReg(0x05, GIF_XYZ(v1, z1));
}

void gif_Line(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim)
{
    int p0[4];
    int p1[4];

    p0[0] = v0[0] * D_0063A064 / 640 * 16;
    p0[1] = v0[1] * D_0063A068 / 224 * 16;
    p1[0] = v1[0] * D_0063A064 / 640 * 16;
    p1[1] = v1[1] * D_0063A068 / 224 * 16;
    makeLine2D(p0, p1, z0, z1, col, prim);
}
/* gif_MakeSpriteNoTexture is `inline` and small enough that the Sprite wrappers
   inline it, while gif_MakeSprite stays a call; interim stand-in. */
static inline void makeSpriteNoTexture(int x, int y, int w, int h, long long z, unsigned char *col,
                                       int prim)
{
    int fx = w + 0x8000;
    int fy = h + 0x8000;

    setGsReg(0x00, (prim << 6) | 0x406);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XY(x, y, z));
    setGsReg(0x05, GIF_XY0(x + fx, y + fy, z));
}

/* gif_MakeSpriteNoTextureOffset is `inline` too; interim stand-in. */
static inline void makeSpriteNoTextureOffset(int x, int y, int w, int h, long long z,
                                             unsigned char *col, int prim)
{
    setGsReg(0x00, (prim << 6) | 0x406);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XY0(GIF_OX + x, GIF_OY + y, z));
    setGsReg(0x05, GIF_XY0(GIF_OX + x + w, GIF_OY + y + h, z));
}

void gif_Sprite(int *r, long long z, int *uv, unsigned char *col, int prim)
{
    int x = r[0] * D_0063A064 / 640 * 16;
    int y = r[1] * D_0063A068 / 224 * 16;
    int w = r[2] * D_0063A064 / 640 * 16;
    int h = r[3] * D_0063A068 / 224 * 16;

    if (uv == 0) {
        makeSpriteNoTexture(x, y, w, h, z, col, prim);
    } else {
        GifUvRect t = *(GifUvRect *)uv;

        t.u0 *= 16;
        t.v0 *= 16;
        t.u1 *= 16;
        t.v1 *= 16;
        gif_MakeSprite(x, y, w, h, z, (int *)&t, col, prim);
    }
}
void gif_SpriteSensitive(int *r, long long z, int *uv, unsigned char *col, int prim)
{
    int x = r[0] * D_0063A064 / 640;
    int y = r[1] * D_0063A068 / 224;
    int w = r[2] * D_0063A064 / 640;
    int h = r[3] * D_0063A068 / 224;

    if (uv) {
        gif_MakeSprite(x, y, w, h, z, uv, col, prim);
    } else {
        makeSpriteNoTexture(x, y, w, h, z, col, prim);
    }
}
void gif_SpriteOffset(int *r, long long z, int *uv, unsigned char *col, int prim)
{
    int x = r[0] * D_0063A064 / 640 * 16;
    int y = r[1] * D_0063A068 / 224 * 16;
    int w = r[2] * D_0063A064 / 640 * 16;
    int h = r[3] * D_0063A068 / 224 * 16;

    if (uv == 0) {
        makeSpriteNoTextureOffset(x, y, w, h, z, col, prim);
    } else {
        GifUvRect t = *(GifUvRect *)uv;

        t.u0 *= 16;
        t.v0 *= 16;
        t.u1 *= 16;
        t.v1 *= 16;
        gif_MakeSpriteOffset(x, y, w, h, z, (int *)&t, col, prim);
    }
}
void gif_SpriteSensitiveOffset(int *r, long long z, int *uv, unsigned char *col, int prim)
{
    int x = r[0] * D_0063A064 / 640;
    int y = r[1] * D_0063A068 / 224;
    int w = r[2] * D_0063A064 / 640;
    int h = r[3] * D_0063A068 / 224;

    if (uv) {
        gif_MakeSpriteOffset(x, y, w, h, z, uv, col, prim);
    } else {
        makeSpriteNoTextureOffset(x, y, w, h, z, col, prim);
    }
}
void gif_SpriteOrg(int *r, long long z, int *uv, unsigned char *col, int prim)
{
    int x = r[0] * 16;
    int y = r[1] * 16;
    int w = r[2] * 16;
    int h = r[3] * 16;

    if (uv == 0) {
        makeSpriteNoTexture(x, y, w, h, z, col, prim);
    } else {
        GifUvRect t = *(GifUvRect *)uv;

        t.u0 *= 16;
        t.v0 *= 16;
        t.u1 *= 16;
        t.v1 *= 16;
        gif_MakeSprite(x, y, w, h, z, (int *)&t, col, prim);
    }
}
void gif_SpriteSensitiveOrg(int *r, long long z, int *uv, unsigned char *col, int prim)
{
    int x = r[0];
    int y = r[1];
    int w = r[2];
    int h = r[3];

    if (uv) {
        gif_MakeSprite(x, y, w, h, z, uv, col, prim);
    } else {
        makeSpriteNoTexture(x, y, w, h, z, col, prim);
    }
}
extern int D_0063A074;
extern int D_0063A078;

void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm, unsigned int w,
                           unsigned int h, int useoffset, int clear)
{
    setGsReg(0x4C,
             (fbp >> 5) | ((unsigned long long)((w >> 6) & 0x3F) << 16) | ((psm & 0xF) << 24));
    setGsReg(0x40, ((unsigned long long)(w - 1) << 16) | ((unsigned long long)(h - 1) << 48));
    if (clear) {
        setGsReg(0x47, 0x30000);
        setGsReg(0x00, 6);
        setGsReg(0x01, 0xFE00LL << 46);
        setGsReg(0x05, 0);
        setGsReg(0x05, (unsigned long long)(w << 4) | ((unsigned long long)(h << 4) << 16));
        setGsReg(0x47, 0x50000);
    }
    if (useoffset) {
        setGsReg(0x18, (unsigned long long)(unsigned int)(((0x800 - (w >> 1)) << 4) + D_0063A074) |
                           ((unsigned long long)(((0x800 - (h >> 1)) << 4) + D_0063A078) << 32));
    } else {
        setGsReg(0x18, (unsigned long long)(unsigned int)((0x800 - (w >> 1)) << 4) |
                           ((unsigned long long)((0x800 - (h >> 1)) << 4) << 32));
    }
}
extern int D_00639F68[2];
extern int D_00639F70;

/* INTERIM stand-in for the `inline` _IsInScreen (its out-of-line copy sits at
   its own ROM slot further down this file); same construct as setGsReg. */
static inline int isInScreen(volatile int *p)
{
    if (p[2] < 0)
        return 0;
    if (p[2] > 0x0FFFFFF0)
        return 0;
    if (p[0] < 0)
        return 0;
    if (p[0] > 0xFFF0)
        return 0;
    if (p[1] < 0)
        return 0;
    return p[1] <= 0xFFF0;
}

/* One vertex through the VU0 macro-mode pipeline: transform by the current
   matrix in vf4..vf7, perspective-divide by w and convert to the GS's 12.4
   fixed-point screen coordinates. */
static inline void rotTransPers(void *src)
{
    VU0_LSV_R(lqc2, 8, 0x0, src);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 10, 7, 8, w);
    VU0_REG("vdiv Q, $vf0w, $vf10w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf10, $vf10, Q");
    VU0_V2OP(vftoi4.xyz, 11, 10);
}

/* One vertex through the VU0 pipeline into a caller-supplied projected-vertex
   slot, answering whether the result is on screen.  The destination is a
   parameter, so its address is materialised at the call site — which is why
   each `addiu aN,sp,K` sits in the previous visibility test's delay slot.
   The first vertex lands at frame offset 0, where the address folds to $sp
   itself and no address register is needed, so it is written out here. */
static inline int projectVertex(int *d, void *src)
{
    rotTransPers(src);
    VU0_LSV_R(sqc2, 11, 0x0, d);
    return isInScreen(d);
}

void gif_DrawPolyF4(void *p0, void *p1, void *p2, void *p3, int r, int g, int b, int a, int prim)
{
    int q[4][4];
    int i;

    setGsReg(0x00, ((long long)prim << 6) | 0x104);
    setGsReg(0x01, (long long)r | ((long long)g << 8) | ((long long)b << 16) |
                       ((long long)a << 24) | (0xFE00LL << 46));
    rotTransPers(p0);
    VU0_LSV_R(sqc2, 11, 0x0, q[0]);
    if (!isInScreen(q[0]))
        return;
    if (!projectVertex(q[1], p1))
        return;
    if (!projectVertex(q[2], p2))
        return;
    if (!projectVertex(q[3], p3))
        return;
    for (i = 0; i < 4; i++) {
        int *s = q[i];

        setGsReg(0x05, GIF_XY0(s[0], s[1], (long long)s[2]));
    }
}
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripF);
INCLUDE_ASM("asm/nonmatchings/src/GifPacket", gif_DrawStripFST);
void gif_DrawStripG(void *v, void *col, int n, int prim)
{
    char *p = v;
    unsigned char *c = col;
    int i;

    D_00639F68[0] = D_00639F68[1] = 0;
    setGsReg(0x00, ((long long)prim << 6) | 0x10C);
    D_00639F70 = 0;
    for (i = 0; i < n; i++, c += 4, p += 16) {
        volatile int q[4];
        int t;

        rotTransPers(p);
        VU0_LSV_R(sqc2, 11, 0x0, q);
        t = isInScreen(q);
        setGsReg(0x01, GIF_RGBA(c) | (0xFE00LL << 46));
        if (t && D_00639F68[0] && D_00639F68[1]) {
            setGsReg(0x05, GIF_XY0(q[0], q[1], (long long)q[2]));
        } else {
            setGsReg(0x0D, GIF_XY0(q[0], q[1], (long long)q[2]));
        }
        D_00639F68[D_00639F70++] = t;
        D_00639F70 &= 1;
    }
}
void gif_Draw2DStripG(int *v, unsigned char *col, int n, int prim)
{
    int i;

    D_00639F68[0] = D_00639F68[1] = 0;
    setGsReg(0x00, ((long long)prim << 6) | 0x10C);
    D_00639F70 = 0;
    for (i = 0; i < n; i++, col += 4, v += 4) {
        int c;

        c = isInScreen(v);
        setGsReg(0x01, GIF_RGBA(col) | (0xFE00LL << 46));
        if (c && D_00639F68[0] && D_00639F68[1]) {
            setGsReg(0x05, GIF_XY0(v[0], v[1], (long long)v[2]));
        } else {
            setGsReg(0x0D, GIF_XY0(v[0], v[1], (long long)v[2]));
        }
        D_00639F68[D_00639F70++] = c;
        D_00639F70 &= 1;
    }
}
void gif_Draw2DUVStripG(int *v, int *uv, unsigned char *col, int n, int prim)
{
    int i;

    D_00639F68[0] = D_00639F68[1] = 0;
    setGsReg(0x00, ((long long)prim << 6) | 0x11C);
    D_00639F70 = 0;
    for (i = 0; i < n; i++, col += 4, v += 4, uv += 4) {
        int c;

        c = isInScreen(v);
        setGsReg(0x01, GIF_RGBA(col) | (0xFE00LL << 46));
        setGsReg(0x03, GIF_UV(uv[0], uv[1]));
        if (c && D_00639F68[0] && D_00639F68[1]) {
            setGsReg(0x05, GIF_XY0(v[0], v[1], (long long)v[2]));
        } else {
            setGsReg(0x0D, GIF_XY0(v[0], v[1], (long long)v[2]));
        }
        D_00639F68[D_00639F70++] = c;
        D_00639F70 &= 1;
    }
}
void gif_Init(void)
{
    D_00639F60 = 0;
}
extern void dl_SetDLPriority();
extern void gif_StartPacket();

void gif_StartPacketPri(void)
{
    dl_SetDLPriority();
    gif_StartPacket();
    D_00639F60 = 1;
}
extern void gif_StartPacketPath1(void);

void gif_StartPacketPriPath1(void)
{
    dl_SetDLPriority();
    gif_StartPacketPath1();
    D_00639F60 = 1;
}

void gif_SetGsReg(long long a0, long long a1)
{
    *D_004EE6F0.ptr++ = a1;
    *D_004EE6F0.ptr++ = a0;
}
int gif_CheckOpen(void)
{
    return D_00639F60;
}
/* gif_MakePoint2D is `inline` per the listing: its lines 318-320 appear inside
   gif_Point and the rest of the point family.  While its own out-of-line copy
   is still asm, the callers the listing shows inlining it call this static
   stand-in; it collapses to one `inline` definition at layout. */
static inline void makePoint2D(int *v, long long z, unsigned char *col, long long prim)
{
    setGsReg(0x00, (prim << 6) | 0x100);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZ(v, z));
}

void gif_MakePoint2D(int *v, long long z, unsigned char *col, int prim)
{
    setGsReg(0x00, ((long long)prim << 6) | 0x100);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZ(v, z));
}
void gif_MakePoint2DOffset(int *v, long long z, unsigned char *col, int prim)
{
    setGsReg(0x00, 0x100 | ((long long)prim << 6));
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZOFF(v, z));
}
void gif_MakeLine2D(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim)
{
    setGsReg(0x00, ((long long)prim << 6) | 0xA);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZ(v0, z0));
    setGsReg(0x05, GIF_XYZ(v1, z1));
}
void gif_MakeSpriteNoTexture(int x, int y, int w, int h, long long z, unsigned char *col, int prim)
{
    int fx = w + 0x8000;
    int fy = h + 0x8000;

    setGsReg(0x00, (prim << 6) | 0x406);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XY(x, y, z));
    setGsReg(0x05, GIF_XY0(x + fx, y + fy, z));
}
void gif_MakeSpriteNoTextureOffset(int x, int y, int w, int h, long long z, unsigned char *col,
                                   int prim)
{
    setGsReg(0x00, (prim << 6) | 0x406);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XY0(GIF_OX + x, GIF_OY + y, z));
    setGsReg(0x05, GIF_XY0(GIF_OX + x + w, GIF_OY + y + h, z));
}
void gif_Point(int *v, long long z, unsigned char *col, int prim)
{
    int p[2];

    p[0] = v[0] * D_0063A064 / 640;
    p[1] = v[1] * D_0063A068 / 224;
    makePoint2D(p, z, col, prim);
}
void gif_LineOffset(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim)
{
    int p0[4];
    int p1[4];

    p0[0] = v0[0] * D_0063A064 / 640 * 16;
    p0[1] = v0[1] * D_0063A068 / 224 * 16;
    p1[0] = v1[0] * D_0063A064 / 640 * 16;
    p1[1] = v1[1] * D_0063A068 / 224 * 16;
    gif_MakeLine2DOffset(p0, p1, z0, z1, col, prim);
}
/* .rodata — carved VMA 0x54E0B0..0x54E170; the 12 ALPHA_1/2 blend-parameter
   quadruples gif_SetAlpha packs into the GS ALPHA register, bytes verified
   against baserom/pal/baseelf.rom */
const GsAlphaEnt D_0054E0B0[12] = {
    {0, 2, 2, 1}, {2, 0, 2, 1}, {0, 1, 2, 1}, {1, 2, 2, 0}, {0, 1, 0, 1}, {0, 2, 0, 1},
    {2, 0, 0, 1}, {0, 1, 0, 1}, {0, 2, 1, 1}, {2, 0, 1, 1}, {0, 1, 1, 1}, {1, 2, 0, 1},
};

void gif_SetAlpha(long long a0, long long a1, long long a2)
{
    unsigned long long *p, *q;
    unsigned long long v;
    int idx;

    idx = (int)a1;
    p = D_004EE6F0.ptr;
    *(volatile unsigned long long *)p = (a0 == 0);
    p++;
    *(unsigned long long *volatile *)&D_004EE6F0.ptr = p;
    *(volatile unsigned long long *)p = 0x49;
    *(unsigned long long *volatile *)&D_004EE6F0.ptr = p + 1;
    a1 = 0x42;
    v = (unsigned long long)D_0054E0B0[idx].a | ((unsigned long long)a2 << 32);
    v |=
        ((unsigned long long)D_0054E0B0[idx].c << 4) | ((unsigned long long)D_0054E0B0[idx].b << 2);
    v |= (unsigned long long)D_0054E0B0[idx].d << 6;
    *(volatile unsigned long long *)(p + 1) = v;
    *(unsigned long long *volatile *)&D_004EE6F0.ptr = p + 2;
    q = p + 3;
    *(volatile unsigned long long *)(p + 2) = a1;
    D_004EE6F0.ptr = q;
}
void gif_MoveImage(long long sbp, long long sbw, long long psm, int *rect, long long dbp,
                   long long dbw, long long dsax, long long dsay)
{
    setGsReg(0x50, (psm << 56) | (dbw << 48) | (dbp << 32) | (psm << 24) | (sbw << 16) | sbp);
    setGsReg(0x51, (dsay << 48) | (rect[1] << 16) | (dsax << 32) | rect[0]);
    setGsReg(0x52, ((long long)rect[3] << 32) | rect[2]);
    setGsReg(0x53, 2);
}
void gif_SetZTest(int a0)
{
    int new_var;
    unsigned long long *p, *q;
    if (a0) {
        a0 = 0x50000;
        new_var = 0;
        do {
        } while (new_var);
    } else {
        a0 = 0x30000;
    }
    p = D_004EE6F0.ptr;
    *(volatile unsigned long long *)p = a0;
    p++;
    *(unsigned long long *volatile *)&D_004EE6F0.ptr = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x47;
    D_004EE6F0.ptr = q;
}
void gif_SetZWrite(int a0)
{
    unsigned long long *p, *q;
    int new_var;
    unsigned long long tag;
    if (a0) {
        tag = 0x300000C0;
        new_var = 0;
        do {
        } while (new_var);
    } else {
        tag = 0x1300000C0;
    }
    p = D_004EE6F0.ptr;
    *(volatile unsigned long long *)p = tag;
    p++;
    *(unsigned long long *volatile *)&D_004EE6F0.ptr = p;
    q = p + 1;
    *(volatile unsigned long long *)p = 0x4E;
    D_004EE6F0.ptr = q;
}
void gif_SetHalfOffset(void)
{
    setGsReg(0x18, (long long)(((0x800 - D_0063A064 / 2) << 4) + D_0063A074) |
                       ((long long)(((0x800 - D_0063A068 / 2) << 4) + D_0063A078) << 32));
}
int _IsInScreen(volatile int *a0)
{
    if (a0[2] < 0)
        return 0;
    if (a0[2] > 0x0FFFFFF0)
        return 0;
    if (a0[0] < 0)
        return 0;
    if (a0[0] > 0xFFF0)
        return 0;
    if (a0[1] < 0)
        return 0;
    return a0[1] <= 0xFFF0;
}
