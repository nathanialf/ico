#include "common.h"
#include "typedef.h"
#include "debug.h"
#include "Shadow.h"

extern char D_0054FD50[];
extern char *matrixptr;
/* kept local: this TU's uses of _CopyVector do not fit the prototype in Matrix.h */
extern void _CopyVector(void *a0, void *a1);
/* kept local: this TU's uses of _SetCurrentMatrix do not fit the prototype in Matrix.h */
extern void _SetCurrentMatrix(void *a0);
/* kept local: this TU's uses of _ClearTransCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ClearTransCurrentMatrix(void);
/* kept local: this TU's uses of _ApplyCurrentMatrix do not fit the prototype in Matrix.h */
extern void _ApplyCurrentMatrix(void *a0, void *a1);
/* kept local: this TU's uses of _NormalizeVector do not fit the prototype in Matrix.h */
extern void _NormalizeVector(void *a0, void *a1);
/* kept local: this TU's uses of _PopCurrentMatrix do not fit the prototype in Matrix.h */
extern void _PopCurrentMatrix(void);
/* kept local: this TU's uses of _PushCurrentMatrix do not fit the prototype in Matrix.h */
extern void _PushCurrentMatrix(void *a0);
/* kept local: this TU's uses of _ScaleVector do not fit the prototype in Matrix.h */
extern void _ScaleVector(void *a0, void *a1, float a2);
/* kept local: this TU's uses of _TransposeCurrentMatrix do not fit the prototype in Matrix.h */
extern void _TransposeCurrentMatrix(void);
/* kept local: this TU's uses of these do not fit the prototypes in Matrix.h */
extern void _ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);
extern void _InterVectorXYZ(void *a0, void *a1, void *a2, float t);
extern void _MulCurrentMatrixL(void *a0);
extern void _InitCurrentMatrix(void);
extern void _MulCurrentMatrixR(void *a0);
extern void _GetCurrentMatrix(void *a0);
/* one skinning matrix per cluster, built by shadow_EntryClusterShadow */
extern char D_0067C070[];
extern int D_0063A17C;
extern int D_0063A178;

/* The display-list packet builder state, the record src/GifPacket.c carries
 * as GifDpk; this function opens, fills and closes a PATH1 packet of its own.
 * RECONSTRUCTION: this TU holds every packet address (dma, ptr, tail, gif,
 * end) as one pointer union, read and written through its members, so each
 * field access is alias set 0 (c-common.c c_get_alias_set: a reference
 * through a union). WHAT THE BYTES PIN: the open's gif = 0, end = 0 and
 * ptr = c + 8 stores survive flow's dead-store scan, so the int tag word
 * store between them and their second stores may alias them; the screen-size
 * loads wait for that tag store, so it is an int store outside any struct;
 * and the close's end load waits for the last A+D packet store, which only a
 * field read that may alias the unsigned long long packet words does (the
 * ROM's end-tag arithmetic reuses the final cursor's register, so the cursor
 * store precedes it in sched1, and that register file is what leaves t7 to
 * reload for the whole function). WHAT THEY CANNOT PIN: the member names and
 * types beyond one 64-bit packet pointer and one byte pointer, or the names
 * of the union and the record in the dev's header. */
typedef union {
    unsigned long long *d;
    char *c;
} ShadowPkPtr;

typedef struct {
    int cur;
    int *buf[2];
    ShadowPkPtr dma;
    ShadowPkPtr ptr;
    ShadowPkPtr tail;
    ShadowPkPtr gif;
    ShadowPkPtr end;
} ShadowDpk;

extern ShadowDpk D_004EE6F0;
/* the screen width and height in pixels */
extern int D_0063A064;
extern int D_0063A068;
/* kept local: this TU's uses of these do not fit the prototypes in the headers */
extern void tex_LockHeadTBP(int tbp, int pri);
extern void dl_SetDLPriority(int pri);
extern void dl_OpenDma(int chan, void *dma, int flag);
extern void dl_CloseDma(void);

/* The GS A+D writer, a MACRO as in Texture.c: the listing puts every writer's
 * value and both of its stores on the line of the use (337 carries FRAME,
 * SCISSOR and XYOFFSET together, 340 the whole sprite), where an inlined
 * function would carry its own lines. */
