#include "common.h"
#include "typedef.h"
#include "Basic.h"
#include "Texture.h"
#include "DisplayList.h"
#include <string.h>

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

typedef struct CdvdRec {
    /* the trimmed name tex_GetTextureNo compares against, and behind it the
     * path the texture was loaded from, which tex_initTextureSub keeps so a
     * second read of the same name from a different path can be reported */
    char name[0x18];
    char file[0x60];
    long long x78;
    char pad80[0xD8 - 0x80];
    /* the base of the per-level transfer packets tex_setRegisters allocates */
    char *xD8;
    /* the TIM2 file image the record was built from */
    void *xDC;
    unsigned short xE0;
    char padE2[0xE4 - 0xE2];
    TexLevel clut;
    TexLevel lv[7];
    char pad204[0x290 - 0x204];
    int x290;
    int x294;
    unsigned int x298;
    int x29C;
    int x2A0;
    short x2A4;
    short x2A6;
    int x2A8;
    char pad2AC[0x2BC - 0x2AC];
    /* the three CLUT copies tex_initTextureSub allocates for the scroll */
    void *x2BC;
    void *x2C0;
    void *x2C4;
    /* one byte per display list priority: the slot's transfer-done flag */
    char x2C8[8];
    char pad2D0[0x2D6 - 0x2D0];
    unsigned short x2D6;
    char pad2D8[0x2E8 - 0x2D8];
} CdvdRec;

extern CdvdRec D_0068AFE0[];

typedef struct TexEntry {
    char pad0[8];
    char name[0x78];
    long long x80;
    char pad88[0x2D0 - 0x88];
    char x2D0[0x2D8 - 0x2D0];
    unsigned int pad2D8;
    unsigned char pad2DC;
    unsigned short used : 1;
    unsigned short lv : 15;
    unsigned short pad2DF : 1;
    short x2E0;
    char pad2E2[0x2E8 - 0x2E2];
} TexEntry;

extern int D_0063C164;
extern TexEntry D_0068AFD8[];

typedef struct TexClutEnt {
    int f0;
    int f4;
    int f8;
} TexClutEnt;

extern TexClutEnt D_00290B78[];

/* one VRAM slot per display list priority: the free-address cursor, the top of
 * the region and the texture id the slot last had programmed. */
typedef struct VramPri {
    short f0;
    short f1;
    short f2;
} VramPri;

extern VramPri D_0068AF88[];

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

/* the 0x40-byte block the ICO tools append to the TIM2 header, recognised by
 * its "ICO" magic and copied whole into the first 0x40 bytes of the record's
 * TexExt at 0x268. The two ints at 0x28 and 0x2C are the mag and min filter
 * terms tex_UpdateMipMapLevel reads back as x290 and x294, and the two shorts
 * at 0x3C and 0x3E the terms it reads back as x2A4 and x2A6. */
typedef struct Tim2Ext {
    char magic[4];
    /* the U and V scroll speeds, and behind them the U and V amplitudes the
     * sine animation multiplies its sample by */
    float f04;
    float f08;
    float f0C;
    float f10;
    int x14;
    int x18;
    /* the two enables tex_textureAnimation tests before it scrolls the CLUT */
    int x1C;
    int x20;
    char pad24[0x28 - 0x24];
    int x28;
    int x2C;
    char pad30[0x3C - 0x30];
    short h3C;
    short h3E;
} Tim2Ext;

/* the texture's UV record at 0x A8 of the texture record: the two scroll
 * offsets tex_textureAnimation writes and tex_SetUVScroll seeds. */
typedef struct TexUV {
    char pad0[0x10];
    float f10;
    float f14;
    char pad18[0x30 - 0x18];
} TexUV;

/* the animation record at 0x268 of the texture record. It opens with the
 * 0x40-byte ICO block copied off the TIM2 header and continues with the state
 * the animation keeps between frames. */
typedef struct TexExt {
    Tim2Ext file;
    int x40;
    float f44;
    float f48;
    int x4C;
    unsigned short h50;
    unsigned short h52;
    int x54;
    int x58;
    char pad5C[0x80 - 0x5C];
} TexExt;

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

    if (16000 <= D_0068AF88[dl_GetPri()].f0 + size) {
        tex_ResetVramPri(pri);
    }
    ret = D_0068AF88[dl_GetPri()].f0;
    D_0068AF88[dl_GetPri()].f0 = ret + size;
    return ret;
}

