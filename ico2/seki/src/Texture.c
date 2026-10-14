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
     * second read of the same name from a different path can be reported */
    char name[24];
    char file[64];
    TexPkt pkt; /* 0x58 */
    TexUV uv;   /* 0xA8 */
    /* the base of the per-level transfer packets tex_setRegisters allocates */
    TexLevelPkt *levelPkt;
    /* the TIM2 file image the record was built from */
    void *tim2;
    unsigned short levelNum; /* the mipmap level count */
    char padE2[2];
    TexLevel clut;
    TexLevel lv[7];
    char pad204[4];
    /* the TIM2 picture and mipmap headers tex_makeTexturePacket copies in;
     * tex_Tool rebuilds the three CLUT copies from the picture's clutSize */
    Tim2Picture pic; /* 0x208 */
    Tim2Mipmap mip;  /* 0x238 */
    /* the animation record, opening with the 0x40-byte ICO block copied
     * whole from the TIM2 header */
    TexExt ext;
};

/* one texture slot, 0x2E8 bytes: eight bytes the record follows. The code
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

/* the VRAM slot per display list priority, the 200 texture slots, and the
 * working copy of the selected texture's ICO block tex_Tool edits */
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

/* three qwords: a VIF DIRECT of two, the GIF A+D tag and the TEXFLUSH write
   that closes the upload; qword aligned because
   dl_OpenDma chains it into the display list as a DMA source */
static const unsigned int texFlushPacket[3][4] __attribute__((aligned(16))) = {
    /* derived name */
    {0, 0, 0, 0x50000002},
    {0x8001, 0x10000000, 0xE, 0},
    {1, 0, 0x3F, 0},
};

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

static int tex_transVramClutTex(Tim2Picture *pic, TexData *t, int levels, int lv)
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
                         psmTable[pic->clutType & 0x3F].psm, w, h);
    for (i = lv; i < levels - lv; i++) {
        n = texLoadLevel(t->lv[i].addr, t, i, t->lv[i].tbp[dl_GetPri()], t->lv[i].dbw,
                         psmTable[pic->imageType].psm, pic->imageWidth >> i, pic->imageHeight >> i);
        total += n;
    }
    return total;
}

/* the same claim loop as texAllocVram's tail without the CLUT */
static inline void texAllocLevels(TexData *t, int levels, int lv) /* derived name */
{
    int i;

    for (i = lv; i < levels - lv; i++) {
        t->lv[i].tbp[dl_GetPri()] = tex_AllocVramAuto(0, t->lv[i].vramSize);
    }
}

static int tex_transVramDirectTex(Tim2Picture *pic, TexData *t, int levels, int lv)
{
    int total = 0;
    int n;
    int i;

    texAllocLevels(t, levels, lv);
    for (i = lv; i < levels - lv; i++) {
        n = texLoadLevel(t->lv[i].addr, t, i, t->lv[i].tbp[dl_GetPri()], t->lv[i].dbw,
                         psmTable[pic->imageType].psm, pic->imageWidth >> i, pic->imageHeight >> i);
        total += n;
    }
    return total;
}

static void tex_transRegister(TexData *t)
{
    dl_OpenDma(2, &t->pkt, 5);
    dl_CloseDma();
}

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

static void tex_convertImage(void *dst, void *src, short fmt, short w, short h);

INCLUDE_ASM(tex_convertImage);

static void tex_makeCopyImage(Tim2Picture *pic, TexData *t, char *src, int convert)
{
    Tim2Mipmap *mip = (Tim2Mipmap *)(pic + 1);
    int i;
    DpkHead *p;
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

        p = t->lv[0].addr;
        n = pic->imageSize >> 4;
        p->vif[0] = 0;
        p->vif[1] = 0;
        p->vif[2] = 0x13000000;
        p->vif[3] = (n + 1) | 0x50000000;
        p->tag[0] = (n | 0x8000) | ((long long)0x8000 << 44);
        p->tag[1] = 0;
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

            p = t->lv[i].addr;
            n = mip->sizes[i] >> 4;
            p->vif[0] = 0;
            p->vif[1] = 0;
            p->vif[2] = 0x13000000;
            p->vif[3] = (n + 1) | 0x50000000;
            p->tag[0] = (n | 0x8000) | ((long long)0x8000 << 44);
            p->tag[1] = 0;
            src += mip->sizes[i];
            q = (int *)((char *)p + (mip->sizes[i] + 32));
            *q++ = 0;
            *q++ = 0;

            *q++ = 0;
            *q++ = 0;
        }
    }
}

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

int tex_TransTexture(int id, int ret);

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

