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
#include "DisplayList.h"

#ifdef VERSION_JUN26
#include "Primitive.h"

/* .bss in this build: one 136-float hatch row, the centre the game-over dark
   volume and its shock ring spread from (uninitialised: the object has no
   .data), the sixteen rows the volume is built from, and the four 16-entry
   cosine and sine tables the ring is stepped with (0x754E60, 0x755080,
   0x755090, 0x757290..0x757390; no position for the ordinary dark volume) */
static float hatchRow[136]; /* derived name */

static sceVu0FVECTOR gameOverCenter; /* derived name */

static float hatchRows[16 * 136]; /* derived name */

static float cosB[16]; /* derived name */

static float cosA[16]; /* derived name */

static float sinB[16]; /* derived name */

static float sinA[16]; /* derived name */
#else
/* the centre the game-over dark volume and its shock ring spread from, and
   the position of the ordinary dark volume, both homogeneous points */
static sceVu0FVECTOR gameOverCenter = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */

static sceVu0FVECTOR darkVolumeCenter = {0.0f, 0.0f, 0.0f, 1.0f}; /* derived name */
#endif

/* the colour draw and drawHT take by value: four bytes in one register */
typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} DVColor; /* derived name */

#ifdef VERSION_JUN26
/* the screen grid's mesh, never set in this build, then drawHT's state: the
   strip's vertex count, whose parity flips the edge, the previous vertex and
   the edge vector the next vertex is tested against */
static Mesh3D *gridMesh; /* derived name */
#else
static void draw(void *v, int n, DVColor col, int neg);
static void drawHT(float *v, int n, DVColor col, int neg);
#endif

/* drawHT's state: the strip's vertex count, whose parity flips the edge,
   the previous vertex and the edge vector the next vertex is tested
   against */
static int stripCount; /* derived name */

static float prevX; /* derived name */

static float prevY; /* derived name */

static float edgeX; /* derived name */

static float edgeY; /* derived name */

#ifdef VERSION_JUN26
/* the screen grid's turn and frame count */
static short gridTurn = 0; /* derived name */

static int gridCount = 0; /* derived name */
/* draw and drawHT's state: the two strip halves' written flags and the half
   being filled */
#else
/* draw and drawHT's state: the two strip halves' written flags, the half
   being filled, and the GS PRIM value the strips are drawn with */
#endif

static int stripHalfDone[2] = {0, 0}; /* derived name */

static int stripHalf = 0; /* derived name */

#ifdef VERSION_JUN26
/* a 30 by 30 grid round the game-over centre, its texture coordinates the
   screen positions of its vertices; nothing calls it in this build */
static void dispGameOverGrid(void) /* derived name */
{
    sceVu0FVECTOR origin = {2048.0f, 2048.0f, 0.0f, 0.0f};
    Mesh3D *mesh = gridMesh;
    float *scr = (float *)(matrixptr + 768);
    float *tmp = (float *)(matrixptr + 1024);
    float invW = 1.0f / ScreenWidth;
    float invH = 1.0f / ScreenHeight;
    float *center = (float *)(matrixptr + 832);
    float *offset = (float *)(matrixptr + 896);
    float *d = (float *)(matrixptr + 960);
    float size;
    float q;
    int i;
    int j;
    Prim3DVec *p;
    Prim3DVec *st;

    if (gridCount < 500) {
        size = gridCount / 10.0f;
    } else {
        size = 0.0f;
    }
    if (1000 < gridCount) {
        gridCount = 0;
    }
    gridCount++;
    gridTurn -= 1.0f;
    CopyVector(center, gameOverCenter);
    CopyVector(offset, origin);
    CopyVector(d, ZeroVector);
    _InitCurrentMatrix();
    _SetCurrentMatrix(matrixptr + 256);
    for (i = 0; i < 30; i++) {
        p = &mesh->pos[i * 30];
        st = &mesh->st[i * 30];
        d[0] = (i - 15) * size;
        for (j = 0; j < 30; j++, p++, st++) {
            float height = 0.0f;

            d[1] = height;
            d[2] = (j - 15) * size;
            _AddVector(p, center, d);
            _ApplyCurrentMatrix(scr, p);
            q = 1.0f / scr[3];
            _ScaleVector(tmp, scr, q);
            _SubVector(scr, tmp, offset);
            st->x = scr[0] * invW + 0.5f + q * 0.0f + invW * 0.5f;
            st->y = scr[1] * invH + 0.5f + q * 0.0f;
        }
    }
    prim_UpdateMesh3D(mesh, 9, buffer_ID);
}

