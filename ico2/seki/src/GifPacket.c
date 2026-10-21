#include "typedef.h"
#include "GifPacket.h"
#include "GsBase.h"
#include "DmaPacket.h"
#include "DisplayList.h"
#include "main.h"
#include "debug.h"

typedef struct { /* field names derived */
    int a, b, c, d;
} GsAlphaEnt; /* derived name */

/* The display-list packet builder state.  `ptr` is the write cursor; `dma`,
   `tail`, `gif` and `end` are the back-pointers into the packet that
   gif_EndPacket patches once the packet's size is known (DMA tag, source
   chain tail, VIF DIRECT code and GIF tag respectively). */

/* One 64-bit slot of a DMA/GIF packet: written either as the whole qword
   (DMA tag, GIF tag, A+D data) or as one of its two 32-bit halves. */

/* The two GS register payloads this file packs over and over: RGBAQ from a
   4-byte colour, and XYZ2 from a 2D screen point plus a 64-bit Z.  The GS
   window origin is 2048.0 pixels, i.e. 0x8000 in 1/16-pixel units. */
#define GIF_RGBA(c) /* derived name */                                                             \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
/* the same packed XYZ2 word with the window origin already folded into the
   coordinates (the sprite family offsets its size once, then adds the corner) */
/* the same RGBAQ payload from a GifColor */
#define GIF_COLOR(c) /* derived name */                                                            \
    ((long long)(c)->r | ((long long)(c)->g << 8) | ((long long)(c)->b << 16) |                    \
     ((long long)(c)->a << 24))
#define GIF_XY0(x, y, z) ((long long)(x) | ((long long)(y) << 16) | ((z) << 32)) /* derived name */
/* the ST/UV pair the textured-sprite family packs into the UV register */
#define GIF_UV(u, v) ((long long)(u) | ((long long)(v) << 16)) /* derived name */
#define GIF_XY(x, y, z)                                        /* derived name */                  \
    ((long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16) | ((z) << 32))
#define GIF_XYZ(v, z) GIF_XY((v)[0], (v)[1], z) /* derived name */
/* The "Offset" family adds the float draw origin (in 1/16-pixel units) instead
   of the fixed 2048.0-pixel window origin. */
#define GIF_OX ((int)center_X * 16)                                   /* derived name */
#define GIF_OY ((int)center_Y * 16)                                   /* derived name */
#define GIF_XYZOFF(v, z) GIF_XY0(GIF_OX + (v)[0], GIF_OY + (v)[1], z) /* derived name */

/* the 12 ALPHA_1/2 blend-parameter quadruples gif_SetAlpha packs into the GS
   ALPHA register */
static const GsAlphaEnt alphaTable[12] = {
    /* derived name */
    {0, 2, 2, 1}, {2, 0, 2, 1}, {0, 1, 2, 1}, {1, 2, 2, 0}, {0, 1, 0, 1}, {0, 2, 0, 1},
    {2, 0, 0, 1}, {0, 1, 0, 1}, {0, 2, 1, 1}, {2, 0, 1, 1}, {0, 1, 1, 1}, {1, 2, 0, 1},
};

static void gif_StartPacket(void)
{
    char *c;

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
}

/* the open-packet flag gif_EndPacket clears, then the strip drawers' last two on-screen
   flags and the index of the older one. */
static int packetOpen = 0; /* derived name */

void gif_StartPacketPri(int pri)
{
    if (packetOpen) {
        debug_StdPrintfDummy("gif already open %d\n", frame_count);
        return;
    }
    dl_SetDLPriority(pri);
    gif_StartPacket();
    packetOpen = 1;
}