#define setGsReg(reg, val)                                                                         \
    {                                                                                              \
        *D_004EE6F0.ptr.d++ = (val);                                                               \
        *D_004EE6F0.ptr.d++ = (reg);                                                               \
    }
/* The PATH1 packet open and close, written out here and not called: the
 * listing puts every instruction of each on ONE line of Shadow.c (332 for the
 * open), where an inlined function body would carry src/GifPacket.c's own
 * lines, so both are MACROS in the dev's TU and gif_StartPacketPath1 keeps its
 * out-of-line copy at its own ROM slot. The statements are, one for one, the
 * ones that file's matched gif_StartPacketPath1 and gif_EndPacketPath1 carry
 * (the close, on line 351, is written out at its site below). */
#define gifStartPacketPath1(c)                                                                     \
    {                                                                                              \
        (c) = D_004EE6F0.ptr.c;                                                                    \
        D_004EE6F0.gif.c = 0;                                                                      \
        D_004EE6F0.end.c = 0;                                                                      \
        D_004EE6F0.dma.c = (c);                                                                    \
        D_004EE6F0.tail.c = (c);                                                                   \
        D_004EE6F0.ptr.c = ((c) + 8);                                                              \
        *(unsigned int *)((c) + 8) = 0x11000000;                                                   \
        D_004EE6F0.gif.c = ((c) + 0xC);                                                            \
        D_004EE6F0.end.c = ((c) + 0x10);                                                           \
        D_004EE6F0.ptr.c = ((c) + 0x18);                                                           \
        ((GifPkWord *)((c) + 0x18))->d = 0xE;                                                      \
        D_004EE6F0.ptr.c = ((c) + 0x20);                                                           \
    }
/* FRAME_1, SCISSOR_1 and XYOFFSET_1 for a w by h buffer at base fbp, the
 * window centred on the GS's 2048.0 origin and moved by ox, oy sixteenths. A
 * MACRO: the listing puts all six stores of each use on one line (337, 342,
 * 432, 444, 462). */
#define setFrame(fbp, w, h, ox, oy)                                                                \
    {                                                                                              \
        setGsReg(0x4C, (fbp) | ((long long)(((w) >> 6) & 0x3F) << 16));                            \
        setGsReg(0x40, ((long long)((w) - 1) << 16) | ((long long)((h) - 1) << 48));               \
        setGsReg(0x18, (((long long)(2048 - (w) / 2) << 4) + (ox)) |                               \
                           ((((long long)(2048 - (h) / 2) << 4) + (oy)) << 32));                   \
    }
/* RGBAQ packed from a four-byte colour, as src/GifPacket.c packs it */
#define GIF_RGBA(c)                                                                                \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
/* XYZ2 with the 2048.0-pixel window origin folded in, and without it */
#define GIF_XY0(x, y, z) ((long long)(x) | ((long long)(y) << 16) | ((z) << 32))
#define GIF_XY(x, y, z)                                                                            \
    ((long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16) | ((z) << 32))
/* The untextured sprite: PRIM, RGBAQ and the two XYZ2 corners of the rect r
 * (x, y, w, h in sixteenths). The far corner is x + fx with fx = w + 0x8000,
 * as GsBase.c's gsbSpriteNoTexture holds it: the ROM adds 0x8000 to w and h
 * first (`addu a2,a2,t3`, `addu a3,a3,t3`) and x and y to those sums, where
 * a textual x + w + 0x8000 is reassociated by fold. A MACRO: the listing puts
 * the whole sprite on the line of the use (340, 345) and shows no rows of a
 * helper. */
#define spriteRect(r, col, prim)                                                                   \
    {                                                                                              \
        setGsReg(0x00, prim);                                                                      \
        setGsReg(0x01, GIF_RGBA(col));                                                             \
        setGsReg(0x05, GIF_XY((r)[0], (r)[1], 0xFFFFFFFFLL));                                      \
        {                                                                                          \
            int fx = (r)[2] + 0x8000;                                                              \
            int fy = (r)[3] + 0x8000;                                                              \
                                                                                                   \
            setGsReg(0x05, GIF_XY0((r)[0] + fx, (r)[1] + fy, 0xFFFFFFFFLL));                       \
        }                                                                                          \
    }