/* Build the 16 by 17 sphere vertex table renderViewCoordZSphere walks 34
   vectors at a time, then clear the effect's centre.  Each entry is the pair
   of vectors for ring i and ring i+1, so the row holds 17 pairs of 8 floats
   and the ring stride is 136 floats.  Angles are the 16 bit binary turn the
   sin and cos tables take, 0x800 a ring and 0x1000 a step round it. */
void InitGameOverEffect(void)
{
    int i;
    int j;
    float ca;
    float sa;
    float cb;
    float sb;

    for (i = 0; i < 16; i++) {
        short a = i * 0x800;
        short b = (i + 1) * 0x800;

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
    CopyVector(gameOverCenter, ZeroPoint);
}

/* clamp a screen position's x and y to 0..4095 */
inline void ClampScreenPosition(float *dst, float *src) /* derived name */
{
    if (src[0] < 0.0f) {
        dst[0] = 0.0f;
    }
    if (4095.0f < src[0]) {
        dst[0] = 4095.0f;
    }
    if (src[1] < 0.0f) {
        dst[1] = 0.0f;
    }
    if (4095.0f < src[1]) {
        dst[1] = 4095.0f;
    }
}

/* project one object-space vertex through the VU0 matrix in vf4 to vf7 */
static __inline__ void projectVertex(void *dst, const void *src) /* derived name */
{
    __asm__ __volatile__("lqc2 $vf8, 0x0(%1)\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                         "vmaddw.xyzw $vf10, $vf7, $vf8w\n\t"
                         "vdiv Q, $vf0w, $vf10w\n\t"
                         "vwaitq\n\t"
                         "vmulq.xyz $vf10, $vf10, Q\n\t"
                         "sqc2 $vf10, 0x0(%0)"
                         :
                         : "r"(dst), "r"(src));
}
#else
static long stripPrim = 0x144; /* derived name */

/* project one object-space vertex through the VU0 matrix in vf4 to vf7,
   clamp it to the screen limits vf12 and vf13 carry and store the 12.4 fixed
   point result */
static __inline__ void projectVertex(void *dst, const void *src) /* derived name */
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
#endif

#ifdef VERSION_JUN26
/* project a vertex to the 12.4 screen position the strip takes, clamped
   to the GS window; nonzero when it falls on the screen */
static __inline__ int projectToScreen(int *xy, float *v) /* derived name */
{
    float f[4];

    projectVertex(f, v);
    ClampScreenPosition(f, f);
    _FTOI4Vector(xy, f);
    return _IsInScreen(xy);
}

/* emit one triangle strip of n vertices, the ones off the screen not
   closing a triangle */
static void draw(float *v, DVColor col, int n, int abe)
{
    int xy[4];
    int i;
    int in;
    int idx;

    stripHalfDone[1] = 0;
    stripHalfDone[0] = 0;
    stripHalf = 0;
    gif_SetGsReg(0, ((long)abe << 6) | 260);
    gif_SetGsReg(1, (long)col.r | ((long)col.g << 8) | ((long)col.b << 16) | ((long)col.a << 24) |
                        ((long)0xFE00 << 46));
    for (i = 0; i < n; i++, v += 4) {
        in = projectToScreen(xy, v);
        if (in != 0 && stripHalfDone[0] != 0 && stripHalfDone[1] != 0) {
            gif_SetGsReg(5, (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32));
        } else {
            gif_SetGsReg(13, (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32));
        }
        idx = stripHalf;
        stripHalfDone[idx] = in;
        stripHalf = ++idx & 1;
    }
}
#else
/* emit one triangle strip of n projected vertices */
static __inline__ void drawStrip(int *v, int n, DVColor col) /* derived name */
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
#endif

#ifdef VERSION_JUN26
/* the same strip, a triangle drawn only when its winding is the one side
   asks for */
static void drawHT(float *v, DVColor col, int n, int abe, int side)
{
    int xy[4];
    int i;
    int in;
    int idx;

    stripHalfDone[1] = 0;
    stripHalfDone[0] = 0;
    stripHalf = 0;
    stripCount = 0;
    gif_SetGsReg(0, ((long)abe << 6) | 260);
    gif_SetGsReg(1, (long)col.r | ((long)col.g << 8) | ((long)col.b << 16) | ((long)col.a << 24) |
                        ((long)0xFE00 << 46));
    for (i = 0; i < n; i++, v += 4) {
        in = projectToScreen(xy, v);
        if (in != 0 && stripHalfDone[0] != 0 && stripHalfDone[1] != 0) {
            if ((side & 1) ^
                (0.0f < edgeX * ((float)xy[1] - prevY) - edgeY * ((float)xy[0] - prevX))) {
                gif_SetGsReg(5, (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32));
            } else {
                gif_SetGsReg(13, (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32));
            }
        } else {
            gif_SetGsReg(13, (long)xy[0] | ((long)xy[1] << 16) | ((long)xy[2] << 32));
        }
        idx = stripHalf;
        stripHalfDone[idx] = in;
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
    }
}
#else
static void draw(void *v, int n, DVColor col, int neg)
{
    if (neg != 0) {
        drawStrip(v, n, col);
    } else {
        DVColor c = {-col.r, -col.g, -col.b, 128};

        drawStrip(v, n, c);
    }
}

/* one screen-space segment of the half-tone pass */
typedef struct { /* field names derived */
    int on;
    int side;
    long long xy;
} DVSeg; /* derived name */

/* one pass over the prepared segments, emitting the segments whose side
   flag is not the one this pass draws */
static __inline__ void drawHalfStrip(DVSeg *b, unsigned int n, DVColor col,
                                     int side) /* derived name */
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

static void drawHT(float *v, int n, DVColor col, int neg)
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
#endif

#ifdef VERSION_JUN26
/* drawHT in the colour, or in its complement when neg is the side drawn */
static __inline__ void drawSide(float *v, int n, DVColor col, int neg, int side) /* derived name */
{
    if (side != neg) {
        drawHT(v, col, n, 1, side);
    } else {
        DVColor c = {-col.r, -col.g, -col.b, 128};

        drawHT(v, c, n, 1, side);
    }
}
#else
/* one 136-float hatch row, the eight rows the volume is built from, and the
   four cosine and sine tables the ring is stepped with */
static float hatchRow[136]; /* derived name */

static float hatchRows[8 * 136]; /* derived name */

static float cosB[8]; /* derived name */

static float cosA[8]; /* derived name */

static float sinB[8]; /* derived name */

static float sinA[8]; /* derived name */

/* load the VU0 screen clamp limits vmaxx and vminix read out of vf13 and
   vf12 in projectVertex */
static __inline__ void setScreenClamp(float hi, float lo) /* derived name */
{
    __asm__ __volatile__("mfc1 $8, %0\n\t"
                         "qmtc2.ni $8, $vf12\n\t"
                         "mfc1 $8, %1\n\t"
                         "qmtc2.ni $8, $vf13"
                         :
                         : "f"(hi), "f"(lo)
                         : "$8");
}
#endif

#ifdef VERSION_JUN26
/* draw in the colour, or in its complement when neg is set */
static __inline__ void drawCut(float *v, int n, DVColor col, int neg) /* derived name */
{
    if (neg != 0) {
        DVColor c = {-col.r, -col.g, -col.b, 128};

        draw(v, c, n, 1);
    } else {
        draw(v, col, n, 1);
    }
}
#else
/* dst = base + v * s over xyz, keeping base's w */
static __inline__ void addScaledVectorXYZ(void *dst, const void *base, const void *v,
                                          float s) /* derived name */
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
#endif

#ifdef VERSION_JUN26
/* project the view-space sphere around pos, ring by ring; the ring that
   crosses the near plane is cut there, its cut edge drawn as a strip of its
   own on the side that faces the camera, and ends the sphere */
static void renderViewCoordZSphere(void *pos, DVColor col, int neg, int side, float r)
{
    float v[4];
    float t[4];
    int i;
    int n;

    _ApplyMatrix(v, matrixptr + 0x80, pos);
    if (v[2] + r * cosA[0] < 100.0f) {
        return;
    }
    _SetCurrentMatrix(matrixptr + 0xC0);
    for (i = 0; i < 16; i++) {
        float z0 = v[2] + r * cosB[i];
        float z1 = v[2] + r * cosA[i];

        if (100.0f < z0) {
            for (n = 0; n < 34; n++) {
                _ScaleVectorXYZ(t, &hatchRows[i * 136 + n * 4], r);
                _AddVectorXYZ(&hatchRow[n * 4], v, t);
            }
            drawSide(hatchRow, 34, col, neg, side);
        } else {
            float s = (z1 - 100.0f) / (z1 - z0);
            float w[4];

            for (n = 0; n < 34; n++) {
                _ScaleVectorXYZ(w, &hatchRows[i * 136 + n * 4], r);
                _AddVectorXYZ(&hatchRow[n * 4], v, w);
                if (n & 1) {
                    _InterVector(&hatchRow[n * 4], &hatchRow[n * 4], &hatchRow[(n - 1) * 4], s);
                }
            }
            drawSide(hatchRow, 34, col, neg, side);
            if (side != 0) {
                float e[4];

                for (n = 0; n < 34; n++) {
                    _ScaleVectorXYZ(e, &hatchRows[i * 136 + n * 4], r);
                    _AddVectorXYZ(&hatchRow[n * 4], v, e);
                    if (n & 1) {
                        _InterVector(&hatchRow[(n - 1) * 4], &hatchRow[n * 4],
                                     &hatchRow[(n - 1) * 4], s);
                        CopyVector(&hatchRow[n * 4], v);
                        hatchRow[n * 4 + 2] = 100.0f;
                    }
                }
                drawCut(hatchRow, 34, col, neg);
            }
            return;
        }
    }
}
#else
/* project the view-space sphere around pos, splitting each of the 8 rings
   at the near plane */
static void renderViewCoordZSphere(void *pos, DVColor col, int neg, float r)
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
#endif

/* the packet writer's cursor check, built only when DEBUG is defined */
static __inline__ void dvCheckPacket(char *p) /* derived name */
{
#ifdef DEBUG
    if (p < (char *)PacketBufferStruct.buf[PacketBufferStruct.cur]) {
        scePrintf("dark volume: packet cursor %p below its buffer\n", p);
    }
#endif
}

/* the GS-register writer, a macro */
#ifdef VERSION_JUN26
#define dvSetGsReg(reg, val) /* derived name */                                                    \
    dvCheckPacket(PacketBufferStruct.ptr.c);                                                       \
    *PacketBufferStruct.ptr.d++ = (val);                                                           \
    *PacketBufferStruct.ptr.d++ = (reg)
/* FRAME_1, SCISSOR_1 and XYOFFSET_1 for a w by h buffer at base fbp, the
   window centred on the GS's 2048.0 origin (ico2/seki/src/Shadow.c's setFrame) */
#define dvSetFrame(fbp, w, h) /* derived name */                                                   \
    {                                                                                              \
        dvSetGsReg(0x4C, (fbp) | ((long long)(((w) >> 6) & 0x3F) << 16));                          \
        dvSetGsReg(0x40, ((long long)((w) - 1) << 16) | ((long long)((h) - 1) << 48));             \
        dvSetGsReg(0x18,                                                                           \
                   ((2048 - (long long)((w) / 2)) << 4) | ((2048 - (long long)((h) / 2)) << 36));  \
    }
/* RGBAQ packed from a colour record */
#define dvRGBA(c) /* derived name */                                                               \
    ((long)(c).r | ((long)(c).g << 8) | ((long)(c).b << 16) | ((long)(c).a << 24))
/* the untextured sprite: PRIM, RGBAQ and the two XYZ2 corners of the rect r
   (x, y, w, h in sixteenths), the far corner x + fx with fx = w + 0x8000 */
#define dvSpriteRect(r, col, prim) /* derived name */                                              \
    {                                                                                              \
        dvCheckPacket(PacketBufferStruct.ptr.c);                                                   \
        dvSetGsReg(0x00, prim);                                                                    \
        dvSetGsReg(0x01, dvRGBA(col));                                                             \
        dvSetGsReg(0x05, (long)((r)[0] + 0x8000) | ((long)((r)[1] + 0x8000) << 16) |               \
                             0xFFFFFFFF00000000LL);                                                \
        {                                                                                          \
            int fx = (r)[2] + 0x8000;                                                              \
            int fy = (r)[3] + 0x8000;                                                              \
                                                                                                   \
            dvSetGsReg(0x05,                                                                       \
                       (long)((r)[0] + fx) | ((long)((r)[1] + fy) << 16) | 0xFFFFFFFF00000000LL);  \
        }                                                                                          \
    }
/* the textured sprite: PRIM, RGBAQ, then a UV and an XYZ2 for each corner */
#define dvSpriteUV(r, uv, col, prim) /* derived name */                                            \
    {                                                                                              \
        dvCheckPacket(PacketBufferStruct.ptr.c);                                                   \
        dvSetGsReg(0x00, prim);                                                                    \
        dvSetGsReg(0x01, dvRGBA(col));                                                             \
        dvSetGsReg(0x03, (long)(uv)[0] | ((long)(uv)[1] << 16));                                   \
        dvSetGsReg(0x05, (long)((r)[0] + 0x8000) | ((long)((r)[1] + 0x8000) << 16) |               \
                             0xFFFFFFFF00000000LL);                                                \
        dvSetGsReg(0x03, (long)((uv)[0] + (uv)[2]) | ((long)((uv)[1] + (uv)[3]) << 16));           \
        {                                                                                          \
            int fx = (r)[2] + 0x8000;                                                              \
            int fy = (r)[3] + 0x8000;                                                              \
                                                                                                   \
            dvSetGsReg(0x05,                                                                       \
                       (long)((r)[0] + fx) | ((long)((r)[1] + fy) << 16) | 0xFFFFFFFF00000000LL);  \
        }                                                                                          \
    }
#else
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
#define dvSetGsReg(reg, val) /* derived name */                                                    \
    dvCheckPacket(PacketBufferStruct.ptr.c);                                                       \
    *PacketBufferStruct.ptr.d++ = (val);                                                           \
    *PacketBufferStruct.ptr.d++ = (reg)
/* FRAME_1, SCISSOR_1 and XYOFFSET_1 for a w by h buffer at base fbp, the
   window centred on the GS's 2048.0 origin (ico2/seki/src/Shadow.c's setFrame) */
#define dvSetFrame(fbp, w, h) /* derived name */                                                   \
    {                                                                                              \
        dvSetGsReg(0x4C, (fbp) | ((long long)(((w) >> 6) & 0x3F) << 16));                          \
        dvSetGsReg(0x40, ((long long)((w) - 1) << 16) | ((long long)((h) - 1) << 48));             \
        dvSetGsReg(0x18,                                                                           \
                   ((2048 - (long long)((w) / 2)) << 4) | ((2048 - (long long)((h) / 2)) << 36));  \
    }
#else
#define dvSetGsReg(reg, val) /* derived name */                                                    \
    dvCheckPacket(PacketBufferStruct.ptr.c);                                                       \
    *PacketBufferStruct.ptr.d++ = (val);                                                           \
    *PacketBufferStruct.ptr.d++ = (reg)
/* FRAME_1, SCISSOR_1 and XYOFFSET_1 for a w by h buffer at base fbp, moved
   by ox, oy sixteenths (ico2/seki/src/Shadow.c's setFrame) */
#define dvSetFrame(fbp, w, h, ox, oy) /* derived name */                                           \
    {                                                                                              \
        dvSetGsReg(0x4C, (fbp) | ((long long)(((w) >> 6) & 0x3F) << 16));                          \
        dvSetGsReg(0x40, ((long long)((w) - 1) << 16) | ((long long)((h) - 1) << 48));             \
        dvSetGsReg(0x18, (((long long)(2048 - (w) / 2) << 4) + (ox)) |                             \
                             ((((long long)(2048 - (h) / 2) << 4) + (oy)) << 32));                 \
    }
#endif
#endif

/* the packet open: every insn carries the row of its call (311, 347, 392) */
#define dvOpenPacket() /* derived name */                                                          \
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

/* sonic's three colours, one record each; the packet colours are const like
   darkVolume's, the sphere colour is not */
static const DVColor sonicPacketColor = {0, 0, 0, 0}; /* derived name */

#ifdef VERSION_JUN26
static DVColor sonicGreyColor = {128, 128, 128, 128}; /* derived name */
#endif

static DVColor sonicSphereColor = {255, 255, 255, 128}; /* derived name */

static const DVColor sonicRingColor = {0, 0, 0, 128}; /* derived name */

#ifdef VERSION_JUN26
static const DVColor sonicFadeColor = {138, 138, 138, 128}; /* derived name */
#endif

/* darkVolume's four colours */
static const DVColor volumePacketColor = {0, 0, 0, 0}; /* derived name */

static const DVColor volumeEdgeColor = {128, 128, 128, 80}; /* derived name */

static const DVColor volumeOuterColor = {255, 255, 255, 128}; /* derived name */

static const DVColor volumeInnerColor = {127, 0, 98, 128}; /* derived name */

static void sonic(void *pos, float t)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};
    int rect2[4] = {4, 4, ScreenWidth * 16, ScreenHeight * 16};