void gif_EndPacket(void)
{
    char *p;

    if (packetOpen == 0) {
        debug_StdPrintfDummy("gif not open %d\n", frame_count);
    } else {
        if (PacketBufferStruct.tail.c == 0 || PacketBufferStruct.gif.c == 0 ||
            PacketBufferStruct.end.c == 0) {
            debug_StdPrintfDummy("d:%p v:%p g:%p\n", PacketBufferStruct.tail.c,
                                 PacketBufferStruct.gif.c, PacketBufferStruct.end.c);
            packetOpen = 0;
            return;
        }

        ((GifPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
            ((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) | 0x50000000;
        ((GifPkWord *)PacketBufferStruct.tail.c)->d =
            (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.tail.c) >>
                             4) -
                            1) |
                           0x10000000);
        p = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = p;
        ((GifPkWord *)p)->d = 0x60000000;
        PacketBufferStruct.ptr.c = p + 8;
        ((GifPkWord *)(p + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = p + 0xC;
        ((GifPkWord *)(p + 8))->w[1] = 0;
        PacketBufferStruct.ptr.c = p + 0x10;
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
        packetOpen = 0;
    }
}

void gif_SetGsReg(long long reg, long long data)
{
    if (packetOpen == 0) {
        debug_StdPrintfDummy("gif not open\n");
        return;
    }
    *PacketBufferStruct.ptr.d++ = data;
    *PacketBufferStruct.ptr.d++ = reg;
}

static void gif_StartPacketPath1(void)
{
    char *c;

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
}

void gif_StartPacketPriPath1(int pri)
{
    if (packetOpen) {
        debug_StdPrintfDummy("gif already open %d\n", frame_count);
        return;
    }
    dl_SetDLPriority(pri);
    gif_StartPacketPath1();
    packetOpen = 1;
}

void gif_EndPacketPath1(void)
{
    char *p;
    char *q;

    if (packetOpen == 0) {
        debug_StdPrintfDummy("gif not open %d\n", frame_count);
        return;
    }
    if (PacketBufferStruct.tail.c == 0 || PacketBufferStruct.gif.c == 0 ||
        PacketBufferStruct.end.c == 0) {
        debug_StdPrintfDummy("d:%p v:%p g:%p\n", PacketBufferStruct.tail.c,
                             PacketBufferStruct.gif.c, PacketBufferStruct.end.c);
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
    packetOpen = 0;
}

void gif_MakePoint2D(int *v, long long z, unsigned char *col, int prim)
{
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0x100);
    gif_SetGsReg(0x01, GIF_RGBA(col));
    gif_SetGsReg(0x05, GIF_XYZ(v, z));
}

void gif_MakePoint2DOffset(int *v, long long z, unsigned char *col, int prim)
{
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0x100);
    gif_SetGsReg(0x01, GIF_RGBA(col));
    gif_SetGsReg(0x05, GIF_XYZOFF(v, z));
}

void gif_MakeLine2D(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim)
{
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0xA);
    gif_SetGsReg(0x01, GIF_RGBA(col));
    gif_SetGsReg(0x05, GIF_XYZ(v0, z0));
    gif_SetGsReg(0x05, GIF_XYZ(v1, z1));
}

void gif_MakeLine2DOffset(int *v0, int *v1, long long z0, long long z1, unsigned char *col,
                          int prim)
{
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0xA);
    gif_SetGsReg(0x01, GIF_RGBA(col));
    gif_SetGsReg(0x05, GIF_XYZOFF(v0, z0));
    gif_SetGsReg(0x05, GIF_XYZOFF(v1, z1));
}

void gif_MakeSpriteNoTexture(int x, int y, int w, int h, long long z, GifColor *col, int prim)
{
    int fx;
    int fy;

    gif_SetGsReg(0x00, (prim << 6) | 0x406);
    gif_SetGsReg(0x01, GIF_COLOR(col));
    gif_SetGsReg(0x05, GIF_XY(x, y, z));
    fx = w + 0x8000;
    fy = h + 0x8000;
    gif_SetGsReg(0x05, GIF_XY0(x + fx, y + fy, z));
}