void shadow_Reset(void)
{
    char *c;
    char *p;
    char *q;

    if (D_0063A17C != D_0063A178) {
        D_0063A178 = D_0063A17C;
    }
    tex_LockHeadTBP(0x3D80, 3);
    dl_SetDLPriority(3);
    gifStartPacketPath1(c);
    {
        int full[4] = {-D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16, D_0063A064 * 16,
                       D_0063A068 * 16};
        int band[4] = {-D_0063A064 / 2 * 16, -D_0063A068 / 2 * 16, D_0063A064 * 16, 256};
        unsigned char col[4] = {0};

        setFrame(0x140, D_0063A064, D_0063A068, 0, 0);
        setGsReg(0x4E, 0xC0 | ((long long)0x30 << 24) | ((long long)1 << 32));
        setGsReg(0x47, 0x30000);
        spriteRect(band, col, 0x406);

        setFrame(0x142, D_0063A064, D_0063A068, 0, 0);
        setGsReg(0x4E, 0xC0 | ((long long)0x30 << 24) | ((long long)1 << 32));
        setGsReg(0x47, 0x30000);
        spriteRect(full, col, 0x406);

        setGsReg(0x4A, 0);
        setGsReg(0x3B, 0x80 | ((long long)0x80 << 32));
        setGsReg(0x47, 0x50000);
        setGsReg(0x42, 0x68 | ((long long)0x80 << 32));
        setGsReg(0x46, 0);
    }
    ((GifPkWord *)D_004EE6F0.end.c)->d =
        (unsigned int)(((unsigned int)(D_004EE6F0.ptr.c - D_004EE6F0.end.c) >> 4) - 1) |
        0x1000000000008000LL;
    ((GifPkWord *)D_004EE6F0.gif.c)->w[0] =
        (((unsigned int)(D_004EE6F0.ptr.c - D_004EE6F0.gif.c) >> 4) << 16) | 0x6C008000;
    p = D_004EE6F0.ptr.c;
    ((GifPkWord *)p)->w[0] = 0x15000000;
    p += 4;
    D_004EE6F0.ptr.c = p;
    ((GifPkWord *)p)->w[0] = 0;
    D_004EE6F0.ptr.c = (p + 4);
    ((GifPkWord *)(p + 4))->w[0] = 0;
    D_004EE6F0.ptr.c = (p + 8);
    ((GifPkWord *)(p + 8))->w[0] = 0;
    D_004EE6F0.ptr.c = (p + 0xC);
    ((GifPkWord *)D_004EE6F0.tail.c)->d =
        (unsigned int)((((unsigned int)(D_004EE6F0.ptr.c - D_004EE6F0.tail.c) >> 4) - 1) |
                       0x10000000);
    q = D_004EE6F0.ptr.c;
    D_004EE6F0.tail.c = q;
    ((GifPkWord *)q)->d = 0x60000000;
    D_004EE6F0.ptr.c = (q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    D_004EE6F0.ptr.c = (q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    D_004EE6F0.ptr.c = (q + 0x10);
    dl_OpenDma(5, D_004EE6F0.dma.c, 0);
    dl_CloseDma();
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_Draw);

void shadow_Render(void)
{
    /* CRUTCH: zero-code frame reservation. The body is one printf stub and ROM
       still reserves 16 bytes of vars, so the vector the stub printed was a
       local here. Deleting it changes the object. See docs/crutch_ledger.md. */
    float buf[4];
    debug_StdPrintfDummy(D_0054FD50);
}

void shadow_getShadowVectorAverage(void *a0, char *a1)
{
    _CopyVector(a0, a1 + 0x860);
    _SetCurrentMatrix(matrixptr + 0x80);
    _ClearTransCurrentMatrix();
    _ApplyCurrentMatrix(a0, a0);
    _NormalizeVector(a0, a0);
}

/* the same quadword copy type src/Primitive.c uses: the accumulator reset is
 * one lq/sq pair per vertex */
typedef int Qw128 __attribute__((mode(TI)));

/* one weighted vertex of a cluster run: the vertex it moves and the weight it
 * moves it by */
typedef struct ClusterWeight {
    int idx;
    float w;
    int _8;
    int _C;
} ClusterWeight;

/* one cluster of a shadow volume: the -1 terminated run of weighted vertices
 * and the matrix slot it is skinned through */
typedef struct ClusterPoly {
    ClusterWeight *run;
    int matrix;
    int _8;
    int _C;
} ClusterPoly;

/* The listing puts this body at rows 619-620, inside shadow_EntryClusterShadow's
 * own line span. One asm block: the weight goes through $8 by hand and the
 * three vnop runs are scheduled around the multiply and the accumulate. */
static inline void applyWeightedVtx(void *dst, void *src, float w)
{
    __asm__ __volatile__("lqc2 $vf8, 0(%1)\n\t"
                         "lqc2 $vf9, 0(%0)\n\t"
                         "mfc1 $8, %2\n\t"
                         "qmtc2.ni $8, $vf11\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                         "vmaddw.xyzw $vf10, $vf7, $vf0w\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vmulx.xyz $vf10, $vf10, $vf11x\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vadd.xyz $vf9, $vf9, $vf10\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "sqc2 $vf9, 0(%0)"
                         :
                         : "r"(dst), "r"(src), "f"(w)
                         : "$8");
}

void shadow_EntryClusterShadow(char *a0, float a1)
{
    VECTOR zero = {0.0f, 0.0f, 0.0f, 1.0f};
    float v[4];
    float sa[4];
    float sb[4];
    char *x = *(char **)(a0 + 0x858);
    char *p;
    int i;
    unsigned int k;

    _InitCurrentMatrix();
    shadow_getShadowVectorAverage(v, a0);
    _ScaleVectorXYZ(sa, v, a1);
    _ScaleVectorXYZ(sb, v, 4.0f);

    for (i = 0; i < *(int *)(a0 + 8); i++) {
        _SetCurrentMatrix(*(char **)(a0 + 0xC) + i * 0x40);
        _MulCurrentMatrixR(*(char **)(a0 + 0x90) + i * 0x40);
        _MulCurrentMatrixL(matrixptr + 0x80);
        _GetCurrentMatrix(D_0067C070 + i * 0x40);
    }

    __asm__ __volatile__("lq $8, 0(%0)" : : "r"(&zero) : "$8");
    for (i = 0, p = *(char **)(x + 0x40); i < *(char *)(x + 0x2E); i++, p += 0x180) {
        for (k = 0; k < *(unsigned int *)(p + 0x94); k++) {
            __asm__ __volatile__("sq $8, 0(%0)" : : "r"((Qw128 *)*(char **)(p + 0x174) + k) : "$8");
        }
    }

    for (i = 0, p = *(char **)(x + 0x40); i < *(char *)(x + 0x2E); i++, p += 0x180) {
        for (k = 0; k < *(unsigned int *)(p + 0xF4); k++) {
            ClusterWeight *e;
            VECTOR *dst;
            VECTOR *src;

            _SetCurrentMatrix(D_0067C070 + (*(ClusterPoly **)(p + 0xF0))[k].matrix * 0x40);
            e = (*(ClusterPoly **)(p + 0xF0))[k].run;
            /* the listing gives both base loads the run load's row (648) and
             * the -1 of the loop test the next row (649): they are read once
             * here, ahead of the loop, not inside it */
            dst = *(VECTOR **)(p + 0x174);
            src = *(VECTOR **)(p + 0x90);
            do {
                applyWeightedVtx(dst + e->idx, src + e->idx, e->w);
            } while ((++e)->idx != -1);
        }
        for (k = 0; k < *(unsigned int *)(p + 0x94); k++) {
            _AddVectorXYZ(*(char **)(p + 0x178) + k * 16, *(char **)(p + 0x174) + k * 16, sa);
            _AddVectorXYZ(*(char **)(p + 0x174) + k * 16, *(char **)(p + 0x174) + k * 16, sb);
        }
    }

    for (i = 0, p = *(char **)(x + 0x40); i < *(char *)(x + 0x2E); i++, p += 0x180) {
        VECTOR *va = (VECTOR *)*(char **)(p + 0x174);
        VECTOR *vb = (VECTOR *)*(char **)(p + 0x178);

        for (k = 0; k < *(unsigned int *)(p + 0x94); k++) {
            if (1.0f <= va[k].z && 1.0f <= vb[k].z) {
            } else if (va[k].z < 1.0f && vb[k].z < 1.0f) {
                vb[k].w = -1.0f;
                va[k].w = -1.0f;
            } else if (vb[k].z < 1.0f) {
                _InterVectorXYZ(&vb[k], &va[k], &vb[k],
                                1.0f - (va[k].z - 1.0f) / (va[k].z - vb[k].z));
            } else if (va[k].z < 1.0f) {
                _InterVectorXYZ(&va[k], &vb[k], &va[k],
                                1.0f - (vb[k].z - 1.0f) / (vb[k].z - va[k].z));
            }
        }
    }
}

/* The listing puts this body at rows 750-751, inside shadow_EntryNormalShadow's
 * own line span, so the dev wrote it at the head of that function. One asm
 * block because the two vnop runs are hand scheduled around the multiply, and
 * both addresses are "r" operands: the ROM's copy reaches them in $3 and $2,
 * the registers the surrounding loop allocates, not in the argument
 * registers a fixed spelling would force. */
static inline void applyCurrentMatrixV(void *dst, void *src)
{
    __asm__ __volatile__("lqc2 $vf8, 0(%1)\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf8x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf8y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf8z\n\t"
                         "vmaddw.xyzw $vf9, $vf7, $vf0w\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "sqc2 $vf9, 0(%0)"
                         :
                         : "r"(dst), "r"(src));
}

void shadow_EntryNormalShadow(char *a0, int a1, float a2)
{
    float v[4];
    float sa[4];
    float sb[4];
    char *x = *(char **)(a0 + 0x858);
    int i;
    int j;
    char *p;

    shadow_getShadowVectorAverage(v, a0);
    _ScaleVectorXYZ(sa, v, a2);
    _ScaleVectorXYZ(sb, v, 4.0f);
    _SetCurrentMatrix(*(char **)(a0 + 0xC) + a1 * 0x40);
    _MulCurrentMatrixL(matrixptr + 0x80);

    p = *(char **)(x + 0x40);
    for (i = 0; i < *(char *)(x + 0x2E); i++, p += 0x180) {
        for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
            applyCurrentMatrixV(*(char **)(p + 0x174) + j * 16, *(char **)(p + 0x90) + j * 16);
        }
        for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
            _AddVectorXYZ(*(char **)(p + 0x178) + j * 16, *(char **)(p + 0x174) + j * 16, sa);
            _AddVectorXYZ(*(char **)(p + 0x174) + j * 16, *(char **)(p + 0x174) + j * 16, sb);
        }
    }

    p = *(char **)(x + 0x40);
    for (i = 0; i < *(char *)(x + 0x2E); i++, p += 0x180) {
        VECTOR *va = (VECTOR *)*(char **)(p + 0x174);
        VECTOR *vb = (VECTOR *)*(char **)(p + 0x178);

        for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
            if (1.0f <= va[j].z && 1.0f <= vb[j].z) {
            } else if (va[j].z < 1.0f && vb[j].z < 1.0f) {
                vb[j].w = -1.0f;
                va[j].w = -1.0f;
            } else if (vb[j].z < 1.0f) {
                _InterVectorXYZ(&vb[j], &va[j], &vb[j],
                                1.0f - (va[j].z - 1.0f) / (va[j].z - vb[j].z));
            } else if (va[j].z < 1.0f) {
                _InterVectorXYZ(&va[j], &vb[j], &va[j],
                                1.0f - (vb[j].z - 1.0f) / (vb[j].z - va[j].z));
            }
        }
    }
}

