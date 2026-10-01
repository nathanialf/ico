#include "sugiCommon.h"
#include "GsBase.h"
#include "darkVolume.h"
#include "gobj.h"
#include "obj_manager.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "tableSin.h"
#include <libvu0.h>
#include "Matrix.h"
#include "main.h"
#include "GifPacket.h"
#include "DmaPacket.h"

/* The TU's .data, in ROM run order (names ours): the centre the game-over
   dark volume and its shock ring spread from, and the position of the
   ordinary dark volume, both homogeneous points. */
static sceVu0FVECTOR gameOverCenter = {0.0f, 0.0f, 0.0f, 1.0f};

static sceVu0FVECTOR darkVolumeCenter = {0.0f, 0.0f, 0.0f, 1.0f};

/* The colour draw and drawHT take by value: four bytes in one register, which
   is why every call site masks the parameter home to 32 bits. */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} DVColor;

void draw(void *v, int n, DVColor col, int neg);
void drawHT(float *v, int n, DVColor col, int neg);

/* .sbss, owned by darkVolume.o (0x14, the run and MAIN.MAP's own size; MAIN.MAP
   names no symbol in it), in the ROM's run order, all drawHT's: the strip's
   vertex count, whose parity flips the edge, the previous vertex and the edge
   vector the next vertex is tested against (names ours). */
static int stripCount;

static float prevX;

static float prevY;

static float edgeX;

static float edgeY;

/* The TU's .sdata opens with draw and drawHT's state (MAIN.MAP names nothing in
   the run): the two strip halves' written flags, the half being filled, and the
   GS PRIM value the strips are drawn with. */
static int stripHalfDone[2] = {0, 0}; /* derived name */

static int stripHalf = 0; /* derived name */

static long stripPrim = 0x144; /* derived name */

/* listing line 80: project one object-space vertex through the VU0 matrix in
   vf4 to vf7, clamp it to the screen limits vf12 and vf13 carry and store the
   12.4 fixed point result. */
static __inline__ void projectVertex(void *dst, const void *src)
{
    __asm__ __volatile__("lqc2 $vf8, 0x0(%1)\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                         "vmaddw.xyzw $vf10, $vf7, $vf8w\n\t"
                         "vdiv Q, $vf0w, $vf10w\n\t"
                         "vwaitq\n\t"
                         "vmulq.xyz $vf10, $vf10, Q\n\t"
                         "vmaxx.xy $vf10, $vf10, $vf13x\n\t"
                         "vminix.xy $vf10, $vf10, $vf12x\n\t"
                         "vftoi4.xyzw $vf11, $vf10\n\t"
                         "sqc2 $vf11, 0x0(%0)"
                         :
                         : "r"(dst), "r"(src));
}

/* listing lines 153-173: emit one triangle strip of n projected vertices. */
static __inline__ void drawStrip(int *v, int n, DVColor col)
{
    int xy[4];
    int idx;

    gif_SetGsReg(0, stripPrim);
    gif_SetGsReg(1, (long)col.r | ((long)col.g << 8) | ((long)col.b << 16) | ((long)col.a << 24) |
                        ((long)0xFE00 << 46));
    stripHalfDone[1] = 0;
    stripHalfDone[0] = 0;
    stripHalf = 0;
    while (n-- != 0) {
        projectVertex(xy, v);
        if (stripHalfDone[0] != 0 && stripHalfDone[1] != 0) {
            gif_SetGsReg(5, (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32));
        } else {
            gif_SetGsReg(13, (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32));
        }
        idx = stripHalf;
        stripHalfDone[idx] = 1;
        stripHalf = ++idx & 1;
        v += 4;
    }
}

/* listing lines 176-182 */
void draw(void *v, int n, DVColor col, int neg)
{
    if (neg != 0) {
        drawStrip(v, n, col);
    } else {
        DVColor c = {-col.r, -col.g, -col.b, 128};

        drawStrip(v, n, c);
    }
}