#ifdef VERSION_JUN26
    dl_SetDLPriority(12);
    dvOpenPacket();
    dvSetFrame(0x140, ScreenWidth, ScreenHeight);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x47, 0x30000);
    dvSpriteRect(rect, sonicPacketColor, 0x406);
#else
    dl_SetDLPriority(10);
    dvOpenPacket();
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
    dvSetFrame(0x140, ScreenWidth, ScreenHeight);
#else
    dvSetFrame(0x140, ScreenWidth, ScreenHeight, 0, 0);
#endif
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
#endif
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
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
#ifdef VERSION_JUN26
    gif_StartPacketPri(12);
    renderViewCoordZSphere(pos, sonicSphereColor, 0, 1, (t + 100.0f) * 3.0f);
    renderViewCoordZSphere(pos, sonicSphereColor, 0, 0, (t + 100.0f) * 3.0f);
    renderViewCoordZSphere(pos, sonicSphereColor, 1, 0, t * 3.0f);
    renderViewCoordZSphere(pos, sonicSphereColor, 1, 1, t * 3.0f);
    gif_EndPacket();
    dl_SetDLPriority(12);
#else
    gif_StartPacketPri(10);
    renderViewCoordZSphere(pos, sonicSphereColor, 1, (t + 50.0f) * 3.0f);
    renderViewCoordZSphere(pos, sonicSphereColor, 0, t * 2.5f);
    gif_EndPacket();
    dl_SetDLPriority(10);