void __GetCameraPos(void *a0)
{
    _PushCurrentMatrix(a0);
    _SetCurrentMatrix(matrixptr + 0x80);
    _ClearTransCurrentMatrix();
    _TransposeCurrentMatrix();
    _ApplyCurrentMatrix(a0, matrixptr + 0xB0);
    _ScaleVector(a0, a0, -1.0f);
    *(float *)((char *)a0 + 0xC) = 1.0f;
    _PopCurrentMatrix();
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_RenderVolume);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Shadow", shadow_RenderVolumeMulti);

extern void *mallocseki(int size);

/* The three record shapes shadow_MakeObjectData copies out of the model into
 * its own heap. The vertex and polygon records are eight-byte aligned, which
 * is what makes the ROM copy them with ld/sd pairs; the strip record starts
 * with a short count and is only two-byte aligned, so its copy is ldl/ldr. */
typedef struct ShadowVtx {
    int _0;
    int _4;
    int _8;
    int _C;
} __attribute__((aligned(16))) ShadowVtx;

typedef struct ShadowPoly {
    ShadowVtx *pts;
    int _4;
    int _8;
    int _C;
} __attribute__((aligned(16))) ShadowPoly;

typedef struct ShadowRun {
    short count;
    char _2[0xE];
} ShadowRun;

