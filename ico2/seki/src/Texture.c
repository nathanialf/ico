#include "common.h"
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
    int addr;
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
    char pad80[0xE0 - 0x80];
    unsigned short xE0;
    char padE2[0xE4 - 0xE2];
    TexLevel clut;
    TexLevel lv[7];
    char pad204[0x290 - 0x204];
    int x290;
    int x294;
    char pad298[0x2A4 - 0x298];
    short x2A4;
    short x2A6;
    int x2A8;
    char pad2AC[0x2C8 - 0x2AC];
    /* one byte per display list priority: the slot's transfer-done flag */
    char x2C8[8];
    char pad2D0[0x2E8 - 0x2D0];
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
    /* the mipmap header that follows the picture header when there is more
     * than one level: two MIPTBP registers and then one image size per level,
     * which is the array at 0x40 tex_makeCopyImage walks. */
    unsigned long long GsMiptbp1;
    unsigned long long GsMiptbp2;
    unsigned int sizes[8];
} Tim2Picture;

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_AllocVramAuto);

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
    dl_OpenDma(2, *(int *)((char *)tex + 0xD8) + idx * 0x50, 5);
    dl_CloseDma();
    dl_OpenDma(2, addr & 0x0FFFFFFF, size + 3);
    dl_CloseDma();
    dl_OpenDma(2, (int)D_005502C0, 3);
    dl_CloseDma();
    return size << 4;
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_setTexReg);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_transVramClutTex);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_transVramDirectTex);

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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_setRegisters);

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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_convertClutCSM2ToCSM1);

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

extern int mallocseki(int size);
extern void malloc_MemCpy(void *dst, void *src, int n);
extern void tex_convertImage(void *dst, void *src, short fmt, short w, short h);

void tex_makeCopyImage(Tim2Picture *pic, CdvdRec *t, char *src, int convert)
{
    int i;
    int *p;
    int *q;
    int n;

    if (t->xE0 == 1) {
        t->lv[0].addr = mallocseki(pic->imageSize + 48);

        if (convert && 256 <= pic->imageWidth) {
            tex_convertImage((void *)(t->lv[0].addr + 32), src, pic->imageType, pic->imageWidth,
                             pic->imageHeight);
        } else {
            malloc_MemCpy((void *)(t->lv[0].addr + 32), src, pic->imageSize);
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
            t->lv[i].addr = mallocseki(pic->sizes[i] + 48);

            if (convert && 256 <= (pic->imageWidth >> i)) {
                tex_convertImage((void *)(t->lv[i].addr + 32), src, pic->imageType,
                                 pic->imageWidth >> i, pic->imageHeight >> i);
            } else {
                malloc_MemCpy((void *)(t->lv[i].addr + 32), src, pic->sizes[i]);
            }

            p = (int *)t->lv[i].addr;
            n = pic->sizes[i] >> 4;
            p[0] = 0;
            p[1] = 0;
            p[2] = 0x13000000;
            p[3] = (n + 1) | 0x50000000;
            *(long long *)(p + 4) = (n | 0x8000) | ((long long)0x8000 << 44);
            *(long long *)(p + 6) = 0;
            src += pic->sizes[i];
            q = (int *)((char *)p + (pic->sizes[i] + 32));
            *q++ = 0;
            *q++ = 0;

            *q++ = 0;
            *q++ = 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_makeTexturePacket);

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

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * tex_GetTWTH here and in tex_setTexReg, so it is a public `inline` of the
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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_scrollClut);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_textureAnimation);

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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_FreeTexture);

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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Texture", tex_dispClut);
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

extern int D_0028F804[];

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

typedef struct TexUV {
    char pad0[0x10];
    float f10;
    float f14;
    char pad18[0x18];
} TexUV;

typedef struct TexExt {
    char pad0[4];
    float f04;
    float f08;
    char pad0C[0x40 - 0x0C];
    int x40;
    float f44;
    float f48;
    int x4C;
    short h50;
    char pad52[0x80 - 0x52];
} TexExt;

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
        ext->f04 = su;
        ext->f08 = sv;
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