static inline int texAllocClutVram(int size)
{
    int pri = dl_GetPri();
    int ret;

    if (16128 <= D_0068AF88[dl_GetPri()].f1 + size) {
        tex_ResetVramPri(pri);
    }
    ret = D_0068AF88[dl_GetPri()].f1;
    D_0068AF88[dl_GetPri()].f1 = ret + size;
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

/* kept local: this TU's uses of these do not fit the prototypes in GifPacket.h */
extern void gif_StartPacketPri(int pri);
extern void gif_SetGsReg(long long reg, long long val);
extern void gif_EndPacket(void);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void debug_StdPrintfDummy();
/* "src/Texture.c" */
extern char D_00550328[];
/* "0" */
extern char D_0063A1F0[];
/* "tex_loadImage:" + EUC-JP "the texture format cannot be told apart" + ".\n" */
extern char D_005502F0[];
/* "tex_loadImage:" + EUC-JP "the texture size is too large" + ".\n" */
extern char D_00550338[];
/* three qwords: the GIF tag and the A+D write of TEXFLUSH that closes the upload */
extern int D_005502C0[];

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
        debug_StdPrintfDummy(D_005502F0);
        debug_assert(D_00550328, 645);
        __assert(D_00550328, 645, D_0063A1F0);
    }
    if (size > 0x20000) {
        debug_StdPrintfDummy(D_00550338);
        debug_assert(D_00550328, 650);
        __assert(D_00550328, 650, D_0063A1F0);
    }
    gif_StartPacketPri(dl_GetPri());
    gif_SetGsReg(0x50, ((long long)dbp << 32) | ((long long)dbw << 48) | ((long long)dpsm << 56));
    gif_EndPacket();
    dl_OpenDma(2, (int)(tex->xD8 + idx * 80), 5);
    dl_CloseDma();
    dl_OpenDma(2, addr & 0x0FFFFFFF, size + 3);
    dl_CloseDma();
    dl_OpenDma(2, (int)D_005502C0, 3);
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

/* EUC-JP: "a texture type that is neither DIRECT nor CLUT was specified" + ".\n" */
extern char D_00550460[];
extern GifDpk D_004EE6F0;

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
        *D_004EE6F0.ptr++ = (val);                                                                 \
        *D_004EE6F0.ptr++ = (reg);                                                                 \
    }
/* the record carries seven mipmap levels, so a level index is clamped to the
 * last one before it indexes lv[] */
#define TEXLV(n) ((n) < 7 ? (n) : 6)

void tex_setTexReg(Tim2Picture *pic, CdvdRec *t, int levels, int lv, int clut)
{
    unsigned int tfx = 0;

    if (t->x2A8 != 0) {
        tfx = t->x298;
    }
    gif_StartPacketPri(dl_GetPri());
    switch (clut) {
    case 0:
        setGsReg(6, (long long)t->lv[TEXLV(lv)].tbp[dl_GetPri()] |
                        ((long long)t->lv[TEXLV(lv)].dbw << 14) |
                        ((long long)D_00290B78[pic->imageType].f0 << 20) |
                        ((long long)(getTWTH(pic->imageWidth) - lv) << 26) |
                        ((long long)(getTWTH(pic->imageHeight) - lv) << 30) | ((long long)1 << 34) |
                        ((long long)tfx << 35));
        break;
    case 1:
        setGsReg(6, (long long)t->lv[TEXLV(lv)].tbp[dl_GetPri()] |
                        ((long long)t->lv[TEXLV(lv)].dbw << 14) |
                        ((long long)D_00290B78[pic->imageType].f0 << 20) |
                        ((long long)(getTWTH(pic->imageWidth) - lv) << 26) |
                        ((long long)(getTWTH(pic->imageHeight) - lv) << 30) | ((long long)1 << 34) |
                        ((long long)tfx << 35) | ((long long)t->clut.tbp[dl_GetPri()] << 37) |
                        ((long long)D_00290B78[pic->clutType & 0x3F].f0 << 51) |
                        ((long long)2 << 61));
        break;
    default:
        debug_StdPrintfDummy(D_00550460);
        debug_assert(D_00550328, 788);
        __assert(D_00550328, 788, D_0063A1F0);
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
                         D_00290B78[pic->clutType & 0x3F].f0, w, h);
    for (i = lv; i < levels - lv; i++) {
        n = texLoadLevel(t->lv[i].addr, t, i, t->lv[i].tbp[dl_GetPri()], t->lv[i].dbw,
                         D_00290B78[pic->imageType].f0, pic->imageWidth >> i,
                         pic->imageHeight >> i);
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
                         D_00290B78[pic->imageType].f0, pic->imageWidth >> i,
                         pic->imageHeight >> i);
        total += n;
    }
    return total;
}

void tex_transRegister(int a0)
{
    dl_OpenDma(2, a0 + 0x58, 5);
    dl_CloseDma();
}

extern int D_0063B120;
extern int tex_transVramDirectTex(Tim2Picture *pic, CdvdRec *t, int levels, int lv);
extern int tex_transVramClutTex(Tim2Picture *pic, CdvdRec *t, int levels, int lv);
extern void tex_setTexReg(Tim2Picture *pic, CdvdRec *t, int levels, int lv, int clut);
extern void dl_SetDLPriority(int pri);
extern void debug_StdPrintfDummy();
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
/* "tex_transTM2:" + EUC-JP "there are too many mipmap textures" + ".\n" */
extern char D_005504A0[];
/* EUC-JP "the texture is corrupt" + ".\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n" */
extern char D_005504D8[];
/* "src/Texture.c" */
extern char D_00550328[];
/* "FALSE" */
extern char D_0063A1F8[];