void shadow_MakeObjectData(char *a0)
{
    int i;
    int j;
    int l;
    /* zeroed here and again after each polygon, so the scan starts from a
     * value carried round the loop (the ROM clears it in the outer loop's
     * preheader and in the polygon loop's latch, never before the scan) */
    int m = 0;
    int n;
    int c;
    char *p;
    ShadowVtx *q;
    ShadowPoly *r;
    ShadowVtx *t;
    ShadowRun **s;
    ShadowRun *u;

    for (i = 0; i < *(char *)(a0 + 0x2E); i++) {
        p = *(char **)(a0 + 0x40) + i * 0x180;
        if (*(char *)(a0 + 0x2F) != 0) {
            *(void **)(p + 0x174) = mallocseki(*(unsigned int *)(p + 0x94) * 16);
            *(void **)(p + 0x178) = mallocseki(*(unsigned int *)(p + 0x94) * 16);
            q = (ShadowVtx *)mallocseki(*(unsigned int *)(p + 0x94) * 16);
            for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
                _CopyVector(&q[j], *(char **)(p + 0x90) + j * 16);
            }
            *(ShadowVtx **)(p + 0x90) = q;

            r = (ShadowPoly *)mallocseki(*(unsigned int *)(p + 0xF4) * 16);
            for (j = 0; j < *(unsigned int *)(p + 0xF4); j++) {
                r[j] = (*(ShadowPoly **)(p + 0xF0))[j];
                while (r[j].pts[m]._0 != -1) {
                    m++;
                }
                t = r[j].pts = (ShadowVtx *)mallocseki((m + 1) * 16);
                for (l = 0; l < m + 1; l++) {
                    *t++ = (*(ShadowPoly **)(p + 0xF0))[j].pts[l];
                }
                m = 0;
            }
            *(ShadowPoly **)(p + 0xF0) = r;
        } else {
            *(void **)(p + 0x174) = mallocseki(*(unsigned int *)(p + 0x94) * 16);
            *(void **)(p + 0x178) = mallocseki(*(unsigned int *)(p + 0x94) * 16);
            q = (ShadowVtx *)mallocseki(*(unsigned int *)(p + 0x94) * 16);
            for (j = 0; j < *(unsigned int *)(p + 0x94); j++) {
                _CopyVector(&q[j], *(char **)(p + 0x90) + j * 16);
            }
            *(ShadowVtx **)(p + 0x90) = q;
        }

        s = (ShadowRun **)mallocseki(*(unsigned int *)(p + 0x104) * 4);
        /* the strip pass reuses the outer loop's own index, which is what
         * makes the ROM step the outer loop on from where this one ended */
        for (i = 0; i < *(unsigned int *)(p + 0x104); i++) {
            u = (*(ShadowRun ***)(p + 0x100))[i];
            n = 0;
            for (;;) {
                c = u->count;
                if (c == 0) {
                    break;
                }
                u += c + 1;
                n += c + 1;
            }
            n++;
            s[i] = (ShadowRun *)mallocseki(n * 16);
            for (j = 0; j < n; j++) {
                s[i][j] = (*(ShadowRun ***)(p + 0x100))[i][j];
            }
        }
        *(ShadowRun ***)(p + 0x100) = s;
    }
}

