#include "typedef.h"
#include "Basic.h"
#include "Texture.h"
#include "DisplayList.h"
#include "debug.h"
#include <string.h>
#include "GsBase.h"
#include "debug_exception.h"
#include <libgraph.h>
#include <eekernel.h>
#include "tableSin.h"
#include "main.h"
#include "DmaPacket.h"
#include "FileManager.h"
#include <assert.h>
#include <stdio.h>
#include "include_asm.h"

/* One mipmap level of a texture record, 0x24 bytes: the address, the buffer
 * width and the VRAM size, and a 13-entry short table indexed by the display
 * list priority (tex_initTM2's clear loops run j from 12 down to 0).  The CLUT
 * has a record of its own at 0xE4 and the image's mipmap levels an array at
 * 0x108; tex_initTM2 clears seven of them and they end at 0x204, below the
 * TIM2 picture header the record keeps at 0x208. */
typedef struct TexLevel { /* field names derived */
    void *addr;
    short dbw;
    short vramSize;
    short tbp[13];
    short pad22;
} TexLevel; /* derived name */

/* the texture's UV packet at 0xA8 of the texture record, three quadwords the
 * record hands the display list: the UNPACK of one quadword, the quadword
 * (the two scroll offsets tex_textureAnimation writes and tex_SetUVScroll
 * seeds, then z and w, written once as zero) and the MSCAL. */
typedef struct TexUV { /* field names derived */
    int vif[4];
    float uOfs;
    float vOfs;
    long long zw;
    int end[4];
} TexUV; /* derived name */

/* the record's own five-quadword GS packet at 0x58: the DIRECT head, TEX1_1
 * and TEST_1 as A+D writes, and the closing VIF codes */
typedef struct TexPkt { /* field names derived */
    DpkHead head;
    DpkRegAD tex1;
    DpkRegAD test;
    int end[4];
} TexPkt; /* derived name */

/* one level's transfer packet: the DIRECT head, then TRXPOS, TRXREG and
 * TRXDIR, the host-to-local transfer the level's image packet follows */
typedef struct TexLevelPkt { /* field names derived */
    DpkHead head;
    DpkRegAD trxpos;
    DpkRegAD trxreg;
    DpkRegAD trxdir;
} TexLevelPkt; /* derived name */

/* the TIM2 picture header.  The fields this file reads off
 * it are clutColors at 0x0E, clutType at 0x12 (masked with 0x3F where the
 * compound bits have to go), imageType at 0x13 and the width and height at
 * 0x14 and 0x16. */
typedef struct Tim2Picture { /* field names derived */
    unsigned int totalSize;
    unsigned int clutSize;
    unsigned int imageSize;
    unsigned short headerSize;
    unsigned short clutColors;
    unsigned char picFormat;
    unsigned char mipMapTextures;
    unsigned char clutType;
    unsigned char imageType;
    unsigned short imageWidth;
    unsigned short imageHeight;
    unsigned long long GsTex0;
    unsigned long long GsTex1;
    unsigned int GsRegs;
    unsigned int GsTexClut;
} Tim2Picture; /* derived name */

/* the TIM2 mipmap header that follows the picture header when there is more
 * than one level, two MIPTBP registers and then one image size per level.
 * tex_makeTexturePacket copies 0x30 bytes of picture header into the record
 * and a second 0x30 bytes of mipmap header after it, and steps over a variable
 * number of size words through the mipmap_header_size table before it reaches
 * the ICO block. */
typedef struct Tim2Mipmap { /* field names derived */
    unsigned long long GsMiptbp1;
    unsigned long long GsMiptbp2;
    unsigned int sizes[8];
} Tim2Mipmap; /* derived name */

struct TexData { /* field names derived */
    /* the trimmed name tex_GetTextureNo compares against, and behind it the
     * path the texture was loaded from, which tex_initTextureSub keeps so a
     * second read of the same name from a different path can be reported
     * (this build's are 32 and 128 bytes: tex_initTextureSub compares the
     * path at 0x20, and every later field the code reads sits 0x48 past
     * PAL's: the sampling word at 0xC0, the TIM2 picture at 0x250, the ICO
     * block at 0x2B0, the used flag in the dword at 0x318) */
    char name[32];
    char file[128];
    TexPkt pkt; /* 0xA0 */
    TexUV uv;   /* 0xF0 */
    /* the base of the per-level transfer packets tex_setRegisters allocates */
    TexLevelPkt *levelPkt;
    /* the TIM2 file image the record was built from */
    void *tim2;
    unsigned short levelNum; /* the mipmap level count */
    char pad12A[2];
    TexLevel clut;
    TexLevel lv[7];
    char pad24C[4];
    /* the TIM2 picture and mipmap headers tex_makeTexturePacket copies in;
     * tex_Tool rebuilds the three CLUT copies from the picture's clutSize */
    Tim2Picture pic; /* 0x250 */
    Tim2Mipmap mip;  /* 0x280 */
    /* the animation record, opening with the 0x40-byte ICO block copied
     * whole from the TIM2 header */
    TexExt ext;
};