int tex_transTM2(Tim2Picture *pic, CdvdRec *t, int id, int pri)
{
    int ret = 0;
    int levels = t->xE0 - D_0068AFD8[id].lv;

    if (8 <= levels) {
        debug_StdPrintfDummy(D_005504A0);
        debug_assert(D_00550328, 886);
        __assert(D_00550328, 886, D_0063A1F8);
    }
    dl_SetDLPriority(pri);
    switch (pic->imageType) {
    case 1:
    case 2:
    case 3:
        if (D_0068AFD8[id].x2D0[pri] == 0) {
            ret = tex_transVramDirectTex(pic, t, levels, D_0068AFD8[id].lv);
        }
        if (D_0068AF88[dl_GetPri()].f2 != id) {
            tex_transRegister(t);
            tex_setTexReg(pic, t, levels, D_0068AFD8[id].lv, 0);
            D_0068AF88[dl_GetPri()].f2 = id;
            D_0063B120++;
        }
        break;
    case 4:
    case 5:
        if (D_0068AFD8[id].x2D0[pri] == 0) {
            ret = tex_transVramClutTex(pic, t, levels, D_0068AFD8[id].lv);
        }
        if (D_0068AF88[dl_GetPri()].f2 != id) {
            tex_transRegister(t);
            tex_setTexReg(pic, t, levels, D_0068AFD8[id].lv, 1);
            D_0068AF88[dl_GetPri()].f2 = id;
            D_0063B120++;
        }
        break;
    default:
        debug_StdPrintfDummy(D_005504D8, t, pic->imageType, pic->clutType, t->lv[0].addr,
                             t->clut.addr, t);
        debug_assert(D_00550328, 919);
        __assert(D_00550328, 919, D_0063A1F8);
        break;
    }
    D_0068AFD8[id].x2D0[pri] = 1;
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

    t->clut.dbw = texTBW(&D_00290B78[pic->clutType & 0x3F], pic->imageWidth);

    for (i = 0; i < t->xE0; i++) {
        t->lv[i].vramSize =
            ((pic->imageWidth >> i) * (pic->imageHeight >> i) / D_00290B78[pic->imageType].f4 / 2) *
                D_00290B78[pic->imageType].f8 >>
            6;

        dbw = texTBW(&D_00290B78[pic->imageType], pic->imageWidth >> i);

        t->lv[i].dbw = dbw;
    }
}

extern int D_0028F804[];

void tex_setRegisters(Tim2Picture *pic, CdvdRec *t)
{
    int *p;
    int *q;
    int i;
    int levels = t->xE0;
    int cw = 0;
    int ch = 0;
    int mmag = 1;
    int mmin = D_0028F804[0];
    int aref = 96;
    int atst = 1;
    int k = -165;
    int l = 0;

    if (t->x2A8 != 0) {
        mmag = t->x290;
        mmin = t->x294;
        if (t->x29C != 0) {
            aref = t->x29C;
            atst = t->x2A0;
        }
        k = t->x2A4;
        l = t->x2A6;
    }

    p = (int *)((char *)t + 0x58);

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

    q = (int *)((char *)t + 0xA8);

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

    t->xD8 = mallocseki((pic->imageType == 4 || pic->imageType == 5 ? levels + 1 : levels) * 80);

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
        debug_StdPrintfDummy(D_005504D8, t, pic->imageType, pic->clutType, t->lv[0].addr,
                             t->clut.addr, t);
        debug_assert(D_00550328, 1066);
        __assert(D_00550328, 1066, D_0063A1F8);
    }

    /* listing row 1069 is a second switch on the same field: the case range
     * 4..5 is what lowers to the ROM's signed slti 6 and slti 4 pair, and gcse
     * shares the field's load with the switch above, reloading it only after
     * the default arm's calls. */
    switch (pic->imageType) {
    case 4:
    case 5:
        *(int *)(t->xD8 + levels * 80) = 0;
        *(int *)(t->xD8 + levels * 80 + 4) = 0;
        *(int *)(t->xD8 + levels * 80 + 8) = 0x13000000;
        *(int *)(t->xD8 + levels * 80 + 12) = 0x50000005;

        *(long long *)(t->xD8 + levels * 80 + 16) = 0x1000000000008004LL;
        *(long long *)(t->xD8 + levels * 80 + 24) = 14;

        *(long long *)(t->xD8 + levels * 80 + 32) = 0;
        *(long long *)(t->xD8 + levels * 80 + 40) = 81;
        *(long long *)(t->xD8 + levels * 80 + 48) = cw | ((long long)ch << 32);
        *(long long *)(t->xD8 + levels * 80 + 56) = 82;

        *(long long *)(t->xD8 + levels * 80 + 64) = 0;
        *(long long *)(t->xD8 + levels * 80 + 72) = 83;
        break;
    }

    for (i = 0; i < levels; i++) {
        *(int *)(t->xD8 + i * 80) = 0;
        *(int *)(t->xD8 + i * 80 + 4) = 0;
        *(int *)(t->xD8 + i * 80 + 8) = 0x13000000;
        *(int *)(t->xD8 + i * 80 + 12) = 0x50000005;

        *(long long *)(t->xD8 + i * 80 + 16) = 0x1000000000008004LL;
        *(long long *)(t->xD8 + i * 80 + 24) = 14;

        *(long long *)(t->xD8 + i * 80 + 32) = 0;
        *(long long *)(t->xD8 + i * 80 + 40) = 81;
        *(long long *)(t->xD8 + i * 80 + 48) =
            (pic->imageWidth >> i) | ((long long)(pic->imageHeight >> i) << 32);
        *(long long *)(t->xD8 + i * 80 + 56) = 82;

        *(long long *)(t->xD8 + i * 80 + 64) = 0;
        *(long long *)(t->xD8 + i * 80 + 72) = 83;
    }
}