inline void shadow_KillShadow(int val)
{
    D_0063A17C = val;
}

inline void shadow_DispCancel(int a0, int a1)
{
    char *obj = isysGObjGetExist_begin(a0);
    if (obj != 0) {
        long long bit = (long long)(a1 & 1) << 26;
        do {
            char *node = *(char **)(obj + 0x15C);
            if (node != 0) {
                char *dl = *(char **)(node + 0x854);
                if (dl != 0) {
                    char *x = *(char **)(node + 0x858);
                    if (x != 0) {
                        if (*(short *)(dl + 0x30) == a0) {
                            *(long long *)(x + 0x30) =
                                (*(long long *)(x + 0x30) & ~0x04000000) | bit;
                        }
                    }
                }
            }
            obj = isysGObjGetExist_next(obj);
        } while (obj != 0);
    }
}

inline void shadow_SetLength(char *a0, float f)
{
    if (0.0f < f) {
        *(float *)(*(char **)(a0 + 0x858) + 0x3C) = f;
    } else {
        *(float *)(*(char **)(a0 + 0x858) + 0x3C) = *(float *)(*(char **)(a0 + 0x854) + 0x3C);
    }
}

inline void shadow_Init(void)
{
    char *obj;
    D_0063A178 = 0;
    D_0063A17C = 0;
    for (obj = isysGObjGetExist_begin(); obj != 0; obj = isysGObjGetExist_next(obj)) {
        char *node = *(char **)(obj + 0x15C);
        if (node != 0) {
            char *dl = *(char **)(node + 0x854);
            if (dl != 0) {
                char *x = *(char **)(node + 0x858);
                if (x != 0) {
                    *(long long *)(x + 0x30) &= ~0x04000000;
                }
            }
        }
    }
}

