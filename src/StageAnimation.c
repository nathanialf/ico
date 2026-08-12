#include "common.h"







extern const char D_00555BF8[];
extern void func_001AD768();
extern int bga_SetCamFrame();
extern const char D_00631D88[];
extern void func_00263FF0(char *file, int line, char *msg);
extern void debug_assertMessage();
extern const char D_00555D78[];
extern int font_CheckAlign();
extern char D_00674058[];
extern int D_00633C54;
extern void font_GetWidth();
extern int *D_00633C58;
extern int resetmallocseki(void *a0);
extern void func_00117768(void);
extern void func_001FAA58();
extern int D_00274ED4[];
extern int D_00631D54;
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_MakeGObj);

extern char *D_00631970;
extern void _ClearTransCurrentMatrix(void *a0, void *a1);
extern void _InverseCurrentMatrix(void *a0, void *a1, float a2);
extern void _PopCurrentMatrix(void *a0);
extern void _RotCurrentMatrixY(void);
extern void func_00117C80(void *a0);
extern void func_00117C98(void);
extern void func_00117CE0(void);

void stage_ApplyData(void *a0) {
    func_00117C80(a0);
    _PopCurrentMatrix(D_00631970 + 0x80);
    func_00117CE0();
    _RotCurrentMatrixY();
    _ClearTransCurrentMatrix(a0, D_00631970 + 0xB0);
    _InverseCurrentMatrix(a0, a0, -1.0f);
    *(float *)((char *)a0 + 0xC) = 1.0f;
    func_00117C98();
}

/* StageAnimation .rodata run 0x555938..0x555E70 -- byte-verified against
 * baseelf; defs interleave with INCLUDE_ASM stubs so .o section order ==
 * VMA order */
const unsigned int D_00555938[0x16] = { 0x00000000, 0x00000001, 0x00000003, 0x00000004, 0x00000005, 0x00000001, 0x00000002, 0x00000000, 0x00000005, 0x00000003, 0x00000003, 0x00000004, 0x00000000, 0x00000001, 0x00000002, 0x00000004, 0x00000005, 0x00000003, 0x00000002, 0x00000000, 0x00000000, 0x00000000 };

/* ---------------------------------------------------------------- */
/* stage_Init -- build the projected drop-shadow silhouette geometry   */
/* for one stage object and append it to the current display packet.  */

#include "vu0.h"

typedef struct { float x, y, z, w; } SVec;

/* One vertex of a silhouette outline (0x10 bytes).  An outline is a
 * 0x10-byte header whose first short is the vertex count, followed by
 * that many entries; outlines run back to back until a zero count. */
typedef struct {
    short code;    /* 0x00 -- on the first vertex: outline winding */
    short pad02;
    short vtx;     /* 0x04 -- index into the top/bottom vertex arrays */
    short pad06;
    int   pad08;
    int   pad0C;
} SilVtx;

typedef struct {
    unsigned char pad000[0x100];
    SilVtx      **outline;  /* 0x100 */
    unsigned int  noutline; /* 0x104 */
    unsigned char pad108[0x6C];
    SVec         *top;      /* 0x174 */
    SVec         *bottom;   /* 0x178 */
    unsigned char pad17C[0x4];
} SilPart;                  /* 0x180 */

typedef struct {
    unsigned char pad00[0x2E];
    signed char   nparts;   /* 0x2E */
    unsigned char pad2F;
    long long     flags;    /* 0x30 */
    unsigned char pad38[0x4];
    float         alpha;    /* 0x3C */
    SilPart      *parts;    /* 0x40 */
    SVec         *planes;   /* 0x44 */
} SilObj;

typedef struct {
    unsigned char pad00[0xC];
    unsigned int  head;     /* 0x0C */
    unsigned int  cur;      /* 0x10 */
    unsigned int  tag;      /* 0x14 */
    unsigned int  cnt;      /* 0x18 */
    unsigned int  f1C;      /* 0x1C */
} DpkCtx;

extern DpkCtx D_004C7710;
extern int D_00631C5C;
extern int D_00631C60;
extern char D_00276230[];
extern float D_00674030[];

extern void mc_Init(void *m);
extern void _RotTransPersCurrentMatrix(void *d, void *s, void *v);
extern void _PushVu0Registers(void *d, void *s, float f);
extern void _TransposeCurrentMatrix(void *d, void *s, void *m);
extern void _ApplyCurrentMatrix(void *d, void *s, void *m);
extern int light_killLinkAmbient(void *v);
extern void GetCylinderCollision(void *v, void *self);
extern void func_00118510(void *a, void *b);
extern void func_00123C20(void *a, void *self);
extern void func_00123C70(void *self, float f);
extern void stage_MakeGObj(void *self, int mode, float f);
extern void dpk_SwapBuffer(int a);
extern void dpk_Init(int a, int b, int c);
extern int dpk_CheckBufferSize(void);
extern void dl_GetPri(void);

/* One outline vertex's screen-space source pointer: byte offset OFF into
 * the top or bottom vertex array. */
#define SIL_VTX(D, OFF, BASE)                                            \
    (D) = (SVec *)((OFF) + (int)(BASE))

/* The guard band this edge is clipped against. */
#define SIL_GUARD(G)                                                     \
    (G) = D_00276230