void gif_MakeSprite(int x, int y, int w, int h, long long z, GifRect *uv, GifColor *col, int prim)
{
    int fx;
    int fy;

    gif_SetGsReg(0x00, (prim << 6) | 0x116);
    gif_SetGsReg(0x01, GIF_COLOR(col));
    gif_SetGsReg(0x03, GIF_UV(uv->x, uv->y));
    gif_SetGsReg(0x05, GIF_XY(x, y, z));
    gif_SetGsReg(0x03, GIF_UV(uv->x + uv->w, uv->y + uv->h));
    fx = w + 0x8000;
    fy = h + 0x8000;
    gif_SetGsReg(0x05, GIF_XY0(x + fx, y + fy, z));
}

void gif_MakeSpriteNoTextureOffset(int x, int y, int w, int h, long long z, GifColor *col, int prim)
{
    gif_SetGsReg(0x00, (prim << 6) | 0x406);
    gif_SetGsReg(0x01, GIF_COLOR(col));
    gif_SetGsReg(0x05, GIF_XY0(GIF_OX + x, GIF_OY + y, z));
    gif_SetGsReg(0x05, GIF_XY0(GIF_OX + x + w, GIF_OY + y + h, z));
}

void gif_MakeSpriteOffset(int x, int y, int w, int h, long long z, GifRect *uv, GifColor *col,
                          int prim)
{
    gif_SetGsReg(0x00, (prim << 6) | 0x116);
    gif_SetGsReg(0x01, GIF_COLOR(col));
    gif_SetGsReg(0x03, GIF_UV(uv->x, uv->y));
    gif_SetGsReg(0x05, GIF_XY0(GIF_OX + x, GIF_OY + y, z));
    gif_SetGsReg(0x03, GIF_UV(uv->x + uv->w, uv->y + uv->h));
    gif_SetGsReg(0x05, GIF_XY0(GIF_OX + x + w, GIF_OY + y + h, z));
}

void gif_MakeSpriteWithStrip(int *r, long long z, GifRect *uv, GifColor *col, int prim)
{
    gif_SetGsReg(0x00, (prim << 6) | 0x114);
    gif_SetGsReg(0x01, GIF_COLOR(col));
    gif_SetGsReg(0x03, GIF_UV(uv->x, uv->y));
    gif_SetGsReg(0x0D, GIF_XY(r[0], r[1], z));
    gif_SetGsReg(0x03, GIF_UV(uv->x, uv->y + uv->h));
    gif_SetGsReg(0x0D, GIF_XY(r[2], r[3], z));
    gif_SetGsReg(0x03, GIF_UV(uv->x + uv->w, uv->y));
    gif_SetGsReg(0x05, GIF_XY(r[4], r[5], z));
    gif_SetGsReg(0x03, GIF_UV(uv->x + uv->w, uv->y + uv->h));
    gif_SetGsReg(0x05, GIF_XY(r[6], r[7], z));
}

void gif_SpriteSensitive(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim)
{
    int x = r->x * ScreenWidth / 640;
    int y = r->y * ScreenHeight / 224;
    int w = r->w * ScreenWidth / 640;
    int h = r->h * ScreenHeight / 224;

    if (uv == 0) {
        gif_MakeSpriteNoTexture(x, y, w, h, z, col, prim);
    } else {
        gif_MakeSprite(x, y, w, h, z, uv, col, prim);
    }
}

void gif_SpriteSensitiveOffset(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim)
{
    int x = r->x * ScreenWidth / 640;
    int y = r->y * ScreenHeight / 224;
    int w = r->w * ScreenWidth / 640;
    int h = r->h * ScreenHeight / 224;

    if (uv == 0) {
        gif_MakeSpriteNoTextureOffset(x, y, w, h, z, col, prim);
    } else {
        gif_MakeSpriteOffset(x, y, w, h, z, uv, col, prim);
    }
}

void gif_SpriteSensitiveOrg(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim)
{
    int x = r->x;
    int y = r->y;
    int w = r->w;
    int h = r->h;

    if (uv == 0) {
        gif_MakeSpriteNoTexture(x, y, w, h, z, col, prim);
    } else {
        gif_MakeSprite(x, y, w, h, z, uv, col, prim);
    }
}