/* listing rows 970-979: the second file-static helper, inlined here only. It
 * fills in one VRAM size and one buffer width per mipmap level. */
static inline void texInitMipLevels(Tim2Picture *pic, CdvdRec *t)
{
    int i;
    int dbw;

    for (i = 0; i < t->xE0; i++) {
        t->lv[i].vramSize =
            ((pic->imageWidth >> i) * (pic->imageHeight >> i) / D_00290B78[pic->imageType].f4) *
                D_00290B78[pic->imageType].f8 >>
            6;

        dbw = texTBW(&D_00290B78[pic->imageType], pic->imageWidth >> i);

        t->lv[i].dbw = dbw;
    }
}

extern void tex_setRegisters(Tim2Picture *pic, CdvdRec *t);
extern void debug_StdPrintfDummy();
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
/* EUC-JP "the texture is corrupt" + ".\"%s\"I:%d C:%d iadr:%p cadr:%p hadr:%p\n" */
extern char D_005504D8[];
/* "src/Texture.c" */
extern char D_00550328[];
/* "FALSE" */
extern char D_0063A1F8[];

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
        debug_StdPrintfDummy(D_005504D8, t, pic->imageType, pic->clutType, t->lv[0].addr,
                             t->clut.addr, t);
        debug_assert(D_00550328, 1143);
        __assert(D_00550328, 1143, D_0063A1F8);
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

extern void sceGsSyncPath(int mode, int timeout);
/* dpsm is short here for the reason the repo's sceGsSetDefDispEnv declaration
 * carries: the ROM reads D_00290B78's first word with lh at this call site and
 * with lw five instructions later, so the argument is a 16-bit conversion of an
 * int field, which is what a short parameter spells. */
extern void sceGsSetDefLoadImage(sceGsLoadImage *img, int dbp, int dbw, short dpsm, int dsax,
                                 int dsay, int rrw, int rrh);
extern void sceGsSetDefStoreImage(sceGsStoreImage *img, int sbp, int sbw, int spsm, int ssax,
                                  int ssay, int rrw, int rrh);
extern int sceGsExecLoadImage(sceGsLoadImage *img, void *src);
extern int sceGsExecStoreImage(sceGsStoreImage *img, void *dst);
extern void FlushCache(int mode);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
/* "src/Texture.c" */
extern char D_00550328[];
/* "FALSE" */
extern char D_0063A1F8[];

void tex_convertImage(void *dst, void *src, short fmt, short w, short h)
{
    sceGsLoadImage limg;
    sceGsStoreImage simg;
    int w2 = w;

    sceGsSyncPath(0, 0);
    sceGsSetDefLoadImage(&limg, 0x2800, w >> 6, D_00290B78[fmt].f0, 0, 0, w2, h);
    FlushCache(0);
    if (sceGsExecLoadImage(&limg, src)) {
        debug_assert(D_00550328, 1246);
        __assert(D_00550328, 1246, D_0063A1F8);
    }
    sceGsSyncPath(0, 0);
    switch (D_00290B78[fmt].f0) {
    case 19:
        w2 = w >> 2;
        break;
    case 20:
        w2 = w >> 3;
        break;
    default:
        debug_assert(D_00550328, 1251);
        __assert(D_00550328, 1251, D_0063A1F8);
        break;
    }
    if (32767 < w * h >> 4) {
        debug_assert(D_00550328, 1254);
        __assert(D_00550328, 1254, D_0063A1F8);
    }
    sceGsSetDefStoreImage(&simg, 0x2800, w2 >> 6, 0, 0, 0, w2, h);
    FlushCache(0);
    if (sceGsExecStoreImage(&simg, dst)) {
        debug_assert(D_00550328, 1259);
        __assert(D_00550328, 1259, D_0063A1F8);
    }
    sceGsSyncPath(0, 0);
}

extern void malloc_MemCpy(void *dst, void *src, int n);
extern void tex_convertImage(void *dst, void *src, short fmt, short w, short h);