/* the guard band the projected outline is clipped against */
/* One VU0 quadword move.  Only the addressed quadword is touched. */
#define SIL_LSV(mnem, vf, off, base)                                     \
    __asm__ __volatile__(#mnem " $vf" #vf ", " #off "(%0)" : : "r"(base))

#define SIL_HW ((D_00631C5C * 3) / 2)
#define SIL_HH ((D_00631C60 * 3) / 2)

/* Project the top/bottom pair of an outline vertex through the camera
 * matrix held in vf4..vf7, roll the three-deep windows vf20..vf22 and
 * vf23..vf25, and write the screen-space pair to OA/OB.  Yields the
 * signed area of the projected triangle in DOT. */
#define SIL_PROJECT(PT, PB, OA, OB, DOT, GB)                             \
{                                                                        \
    VU0_REG("vmove.xyzw $vf10, $vf11");                                  \
    VU0_REG("vmove.xyzw $vf13, $vf14");                                  \
    VU0_REG("vmove.xyzw $vf20, $vf21");                                  \
    VU0_REG("vmove.xyzw $vf23, $vf24");                                  \
    VU0_REG("vmove.xyzw $vf11, $vf12");                                  \
    VU0_REG("vmove.xyzw $vf14, $vf15");                                  \
    VU0_REG("vmove.xyzw $vf21, $vf22");                                  \
    VU0_REG("vmove.xyzw $vf24, $vf25");                                  \
    SIL_LSV(lqc2, 12, 0x0, (PT));                                      \
    SIL_LSV(lqc2, 15, 0x0, (PB));                                      \
    VU0_REG("vnop");                                                     \
    VU0_REG("vsub.xyz $vf8, $vf10, $vf11");                              \
    VU0_REG("vsub.xyz $vf9, $vf12, $vf11");                              \
    VU0_REG("vmulax.xyzw ACC, $vf4, $vf12x");                           \
    VU0_REG("vmadday.xyzw ACC, $vf5, $vf12y");                          \
    VU0_REG("vmaddaz.xyzw ACC, $vf6, $vf12z");                          \
    VU0_REG("vmaddw.xyzw $vf22, $vf7, $vf0w");                           \
    VU0_REG("vdiv Q, $vf0w, $vf22w");                                   \
    VU0_WAIT();                                                          \
    VU0_REG("vmulq.xyzw $vf22, $vf22, Q");                              \
    VU0_REG("vopmula.xyz ACC, $vf8, $vf9");                             \
    VU0_REG("vopmsub.xyz $vf2, $vf9, $vf8");                             \
    VU0_REG("vaddw.x $vf3, $vf0, $vf0w");                                \
    VU0_REG("vmulax.xyzw ACC, $vf4, $vf15x");                           \
    VU0_REG("vmadday.xyzw ACC, $vf5, $vf15y");                          \
    VU0_REG("vmaddaz.xyzw ACC, $vf6, $vf15z");                          \
    VU0_REG("vmaddw.xyzw $vf25, $vf7, $vf0w");                           \
    VU0_REG("vdiv Q, $vf0w, $vf25w");                                   \
    VU0_WAIT();                                                          \
    VU0_REG("vmulq.xyzw $vf25, $vf25, Q");                              \
    VU0_REG("vmul.xyz $vf2, $vf1, $vf2");                                \
    VU0_REG("vmove.w $vf12, $vf0");                                      \
    VU0_REG("vmove.w $vf15, $vf0");                                      \
    VU0_REG("vnop");                                                     \
    VU0_REG("vaddax.x ACC, $vf0, $vf2x");                               \
    VU0_REG("vmadday.x ACC, $vf3, $vf2y");                              \
    VU0_REG("vmaddz.x $vf2, $vf3, $vf2z");                               \
    VU0_REG("vnop");                                                     \
    VU0_REG("vnop");                                                     \
    VU0_REG("vnop");                                                     \
    __asm__ __volatile__(".set noreorder\n"                              \
                         "qmfc2.ni $7, $vf2\n"                           \
                         "mtc1 $7, %0\n"                                 \
                         ".set reorder\n" : "=f"(DOT) : : "$7");         \
    SIL_LSV(lqc2, 8, 0x0, (GB));                                        \
    VU0_REG("vnop");                                                     \
    VU0_REG("vnop");                                                     \
    VU0_REG("vnop");                                                     \
    VU0_REG("vsub.xyzw $vf18, $vf22, $vf8");                             \
    VU0_REG("vsub.xyzw $vf19, $vf25, $vf8");                             \
    VU0_REG("vnop");                                                     \
    VU0_REG("vnop");                                                     \
    SIL_LSV(sqc2, 18, 0x0, (OA));                                      \
    SIL_LSV(sqc2, 19, 0x0, (OB));                                      \
}

/* Slide one end of the projected edge to parameter T along it. */
#define SIL_LERP_TOP(T)                                                  \
    __asm__ __volatile__(".set noreorder\n"                              \
                         "mfc1 $8, %0\n"                                 \
                         "qmtc2.ni $8, $vf8\n"                           \
                         "vsubx.w $vf8, $vf0, $vf8x\n"                   \
                         "vnop\n vnop\n vnop\n"                          \
                         "vmulaw.xyz ACC, $vf19, $vf8w\n"               \
                         "vmaddx.xyz $vf22, $vf18, $vf8x\n"              \
                         "lqc2 $vf8, 0(%1)\n"                            \
                         "vnop\n vnop\n vnop\n"                          \
                         "vadd.xyzw $vf22, $vf22, $vf8\n"                \
                         ".set reorder\n"                                \
                         : : "f"(T), "r"(D_00276230) : "$8")

#define SIL_LERP_BOT(T)                                                  \
    __asm__ __volatile__(".set noreorder\n"                              \
                         "mfc1 $8, %0\n"                                 \
                         "qmtc2.ni $8, $vf8\n"                           \
                         "vsubx.w $vf8, $vf0, $vf8x\n"                   \
                         "vnop\n vnop\n vnop\n"                          \
                         "vmulaw.xyz ACC, $vf18, $vf8w\n"               \
                         "vmaddx.xyz $vf25, $vf19, $vf8x\n"              \
                         "lqc2 $vf8, 0(%1)\n"                            \
                         "vnop\n vnop\n vnop\n"                          \
                         "vadd.xyzw $vf25, $vf25, $vf8\n"                \
                         ".set reorder\n"                                \
                         : : "f"(T), "r"(D_00276230) : "$8")

/* Liang-Barsky: pull the two edge parameters in against one guard line. */
#define SIL_CLIP_HI(A, B, H, T0, T1)                                     \
    if ((A) > (H) && (B) <= (H)) {                                       \
        float _r = ((B) - (H)) / ((B) - (A));                            \
        if (_r < (T0)) if (_r < 1.0f) if (_r > 0.0f) (T0) = _r;          \
    } else if ((B) > (H) && (A) <= (H)) {                                \
        float _r = ((A) - (H)) / ((A) - (B));                            \
        if (_r < (T1)) if (_r < 1.0f) if (_r > 0.0f) (T1) = _r;          \
    }

#define SIL_CLIP_LO(A, B, H, T0, T1)                                     \
    if ((A) < -(H) && (B) >= -(H)) {                                     \
        float _r = ((B) + (H)) / ((B) - (A));                            \
        if (_r < (T0)) if (_r < 1.0f) if (_r > 0.0f) (T0) = _r;          \
    } else if ((B) < -(H) && (A) >= -(H)) {                              \
        float _r = ((A) + (H)) / ((A) - (B));                            \
        if (_r < (T1)) if (_r < 1.0f) if (_r > 0.0f) (T1) = _r;          \
    }

/* Compose the eight light planes through the camera into DST via the
 * VU0 current-matrix helpers, then link the result into the light rig.
 * M0/M1 are caller scratch quads.  Returns 0 when the light is dead. */
static inline int stage_SetupLightPlanes(SVec *m0, SVec *m1, SVec *dst,
                                         SVec *planes, float scale)
{
    SVec *p;
    SVec *d;
    int k;

    mc_Init(m0);
    for (k = 7, p = planes; k >= 0; k--) {
        _RotTransPersCurrentMatrix(m0, m0, p);
        p++;
    }
    _PushVu0Registers(m0, m0, 0.125f);
    p = planes;
    d = dst;
    for (k = 7; k >= 0; k--) {
        _TransposeCurrentMatrix(m1, p, m0);
        _InverseCurrentMatrix(m1, m1, scale);
        _ApplyCurrentMatrix(d, p, m1);
        d++;
        p++;
    }
    _PopCurrentMatrix(D_00631970 + 0x300);
    return light_killLinkAmbient(dst);
}

/* Clip the edge just projected into WA/WB against the guard band.  When
 * nothing survives, stamp both source vertices with w = -1 and report
 * -1; otherwise report the signed area scaled by the outline winding. */
static inline float stage_ClipSilEdge(SVec *w, SVec *vt, SVec *vb,
                                      float dot, float sgn)
{
    if (w[0].x > -SIL_HW && w[0].x < SIL_HW &&
        w[1].x > -SIL_HW && w[1].x < SIL_HW &&
        w[0].y > -SIL_HH && w[0].y < SIL_HH &&
        w[1].y > -SIL_HH && w[1].y < SIL_HH)
        return dot * sgn;
    {
        int j1, j2;
        if (w[0].x <= -SIL_HW && w[1].x <= -SIL_HW) goto reject;
        if (w[0].x >= SIL_HW && w[1].x >= SIL_HW) goto reject;
        if (w[0].y <= -SIL_HH) {
            if (w[1].y <= -SIL_HH) goto reject;
        }
        if (w[0].y >= SIL_HH) {
            if (w[1].y >= SIL_HH) goto reject;
        }

        /* Vestigial degenerate-edge guards.  Load-bearing shape: the two goto
         * uses give the clip-entry label LABEL_NUSES == 2, and cse1 both
         * stops its basic-block scan at the label and refuses to follow a
         * conditional jump whose target has NUSES != 1 (cse.c:8399), so
         * the clip code below recomputes the guard band instead of reusing
         * the reject tests' values (18 computations, which is ROM's
         * count).  j1/j2's reference cycle keeps the never-read stores
         * alive past every trivially-dead sweep; flow's liveness then
         * deletes both stores, and jump2 deletes the two never-taken
         * branches and the label.  Zero bytes in the image, and none of
         * the old do{}while(0)'s loop notes, whose LOOP_BEG padded the
         * clip entry with a nop ROM does not have. */
        if ((int)vt < 0) goto clipband;
        j1 = j2;
        j2 = j1;
        if ((int)vt > 0) goto clipband;
        j1 = j2;
        j2 = j1;
clipband:;
    {
        float hx = SIL_HW;
        float hy = SIL_HH;
        float t1 = 1.0f;
        float t0 = 1.0f;

        SIL_CLIP_HI(w[0].x, w[1].x, hx, t0, t1)
        SIL_CLIP_LO(w[0].x, w[1].x, hx, t0, t1)
        SIL_CLIP_HI(w[0].y, w[1].y, hy, t0, t1)
        SIL_CLIP_LO(w[0].y, w[1].y, hy, t0, t1)

        w[2].x = t0;
        w[2].y = t1;
        t0 = 1.0f - t0;
        t1 = 1.0f - t1;
        {
            float span = t0 + t1;
            if (1.0f <= span) goto reject;
            if (span <= 0.0f) {
reject:
                vb->w = -1.0f;
                vt->w = -1.0f;
                return -1.0f;
            }
        }
        if (0.0f < w[2].x && w[2].x < 1.0f) SIL_LERP_TOP(w[2].x);
        if (0.0f < w[2].y && w[2].y < 1.0f) SIL_LERP_BOT(w[2].y);
    }
    }
    return dot * sgn;
}

/* Every one of the six projected quads must land inside the packet's
 * 16-bit screen window with a non-negative Z, or the whole strip is
 * dropped.
 *
 * Deliberately a plain block, NOT the usual do{...}while(0) macro
 * hygiene.  A loop note attaches to the very next insn -- here the
 * `(M) = 0` gcc emits ahead of the loop -- and haifa-sched.c:3763
 * turns any insn carrying a loop note into a full scheduling barrier.
 * loop.c builds this preheader by appending (move_movables hoists the
 * two comparison constants, strength_reduce appends the row pointer's
 * biv init, all emit_insn_before(loop_start)), so `(M) = 0` always has
 * the smaller LUID and only the scheduler can reach ROM's
 * `li / li / move m,zero / move row,base` order.  With the do-while
 * that insn is pinned first.  Measured round 20. */
#define SIL_CHECK_QUADS(SCR, M, BAD)                                     \
    {                                                                    \
        for ((M) = 0; (M) < 6; (M)++) {                                  \
            int *_sc = (SCR)[(M)];                                       \
            if (_sc[0] < 0x11 || _sc[0] > 0xFFEF ||                      \
                _sc[1] < 0x11 || _sc[1] > 0xFFEF ||                      \
                _sc[2] < 0) {                                            \
                (BAD) = 1;                                               \
                goto checked;                                            \
            }                                                            \
        }                                                                \
    }

/* Emit one triangle-strip packet for the quad just accepted: the two GIF
 * tags, then ten REGLIST vertex pairs in strip order.  Each vertex takes
 * the sign of the cross product of its two strip edges (cases 2/4/5/7/8
 * compute one, cases 3/6/9 reuse the negated cached value) and picks one
 * of the two RGBAQ constants from it.
 *
 * The do/while(0) is load-bearing beyond hygiene: its loop notes put the
 * `SCR[idx]` reference one loop level deeper, restoring the reference
 * SIL_CHECK_QUADS gives up by being a plain block (refs 26 -> 27,
 * priority 8320 -> 8640), which is what keeps &scr at rank 4 and in
 * register t3.  haifa-sched.c:3763 hangs a stripped loop note on the next
 * real insn and makes THAT insn a full barrier, so both barriers here land
 * where nothing was free to move anyway -- LOOP_BEG on the first `PK[0] =`
 * store (a block head) and LOOP_END on the k-loop tail -- and the
 * LOOP_ALIGN walk reaches the same packet-loop label the `for (m ...)`
 * note already aligns, so it costs no pad.  Round 20/21. */
#define SIL_EMIT_STRIP(PK, ORDER, SCR, C)                  \
    do {                                                   \
        long long *q;                                      \
        int m;                                             \
        PK[0] = 0x1000000000008001LL;                      \
        PK[1] = 0xE;                                       \
        PK[2] = 0x144;                                     \
        PK[3] = 0;                                         \
        PK[4] = 0x240000000000800ALL;                      \
        PK[5] = 0x51;                                      \
        q = PK + 6;                                        \
        for (m = 0; m < 10; m++) {                         \
            int idx = ORDER[m];                            \
            float v;                                       \
            switch (m) {                                   \
            case 0:                                        \
            case 1:                                        \
                v = 1.0f;                                  \
                goto scaled;                               \
            case 2:                                        \
                VU0_REG(".set noreorder\n\t"               \
                        "vsub.xy $vf8, $vf20, $vf21\n\t"   \
                        "vsub.xy $vf9, $vf23, $vf21\n\t"   \
                        ".set reorder");                   \
                break;                                     \
            case 3:                                        \
                v = -D_00674030[2];                        \
                goto scaled;                               \
            case 4:                                        \
                VU0_REG(".set noreorder\n\t"               \
                        "vsub.xy $vf8, $vf23, $vf24\n\t"   \
                        "vsub.xy $vf9, $vf25, $vf24\n\t"   \
                        ".set reorder");                   \
                break;                                     \
            case 5:                                        \
                VU0_REG(".set noreorder\n\t"               \
                        "vsub.xy $vf8, $vf24, $vf25\n\t"   \
                        "vsub.xy $vf9, $vf21, $vf25\n\t"   \
                        ".set reorder");                   \
                break;                                     \
            case 6:                                        \
                v = -D_00674030[5];                        \
                goto scaled;                               \
            case 7:                                        \
                VU0_REG(".set noreorder\n\t"               \
                        "vsub.xy $vf8, $vf21, $vf22\n\t"   \
                        "vsub.xy $vf9, $vf20, $vf22\n\t"   \
                        ".set reorder");                   \
                break;                                     \
            case 8:                                        \
                VU0_REG(".set noreorder\n\t"               \
                        "vsub.xy $vf8, $vf22, $vf20\n\t"   \
                        "vsub.xy $vf9, $vf25, $vf20\n\t"   \
                        ".set reorder");                   \
                break;                                     \
            case 9:                                        \
                v = -D_00674030[8];                        \
                goto scaled;                               \
            }                                              \
            VU0_REG("vopmula.xyz ACC, $vf8, $vf9");        \
            VU0_REG("vopmsub.xyz $vf2, $vf9, $vf8");       \
            VU0_REG("vaddz.x $vf2, $vf0, $vf2z");          \
            {                                              \
                float z;                                   \
                __asm__ __volatile__(".set noreorder\n"    \
                                     "qmfc2.ni $7, $vf2\n" \
                                     "mtc1 $7, %0\n"       \
                                     ".set reorder\n"      \
                                     : "=f"(z) : : "$7");  \
                D_00674030[m] = z;                         \
                v = z;                                     \
            }                                              \
        scaled:                                            \
            v *= C;                                        \
            if (v < 0.0f) {                                \
                *q++ = 0x3F80000080080808LL;               \
            } else {                                       \
                *q++ = 0x3F80000080F8F8F8LL;               \
            }                                              \
            {                                              \
                int *sv = SCR[idx];                        \
                *q++ =                                     \
                    (long long)sv[0] |                     \
                    ((long long)sv[1] << 16) |             \
                    ((long long)sv[2] << 32);              \
            }                                              \
            C = -C;                                        \
        }                                                  \
        PK = q;                                            \
    } while (0)

typedef struct { int e[20]; } SilOrder;

/* One DMA tag as the packet writer sees it: the 64-bit tag word plus the two
 * 32-bit words of inline data that share its qword. */
typedef union {
    long long    q;
    unsigned int w[4];
} Qword;

void stage_Init(void *self)
{
    SVec cyl;             /* 0x00 */
    SVec mtx;             /* 0x10 */
    SVec work[8];         /* 0x20 -- light planes, then clip scratch */
    SVec tmpa;            /* 0xA0 */
    SVec tmpb;            /* 0xB0 */
    int order[20];        /* 0xC0 */
    int scr[6][4];        /* 0x110 */
    long long *first;     /* 0x170 */
    long long *packet;
    SilObj *o;
    char *dl;
    SVec *w;
    float alpha;
    float scale;
    int i;

    o = *(SilObj **)((char *)self + 0x824);
    dl = *(char **)((char *)self + 0x820);
    alpha = *(float *)(dl + 0x3C);
    if (o->flags & 0x04000000) return;

    if (alpha != o->alpha) {
        if (o->alpha > 0.0f) alpha = o->alpha;
    }
    w = work;
    scale = alpha * 1.4142135f;

    if (stage_SetupLightPlanes(&tmpa, &tmpb, work, o->planes, scale) == 0)
        return;

    stage_ApplyData(&mtx);
    GetCylinderCollision(&cyl, self);
    func_00118510(&cyl, &mtx);

    if (*(unsigned short *)((char *)self + 0x818) == 1) {
        func_00123C70(self, alpha);
    } else {
        stage_MakeGObj(self, 0, alpha);
    }
    dpk_SwapBuffer(3);
    func_00123C20(&cyl, self);

    {
        char *cm = D_00631970 + 0xC0;
        SIL_LSV(lqc2, 4, 0x00, cm);
        SIL_LSV(lqc2, 5, 0x10, cm);
        SIL_LSV(lqc2, 6, 0x20, cm);
        SIL_LSV(lqc2, 7, 0x30, cm);
    }
    SIL_LSV(lqc2, 1, 0x00, &cyl);

    {
        unsigned int p = D_004C7710.cur;
        D_004C7710.cnt = 0;
        D_004C7710.head = p;
        D_004C7710.cur = p + 8;
        D_004C7710.f1C = 0;
        D_004C7710.tag = p;
        ((Qword *)p)->w[2] = 0x11000000;
        D_004C7710.cnt = p + 0xC;
        D_004C7710.cur = p + 0x10;
        first = (long long *)(p + 0x10);
        packet = first;
    }

    for (i = 0; i < o->nparts; i++) {
        SilPart *part = &o->parts[i];
        SVec *top = part->top;
        SVec *bot = part->bottom;
        unsigned int j;
        for (j = 0; j < part->noutline; j++) {
            SilVtx *p = part->outline[j];
            int n;
            while ((n = (p++)->code) != 0) {
                float sgn;
                char *gb2;
                float nsgn;
                float dot;
                float d;
                SVec *at, *ab, *bt, *bb;
                int nskip;
                int ns;
                int k;

                sgn = p->code ? 1.0f : -1.0f;
                {
                int va = p->vtx;
                int vb = p[1].vtx;
                int oa;
                int ob;
                char *gb;

                SVec *wp = work;   /* the second edge writes through its own cursor */

                gb = (char *)&work[1];  /* dead first store: SIL_GUARD below rewrites it
                                         * before any use, so flow deletes it -- but it
                                         * hands gcse the (sp+48) expression ahead of the
                                         * guard-band high part, which orders the two PRE
                                         * preheader insertions the way ROM has them */
                nskip = 0;
                oa = va * 16;
                SIL_GUARD(gb);
                ob = vb * 16;
                SIL_VTX(at, oa, top);
                SIL_VTX(bt, ob, top);
                SIL_VTX(ab, oa, bot);
                SIL_VTX(bb, ob, bot);
                if ((int)w < 0) { va = 0; vb = 0; }

                SIL_PROJECT(at, ab, w, &work[1], dot, gb)
                w[2].y = 1.0f;
                w[2].x = 1.0f;
                d = stage_ClipSilEdge(work, at, ab, dot, sgn);
                if (d == -1.0f) {
                    if (at->w == -1.0f) nskip = 1;
                }
                nsgn = -sgn;

                {
                gb2 = D_00276230;

                SIL_PROJECT(bt, bb, wp, &work[1], dot, gb2)
                wp[2].y = 1.0f;
                wp[2].x = 1.0f;
                d = stage_ClipSilEdge(work, bt, bb, dot, nsgn);
                if (d == -1.0f) {
                    if (bt->w == -1.0f) nskip = 2;
                }
                if ((int)bb < 0) { nsgn = 0.0f; dot = 0.0f; }
                }

                } /* wp */
                p += 2;
                ns = nskip;
                for (k = 2; k < n; k++) {
                    SVec *kt;
                    SVec *kb;

                    if (top[p->vtx].w == -1.0f) {
                        ns = 3;
                    } else if (ns) {
                        ns--;
                    }
                    kt = (SVec *)(p->vtx * 16 + (int)top);
                    kb = (SVec *)(p->vtx * 16 + (int)bot);

                    {
                    gb2 = D_00276230;

                    SIL_PROJECT(kt, kb, w, &work[1], dot, gb2)
                    }
                    w[2].y = 1.0f;
                    w[2].x = 1.0f;
                    d = stage_ClipSilEdge(work, kt, kb, dot, sgn);
                    if (d >= 0.0f) {
                        if (ns == 0) {
                            int m;
                            int bad;
                            float c;

                            *(SilOrder *)order = *(const SilOrder *)D_00555938;
                            c = sgn;
                            VU0_REG("vftoi4.xyzw $vf26, $vf20");
                            VU0_REG("vftoi4.xyzw $vf27, $vf21");
                            VU0_REG("vftoi4.xyzw $vf28, $vf22");
                            VU0_REG("vftoi4.xyzw $vf29, $vf23");
                            VU0_REG("vftoi4.xyzw $vf30, $vf24");
                            VU0_REG("vftoi4.xyzw $vf31, $vf25");
                            /* One asm statement, not six.  gcse PRE hoists
                             * &scr into a loop-invariant pseudo and rewrites
                             * every use into a copy from it; cprop_insn
                             * (gcse.c:3690) refuses to propagate into an insn
                             * whose pattern is not a SET, so an asm operand
                             * keeps that copy for ever.  Naming the base and
                             * storing through it therefore costs a `move`,
                             * while dropping the name gives the invariant six
                             * references instead of one -- and REG_N_REFS +=
                             * loop_depth (5 here) lifts it from rank 4 to
                             * rank 2 of its conflicting group, turning t3
                             * into t1.  A single asm insn is one reference
                             * and no copy, which is ROM.  Round 20. */
                            __asm__ __volatile__(
                                "sqc2 $vf26, 0x00(%0)\n"
                                "sqc2 $vf27, 0x10(%0)\n"
                                "sqc2 $vf28, 0x20(%0)\n"
                                "sqc2 $vf29, 0x30(%0)\n"
                                "sqc2 $vf30, 0x40(%0)\n"
                                "sqc2 $vf31, 0x50(%0)\n"
                                : : "r"(scr));

                            SIL_CHECK_QUADS(scr, m, bad);
                            bad = 0;
                        checked:
                            if (bad == 0) {
                            /* The macro's do/while(0) is load-bearing --
                             * see SIL_EMIT_STRIP for the measurement. */
                            SIL_EMIT_STRIP(packet, order, scr, c);
                            }
                        }
                    } else {
                        if (top[p->vtx].w == -1.0f) ns = 3;
                    }
                    sgn = -sgn;
                    p++;
                }
            }
        }
    }

    {
        unsigned int start = D_004C7710.tag;
        int qwc = (int)(((unsigned int)packet - start) >> 4) - 1;
        int emitted = packet - first;

        D_004C7710.cur = (unsigned int)packet;
        ((Qword *)start)->q = (unsigned int)(qwc | 0x10000000);
        {
            unsigned int e = D_004C7710.cnt;
            *(int *)e = (int)(((D_004C7710.cur - e) >> 4) | 0x50000000);
        }
        {
            unsigned int c = D_004C7710.cur;
            D_004C7710.tag = c;
            ((Qword *)c)->q = 0x60000000LL;
            D_004C7710.cur = c + 8;
            *(int *)(c + 8) = 0;
            D_004C7710.cur = c + 0xC;
            *(int *)(c + 0xC) = 0;
            D_004C7710.cur = c + 0x10;
            if (emitted > 0) {
                dpk_SwapBuffer(dpk_CheckBufferSize());
                dpk_Init(5, D_004C7710.head, 0);
                dl_GetPri();
            }
        }
    }
    dpk_SwapBuffer(0);
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetAnimation);
ASM_LIT4_SLOT(D_00630A74, 1.4142135f);

/* D_005559E8/F0/F4 hand-assembled as one contiguous block: dlabel (used by
 * INCLUDE_RODATA and gcc -fdata-sections alike) forces .align 3 on every
 * per-symbol section, but D_005559F4 sits at a VMA only 4-aligned (right
 * after the 4-byte D_005559F0) -- no gap in the ROM to absorb an 8-align
 * pad. Emitting the run as one un-aligned block starting from the already
 * 8-aligned D_005559E8 sidesteps it; see include/labels.inc dlabel comment. */
__asm__(
    ".section .rodata.D_005559E8,\"a\",@progbits\n"
    ".globl D_005559E8\n"
    ".type D_005559E8, @object\n"
    "D_005559E8:\n"
    "    .word D_00555B10\n"
    "    .word D_002751CC\n"
    ".size D_005559E8, 8\n"
    ".globl D_005559F0\n"
    ".type D_005559F0, @object\n"
    "D_005559F0:\n"
    "    .word 0x00000000\n"
    ".size D_005559F0, 4\n"
    ".globl D_005559F4\n"
    ".type D_005559F4, @object\n"
    "D_005559F4:\n"
    "    .word 0x00000080\n"
    "    .word D_00555AF8\n"
    "    .word 0x002751E0\n"
    "    .word 0x00000000\n"
    "    .word 0x000000FF\n"
    "    .word D_00555AE0\n"
    "    .word 0x002751E4\n"
    "    .word 0x00000000\n"
    "    .word 0x000000FF\n"
    "    .word D_00555AC8\n"
    "    .word 0x002751E8\n"
    "    .word 0x00000000\n"
    "    .word 0x000000FF\n"
    "    .word D_00555AB0\n"
    "    .word 0x002751D0\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    "    .word D_00555A98\n"
    "    .word 0x002751D4\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    "    .word D_00555A80\n"
    "    .word 0x002751D8\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    "    .word D_00555A68\n"
    "    .word 0x002751DC\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    ".size D_005559F4, 116\n"
    ".section .text\n"
);
const char D_00555A68[0x18] = " Shadow Blend 1/64 ";
const char D_00555A80[0x18] = " Shadow Blend 1/16 ";
const char D_00555A98[0x18] = " Shadow Blend 1/4  ";
const char D_00555AB0[0x18] = " Shadow Blend 1/1  ";
const char D_00555AC8[0x18] = " Shadow Color B    ";
const char D_00555AE0[0x18] = " Shadow Color G    ";
const char D_00555AF8[0x18] = " Shadow Color R    ";
const char D_00555B10[0x18] = " Shadow Depth      ";
INCLUDE_RODATA("asm/nonmatchings/src/StageAnimation", D_00555B28);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ContinueAnimation);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ResetAnimation);