/* one screen-space segment of the half-tone pass */
typedef struct {
    int on;
    int side;
    long long xy;
} DVSeg;

/* listing lines 190-203: one pass over the prepared segments, emitting the
   segments whose side flag is not the one this pass draws. */
static __inline__ void drawHalfStrip(DVSeg *b, unsigned int n, DVColor col, int side)
{
    gif_SetGsReg(0, stripPrim);
    gif_SetGsReg(1, (long)col.r | ((long)col.g << 8) | ((long)col.b << 16) | ((long)col.a << 24) |
                        ((long)0xFE00 << 46));
    while (n-- > 0) {
        if (b->on != 0 && b->side != side) {
            gif_SetGsReg(5, b->xy);
        } else {
            gif_SetGsReg(13, b->xy);
        }
        b++;
    }
}

/* listing lines 206-239 */
void drawHT(float *v, int n, DVColor col, int neg)
{
    DVSeg buf[n];
    DVSeg *p = buf;
    int xy[4];
    int i;
    int idx;

    stripHalfDone[1] = 0;
    stripHalfDone[0] = 0;
    stripHalf = 0;
    stripCount = 0;
    for (i = 0; i < n; i++, v += 4, p++) {
        projectVertex(xy, v);
        if (stripHalfDone[0] != 0 && stripHalfDone[1] != 0) {
            p->on = 1;
            p->side = 0.0f < edgeX * ((float)xy[1] - prevY) - edgeY * ((float)xy[0] - prevX);
        } else {
            p->on = 0;
            p->side = 0;
        }
        idx = stripHalf;
        stripHalfDone[idx] = 1;
        stripHalf = ++idx & 1;
        edgeX = (float)xy[0] - prevX;
        edgeY = (float)xy[1] - prevY;
        if (stripCount & 1) {
            edgeX = -edgeX;
            edgeY = -edgeY;
        }
        prevX = (float)xy[0];
        prevY = (float)xy[1];
        stripCount = stripCount + 1;
        p->xy = (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32);
    }
    {
        DVColor c = {-col.r, -col.g, -col.b, 128};

        if (neg != 0) {
            drawHalfStrip(buf, n, col, 1);
            drawHalfStrip(buf, n, c, 0);
        } else {
            drawHalfStrip(buf, n, c, 1);
            drawHalfStrip(buf, n, col, 0);
        }
    }
}

/* .bss, owned by darkVolume.o (0x13A0, the run and MAIN.MAP's own size,
   tiled exactly by these six), in the ROM's run order: one 136-float hatch row,
   the eight rows the volume is built from, and the four cosine and sine tables
   the ring is stepped with. */
/* */
static float hatchRow[136];

static float hatchRows[8 * 136];

static float cosB[8];

static float cosA[8];

static float sinB[8];

static float sinA[8];

extern int D_0028FF00[];
void _SetCurrentMatrix(void *m);

/* listing lines 62-65: load the VU0 screen clamp limits vmaxx and vminix read
   out of vf13 and vf12 in the projection block at line 80. */
static __inline__ void setScreenClamp(float hi, float lo)
{
    __asm__ __volatile__("mfc1 $8, %0\n\t"
                         "qmtc2.ni $8, $vf12\n\t"
                         "mfc1 $8, %1\n\t"
                         "qmtc2.ni $8, $vf13"
                         :
                         : "f"(hi), "f"(lo)
                         : "$8");
}

/* listing line 117: dst = base + v * s over xyz, keeping base's w. */
static __inline__ void addScaledVectorXYZ(void *dst, const void *base, const void *v, float s)
{
    __asm__ __volatile__("lqc2 $vf14, 0x0(%1)\n\t"
                         "lqc2 $vf15, 0x0(%2)\n\t"
                         "mfc1 $8, %3\n\t"
                         "qmtc2.ni $8, $vf16\n\t"
                         "vmulx.xyz $vf15, $vf15, $vf16x\n\t"
                         "vadd.xyz $vf14, $vf14, $vf15\n\t"
                         "sqc2 $vf14, 0x0(%0)"
                         :
                         : "r"(dst), "r"(base), "r"(v), "f"(s)
                         : "$8");
}