void tex_makeCopyImage(Tim2Picture *pic, CdvdRec *t, char *src, int convert)
{
    Tim2Mipmap *mip = (Tim2Mipmap *)(pic + 1);
    int i;
    int *p;
    int *q;
    int n;

    if (t->xE0 == 1) {
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
        for (i = 0; i < t->xE0; i++) {
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

extern int mipmap_header_size[];
extern int sprintf(char *buf, const char *fmt, ...);
extern void debug_DispQW(void *p, int n);
extern void debug_StdPrintfDummy();
extern void debug_assert(char *file, int line);
extern void debug_assertMessage(char *file, int line, char *msg);
extern void __assert(char *file, int line, char *expr);
/* "ICO" */
extern char D_0063A200[];
/* "e" */
extern char D_0063A208[];
/* "src/Texture.c" */
extern char D_00550328[];
/* "0" */
extern char D_0063A1F0[];
/* "tex_makeTexturePacket:" + EUC-JP "the texture user header is an unknown
 * format" + ".'%s'\n" */
extern char D_005507F0[];
/* "TEXTURE BROKEN. \"%s\"\n    I:%d C:%d iadr:%p cadr:%p hadr:%p\n" */
extern char D_00550840[];

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

    t->xDC = file;
    t->xE0 = pic->mipMapTextures;
    t->clut.addr = 0;

    for (i = 0; i < 7; i++) {
        t->lv[i].addr = 0;
    }

    *(Tim2Picture *)((char *)t + 0x208) = *pic;
    if (2 <= pic->mipMapTextures) {
        *(Tim2Mipmap *)((char *)t + 0x238) = *mip;
    }

    if (strcmp(ext->magic, D_0063A200) == 0 &&
        pic->headerSize != mipmap_header_size[pic->mipMapTextures] + 48) {
        if (mipmap_header_size[pic->mipMapTextures] + 48 != pic->headerSize - 64) {
            debug_StdPrintfDummy(D_005507F0, t);
            debug_assert(D_00550328, 1392);
            __assert(D_00550328, 1392, D_0063A1F0);
        }
        *(Tim2Ext *)((char *)t + 0x268) = *ext;
        t->x2A8 = 1;
    } else {
        t->x2A8 = 0;
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
        sprintf(buf, D_00550840, t, pic->imageType, pic->clutType, t->lv[0].addr, t->clut.addr, t);
        debug_StdPrintfDummy(buf);
        debug_assertMessage(D_00550328, 1427, buf);
        __assert(D_00550328, 1427, D_0063A208);
        break;
    }
}

extern int sprintf(char *buf, const char *fmt, ...);
/* "%s" */
extern char D_0063A210[];

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
    sprintf(tmp, D_0063A210, &name[k]);
    sprintf(name, D_0063A210, tmp);
    for (i = 0; name[i] != 0; i++) {
        if (name[i] == '.') {
            name[i] = 0;
            break;
        }
    }
}

extern int tex_GetTextureNo(char *name);
extern void tex_makeTexturePacket(void *pkt, CdvdRec *t);
extern int malloc_GetPartition(void);
extern int D_0063C164;
/* "\x1b[31m" + EUC-JP "a texture of the same name was read from another path" + ".\n" */
extern char D_00550880[];
/* "2:%s\x1b[0m\n" */
extern char D_005508B8[];
/* EUC-JP "there are too many textures, make the texture list region bigger" */
extern char D_005508C8[];
/* "1:%s\n" */
extern char D_0063A218[];

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

    sprintf(buf, D_0063A210, name);
    texTrimName(buf);

    no = tex_GetTextureNo(buf);
    if (no != -1) {
        if (strcmp(name, D_0068AFE0[no].file) != 0) {
            debug_StdPrintfDummy(D_00550880);
            debug_StdPrintfDummy(D_0063A218, name);
            debug_StdPrintfDummy(D_005508B8, D_0068AFE0[no].file);
        }
        return -1;
    }

    t = &D_0068AFE0[D_0063C164];
    ((TexEntry *)((char *)D_0068AFE0 - 8))[D_0063C164].lv = 0;
    D_0068AFE0[D_0063C164].x2C8[pri] = 0;

    sprintf(t->file, D_0063A210, name);
    sprintf(t->name, D_0063A210, buf);
    tex_makeTexturePacket(pkt, t);
    tex_initTM2((Tim2Picture *)((char *)t + 0x208), t);
    no = D_0063C164;

    *(int *)((char *)t + 0x2AC) = 0;
    *(int *)((char *)t + 0x2B0) = 0;
    *(int *)((char *)t + 0x2B4) = 0;
    *(short *)((char *)t + 0x2B8) = 0;
    *(short *)((char *)t + 0x2BA) = 0;
    if (*(int *)((char *)t + 0x2A8) != 0) {
        *(int *)((char *)t + 0x2BC) = mallocseki(*(int *)((char *)t + 0x20C));

        *(int *)((char *)t + 0x2C0) = mallocseki(*(int *)((char *)t + 0x20C));

        *(int *)((char *)t + 0x2C4) = mallocseki(*(int *)((char *)t + 0x20C));

        malloc_MemCpy(*(void **)((char *)t + 0x2BC), *(char **)((char *)t + 0xE4) + 0x20,
                      *(int *)((char *)t + 0x20C));

        malloc_MemCpy(*(void **)((char *)t + 0x2C0), *(char **)((char *)t + 0xE4) + 0x20,
                      *(int *)((char *)t + 0x20C));

        malloc_MemCpy(*(void **)((char *)t + 0x2C4), *(char **)((char *)t + 0xE4) + 0x20,
                      *(int *)((char *)t + 0x20C));
    } else {
        *(int *)((char *)t + 0x2BC) = 0;
        *(int *)((char *)t + 0x2C0) = 0;
        *(int *)((char *)t + 0x2C4) = 0;
    }
    D_0068AFD8[D_0063C164].used = 1;

    D_0068AFD8[D_0063C164].x2E0 = malloc_GetPartition();
    D_0063C164++;
    if (200 <= D_0063C164) {
        debug_StdPrintfDummy(D_005508C8);
        debug_assert(D_00550328, 1523);
        __assert(D_00550328, 1523, D_0063A1F0);
    }
    return no;
}