const unsigned int D_00555B70[0x10] = { 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

void stage_CalcAnimationNoParent(int val) {
    D_00631D54 = val;
}

extern void *func_0013ECF8(void *obj);
extern void *isysGObjRemoveObjDL(int a0);

void stage_CalcAnimationParent(int a0, int a1) {
    void *obj;
    for (obj = isysGObjRemoveObjDL(a0); obj != 0; obj = func_0013ECF8(obj)) {
        void *node = *(void **)((char *)obj + 0x15C);
        if (node != 0) {
            void *dl = *(void **)((char *)node + 0x820);
            if (dl != 0) {
                void *x = *(void **)((char *)node + 0x824);
                if (x != 0) {
                    if (*(short *)((char *)dl + 0x30) == a0) {
                        *(long long *)((char *)x + 0x30) =
                            (*(long long *)((char *)x + 0x30) & ~0x04000000) |
                            ((long long)(a1 & 1) << 26);
                    }
                }
            }
        }
    }
}

void stage_DispAnimation(char *a0, float f12)
{
    if (f12 > 0.0f) {
        *((float *)(((char *)(*((int *)(a0 + 0x824)))) + 0x3C)) = f12;
        return;
    }
    {
        float src = *((float *)(((char *)(*((int *)(a0 + 0x820)))) + 0x3C));
        *((float *)(((char *)(*((int *)(a0 + 0x824)))) + 0x3C)) = src;
    }
}

extern int D_00631D50;

void stage_SetScale(int a0) {
    void *obj;
    D_00631D50 = 0;
    D_00631D54 = 0;
    for (obj = isysGObjRemoveObjDL(a0); obj != 0; obj = func_0013ECF8(obj)) {
        void *node = *(void **)((char *)obj + 0x15C);
        if (node != 0) {
            void *dl = *(void **)((char *)node + 0x820);
            if (dl != 0) {
                void *x = *(void **)((char *)node + 0x824);
                if (x != 0) {
                    *(long long *)((char *)x + 0x30) &= ~0x04000000;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimation);

const char D_00555BF8[0x18] = "src/StageAnimation.c";
const char D_00555C10[0x28] = "Too much Stage Animation Objects.\n";

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimationDissolve);

const char D_00555C68[0x30] = "stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n\0\0";
const char D_00555C98[0x30] = "1ステージ中の BgAnimation の種類が多すぎます\n\0\0\0";
const char D_00555CC8[0x30] = "stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました\n\0\0";

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_MakePlayBgAnimation);

const unsigned int D_00555D20[0x16] = { 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x656C6C49, 0x206C6167, 0x756F7247, 0x6F4E2070, 0x6425202E, 0x0000000A };
const char D_00555D78[0x38] = "stage_CheckAnimationFinish:illegal Animation No.\n";
const char D_00555DB0[0x30] = "stage_ContinueAnimation:illegal Animation No.\n";
const char D_00555DE0[0x48] = "指定したIDが存在しないか、アニメーションが読み込まれていません.\n\0\0\0\0\0\0\0\0";
const char D_00555E28[0x48] = "ステージセグメントにメモリが確保できません.(ヒープメモリ不足)\n\0\0\0\0\0\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_KillPlayBgAnimation);

extern int bga_SetCamFrame(int a0);
extern int font_CheckAlign(int a0);
extern void func_001AD768(void *a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

int stage_DispBgAnimation(int a0, int a1) {
    int i;
    char *e = (char *)D_00674058;
    for (i = 0; i < D_00633C54; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
                case 0:
                    if (bga_SetCamFrame(*(int *)(e + 0x284)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
                case 1:
                    if (font_CheckAlign(*(int *)(e + 0x288)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
            }
        }
    }
    debug_assertMessage(D_00555DB0);
    func_001AD768(D_00555BF8, 0x38D);
    func_00263FF0(D_00555BF8, 0x38D, D_00631D88);
    return 0;
}

void stage_SetCameraForceOff(void)
{
    func_001FAA58();
    if (D_00274ED4[0] != 0) return;
    func_00117768();
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFinish);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFrame);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetLoopFlag);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetFrameStep);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetParentOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetParentOfGObjWithLocalRotationFlag);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetLocalizeGeometry);

void stage_KillPlayBgAnimationIfOverMaxCount(int **self)
{
    int *node = *self;
    int *next;
    int *prev;
    if (node == 0) return;
    next = (int *)node[0x10 / 4];
    if (next != 0) {
        next[0x14 / 4] = node[0x14 / 4];
    } else {
        D_00633C58 = (int *)node[0x14 / 4];
        node = *self;
    }
    prev = (int *)node[0x14 / 4];
    if (prev != 0) {
        prev[0x10 / 4] = node[0x10 / 4];
    }
    if (D_00633C58 != 0) {
        D_00633C58[0x10 / 4] = 0;
    }
    resetmallocseki(*self);
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFrameIn);

void func_0012AA78(int a0, int a1, int a2, int a3)
{
    font_GetWidth(a0, a1, a2, a3);
}

int func_0012AA80(int key)
{
    int count = *(volatile int *)&D_00633C54;
    int i = 0;
    char *e = (char *)D_00674058;
    if (count > 0) {
        do {
            int *entry1 = *(int **)(e + 0x280);
            if (key == entry1[0x58 / 4]) {
                int v = *(int *)(e + 0x28C) >> 30;
                switch (v) {
                case 0: return bga_SetCamFrame(*(int *)(e + 0x284));
                case 1: return font_CheckAlign(*(int *)(e + 0x288));
                }
            }
            i++;
            e += 0x290;
        } while (i < count);
    }
    debug_assertMessage(D_00555D78);
    func_001AD768(D_00555BF8, 0x360);
    func_00263FF0(D_00555BF8, 0x360, D_00631D88);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AB50);

void func_0012ABE0(int key, int a1)
{
    int count = *(volatile int *)&D_00633C54;
    int i;
    char *e = (char *)D_00674058;
    for (i = 0; i < count; i++, e += 0x290) {
        int *p = *(int **)(e + 0x280);
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = a1;
            p = &(*((volatile int *)(&D_00633C54)));
            count = *p;
        }
    }
}

void func_0012AC28(int target, int val)
{
    int n = D_00633C54;
    char *p = (char *)D_00674058;
    int i;
    if (n <= 0) return;
    i = n;
    do {
        int *entry1 = *(int **)(p + 0x280);
        if (target == entry1[0x58 / 4]) {
            int *entry2 = *(int **)(p + 0x284);
            *(float *)((char *)entry2 + 0x1C) = (float)val;
        }
        p += 0x290;
    } while (--i);
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AC70);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012ACD8);