static void tex_scrollClut(void *dstClut, void *curClut, void *srcClut, int sizeDiv, int colors,
                           void *ext, int frame, void *tex)
{
    TexColor buf[colors];
    TexExt *e = ext;
    TexColor *dst = dstClut;
    TexColor *cur = curClut;
    TexColor *src = srcClut;
    int lo;
    int hi;
    int step;
    int rem;
    int span;
    int k;
    int i;
    int j;
    int n;

    if (sizeDiv != 2) {
        return;
    }

    lo = e->file.csBgn;
    hi = e->file.csEnd;
    if (colors < lo || colors < hi) {
        debug_StdPrintfDummy(
            "illegal user space data [%s] Clut Scroll (color:%d start:%d end:%d)\n", tex, colors,
            lo, hi);
        return;
    }

    /* A swap of start and end whose last line reads lo where the temporary
     * was meant, so it only clamps start to end. */
    if (hi < lo) {
        i = lo;
        lo = hi;
        hi = lo;
    }

    step = ABSF(e->file.csSpd);
    rem = frame % step;
    if (rem == 0) {
        span = hi - lo + 1;
        k = ABSF(e->file.csStp) % span * SIGNF(e->file.csSpd) * SIGNF(e->file.csStp);

        for (i = lo; i <= hi; i++) {
            cur[CLUT_CSM1(colors, i)] = src[CLUT_CSM1(colors, i)];
        }
        for (i = lo; i <= hi; i++) {
            j = i + k;
            while (j < lo) {
                j += span;
            }
            while (hi < j) {
                j -= span;
            }
            buf[CLUT_CSM1(colors, i)] = src[CLUT_CSM1(colors, j)];
        }
        for (i = lo; i <= hi; i++) {
            src[CLUT_CSM1(colors, i)] = buf[CLUT_CSM1(colors, i)];
        }
    }
    for (i = lo; i <= hi; i++) {
        n = CLUT_CSM1(colors, i);
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

static void tex_textureAnimation(void)
{
    int i;

    for (i = 0; i < texCount; i++) {
        TexData *t = &texTable[i].rec;
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
                int clut = psmTable[t->pic.clutType & 0x3F].sizeDiv;
                unsigned int n = t->pic.clutSize >> 2;

                tex_scrollClut((char *)t->clut.addr + 0x20, e->clutA, e->clutB, clut, n, e,
                               e->clutFrame, t);
            }
            e->clutFrame++;
        }
    }
}