extern int file_LoadFile(int *size, char *name, int a2);
extern int sprintf(char *buf, const char *fmt, ...);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void debug_StdPrintfDummy();
/* "%s" */
extern char D_0063A210[];
/* "%s.tm2" */
extern char D_0063A220[];
/* EUC-JP: texture "%s" not found. */
extern char D_00550908[];
/* "src/Texture.c" */
extern char D_00550328[];
/* "FALSE" */
extern char D_0063A1F8[];

int tex_LoadTexturePart(void *name, int a1)
{
    char buf[272];
    int size = 0;

    sprintf(buf, D_0063A220, name);
    if (file_LoadFile(&size, buf, a1) >= 0) {
        texTrimName(buf);
        return tex_initTextureSub(buf, size);
    } else {
        debug_StdPrintfDummy(D_00550908, buf);
        debug_assert(D_00550328, 1590);
        __assert(D_00550328, 1590, D_0063A1F8);
        return -1;
    }
}

extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void debug_StdPrintfDummy();
/* "tex_TransTexture:INVALID TEXTURE ID. %d/%d\n" */
extern char D_00550930[];
/* "tex_TransTexture:" + EUC-JP "texture transfer failed" + ". %d\n" */
extern char D_00550960[];
/* the same message with ". %d:%s\n" */
extern char D_00550998[];
/* "src/Texture.c" */
extern char D_00550328[];
/* "FALSE" */
extern char D_0063A1F8[];
extern int D_0063B11C;

int tex_TransTexture(int id, int ret)
{
    CdvdRec *t = &D_0068AFE0[id];

    if (id < 0 || D_0063C164 <= id) {
        debug_Assert(D_00550930, id, D_0063C164);
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
            debug_StdPrintfDummy(D_00550960, id);
        } else {
            debug_StdPrintfDummy(D_00550998, id, t);
        }
        debug_assert(D_00550328, 1685);
        __assert(D_00550328, 1685, D_0063A1F8);
    }
    if (ret != 0) {
        D_0063B11C++;
    }
    dl_OpenDma(2, (int)((char *)t + 0xA8), 3);
    dl_CloseDma();
    return ret;
}

/* the same stand-in for tex_GetTextureData, whose body the listing inlines
 * here at row 1642. */
static inline int *getTextureDataDefocus(int idx)
{
    return (int *)((char *)D_0068AFE0 + idx * 0x2E8);
}

typedef struct TexColor {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} TexColor;

/* the four bytes 0x80 0x80 0x80 0x80 */
extern TexColor D_0063A228[];
extern int D_0063A064;
extern int D_0063A068;
extern void gif_StartPacketPri(int pri);
extern void gif_SetGsReg(long long reg, long long val);
extern void gif_EndPacket(void);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SetDrawEnviroment(unsigned long long fbp, unsigned long long psm, unsigned int w,
                                  unsigned int h, int useoffset, int clear);
/* kept local: this TU's one use passes the depth as a 32-bit 0xFFFFFFFF, which
 * the ROM materialises with a bare lui/ori and hands over unextended, so the
 * parameter is 32 bits here and not the long long GifPacket.h carries. */
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
        TexColor col = D_0063A228[0];
        gif_SetZTest(0);
        gif_SetZWrite(0);
        gif_SetDrawEnviroment(tbp, 0, w, h, 0, 0);
        gif_SpriteSensitiveOrg(rect, 0xFFFFFFFF, uv, (unsigned char *)&col, 0);
        gif_SetZWrite(1);
        gif_SetZTest(1);

        gif_SetGsReg(6, tbp | ((long long)(w < 64 ? 1 : w / 64) << 14) |
                            ((long long)getTWTH(w) << 26) | ((long long)getTWTH(h) << 30) |
                            ((long long)1 << 34));
        gif_SetDrawEnviroment(2048, 0, D_0063A064, D_0063A068, 1, 0);
        gif_EndPacket();
    }
}

/* "illegal user space data [%s] Clut Scroll (color:%d start:%d end:%d)\n" */
extern char D_005509D0[];

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