void gif_SetAlpha(long long alpha, long long mode, long long fix)
{
    unsigned long long v;
    int idx;

    gif_SetGsReg(0x49, alpha == 0);
    idx = mode;
    v = (unsigned long long)alphaTable[idx].a | ((unsigned long long)fix << 32);
    v |=
        ((unsigned long long)alphaTable[idx].c << 4) | ((unsigned long long)alphaTable[idx].b << 2);
    v |= (unsigned long long)alphaTable[idx].d << 6;
    gif_SetGsReg(0x42, v);
}

void gif_MoveImage(long long sbp, long long sbw, long long psm, int *rect, long long dbp,
                   long long dbw, long long dsax, long long dsay)
{
    gif_SetGsReg(0x50, (psm << 56) | (dbw << 48) | (dbp << 32) | (psm << 24) | (sbw << 16) | sbp);
    gif_SetGsReg(0x51, (dsay << 48) | (rect[1] << 16) | (dsax << 32) | rect[0]);
    gif_SetGsReg(0x52, ((long long)rect[3] << 32) | rect[2]);
    gif_SetGsReg(0x53, 2);
}

void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm, unsigned int w,
                           unsigned int h, int useoffset, int clear)
{
    unsigned int x;
    unsigned int y;

    gif_SetGsReg(0x4C,
                 (fbp >> 5) | ((unsigned long long)((w >> 6) & 0x3F) << 16) | ((psm & 0xF) << 24));
    gif_SetGsReg(0x40, ((unsigned long long)(w - 1) << 16) | ((unsigned long long)(h - 1) << 48));
    if (clear) {
        gif_SetGsReg(0x47, 0x30000);
        gif_SetGsReg(0x00, 6);
        gif_SetGsReg(0x01, 0xFE00LL << 46);
        gif_SetGsReg(0x05, 0);
        gif_SetGsReg(0x05, (unsigned long long)(w << 4) | ((unsigned long long)(h << 4) << 16));
        gif_SetGsReg(0x47, 0x50000);
    }
    x = (0x800 - (w >> 1)) << 4;
    y = (0x800 - (h >> 1)) << 4;
    gif_SetGsReg(0x18, (unsigned long long)x |
                           ((unsigned long long)(useoffset && odd_even ? y + 8 : y) << 32));
}

void gif_SetZTest(int on)
{
    if (on)
        gif_SetGsReg(0x47, 0x50000);
    else
        gif_SetGsReg(0x47, 0x30000);
}

void gif_SetZWrite(int on)
{
    if (on)
        gif_SetGsReg(0x4E, 0x300000C0);
    else
        gif_SetGsReg(0x4E, 0x1300000C0LL);
}

void gif_SetHalfOffset(int interlace, int odd)
{
    int x = (0x800 - ScreenWidth / 2) << 4;
    int y = (0x800 - ScreenHeight / 2) << 4;

    if (interlace == 0) {
        odd = 0;
    }
    gif_SetGsReg(0x18, (long long)x | ((long long)(odd ? y + 8 : y) << 32));
}

static int stripVisible[2] = {0, 0}; /* derived name */

static int stripIndex = 0; /* derived name */

/* the on-screen test of a projected vertex, which the strip and polygon
   functions and _IsInScreen further down this file inline */
static inline int isInScreen(int *p) /* derived name */
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
    return p[1] <= 65520;
}

/* One vertex through the VU0 macro-mode pipeline: transform by the current
   matrix in vf4..vf7, perspective-divide by w and convert to the GS's 12.4
   fixed-point screen coordinates, stored to dst, in one asm statement. */
static inline void rotTransPers(int *dst, void *src) /* derived name */
{
    __asm__ __volatile__(".set noreorder\n\t"
                         "lqc2 $vf8, 0x0(%1)\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                         "vmaddw.xyzw $vf10, $vf7, $vf8w\n\t"
                         "vdiv Q, $vf0w, $vf10w\n\t"
                         "vwaitq\n\t"
                         "vmulq.xyz $vf10, $vf10, Q\n\t"
                         "vftoi4.xyz $vf11, $vf10\n\t"
                         "sqc2 $vf11, 0x0(%0)\n\t"
                         ".set reorder"
                         :
                         : "r"(dst), "r"(src)
                         : "memory");
}