/* listing lines 242-293: project the view-space sphere around pos, splitting each
   of the 8 rings at the near plane. The first arm's counter is not read in its
   body, so loop.c reverses that loop and the ROM counts it down with bgez; the
   second and third read n and stay ascending. */
void renderViewCoordZSphere(void *pos, DVColor col, int neg, float r)
{
    float v[4];
    int i;
    int n;
    float *p;
    float *q;

    _ApplyMatrix(v, matrixptr + 0x80, pos);
    if (v[2] + r * cosA[0] < 1.0f) {
        return;
    }
    _SetCurrentMatrix(matrixptr + 0xC0);
    setScreenClamp(4095.0f, 0.0f);
    for (i = 0; i < 8; i++) {
        float z0 = v[2] + r * cosB[i];
        float z1 = v[2] + r * cosA[i];

        p = &hatchRows[i * 136];
        q = hatchRow;
        if (1.0f < z0) {
            for (n = 0; n < 34; n++, p += 4, q += 4) {
                addScaledVectorXYZ(q, v, p, r);
            }
            drawHT(hatchRow, 34, col, neg);
        } else {
            float t = (z1 - 1.0f) / (z1 - z0);

            for (n = 0; n < 34; n++, p += 4, q += 4) {
                addScaledVectorXYZ(q, v, p, r);
                if (n & 1) {
                    _InterVectorXYZ(q, q, q - 4, t);
                }
            }
            drawHT(hatchRow, 34, col, neg);
            q = hatchRow;
            for (n = 0; n < 34; n++, q += 4) {
                if (n & 1) {
                    CopyVector(q - 4, q);
                    CopyVector(q, v);
                    hatchRow[n * 4 + 2] = 1.0f;
                }
            }
            draw(hatchRow, 34, col, neg);
            return;
        }
    }
}

inline void ExecGameOverEffect(void) {}

/* WHAT THE BYTES PIN (PacketBufferStruct's union fields, DmaPacket.h): the
   open's gif = 0, end = 0 and ptr = c + 8 stores survive flow, and the
   screen-size load waits for the tag store. */
void dl_SetDLPriority(int a0);
void dl_OpenDma(int a0, int a1, int a2);
void dl_CloseDma(void);
void gif_EndPacket(void);

/* The packet writer's cursor check (our name and test), built only when
   DEBUG is defined; the retail build does not define it, so the preprocessor
   leaves the helper without a body, and each call still evaluates its
   argument into the parameter's copy, which is dead and emits no byte.
   RECONSTRUCTION. WHAT THE
   BYTES PIN: darkVolume's RTL at cse1's input is 57 to 74 insns longer, before
   the second packet's XYZ2 write at +272, than its statements give, all of it
   deleted by cse1 (cse.c 8739-8761 flushes its table every 1000 insns, and only
   a flush between that write's cursor load and the next write's address puts
   the tail on the ROM's c + 288 base); two insns per GS write (the argument's
   high/load pair, dead once cse1 forwards the cursor) is 64 there, and the
   check at the head of each packet open and close adds 8, 72 in all. In sonic
   the same check at the open and the close is what puts cse1's flush on the
   ROM's insn (UV1's cursor store in the second packet). WHAT THEY
   CANNOT PIN: that the developer's writer carried this check, its name, test
   or argument; any straight-line code of that size that cse1 deletes before
   that write, and that gives no load an earlier equivalent, gives the same
   bytes. */
static __inline__ void dvCheckPacket(char *p)
{
#ifdef DEBUG
    if (p < (char *)PacketBufferStruct.buf[PacketBufferStruct.cur]) {
        scePrintf("dark volume: packet cursor %p below its buffer\n", p);
    }
#endif
}

/* the GS-register writer: the listing gives each write the row of its call
   (sonic's rows 313, 314, 331 ...), not rows of its own, so it is a macro */