/* one texture slot, 0x330 bytes in this build (the stubs step texTable by
 * 816): eight bytes the record follows, then the 0x328-byte record (PAL's
 * slot is 0x2E8; the 0x48 bytes are the longer name and path). The code
 * passes the record itself around (the address of slot + 8). */
typedef struct TexEntry { /* field names derived */
    char head[8];
    TexData rec;
} TexEntry; /* derived name */

/* the row tex_Tool has selected, and the number of texture slots in use */
static int toolRow; /* derived name */

static int texCount; /* derived name */

typedef struct TexClutEnt { /* field names derived */
    int psm;
    int sizeDiv;
    int sizeMul;
} TexClutEnt; /* derived name */

/* the TIM2 mipmap header size by mipmap level count */
int mipmap_header_size[] = {0, 0, 32, 32, 32, 48, 48, 48};

/* one entry per TIM2 image type: the GS pixel storage mode and the two
   factors the buffer width and size arithmetic reads */
static TexClutEnt psmTable[] = {
    {0, 0, 0}, {2, 4, 4}, {1, 3, 2}, {0, 2, 2}, {20, 1, 1}, {19, 2, 1},
}; /* derived name */

/* one string per TIM2 image type, printed with %8s */
char *textype[] = {"NONE", "PSMCT16", "PSMCT24", "PSMCT32", "PSMT4", "PSMT8"};

/* one VRAM slot per display list priority: the texture and CLUT free-address
 * cursors and the texture id the slot last had programmed */
typedef struct VramPri { /* field names derived */
    short texAddr;
    short clutAddr;
    short lastTex;
} VramPri; /* derived name */

/* the VRAM slot per display list priority, the 200 texture slots and the
 * working copy of the selected texture's ICO block tex_Tool edits (this build
 * has no head-TBP lock table) */
static VramPri vramPri[13]; /* derived name */

static TexEntry texTable[200]; /* derived name */

static Tim2Ext toolExt; /* derived name */

/* The two VRAM bump allocators tex_AllocVramAuto dispatches to.  The limits
   are the texture and CLUT ends of the 16 KB VRAM window the priority table
   hands out. */
static inline int texAllocTexVram(int size) /* derived name */
{
    int pri = dl_GetPri();
    int ret;

    if (16000 <= vramPri[dl_GetPri()].texAddr + size) {
        tex_ResetVramPri(pri);
    }
    ret = vramPri[dl_GetPri()].texAddr;
    vramPri[dl_GetPri()].texAddr = ret + size;
    return ret;
}

static inline int texAllocClutVram(int size) /* derived name */
{
    int pri = dl_GetPri();
    int ret;

    if (16128 <= vramPri[dl_GetPri()].clutAddr + size) {
        tex_ResetVramPri(pri);
    }
    ret = vramPri[dl_GetPri()].clutAddr;
    vramPri[dl_GetPri()].clutAddr = ret + size;
    return ret;
}

int tex_AllocVramAuto(int kind, int size)
{
    int ret = -1;

    switch (kind) {
    case 0:
        ret = texAllocTexVram(size);
        break;
    case 1:
        ret = texAllocClutVram(size);
        break;
    }
    return ret;
}

/* as in GifPacket.h, which this TU does not include */
extern void gif_StartPacketPri(int pri);
/* as in GifPacket.h, which this TU does not include */
extern void gif_SetGsReg(long long reg, long long data);
/* as in GifPacket.h, which this TU does not include */
extern void gif_EndPacket(void);

/* "0" */

/* the TEXFLUSH write that closes the upload (this build keeps the one qword;
   the VIF DIRECT and the GIF A+D tag are not part of it); qword aligned
   because dl_OpenDma chains it into the display list as a DMA source */