/* One vertex through the VU0 pipeline into a caller-supplied projected-vertex
   slot, answering whether the result is on screen.  The first vertex, at
   frame offset 0, is written out here. */
static inline int projectVertex(int *d, void *src) /* derived name */
{
    rotTransPers(d, src);
    return isInScreen(d);
}

void gif_DrawPolyF4(void *p0, void *p1, void *p2, void *p3, int r, int g, int b, int a, int prim)
{
    int q[4][4];
    int i;

    gif_SetGsReg(0x00, ((long long)prim << 6) | 0x104);
    gif_SetGsReg(0x01, (long long)r | ((long long)g << 8) | ((long long)b << 16) |
                           ((long long)a << 24) | (0xFE00LL << 46));
    rotTransPers(q[0], p0);
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

        gif_SetGsReg(0x05, GIF_XY0(s[0], s[1], (long long)s[2]));
    }
}

void gif_DrawStripF(void *v, GifColor col, int n, int prim)
{
    char *p = v;
    int i;

    stripVisible[0] = stripVisible[1] = 0;
    stripIndex = 0;
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0x104);
    gif_SetGsReg(0x01, GIF_COLOR(&col) | (0xFE00LL << 46));
    for (i = 0; i < n; i++, p += 16) {
        int q[4];
        int t;

        rotTransPers(q, p);
        t = isInScreen(q);
        if (t && stripVisible[0] && stripVisible[1]) {
            gif_SetGsReg(0x05, GIF_XY0(q[0], q[1], (long long)q[2]));
        } else {
            gif_SetGsReg(0x0D, GIF_XY0(q[0], q[1], (long long)q[2]));
        }
        stripVisible[stripIndex++] = t;
        stripIndex &= 1;
    }
}

void gif_DrawStripG(void *v, void *col, int n, int prim)
{
    char *p = v;
    unsigned char *c = col;
    int i;

    stripVisible[0] = stripVisible[1] = 0;
    stripIndex = 0;
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0x10C);
    for (i = 0; i < n; i++, c += 4, p += 16) {
        int q[4];
        int t;

        rotTransPers(q, p);
        t = isInScreen(q);
        gif_SetGsReg(0x01, GIF_RGBA(c) | (0xFE00LL << 46));
        if (t && stripVisible[0] && stripVisible[1]) {
            gif_SetGsReg(0x05, GIF_XY0(q[0], q[1], (long long)q[2]));
        } else {
            gif_SetGsReg(0x0D, GIF_XY0(q[0], q[1], (long long)q[2]));
        }
        stripVisible[stripIndex++] = t;
        stripIndex &= 1;
    }
}

void gif_Draw2DStripG(int *v, GifColor *col, int n, int prim)
{
    int i;

    stripVisible[0] = stripVisible[1] = 0;
    stripIndex = 0;
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0x10C);
    for (i = 0; i < n; i++, col++, v += 4) {
        int c;

        c = isInScreen(v);
        gif_SetGsReg(0x01, GIF_COLOR(col) | (0xFE00LL << 46));
        if (c && stripVisible[0] && stripVisible[1]) {
            gif_SetGsReg(0x05, GIF_XY0(v[0], v[1], (long long)v[2]));
        } else {
            gif_SetGsReg(0x0D, GIF_XY0(v[0], v[1], (long long)v[2]));
        }
        stripVisible[stripIndex++] = c;
        stripIndex &= 1;
    }
}

void gif_Draw2DUVStripG(int *v, int *uv, unsigned char *col, int n, int prim)
{
    int i;

    stripVisible[0] = stripVisible[1] = 0;
    stripIndex = 0;
    gif_SetGsReg(0x00, ((long long)prim << 6) | 0x11C);
    for (i = 0; i < n; i++, col += 4, v += 4, uv += 4) {
        int c;

        c = isInScreen(v);
        gif_SetGsReg(0x01, GIF_RGBA(col) | (0xFE00LL << 46));
        gif_SetGsReg(0x03, GIF_UV(uv[0], uv[1]));
        if (c && stripVisible[0] && stripVisible[1]) {
            gif_SetGsReg(0x05, GIF_XY0(v[0], v[1], (long long)v[2]));
        } else {
            gif_SetGsReg(0x0D, GIF_XY0(v[0], v[1], (long long)v[2]));
        }
        stripVisible[stripIndex++] = c;
        stripIndex &= 1;
    }
}