#endif
    dvOpenPacket();
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x46, 1);
    dvSetGsReg(0x4A, 0);
    dvSetGsReg(0x3B, 0x8000008080LL);
    dvSetGsReg(0x14, 0x60);
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    dvSetFrame(0x40, ScreenWidth, ScreenHeight);
#else
    dvSetFrame(0x40, ScreenWidth, ScreenHeight, screenOffsetX, screenOffsetY);
#endif
    dvSetGsReg(0x42, 0x44);
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x06, 0x664122800LL);
    {
#ifdef VERSION_JUN26
        int rect3[4] = {-ScreenWidth / 2 * 16 + 1000, -ScreenHeight / 2 * 16 + 1000,
                        ScreenWidth * 16 - 1000, ScreenHeight * 16 - 1000};

        dvSetGsReg(0x42, 0x8000000068LL);
        dvSpriteUV(rect3, rect2, sonicRingColor, 0x156);
#else
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
#endif
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
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
#ifdef VERSION_JUN26
    dl_SetDLPriority(12);
    dvOpenPacket();
    {
        int rect4[4] = {1004, 1004, ScreenWidth * 16 - 1000, ScreenHeight * 16 - 1000};

        {
            dvSetGsReg(0x46, 1);
            dvSetGsReg(0x4A, 0);
            dvSetFrame(0x40, ScreenWidth, ScreenHeight);
#else
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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
            dvSetFrame(0x40, ScreenWidth, ScreenHeight);
#else
            dvSetFrame(0x40, ScreenWidth, ScreenHeight, screenOffsetX, screenOffsetY);
#endif
#endif
            dvSetGsReg(0x06, 0x664020800LL);
            dvSetGsReg(0x14, 0x60);
            dvSetGsReg(0x47, 0x33001);
            dvSetGsReg(0x4E, 0x1300000C0LL);
            dvSetGsReg(0x42, 0x44);
#ifdef VERSION_JUN26
            dvSpriteUV(rect, rect4, sonicFadeColor, 0x156);
#else
            dvSetGsReg(0x00, 0x156);
            dvSetGsReg(0x01, (long)c.r | ((long)c.g << 8) | ((long)c.b << 16) | ((long)c.a << 24));
            dvSetGsReg(0x03, (long)rect4[0] | ((long)rect4[1] << 16));
            dvSetGsReg(0x05, (long)(rect[0] + 0x8000) | ((long)(rect[1] + 0x8000) << 16) |
                                 0xFFFFFFFF00000000LL);
            dvSetGsReg(0x03, (long)(rect4[0] + rect4[2]) | ((long)(rect4[1] + rect4[3]) << 16));
            dvSetGsReg(0x05, (long)(rect[0] + 0x8000 + rect[2]) |
                                 ((long)(rect[1] + 0x8000 + rect[3]) << 16) | 0xFFFFFFFF00000000LL);
#endif
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
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
}

#ifdef VERSION_JUN26
static void darkVolume(void *pos, float radius)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};
    int rect2[4] = {4, 4, ScreenWidth * 16, ScreenHeight * 16};

    dl_SetDLPriority(12);
    dvOpenPacket();
    dvSetFrame(0x140, ScreenWidth, ScreenHeight);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x47, 0x30000);
    dvSpriteRect(rect, volumePacketColor, 0x406);
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
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    gif_StartPacketPri(12);
    {
        DVColor c = {volumeOuterColor.r - volumeInnerColor.r - 1,
                     volumeOuterColor.g - volumeInnerColor.g - 1,
                     volumeOuterColor.b - volumeInnerColor.b - 1, 128};

        renderViewCoordZSphere(pos, volumeOuterColor, 0, 1, radius + 30.0f);
        renderViewCoordZSphere(pos, volumeOuterColor, 0, 0, radius + 30.0f);
        renderViewCoordZSphere(pos, volumeInnerColor, 1, 1, radius + 20.0f);
        renderViewCoordZSphere(pos, volumeInnerColor, 1, 0, radius + 20.0f);
        renderViewCoordZSphere(pos, c, 1, 1, radius);
        renderViewCoordZSphere(pos, c, 1, 0, radius);
        gif_EndPacket();
    }
    dl_SetDLPriority(12);
    dvOpenPacket();
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x4E, 0x1300000C0LL);
    dvSetGsReg(0x46, 1);
    dvSetGsReg(0x4A, 0);
    dvSetGsReg(0x3B, 0x8000008080LL);
    dvSetGsReg(0x14, 0x60);
    dvSetFrame(0x1000040, ScreenWidth, ScreenHeight);
    dvSetGsReg(0x42, 0x44);
    dvSetGsReg(0x47, 0x30000);
    dvSetGsReg(0x06, 0x664122800LL);
    dvSpriteUV(rect, rect2, volumeEdgeColor, 0x156);
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
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
}
#else
static void darkVolume(void *pos, float radius, float ratio, float edge)
{
    int rect[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                   ScreenHeight * 16};
    int rect2[4] = {4, 4, ScreenWidth * 16, ScreenHeight * 16};

    dl_SetDLPriority(10);
    dvOpenPacket();
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    dvSetFrame(0x140, ScreenWidth, ScreenHeight);
#else
    dvSetFrame(0x140, ScreenWidth, ScreenHeight, 0, 0);
#endif
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
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    gif_StartPacketPri(10);
    {
        DVColor c = {volumeOuterColor.r - volumeInnerColor.r - 1,
                     volumeOuterColor.g - volumeInnerColor.g - 1,
                     volumeOuterColor.b - volumeInnerColor.b - 1, 128};

        renderViewCoordZSphere(pos, volumeOuterColor, 1, radius + edge);
        renderViewCoordZSphere(pos, volumeInnerColor, 0, radius * ratio + edge * 0.6666667f);
        renderViewCoordZSphere(pos, c, 0, radius * ratio * ratio);
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
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    dvSetFrame(0x1000040, ScreenWidth, ScreenHeight);
#else
    dvSetFrame(0x1000040, ScreenWidth, ScreenHeight, screenOffsetX, screenOffsetY);
#endif
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
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
}
#endif

/* the game-over effect's state and the ordinary dark volume's radius and
   target radius */
static int gameOverActive = 0; /* derived name */

static float gameOverRadius = 0; /* derived name */

#ifdef VERSION_JUN26
int InitDarkVolumeGeo(GObj *self)
{
    return 0;
}
#else
static int gameOverRing = 0; /* derived name */

static int gameOverQueen = 0; /* derived name */

static float gameOverSpeed = 25.0f; /* derived name */

static float darkVolumeRadius = 0; /* derived name */

static float darkVolumeTarget = 0; /* derived name */

/* arm the game-over dark volume, shared by StartGameOverEffect and
   StartQueenAttackEffect */
static inline void setGameOverEffect(float *center, float speed) /* derived name */
{
    gameOverActive = 1;
    gameOverRadius = 0;
    gameOverRing = 1;
    gameOverQueen = 0;
    CopyVector(gameOverCenter, center);
    gameOverSpeed = speed;
}
#endif

#ifdef VERSION_JUN26
void DarkVolumeGeo(GObj *self) {}

void DarkVolumeDL(void) {}

void ExecGameOverEffect(void) {}

/* the game-over test effect: the second pad's button starts it round the
   boy, and it spreads until it is 5000 across */
void DispGameOverEffect(void)
{
    float pos[4];

    if (boyGObj == 0) {
        return;
    }
    if (pad[1].flags & 0x100) {
        gameOverRadius = 0;
        gameOverActive = 1;
    }
    if (gameOverActive != 0) {
        GetRootPosition(pos, boyGObj);
        gameOverRadius = gameOverRadius + 25.0f;
        sonic(pos, gameOverRadius);
        darkVolume(pos, gameOverRadius);
        if (5000.0f < gameOverRadius) {
            gameOverActive = 0;
        }
    }
}
#else
inline void StartGameOverEffect(float *center, float speed)
{
    if (girlGObj != 0) {
#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
        ExecuteSEPackage(girlGObj, 117);
        ExecuteSEPackage(girlGObj, 118);
        ExecuteSEPackage(girlGObj, 119);
        ExecuteSEPackage(girlGObj, 120);
        ExecuteSEPackage(girlGObj, 121);
#else
        ExecuteSEPackage(girlGObj, 0x7A);
        ExecuteSEPackage(girlGObj, 0x7B);
        ExecuteSEPackage(girlGObj, 0x7C);
        ExecuteSEPackage(girlGObj, 0x7D);
        ExecuteSEPackage(girlGObj, 0x7E);
#endif
    }
    setGameOverEffect(center, speed);
}

inline void StartQueenAttackEffect(float *center, float speed)
{
    setGameOverEffect(center, speed);
    gameOverQueen = 1;
    gameOverRing = 0;
}

inline void ResetGameOverEffect(void)
{
    gameOverActive = 0;
    gameOverRing = 0;
}

void SetDarkVolumeEffect(float *pos, float size)
{
    darkVolumeTarget = size;
    CopyVector(darkVolumeCenter, pos);
}

/* the per-object hit test, inlined at all three sites */
static inline void sendGameOverMail(void *gobj, float r2) /* derived name */
{
    float pos[4];

    GetRootPosition(pos, gobj);
    if (distance_squared(pos, gameOverCenter) < r2) {
        iosOmSendMail(gobj, 0x22, gobj);
    }
}
#endif

#ifndef VERSION_JUN26
#ifdef VERSION_NTSC
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
            for (g = isysGObjSearchFromObjKindID_begin(61); g != 0;
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
#else
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
#ifdef VERSION_AUG6
            for (g = isysGObjSearchFromObjKindID_begin(60); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
#else
            for (g = isysGObjSearchFromObjKindID_begin(62); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
#endif
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
#endif

void GetGameOverEffectCenterPosition(float *pos)
{
    CopyVector(pos, gameOverCenter);
}

/* Build the 8 by 17 sphere vertex table renderViewCoordZSphere walks 34
   vectors at a time, then reset the effect state.  Each entry is the pair of
   vectors for ring i and ring i+1, so the row holds 17 pairs of 8 floats and
   the ring stride is 136 floats.  Angles are the 16 bit binary turn the sin
   and cos tables take, 0x1000 per step. */
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

#ifdef VERSION_NTSC
int InitDarkVolumeGeo(GObj *self)
{
    return 0;
}

void DarkVolumeGeo(GObj *self) {}
#else
#ifdef VERSION_AUG6
int InitDarkVolumeGeo(GObj *self)
{
    return 0;
}
#else
inline int InitDarkVolumeGeo(GObj *self)
{
    *(int *)GOBJ_SUB(self)->nodeMtx = 0;
    return 0;
}
#endif

#ifdef VERSION_AUG6
void DarkVolumeGeo(GObj *self) {}
#else
void SetupDarkVolume(void *pos, float radius, float edge)
{
    darkVolume(pos, radius, 1.0f, edge);
}

void DarkVolumeGeo(GObj *self)
{
    float *p;

    GOBJ_SUB(self)->disp = 0;
    p = (float *)GOBJ_SUB(self)->nodeMtx;
    if (1e-05f < *p) {
        SetupDarkVolume((char *)p + 0x30, *p * 50.0f, 10.0f);
    }
}
#endif
#endif

inline void DarkVolumeDL(void) {}
#endif