#define dvSetGsReg(reg, val)                                                                       \
    dvCheckPacket(PacketBufferStruct.ptr.c);                                                       \
    *PacketBufferStruct.ptr.d++ = (val);                                                           \
    *PacketBufferStruct.ptr.d++ = (reg)
/* FRAME_1, SCISSOR_1 and XYOFFSET_1 for a w by h buffer at base fbp, moved by
   ox, oy sixteenths (ico2/seki/src/Shadow.c's setFrame). A MACRO: the listing
   gives the three writes of each packet the rows of one call over three lines
   (442-444, 498-500), the write after it resuming on the next line */
#define dvSetFrame(fbp, w, h, ox, oy)                                                              \
    {                                                                                              \
        dvSetGsReg(0x4C, (fbp) | ((long long)(((w) >> 6) & 0x3F) << 16));                          \
        dvSetGsReg(0x40, ((long long)((w) - 1) << 16) | ((long long)((h) - 1) << 48));             \
        dvSetGsReg(0x18, (((long long)(2048 - (w) / 2) << 4) + (ox)) |                             \
                             ((((long long)(2048 - (h) / 2) << 4) + (oy)) << 32));                 \
    }
/* the packet open: every insn carries the row of its call (311, 347, 392) */
#define dvOpenPacket()                                                                             \
    {                                                                                              \
        char *c;                                                                                   \
                                                                                                   \
        dvCheckPacket(PacketBufferStruct.ptr.c);                                                   \
        c = PacketBufferStruct.ptr.c;                                                              \
        PacketBufferStruct.gif.c = 0;                                                              \
        PacketBufferStruct.end.c = 0;                                                              \
        PacketBufferStruct.dma.c = c;                                                              \
        PacketBufferStruct.tail.c = c;                                                             \
        PacketBufferStruct.ptr.c = c + 8;                                                          \
        *(unsigned int *)(c + 8) = 0x11000000;                                                     \
        PacketBufferStruct.gif.c = c + 0xC;                                                        \
        PacketBufferStruct.end.c = c + 0x10;                                                       \
        PacketBufferStruct.ptr.c = c + 0x18;                                                       \
        ((GifPkWord *)(c + 0x18))->d = 0xE;                                                        \
        PacketBufferStruct.ptr.c = c + 0x20;                                                       \
    }

/* sonic's three colours, one record each. The packet colours are const like
   darkVolume's: the ROM issues their byte loads above the packet stores through
   the cursor, which only an unchanging read allows (a char read aliases every
   store otherwise). The sphere colour is not: the ROM loads it again for the
   second renderViewCoordZSphere call, where a const load would be kept across
   the first call. */
static const DVColor sonicPacketColor = {0, 0, 0, 0}; /* derived name */

static DVColor sonicSphereColor = {255, 255, 255, 128}; /* derived name */

static const DVColor sonicRingColor = {0, 0, 0, 128}; /* derived name */

/* darkVolume's four colours, after sonic's in the TU's .sdata */
static const DVColor volumePacketColor = {0, 0, 0, 0}; /* derived name */

static const DVColor volumeEdgeColor = {128, 128, 128, 80}; /* derived name */

static const DVColor volumeOuterColor = {255, 255, 255, 128}; /* derived name */

static const DVColor volumeInnerColor = {127, 0, 98, 128}; /* derived name */