static const unsigned int texFlushPacket[4]
    __attribute__((aligned(16))) = {1, 0, 0x3F, 0}; /* derived name */

static int tex_loadImage(unsigned int addr, TexData *tex, int idx, short dbp, short dbw, short dpsm,
                         short dsax, short dsay, short w, short h);

INCLUDE_ASM(tex_loadImage);

/* the exponent of the smallest power of two at least size, -1 past 1024,
 * which tex_setTexReg and tex_TransTextureDefocus inline */
static inline int getTWTH(int size) /* derived name */
{
    int ret = -1;
    int i;
    for (i = 0; i < 11; i++) {
        if ((1 << i) >= size) {
            ret = i;
            break;
        }
    }
    return ret;
}

/* The GS A+D writer, a macro: the packet cursor is bumped before the
 * register value is computed. */
#define setGsReg(reg, val) /* derived name */                                                      \
    {                                                                                              \
        *PacketBufferStruct.ptr.d++ = (val);                                                       \
        *PacketBufferStruct.ptr.d++ = (reg);                                                       \
    }
/* the record carries seven mipmap levels, so a level index is clamped to the
 * last one before it indexes lv[] */
#define TEXLV(n) ((n) < 7 ? (n) : 6) /* derived name */

INCLUDE_ASM(tex_setTexReg);

/* Claim one VRAM buffer per level for the current display list priority. */
static inline void texAllocVram(TexData *t, int levels, int lv) /* derived name */
{
    int i;

    t->clut.tbp[dl_GetPri()] = tex_AllocVramAuto(1, t->clut.vramSize);
    for (i = lv; i < levels - lv; i++) {
        t->lv[i].tbp[dl_GetPri()] = tex_AllocVramAuto(0, t->lv[i].vramSize);
    }
}

/* The level upload, inlined at both call sites; its parameters are ints,
 * narrowed to tex_loadImage's shorts at the call. */
static inline int texLoadLevel(void *addr, TexData *t, int n, int dbp, int dbw, int dpsm, int w,
                               int h) /* derived name */
{
    return tex_loadImage((unsigned int)addr, t, n, dbp, dbw, dpsm, 0, 0, w, h);
}

INCLUDE_ASM(tex_transVramClutTex);

/* the same claim loop as texAllocVram's tail without the CLUT */
static inline void texAllocLevels(TexData *t, int levels, int lv) /* derived name */
{
    int i;

    for (i = lv; i < levels - lv; i++) {
        t->lv[i].tbp[dl_GetPri()] = tex_AllocVramAuto(0, t->lv[i].vramSize);
    }
}

INCLUDE_ASM(tex_transVramDirectTex);

INCLUDE_ASM(tex_transRegister);

/* "FALSE" */

INCLUDE_ASM(tex_transTM2);

/* Turn a width in texels into the GS buffer width in units of 64; inlined
 * twice in tex_initClutTexture and once here.  The first arm's eleven formats
 * are PSMCT32, PSMCT24, PSMCT16, PSMCT16S, PSMT8H, PSMT4HL, PSMT4HH, PSMZ32,
 * PSMZ24, PSMZ16 and PSMZ16S; the second arm's PSMT8 and PSMT4 round up to an
 * even number of blocks. */
static inline int texTBW(TexClutEnt *e, int w) /* derived name */
{
    int psm = e->psm;
    int n;
    int odd;

    switch (psm) {
    case 0:
    case 1:
    case 2:
    case 10:
    case 27:
    case 36:
    case 44:
    case 48:
    case 49:
    case 50:
    case 58:
        return (w + 63) >> 6;
    case 19:
    case 20:
        n = (w + 63) >> 6;
        odd = n & 1;
        return n + odd;
    }
    return 0;
}

INCLUDE_ASM(tex_initClutTexture);

INCLUDE_ASM(tex_setRegisters);

/* Fill in one VRAM size and one buffer width per mipmap level. */
static inline void texInitMipLevels(Tim2Picture *pic, TexData *t) /* derived name */
{
    int i;
    int dbw;

    for (i = 0; i < t->levelNum; i++) {
        t->lv[i].vramSize =
            ((pic->imageWidth >> i) * (pic->imageHeight >> i) / psmTable[pic->imageType].sizeDiv) *
                psmTable[pic->imageType].sizeMul >>
            6;

        dbw = texTBW(&psmTable[pic->imageType], pic->imageWidth >> i);

        t->lv[i].dbw = dbw;
    }
}

