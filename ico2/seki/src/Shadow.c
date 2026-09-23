#include "common.h"
#include "typedef.h"
#include "debug.h"
#include "Shadow.h"

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

extern ShadowDpk PacketBufferStruct;
/* the screen width and height in pixels */
extern int ScreenWidth;
extern int ScreenHeight;
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
        *PacketBufferStruct.ptr.d++ = (val);                                                       \
        *PacketBufferStruct.ptr.d++ = (reg);                                                       \
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
        (c) = PacketBufferStruct.ptr.c;                                                            \
        PacketBufferStruct.gif.c = 0;                                                              \
        PacketBufferStruct.end.c = 0;                                                              \
        PacketBufferStruct.dma.c = (c);                                                            \
        PacketBufferStruct.tail.c = (c);                                                           \
        PacketBufferStruct.ptr.c = ((c) + 8);                                                      \
        *(unsigned int *)((c) + 8) = 0x11000000;                                                   \
        PacketBufferStruct.gif.c = ((c) + 0xC);                                                    \
        PacketBufferStruct.end.c = ((c) + 0x10);                                                   \
        PacketBufferStruct.ptr.c = ((c) + 0x18);                                                   \
        ((GifPkWord *)((c) + 0x18))->d = 0xE;                                                      \
        PacketBufferStruct.ptr.c = ((c) + 0x20);                                                   \
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
        int full[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16,
                       ScreenHeight * 16};
        int band[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16, 256};
        unsigned char col[4] = {0};

        setFrame(0x140, ScreenWidth, ScreenHeight, 0, 0);
        setGsReg(0x4E, 0xC0 | ((long long)0x30 << 24) | ((long long)1 << 32));
        setGsReg(0x47, 0x30000);
        spriteRect(band, col, 0x406);

        setFrame(0x142, ScreenWidth, ScreenHeight, 0, 0);
        setGsReg(0x4E, 0xC0 | ((long long)0x30 << 24) | ((long long)1 << 32));
        setGsReg(0x47, 0x30000);
        spriteRect(full, col, 0x406);

        setGsReg(0x4A, 0);
        setGsReg(0x3B, 0x80 | ((long long)0x80 << 32));
        setGsReg(0x47, 0x50000);
        setGsReg(0x42, 0x68 | ((long long)0x80 << 32));
        setGsReg(0x46, 0);
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
    PacketBufferStruct.ptr.c = p;
    ((GifPkWord *)p)->w[0] = 0;
    PacketBufferStruct.ptr.c = (p + 4);
    ((GifPkWord *)(p + 4))->w[0] = 0;
    PacketBufferStruct.ptr.c = (p + 8);
    ((GifPkWord *)(p + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = (p + 0xC);
    ((GifPkWord *)PacketBufferStruct.tail.c)->d =
        (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.tail.c) >>
                         4) -
                        1) |
                       0x10000000);
    q = PacketBufferStruct.ptr.c;
    PacketBufferStruct.tail.c = q;
    ((GifPkWord *)q)->d = 0x60000000;
    PacketBufferStruct.ptr.c = (q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = (q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    PacketBufferStruct.ptr.c = (q + 0x10);
    dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
    dl_CloseDma();
}

/* The textured sprite: PRIM, RGBAQ, then a UV and an XYZ2 pair for each
 * corner, the far corner as spriteRect holds it. A MACRO: the listing puts all
 * of it on the line of the use (440 and 457). */
#define spriteUV(r, uv, col, prim)                                                                 \
    {                                                                                              \
        setGsReg(0x00, prim);                                                                      \
        setGsReg(0x01, GIF_RGBA(col));                                                             \
        setGsReg(0x03, (long long)(uv)[0] | ((long long)(uv)[1] << 16));                           \
        setGsReg(0x05, GIF_XY((r)[0], (r)[1], 0xFFFFFFFFLL));                                      \
        setGsReg(0x03, (long long)((uv)[0] + (uv)[2]) | ((long long)((uv)[1] + (uv)[3]) << 16));   \
        {                                                                                          \
            int fx = (r)[2] + 0x8000;                                                              \
            int fy = (r)[3] + 0x8000;                                                              \
                                                                                                   \
            setGsReg(0x05, GIF_XY0((r)[0] + fx, (r)[1] + fy, 0xFFFFFFFFLL));                       \
        }                                                                                          \
    }

/* the 12.4 window offsets XYOFFSET_1 is programmed with for the screen pass */
extern int D_0063A074;
extern int D_0063A078;
/* the debug flag word: bit 0 turns the on-screen labels on */
extern int D_0063B13C;
/* "S", the one character label this pass prints */
extern char D_0063A180[];
/* kept local: this TU reads the stage setting record for its tint bytes only,
 * so it takes the byte view src/layout_texture.c also uses */
extern unsigned char D_0028F720[];
/* kept local: this TU's uses of these do not fit the prototypes in the headers */
extern void tex_UnlockHeadTBP(int pri);

void shadow_Draw(void)
{
    if (D_0063B13C & 1) {
        debug_Printf(500, ScreenHeight / 2 - 8, 0xCCCCCC00u, (int)D_0063A180);
    }
    {
        /* The four level tables are this block's statics: Shadow.o's .rodata
         * opens with them in this order (0x54FCB0, 0x54FCC0, 0x54FCD0,
         * 0x54FD10), and the listing leaves rows 382 to 409 code-free between
         * the label print and the rect initializer. As block statics they
         * give the ROM's register file and preheader order, where extern
         * placeholders left the loop-one preheader and the open's cursor
         * register off (strict 150 against 40 before the switch below). The
         * names are ours: the map lists none. */
        /* the frame buffer pointer of each shadow mipmap level */
        static const unsigned int levelFbp[4] = {0x142, 0x1C2, 0x1E2, 0x1EA};
        /* the texture base pointer of each shadow mipmap level */
        static const unsigned int levelTbp[4] = {0x2840, 0x3840, 0x3C40, 0x3D40};
        /* the sprite corner and size of each level in 12.4 screen units */
        static const int levelRect[4][4] = {{-4100, -4100, 8192, 8192},
                                            {-2052, -2052, 4096, 4096},
                                            {-1028, -1028, 2048, 2048},
                                            {-516, -516, 1024, 1024}};
        /* the sprite texture rectangle of each level at the 512 pixel default */
        static const int levelUV[4][4] = {
            {4, 4, 8192, 8192}, {4, 4, 4096, 4096}, {4, 4, 2048, 2048}, {4, 4, 1024, 1024}};
        int rect[4][4] = {{4, 4, ScreenWidth * 16, ScreenHeight * 16},
                          {4, 4, ScreenWidth * 8, ScreenHeight * 8},
                          {4, 4, ScreenWidth * 4, ScreenHeight * 4},
                          {4, 4, ScreenWidth * 2, ScreenHeight * 2}};
        int off[4] = {-(ScreenWidth >> 1) * 16, -(ScreenHeight >> 1) * 16, ScreenWidth * 16,
                      ScreenHeight * 16};
        unsigned char col[4] = {128, 128, 128, D_0028F720[0xAC]};
        int dbg = 0; /* local debug switch, see the test in the upward loop */
        int i;
        char *c;
        char *q;

        dl_SetDLPriority(3);
        gifStartPacketPath1(c);
        setGsReg(0x47, 0x30000);
        setGsReg(0x4E, 0xC0 | ((long long)0x30 << 24) | ((long long)1 << 32));
        setGsReg(0x46, 1);
        setGsReg(0x4A, 0);
        setGsReg(0x3B, 0x8080 | ((long long)0x80 << 32));
        setGsReg(0x14, 0x60);

        for (i = 0; i < 3; i++) {
            setFrame(levelFbp[i + 1], 512 >> (i + 1), 512 >> (i + 1), 0, 0);
            if (i == 0) {
                *PacketBufferStruct.ptr.d++ = levelTbp[i] | ((long long)(512 >> i) / 64 << 14) |
                                              ((long long)1 << 20) | ((long long)(9 - i) << 26) |
                                              ((long long)(9 - i) << 30) |
                                              ((long long)0x8000 << 19);
                *PacketBufferStruct.ptr.d++ = 0x06;
            } else {
                *PacketBufferStruct.ptr.d++ =
                    levelTbp[i] | ((long long)(512 >> i) / 64 << 14) | ((long long)(9 - i) << 26) |
                    ((long long)(9 - i) << 30) | ((long long)0x8000 << 19);
                *PacketBufferStruct.ptr.d++ = 0x06;
            }
            spriteUV(levelRect[i + 1], levelUV[i], col, 0x116);
        }

        setFrame(0x40, ScreenWidth, ScreenHeight, 0, 0);
        setGsReg(0x42, 0x44);
        setGsReg(0x47, 0x3400D);

        for (i = 3; i > 0; i--) {
            unsigned char col2[4] = {D_0028F720[0xC0], D_0028F720[0xC4], D_0028F720[0xC8],
                                     D_0028F720[0xB0 + i * 4]};

            /* Local debug switch, off. What the bytes pin: the ROM's seven
               spill slots (ScreenHeight 0x80, ScreenWidth 0x84, the two window
               offsets 0x88 and 0x90, the rect column addresses 0x98 to 0xA0)
               are gcse's PRE reaching registers in hash-bucket order, and that
               order needs an expression table of 391 buckets, so shadow_Draw
               reached gcse with 780 to 783 insns (781 with this arm, 774
               without it; the 405-bucket window, 808 to 811, is the other
               one). Also pinned: the arm is one test around straight-line
               stores inside the upward loop, since a test that cse's
               skip-blocks cannot pass (an && chain) or an edge out of the body
               (a continue) changes PRE's insertions there. cse cannot carry
               dbg's 0 across the loop label, gcse's constant propagation folds
               the test and the next jump pass deletes the arm; the listing
               leaves rows 449 to 453 code-free between the colour and the
               TEX0 word. What the bytes cannot pin: the arm's text. */
            if (dbg) {
                col2[0] = col2[1] = col2[2] = col2[3] = 0x80;
            }
            *PacketBufferStruct.ptr.d++ = levelTbp[i] | ((long long)(512 >> i) / 64 << 14) |
                                          ((long long)(9 - i) << 26) | ((long long)(9 - i) << 30) |
                                          ((long long)0x8000 << 19);
            *PacketBufferStruct.ptr.d++ = 0x06;
            setGsReg(0x14, 0x60);
            spriteUV(off, rect[i], col2, 0x156);
        }

        setGsReg(0x4E, 0x300000C0);
        setGsReg(0x47, 0x50000);
        setFrame(0x40, ScreenWidth, ScreenHeight, D_0063A074, D_0063A078);

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
        q = PacketBufferStruct.ptr.c;
        PacketBufferStruct.tail.c = q;
        ((GifPkWord *)q)->d = 0x60000000;
        PacketBufferStruct.ptr.c = (q + 8);
        ((GifPkWord *)(q + 8))->w[0] = 0;
        PacketBufferStruct.ptr.c = (q + 0xC);
        ((GifPkWord *)(q + 8))->w[1] = 0;
        PacketBufferStruct.ptr.c = (q + 0x10);
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    tex_UnlockHeadTBP(3);
}

void shadow_Render(void)
{
    /* CRUTCH: zero-code frame reservation. The body is one printf stub and ROM
       still reserves 16 bytes of vars, so the vector the stub printed was a
       local here. Deleting it changes the object. See docs/crutch_ledger.md. */
    float buf[4];
    debug_StdPrintfDummy("shadow_Render called\n");
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

/* The volume renderers below are line-for-line twins in the listing and share
 * one set of static helpers, written here because the listing puts their rows
 * (844 to 1259) above __GetCameraPos and below shadow_EntryNormalShadow.
 * None of them has a symbol of its own: every row run appears only inside
 * shadow_RenderVolume and shadow_RenderVolumeMulti. */

/* the screen-space origin every projected point is measured from */
extern VECTOR D_00290B40;
/* the face normal z of each strip position, read back by the position that
 * shares the face with the one that computed it */
extern float D_0067D070[];

/* rows 844-845: the projection matrix and the shadow direction into the VU0
 * register file, where the edge projector below leaves them for the whole
 * mesh walk */
static inline void loadVolumeMatrix(void *dir)
{
    char *m = matrixptr + 0xC0;

    __asm__ __volatile__("lqc2 $vf4, 0x0(%0)\n\t"
                         "lqc2 $vf5, 0x10(%0)\n\t"
                         "lqc2 $vf6, 0x20(%0)\n\t"
                         "lqc2 $vf7, 0x30(%0)\n\t"
                         "lqc2 $vf1, 0x0(%1)"
                         :
                         : "r"(m), "r"(dir));
}

/* row 867: the six strip vertices out of the VU register file as integer
 * screen coordinates */
static inline void storeVolumeVerts(void *dst)
{
    __asm__ __volatile__("vftoi4.xyzw $vf26, $vf20\n\t"
                         "vftoi4.xyzw $vf27, $vf21\n\t"
                         "vftoi4.xyzw $vf28, $vf22\n\t"
                         "vftoi4.xyzw $vf29, $vf23\n\t"
                         "vftoi4.xyzw $vf30, $vf24\n\t"
                         "vftoi4.xyzw $vf31, $vf25\n\t"
                         "sqc2 $vf26, 0x0(%0)\n\t"
                         "sqc2 $vf27, 0x10(%0)\n\t"
                         "sqc2 $vf28, 0x20(%0)\n\t"
                         "sqc2 $vf29, 0x30(%0)\n\t"
                         "sqc2 $vf30, 0x40(%0)\n\t"
                         "sqc2 $vf31, 0x50(%0)"
                         :
                         : "r"(dst));
}

/* rows 896-1080: project one silhouette edge and clip the projected segment
 * to the screen rectangle. Returns the facing dot times the winding sign, or
 * -1.0f when the edge is wholly off screen, which is also how the caller
 * learns that both ends were marked away.
 * The projection is one hand scheduled block written straight into this body
 * (row 901, five rows below the definition's 896, where the loop's call
 * copies its two vertex addresses). It rolls the six vertex registers of the
 * strip down by one, projects the edge's two ends, divides both by w, takes
 * the facing dot of the new triangle and leaves the two screen points both in
 * the VU registers the emitter reads and in oa/ob for the clipper. Because
 * &oa is this body's own frame address, the block's operand is the frame
 * register itself, which is why the ROM keeps the opening helper's frame copy
 * (`daddu $11,$16,$0`) as the second opening edge's store base. The GPR the
 * dot product passes through is a named $7 (and the slides' is $8), declared
 * clobbered, as Matrix.c and BgAnimation.c write theirs: the ROM keeps $7 and
 * $8 in every copy and allocates round them. The frame vectors precede the
 * origin table in the operand list, which is the order the loop hoists them. */
static inline float clipVolumeEdge(VECTOR *pa, VECTOR *pb, float sgn)
{
    VECTOR oa;
    VECTOR ob;
    float rate[2];
    float dot;
    float fw, fh, t0, t1, t;

    __asm__ __volatile__("vmove.xyzw $vf10, $vf11\n\t"
                         "vmove.xyzw $vf13, $vf14\n\t"
                         "vmove.xyzw $vf20, $vf21\n\t"
                         "vmove.xyzw $vf23, $vf24\n\t"
                         "vmove.xyzw $vf11, $vf12\n\t"
                         "vmove.xyzw $vf14, $vf15\n\t"
                         "vmove.xyzw $vf21, $vf22\n\t"
                         "vmove.xyzw $vf24, $vf25\n\t"
                         "lqc2 $vf12, 0x0(%1)\n\t"
                         "lqc2 $vf15, 0x0(%2)\n\t"
                         "vnop\n\t"
                         "vsub.xyz $vf8, $vf10, $vf11\n\t"
                         "vsub.xyz $vf9, $vf12, $vf11\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf12x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf12y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf12z\n\t"
                         "vmaddw.xyzw $vf22, $vf7, $vf0w\n\t"
                         "vdiv Q, $vf0w, $vf22w\n\t"
                         "vwaitq\n\t"
                         "vmulq.xyzw $vf22, $vf22, Q\n\t"
                         "vopmula.xyz ACC, $vf8, $vf9\n\t"
                         "vopmsub.xyz $vf2, $vf9, $vf8\n\t"
                         "vaddw.x $vf3, $vf0, $vf0w\n\t"
                         "vmulax.xyzw ACC, $vf4, $vf15x\n\t"
                         "vmadday.xyzw ACC, $vf5, $vf15y\n\t"
                         "vmaddaz.xyzw ACC, $vf6, $vf15z\n\t"
                         "vmaddw.xyzw $vf25, $vf7, $vf0w\n\t"
                         "vdiv Q, $vf0w, $vf25w\n\t"
                         "vwaitq\n\t"
                         "vmulq.xyzw $vf25, $vf25, Q\n\t"
                         "vmul.xyz $vf2, $vf1, $vf2\n\t"
                         "vmove.w $vf12, $vf0\n\t"
                         "vmove.w $vf15, $vf0\n\t"
                         "vnop\n\t"
                         "vaddax.x ACC, $vf0, $vf2x\n\t"
                         "vmadday.x ACC, $vf3, $vf2y\n\t"
                         "vmaddz.x $vf2, $vf3, $vf2z\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "qmfc2.ni $7, $vf2\n\t"
                         "mtc1 $7, %0\n\t"
                         "lqc2 $vf8, 0x0(%5)\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "vsub.xyzw $vf18, $vf22, $vf8\n\t"
                         "vsub.xyzw $vf19, $vf25, $vf8\n\t"
                         "vnop\n\t"
                         "vnop\n\t"
                         "sqc2 $vf18, 0x0(%3)\n\t"
                         "sqc2 $vf19, 0x0(%4)"
                         : "=f"(dot)
                         : "r"(pa), "r"(pb), "r"(&oa), "r"(&ob), "r"(&D_00290B40)
                         : "$7");

    rate[0] = rate[1] = 1.0f;
    /* rows 977 and 981: a wholly visible edge returns at once */
    if (-ScreenWidth < oa.x && oa.x < ScreenWidth && -ScreenWidth < ob.x && ob.x < ScreenWidth &&
        -ScreenHeight < oa.y && oa.y < ScreenHeight && -ScreenHeight < ob.y &&
        ob.y < ScreenHeight) {
        return dot * sgn;
    }
    if ((oa.x <= -ScreenWidth && ob.x <= -ScreenWidth) ||
        (ScreenWidth <= oa.x && ScreenWidth <= ob.x) ||
        (oa.y <= -ScreenHeight && ob.y <= -ScreenHeight) ||
        (ScreenHeight <= oa.y && ScreenHeight <= ob.y)) {
        pb->w = -1.0f;
        pa->w = -1.0f;
        return -1.0f;
    }
    fw = ScreenWidth;
    fh = ScreenHeight;
    t0 = t1 = 1.0f;
    if (fw < oa.x && ob.x <= fw) {
        t = (ob.x - fw) / (ob.x - oa.x);
        if (t < t0 && t < 1.0f && 0.0f < t) {
            t0 = t;
        }
    } else if (fw < ob.x && oa.x <= fw) {
        t = (oa.x - fw) / (oa.x - ob.x);
        if (t < t1 && t < 1.0f && 0.0f < t) {
            t1 = t;
        }
    }
    if (oa.x < -fw && -fw <= ob.x) {
        t = (ob.x + fw) / (ob.x - oa.x);
        if (t < t0 && t < 1.0f && 0.0f < t) {
            t0 = t;
        }
    } else if (ob.x < -fw && -fw <= oa.x) {
        t = (oa.x + fw) / (oa.x - ob.x);
        if (t < t1 && t < 1.0f && 0.0f < t) {
            t1 = t;
        }
    }
    if (fh < oa.y && ob.y <= fh) {
        t = (ob.y - fh) / (ob.y - oa.y);
        if (t < t0 && t < 1.0f && 0.0f < t) {
            t0 = t;
        }
    } else if (fh < ob.y && oa.y <= fh) {
        t = (oa.y - fh) / (oa.y - ob.y);
        if (t < t1 && t < 1.0f && 0.0f < t) {
            t1 = t;
        }
    }
    if (oa.y < -fh && -fh <= ob.y) {
        t = (ob.y + fh) / (ob.y - oa.y);
        if (t < t0 && t < 1.0f && 0.0f < t) {
            t0 = t;
        }
    } else if (ob.y < -fh && -fh <= oa.y) {
        t = (oa.y + fh) / (oa.y - ob.y);
        if (t < t1 && t < 1.0f && 0.0f < t) {
            t1 = t;
        }
    }
    rate[0] = t0;
    rate[1] = t1;
    t0 = 1.0f - t0;
    t1 = 1.0f - t1;
    if (1.0f <= t0 + t1 || t0 + t1 <= 0.0f) {
        pb->w = -1.0f;
        pa->w = -1.0f;
        return -1.0f;
    }
    /* rows 1040 and 1060: slide each end of the projected edge to the clip
     * parameter found for it, both blocks inside this body */
    if (0.0f < rate[0] && rate[0] < 1.0f) {
        __asm__ __volatile__("mfc1 $8, %0\n\t"
                             "qmtc2.ni $8, $vf8\n\t"
                             "vsubx.w $vf8, $vf0, $vf8x\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vmulaw.xyz ACC, $vf19, $vf8w\n\t"
                             "vmaddx.xyz $vf22, $vf18, $vf8x\n\t"
                             "lqc2 $vf8, 0x0(%1)\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vadd.xyzw $vf22, $vf22, $vf8"
                             :
                             : "f"(rate[0]), "r"(&D_00290B40)
                             : "$8");
    }
    if (0.0f < rate[1] && rate[1] < 1.0f) {
        __asm__ __volatile__("mfc1 $8, %0\n\t"
                             "qmtc2.ni $8, $vf8\n\t"
                             "vsubx.w $vf8, $vf0, $vf8x\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vmulaw.xyz ACC, $vf18, $vf8w\n\t"
                             "vmaddx.xyz $vf25, $vf19, $vf8x\n\t"
                             "lqc2 $vf8, 0x0(%1)\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vnop\n\t"
                             "vadd.xyzw $vf25, $vf25, $vf8"
                             :
                             : "f"(rate[1]), "r"(&D_00290B40)
                             : "$8");
    }
    return dot * sgn;
}

/* rows 1092-1098: the first two edges of a strip, which open it. Returns the
 * number of strip positions still to skip because an opening vertex was
 * marked away. */
static inline int clipVolumeHead(VECTOR *ta, VECTOR *ba, VECTOR *tb, VECTOR *bb, float sgn)
{
    int state = 0;

    if (clipVolumeEdge(ta, ba, sgn) == -1.0f && ta->w == -1.0f) {
        state = 1;
    }
    if (clipVolumeEdge(tb, bb, -sgn) == -1.0f && tb->w == -1.0f) {
        state = 2;
    }
    return state;
}

#define VOLUME_EDGE(a, b, c)                                                                       \
    VU0_REG("vsub.xy $vf8, $vf" #a ", $vf" #b "\n\t"                                               \
            "vsub.xy $vf9, $vf" #c ", $vf" #b)

/* the facing z of the strip position i. The three positions that share a face
 * with the position two before them read the facing that one measured back
 * out of D_0067D070 instead of taking the cross product again. The cross
 * product of the two edges left in vf8 and vf9 is written straight into the
 * table (row 1124 carries both the block and the store; row 1134 only the
 * return). */
static inline float volumeStripFaceZ(int i)
{
    switch (i) {
    case 0:
    case 1:
        return 1.0f;
    case 2:
        VOLUME_EDGE(20, 21, 23);
        break;
    case 3:
        return -D_0067D070[2];
    case 4:
        VOLUME_EDGE(23, 24, 25);
        break;
    case 5:
        VOLUME_EDGE(24, 25, 21);
        break;
    case 6:
        return -D_0067D070[5];
    case 7:
        VOLUME_EDGE(21, 22, 20);
        break;
    case 8:
        VOLUME_EDGE(22, 20, 25);
        break;
    case 9:
        return -D_0067D070[8];
    }
    __asm__ __volatile__("vopmula.xyz ACC, $vf8, $vf9\n\t"
                         "vopmsub.xyz $vf2, $vf9, $vf8\n\t"
                         "vaddz.x $vf2, $vf0, $vf2z\n\t"
                         "qmfc2.ni $7, $vf2\n\t"
                         "mtc1 $7, %0"
                         : "=f"(D_0067D070[i])
                         :
                         : "$7");
    return D_0067D070[i];
}

/* rows 1197-1202: the strip is dropped whole if any of its six vertices left
 * the guard band or went behind the eye */
static inline int volumeVertsOutOfRange(int *vi)
{
    int n;
    int *v;

    /* row 1198 carries both the count and the cursor, so the cursor is set
     * in the for and the parameter itself is never stepped */
    for (n = 0, v = vi; n < 6; n++, v += 4) {
        if (v[0] < 0x11 || 0xFFEF < v[0] || v[1] < 0x11 || 0xFFEF < v[1] || v[2] < 0) {
            return 1;
        }
    }
    return 0;
}

/* rows 1210-1259: one shadow volume strip. Ten positions of a triangle strip
 * over the six projected vertices, each position carrying the front or the
 * back stencil colour its facing picks. */
static inline unsigned long long *emitVolumeStrip(unsigned long long *p, float sign)
{
    int order[20] = {0, 1, 3, 4, 5, 1, 2, 0, 5, 3, 3, 4, 0, 1, 2, 4, 5, 3, 2, 0};
    int vi[6][4];
    int i;
    int k;
    int *v;
    /* row 1221, six rows below the table's 1215: the running sign is a local
     * copy, so the caller's winding sign is never written */
    float sgn = sign;

    storeVolumeVerts(vi);
    if (volumeVertsOutOfRange(&vi[0][0])) {
        return p;
    }
    p[0] = 0x1000000000008001LL;
    p[1] = 0xE;
    p[2] = 0x144;
    p[3] = 0;
    p[4] = 0x240000000000800ALL;
    p[5] = 0x51;
    p += 6;
    /* rows 1238-1251: the for line carries the index step, the sign flip and
     * the vertex word's pointer step; the colour word steps its own pointer
     * in each arm (row 1245 keeps the merged step) */
    for (i = 0; i < 10; i++, sgn = -sgn, p++) {
        k = order[i];
        if (volumeStripFaceZ(i) * sgn < 0.0f) {
            *p++ = 0x3F80000080040404LL;
        } else {
            *p++ = 0x3F80000080FCFCFCLL;
        }
        v = vi[k];
        *p = (long long)v[0] | ((long long)v[1] << 16) | ((long long)v[2] << 32);
    }
    return p;
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

/* kept local: this TU's uses of these do not fit the prototypes in the headers */
extern int dl_GetPri(void);
extern void GetRootPositionByDObj(void *v, char *o);
extern float _GetLength(void *a, void *b);

/* One sixteen-byte record of a part's silhouette strip list. A strip opens
 * with a record whose count is its vertex count (0 ends the list); each
 * vertex record that follows carries its facing flag in the same short and
 * its vertex index at +4. Only two-byte aligned, which is why
 * shadow_MakeObjectData copies it with ldl/ldr. */
typedef struct ShadowRun {
    short count;
    short _2;
    short vtx;
    char _6[0xA];
} ShadowRun;

void shadow_RenderVolume(char *o)
{
    VECTOR pos;
    VECTOR cam;
    char *x = *(char **)(o + 0x858);
    float len = *(float *)(*(char **)(o + 0x854) + 0x3C);
    unsigned long long *p;
    unsigned long long *start;
    char *c;
    char *q;
    char *part;
    ShadowRun *e;
    VECTOR *top;
    VECTOR *bot;
    int i;
    unsigned int j;
    int k;
    int n;
    int state;
    float sgn;
    float r;

    if (*(long long *)(x + 0x30) & 0x04000000) {
        return;
    }
    if (len != *(float *)(x + 0x3C) && 0.0f < *(float *)(x + 0x3C)) {
        len = *(float *)(x + 0x3C);
    }
    __GetCameraPos(&cam);
    GetRootPositionByDObj(&pos, o);
    _GetLength(&pos, &cam);
    if (*(unsigned short *)(o + 0x84C) == 1) {
        shadow_EntryClusterShadow(o, len);
    } else {
        shadow_EntryNormalShadow(o, 0, len);
    }
    dl_SetDLPriority(3);
    shadow_getShadowVectorAverage(&pos, o);
    loadVolumeMatrix(&pos);
    c = PacketBufferStruct.ptr.c;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.dma.c = c;
    PacketBufferStruct.end.c = 0;
    PacketBufferStruct.tail.c = c;
    PacketBufferStruct.ptr.c = (c + 8);
    ((GifPkWord *)(c + 8))->w[0] = 0x11000000;
    PacketBufferStruct.gif.c = c + 0xC;
    PacketBufferStruct.ptr.c = (c + 0x10);
    p = PacketBufferStruct.ptr.d;
    start = p;
    for (i = 0; i < *(char *)(x + 0x2E); i++) {
        part = *(char **)(x + 0x40) + i * 0x180;
        top = (VECTOR *)*(char **)(part + 0x174);
        bot = (VECTOR *)*(char **)(part + 0x178);
        for (j = 0; j < *(unsigned int *)(part + 0x104); j++) {
            e = (*(ShadowRun ***)(part + 0x100))[j];
            while ((n = (e++)->count) != 0) {
                sgn = e->count != 0 ? 1.0f : -1.0f;
                state = clipVolumeHead(&top[e[0].vtx], &bot[e[0].vtx], &top[e[1].vtx],
                                       &bot[e[1].vtx], sgn);
                e += 2;
                for (k = 2; k < n; k++) {
                    if (top[e->vtx].w == -1.0f) {
                        state = 3;
                    } else if (state) {
                        state--;
                    }
                    r = clipVolumeEdge(&top[e->vtx], &bot[e->vtx], sgn);
                    if (0.0f <= r) {
                        if (state == 0) {
                            p = emitVolumeStrip(p, sgn);
                        }
                    } else if (top[e->vtx].w == -1.0f) {
                        state = 3;
                    }
                    sgn = -sgn;
                    e++;
                }
            }
        }
    }
    PacketBufferStruct.ptr.d = p;
    ((GifPkWord *)PacketBufferStruct.tail.c)->d =
        (unsigned int)((((unsigned int)((char *)p - PacketBufferStruct.tail.c) >> 4) - 1) |
                       0x10000000);
    ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
        ((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) | 0x50000000;
    q = PacketBufferStruct.ptr.c;
    PacketBufferStruct.tail.c = q;
    ((GifPkWord *)q)->d = 0x60000000;
    PacketBufferStruct.ptr.c = (q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = (q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    PacketBufferStruct.ptr.c = (q + 0x10);
    if (p - start > 0) {
        dl_SetDLPriority(dl_GetPri());
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    dl_SetDLPriority(0);
}

void shadow_RenderVolumeMulti(char *o, int idx)
{
    VECTOR pos;
    VECTOR cam;
    char *x = *(char **)(o + 0x858);
    float len = *(float *)(*(char **)(o + 0x854) + 0x3C);
    unsigned long long *p;
    unsigned long long *start;
    char *c;
    char *q;
    char *part;
    ShadowRun *e;
    VECTOR *top;
    VECTOR *bot;
    int i;
    unsigned int j;
    int k;
    int n;
    int state;
    float sgn;
    float r;

    if (*(long long *)(x + 0x30) & 0x04000000) {
        return;
    }
    if (len != *(float *)(x + 0x3C) && 0.0f < *(float *)(x + 0x3C)) {
        len = *(float *)(x + 0x3C);
    }
    __GetCameraPos(&cam);
    GetRootPositionByDObj(&pos, o);
    _GetLength(&pos, &cam);
    shadow_EntryNormalShadow(o, idx, len);
    dl_SetDLPriority(3);
    shadow_getShadowVectorAverage(&pos, o);
    loadVolumeMatrix(&pos);
    c = PacketBufferStruct.ptr.c;
    PacketBufferStruct.gif.c = 0;
    PacketBufferStruct.dma.c = c;
    PacketBufferStruct.end.c = 0;
    PacketBufferStruct.tail.c = c;
    PacketBufferStruct.ptr.c = (c + 8);
    ((GifPkWord *)(c + 8))->w[0] = 0x11000000;
    PacketBufferStruct.gif.c = c + 0xC;
    PacketBufferStruct.ptr.c = (c + 0x10);
    p = PacketBufferStruct.ptr.d;
    start = p;
    for (i = 0; i < *(char *)(x + 0x2E); i++) {
        part = *(char **)(x + 0x40) + i * 0x180;
        top = (VECTOR *)*(char **)(part + 0x174);
        bot = (VECTOR *)*(char **)(part + 0x178);
        for (j = 0; j < *(unsigned int *)(part + 0x104); j++) {
            e = (*(ShadowRun ***)(part + 0x100))[j];
            while ((n = (e++)->count) != 0) {
                sgn = e->count != 0 ? 1.0f : -1.0f;
                state = clipVolumeHead(&top[e[0].vtx], &bot[e[0].vtx], &top[e[1].vtx],
                                       &bot[e[1].vtx], sgn);
                e += 2;
                for (k = 2; k < n; k++) {
                    if (top[e->vtx].w == -1.0f) {
                        state = 3;
                    } else if (state) {
                        state--;
                    }
                    r = clipVolumeEdge(&top[e->vtx], &bot[e->vtx], sgn);
                    if (0.0f <= r) {
                        if (state == 0) {
                            p = emitVolumeStrip(p, sgn);
                        }
                    } else if (top[e->vtx].w == -1.0f) {
                        state = 3;
                    }
                    sgn = -sgn;
                    e++;
                }
            }
        }
    }
    PacketBufferStruct.ptr.d = p;
    ((GifPkWord *)PacketBufferStruct.tail.c)->d =
        (unsigned int)((((unsigned int)((char *)p - PacketBufferStruct.tail.c) >> 4) - 1) |
                       0x10000000);
    ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =
        ((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) | 0x50000000;
    q = PacketBufferStruct.ptr.c;
    PacketBufferStruct.tail.c = q;
    ((GifPkWord *)q)->d = 0x60000000;
    PacketBufferStruct.ptr.c = (q + 8);
    ((GifPkWord *)(q + 8))->w[0] = 0;
    PacketBufferStruct.ptr.c = (q + 0xC);
    ((GifPkWord *)(q + 8))->w[1] = 0;
    PacketBufferStruct.ptr.c = (q + 0x10);
    if (p - start > 0) {
        dl_SetDLPriority(dl_GetPri());
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);
        dl_CloseDma();
    }
    dl_SetDLPriority(0);
}

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
