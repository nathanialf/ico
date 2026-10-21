#include "typedef.h"
#include "GifPacket.h"
#include "GsBase.h"
#include "DmaPacket.h"
#include "DisplayList.h"
#include "include_asm.h"

typedef struct { /* field names derived */
    int a, b, c, d;
} GsAlphaEnt; /* derived name */

/* The display-list packet builder state.  `ptr` is the write cursor; `dma`,
   `tail`, `gif` and `end` are the back-pointers into the packet that
   gif_EndPacket patches once the packet's size is known (DMA tag, source
   chain tail, VIF DIRECT code and GIF tag respectively). */

/* One 64-bit slot of a DMA/GIF packet: written either as the whole qword
   (DMA tag, GIF tag, A+D data) or as one of its two 32-bit halves. */

/* one A+D register write, which gif_SetGsReg and most of this file inline */
static inline void setGsReg(long long reg, long long data) /* derived name */
{
    *PacketBufferStruct.ptr.d++ = data;
    *PacketBufferStruct.ptr.d++ = reg;
}

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

INCLUDE_ASM(gif_StartPacketPri);

/* the open-packet flag gif_EndPacket clears, then the strip drawers' last two on-screen
   flags and the index of the older one. */
static int packetOpen = 0; /* derived name */

INCLUDE_ASM(gif_EndPacket);

INCLUDE_ASM(gif_SetGsReg);

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

INCLUDE_ASM(gif_StartPacketPriPath1);

INCLUDE_ASM(gif_EndPacketPath1);

INCLUDE_ASM(func_0010FF68);

INCLUDE_ASM(func_00110010);

INCLUDE_ASM(gif_MakeLine2D);

INCLUDE_ASM(func_001101C0);

INCLUDE_ASM(gif_MakeSpriteNoTexture);

INCLUDE_ASM(func_001103D0);

INCLUDE_ASM(func_00110508);

INCLUDE_ASM(func_00110628);

INCLUDE_ASM(func_00110798);

void gif_MakeLine2DOffset(int *v0, int *v1, long long z0, long long z1, unsigned char *col,
                          int prim);

void gif_MakeSprite(int x, int y, int w, int h, long long z, GifRect *uv, GifColor *col, int prim);

void gif_MakeSpriteOffset(int x, int y, int w, int h, long long z, GifRect *uv, GifColor *col,
                          int prim);

/* a point at an offset position, which gif_MakePoint2DOffset and
   gif_PointOffset inline */
static inline void makePoint2DOffset(int *v, long long z, unsigned char *col,
                                     int prim) /* derived name */
{
    setGsReg(0x00, 0x100 | ((long long)prim << 6));
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZOFF(v, z));
}

/* a two-point line, which gif_MakeLine2D and gif_Line inline */
static inline void makeLine2D(int *v0, int *v1, long long z0, long long z1, unsigned char *col,
                              int prim) /* derived name */
{
    setGsReg(0x00, ((long long)prim << 6) | 0xA);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZ(v0, z0));
    setGsReg(0x05, GIF_XYZ(v1, z1));
}

/* an untextured sprite, which gif_MakeSpriteNoTexture and the Sprite
   wrappers inline; gif_MakeSprite stays a call */
static inline void makeSpriteNoTexture(int x, int y, int w, int h, long long z, GifColor *col,
                                       int prim) /* derived name */
{
    int fx = w + 0x8000;
    int fy = h + 0x8000;

    setGsReg(0x00, (prim << 6) | 0x406);
    setGsReg(0x01, GIF_COLOR(col));
    setGsReg(0x05, GIF_XY(x, y, z));
    setGsReg(0x05, GIF_XY0(x + fx, y + fy, z));
}

/* an untextured sprite at an offset position, which
   gif_MakeSpriteNoTextureOffset and the offset Sprite wrappers inline */
static inline void makeSpriteNoTextureOffset(int x, int y, int w, int h, long long z, GifColor *col,
                                             int prim) /* derived name */
{
    setGsReg(0x00, (prim << 6) | 0x406);
    setGsReg(0x01, GIF_COLOR(col));
    setGsReg(0x05, GIF_XY0(GIF_OX + x, GIF_OY + y, z));
    setGsReg(0x05, GIF_XY0(GIF_OX + x + w, GIF_OY + y + h, z));
}

INCLUDE_ASM(gif_SpriteSensitive);

INCLUDE_ASM(gif_SpriteSensitiveOffset);

INCLUDE_ASM(gif_SpriteSensitiveOrg);

INCLUDE_ASM(gif_SetAlpha);

INCLUDE_ASM(func_00110B50);

INCLUDE_ASM(gif_SetDrawEnviroment);

INCLUDE_ASM(gif_SetZTest);

INCLUDE_ASM(gif_SetZWrite);

INCLUDE_ASM(func_00110D90);

static int stripVisible[2] = {0, 0}; /* derived name */

static int stripIndex = 0; /* derived name */

/* the on-screen test of a projected vertex, which the strip and polygon
   functions and _IsInScreen further down this file inline */
static inline int isInScreen(volatile int *p) /* derived name */
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
static inline void rotTransPers(volatile int *dst, void *src) /* derived name */
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

INCLUDE_ASM(gif_DrawPolyF4);

INCLUDE_ASM(gif_DrawStripF);

INCLUDE_ASM(func_00111298);

INCLUDE_ASM(gif_Draw2DStripG);

INCLUDE_ASM(func_00111608);

void gif_Init(void)
{
    packetOpen = 0;
}

/* DisplayList.h is not included: this file's uses of dl_OpenDma do not fit
 * its prototype there */

int gif_CheckOpen(void)
{
    return packetOpen;
}

INCLUDE_ASM(func_001117E8);

INCLUDE_ASM(gif_PointOffset);

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

/* a point, which gif_MakePoint2D, gif_Point and the rest of the point
   family inline */
static inline void makePoint2D(int *v, long long z, unsigned char *col,
                               long long prim) /* derived name */
{
    setGsReg(0x00, (prim << 6) | 0x100);
    setGsReg(0x01, GIF_RGBA(col));
    setGsReg(0x05, GIF_XYZ(v, z));
}

INCLUDE_ASM(gif_LineOffset);

INCLUDE_ASM(gif_Sprite);

INCLUDE_ASM(gif_MoveImage);

INCLUDE_ASM(gif_SetHalfOffset);

INCLUDE_ASM(_IsInScreen);