void sonic(void *pos, float t)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};
    int rect2[4] = {4, 4, ScreenWidth * 16, ScreenHeight * 16};

    dl_SetDLPriority(10);
    dvOpenPacket();
    dvSetFrame(0x140, ScreenWidth, ScreenHeight, 0, 0);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x49, 0);
    dvSetGsReg(0x42, 0x8000000044LL);
    dvSetGsReg(0x00, 0x406);
    dvSetGsReg(0x01, (long)sonicPacketColor.r | ((long)sonicPacketColor.g << 8) |
                         ((long)sonicPacketColor.b << 16) | ((long)sonicPacketColor.a << 24));
    dvSetGsReg(0x05,
               (long)(rect[0] + 0x8000) | ((long)(rect[1] + 0x8000) << 16) | 0xFFFFFFFF00000000LL);
    dvSetGsReg(0x05, (long)(rect[0] + 0x8000 + rect[2]) |
                         ((long)(rect[1] + 0x8000 + rect[3]) << 16) | 0xFFFFFFFF00000000LL);
    dvSetGsReg(0x4A, 0);
    dvSetGsReg(0x3B, 0x8000000080LL);
    dvSetGsReg(0x47, 0x50000);
    dvSetGsReg(0x42, 0x8000000068LL);
    dvSetGsReg(0x46, 0);
    {
        char *p;
        char *q;

        dvCheckPacket(PacketBufferStruct.ptr.c);
        ((GifPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
            (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
            0x6C008000;
        p = PacketBufferStruct.ptr.c;
        ((GifPkWord *)p)->w[0] = 0x15000000;
        p += 4;
        PacketBufferStruct.ptr.c = p;
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
        dl_OpenDma(5, (int)PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    gif_StartPacketPri(10);
    renderViewCoordZSphere(pos, sonicSphereColor, 1, (t + 50.0f) * 3.0f);
    renderViewCoordZSphere(pos, sonicSphereColor, 0, t * 2.5f);
    gif_EndPacket();
    dl_SetDLPriority(10);
    dvOpenPacket();
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x46, 1);
    dvSetGsReg(0x4A, 0);
    dvSetGsReg(0x3B, 0x8000008080LL);
    dvSetGsReg(0x14, 0x60);
    dvSetFrame(0x40, ScreenWidth, ScreenHeight, screenOffsetX, screenOffsetY);
    dvSetGsReg(0x42, 0x44);
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x06, 0x664122800LL);
    {
        int rect3[4] = {-ScreenWidth / 2 * 16 + 500, -ScreenHeight / 2 * 16 + 500,
                        ScreenWidth * 16 - 500, ScreenHeight * 16 - 500};

        dvSetGsReg(0x42, 0x8000000068LL);
        dvSetGsReg(0x00, 0x156);
        dvSetGsReg(0x01, (long)sonicRingColor.r | ((long)sonicRingColor.g << 8) |
                             ((long)sonicRingColor.b << 16) | ((long)sonicRingColor.a << 24));
        dvSetGsReg(0x03, (long)rect2[0] | ((long)rect2[1] << 16));
        dvSetGsReg(0x05, (long)(rect3[0] + 0x8000) | ((long)(rect3[1] + 0x8000) << 16) |
                             0xFFFFFFFF00000000LL);
        dvSetGsReg(0x03, (long)(rect2[0] + rect2[2]) | ((long)(rect2[1] + rect2[3]) << 16));
        dvSetGsReg(0x05, (long)(rect3[0] + 0x8000 + rect3[2]) |
                             ((long)(rect3[1] + 0x8000 + rect3[3]) << 16) | 0xFFFFFFFF00000000LL);
        dvSetGsReg(0x4E, 0x300000C0);
        dvSetGsReg(0x47, 0x50000);
    }
    {
        char *p;
        char *q;

        dvCheckPacket(PacketBufferStruct.ptr.c);
        ((GifPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
            (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
            0x6C008000;
        p = PacketBufferStruct.ptr.c;
        ((GifPkWord *)p)->w[0] = 0x15000000;
        p += 4;
        PacketBufferStruct.ptr.c = p;
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
        dl_OpenDma(5, (int)PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    dl_SetDLPriority(10);
    dvOpenPacket();
    {
        int rect4[4] = {504, 504, ScreenWidth * 16 - 500, ScreenHeight * 16 - 500};
        unsigned char v;
        float s = t * 3.0f;

        if (1000.0f < s) {
            v = 138;
        } else {
            v = s * -107.0f * 0.001f + 245.0f;
        }
        {
            DVColor c = {v, v + 10, v, 128};

            dvSetGsReg(0x46, 1);
            dvSetGsReg(0x4A, 0);
            dvSetFrame(0x40, ScreenWidth, ScreenHeight, screenOffsetX, screenOffsetY);
            dvSetGsReg(0x06, 0x664020800LL);
            dvSetGsReg(0x14, 0x60);
            dvSetGsReg(0x47, 0x33001);
            dvSetGsReg(0x4E, 0x1300000C0LL);
            dvSetGsReg(0x42, 0x44);
            dvSetGsReg(0x00, 0x156);
            dvSetGsReg(0x01, (long)c.r | ((long)c.g << 8) | ((long)c.b << 16) | ((long)c.a << 24));
            dvSetGsReg(0x03, (long)rect4[0] | ((long)rect4[1] << 16));
            dvSetGsReg(0x05, (long)(rect[0] + 0x8000) | ((long)(rect[1] + 0x8000) << 16) |
                                 0xFFFFFFFF00000000LL);
            dvSetGsReg(0x03, (long)(rect4[0] + rect4[2]) | ((long)(rect4[1] + rect4[3]) << 16));
            dvSetGsReg(0x05, (long)(rect[0] + 0x8000 + rect[2]) |
                                 ((long)(rect[1] + 0x8000 + rect[3]) << 16) | 0xFFFFFFFF00000000LL);
        }
    }
    {
        char *p;
        char *q;

        dvCheckPacket(PacketBufferStruct.ptr.c);
        ((GifPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
            (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
            0x6C008000;
        p = PacketBufferStruct.ptr.c;
        ((GifPkWord *)p)->w[0] = 0x15000000;
        p += 4;
        PacketBufferStruct.ptr.c = p;
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
        dl_OpenDma(5, (int)PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
}

void darkVolume(void *pos, float a1, float a2, float a3)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};
    int rect2[4] = {4, 4, ScreenWidth * 16, ScreenHeight * 16};

    dl_SetDLPriority(10);
    dvOpenPacket();
    dvSetFrame(0x140, ScreenWidth, ScreenHeight, 0, 0);
    dvSetGsReg(0x4A, 0);
    dvSetGsReg(0x3B, 0x8000000080LL);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x49, 0);
    dvSetGsReg(0x42, 0x8000000044LL);
    dvSetGsReg(0x00, 0x406);
    dvSetGsReg(0x01, (long)volumePacketColor.r | ((long)volumePacketColor.g << 8) |
                         ((long)volumePacketColor.b << 16) | ((long)volumePacketColor.a << 24));
    dvSetGsReg(0x05,
               (long)(rect[0] + 0x8000) | ((long)(rect[1] + 0x8000) << 16) | 0xFFFFFFFF00000000LL);
    dvSetGsReg(0x05, (long)(rect[0] + 0x8000 + rect[2]) |
                         ((long)(rect[1] + 0x8000 + rect[3]) << 16) | 0xFFFFFFFF00000000LL);
    dvSetGsReg(0x47, 0x50000);
    dvSetGsReg(0x42, 0x8000000068LL);
    dvSetGsReg(0x46, 0);
    {
        char *p;
        char *q;

        dvCheckPacket(PacketBufferStruct.ptr.c);
        ((GifPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
            (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
            0x6C008000;
        p = PacketBufferStruct.ptr.c;
        ((GifPkWord *)p)->w[0] = 0x15000000;
        p += 4;
        PacketBufferStruct.ptr.c = p;
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
        dl_OpenDma(5, (int)PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    gif_StartPacketPri(10);
    {
        DVColor c = {volumeOuterColor.r - volumeInnerColor.r - 1,
                     volumeOuterColor.g - volumeInnerColor.g - 1,
                     volumeOuterColor.b - volumeInnerColor.b - 1, 128};

        renderViewCoordZSphere(pos, volumeOuterColor, 1, a1 + a3);
        renderViewCoordZSphere(pos, volumeInnerColor, 0, a1 * a2 + a3 * 0.6666667f);
        renderViewCoordZSphere(pos, c, 0, a1 * a2 * a2);
        gif_EndPacket();
    }
    dl_SetDLPriority(10);
    dvOpenPacket();
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x46, 1);
    dvSetGsReg(0x4A, 0);
    dvSetGsReg(0x3B, 0x8000008080LL);
    dvSetGsReg(0x14, 0x60);
    dvSetFrame(0x1000040, ScreenWidth, ScreenHeight, screenOffsetX, screenOffsetY);
    dvSetGsReg(0x42, 0x44);
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x06, 0x664122800LL);
    dvSetGsReg(0x00, 0x156);
    dvSetGsReg(0x01, (long)volumeEdgeColor.r | ((long)volumeEdgeColor.g << 8) |
                         ((long)volumeEdgeColor.b << 16) | ((long)volumeEdgeColor.a << 24));
    dvSetGsReg(0x03, (long)rect2[0] | ((long)rect2[1] << 16));
    dvSetGsReg(0x05,
               (long)(rect[0] + 0x8000) | ((long)(rect[1] + 0x8000) << 16) | 0xFFFFFFFF00000000LL);
    dvSetGsReg(0x03, (long)(rect2[0] + rect2[2]) | ((long)(rect2[1] + rect2[3]) << 16));
    dvSetGsReg(0x05, (long)(rect[0] + 0x8000 + rect[2]) |
                         ((long)(rect[1] + 0x8000 + rect[3]) << 16) | 0xFFFFFFFF00000000LL);
    dvSetGsReg(0x4E, 0x300000C0);
    dvSetGsReg(0x47, 0x50000);
    {
        char *p;
        char *q;

        dvCheckPacket(PacketBufferStruct.ptr.c);
        ((GifPkWord *)PacketBufferStruct.end.c)->d =
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >>
                            4) -
                           1) |
            0x1000000000008000LL;
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
            (((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) << 16) |
            0x6C008000;
        p = PacketBufferStruct.ptr.c;
        ((GifPkWord *)p)->w[0] = 0x15000000;
        p += 4;
        PacketBufferStruct.ptr.c = p;
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
        dl_OpenDma(5, (int)PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
}

/* The rest of the TU's .sdata: the game-over effect's state and the ordinary
   dark volume's radius and target radius. */
static int gameOverActive = 0; /* derived name */

static float gameOverRadius = 0; /* derived name */

static int gameOverRing = 0; /* derived name */

static int gameOverQueen = 0; /* derived name */

static float gameOverSpeed = 25.0f; /* derived name */

static float darkVolumeRadius = 0; /* derived name */

static float darkVolumeTarget = 0; /* derived name */

/* listing lines 526-533: arm the game-over dark volume, shared by
   StartGameOverEffect and StartQueenAttackEffect */
static inline void setGameOverEffect(int a0, float t)
{
    gameOverActive = 1;
    gameOverRadius = 0;
    gameOverRing = 1;
    gameOverQueen = 0;
    CopyVector(gameOverCenter, a0);
    gameOverSpeed = t;
}

inline void StartGameOverEffect(int a0, float t)
{
    if (girlGObj != 0) {
        ExecuteSEPackage(girlGObj, 0x7A);
        ExecuteSEPackage(girlGObj, 0x7B);
        ExecuteSEPackage(girlGObj, 0x7C);
        ExecuteSEPackage(girlGObj, 0x7D);
        ExecuteSEPackage(girlGObj, 0x7E);
    }
    setGameOverEffect(a0, t);
}

inline void StartQueenAttackEffect(int a0, float t)
{
    setGameOverEffect(a0, t);
    gameOverQueen = 1;
    gameOverRing = 0;
}

inline void ResetGameOverEffect(void)
{
    gameOverActive = 0;
    gameOverRing = 0;
}

void SetDarkVolumeEffect(int a0, float a1)
{
    darkVolumeTarget = a1;
    CopyVector(darkVolumeCenter, (void *)a0);
}

/* listing lines 566-568: the per-object hit test, inlined at all three sites */
static inline void sendGameOverMail(void *gobj, float r2)
{
    float pos[4];

    GetRootPosition(pos, gobj);
    if (distance_squared(pos, gameOverCenter) < r2) {
        iosOmSendMail(gobj, 0x22, gobj);
    }
}

void DispGameOverEffect(void)
{
    void *g;

    if (gameOverActive != 0) {
        sonic(gameOverCenter, gameOverRadius);
        darkVolume(gameOverCenter, gameOverRadius, 1.0f, 30.0f);
        if (gameOverRing != 0) {
            float r2 = gameOverRadius * gameOverRadius;

            g = (void *)boyGObj;
            if (g != 0) {
                sendGameOverMail(g, r2);
            }
            for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
                sendGameOverMail(g, r2);
            }
            for (g = isysGObjSearchFromObjKindID_begin(62); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
                sendGameOverMail(g, r2);
            }
        }
        if (gameOverRadius < 50000.0f && systemStatus[5] == 0) {
            gameOverRadius = gameOverRadius + gameOverSpeed;
        }
    } else {
        if (darkVolumeTarget < 0.001f && darkVolumeRadius < 1.0f) {
            return;
        }
        darkVolume(darkVolumeCenter, darkVolumeRadius, 0.96f, 0.0f);
        if (systemStatus[5] != 0) {
            return;
        }
        darkVolumeRadius = darkVolumeRadius + (darkVolumeTarget - darkVolumeRadius) * 0.3f;
        darkVolumeTarget = 0.0f;
    }
}

void GetGameOverEffectCenterPosition(int a0)
{
    CopyVector(a0, gameOverCenter);
}

/* listing lines 647-676: build the 8 by 17 sphere vertex table renderViewCoordZSphere
   walks 34 vectors at a time, then reset the effect state. Each entry is the pair
   of vectors for ring i and ring i+1, so the row holds 17 pairs of 8 floats and the
   ring stride is 136 floats. Angles are the 16 bit binary turn the sin and cos
   tables take, 0x1000 per step. */
void InitGameOverEffect(void)
{
    int i;
    int j;
    float ca;
    float sa;
    float cb;
    float sb;

    for (i = 0; i < 8; i++) {
        short a = i * 0x1000;
        short b = (i + 1) * 0x1000;

        ca = GetTableCos(a);
        sa = GetTableSin(a);
        cb = GetTableCos(b);
        sb = GetTableSin(b);
        cosA[i] = ca;
        cosB[i] = cb;
        sinA[i] = sa;
        sinB[i] = sb;
        for (j = 0; j < 17; j++) {
            float *p = &hatchRows[i * 136 + j * 8];
            float *q = p + 4;
            short k = j * 0x1000;
            float s = GetTableSin(k);
            float c = GetTableCos(k);

            p[0] = sa * s;
            p[1] = sa * c;
            p[2] = ca;
            p[3] = 1.0f;
            q[0] = sb * s;
            q[1] = sb * c;
            q[2] = cb;
            q[3] = 1.0f;
        }
    }
    ResetGameOverEffect();
    darkVolumeRadius = 0;
    darkVolumeTarget = 0;
    CopyVector(darkVolumeCenter, ZeroPoint);
}

inline int InitDarkVolumeGeo(char *a0)
{
    **(int **)(*(char **)(a0 + 0x15C) + 0xC) = 0;
    return 0;
}

void SetupDarkVolume(void *a0, float a1, float a2)
{
    darkVolume(a0, a1, 1.0f, a2);
}

void DarkVolumeGeo(char *a0)
{
    float *p;

    GOBJ_SUB(a0)->f_74 = 0;
    p = (float *)GOBJ_SUB(a0)->f_C;
    if (1e-05f < *p) {
        SetupDarkVolume((char *)p + 0x30, *p * 50.0f, 10.0f);
    }
}

inline void DarkVolumeDL(void) {}