/* one row of the shadow tool: the name it prints, the variable it edits and
 * the range it wraps that variable through */
typedef struct ShadowToolRow {
    char *name;
    int *val;
    int min;
    int max;
} ShadowToolRow;

extern ShadowToolRow D_0054FE18[];
/* the two menu colours, unselected then selected */
extern unsigned int D_0054FF58[];
/* "Shadow Tool" */
extern char D_0054FF60[];
/* "%s : %s" */
extern char D_0063A198[];
/* "%s : %d" */
extern char D_0063A1A0[];
/* "Shadow %s => %s\n" */
extern char D_0054FF70[];
/* "Shadow %s => %d\n" */
extern char D_0054FF88[];
/* the names a 0/1 row prints instead of its number */
extern char *D_00290B50[];
/* the row the tool has selected */
extern int D_0063A194;

/* the pad record this TU reads, the same one common/src/layout_action.c calls
 * R58: the flag word it tests for the two buttons at 4 and the auto-repeat
 * word it tests for the four directions at 0xC */
typedef struct PadRec {
    int _0;
    int flags;
    int _8;
    int repeat;
    char _10[0x48];
} PadRec;

extern PadRec D_0028F8F0[];

int shadow_Tool(void)
{
    int ret = 0;
    int i;

    debug_PrintfDummy(10, 50, 0xFF800000u, (int)D_0054FF60);
    for (i = 0; i < 8; i++) {
        if (D_0054FE18[i].min == 0 && D_0054FE18[i].max == 1) {
            debug_PrintfDummy(0x12, (i + 1) * 8 + 50, D_0054FF58[D_0063A194 == i], (int)D_0063A198,
                              (int)D_0054FE18[i].name, (int)D_00290B50[*D_0054FE18[i].val]);
        } else {
            debug_PrintfDummy(0x12, (i + 1) * 8 + 50, D_0054FF58[D_0063A194 == i], (int)D_0063A1A0,
                              (int)D_0054FE18[i].name, *D_0054FE18[i].val);
        }
    }
    if (D_0028F8F0[0].repeat & 0x4000) {
        D_0063A194++;
        if (8 <= D_0063A194) {
            D_0063A194 = 0;
        }
    }
    if (D_0028F8F0[0].repeat & 0x1000) {
        D_0063A194--;
        if (D_0063A194 < 0) {
            D_0063A194 = 7;
        }
    }
    if (D_0028F8F0[0].repeat & 0x2000) {
        if (++*D_0054FE18[D_0063A194].val > D_0054FE18[D_0063A194].max) {
            *D_0054FE18[D_0063A194].val = D_0054FE18[D_0063A194].min;
        }
    }
    if (D_0028F8F0[0].repeat & 0x8000) {
        if (--*D_0054FE18[D_0063A194].val < D_0054FE18[D_0063A194].min) {
            *D_0054FE18[D_0063A194].val = D_0054FE18[D_0063A194].max;
        }
    }
    if (D_0028F8F0[0].flags & 0x20) {
        for (i = 0; i < 8; i++) {
            if (D_0054FE18[i].min == 0 && D_0054FE18[i].max == 1) {
                debug_StdPrintfDummy(D_0054FF70, D_0054FE18[i].name,
                                     D_00290B50[*D_0054FE18[i].val]);
            } else {
                debug_StdPrintfDummy(D_0054FF88, D_0054FE18[i].name, *D_0054FE18[i].val);
            }
        }
        ret = 1;
    }
    if (D_0028F8F0[0].flags & 0x40) {
        ret = -1;
    }
    if (ret != 0) {
        D_0063A194 = 0;
    }
    return ret;
}