void gif_Init(void)
{
    packetOpen = 0;
}

int gif_CheckOpen(void)
{
    return packetOpen;
}

void gif_Point(int *v, long long z, unsigned char *col, int prim)
{
    int p[2];

    p[0] = v[0] * ScreenWidth / 640;
    p[1] = v[1] * ScreenHeight / 224;
    gif_MakePoint2D(p, z, col, prim);
}

void gif_PointOffset(int *v, long long z, unsigned char *col, int prim)
{
    int p[2];

    p[0] = v[0] * ScreenWidth / 640;
    p[1] = v[1] * ScreenHeight / 224;
    gif_MakePoint2DOffset(p, z, col, prim);
}

void gif_Line(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim)
{
    int p0[4];
    int p1[4];

    p0[0] = v0[0] * ScreenWidth / 640 * 16;
    p0[1] = v0[1] * ScreenHeight / 224 * 16;
    p1[0] = v1[0] * ScreenWidth / 640 * 16;
    p1[1] = v1[1] * ScreenHeight / 224 * 16;
    gif_MakeLine2D(p0, p1, z0, z1, col, prim);
}

void gif_LineOffset(int *v0, int *v1, long long z0, long long z1, unsigned char *col, int prim)
{
    int p0[4];
    int p1[4];

    p0[0] = v0[0] * ScreenWidth / 640 * 16;
    p0[1] = v0[1] * ScreenHeight / 224 * 16;
    p1[0] = v1[0] * ScreenWidth / 640 * 16;
    p1[1] = v1[1] * ScreenHeight / 224 * 16;
    gif_MakeLine2DOffset(p0, p1, z0, z1, col, prim);
}

void gif_Sprite(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim)
{
    int x = r->x * ScreenWidth / 640 * 16;
    int y = r->y * ScreenHeight / 224 * 16;
    int w = r->w * ScreenWidth / 640 * 16;
    int h = r->h * ScreenHeight / 224 * 16;

    if (uv == 0) {
        gif_MakeSpriteNoTexture(x, y, w, h, z, col, prim);
    } else {
        GifRect t = *uv;

        t.x *= 16;
        t.y *= 16;
        t.w *= 16;
        t.h *= 16;
        gif_MakeSprite(x, y, w, h, z, &t, col, prim);
    }
}

void gif_SpriteOffset(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim)
{
    int x = r->x * ScreenWidth / 640 * 16;
    int y = r->y * ScreenHeight / 224 * 16;
    int w = r->w * ScreenWidth / 640 * 16;
    int h = r->h * ScreenHeight / 224 * 16;

    if (uv == 0) {
        gif_MakeSpriteNoTextureOffset(x, y, w, h, z, col, prim);
    } else {
        GifRect t = *uv;

        t.x *= 16;
        t.y *= 16;
        t.w *= 16;
        t.h *= 16;
        gif_MakeSpriteOffset(x, y, w, h, z, &t, col, prim);
    }
}

void gif_SpriteOrg(GifRect *r, long long z, GifRect *uv, GifColor *col, int prim)
{
    int x = r->x * 16;
    int y = r->y * 16;
    int w = r->w * 16;
    int h = r->h * 16;

    if (uv == 0) {
        gif_MakeSpriteNoTexture(x, y, w, h, z, col, prim);
    } else {
        GifRect t = *uv;

        t.x *= 16;
        t.y *= 16;
        t.w *= 16;
        t.h *= 16;
        gif_MakeSprite(x, y, w, h, z, &t, col, prim);
    }
}

int _IsInScreen(int *v)
{
    return isInScreen(v);
}
