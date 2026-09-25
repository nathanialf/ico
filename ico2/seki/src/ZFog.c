#include "common.h"
#include "debug.h"
#include <eekernel.h>
#include "typedef.h"

/* The fog CLUT upload packet: a VIF code quad (nop, nop, FLUSHA, DIRECT 65),
 * a GIFtag (EOP, NLOOP=64, FLG=IMAGE), the 256-entry 32-bit CLUT itself and a
 * trailing FLUSHA quad: ZFog.o's whole .bss (VMA 0x6AF590..0x6AF9C0). */
typedef struct FogClutPacket {
    unsigned int vif[4];    /* 0x000 */
    long long gif[2];       /* 0x010 */
    unsigned int clut[256]; /* 0x020 */
    unsigned int vifEnd[4]; /* 0x420 */
} FogClutPacket;

static FogClutPacket
    fogClutPacket; /* static: fog_DrawFog and fog_MakeFogClut reach it as a local symbol, as the ROM's relocations do */

/* kept local: the stage settings record's fog words, which the shared
   StageSetting (typedef.h) still carries as padding; read as fields, as
   GsBase.c and Light.c read the record (the ROM's single base register). */
typedef struct FogStage {
    char pad000[0x80];
    int fogOn; /* 0x080 */
    char pad084[0xC];
    int fogColR;    /* 0x090 */
    int fogColG;    /* 0x094 */
    int fogColB;    /* 0x098 */
    int fogColA;    /* 0x09C */
    int fogOffsetA; /* 0x0A0 */
    int fogNear;    /* 0x0A4 */
    int fogFar;     /* 0x0A8 */
    char pad0AC[0x74];
    int fogStrength; /* 0x120 */
} FogStage;

extern FogStage D_0028F720;

void fog_MakeFogClut(void)
{
    unsigned int buf[8][2][2][8];
    unsigned int *clut = fogClutPacket.clut;
    int i;
    int j;
    int k;
    int l;
    int near;
    int far;
    int r;
    int g;
    int b;
    int a;
    float v;

    near = D_0028F720.fogNear;
    far = D_0028F720.fogFar;

    r = D_0028F720.fogColR;
    g = D_0028F720.fogColG;
    b = D_0028F720.fogColB;
    a = D_0028F720.fogColA;

    fogClutPacket.vif[0] = 0;
    fogClutPacket.vif[1] = 0;
    fogClutPacket.vif[2] = 0x13000000;
    fogClutPacket.vif[3] = 0x50000041;
    fogClutPacket.gif[0] = 0x0800000000008040;
    fogClutPacket.gif[1] = 0;
    fogClutPacket.vifEnd[0] = 0x13000000;
    fogClutPacket.vifEnd[1] = 0;
    fogClutPacket.vifEnd[2] = 0;
    fogClutPacket.vifEnd[3] = 0;

    for (i = 0; i < 256; i++) {
        if (i <= near) {
            v = 0.0f;
        } else if (i > far) {
            v = a / 2;
        } else {
            v = a * (i - near) / (far - near) / 2;
        }
        clut[255 - i] = ((int)v << 24) | (b << 16) | (g << 8) | r;
    }

    /* GS 32-bit CLUT storage swizzle: the two middle 8-entry blocks of every
     * 32-entry run trade places. */
    for (i = 0; i < 8; i++) {
        for (j = 0; j < 2; j++) {
            for (k = 0; k < 2; k++) {
                for (l = 0; l < 8; l++) {
                    buf[i][k][j][l] = *clut++;
                }
            }
        }
    }

    for (i = 0; i < 256; i++) {
        fogClutPacket.clut[i] = ((unsigned int *)buf)[i];
    }

    FlushCache(0);
}

/* The display-list packet builder state, the record src/GifPacket.c carries
 * as GifDpk, held here as src/Shadow.c holds it: every packet address is one
 * pointer union, so each field access is alias set 0 (c-common.c
 * c_get_alias_set: a reference through a union). */
typedef union {
    unsigned long long *d;
    char *c;
} FogPkPtr;