void tex_scrollClut(int a0, int a1, int a2, int a3, int a4, void *a5, int a6, void *a7)
{
    TexColor buf[a4];
    TexExt *e = (TexExt *)a5;
    TexColor *dst = (TexColor *)a0;
    TexColor *cur = (TexColor *)a1;
    TexColor *src = (TexColor *)a2;
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

    lo = e->file.x14;
    hi = e->file.x18;
    if (a4 < lo || a4 < hi) {
        debug_StdPrintfDummy(D_005509D0, a7, a4, lo, hi);
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

    step = ABSF(e->file.x1C);
    rem = a6 % step;
    if (rem == 0) {
        span = hi - lo + 1;
        /* listing row 1859 is this one statement: fold pushes the products
         * and the int conversion into the arms of the ABSF and SIGNF
         * conditionals, which is where the ROM's two remainders, the neg.s
         * and times-zero arms and the conversion after the last sign step
         * come from (BgAnimation's rows 2135 to 2137 are the same sign idiom
         * on one line each) */
        k = ABSF(e->file.x20) % span * SIGNF(e->file.x1C) * SIGNF(e->file.x20);

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

extern int D_0028F4C0[];
extern float GetTableSin(short angle);

void tex_textureAnimation(void)
{
    int i;

    for (i = 0; i < D_0063C164; i++) {
        CdvdRec *t = &D_0068AFE0[i];
        TexExt *e = (TexExt *)((char *)t + 0x268);
        TexUV *uv = (TexUV *)((char *)t + 0xA8);

        if (e->x40 != 0) {
            if (e->file.f0C != 0.0f) {
                uv->f10 =
                    e->file.f0C *
                    GetTableSin((short)(e->h50 * 3.1415927f * e->file.f04 /
                                        ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10430.378f));
            } else {
                uv->f10 = uv->f10 + e->file.f04;
                if (0.0f < e->file.f04) {
                    if (1.0f < uv->f10) {
                        uv->f10 = uv->f10 - 2.0f;
                    }
                    if (e->x4C != 0 && uv->f10 > e->f44) {
                        uv->f10 = e->f44;
                        e->file.f04 = 0.0f;
                    }
                } else {
                    if (uv->f10 < -1.0f) {
                        uv->f10 = uv->f10 + 2.0f;
                    }
                    if (e->x4C != 0 && uv->f10 < e->f44) {
                        uv->f10 = e->f44;
                        e->file.f04 = 0.0f;
                    }
                }
            }

            if (e->file.f10 != 0.0f) {
                uv->f14 =
                    e->file.f10 *
                    GetTableSin((short)(e->h50 * 3.1415927f * e->file.f08 /
                                        ((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * 10430.378f));
            } else {
                uv->f14 = uv->f14 + e->file.f08;
                if (0.0f < e->file.f08) {
                    if (1.0f < uv->f14) {
                        uv->f14 = uv->f14 - 2.0f;
                    }
                    if (e->x4C != 0 && uv->f14 > e->f48) {
                        uv->f14 = e->f48;
                        e->file.f08 = 0.0f;
                    }
                } else {
                    if (uv->f14 < -1.0f) {
                        uv->f14 = uv->f14 + 2.0f;
                    }
                    if (e->x4C != 0 && uv->f14 < e->f48) {
                        uv->f14 = e->f48;
                        e->file.f08 = 0.0f;
                    }
                }
            }

            e->h50++;

            if (e->file.x1C != 0 && e->file.x20 != 0 && e->file.x14 != e->file.x18) {
                int clut = D_00290B78[*(unsigned char *)((char *)t + 0x21A) & 0x3F].f4;
                unsigned int n = *(unsigned int *)((char *)t + 0x20C) >> 2;

                tex_scrollClut((int)t->clut.addr + 0x20, e->x54, e->x58, clut, n, e, e->h52, t);
            }
            e->h52++;
        }
    }
}

void tex_SetClutAnimation(int id, int frame)
{
    char *t = (char *)&D_0068AFE0[id];
    char *c = t + 0x268;

    if (*(int *)(c + 0x40) != 0) {
        int clut = D_00290B78[*(unsigned char *)(t + 0x21A) & 0x3F].f4;
        unsigned int n = *(unsigned int *)(t + 0x20C) >> 2;

        if (frame != -1) {
            *(short *)(c + 0x52) = frame;
        }
        tex_scrollClut(*(int *)(t + 0xE4) + 0x20, *(int *)(c + 0x54), *(int *)(c + 0x58), clut, n,
                       c, frame == -1 ? 0 : *(unsigned short *)(c + 0x52), t);
    }
}

extern int freeseki(void *p);

int tex_FreeTexture(int id)
{
    int i;
    CdvdRec *t = (CdvdRec *)D_0068AFD8[id].name;

    if (D_0068AFD8[id].used == 0) {
        return -1;
    }
    D_0068AFD8[id].used = 0;

    if (t->clut.addr != 0) {
        freeseki(t->clut.addr);
    }
    for (i = 0; i < t->xE0; i++) {
        if (t->lv[i].addr != 0) {
            freeseki(t->lv[i].addr);
        }
    }
    if (t->x2BC != 0) {
        freeseki(t->x2BC);
    }
    if (t->x2C0 != 0) {
        freeseki(t->x2C0);
    }
    if (t->x2C4 != 0) {
        freeseki(t->x2C4);
    }
    return 0;
}

extern int D_006AF518[];

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_ResetVramPri into tex_LockHeadTBP/tex_UnlockHeadTBP, so it is a public `inline` of the
 * deferred tail; until tex_Init, which sits between the tail's members, is C,
 * the copy is emitted here as a plain function at its ROM position and the
 * caller inlines the static stand-in resetVramPri, which collapses at layout. */
static inline void resetVramPri(int pri)
{
    int i;

    dl_SetDLPriority(pri);

    if (D_006AF518[pri] != 0) {
        D_0068AF88[pri].f0 = D_006AF518[pri];
    } else {
        D_0068AF88[pri].f0 = 0x2800;
    }
    D_0068AF88[pri].f1 = 0x3E80;
    D_0068AF88[pri].f2 = -1;
    for (i = 0; i < D_0063C164; i++) {
        D_0068AFD8[i].x2D0[pri] = 0;
    }
}

extern int D_0028F4C0[];
extern void tex_textureAnimation(void);

void tex_ResetVram(void)
{
    int i;

    for (i = 0; i < 13; i++) {
        D_006AF518[i] = 0;
        resetVramPri(i);
    }
    if (D_0028F4C0[5] == 0) {
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
#define DISP_X(v) ((v) * D_0063A064 / 640)
#define DISP_Y(v) ((v) * D_0063A068 / 224)

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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_printTexture);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_Tool);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_ListTool);

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

    for (i = 0; i < D_0063C164; i++) {
        if (D_0068AFD8[i].used) {
            if (strcmp(name, D_0068AFD8[i].name) == 0) {
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

    for (i = 0; i < D_0063C164; i++) {
        if (D_0068AFD8[i].used) {
            if (strcmp(name, D_0068AFD8[i].name) == 0) {
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
    return (int *)((char *)D_0068AFE0 + idx * 0x2E8);
}

static inline int *getTextureData(int idx)
{
    return (int *)((char *)D_0068AFE0 + idx * 0x2E8);
}

int *tex_GetTextureName(int idx)
{
    return (int *)((char *)D_0068AFE0 + idx * 0x2E8);
}

void tex_SetSamplingType(int *a0, int a1, int a2)
{
    long long *slot = (long long *)((char *)a0 + 0x78);
    *slot = (*slot & ~(long long)0xE0) | (a1 << 5) | (a2 << 6);
}

extern int D_0068B248[];

int *tex_GetTexExtData(int idx)
{
    return (int *)((char *)D_0068B248 + idx * 0x2E8);
}

short tex_GetVramFreeAddress(int a0)
{
    return D_0068AF88[a0].f0;
}

void tex_UpdateMipMapLevel(void)
{
    int i;
    for (i = 0; i < D_0063C164; i++) {
        CdvdRec *tex = &D_0068AFE0[i];
        int mxl = tex->xE0;
        int k, l;
        int mmag, mmin;
        if (tex->x2A8 != 0) {
            k = tex->x2A4;
            l = tex->x2A6;
            mmag = tex->x290;
            mmin = tex->x294;
        } else {
            k = -165;
            l = 0;
            mmag = 1;
            mmin = D_0028F804[0];
        }
        tex->x78 = ((long long)(mxl - 1) << 2) | ((long long)mmag << 5) | ((long long)mmin << 6) |
                   ((long long)l << 19) | ((long long)k << 32);
    }
}

void tex_LockHeadTBP(int tbp, int pri)
{
    D_006AF518[pri] = tbp;
    resetVramPri(pri);
}

void tex_UnlockHeadTBP(int pri)
{
    D_006AF518[pri] = 0;
    resetVramPri(pri);
}

void tex_ResetVramPri(int pri)
{
    int i;

    dl_SetDLPriority(pri);

    if (D_006AF518[pri] != 0) {
        D_0068AF88[pri].f0 = D_006AF518[pri];
    } else {
        D_0068AF88[pri].f0 = 0x2800;
    }
    D_0068AF88[pri].f1 = 0x3E80;
    D_0068AF88[pri].f2 = -1;
    for (i = 0; i < D_0063C164; i++) {
        D_0068AFD8[i].x2D0[pri] = 0;
    }
}

int tex_GetTextureNum(void)
{
    return D_0063C164;
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

    if (ext->x40 != 0) {
        ext->file.f04 = su;
        ext->file.f08 = sv;
        ext->h50 = 0;
        uv->f10 = u;
        uv->f14 = v;
        ext->f44 = ou;
        ext->f48 = ov;
        ext->x4C = a1;
    }
}

extern int D_0063A22C;
extern void tex_ResetVram(void);

void tex_Init(void)
{
    int i;

    tex_ResetVram();
    D_0063C164 = 0;
    if (D_0063A22C == 0) {
        for (i = 199; i >= 0; i--) {
            D_0068AFD8[i].x2E0 = 1;
        }
        D_0063A22C = 1;
    } else {
        while (D_0068AFD8[D_0063C164].x2E0 == 0) {
            D_0063C164++;
        }
    }
}

extern int D_0028F720[];

int tex_RemakeRegistersSampleMin(void)
{
    int count = D_0063C164;
    int i;
    for (i = 0; i < count; i++) {
        CdvdRec *b = &D_0068AFE0[i];
        int f5 = D_0028F720[57];
        int f8 = 1;
        if (b->x2A8 != 0) {
            f8 = b->x290;
            f5 = b->x294;
        }
        b->x78 = (b->x78 & ~0xE0) | (f8 << 5) | (f5 << 6);
    }
    return 0;
}