void tex_SetClutAnimation(int id, int frame)
{
    TexData *t = &texTable[id].rec;
    TexExt *c = &t->ext;

    if (c->animated != 0) {
        int clut = psmTable[t->pic.clutType & 0x3F].sizeDiv;
        unsigned int n = t->pic.clutSize >> 2;

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
    TexData *t = &texTable[id].rec;

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

/* the reset of one priority's VRAM cursor, which tex_ResetVram inlines */
static inline void resetVramPri(int pri) /* derived name */
{
    int i;

    dl_SetDLPriority(pri);

    vramPri[pri].texAddr = 0x2800;
    vramPri[pri].clutAddr = 0x3E80;
    vramPri[pri].lastTex = -1;
    for (i = 0; i < texCount; i++) {
        texTable[i].rec.ext.transDone[pri] = 0;
    }
}

/* tex_Init's first-call flag: the table is marked free once, later calls
   recount the loaded entries. */
static int texTableReady = 0; /* derived name */

void tex_ResetVram(void);

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

static void tex_printTexture(int id)
{
    TexData *p = &texTable[id].rec;
    int lv = texTable[id].rec.ext.level;
    float st[4];

    debug_PrintfDummy(ScreenWidth - 160, 195, 0xFF800000, "%8s:SIZE=%3dX%3d",
                      textype[p->pic.imageType], p->pic.imageWidth >> lv, p->pic.imageHeight >> lv);

    tex_TransTexture(id, 11);
    gif_StartPacketPri(11);
    {
        float one = 1.0f;
        TexColor col = {128, 128, 128, 128};
        int w = p->pic.imageWidth >> lv;
        int h = p->pic.imageHeight >> lv;
        int rect[4] = {(304 - w) * 16, -1536, w * 16, h / 2 * 16};

        st[0] = p->uv.uOfs;
        st[1] = p->uv.vOfs;
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
         * GsBase.c reads its scale. */
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
typedef struct TexToolRow { /* field names derived */
    char *label;
    float min;
    float max;
    float step;
    int type;
    void *var;
    int _18;
} TexToolRow; /* derived name */

static int tex_Tool(int *tno)
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
    /* the step multiplier the shoulder button scales by ten at a time */
    static int stepScale = 1; /* derived name */
    unsigned int col[2] = {0xFFFFFF00, 0xFFC0C000};

    /* One print per row type, int, short and float, as nested inline
     * functions. */
    inline void printInt(int i) /* derived name */
    {
        debug_PrintfDummy(10, i * 9 + 46, col[i == toolRow], "%s:%d", m[i].label, *(int *)m[i].var);
    }

    inline void printShort(int i) /* derived name */
    {
        debug_PrintfDummy(10, i * 9 + 46, col[i == toolRow], "%s:%d", m[i].label,
                          *(short *)m[i].var);
    }

    inline void printFloat(int i) /* derived name */
    {
        debug_PrintfDummy(10, i * 9 + 46, col[i == toolRow], "%s:%f", m[i].label,
                          *(float *)m[i].var);
    }

    int cnt = 0;
    int chg = 0;
    int ret = 0;
    int i;
    TexData *rec;

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
                 * return */
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
            malloc_MemCpy((char *)rec->clut.addr + 0x20, rec->ext.clutOrg, rec->pic.clutSize);
            malloc_MemCpy(rec->ext.clutA, rec->ext.clutOrg, rec->pic.clutSize);
            malloc_MemCpy(rec->ext.clutB, rec->ext.clutOrg, rec->pic.clutSize);
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
        TexData *t = &texTable[i].rec;

        sum = 0;
        for (j = 0; j < t->levelNum; j++) {
            sum += t->pic.totalSize >> (j * 2);
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
        TexData *t = &texTable[i].rec;

        sum = 0;
        for (j = 0; j < t->levelNum; j++) {
            sum += t->pic.totalSize >> (j * 2);
        }

        if (i == listTexNo) {
            debug_PrintfDummy(10, row * 8 + 50, 0xFF808000, "%03d%18s%7d:%1d/%1d:%s:%s:%s",
                              listTexNo, (int)t, sum, texTable[listTexNo].rec.ext.level + 1,
                              t->levelNum, imageTypeName[t->pic.imageType],
                              clutTypeName[t->pic.clutType & 0x3F], headerName[t->ext.animated]);
        } else {
            debug_PrintfDummy(10, row * 8 + 50, 0xFFFFFF00, "%03d%18s%7d:%1d/%1d:%s:%s:%s", i,
                              (int)t, sum, texTable[i].rec.ext.level + 1, t->levelNum,
                              imageTypeName[t->pic.imageType], clutTypeName[t->pic.clutType & 0x3F],
                              headerName[t->ext.animated]);
        }
        row++;
    }

    debug_PrintfDummy(10, row * 8 + 50, 0xFF800000, "   %17s %7d ", "TotalTextureSize", total);

    if ((pad[0].flags & 0x80) != 0) {
        TexEntry *e = &texTable[listTexNo];
        TexData *t = &e->rec;

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

int tex_GetTextureNo(const char *name)
{
    return getTextureNo(name);
}

TexData *tex_GetTextureData(int idx)
{
    return getTextureData(idx);
}

char *tex_GetTextureName(int idx)
{
    return texTable[idx].rec.name;
}

void tex_SetSamplingType(TexData *tex, int mag, int min)
{
    tex->pkt.tex1.data = (tex->pkt.tex1.data & ~(long long)0xE0) | (mag << 5) | (min << 6);
}

TexExt *tex_GetTexExtData(int idx)
{
    return &texTable[idx].rec.ext;
}

short tex_GetVramFreeAddress(int pri)
{
    return vramPri[pri].texAddr;
}

INCLUDE_ASM(tex_UpdateMipMapLevel);

INCLUDE_ASM(tex_ResetVramPri);

int tex_GetTextureNum(void)
{
    return texCount;
}

/* the int flag is the last parameter, after the six floats */
void tex_SetUVScroll(const char *name, float u, float v, float su, float sv, float ou, float ov,
                     int limitOn)
{
    int no = getTextureNo(name);
    TexData *tex = getTextureData(no);
    TexExt *ext = &tex->ext;
    TexUV *uv = &tex->uv;

    if (ext->animated != 0) {
        ext->file.scrlU = su;
        ext->file.scrlV = sv;
        ext->frame = 0;
        uv->uOfs = u;
        uv->vOfs = v;
        ext->uLimit = ou;
        ext->vLimit = ov;
        ext->limitOn = limitOn;
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

int tex_RemakeRegistersSampleMin(int arg)
{
    int count = texCount;
    int i;
    for (i = 0; i < count; i++) {
        TexData *b = &texTable[i].rec;
        int min = GlobalStageSetting.texSampleMode;
        int mag = 1;
        if (b->ext.animated != 0) {
            mag = b->ext.file.smpMag;
            min = b->ext.file.smpMin;
        }
        b->pkt.tex1.data = (b->pkt.tex1.data & ~0xE0) | (mag << 5) | (min << 6);
    }
    return 0;
}