typedef struct {
    int cur;
    int *buf[2];
    FogPkPtr dma;
    FogPkPtr ptr;
    FogPkPtr tail;
    FogPkPtr gif;
    FogPkPtr end;
} FogDpk;

extern FogDpk PacketBufferStruct;
extern int ScreenWidth;
extern int ScreenHeight;
extern int D_0063A074;
extern int D_0063A078;
extern int D_0063B1F0;
extern int D_0063B13C;
extern char D_0063A340[];
extern int tex_AllocVramAuto(int a0, int a1);
extern void tex_ResetVramPri(int pri);
extern void dl_OpenDma(int chan, void *dma, int flag);
extern void dl_CloseDma(void);

/* RECONSTRUCTION.  The packet writers the listing attributes to their
   invoking lines in fog_DrawFog (no GifPacket.c rows), so macros; their
   bodies are gif_StartPacket's, gif_SetGsReg's and gif_EndPacket's own
   (GifPacket.c), the end one with its DMA kick. */
#define FOG_START_PACKET()                                                                         \
    {                                                                                              \
        char *c = PacketBufferStruct.ptr.c;                                                        \
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
#define FOG_SET_GSREG(reg, val)                                                                    \
    {                                                                                              \
        *PacketBufferStruct.ptr.d++ = (val);                                                       \
        *PacketBufferStruct.ptr.d++ = (reg);                                                       \
    }
#define FOG_END_PACKET()                                                                           \
    {                                                                                              \
        char *p;                                                                                   \
        ((GifPkWord *)PacketBufferStruct.end.c)->d =                                               \
            (unsigned int)(((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.end.c) >> \
                            4) -                                                                   \
                           1) |                                                                    \
            0x1000000000008000LL;                                                                  \
        ((GifPkWord *)PacketBufferStruct.gif.c)->w[0] =                                            \
            ((unsigned int)(PacketBufferStruct.ptr.c - PacketBufferStruct.gif.c) >> 4) |           \
            0x50000000;                                                                            \
        ((GifPkWord *)PacketBufferStruct.tail.c)->d =                                              \
            (unsigned int)((((unsigned int)(PacketBufferStruct.ptr.c -                             \
                                            PacketBufferStruct.tail.c) >>                          \
                             4) -                                                                  \
                            1) |                                                                   \
                           0x10000000);                                                            \
        p = PacketBufferStruct.ptr.c;                                                              \
        PacketBufferStruct.tail.c = p;                                                             \
        ((GifPkWord *)p)->d = 0x60000000;                                                          \
        PacketBufferStruct.ptr.c = p + 8;                                                          \
        ((GifPkWord *)(p + 8))->w[0] = 0;                                                          \
        PacketBufferStruct.ptr.c = p + 0xC;                                                        \
        ((GifPkWord *)(p + 8))->w[1] = 0;                                                          \
        PacketBufferStruct.ptr.c = p + 0x10;                                                       \
        dl_OpenDma(5, PacketBufferStruct.dma.c, 0);                                                \
        dl_CloseDma();                                                                             \
    }
/* FRAME_1, SCISSOR_1 and XYOFFSET_1 for a w by h buffer at base fbp, the
   window centred on the GS's 2048.0 origin and moved by ox, oy sixteenths:
   src/Shadow.c's setFrame, on one line of the use as the listing has it. */
#define FOG_SET_FRAME(fbp, w, h, ox, oy)                                                           \
    {                                                                                              \
        FOG_SET_GSREG(0x4C, (fbp) | ((long long)(((w) >> 6) & 0x3F) << 16));                       \
        FOG_SET_GSREG(0x40, ((long long)((w) - 1) << 16) | ((long long)((h) - 1) << 48));          \
        FOG_SET_GSREG(0x18, (((long long)(2048 - (w) / 2) << 4) + (ox)) |                          \
                                ((((long long)(2048 - (h) / 2) << 4) + (oy)) << 32));              \
    }
/* RGBAQ packed from a four-byte colour, and XYZ2 with and without the
   2048.0-pixel window origin folded in, as src/Shadow.c packs them */
#define GIF_RGBA(c)                                                                                \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
#define GIF_XY0(x, y, z) ((long long)(x) | ((long long)(y) << 16) | ((z) << 32))
#define GIF_XY(x, y, z)                                                                            \
    ((long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16) | ((z) << 32))
/* The textured sprite, src/Shadow.c's spriteUV: PRIM, RGBAQ, then a UV and
   an XYZ2 pair for each corner, the far corner as x + fx with fx = w + 0x8000.
   A MACRO: the listing puts all of it on the line of the use. */
#define FOG_SPRITE_UV(r, uv, col, prim, z)                                                         \
    {                                                                                              \
        FOG_SET_GSREG(0x00, prim);                                                                 \
        FOG_SET_GSREG(0x01, GIF_RGBA(col));                                                        \
        FOG_SET_GSREG(0x03, (long long)(uv)[0] | ((long long)(uv)[1] << 16));                      \
        FOG_SET_GSREG(0x05, GIF_XY((r)[0], (r)[1], z));                                            \
        FOG_SET_GSREG(0x03,                                                                        \
                      (long long)((uv)[0] + (uv)[2]) | ((long long)((uv)[1] + (uv)[3]) << 16));    \
        {                                                                                          \
            int fx = (r)[2] + 0x8000;                                                              \
            int fy = (r)[3] + 0x8000;                                                              \
                                                                                                   \
            FOG_SET_GSREG(0x05, GIF_XY0((r)[0] + fx, (r)[1] + fy, z));                             \
        }                                                                                          \
    }
/* The untextured sprite, src/Shadow.c's spriteRect: PRIM, RGBAQ and the two
   XYZ2 corners, the far corner as spriteUV holds it. */
#define FOG_SPRITE_RECT(r, col, prim, z)                                                           \
    {                                                                                              \
        FOG_SET_GSREG(0x00, prim);                                                                 \
        FOG_SET_GSREG(0x01, GIF_RGBA(col));                                                        \
        FOG_SET_GSREG(0x05, GIF_XY((r)[0], (r)[1], z));                                            \
        {                                                                                          \
            int fx = (r)[2] + 0x8000;                                                              \
            int fy = (r)[3] + 0x8000;                                                              \
                                                                                                   \
            FOG_SET_GSREG(0x05, GIF_XY0((r)[0] + fx, (r)[1] + fy, z));                             \
        }                                                                                          \
    }

/* RECONSTRUCTION.  The debug switch dbg and its test after the conversion
   loop are code the ROM does not contain: cse cannot carry dbg's 0 across the
   loop label, gcse's constant propagation folds the test and the next jump
   pass deletes the arm, as in src/Shadow.c shadow_Draw.  What the bytes pin:
   the six frame slots are gcse PRE reaching registers in hash bucket order,
   and their offsets and the order of the loads before the loop come out as
   the ROM's only with a 403-bucket table, i.e. 804 to 807 insns at gcse, 16
   more than the function without the arm; the arm sits after the loop (before
   it cse folds the test away) and on the row the listing leaves code-free
   before the FRAME writes, which re-read the packet cursor; it kills none of
   the loads PRE moves (so it writes neither rc0 nor rc1) and computes no
   expression the later code computes.  What they cannot pin: the arm's text.
   The layer made opaque and TEXA set as src/GsBase.c's full-screen sprites
   set it is this programmer's setup for such a sprite, sized to that count. */
/* clang-format off */
void fog_DrawFog(void)
{
    int rc0[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 2 * 16, ScreenWidth * 16, ScreenHeight * 16};
    int vram;
    int i;
    int j;
    int dbg = 0; /* local debug switch, see the test after the loop below */
    int rc1[4] = {8, 8, ScreenWidth * 16, ScreenHeight * 16};
    unsigned char cl[4] = {0x80, 0x80, 0x80, D_0028F720.fogStrength};

    if (D_0063B1F0 == 0) return;
    if (D_0028F720.fogOn == 0) return;

    if (D_0063B13C & 1) debug_Printf(510, ScreenHeight / 2 - 8, 0xCCCCCC00, D_0063A340);

    vram = tex_AllocVramAuto(1, 4);

    tex_ResetVramPri(4);

    FOG_START_PACKET();


    FOG_SET_GSREG(0x50, ((long long)vram << 32) |
                  0x0001000000000000LL);
    FOG_SET_GSREG(0x51, 0);
    FOG_SET_GSREG(0x52, 0x0000001000000010LL);
    FOG_SET_GSREG(0x53, 0);

    FOG_END_PACKET();


    dl_OpenDma(2, (void *)((int)&fogClutPacket & 0x0FFFFFFF), 67);
    dl_CloseDma();

    FOG_START_PACKET();

    FOG_SET_GSREG(63, 1);


    FOG_SET_GSREG(0x50, 0x1800 | ((long long)(ScreenWidth / 64) << 16) | ((long long)0x30 << 24) |
                  ((long long)0x2800 << 32) |
                  ((long long)(ScreenWidth / 64) << 48));
    FOG_SET_GSREG(0x51, 0);
    FOG_SET_GSREG(0x52, ScreenWidth | ((long long)ScreenHeight << 32));
    FOG_SET_GSREG(0x53, 2);

    for (i = 0; i < ScreenHeight / 32; i++) {
        for (j = 0; j < 4; j++) {
            FOG_SET_GSREG(0x50, ((i * (ScreenWidth / 2) + 0x2800) | 0x14020000) |
                          ((long long)(i * (ScreenWidth / 2) + 0x2800) << 32) |
                          0x1402000000000000LL);
            FOG_SET_GSREG(0x51, (long long)(16 + j * 32) | ((long long)(16 + j * 32 + 8) << 32));
            FOG_SET_GSREG(0x52, ((long long)(ScreenWidth / 2 * 4) << 32) | 8);
            FOG_SET_GSREG(0x53, 2);
        }
    }
    if (dbg) { cl[3] = 0x80; FOG_SET_GSREG(0x3B, 0x8000000080LL); }
    FOG_SET_FRAME(64, ScreenWidth, ScreenHeight, 0, 0);
    FOG_SET_GSREG(73, 0); FOG_SET_GSREG(66, ((long long)128 << 32) | 0x44);
    FOG_SET_GSREG(6, 0x2800 | ((long long)(ScreenWidth / 64) << 14) | ((long long)0x1B << 20) | ((long long)9 << 26) | ((long long)9 << 30) | ((long long)1 << 34) |
                  ((long long)vram << 37) | ((long long)1 << 61));
    FOG_SET_GSREG(78, ((long long)0x13000 << 16) | 0xC0);
    FOG_SET_GSREG(71, 0x50000);
    FOG_SET_GSREG(20, 0);
    FOG_SPRITE_UV(rc0, rc1, cl, 342, 0xFFFFFFLL);
    FOG_SET_GSREG(20, 96);


    if (D_0028F720.fogOffsetA > 0) {
        unsigned char cl2[4] = {D_0028F720.fogColR, D_0028F720.fogColG, D_0028F720.fogColB, D_0028F720.fogOffsetA};





        FOG_SET_GSREG(71, 0x30000);
        FOG_SPRITE_RECT(rc0, cl2, 1094, 0xFFFFFFFFLL);
        FOG_SET_GSREG(71, 0x50000);
    }
    FOG_SET_GSREG(78, ((long long)0x3000 << 16) | 0xC0);

    FOG_SET_FRAME(64, ScreenWidth, ScreenHeight, D_0063A074, D_0063A078);
    FOG_END_PACKET();
}

/* clang-format on */

/* the shared pad-state array (GsBase.c's GsbPad): trg at 0x4, rep at 0xC */

/* one row of the fog debug menu: a label, the int it edits and its range */
typedef struct FogToolItem {
    char *name; /* 0x0 */
    int *val;   /* 0x4 */
    int min;    /* 0x8 */
    int max;    /* 0xC */
} FogToolItem;

extern GsbPad D_0028F8F0[];

/* the two labels the 0/1 row prints; the unspecified bound keeps the 8-byte
   pointer array out of small data under -G 8, which is where the ROM has it */
static char *fogOnOffText[] = {"Off", "On"};

/* .rodata, the head of ZFog.o's run, VMA 0x550AE8..0x550C08: the
   fog tool's nine rows and their names.  Each row names the stage
   setting word it edits; the first row is the only 0/1 one, which is what the
   tool tests to decide between the text and the number format. */
extern char D_00550C10[]; /* "Fog Tool" */
extern char D_00550C20[]; /* "Fog %s => %s\n" */
extern char D_00550C30[]; /* "Fog %s => %d\n" */

static const FogToolItem fogToolItems[9] = {
    {" Fog On/Off   ", &D_0028F720.fogOn, 0, 1},
    {" Fog Color R  ", &D_0028F720.fogColR, 0, 255},
    {" Fog Color G  ", &D_0028F720.fogColG, 0, 255},
    {" Fog Color B  ", &D_0028F720.fogColB, 0, 255},
    {" Fog Color A  ", &D_0028F720.fogColA, 0, 255},
    {" Fog Offset A ", &D_0028F720.fogOffsetA, 0, 255},
    {" Fog Near     ", &D_0028F720.fogNear, 0, 255},
    {" Fog Far      ", &D_0028F720.fogFar, 0, 255},
    {" Fog Strength ", &D_0028F720.fogStrength, 0, 255},
};

/* the colour a row is drawn in: white when the cursor is elsewhere, black when
   it is on this row.  The unspecified bound keeps the 8-byte object out of
   small data under -G 8, which is where the ROM has it. */
static const unsigned int fogRowColor[] = {0xFFFFFF00, 0xFF000000};

extern int D_0063A354;    /* highlighted row */
extern char D_0063A358[]; /* "%s : %s" */
extern char D_0063A360[]; /* "%s : %d" */

int fog_FogTool(void)
{
    int i;
    int v;
    int ret;

    ret = 0;
    debug_PrintfDummy(10, 50, 0xFF800000, D_00550C10);

    for (i = 0; i < 9; i++) {
        if (fogToolItems[i].min == 0 && fogToolItems[i].max == 1) {
            debug_PrintfDummy(18, (i + 1) * 8 + 0x32, fogRowColor[(D_0063A354 == i) ? 1 : 0],
                              D_0063A358, fogToolItems[i].name, fogOnOffText[*fogToolItems[i].val]);
        } else {
            debug_PrintfDummy(18, (i + 1) * 8 + 0x32, fogRowColor[(D_0063A354 == i) ? 1 : 0],
                              D_0063A360, fogToolItems[i].name, *fogToolItems[i].val);
        }
    }

    if (D_0028F8F0[0].rep & 0x4000) {
        D_0063A354++;
        if (D_0063A354 >= 9) {
            D_0063A354 = 0;
        }
    }
    if (D_0028F8F0[0].rep & 0x1000) {
        D_0063A354--;
        if (D_0063A354 < 0) {
            D_0063A354 = 8;
        }
    }
    if (D_0028F8F0[0].rep & 0x2000) {
        v = ++*fogToolItems[D_0063A354].val;
        if (fogToolItems[D_0063A354].max < v) {
            *fogToolItems[D_0063A354].val = fogToolItems[D_0063A354].min;
        }
    }
    if (D_0028F8F0[0].rep & 0x8000) {
        v = --*fogToolItems[D_0063A354].val;
        if (v < fogToolItems[D_0063A354].min) {
            *fogToolItems[D_0063A354].val = fogToolItems[D_0063A354].max;
        }
    }
    if (D_0028F8F0[0].trg & 0x20) {
        for (i = 0; i < 9; i++) {
            if (fogToolItems[i].min == 0 && fogToolItems[i].max == 1) {
                debug_StdPrintfDummy(D_00550C20, fogToolItems[i].name,
                                     fogOnOffText[*fogToolItems[i].val]);
            } else {
                debug_StdPrintfDummy(D_00550C30, fogToolItems[i].name, *fogToolItems[i].val);
            }
        }
        ret = 1;
    }
    if (D_0028F8F0[0].trg & 0x40) {
        ret = -1;
    }
    if (ret != 0) {
        D_0063A354 = 0;
    }
    fog_MakeFogClut();
    return ret;
}