/* "FALSE" */

INCLUDE_ASM(tex_initTM2);

static void tex_convertClutCSM2ToCSM1(Tim2Picture *pic)
{
    int buf[8][2][2][8];
    int *clut = (int *)((char *)pic + pic->headerSize + pic->imageSize);
    int *top = clut;
    int i, j, k, l;

    if ((pic->clutType >> 7) != 0) {
        for (i = 0; i < 8; i++) {
            for (j = 0; j < 2; j++) {
                for (k = 0; k < 2; k++) {
                    for (l = 0; l < 8; l++) {
                        buf[i][k][j][l] = *clut++;
                    }
                }
            }
        }
        clut = top;
        for (i = 0; i < 256; i++) {
            *clut++ = ((int *)buf)[i];
        }
    }
}

/* graph016 takes short parameters; declared that way, tex_convertImage's frame
 * grows by 16 bytes and its registers move, so this file declares int ones
 * and libgraph.h leaves the call out. */
extern int sceGsSetDefStoreImage(sceGsStoreImage *img, int sbp, int sbw, int spsm, int ssax,
                                 int ssay, int rrw, int rrh);

/* "FALSE" */

INCLUDE_ASM(tex_convertImage);

INCLUDE_ASM(tex_makeCopyImage);

/* "ICO" */
/* "e" */
/* "0" */

/* Step over the 16-byte TIM2 file header. */
static inline Tim2Picture *tim2Picture(void *file) /* derived name */
{
    return (Tim2Picture *)((char *)file + 16);
}

/* The CLUT counterpart of tex_makeCopyImage's single-level arm: the same
 * packet header written in front of a copy of the palette. */
static inline void tim2MakeClutPacket(Tim2Picture *pic, TexData *t, char *clut) /* derived name */
{
    DpkHead *p;
    int *q;
    int n;

    if (pic->clutSize != 0) {
        t->clut.addr = mallocseki(pic->clutSize + 80);
        malloc_MemCpy((char *)t->clut.addr + 32, clut, pic->clutSize);

        p = t->clut.addr;
        n = pic->clutSize >> 4;
        p->vif[0] = 0;
        p->vif[1] = 0;
        p->vif[2] = 0x13000000;
        p->vif[3] = (n + 1) | 0x50000000;
        p->tag[0] = (n | 0x8000) | ((long long)0x8000 << 44);
        p->tag[1] = 0;
        q = (int *)((char *)p + (pic->clutSize + 32));
        *q++ = 0;
        *q++ = 0;

        *q++ = 0;
        *q++ = 0;
    }
}

INCLUDE_ASM(tex_makeTexturePacket);

/* "%s" */

/* Cut the directory prefix and the extension off the name in place. */
static inline void texTrimName(char *name) /* derived name */
{
    char tmp[256];
    int i;
    int k;

    k = 0;
    for (i = 0; name[i] != 0; i++) {
        if (name[i] == '/') {
            k = i + 1;
        }
    }
    sprintf(tmp, "%s", &name[k]);
    sprintf(name, "%s", tmp);
    for (i = 0; name[i] != 0; i++) {
        if (name[i] == '.') {
            name[i] = 0;
            break;
        }
    }
}

/* "1:%s\n" */

static int tex_initTextureSub(char *name, void *pkt);

INCLUDE_ASM(tex_initTextureSub);

/* "%s" */
/* "%s.tm2" */

/* "FALSE" */

int tex_LoadTexturePart(char *name, int area);

INCLUDE_ASM(tex_LoadTexturePart);

/* "FALSE" */

INCLUDE_ASM(tex_TransTexture);

/* a texture record by index, which tex_TransTextureDefocus and
 * tex_SetUVScroll inline */
static inline TexData *getTextureData(int idx) /* derived name */
{
    return &texTable[idx].rec;
}

typedef struct TexColor { /* field names derived */
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} TexColor; /* derived name */

/* as in GifPacket.h, which this TU does not include */
extern void gif_SetZTest(int on);
/* as in GifPacket.h, which this TU does not include */
extern void gif_SetZWrite(int on);
/* as in GifPacket.h, which this TU does not include */
extern void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm, unsigned int w,
                                  unsigned int h, int useoffset, int clear);
