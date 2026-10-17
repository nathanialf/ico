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
#include "include_asm.h"

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

/* the colour draw and drawHT take by value: four bytes in one register */
typedef struct { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} DVColor; /* derived name */

static void draw(void *v, int n, DVColor col, int neg);
static void drawHT(float *v, int n, DVColor col, int neg);

/* the count draw reads, then drawHT's state (renderViewCoordZSphere's in
   this build): the strip's vertex count, whose parity flips the edge, the
   previous vertex and the edge vector the next vertex is tested against */
static int drawCount; /* derived name */

static int stripCount; /* derived name */

static float prevX; /* derived name */

static float prevY; /* derived name */

static float edgeX; /* derived name */

static float edgeY; /* derived name */

/* draw and drawHT's state: the two strip halves' written flags, the half
   being filled, and the GS PRIM value the strips are drawn with */
/* This build's .sdata of the TU is the stub-owned run D_0067ACA8: its strip
   state, colours and game-over words differ from PAL's (a sonic colour more,
   no strip PRIM value, three game-over words fewer), only stubs read them,
   and the inline strip and game-over helpers that wrote PAL's have no C
   caller here. */
INCLUDE_ASM(D_0067ACA8);

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

INCLUDE_ASM(draw);

INCLUDE_ASM(InitGameOverEffect);

INCLUDE_ASM(func_001BAE50);

/* one screen-space segment of the half-tone pass */
typedef struct { /* field names derived */
    int on;
    int side;
    long long xy;
} DVSeg; /* derived name */

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

/* project the view-space sphere around pos, splitting each of the 8 rings
   at the near plane */
INCLUDE_ASM(renderViewCoordZSphere);

INCLUDE_ASM(func_001BB2F0);

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
/* darkVolume's four colours */
INCLUDE_ASM(sonic);

INCLUDE_ASM(darkVolume);

/* the game-over effect's state and the ordinary dark volume's radius and
   target radius */
inline void ResetGameOverEffect(void);

/* the per-object hit test, inlined at all three sites */
static inline void sendGameOverMail(void *gobj, float r2) /* derived name */
{
    float pos[4];

    GetRootPosition(pos, gobj);
    if (distance_squared(pos, gameOverCenter) < r2) {
        iosOmSendMail(gobj, 0x22, gobj);
    }
}

/* Build the 8 by 17 sphere vertex table renderViewCoordZSphere walks 34
   vectors at a time, then reset the effect state.  Each entry is the pair of
   vectors for ring i and ring i+1, so the row holds 17 pairs of 8 floats and
   the ring stride is 136 floats.  Angles are the 16 bit binary turn the sin
   and cos tables take, 0x1000 per step. */

void SetupDarkVolume(void *pos, float radius, float edge);

INCLUDE_ASM(InitDarkVolumeGeo);

INCLUDE_ASM(DarkVolumeGeo);

INCLUDE_ASM(DarkVolumeDL);

INCLUDE_ASM(ExecGameOverEffect);

INCLUDE_ASM(DispGameOverEffect);

INCLUDE_ASM(StartQueenAttackEffect);
