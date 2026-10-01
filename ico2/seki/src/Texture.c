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

/* One mipmap level of a texture record: the ROM reads addr with lw at +0, dbw
 * and vramSize with lh at +4 and +6, and indexes a 13-entry short table at +8
 * by the display list priority (tex_initTM2's clear loops run j from 12 down
 * to 0). The stride between levels is 0x24. The CLUT gets a record of its own
 * at 0xE4 and the image's mipmap levels an array at 0x108: that split is what
 * makes the ROM multiply the loop index by 0x24 and fold the 0x108 into the
 * displacement instead of adding one to the index. The array length is not
 * pinned by the ROM, only the two bases and the stride; tex_initTM2 clears
 * seven of them and they end at 0x204, below the packet tex_TransTexture
 * passes at 0x208. */
typedef struct TexLevel {
    void *addr;
    short dbw;
    short vramSize;
    short tbp[13];
    short pad22;
} TexLevel;

/* the 0x40-byte block the ICO tools append to the TIM2 header, recognised by
 * its "ICO" magic and copied whole into the first 0x40 bytes of the record's
 * TexExt at 0x268. The two ints at 0x28 and 0x2C are the mag and min filter
 * terms tex_UpdateMipMapLevel reads back as x290 and x294, and the two shorts
 * at 0x3C and 0x3E the terms it reads back as x2A4 and x2A6. */
typedef struct Tim2Ext { /* field names derived */
    char magic[4];
    /* the U and V scroll speeds, and behind them the U and V amplitudes the
     * sine animation multiplies its sample by */
    float scrlU;
    float scrlV;
    float ampU;
    float ampV;
    /* the CLUT scroll's first and last entry */
    int csBgn;
    int csEnd;
    /* the two enables tex_textureAnimation tests before it scrolls the CLUT */
    int csSpd;
    int csStp;
    /* SHINE */
    int shine;
    /* SMPMAG and SMPMIN */
    int smpMag;
    int smpMin;
    /* TEXFNC, ALPTST and ALPFAI */
    int texFnc;
    int alpTst;
    int alpFai;
    /* MIPMAPK and MIPMAPL */
    short mipmapK;
    short mipmapL;
} Tim2Ext;

/* the texture's UV packet at 0xA8 of the texture record, three quadwords the
 * record hands the display list: the two scroll offsets tex_textureAnimation
 * writes and tex_SetUVScroll seeds sit in its second quadword. */
typedef struct TexUV { /* field names derived */
    char pad0[0x10];
    float uOfs;
    float vOfs;
    char pad18[0x30 - 0x18];
} TexUV;

/* the record's own five-quadword GS packet at 0x58 (the GIF tag, TEX1 and
 * TEST_1 with their register addresses, and the closing tag), built word by
 * word and register by register; d[4] is the TEX1 value and d[6] TEST_1 */
typedef union TexPkt {
    int w[20];
    long long d[10];
} TexPkt;

/* the animation record at 0x268 of the texture record. It opens with the
 * 0x40-byte ICO block copied off the TIM2 header and continues with the state
 * the animation keeps between frames. */
typedef struct TexExt { /* field names derived */
    Tim2Ext file;
    int animated; /* set when the TIM2 carries the ICO block; tex_Tool walks the table by it */
    float uLimit; /* the U and V offsets the scroll stops at while limitOn is set */
    float vLimit;
    int limitOn;
    unsigned short frame;     /* the UV animation's frame */
    unsigned short clutFrame; /* the CLUT scroll's frame */
    /* the three CLUT copies tex_initTextureSub allocates for the scroll */
    void *clutA;
    void *clutB;
    void *clutOrg; /* the untouched copy the other two are restored from */
    /* one byte per display list priority: the slot's transfer-done flag */
    char transDone[8];
    unsigned int pad68;
    unsigned char pad6C;
    unsigned short used : 1;
    /* the mipmap level the record is drawn from */
    unsigned short level : 15;
    unsigned short pad6F : 1;
    short partition; /* the allocator partition the record was built in */
    char pad72[0x78 - 0x72];
} TexExt;

typedef struct CdvdRec { /* field names derived */
    /* the trimmed name tex_GetTextureNo compares against, and behind it the
     * path the texture was loaded from, which tex_initTextureSub keeps so a
     * second read of the same name from a different path can be reported */
    char name[0x18];
    char file[0x40];
    TexPkt pkt; /* 0x58 */
    TexUV uv;   /* 0xA8 */
    /* the base of the per-level transfer packets tex_setRegisters allocates */
    char *levelPkt;
    /* the TIM2 file image the record was built from */
    void *tim2;
    unsigned short levelNum; /* the mipmap level count */
    char padE2[0xE4 - 0xE2];
    TexLevel clut;
    TexLevel lv[7];
    char pad204[0x20C - 0x204];
    /* the byte count tex_Tool hands malloc_MemCpy when it rebuilds the three
     * shadow copies of the image after an edit */
    int clutSize;
    char pad210[0x268 - 0x210];
    /* the animation record, opening with the 0x40-byte ICO block copied
     * whole from the TIM2 header */
    TexExt ext;
} CdvdRec;

/* one texture slot, 0x2E8 bytes: eight bytes the record follows. The code
 * passes the record itself around (the address of slot + 8). */
typedef struct TexEntry {
    char head[8];
    CdvdRec rec;
} TexEntry;

/* .sbss, Texture.o's two words in the ROM's order (MAIN.MAP line 7580 sizes
   the run 8 and names no symbol in it, so the names are ours): the row
   tex_Tool has selected, and the number of texture slots in use. */
static int toolRow;

static int texCount;

typedef struct TexClutEnt {
    int f0;
    int f4;
    int f8;
} TexClutEnt;

/* .data, Texture.o's whole run in the ROM's order (MAIN.MAP line 5807, 0xB0;
   the map names mipmap_header_size at +0 and textype at +0x68, the other
   four are file statics it does not name, so their names are ours). */

/* the TIM2 mipmap header size by mipmap level count */
int mipmap_header_size[] = {0, 0, 32, 32, 32, 48, 48, 48};

/* one entry per TIM2 image type: the GS pixel storage mode and the two
   factors the buffer width and size arithmetic reads */
static TexClutEnt psmTable[] = {
    {0, 0, 0}, {2, 4, 4}, {1, 3, 2}, {0, 2, 2}, {20, 1, 1}, {19, 2, 1},
};

/* one string per TIM2 image type, printed with %8s */
char *textype[] = {"NONE", "PSMCT16", "PSMCT24", "PSMCT32", "PSMT4", "PSMT8"};

/* one VRAM slot per display list priority: the free-address cursor, the top of
 * the region and the texture id the slot last had programmed. */
typedef struct VramPri {
    short f0;
    short f1;
    short f2;
} VramPri;

/* .bss, Texture.o's run in the ROM's order (MAIN.MAP line 7685 names no symbol
 * in it, so the names are ours; 0x245D0 there is the January object before the
 * retail revision added headTbp): the VRAM slot per display list priority, the
 * 200 texture slots, the head TBP tex_LockHeadTBP holds per priority, and the
 * working copy of the selected texture's ICO block tex_Tool edits. */
static VramPri vramPri[13];

static TexEntry texTable[200];

static int headTbp[14];

static Tim2Ext toolExt;

/* PUBLIC SDK NAMING RUNG: the TIM2 picture header. The fields this TU reads off
 * it are clutColors at 0x0E, clutType at 0x12 (masked with 0x3F where the
 * compound bits have to go), imageType at 0x13 and the width and height at
 * 0x14 and 0x16. */
typedef struct Tim2Picture {
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
} Tim2Picture;

/* PUBLIC SDK NAMING RUNG: the mipmap header that follows the picture header
 * when there is more than one level, two MIPTBP registers and then one image
 * size per level. tex_makeTexturePacket proves the split: it copies 0x30 bytes
 * of picture header into the record and a second 0x30 bytes of mipmap header
 * after it, and it steps over a variable number of size words through the
 * mipmap_header_size table before it reaches the ICO block. */
typedef struct Tim2Mipmap {
    unsigned long long GsMiptbp1;
    unsigned long long GsMiptbp2;
    unsigned int sizes[8];
} Tim2Mipmap;

/* The two VRAM bump allocators tex_AllocVramAuto dispatches to. The listing
   attributes them to two separate line runs of Texture.c (533/535 and
   558/560) whose tails jump.c cross-jumped into the one shared copy at
   563/565/566, which is what makes tex_AllocVramAuto's two switch arms share
   everything from the limit test down. Both names are ours: an inlined static
   leaves no symbol for the map to record. The limits are the texture and CLUT
   ends of the 16 KB VRAM window the priority table hands out. */
static inline int texAllocTexVram(int size)
{
    int pri = dl_GetPri();
    int ret;

    if (16000 <= vramPri[dl_GetPri()].f0 + size) {
        tex_ResetVramPri(pri);
    }
    ret = vramPri[dl_GetPri()].f0;
    vramPri[dl_GetPri()].f0 = ret + size;
    return ret;
}

static inline int texAllocClutVram(int size)
{
    int pri = dl_GetPri();
    int ret;

    if (16128 <= vramPri[dl_GetPri()].f1 + size) {
        tex_ResetVramPri(pri);
    }
    ret = vramPri[dl_GetPri()].f1;
    vramPri[dl_GetPri()].f1 = ret + size;
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

/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_StartPacketPri(int pri);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_SetGsReg(long long reg, long long val);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_EndPacket(void);

/* "0" */

/* three qwords: a VIF DIRECT of two, the GIF A+D tag and the TEXFLUSH write
   that closes the upload; qword aligned because
   dl_OpenDma chains it into the display list as a DMA source */
static const unsigned int texFlushPacket[3][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x50000002},
    {0x8001, 0x10000000, 0xE, 0},
    {1, 0, 0x3F, 0},
};