/* this file's one use passes the depth as a 32-bit 0xFFFFFFFF: void (int *,
 * unsigned int, int *, TexColor *, int) here, void (GifRect *, long long,
 * GifRect *, GifColor *, int) in GifPacket.h */
extern void gif_SpriteSensitiveOrg(int *r, unsigned int z, int *uv, TexColor *col, int prim);

INCLUDE_ASM(tex_TransTextureDefocus);

/* A 256-entry CLUT is held in CSM1 order, the two halves of every other
 * 16-entry block swapped, so an entry index is swizzled before the entry is
 * touched. A 16-entry CLUT is held straight. tex_dispClut walks the same
 * order. */
#define CLUT_CSM1(n, i) /* derived name */                                                         \
    ((n) == 16 ? (i)                                                                               \
     : (((i) & 0xF) >= 8 && (((i) >> 4) & 1) == 0)                                                 \
         ? (i) + 8                                                                                 \
         : ((((i) & 0xF) < 8 && (((i) >> 4) & 1) != 0) ? (i) - 8 : (i)))

/* the scroll step and the offset are ints in the ICO block but their sign is
 * taken through a float comparison (Basic.h's ABSF and SIGNF) */

INCLUDE_ASM(tex_scrollClut);

INCLUDE_ASM(tex_SetUVScroll);

static void tex_textureAnimation(void);

INCLUDE_ASM(tex_SetClutAnimation);

INCLUDE_ASM(tex_FreeTexture);

/* PAL's per-priority VRAM cursor reset (an inline of tex_ResetVram and the
 * head-TBP lock pair) has no copy here: tex_ResetVram is stubbed and the lock
 * pair and its table are not in this build. */

/* tex_Init's first-call flag: the table is marked free once, later calls
   recount the loaded entries. */
static int texTableReady = 0; /* derived name */

INCLUDE_ASM(tex_ResetVram);

/* the GS register payloads, spelled as ico2/seki/src/GifPacket.c spells them */
#define GIF_RGBA(c) /* derived name */                                                             \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
#define GIF_XY0(x, y, z) ((long long)(x) | ((long long)(y) << 16) | ((z) << 32)) /* derived name */
#define GIF_XY(x, y, z) /* derived name */                                                         \
    ((long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16) | ((z) << 32))
/* a 640x224 layout coordinate to the screen, gif_SpriteSensitive's scaling */
#define DISP_X(v) ((v) * ScreenWidth / 640)  /* derived name */
#define DISP_Y(v) ((v) * ScreenHeight / 224) /* derived name */

/* The far corner, x + fx with fx = w + 0x8000, the way gif_MakeSpriteNoTexture
 * in GifPacket.c holds it. */
static inline int dispFar(int x, int w) /* derived name */
{
    int fx = w + 0x8000;

    return x + fx;
}

/* The untextured sprite of gif_SpriteSensitive (uv NULL, prim 0: PRIM 0x406),
 * as a macro: the corner coordinates are substituted into both corners. */
#define dispClutSprite(r, col) /* derived name */                                                  \
    {                                                                                              \
        setGsReg(0x00, 0x406);                                                                     \
        setGsReg(0x01, GIF_RGBA(col));                                                             \
        setGsReg(0x05, GIF_XY(DISP_X((r)[0]), DISP_Y((r)[1]), (long long)-4));                     \
        setGsReg(0x05, GIF_XY0(dispFar(DISP_X((r)[0]), DISP_X((r)[2])),                            \
                               dispFar(DISP_Y((r)[1]), DISP_Y((r)[3])), (long long)-4));           \
    }

/* The CLUT viewer: mode 0 draws a 256-entry CLUT as a 16x16 grid in CSM1
 * order, mode 1 a 16-entry CLUT as one row.  Each cell's rectangle is an
 * initialised block-scope array; the coordinates are pixels scaled to the
 * GS's sixteenths with `<< 4`. */
static void tex_dispClut(unsigned char *clut, int mode)
{
    int i;
    int k;

    gif_StartPacketPri(11);
    switch (mode) {
    case 0:
        for (i = 0; i < 16; i++) {
            for (k = 0; k < 16; k++) {
                int rect[4] = {(i * 10 - 160) << 4, (k * 5) << 4, 8 << 4, 4 << 4};
                int n = CLUT_CSM1(256, i + k * 16);
                dispClutSprite(rect, clut + n * 4);
            }
        }
        break;
    case 1:
        for (i = 0; i < 16; i++) {
            int rect[4] = {(i * 10 - 160) << 4, 0, 8 << 4, 4 << 4};
            dispClutSprite(rect, clut + i * 4);
        }
        break;
    }
    gif_EndPacket();
}

/* TEX1 and TEST_1 for the record's own five-qword GS packet at 0x58: the tool
 * rebuilds them from the block it just edited.  Inlined into tex_Tool. */
static inline void toolMakeRegs(TexData *t, int lv) /* derived name */
{
    int aref = 96;
    int afail = 1;
    int zte = 1;
    int ztst = 2;
    int mmag = t->ext.file.smpMag;
    int mmin = t->ext.file.smpMin;
    TexPkt *reg;

    if (t->ext.file.alpTst != 0) {
        aref = t->ext.file.alpTst;
        afail = t->ext.file.alpFai;
    }
    reg = &t->pkt;
    reg->tex1.data = ((long long)(t->levelNum - lv - 1) << 2) | ((long long)mmag << 5) |
                     ((long long)mmin << 6) | ((long long)t->ext.file.mipmapL << 19) |
                     ((long long)t->ext.file.mipmapK << 32);
    /* 13 is the alpha test switched on with the GEQUAL function in the two
     * fields below AREF */
    reg->test.data = 13 | (long long)aref << 4 | (long long)afail << 12 | (long long)zte << 16 |
                     (long long)ztst << 17;
}

/* the shared pad-state array (main.c's PadState): holding the 0x10 button on
 * pad 0 drops alpha blending from the PRIM word. */

INCLUDE_ASM(tex_printTexture);

/* The texture tool's menu table, one row per tunable. `type` picks how `var`
 * is read back: 0 an int, 1 a float, 2 a short. */
typedef struct TexToolRow { /* field names derived */
    char *label;
    float min;
    float max;
    float step;
    int type;
    void *var;
    int _18;
} TexToolRow; /* derived name */

INCLUDE_ASM(tex_Tool);

/* tex_ListTool's short names: per TIM2 image type, per CLUT type and per
   user-header state */
static char *imageTypeName[] = {"NON", "D16", "D24", "D32", "C-4", "C-8"}; /* derived name */

static char *clutTypeName[] = {"--", "16", "24", "32"}; /* derived name */

static char *headerName[] = {" ", "\x80"}; /* derived name */

/* tex_ListTool's state: whether a row is open in tex_Tool, and the texture
   number tex_Tool edits. */
static int listEditing = 0; /* derived name */

static int listTexNo = 0; /* derived name */

static inline void remakeSampling(TexData *t) /* derived name */
{
    int mmag = 1;
    int mmin = GlobalStageSetting.texSampleMode;

    if (t->ext.animated != 0) {
        mmag = t->ext.file.smpMag;
        mmin = t->ext.file.smpMin;
    }
    t->pkt.tex1.data = (t->pkt.tex1.data & ~0xE0) | (mmag << 5) | (mmin << 6);
}

INCLUDE_ASM(tex_ListTool);

int tex_GetTWTH(int size)
{
    return getTWTH(size);
}

int tex_InitTexture(char *name, void *pkt)
{
    return tex_initTextureSub(name, pkt);
}

int tex_LoadTexture(char *name)
{
    return tex_LoadTexturePart(name, 0);
}

/* the name lookup, which tex_SetUVScroll inlines */
static inline int getTextureNo(const char *name) /* derived name */
{
    int i;
    int ret = -1;

    for (i = 0; i < texCount; i++) {
        if (texTable[i].rec.ext.used) {
            if (strcmp(name, texTable[i].rec.name) == 0) {
                ret = i;
                break;
            }
        }
    }
    return ret;
}

INCLUDE_ASM(tex_GetTextureNo);

INCLUDE_ASM(tex_GetTextureData);

INCLUDE_ASM(tex_GetTextureName);

INCLUDE_ASM(tex_SetSamplingType);

INCLUDE_ASM(tex_GetTexExtData);

short tex_GetVramFreeAddress(int pri)
{
    return vramPri[pri].texAddr;
}

INCLUDE_ASM(tex_ResetVramPri);

int tex_GetTextureNum(void)
{
    return texCount;
}

/* the int flag is the last parameter, after the six floats */

INCLUDE_ASM(tex_Init);

INCLUDE_ASM(tex_RemakeRegistersSampleMin);