int tex_loadImage(unsigned int addr, CdvdRec *tex, int idx, short dbp, short dbw, short dpsm,
                  short dsax, short dsay, short w, short h)
{
    int size = 0;

    switch (dpsm) {
    case 0:  /* PSMCT32 */
    case 48: /* PSMZ32 */
        size = w * h >> 2;
        break;
    case 1:  /* PSMCT24 */
    case 49: /* PSMZ24 */
        size = w * h * 3 >> 4;
        break;
    case 2:  /* PSMCT16 */
    case 10: /* PSMCT16S */
    case 50: /* PSMZ16 */
    case 58: /* PSMZ16S */
        size = w * h >> 3;
        break;
    case 19: /* PSMT8 */
    case 27: /* PSMT8H */
        size = w * h >> 4;
        break;
    case 20: /* PSMT4 */
    case 36: /* PSMT4HL */
    case 44: /* PSMT4HH */
        size = w * h >> 5;
        break;
    default:
        /* "tex_loadImage:" + EUC-JP "the texture format cannot be told apart" + ".\n" */
        debug_StdPrintfDummy("tex_loadImage:判別できないテクスチャフォーマットです.\n");
        debug_assert("src/Texture.c", 645);
        __assert("src/Texture.c", 645, "0");
    }
    if (size > 0x20000) {
        /* "tex_loadImage:" + EUC-JP "the texture size is too large" + ".\n" */
        debug_StdPrintfDummy("tex_loadImage:テクスチャのサイズが大きすぎます.\n");
        debug_assert("src/Texture.c", 650);
        __assert("src/Texture.c", 650, "0");
    }
    gif_StartPacketPri(dl_GetPri());
    gif_SetGsReg(0x50, ((long long)dbp << 32) | ((long long)dbw << 48) | ((long long)dpsm << 56));
    gif_EndPacket();
    dl_OpenDma(2, (tex->levelPkt + idx * 80), 5);
    dl_CloseDma();
    dl_OpenDma(2, addr & 0x0FFFFFFF, size + 3);
    dl_CloseDma();
    dl_OpenDma(2, texFlushPacket, 3);
    dl_CloseDma();
    return size << 4;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTWTH into tex_setTexReg and tex_TransTextureDefocus, so it is a
 * public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted at its ROM position and the callers inline this static
 * stand-in, which collapses at layout. */
static inline int getTWTH(int a0)
{
    int ret = -1;
    int i;
    for (i = 0; i < 11; i++) {
        if ((1 << i) >= a0) {
            ret = i;
            break;
        }
    }
    return ret;
}

/* The GS A+D writer this TU expands at every site. It is a MACRO and not the
 * static inline stand-in src/GifPacket.c carries, and the ROM says which:
 * expanded here, the packet cursor is read and bumped BEFORE the register
 * value is computed (`lw 0x10`, save, `addiu 8`, `sw 0x10`, then the forty
 * instructions of the value, then the `sd`), and the second write re-reads
 * the cursor. Through an inline function the value is an argument, so it is
 * computed first and the second write reuses the bumped cursor in a register:
 * two instructions short per packet, measured on all four of them. */
#define setGsReg(reg, val)                                                                         \
    {                                                                                              \
        *PacketBufferStruct.ptr.d++ = (val);                                                       \
        *PacketBufferStruct.ptr.d++ = (reg);                                                       \
    }
/* the record carries seven mipmap levels, so a level index is clamped to the
 * last one before it indexes lv[] */
#define TEXLV(n) ((n) < 7 ? (n) : 6)

void tex_setTexReg(Tim2Picture *pic, CdvdRec *t, int levels, int lv, int clut)
{
    unsigned int tfx = 0;

    if (t->ext.animated != 0) {
        tfx = t->ext.file.texFnc;
    }
    gif_StartPacketPri(dl_GetPri());
    switch (clut) {
    case 0:
        setGsReg(6, (long long)t->lv[TEXLV(lv)].tbp[dl_GetPri()] |
                        ((long long)t->lv[TEXLV(lv)].dbw << 14) |
                        ((long long)psmTable[pic->imageType].f0 << 20) |
                        ((long long)(getTWTH(pic->imageWidth) - lv) << 26) |
                        ((long long)(getTWTH(pic->imageHeight) - lv) << 30) | ((long long)1 << 34) |
                        ((long long)tfx << 35));
        break;
    case 1:
        setGsReg(6, (long long)t->lv[TEXLV(lv)].tbp[dl_GetPri()] |
                        ((long long)t->lv[TEXLV(lv)].dbw << 14) |
                        ((long long)psmTable[pic->imageType].f0 << 20) |
                        ((long long)(getTWTH(pic->imageWidth) - lv) << 26) |
                        ((long long)(getTWTH(pic->imageHeight) - lv) << 30) | ((long long)1 << 34) |
                        ((long long)tfx << 35) | ((long long)t->clut.tbp[dl_GetPri()] << 37) |
                        ((long long)psmTable[pic->clutType & 0x3F].f0 << 51) |
                        ((long long)2 << 61));
        break;
    default:
        /* EUC-JP: "a texture type that is neither DIRECT nor CLUT was specified" + ".\n" */
        debug_StdPrintfDummy("DIRECTでもCLUTでもないテクスチャタイプが指定されました.\n");
        debug_assert("src/Texture.c", 788);
        __assert("src/Texture.c", 788, "0");
        break;
    }
    if (2 <= levels) {
        setGsReg(0x34, (long long)t->lv[TEXLV(lv + 1)].tbp[dl_GetPri()] |
                           ((long long)t->lv[TEXLV(lv + 1)].dbw << 14) |
                           ((long long)t->lv[TEXLV(lv + 2)].tbp[dl_GetPri()] << 20) |
                           ((long long)t->lv[TEXLV(lv + 2)].dbw << 34) |
                           ((long long)t->lv[TEXLV(lv + 3)].tbp[dl_GetPri()] << 40) |
                           ((long long)t->lv[TEXLV(lv + 3)].dbw << 54));
    }
    if (5 <= levels) {
        setGsReg(0x36, (long long)t->lv[TEXLV(lv + 4)].tbp[dl_GetPri()] |
                           ((long long)t->lv[TEXLV(lv + 4)].dbw << 14) |
                           ((long long)t->lv[TEXLV(lv + 5)].tbp[dl_GetPri()] << 20) |
                           ((long long)t->lv[TEXLV(lv + 5)].dbw << 34) |
                           ((long long)t->lv[TEXLV(lv + 6)].tbp[dl_GetPri()] << 40) |
                           ((long long)t->lv[TEXLV(lv + 6)].dbw << 54));
    }
    gif_EndPacket();
}

/* listing rows 708-710: a file-static helper with no symbol of its own, so the
 * January-2002 build inlined it at its only call site. It claims one VRAM
 * buffer per level for the current display list priority. */
static inline void texAllocVram(CdvdRec *t, int levels, int lv)
{
    int i;

    t->clut.tbp[dl_GetPri()] = tex_AllocVramAuto(1, t->clut.vramSize);
    for (i = lv; i < levels - lv; i++) {
        t->lv[i].tbp[dl_GetPri()] = tex_AllocVramAuto(0, t->lv[i].vramSize);
    }
}

/* listing rows 677 and 694: the level upload, a second file-static helper
 * inlined at both call sites. Its parameters are ints, so the short loads of
 * the buffer slot, the buffer width and the format word are folded into the
 * narrowing for tex_loadImage's short parameters on row 694, while the address
 * needs no narrowing and is loaded on row 677, the header, where the inlined
 * copy of the argument is made. */
static inline int texLoadLevel(void *addr, CdvdRec *t, int n, int dbp, int dbw, int dpsm, int w,
                               int h)
{
    return tex_loadImage((unsigned int)addr, t, n, dbp, dbw, dpsm, 0, 0, w, h);
}

int tex_transVramClutTex(Tim2Picture *pic, CdvdRec *t, int levels, int lv)
{
    int total;
    int n;
    int i;
    short w = 16, h = 16;

    texAllocVram(t, levels, lv);
    if (pic->clutColors == 16) {
        w = 8;
        h = 2;
    }
    total = texLoadLevel(t->clut.addr, t, levels - lv, t->clut.tbp[dl_GetPri()], t->clut.dbw,
                         psmTable[pic->clutType & 0x3F].f0, w, h);
    for (i = lv; i < levels - lv; i++) {
        n = texLoadLevel(t->lv[i].addr, t, i, t->lv[i].tbp[dl_GetPri()], t->lv[i].dbw,
                         psmTable[pic->imageType].f0, pic->imageWidth >> i, pic->imageHeight >> i);
        total += n;
    }
    return total;
}

/* listing rows 732-733: the same claim loop as texAllocVram's tail without the
 * CLUT, a 2001 copy of it. */
static inline void texAllocLevels(CdvdRec *t, int levels, int lv)
{
    int i;

    for (i = lv; i < levels - lv; i++) {
        t->lv[i].tbp[dl_GetPri()] = tex_AllocVramAuto(0, t->lv[i].vramSize);
    }
}

int tex_transVramDirectTex(Tim2Picture *pic, CdvdRec *t, int levels, int lv)
{
    int total = 0;
    int n;
    int i;

    texAllocLevels(t, levels, lv);
    for (i = lv; i < levels - lv; i++) {
        n = texLoadLevel(t->lv[i].addr, t, i, t->lv[i].tbp[dl_GetPri()], t->lv[i].dbw,
                         psmTable[pic->imageType].f0, pic->imageWidth >> i, pic->imageHeight >> i);
        total += n;
    }
    return total;
}

void tex_transRegister(CdvdRec *t)
{
    dl_OpenDma(2, &t->pkt, 5);
    dl_CloseDma();
}

extern int tex_transVramDirectTex(Tim2Picture *pic, CdvdRec *t, int levels, int lv);
extern int tex_transVramClutTex(Tim2Picture *pic, CdvdRec *t, int levels, int lv);
extern void tex_setTexReg(Tim2Picture *pic, CdvdRec *t, int levels, int lv, int clut);

/* "FALSE" */

int tex_transTM2(Tim2Picture *pic, CdvdRec *t, int id, int pri)
{
    int ret = 0;
    int levels = t->levelNum - texTable[id].rec.ext.level;

    if (8 <= levels) {
        /* "tex_transTM2:" + EUC-JP "there are too many mipmap textures" + ".\n" */
        debug_StdPrintfDummy("tex_transTM2:ミップマップテクスチャの枚数が多すぎます.\n");
        debug_assert("src/Texture.c", 886);
        __assert("src/Texture.c", 886, "FALSE");
    }
    dl_SetDLPriority(pri);
    switch (pic->imageType) {
    case 1:
    case 2:
    case 3:
        if (texTable[id].rec.ext.transDone[pri] == 0) {
            ret = tex_transVramDirectTex(pic, t, levels, texTable[id].rec.ext.level);
        }
        if (vramPri[dl_GetPri()].f2 != id) {
            tex_transRegister(t);
            tex_setTexReg(pic, t, levels, texTable[id].rec.ext.level, 0);
            vramPri[dl_GetPri()].f2 = id;
            texregs++;
        }
        break;
    case 4:
    case 5:
        if (texTable[id].rec.ext.transDone[pri] == 0) {
            ret = tex_transVramClutTex(pic, t, levels, texTable[id].rec.ext.level);
        }
        if (vramPri[dl_GetPri()].f2 != id) {
            tex_transRegister(t);
            tex_setTexReg(pic, t, levels, texTable[id].rec.ext.level, 1);
            vramPri[dl_GetPri()].f2 = id;
            texregs++;
        }
        break;
    default:
        /* EUC-JP "the texture is corrupt" + ".\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n" */
        debug_StdPrintfDummy("テクスチャが壊れています.\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n",
                             t, pic->imageType, pic->clutType, t->lv[0].addr, t->clut.addr, t);
        debug_assert("src/Texture.c", 919);
        __assert("src/Texture.c", 919, "FALSE");
        break;
    }
    texTable[id].rec.ext.transDone[pri] = 1;
    return ret;
}

/* listing rows 479-500: a file-static helper with no symbol of its own, so the
 * January-2002 build inlined it; it is inlined three times in this TU, twice in
 * tex_initClutTexture and once here, and each copy owns its own jump table. It
 * turns a width in texels into the GS buffer width in units of 64. The case
 * list is read out of the ROM's own table words: the eleven arm-A indices are
 * PSMCT32, PSMCT24, PSMCT16, PSMCT16S, PSMT8H, PSMT4HL, PSMT4HH, PSMZ32,
 * PSMZ24, PSMZ16 and PSMZ16S, and the two arm-B indices are the two
 * half-a-texel-per-byte formats PSMT8 and PSMT4, which round up to an even
 * number of blocks. */
static inline int texTBW(TexClutEnt *e, int w)
{
    int psm = e->f0;
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

void tex_initClutTexture(Tim2Picture *pic, CdvdRec *t)
{
    int i;
    int dbw;

    t->clut.vramSize = 8;

    t->clut.dbw = texTBW(&psmTable[pic->clutType & 0x3F], pic->imageWidth);

    for (i = 0; i < t->levelNum; i++) {
        t->lv[i].vramSize =
            ((pic->imageWidth >> i) * (pic->imageHeight >> i) / psmTable[pic->imageType].f4 / 2) *
                psmTable[pic->imageType].f8 >>
            6;

        dbw = texTBW(&psmTable[pic->imageType], pic->imageWidth >> i);

        t->lv[i].dbw = dbw;
    }
}

void tex_setRegisters(Tim2Picture *pic, CdvdRec *t)
{
    int *p;
    int *q;
    int i;
    int levels = t->levelNum;
    int cw = 0;
    int ch = 0;
    int mmag = 1;
    int mmin = GlobalStageSetting.texSampleMode;
    int aref = 96;
    int atst = 1;
    int k = -165;
    int l = 0;

    if (t->ext.animated != 0) {
        mmag = t->ext.file.smpMag;
        mmin = t->ext.file.smpMin;
        if (t->ext.file.alpTst != 0) {
            aref = t->ext.file.alpTst;
            atst = t->ext.file.alpFai;
        }
        k = t->ext.file.mipmapK;
        l = t->ext.file.mipmapL;
    }

    p = t->pkt.w;

    p[0] = 0;
    p[1] = 0;
    p[2] = 0x13000000;
    p[3] = 0x6C038000;

    *(long long *)(p + 4) = 0x1000000000008002LL;
    *(long long *)(p + 6) = 14;

    *(long long *)(p + 8) = ((long long)(levels - 1) << 2) | ((long long)mmag << 5) |
                            ((long long)mmin << 6) | ((long long)l << 19) | ((long long)k << 32);
    *(long long *)(p + 10) = 20;
    *(long long *)(p + 12) =
        1 | (6 << 1) | ((long long)aref << 4) | ((long long)atst << 12) | (1 << 16) | (2 << 17);
    *(long long *)(p + 14) = 71;

    p[16] = 0x15000000;
    p[17] = 0;
    p[18] = 0;
    p[19] = 0;

    q = (int *)&t->uv;

    q[0] = 0;
    q[1] = 0;
    q[2] = 0x13000000;
    q[3] = 0x6C018000;

    q[4] = 0;
    q[5] = 0;
    *(long long *)(q + 6) = 0;

    q[8] = 0x15000002;
    q[9] = 0;
    q[10] = 0;
    q[11] = 0;

    t->levelPkt =
        mallocseki((pic->imageType == 4 || pic->imageType == 5 ? levels + 1 : levels) * 80);

    switch (pic->imageType) {
    case 1:
    case 2:
    case 3:
        break;
    case 4:
        cw = 8;
        ch = 2;
        break;
    case 5:
        cw = 16;
        ch = 16;
        break;
    default:
        debug_StdPrintfDummy("テクスチャが壊れています.\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n",
                             t, pic->imageType, pic->clutType, t->lv[0].addr, t->clut.addr, t);
        debug_assert("src/Texture.c", 1066);
        __assert("src/Texture.c", 1066, "FALSE");
    }

    /* listing row 1069 is a second switch on the same field: the case range
     * 4..5 is what lowers to the ROM's signed slti 6 and slti 4 pair, and gcse
     * shares the field's load with the switch above, reloading it only after
     * the default arm's calls. */
    switch (pic->imageType) {
    case 4:
    case 5:
        *(int *)(t->levelPkt + levels * 80) = 0;
        *(int *)(t->levelPkt + levels * 80 + 4) = 0;
        *(int *)(t->levelPkt + levels * 80 + 8) = 0x13000000;
        *(int *)(t->levelPkt + levels * 80 + 12) = 0x50000005;

        *(long long *)(t->levelPkt + levels * 80 + 16) = 0x1000000000008004LL;
        *(long long *)(t->levelPkt + levels * 80 + 24) = 14;

        *(long long *)(t->levelPkt + levels * 80 + 32) = 0;
        *(long long *)(t->levelPkt + levels * 80 + 40) = 81;
        *(long long *)(t->levelPkt + levels * 80 + 48) = cw | ((long long)ch << 32);
        *(long long *)(t->levelPkt + levels * 80 + 56) = 82;

        *(long long *)(t->levelPkt + levels * 80 + 64) = 0;
        *(long long *)(t->levelPkt + levels * 80 + 72) = 83;
        break;
    }

    for (i = 0; i < levels; i++) {
        *(int *)(t->levelPkt + i * 80) = 0;
        *(int *)(t->levelPkt + i * 80 + 4) = 0;
        *(int *)(t->levelPkt + i * 80 + 8) = 0x13000000;
        *(int *)(t->levelPkt + i * 80 + 12) = 0x50000005;

        *(long long *)(t->levelPkt + i * 80 + 16) = 0x1000000000008004LL;
        *(long long *)(t->levelPkt + i * 80 + 24) = 14;

        *(long long *)(t->levelPkt + i * 80 + 32) = 0;
        *(long long *)(t->levelPkt + i * 80 + 40) = 81;
        *(long long *)(t->levelPkt + i * 80 + 48) =
            (pic->imageWidth >> i) | ((long long)(pic->imageHeight >> i) << 32);
        *(long long *)(t->levelPkt + i * 80 + 56) = 82;

        *(long long *)(t->levelPkt + i * 80 + 64) = 0;
        *(long long *)(t->levelPkt + i * 80 + 72) = 83;
    }
}

/* listing rows 970-979: the second file-static helper, inlined here only. It
 * fills in one VRAM size and one buffer width per mipmap level. */
static inline void texInitMipLevels(Tim2Picture *pic, CdvdRec *t)
{
    int i;
    int dbw;

    for (i = 0; i < t->levelNum; i++) {
        t->lv[i].vramSize =
            ((pic->imageWidth >> i) * (pic->imageHeight >> i) / psmTable[pic->imageType].f4) *
                psmTable[pic->imageType].f8 >>
            6;

        dbw = texTBW(&psmTable[pic->imageType], pic->imageWidth >> i);

        t->lv[i].dbw = dbw;
    }
}

extern void tex_setRegisters(Tim2Picture *pic, CdvdRec *t);

/* "FALSE" */

void tex_initTM2(Tim2Picture *pic, CdvdRec *t)
{
    int i;
    int j;

    for (i = 0; i < 7; i++) {
        t->lv[i].dbw = 0;
        for (j = 0; j < 13; j++) {
            t->lv[i].tbp[j] = 0;
        }
    }
    t->clut.dbw = 0;
    for (i = 0; i < 13; i++)
        t->clut.tbp[i] = 0;

    switch (pic->imageType) {
    case 4:
    case 5:
        tex_initClutTexture(pic, t);
        break;
    case 1:
    case 2:
    case 3:
        texInitMipLevels(pic, t);
        break;
    default:
        debug_StdPrintfDummy("テクスチャが壊れています.\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n",
                             t, pic->imageType, pic->clutType, t->lv[0].addr, t->clut.addr, t);
        debug_assert("src/Texture.c", 1143);
        __assert("src/Texture.c", 1143, "FALSE");
        break;
    }
    tex_setRegisters(pic, t);
}

void tex_convertClutCSM2ToCSM1(Tim2Picture *pic)
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

/* PUBLIC SDK NAMING RUNG: the two transfer packets libgraph fills in. Only
 * their sizes are read from the ROM: sceGsSetDefLoadImage's last store is the
 * sq at 0x50 of its argument, so the load packet is 0x60 bytes, and
 * sceGsSetDefStoreImage's last store is the sd at 0x68, so the store packet is
 * 0x70; the frame's local block is exactly the two of them, 0xD0. */
typedef struct sceGsLoadImage {
    long long qw[12];
} sceGsLoadImage;

typedef struct sceGsStoreImage {
    long long qw[14];
} sceGsStoreImage;

/* dpsm is short here for the reason the repo's sceGsSetDefDispEnv declaration
 * carries: the ROM reads psmTable's first word with lh at this call site and
 * with lw five instructions later, so the argument is a 16-bit conversion of an
 * int field, which is what a short parameter spells. */
extern void sceGsSetDefLoadImage(sceGsLoadImage *img, int dbp, int dbw, short dpsm, int dsax,
                                 int dsay, int rrw, int rrh);
extern void sceGsSetDefStoreImage(sceGsStoreImage *img, int sbp, int sbw, int spsm, int ssax,
                                  int ssay, int rrw, int rrh);
extern int sceGsExecLoadImage(sceGsLoadImage *img, void *src);
extern int sceGsExecStoreImage(sceGsStoreImage *img, void *dst);

/* "FALSE" */

void tex_convertImage(void *dst, void *src, short fmt, short w, short h)
{
    sceGsLoadImage limg;
    sceGsStoreImage simg;
    int w2 = w;

    sceGsSyncPath(0, 0);
    sceGsSetDefLoadImage(&limg, 0x2800, w >> 6, psmTable[fmt].f0, 0, 0, w2, h);
    FlushCache(0);
    if (sceGsExecLoadImage(&limg, src)) {
        debug_assert("src/Texture.c", 1246);
        __assert("src/Texture.c", 1246, "FALSE");
    }
    sceGsSyncPath(0, 0);
    switch (psmTable[fmt].f0) {
    case 19:
        w2 = w >> 2;
        break;
    case 20:
        w2 = w >> 3;
        break;
    default:
        debug_assert("src/Texture.c", 1251);
        __assert("src/Texture.c", 1251, "FALSE");
        break;
    }
    if (32767 < w * h >> 4) {
        debug_assert("src/Texture.c", 1254);
        __assert("src/Texture.c", 1254, "FALSE");
    }
    sceGsSetDefStoreImage(&simg, 0x2800, w2 >> 6, 0, 0, 0, w2, h);
    FlushCache(0);
    if (sceGsExecStoreImage(&simg, dst)) {
        debug_assert("src/Texture.c", 1259);
        __assert("src/Texture.c", 1259, "FALSE");
    }
    sceGsSyncPath(0, 0);
}

extern void malloc_MemCpy(void *dst, void *src, int n);

void tex_makeCopyImage(Tim2Picture *pic, CdvdRec *t, char *src, int convert)
{
    Tim2Mipmap *mip = (Tim2Mipmap *)(pic + 1);
    int i;
    int *p;
    int *q;
    int n;

    if (t->levelNum == 1) {
        t->lv[0].addr = mallocseki(pic->imageSize + 48);

        if (convert && 256 <= pic->imageWidth) {
            tex_convertImage((char *)t->lv[0].addr + 32, src, pic->imageType, pic->imageWidth,
                             pic->imageHeight);
        } else {
            malloc_MemCpy((char *)t->lv[0].addr + 32, src, pic->imageSize);
        }

        p = (int *)t->lv[0].addr;
        n = pic->imageSize >> 4;
        p[0] = 0;
        p[1] = 0;
        p[2] = 0x13000000;
        p[3] = (n + 1) | 0x50000000;
        *(long long *)(p + 4) = (n | 0x8000) | ((long long)0x8000 << 44);
        *(long long *)(p + 6) = 0;
        q = (int *)((char *)p + (pic->imageSize + 32));
        *q++ = 0;
        *q++ = 0;

        *q++ = 0;
        *q++ = 0;
    } else {
        for (i = 0; i < t->levelNum; i++) {
            t->lv[i].addr = mallocseki(mip->sizes[i] + 48);

            if (convert && 256 <= (pic->imageWidth >> i)) {
                tex_convertImage((char *)t->lv[i].addr + 32, src, pic->imageType,
                                 pic->imageWidth >> i, pic->imageHeight >> i);
            } else {
                malloc_MemCpy((char *)t->lv[i].addr + 32, src, mip->sizes[i]);
            }

            p = (int *)t->lv[i].addr;
            n = mip->sizes[i] >> 4;
            p[0] = 0;
            p[1] = 0;
            p[2] = 0x13000000;
            p[3] = (n + 1) | 0x50000000;
            *(long long *)(p + 4) = (n | 0x8000) | ((long long)0x8000 << 44);
            *(long long *)(p + 6) = 0;
            src += mip->sizes[i];
            q = (int *)((char *)p + (mip->sizes[i] + 32));
            *q++ = 0;
            *q++ = 0;

            *q++ = 0;
            *q++ = 0;
        }
    }
}

/* kept local: int (char *, const char *, ...) here, int (void *, int, ...) in stdio.h */
extern int sprintf(char *buf, const char *fmt, ...);

/* "ICO" */
/* "e" */
/* "0" */

/* listing row 1159: a one-line file-static helper with no symbol of its own,
 * inlined here only. It steps over the 16-byte TIM2 file header. */
static inline Tim2Picture *tim2Picture(void *file)
{
    return (Tim2Picture *)((char *)file + 16);
}

/* listing rows 1204-1224: the third file-static helper, inlined here only. It
 * is the CLUT twin of tex_makeCopyImage's single-level arm, the same packet
 * header written in front of a copy of the palette. */
static inline void tim2MakeClutPacket(Tim2Picture *pic, CdvdRec *t, char *clut)
{
    int *p;
    int *q;
    int n;

    if (pic->clutSize != 0) {
        t->clut.addr = mallocseki(pic->clutSize + 80);
        malloc_MemCpy((char *)t->clut.addr + 32, clut, pic->clutSize);

        p = (int *)t->clut.addr;
        n = pic->clutSize >> 4;
        p[0] = 0;
        p[1] = 0;
        p[2] = 0x13000000;
        p[3] = (n + 1) | 0x50000000;
        *(long long *)(p + 4) = (n | 0x8000) | ((long long)0x8000 << 44);
        *(long long *)(p + 6) = 0;
        q = (int *)((char *)p + (pic->clutSize + 32));
        *q++ = 0;
        *q++ = 0;

        *q++ = 0;
        *q++ = 0;
    }
}

void tex_makeTexturePacket(void *file, CdvdRec *t)
{
    char buf[1024];
    Tim2Picture *pic = tim2Picture(file);
    Tim2Mipmap *mip;
    Tim2Ext *ext;
    char *image;
    char *clut;
    int i;

    mip = (Tim2Mipmap *)(pic + 1);
    ext = (Tim2Ext *)((char *)mip + mipmap_header_size[pic->mipMapTextures]);
    image = (char *)pic + pic->headerSize;
    clut = image + pic->imageSize;

    tex_convertClutCSM2ToCSM1(pic);

    t->tim2 = file;
    t->levelNum = pic->mipMapTextures;
    t->clut.addr = 0;

    for (i = 0; i < 7; i++) {
        t->lv[i].addr = 0;
    }

    *(Tim2Picture *)((char *)t + 0x208) = *pic;
    if (2 <= pic->mipMapTextures) {
        *(Tim2Mipmap *)((char *)t + 0x238) = *mip;
    }

    if (strcmp(ext->magic, "ICO") == 0 &&
        pic->headerSize != mipmap_header_size[pic->mipMapTextures] + 48) {
        if (mipmap_header_size[pic->mipMapTextures] + 48 != pic->headerSize - 64) {
            /* "tex_makeTexturePacket:" + EUC-JP "the texture user header is an unknown
             * format" + ".'%s'\n" */
            debug_StdPrintfDummy(
                "tex_makeTexturePacket:テクスチャのユーザースペースフォーマットが異常です.'%s'\n",
                t);
            debug_assert("src/Texture.c", 1392);
            __assert("src/Texture.c", 1392, "0");
        }
        t->ext.file = *ext;
        t->ext.animated = 1;
    } else {
        t->ext.animated = 0;
    }

    switch (pic->imageType) {
    case 4:
    case 5:
        tim2MakeClutPacket(pic, t, clut);
        tex_makeCopyImage(pic, t, image, 0);
        break;
    case 1:
    case 2:
    case 3:
        tex_makeCopyImage(pic, t, image, 0);
        break;
    default:
        debug_DispQW(file, 1);
        debug_DispQW(pic, 1);
        sprintf(buf, "TEXTURE BROKEN. \"%s\"\n    I:%d C:%d iadr:%p cadr:%p hadr:%p\n", t,
                pic->imageType, pic->clutType, t->lv[0].addr, t->clut.addr, t);
        debug_StdPrintfDummy(buf);
        debug_assertMessage("src/Texture.c", 1427, buf);
        __assert("src/Texture.c", 1427, "e");
        break;
    }
}

/* kept local: int (char *, const char *, ...) here, int (void *, int, ...) in stdio.h */
extern int sprintf(char *buf, const char *fmt, ...);

/* "%s" */

/* listing rows 1444-1458 and 1564-1578: the same trimming code, written out in
 * full at both of its call sites (a 2001 copy-paste), so it has no symbol of
 * its own and the January-2002 build emitted it inline in each. It cuts the
 * directory prefix and the extension off the name in place. */
static inline void texTrimName(char *name)
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

extern void tex_makeTexturePacket(void *pkt, CdvdRec *t);

/* "1:%s\n" */

/* the old-style parameter list is not incidental: tex_InitTexture calls this
 * with NO arguments at all (the ROM's jal has an empty delay slot), which a
 * prototyped definition would reject. */
int tex_initTextureSub(name, pkt)
char *name;

void *pkt;

{
    char buf[272];
    int pri;
    int no;
    CdvdRec *t;

    pri = dl_GetPri();

    sprintf(buf, "%s", name);
    texTrimName(buf);

    no = tex_GetTextureNo(buf);
    if (no != -1) {
        if (strcmp(name, texTable[no].rec.file) != 0) {
            /* "\x1b[31m" + EUC-JP "a texture of the same name was read from another path" + ".\n" */
            debug_StdPrintfDummy("\033[31mパスの違う同名のテクスチャを読み込もうとしました.\n");
            debug_StdPrintfDummy("1:%s
", name);
            debug_StdPrintfDummy("2:%s\033[0m\n", texTable[no].rec.file);
        }
        return -1;
    }

    t = &texTable[texCount].rec;
    texTable[texCount].rec.ext.level = 0;
    texTable[texCount].rec.ext.transDone[pri] = 0;

    sprintf(t->file, "%s", name);
    sprintf(t->name, "%s", buf);
    tex_makeTexturePacket(pkt, t);
    tex_initTM2((Tim2Picture *)((char *)t + 0x208), t);
    no = texCount;

    *(int *)((char *)t + 0x2AC) = 0;
    *(int *)((char *)t + 0x2B0) = 0;
    *(int *)((char *)t + 0x2B4) = 0;
    *(short *)((char *)t + 0x2B8) = 0;
    *(short *)((char *)t + 0x2BA) = 0;
    if (t->ext.animated != 0) {
        t->ext.clutA = mallocseki(t->clutSize);

        t->ext.clutB = mallocseki(t->clutSize);

        t->ext.clutOrg = mallocseki(t->clutSize);

        malloc_MemCpy(t->ext.clutA, (char *)t->clut.addr + 0x20, t->clutSize);

        malloc_MemCpy(t->ext.clutB, (char *)t->clut.addr + 0x20, t->clutSize);

        malloc_MemCpy(t->ext.clutOrg, (char *)t->clut.addr + 0x20, t->clutSize);
    } else {
        t->ext.clutA = 0;
        t->ext.clutB = 0;
        t->ext.clutOrg = 0;
    }
    texTable[texCount].rec.ext.used = 1;

    texTable[texCount].rec.ext.partition = malloc_GetPartition();
    texCount++;
    if (200 <= texCount) {
        /* EUC-JP "there are too many textures, make the texture list region bigger" */
        debug_StdPrintfDummy("テクスチャが多すぎます.テクスチャリスト領域を増やしてください\n");
        debug_assert("src/Texture.c", 1523);
        __assert("src/Texture.c", 1523, "0");
    }
    return no;
}

/* kept local: int (char *, const char *, ...) here, int (void *, int, ...) in stdio.h */
extern int sprintf(char *buf, const char *fmt, ...);

/* "%s" */
/* "%s.tm2" */

/* "FALSE" */

int tex_LoadTexturePart(void *name, int a1)
{
    char buf[272];
    int size = 0;

    sprintf(buf, "%s.tm2", name);
    if (file_LoadFile(&size, buf, a1) >= 0) {
        texTrimName(buf);
        return tex_initTextureSub(buf, size);
    } else {
        /* EUC-JP: texture "%s" not found. */
        debug_StdPrintfDummy("テクスチャ \"%s\" がみつかりません.\n", buf);
        debug_assert("src/Texture.c", 1590);
        __assert("src/Texture.c", 1590, "FALSE");
        return -1;
    }
}

/* "FALSE" */

int tex_TransTexture(int id, int ret)
{
    CdvdRec *t = &texTable[id].rec;

    if (id < 0 || texCount <= id) {
        debug_Assert("tex_TransTexture:INVALID TEXTURE ID. %d/%d\n", id, texCount);
    }
    if (id < 0) {
        ret = -1;
    } else if (*(int *)((char *)t + 0xDC) != 0) {
        ret = tex_transTM2((Tim2Picture *)((char *)t + 0x208), t, id, ret);
    } else {
        ret = -1;
    }
    if (ret < 0) {
        if (t == 0) {
            /* "tex_TransTexture:" + EUC-JP "texture transfer failed" + ". %d\n" */
            debug_StdPrintfDummy("tex_TransTexture:テクスチャの転送に失敗しました. %d\n", id);
        } else {
            /* the same message with ". %d:%s\n" */
            debug_StdPrintfDummy("tex_TransTexture:テクスチャの転送に失敗しました. %d:%s\n", id, t);
        }
        debug_assert("src/Texture.c", 1685);
        __assert("src/Texture.c", 1685, "FALSE");
    }
    if (ret != 0) {
        textures++;
    }
    dl_OpenDma(2, &t->uv, 3);
    dl_CloseDma();
    return ret;
}

/* the same stand-in for tex_GetTextureData, whose body the listing inlines
 * here at row 1642. */
static inline int *getTextureDataDefocus(int idx)
{
    return (int *)&texTable[idx].rec;
}

typedef struct TexColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} TexColor;

/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_StartPacketPri(int pri);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_SetGsReg(long long reg, long long val);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_EndPacket(void);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_SetZTest(int on);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_SetZWrite(int on);
/* kept local: agrees with GifPacket.h, which this TU does not include (gif_SpriteSensitiveOrg differs) */
extern void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm, unsigned int w,
                                  unsigned int h, int useoffset, int clear);
/* kept local: this TU's one use passes the depth as a 32-bit 0xFFFFFFFF, which
 * the ROM materialises with a bare lui/ori and hands over unextended, so the
 * parameter is 32 bits here and not the long long GifPacket.h carries. */
/* kept local: void (int *, unsigned int, int *, unsigned char *, int) here, void (int *, long long, int *, unsigned char *, int) in GifPacket.h */
extern void gif_SpriteSensitiveOrg(int *r, unsigned int z, int *uv, unsigned char *col, int prim);

void tex_TransTextureDefocus(int id, int lv)
{
    int *p;
    int w;
    int h;
    int tbp;
    int rect[4];

    tex_TransTexture(id, dl_GetPri());

    p = getTextureDataDefocus(id);
    w = *(unsigned short *)((char *)p + 0x21C) >> lv;
    h = *(unsigned short *)((char *)p + 0x21E) >> lv;

    tbp = tex_AllocVramAuto(0, w * h / 64);

    gif_StartPacketPri(dl_GetPri());
    rect[0] = -w * 8 - 4;
    rect[1] = -h * 8 - 4;
    rect[2] = w * 16;
    rect[3] = h * 16;
    {
        int uv[4] = {8, 8, *(unsigned short *)((char *)p + 0x21C) * 16,
                     *(unsigned short *)((char *)p + 0x21E) * 16};
        TexColor col = {128, 128, 128, 128};
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetDrawEnviroment(tbp, 0, w, h, 0, 0);
        gif_SpriteSensitiveOrg(rect, 0xFFFFFFFF, uv, (unsigned char *)&col, 0);
        gif_SetZWrite(1);
        gif_SetZTest(1);

        gif_SetGsReg(6, tbp | ((long long)(w < 64 ? 1 : w / 64) << 14) |
                            ((long long)getTWTH(w) << 26) | ((long long)getTWTH(h) << 30) |
                            ((long long)1 << 34));
        gif_SetDrawEnviroment(2048, 0, ScreenWidth, ScreenHeight, 1, 0);
        gif_EndPacket();
    }
}

/* A 256-entry CLUT is held in CSM1 order, the two halves of every other
 * 16-entry block swapped, so an entry index is swizzled before the entry is
 * touched. A 16-entry CLUT is held straight. tex_dispClut walks the same
 * order. */
#define CLUT_CSM1(n, i)                                                                            \
    ((n) == 16 ? (i)                                                                               \
     : (((i) & 0xF) >= 8 && (((i) >> 4) & 1) == 0)                                                 \
         ? (i) + 8                                                                                 \
         : ((((i) & 0xF) < 8 && (((i) >> 4) & 1) != 0) ? (i) - 8 : (i)))

/* the scroll step and the offset are ints in the ICO block but their sign is
 * taken through a float comparison (Basic.h's ABSF and SIGNF), which is where
 * the ROM's cvt.s.w pairs come from */

void tex_scrollClut(void *a0, void *a1, void *a2, int a3, int a4, void *a5, int a6, void *a7)
{
    TexColor buf[a4];
    TexExt *e = a5;
    TexColor *dst = a0;
    TexColor *cur = a1;
    TexColor *src = a2;
    int lo;
    int hi;
    int step;
    int rem;
    int span;
    int k;
    int i;
    int j;
    int n;

    if (a3 != 2) {
        return;
    }

    lo = e->file.csBgn;
    hi = e->file.csEnd;
    if (a4 < lo || a4 < hi) {
        debug_StdPrintfDummy(
            "illegal user space data [%s] Clut Scroll (color:%d start:%d end:%d)\n", a7, a4, lo,
            hi);
        return;
    }

    /* A swap of start and end whose last line reads lo where the temporary
     * was meant, so it only clamps start to end (listing rows 1850 to 1854).
     * What the bytes pin: the then-block held two insns when jump.c tried its
     * conditional-move conversion (the ROM keeps bnezl plus the annulled
     * move, not slt plus movn), cse having deleted the no-op `hi = lo`, and
     * the temporary's store is gone by final. What they cannot pin: which
     * local served as the temporary; it must be one read elsewhere, since a
     * fresh one is deleted as trivially dead after cse1 and movn returns. */
    if (hi < lo) {
        i = lo;
        lo = hi;
        hi = lo;
    }

    step = ABSF(e->file.csSpd);
    rem = a6 % step;
    if (rem == 0) {
        span = hi - lo + 1;
        /* listing row 1859 is this one statement: fold pushes the products
         * and the int conversion into the arms of the ABSF and SIGNF
         * conditionals, which is where the ROM's two remainders, the neg.s
         * and times-zero arms and the conversion after the last sign step
         * come from (BgAnimation's rows 2135 to 2137 are the same sign idiom
         * on one line each) */
        k = ABSF(e->file.csStp) % span * SIGNF(e->file.csSpd) * SIGNF(e->file.csStp);

        for (i = lo; i <= hi; i++) {
            cur[CLUT_CSM1(a4, i)] = src[CLUT_CSM1(a4, i)];
        }
        for (i = lo; i <= hi; i++) {
            j = i + k;
            while (j < lo) {
                j += span;
            }
            while (hi < j) {
                j -= span;
            }
            buf[CLUT_CSM1(a4, i)] = src[CLUT_CSM1(a4, j)];
        }
        for (i = lo; i <= hi; i++) {
            src[CLUT_CSM1(a4, i)] = buf[CLUT_CSM1(a4, i)];
        }
    }
    for (i = lo; i <= hi; i++) {
        n = CLUT_CSM1(a4, i);
        if (step == 1) {
            dst[n] = src[n];
        } else {
            int dr = src[n].r - cur[n].r;
            int dg = src[n].g - cur[n].g;
            int db = src[n].b - cur[n].b;
            int da = src[n].a - cur[n].a;
            dst[n].r = cur[n].r + dr * rem / step;
            dst[n].g = cur[n].g + dg * rem / step;
            dst[n].b = cur[n].b + db * rem / step;
            dst[n].a = cur[n].a + da * rem / step;
        }
    }
}

void tex_textureAnimation(void)
{
    int i;

    for (i = 0; i < texCount; i++) {
        CdvdRec *t = &texTable[i].rec;
        TexExt *e = &t->ext;
        TexUV *uv = &t->uv;

        if (e->animated != 0) {
            if (e->file.ampU != 0.0f) {
                uv->uOfs = e->file.ampU *
                           GetTableSin((short)(e->frame * 3.1415927f * e->file.scrlU /
                                               ((60 - systemStatus[0] * 10) / systemStatus[1]) *
                                               10430.378f));
            } else {
                uv->uOfs = uv->uOfs + e->file.scrlU;
                if (0.0f < e->file.scrlU) {
                    if (1.0f < uv->uOfs) {
                        uv->uOfs = uv->uOfs - 2.0f;
                    }
                    if (e->limitOn != 0 && uv->uOfs > e->uLimit) {
                        uv->uOfs = e->uLimit;
                        e->file.scrlU = 0.0f;
                    }
                } else {
                    if (uv->uOfs < -1.0f) {
                        uv->uOfs = uv->uOfs + 2.0f;
                    }
                    if (e->limitOn != 0 && uv->uOfs < e->uLimit) {
                        uv->uOfs = e->uLimit;
                        e->file.scrlU = 0.0f;
                    }
                }
            }

            if (e->file.ampV != 0.0f) {
                uv->vOfs = e->file.ampV *
                           GetTableSin((short)(e->frame * 3.1415927f * e->file.scrlV /
                                               ((60 - systemStatus[0] * 10) / systemStatus[1]) *
                                               10430.378f));
            } else {
                uv->vOfs = uv->vOfs + e->file.scrlV;
                if (0.0f < e->file.scrlV) {
                    if (1.0f < uv->vOfs) {
                        uv->vOfs = uv->vOfs - 2.0f;
                    }
                    if (e->limitOn != 0 && uv->vOfs > e->vLimit) {
                        uv->vOfs = e->vLimit;
                        e->file.scrlV = 0.0f;
                    }
                } else {
                    if (uv->vOfs < -1.0f) {
                        uv->vOfs = uv->vOfs + 2.0f;
                    }
                    if (e->limitOn != 0 && uv->vOfs < e->vLimit) {
                        uv->vOfs = e->vLimit;
                        e->file.scrlV = 0.0f;
                    }
                }
            }

            e->frame++;

            if (e->file.csSpd != 0 && e->file.csStp != 0 && e->file.csBgn != e->file.csEnd) {
                int clut = psmTable[*(unsigned char *)((char *)t + 0x21A) & 0x3F].f4;
                unsigned int n = *(unsigned int *)((char *)t + 0x20C) >> 2;

                tex_scrollClut((char *)t->clut.addr + 0x20, e->clutA, e->clutB, clut, n, e,
                               e->clutFrame, t);
            }
            e->clutFrame++;
        }
    }
}

void tex_SetClutAnimation(int id, int frame)
{
    CdvdRec *t = &texTable[id].rec;
    TexExt *c = &t->ext;

    if (c->animated != 0) {
        int clut = psmTable[*((unsigned char *)t + 0x21A) & 0x3F].f4;
        unsigned int n = (unsigned int)t->clutSize >> 2;

        if (frame != -1) {
            c->clutFrame = frame;
        }
        tex_scrollClut((char *)t->clut.addr + 0x20, c->clutA, c->clutB, clut, n, c,
                       frame == -1 ? 0 : c->clutFrame, t);
    }
}

int tex_FreeTexture(int id)
{
    int i;
    CdvdRec *t = &texTable[id].rec;

    if (texTable[id].rec.ext.used == 0) {
        return -1;
    }
    texTable[id].rec.ext.used = 0;

    if (t->clut.addr != 0) {
        freeseki(t->clut.addr);
    }
    for (i = 0; i < t->levelNum; i++) {
        if (t->lv[i].addr != 0) {
            freeseki(t->lv[i].addr);
        }
    }
    if (t->ext.clutA != 0) {
        freeseki(t->ext.clutA);
    }
    if (t->ext.clutB != 0) {
        freeseki(t->ext.clutB);
    }
    if (t->ext.clutOrg != 0) {
        freeseki(t->ext.clutOrg);
    }
    return 0;
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_ResetVramPri into tex_LockHeadTBP/tex_UnlockHeadTBP, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in resetVramPri, which collapses at layout. */
static inline void resetVramPri(int pri)
{
    int i;

    dl_SetDLPriority(pri);

    if (headTbp[pri] != 0) {
        vramPri[pri].f0 = headTbp[pri];
    } else {
        vramPri[pri].f0 = 0x2800;
    }
    vramPri[pri].f1 = 0x3E80;
    vramPri[pri].f2 = -1;
    for (i = 0; i < texCount; i++) {
        texTable[i].rec.ext.transDone[pri] = 0;
    }
}

/* tex_Init's first-call flag: the table is marked free once, later calls
   recount the loaded entries.  The .sdata word follows the defocus colour
   template and precedes tex_Tool's labels. */
static int texTableReady = 0; /* derived name */

void tex_ResetVram(void)
{
    int i;

    for (i = 0; i < 13; i++) {
        headTbp[i] = 0;
        resetVramPri(i);
    }
    if (systemStatus[5] == 0) {
        tex_textureAnimation();
    }
}

/* the GS register payloads, spelled as ico2/seki/src/GifPacket.c spells them */
#define GIF_RGBA(c)                                                                                \
    ((long long)(c)[0] | ((long long)(c)[1] << 8) | ((long long)(c)[2] << 16) |                    \
     ((long long)(c)[3] << 24))
#define GIF_XY0(x, y, z) ((long long)(x) | ((long long)(y) << 16) | ((z) << 32))
#define GIF_XY(x, y, z)                                                                            \
    ((long long)((x) + 0x8000) | ((long long)((y) + 0x8000) << 16) | ((z) << 32))
/* a 640x224 layout coordinate to the screen, gif_SpriteSensitive's scaling */
#define DISP_X(v) ((v) * ScreenWidth / 640)
#define DISP_Y(v) ((v) * ScreenHeight / 224)

/* The far corner, x + fx with fx = w + 0x8000, the way gif_MakeSpriteNoTexture
 * in GifPacket.c holds it. WHAT THE BYTES PIN: w + 0x8000 is computed on its
 * own and x added to it (`addu v0,v0,s2; addu a3,a3,v0`), where fold turns a
 * textual x + (w + 0x8000) into (x + 0x8000) + w and cse then reuses the near
 * corner's sum; and the trap chain orders the far corner's divisions x, w then
 * y, h. A two-argument helper gives both. WHAT THEY CANNOT PIN: the form of
 * the 2002 construct. The listing gives it no rows of its own (every
 * instruction of the sprite is on 2240 or 2247), which a same-file inline
 * would not do (tex_GetTWTH's rows 513-518 inside tex_setTexReg) and a header
 * inline would not do either (sugiCommon.h and mv_defs.h rows appear inside
 * their callers); GsBase.c's sprite at its line 1026 is the same case and
 * carries the same stand-in. INTERIM, like GsBase.c's gsbSpriteNoTexture. */
static inline int dispFar(int x, int w)
{
    int fx = w + 0x8000;

    return x + fx;
}

/* The untextured sprite of gif_SpriteSensitive (uv NULL, prim 0: PRIM 0x406),
 * expanded as a MACRO: the listing puts all four register writes on the line
 * of the use, and the ROM divides the near corner's x and y a second time for
 * the far corner (six divide-by-zero traps for four divisions), which is the
 * textual substitution of the corner coordinates into both corners. */
#define dispClutSprite(r, col)                                                                     \
    {                                                                                              \
        setGsReg(0x00, 0x406);                                                                     \
        setGsReg(0x01, GIF_RGBA(col));                                                             \
        setGsReg(0x05, GIF_XY(DISP_X((r)[0]), DISP_Y((r)[1]), (long long)-4));                     \
        setGsReg(0x05, GIF_XY0(dispFar(DISP_X((r)[0]), DISP_X((r)[2])),                            \
                               dispFar(DISP_Y((r)[1]), DISP_Y((r)[3])), (long long)-4));           \
    }

/* The CLUT viewer: mode 0 draws a 256-entry CLUT as a 16x16 grid in CSM1
 * order, mode 1 a 16-entry CLUT as one row. Each cell's rectangle is an
 * initialised block-scope array, rows 2238 and 2246 holding the whole
 * declaration: its BLKmode clobber (expr.c store_constructor) makes loop.c's
 * prescan_loop set unknown_address_altered, so the rectangle is neither
 * hoisted out of the loop nor forwarded into the sprite, and both cells share
 * the frame's first sixteen bytes as the ROM's do. The coordinates are pixels
 * scaled to the GS's sixteenths with `<< 4`; written `* 16`, fold would merge
 * k * 5 * 16 into one multiply by 80, which keeps k live and stops loop.c
 * reversing the inner loop, where the shift of k * 5 is a giv of k. */
void tex_dispClut(unsigned char *clut, int mode)
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
 * rebuilds them from the block it just edited. Listing rows 2265-2279, between
 * tex_dispClut and tex_printTexture, inlined only into tex_Tool. */
static inline void toolMakeRegs(CdvdRec *t, int lv)
{
    int aref = 96;
    int afail = 1;
    int zte = 1;
    int ztst = 2;
    int mmag = t->ext.file.smpMag;
    int mmin = t->ext.file.smpMin;
    long long *reg;

    if (t->ext.file.alpTst != 0) {
        aref = t->ext.file.alpTst;
        afail = t->ext.file.alpFai;
    }
    reg = t->pkt.d;
    reg[4] = ((long long)(t->levelNum - lv - 1) << 2) | ((long long)mmag << 5) |
             ((long long)mmin << 6) | ((long long)t->ext.file.mipmapL << 19) |
             ((long long)t->ext.file.mipmapK << 32);
    /* 13 is the alpha test switched on with the GEQUAL function in the two
     * fields below AREF */
    reg[6] = 13 | (long long)aref << 4 | (long long)afail << 12 | (long long)zte << 16 |
             (long long)ztst << 17;
}

/* the shared pad-state array (main.c's PadState): holding the 0x10 button on
 * pad 0 drops alpha blending from the PRIM word. Declared as the array, so the
 * word is reached %hi/%lo as the ROM does, not gp-relative. */

void tex_printTexture(int id)
{
    char *p = texTable[id].rec.name;
    int lv = texTable[id].rec.ext.level;
    float st[4];

    debug_PrintfDummy(ScreenWidth - 160, 195, 0xFF800000, "%8s:SIZE=%3dX%3d",
                      textype[*(unsigned char *)(p + 0x21B)], *(unsigned short *)(p + 0x21C) >> lv,
                      *(unsigned short *)(p + 0x21E) >> lv);

    tex_TransTexture(id, 11);
    gif_StartPacketPri(11);
    {
        float one = 1.0f;
        TexColor col = {128, 128, 128, 128};
        int w = *(unsigned short *)(p + 0x21C) >> lv;
        int h = *(unsigned short *)(p + 0x21E) >> lv;
        int rect[4] = {(304 - w) * 16, -1536, w * 16, h / 2 * 16};

        st[0] = *(float *)(p + 0xB8);
        st[1] = *(float *)(p + 0xBC);
        st[2] = st[0] + one;
        st[3] = st[1] + one;
        FlushCache(0);

        setGsReg(0x49, 0);
        setGsReg(0x42, 0x44);
        setGsReg(0x08, 0);
        setGsReg(0x47, 0x30000);
        setGsReg(0x4E, 0x1300000C0LL);
        *PacketBufferStruct.ptr.d++ = (pad[0].now & 0x10) == 0 ? 0x56 : 0x16;
        *PacketBufferStruct.ptr.d++ = 0x00;
        /* Q is the bits of `one`, read unsigned the way gsb_filmNoise in
         * GsBase.c reads its scale. The ROM pins the unsigned read: cse2 folds
         * its SImode bit copy to the constant (lui at 2321) and `one` dies in
         * $f0 after the ST sums; a signed read keeps `one` live across
         * FlushCache in $f20. */
        *PacketBufferStruct.ptr.d++ = GIF_RGBA(&col.r) | ((long long)*(unsigned int *)&one << 32);
        *PacketBufferStruct.ptr.d++ = 0x01;
        *PacketBufferStruct.ptr.d++ =
            (long long)*(unsigned int *)&st[0] | ((long long)*(int *)&st[1] << 32);
        *PacketBufferStruct.ptr.d++ = 0x02;
        *PacketBufferStruct.ptr.d++ = GIF_XY(DISP_X(rect[0]), DISP_Y(rect[1]), 0x7FFFFFFFLL);
        *PacketBufferStruct.ptr.d++ = 0x05;
        *PacketBufferStruct.ptr.d++ =
            (long long)*(unsigned int *)&st[2] | ((long long)*(int *)&st[3] << 32);
        *PacketBufferStruct.ptr.d++ = 0x02;
        *PacketBufferStruct.ptr.d++ =
            GIF_XY0(dispFar(DISP_X(rect[0]), DISP_X(rect[2])),
                    dispFar(DISP_Y(rect[1]), DISP_Y(rect[3])), 0x7FFFFFFFLL);
        *PacketBufferStruct.ptr.d++ = 0x05;
        setGsReg(0x4E, 0x300000C0);
        setGsReg(0x47, 0x50000);
    }
    gif_EndPacket();
}

/* The texture tool's menu table, one row per tunable. `type` picks how `var`
 * is read back: 0 an int, 1 a float, 2 a short. */
typedef struct TexToolRow {
    char *label;
    float min;
    float max;
    float step;
    int type;
    void *var;
    int _18;
} TexToolRow;

int tex_Tool(int *tno)
{
    TexToolRow m[17] = {
        {"SELTEX", 0.0f, (float)(texCount - 1), 1.0f, 0, tno},
        {"SCRL-U", -1.0f, 1.0f, 1e-05f, 1, &toolExt.scrlU},
        {"SCRL-V", -1.0f, 1.0f, 1e-05f, 1, &toolExt.scrlV},
        {"AMP-U ", -1.0f, 1.0f, 0.01f, 1, &toolExt.ampU},
        {"AMP-V ", -1.0f, 1.0f, 0.01f, 1, &toolExt.ampV},
        {"CS-BGN", 0.0f, 255.0f, 1.0f, 0, &toolExt.csBgn},
        {"CS-END", 0.0f, 255.0f, 1.0f, 0, &toolExt.csEnd},
        {"CS-SPD", -120.0f, 120.0f, 1.0f, 0, &toolExt.csSpd},
        {"CS-STP", -127.0f, 127.0f, 1.0f, 0, &toolExt.csStp},
        {"SHINE ", 0.0f, 3.0f, 1.0f, 0, &toolExt.shine},
        {"SMPMAG", 0.0f, 1.0f, 1.0f, 0, &toolExt.smpMag},
        {"SMPMIN", 0.0f, 5.0f, 1.0f, 0, &toolExt.smpMin},
        {"TEXFNC", 0.0f, 3.0f, 1.0f, 0, &toolExt.texFnc},
        {"ALPTST", 0.0f, 128.0f, 1.0f, 0, &toolExt.alpTst},
        {"ALPFAI", 0.0f, 3.0f, 1.0f, 0, &toolExt.alpFai},
        {"MIPMAPK", -2047.0f, 0.0f, 1.0f, 2, &toolExt.mipmapK},
        {"MIPMAPL", 0.0f, 3.0f, 1.0f, 2, &toolExt.mipmapL},
    };
    /* the step multiplier the shoulder button scales by ten at a time; the
       .sdata word follows the row labels and precedes col's template, so it
       is declared here */
    static int stepScale = 1; /* derived name */
    unsigned int col[2] = {0xFFFFFF00, 0xFFC0C000};

    /* One print per row type. The listing carries their bodies on rows 2370,
     * 2375 and 2380, inside tex_Tool between col (2366) and the counters
     * (2385), in the order int, short, float, while the row loop reaches them
     * as case 0, 1, 2: nested inline helpers. The names are ours. */
    inline void printInt(int i)
    {
        debug_PrintfDummy(10, i * 9 + 46, col[i == toolRow], (int)"%s:%d", (int)m[i].label,
                          *(int *)m[i].var);
    }

    inline void printShort(int i)
    {
        debug_PrintfDummy(10, i * 9 + 46, col[i == toolRow], (int)"%s:%d", (int)m[i].label,
                          *(short *)m[i].var);
    }

    inline void printFloat(int i)
    {
        debug_PrintfDummy(10, i * 9 + 46, col[i == toolRow], (int)"%s:%f", (int)m[i].label,
                          *(float *)m[i].var);
    }

    int cnt = 0;
    int chg = 0;
    int ret = 0;
    int i;
    CdvdRec *rec;

    for (i = 0; i < texCount; i++) {
        if (texTable[i].rec.ext.animated != 0) {
            cnt++;
        }
    }
    if (cnt == 0) {
        return -1;
    }
    tex_printTexture(*tno);
    while (texTable[*tno].rec.ext.animated == 0) {
        *tno = *tno + 1;
        if (texCount - 1 < *tno) {
            *tno = 0;
        }
    }
    rec = &texTable[*tno].rec;
    toolExt = texTable[*tno].rec.ext.file;
    if (rec->clut.vramSize != 0) {
        tex_dispClut((unsigned char *)rec->clut.addr + 0x20, rec->clut.vramSize < 4);
    }
    debug_PrintfDummy(0x90, 0x2E, col[0], "/%d Name:%s x:x%d", cnt, (int)rec, stepScale);
    switch (m[toolRow].type) {
    case 0:
    case 2:
        if (m[toolRow].type == 0) {
            if (pad[0].rep & 0x2000) {
                *(int *)m[toolRow].var =
                    (int)((float)*(int *)m[toolRow].var + m[toolRow].step * stepScale);
                chg = 1;
            } else if (pad[0].rep & 0x8000) {
                *(int *)m[toolRow].var =
                    (int)((float)*(int *)m[toolRow].var - m[toolRow].step * stepScale);
                chg = -1;
            }
            if (m[toolRow].max < (float)*(int *)m[toolRow].var) {
                *(int *)m[toolRow].var = (int)m[toolRow].min;
            }
            if ((float)*(int *)m[toolRow].var < m[toolRow].min) {
                *(int *)m[toolRow].var = (int)m[toolRow].max;
            }
        } else {
            if (pad[0].rep & 0x2000) {
                *(short *)m[toolRow].var =
                    (short)((float)*(short *)m[toolRow].var + m[toolRow].step * stepScale);
                chg = 1;
            } else if (pad[0].rep & 0x8000) {
                *(short *)m[toolRow].var =
                    (short)((float)*(short *)m[toolRow].var - m[toolRow].step * stepScale);
                chg = -1;
            }
            if (m[toolRow].max < (float)*(short *)m[toolRow].var) {
                *(short *)m[toolRow].var = (short)m[toolRow].min;
            }
            if ((float)*(short *)m[toolRow].var < m[toolRow].min) {
                *(short *)m[toolRow].var = (short)m[toolRow].max;
            }
        }
        if (chg != 0) {
            if (toolRow == 0) {
                /* case -1 breaks and case 1 runs off the end into the one
                 * return (listing rows 2440 and 2446): reorg then gives the
                 * second test the return value and the default jump the
                 * epilogue's first load, as the ROM has them. */
                switch (chg) {
                case -1:
                    while (texTable[*tno].rec.ext.animated == 0) {
                        *tno = *tno - 1;
                        if (*tno < 0) {
                            *tno = texCount - 1;
                        }
                    }
                    break;
                case 1:
                    while (texTable[*tno].rec.ext.animated == 0) {
                        *tno = *tno + 1;
                        if (texCount - 1 < *tno) {
                            *tno = 0;
                        }
                    }
                }
                return 0;
            }
            malloc_MemCpy((char *)rec->clut.addr + 0x20, rec->ext.clutOrg, rec->clutSize);
            malloc_MemCpy(rec->ext.clutA, rec->ext.clutOrg, rec->clutSize);
            malloc_MemCpy(rec->ext.clutB, rec->ext.clutOrg, rec->clutSize);
            rec->ext.clutFrame = 0;
        }
        toolMakeRegs(rec, texTable[*tno].rec.ext.level);
        break;
    case 1:
        if (pad[0].rep & 0x2000) {
            *(float *)m[toolRow].var = *(float *)m[toolRow].var + m[toolRow].step * stepScale;
        }
        if (pad[0].rep & 0x8000) {
            *(float *)m[toolRow].var = *(float *)m[toolRow].var - m[toolRow].step * stepScale;
        }
        if (pad[0].rep & 0x10) {
            *(float *)m[toolRow].var = 0.0f;
        }
        if (m[toolRow].max < *(float *)m[toolRow].var) {
            *(float *)m[toolRow].var = m[toolRow].min;
        }
        if (*(float *)m[toolRow].var < m[toolRow].min) {
            *(float *)m[toolRow].var = m[toolRow].max;
        }
        break;
    }
    if (rec->ext.animated != 0) {
        for (i = 0; i < 17; i++) {
            switch (m[i].type) {
            case 0:
                printInt(i);
                break;
            case 1:
                printFloat(i);
                break;
            case 2:
                printShort(i);
                break;
            }
        }
        ret = (pad[0].flags & 0x40) ? -1 : 0;
        if (pad[0].rep & 0x1000) {
            toolRow--;
            stepScale = 1;
        }
        if (pad[0].rep & 0x4000) {
            toolRow++;
            stepScale = 1;
        }
        if (toolRow < 0) {
            toolRow = 16;
        }
        if (16 < toolRow) {
            toolRow = 0;
        }
        if (pad[0].flags & 0x20) {
            stepScale = stepScale * 10;
        }
        if (1000 < stepScale) {
            stepScale = 1;
        }
    } else {
        toolRow = 0;
    }
    if (toolExt.scrlU == 0.0f) {
        rec->uv.uOfs = 0.0f;
    }
    if (toolExt.scrlV == 0.0f) {
        rec->uv.vOfs = 0.0f;
    }
    if (toolExt.ampU == 0.0f && toolExt.ampV == 0.0f) {
        rec->ext.frame = 0;
    }
    texTable[*tno].rec.ext.file = toolExt;
    return ret;
}

/* tex_ListTool's short names: per TIM2 image type, per CLUT type and per
   user-header state */
static char *imageTypeName[] = {"NON", "D16", "D24", "D32", "C-4", "C-8"};

static char *clutTypeName[] = {"--", "16", "24", "32"};

static char *headerName[] = {" ", "\x80"};

/* tex_ListTool's state: whether a row is open in tex_Tool, and the texture
   number tex_Tool edits. */
static int listEditing = 0; /* derived name */

static int listTexNo = 0; /* derived name */

static inline void remakeSampling(CdvdRec *t)
{
    int mmag = 1;
    int mmin = GlobalStageSetting.texSampleMode;

    if (t->ext.animated != 0) {
        mmag = t->ext.file.smpMag;
        mmin = t->ext.file.smpMin;
    }
    t->pkt.d[4] = (t->pkt.d[4] & ~0xE0) | (mmag << 5) | (mmin << 6);
}

int tex_ListTool(void)
{
    int total;
    int sum;
    int i;
    int j;
    int row;
    int top;
    int end;
    int ret = 0;

    if (listEditing != 0) {
        listEditing = tex_Tool(&listTexNo) == 0;
        return 0;
    }
    total = 0;
    tex_printTexture(listTexNo);

    /* "Texture List [%d] PUSH '\x80' TO EDIT US." */
    debug_PrintfDummy(10, 50, 0xFFFFFF00, "Texture List [%d] PUSH '\200' TO EDIT US.", listTexNo);
    debug_PrintfDummy(10, 58, 0xFF800000, "No.              Name   Size MIP IMG CL US");

    for (i = 0; i < texCount; i++) {
        CdvdRec *t = &texTable[i].rec;

        sum = 0;
        for (j = 0; j < t->levelNum; j++) {
            sum += *(unsigned int *)((char *)t + 0x208) >> (j * 2);
        }
        total += sum;
    }

    top = listTexNo > 5 ? listTexNo : 6;
    if (texCount - 7 < top) {
        top = texCount - 7;
    }
    end = top + 7;
    row = 2;

    for (i = top - 6; i < end; i++) {
        CdvdRec *t = &texTable[i].rec;

        sum = 0;
        for (j = 0; j < t->levelNum; j++) {
            sum += *(unsigned int *)((char *)t + 0x208) >> (j * 2);
        }

        if (i == listTexNo) {
            debug_PrintfDummy(10, row * 8 + 50, 0xFF808000, "%03d%18s%7d:%1d/%1d:%s:%s:%s",
                              listTexNo, (int)t, sum, texTable[listTexNo].rec.ext.level + 1,
                              t->levelNum, imageTypeName[*(unsigned char *)((char *)t + 0x21B)],
                              clutTypeName[*(unsigned char *)((char *)t + 0x21A) & 0x3F],
                              headerName[*(int *)((char *)t + 0x2A8)]);
        } else {
            debug_PrintfDummy(10, row * 8 + 50, 0xFFFFFF00, "%03d%18s%7d:%1d/%1d:%s:%s:%s", i,
                              (int)t, sum, texTable[i].rec.ext.level + 1, t->levelNum,
                              imageTypeName[*(unsigned char *)((char *)t + 0x21B)],
                              clutTypeName[*(unsigned char *)((char *)t + 0x21A) & 0x3F],
                              headerName[*(int *)((char *)t + 0x2A8)]);
        }
        row++;
    }

    debug_PrintfDummy(10, row * 8 + 50, 0xFF800000, "   %17s %7d ", "TotalTextureSize", total);

    if ((pad[0].flags & 0x80) != 0) {
        TexEntry *e = &texTable[listTexNo];
        CdvdRec *t = &e->rec;

        if (++e->rec.ext.level >= t->levelNum) {
            e->rec.ext.level = 0;
        }
        remakeSampling(t);
    }

    if ((pad[0].rep & 0x4000) != 0) {
        listTexNo = listTexNo + 1;
        if (texCount - 1 < listTexNo) {
            listTexNo = 0;
        }
    }
    if ((pad[0].rep & 0x1000) != 0) {
        listTexNo = listTexNo - 1;
        if (listTexNo < 0) {
            listTexNo = texCount - 1;
        }
    }
    if ((pad[0].flags & 0x20) != 0) {
        listEditing = 1;
    }
    if ((pad[0].flags & 0x40) != 0) {
        ret = -1;
    }
    if (ret != 0) {
        listTexNo = 0;
    }
    return ret;
}

int tex_GetTWTH(int a0)
{
    int ret = -1;
    int i;
    for (i = 0; i < 11; i++) {
        if ((1 << i) >= a0) {
            ret = i;
            break;
        }
    }
    return ret;
}

int tex_InitTexture(void)
{
    return tex_initTextureSub();
}

int tex_LoadTexture(void *a0)
{
    return tex_LoadTexturePart(a0, 0);
}

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTextureNo into tex_SetUVScroll, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in getTextureNo, which collapses at layout. */
int tex_GetTextureNo(char *name)
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

static inline int getTextureNo(char *name)
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

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTextureData into tex_SetUVScroll, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in getTextureData, which collapses at layout. */
int *tex_GetTextureData(int idx)
{
    return (int *)&texTable[idx].rec;
}

static inline int *getTextureData(int idx)
{
    return (int *)&texTable[idx].rec;
}

int *tex_GetTextureName(int idx)
{
    return (int *)&texTable[idx].rec;
}

void tex_SetSamplingType(int *a0, int a1, int a2)
{
    long long *slot = (long long *)((char *)a0 + 0x78);
    *slot = (*slot & ~(long long)0xE0) | (a1 << 5) | (a2 << 6);
}

int *tex_GetTexExtData(int idx)
{
    return (int *)&texTable[idx].rec.ext;
}

short tex_GetVramFreeAddress(int a0)
{
    return vramPri[a0].f0;
}

void tex_UpdateMipMapLevel(void)
{
    int i;
    for (i = 0; i < texCount; i++) {
        CdvdRec *tex = &texTable[i].rec;
        int mxl = tex->levelNum;
        int k, l;
        int mmag, mmin;
        if (tex->ext.animated != 0) {
            k = tex->ext.file.mipmapK;
            l = tex->ext.file.mipmapL;
            mmag = tex->ext.file.smpMag;
            mmin = tex->ext.file.smpMin;
        } else {
            k = -165;
            l = 0;
            mmag = 1;
            mmin = GlobalStageSetting.texSampleMode;
        }
        tex->pkt.d[4] = ((long long)(mxl - 1) << 2) | ((long long)mmag << 5) |
                        ((long long)mmin << 6) | ((long long)l << 19) | ((long long)k << 32);
    }
}

void tex_LockHeadTBP(int tbp, int pri)
{
    headTbp[pri] = tbp;
    resetVramPri(pri);
}

void tex_UnlockHeadTBP(int pri)
{
    headTbp[pri] = 0;
    resetVramPri(pri);
}

void tex_ResetVramPri(int pri)
{
    int i;

    dl_SetDLPriority(pri);

    if (headTbp[pri] != 0) {
        vramPri[pri].f0 = headTbp[pri];
    } else {
        vramPri[pri].f0 = 0x2800;
    }
    vramPri[pri].f1 = 0x3E80;
    vramPri[pri].f2 = -1;
    for (i = 0; i < texCount; i++) {
        texTable[i].rec.ext.transDone[pri] = 0;
    }
}

int tex_GetTextureNum(void)
{
    return texCount;
}

/* The int flag is the LAST parameter: EABI assigns the same registers either
   way, but a caller (script.c actSubSekizoSe) shows ROM loading it after the
   six floats. */
void tex_SetUVScroll(char *name, float u, float v, float su, float sv, float ou, float ov, int a1)
{
    int no = getTextureNo(name);
    char *tex = (char *)getTextureData(no);
    TexExt *ext = (TexExt *)(tex + 0x268);
    TexUV *uv = (TexUV *)(tex + 0xA8);

    if (ext->animated != 0) {
        ext->file.scrlU = su;
        ext->file.scrlV = sv;
        ext->frame = 0;
        uv->uOfs = u;
        uv->vOfs = v;
        ext->uLimit = ou;
        ext->vLimit = ov;
        ext->limitOn = a1;
    }
}

void tex_Init(void)
{
    int i;

    tex_ResetVram();
    texCount = 0;
    if (texTableReady == 0) {
        for (i = 199; i >= 0; i--) {
            texTable[i].rec.ext.partition = 1;
        }
        texTableReady = 1;
    } else {
        while (texTable[texCount].rec.ext.partition == 0) {
            texCount++;
        }
    }
}

int tex_RemakeRegistersSampleMin(void)
{
    int count = texCount;
    int i;
    for (i = 0; i < count; i++) {
        CdvdRec *b = &texTable[i].rec;
        int f5 = GlobalStageSetting.texSampleMode;
        int f8 = 1;
        if (b->ext.animated != 0) {
            f8 = b->ext.file.smpMag;
            f5 = b->ext.file.smpMin;
        }
        b->pkt.d[4] = (b->pkt.d[4] & ~0xE0) | (f8 << 5) | (f5 << 6);
    }
    return 0;
}
