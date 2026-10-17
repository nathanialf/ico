#include <libvu0.h>
#include "debug.h"
#include "cdvd.h"
#include "Basic.h"
#include "Matrix.h"
#include "Texture.h"
#include "Packet.h"
#include "DisplayP2O.h"
#include "Light.h"
#include <stdio.h>
#include "debug_exception.h"
#include "memory.h"
#include <assert.h>
#include "include_asm.h"

/* PAL's maxPacketSize word is not in this build: the demo's .sdata of the TU
   opens with pac_DispQW's strings */
/* A word written as a float through the union member. */
typedef union { /* field names derived */
    float f;
    unsigned int ui;
} PacketFloat; /* derived name */

/* A 16-byte vector copied as two doublewords.  pacWork.boxMin and boxMax
   are the 32-byte bounding box, minimum then maximum corner. */
typedef struct { /* field names derived */
    sceVu0FVECTOR f;
} PacBoxVec; /* derived name */

/* The context's counter pair at +0x30 (w[0] the element count, w[1] the GIF
   count) and the state word at +0x38, each read both as 32-bit words and as
   a 64-bit mask. */
typedef union { /* field names derived */
    unsigned long long ul;
    long long l;
    int w[2];
} PacState; /* derived name */

/* The work area's layout.  The cursor is a union of packet pointers, and
   each word is one post-increment statement. */
typedef union { /* field names derived */
    int *i;
    float *f;
    unsigned int addr;
    PacBoxVec *v;
} PacCursor; /* derived name */

typedef struct { /* field names derived */
    char name[32];
    unsigned int dmaTag;
    unsigned int vifCode;
    unsigned int gifTag;
    PacCursor cursor;
    PacState counts;
    PacState state;
    PacketFloat boxMin[4];
    PacketFloat boxMax[4];
} PacWork; /* derived name */

/* the packet builder's work area: the model name the error messages print,
 * the open DMA tag, VIF code and GIF tag, the write cursor, the element
 * counts, the state bits and the bounding box */
static PacWork pacWork; /* derived name */

static void pac_DispQW(void *p, int size)
{
    int i;
    int j;
    int flag;

    flag = 0;
    switch (size) {
    case 0:
        flag = 1;
        size = 4;
        debug_StdPrintfDummy("(addr 0x%08x <fl) : ", p);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_StdPrintfDummy("(addr 0x%08x <%2d>) : ", p, size);
        break;
    default:
        return;
    }
    for (i = 0; i < 16 / size; i++) {
        if (flag == 0) {
            for (j = 16 / (16 / size) - 1; j >= 0; j--)
                debug_StdPrintfDummy("%02x", ((unsigned char *)p)[i * size + j]);
            debug_StdPrintfDummy(" ");
        } else {
            debug_StdPrintfDummy("%12f ", ((float *)p)[i]);
        }
    }
    debug_StdPrintfDummy("
");
}

inline void pac_Dump(int *data, int size)
{
    int *p = data;
    int count;
    size >>= 4;
    if (size <= 0)
        return;
    count = size;
    do {
        int *arg = p;
        p += 4;
        pac_DispQW(arg, 4);
        count--;
    } while (count != 0);
}

INCLUDE_ASM(pac_DumpPac);

inline void pac_DispVu1Memory(int idx, int n, int size)
{
    char *p = (char *)0x1100C000 + (idx << 4);
    int i;
    for (i = 0; i < n; i++) {
        char *q = p;
        p += 0x10;
        pac_DispQW(q, size);
    }
}

/* grows the context's bounding box by one vertex (the strip builders inline
   it) */
static inline void pac_growBounds(PacWork *ctx, char *vtx, int idx) /* derived name */
{
    if (ctx->boxMin[0].f > *(float *)(vtx + idx * 16))
        ctx->boxMin[0].f = *(float *)(vtx + idx * 16);
    if (ctx->boxMax[0].f < *(float *)(vtx + idx * 16))
        ctx->boxMax[0].f = *(float *)(vtx + idx * 16);
    if (ctx->boxMin[1].f > *(float *)(vtx + idx * 16 + 4))
        ctx->boxMin[1].f = *(float *)(vtx + idx * 16 + 4);
    if (ctx->boxMax[1].f < *(float *)(vtx + idx * 16 + 4))
        ctx->boxMax[1].f = *(float *)(vtx + idx * 16 + 4);
    if (ctx->boxMin[2].f > *(float *)(vtx + idx * 16 + 8))
        ctx->boxMin[2].f = *(float *)(vtx + idx * 16 + 8);
    if (ctx->boxMax[2].f < *(float *)(vtx + idx * 16 + 8))
        ctx->boxMax[2].f = *(float *)(vtx + idx * 16 + 8);
}

INCLUDE_ASM(pac_makeBoundingBox);

static void pac_error(char *name, int type);

INCLUDE_ASM(pac_error);

INCLUDE_ASM(pac_makeNormalStrip);

/* one entry of the four-entry cluster weight table pac_getWeight fills: the
 * cluster's bone number and its weight on the vertex */
typedef struct { /* field names derived */
    int no;
    float weight;
} PacWeight; /* derived name */

/* clang-format off */
static int pac_getWeight(PacWeight *w, PObjPart *obj, char *shp, int num)
{
    int ret = -1, n = 0, i = 0;
    int j, id;
    PacWeight tmp; char *bone; float sum;
    for (j = 0; j < 4; j++) { w[j].weight = 0.0f; w[j].no = 0; }

    for (j = 0; j < obj->polyCount; j++) {
        bone = *(char **)(j * 16 + (int)obj->polys);

        for (; *(int *)(i * 16 + (int)bone) >= 0;) {
            if ((id = *(int *)(i * 16 + (int)bone)) == *(short *)(shp + 4)) {
                w[n].no = *(int *)(j * 16 + (int)obj->polys + 4);
                w[n].weight = *(float *)(i * 16 + (int)bone + 4);
                if (n == 0) {
                    ret = id;
                    if ((unsigned int)ret >= obj->vtxCount)
                        pac_error("pac_getWeight(0)", 2);
                }
                if (++n >= 4)
                    pac_error("pac_getWeight(1)", 3);
            }
            i++;
        }
        i = 0;
    }
    if (ret == -1)
        pac_error("pac_getWeight(2)", 4);
    if (n == 3) {

        debug_StdPrintfDummy("vertex has 3 cluster-weights %d(%f) %d(%f) %d(%f)\n", w[0].no, w[0].weight, w[1].no, w[1].weight, w[2].no, w[2].weight);

        for (j = 0; j < n; j++) {
            for (i = j; i < n; i++) {
                if (j != i)
                    if (w[j].weight < w[i].weight) {
                        tmp = w[i];
                        w[i] = w[j];
                        w[j] = tmp;
                    }
            }
        }
        for (j = 2; j < n; j++)
            w[0].weight += w[j].weight;
    }

    sum = w[0].weight + w[1].weight;
    if (sum < 0.99f)
        debug_StdPrintfDummy("warning:weight total %f VtxIdx:%d\n", sum, ret);

    return ret;
}

INCLUDE_ASM(func_00119EF8);

/* GIF tag template for the two texture-mapping modes: per mode the tag's
   FLG/NREG half, then the REGS descriptor. */
typedef struct { /* field names derived */
    unsigned long long tag;
    unsigned long long regs;
} GifTagTmpl; /* derived name */

/* the two GIF tag templates, defined before their first user */
static const GifTagTmpl gifTagTmpl[2] = {
    /* derived name */
    {0x2000400000008000ULL, 0x51},
    {0x3000400000008000ULL, 0x512},
};

INCLUDE_ASM(func_0011A370);

INCLUDE_ASM(func_0011A4F8);

INCLUDE_ASM(func_0011A6C0);

/* Copy a finished packet down into a fresh seki-heap block.  The packet
   builder holds its packet addresses as words (pacWork's tags and cursor,
   pac_makeStrip's pkt and dst) and masks the segment bits off them, so the
   heap's pointers are kept as ints here and there. */
static inline int pac_moveToSeki(int src, int size) /* derived name */
{
    int p;

    p = (int)mallocseki(size);
    if (p == 0)
        debug_Assert("pac_copyStrip:No Enough Memory for Packet.\n");
    debug_StdPrintfDummy("ALL:src:%p => dst:%p (size:%x)\n", src, p, size);
    if (src != p)
        malloc_MemCpy((void *)p, (void *)src, size);
    return p;
}

INCLUDE_ASM(func_0011A810);

INCLUDE_ASM(func_0011A9A8);

/* clang-format on */

/* One packet qword. The file writes this memory both as 32-bit VIF codes
   (pac_setVifCode, pac_setVifEndCode) and as a 64-bit GIF tag, so the
   packet word is a union of the two views. */
typedef union { /* field names derived */
    unsigned long long ul;
    unsigned int ui[2];
} PacketWord; /* derived name */

/* the packet bytes pac_closeTag adds up, the polygons pac_makeStrip counts, the tags
   pac_closeTag and pac_continueTag open, the strips of the current chain
   (the "fchain" the divide messages print) and a word only pac_Init
   clears. pac_makePacket clears and reads the first three. */
static unsigned int pacPacketBytes; /* derived name */

static unsigned int pacPolyCount; /* derived name */

static unsigned int pacTagCount; /* derived name */

static unsigned int pacStripCount; /* derived name */

static int pacUnusedWord; /* derived name */

/* Zero the open DMA tag's two words.  The context pointer is read again for
   the second word: the first store may alias it. */
static inline void pac_closeDmaTag(void) /* derived name */
{
    ((unsigned int *)pacWork.dmaTag)[0] = 0;
    ((unsigned int *)pacWork.dmaTag)[1] = 0;
}

/* Close the VIF list and reopen the DMA tag one qword further on. */
static inline void pac_continueDmaTag(void) /* derived name */
{
    PacWork *ctx = &pacWork;
    int *p = ctx->cursor.i;
    *p++ = 0x17000000;
    ctx->cursor.i = p;
    p[0] = 0;
    ctx->vifCode = (int)(p + 1) & 0x0FFFFFFF;
    ctx->gifTag = (int)(p + 3) & 0x0FFFFFFF;
    ctx->cursor.i = p + 7;
}

/* 192 is the DMA chain's qword budget.  In the "gif over! cut!" message the
   last field is the qword count plus the gif tags the chain already holds
   plus the one about to be opened. */
/* the material attribute word's microprogram-mode bit, read at word width */
typedef struct { /* field names derived */
    unsigned int mode : 1;
} PacMatMode; /* derived name */

static int pac_makeStrip(char **out, PObjPart *obj, PObjGroup *tbl, int matno, int texno,
                         PObjModel *mdl);

INCLUDE_ASM(pac_setMaterialPacket);

INCLUDE_ASM(pac_makeMaterialTable);

/* the line-primitive part's group record: its material table, its
   texture-info table and the two counts */
typedef struct MatLine {        /* field names derived */
    PObjMaterial *materials;    /* 0x00 */
    PObjTexInfo *texs;          /* 0x04 */
    struct PacLineSet *lineSet; /* 0x08 */
    short matCount;             /* 0x0C */
    short texCount;             /* 0x0E */
} MatLine;                      /* derived name */

INCLUDE_ASM(pac_makeMaterialTableLine);

static void pac_getTextureInfo(PObjTexInfo *m, PObjPart *info, int idx);

INCLUDE_ASM(pac_getTextureInfo);

/* One 16-byte shape-table qword, four ints. */
typedef struct { /* field names derived */
    int word[4];
} PacQw; /* derived name */

/* One 32-byte morph target entry (DisplayP2O.h's PObjMorph) as the copy
   loop sees it, 8-byte aligned so it moves in doublewords; a list of them
   ends with -1 in the index word at +0x10. */
typedef struct { /* field names derived */
    long long data[2];
    int index;
    int pad14[3];
} PacNode; /* derived name */

static void pac_makeShapeTable(PObjGroup *grp, PObjPart *obj)
{
    unsigned int i;
    int k;
    int cnt;
    int m;
    short *p;
    int n;
    PacQw **tbl;
    PacNode **ntbl;
    PacNode *dst;
    PacNode *r;
    PacNode *q;

    obj->vtxSave = mallocseki(obj->vtxCount * 16);
    for (i = 0; i < obj->vtxCount; i++)
        _CopyVector(obj->vtxSave + i * 16, obj->vtx + i * 16);
    obj->nrmSave = mallocseki(obj->nrmCount * 16);
    for (i = 0; i < obj->nrmCount; i++)
        _CopyVector(obj->nrmSave + i * 16, obj->nrm + i * 16);
    obj->vtx = mallocseki(obj->vtxCount * 16);
    for (i = 0; i < obj->vtxCount; i++)
        _CopyVector(obj->vtx + i * 16, obj->vtxSave + i * 16);
    obj->nrm = mallocseki(obj->nrmCount * 16);
    for (i = 0; i < obj->nrmCount; i++)
        _CopyVector(obj->nrm + i * 16, obj->nrmSave + i * 16);
    tbl = (PacQw **)mallocseki(obj->stripCount * 4);
    for (i = 0; i < obj->stripCount; i++) {
        p = ((short **)obj->strips)[i];
        cnt = 0;
        n = p[0];
        while (n != 0) {
            p += n * 8 + 8;
            cnt += n + 1;
            n = p[0];
        }
        cnt++;
        tbl[i] = (PacQw *)mallocseki(cnt * 16);
        for (k = 0; k < cnt; k++)
            tbl[i][k] = ((PacQw **)obj->strips)[i][k];
    }
    obj->strips = tbl;
    ntbl = (PacNode **)mallocseki(obj->morphCount * 4);
    for (i = 0; i < obj->morphCount; i++) {
        ntbl[i] = 0;
        q = ((PacNode **)obj->morphs)[i];
        if (q != 0) {
            r = q;
            for (m = 0; r->index != -1; r++)
                m++;
            m += 2;
            ntbl[i] = (PacNode *)mallocseki(m * 32);
            for (r = ((PacNode **)obj->morphs)[i], dst = ntbl[i];; r++, dst++) {
                *dst = *r;
                if (r->index == -1)
                    break;
            }
        }
    }
    obj->morphs = (PObjMorph **)ntbl;
}

/* one line of a line part, 80 bytes: its two vertex indices, two uv indices
   and two colour indices, the vertex count (1 a point, 2 a line), the
   material and the texture slot (-1 for none) */
typedef struct PObjLine { /* field names derived */
    int vtx[2];           /* 0x00 */
    char pad08[24];
    int uv[2]; /* 0x20 */
    char pad28[8];
    int col[2]; /* 0x30 */
    char pad38[8];
    int num; /* 0x40 */
    char pad44[4];
    int mat; /* 0x48 */
    int tex; /* 0x4C */
} PObjLine;  /* derived name */

/* clears the running packet byte counter before a build */
static inline void pac_resetPacketCount(void) /* derived name */
{
    pacPacketBytes = 0;
}

/* allocates and fills a material's texture-info table
   for the strip path */
static inline void pac_makeTextureTable(PObjGroup *dst, PObjPart *src) /* derived name */
{
    PObjTexInfo *tex;
    unsigned int i;

    tex = mallocseki(src->texCount * 80);
    for (i = 0; i < src->texCount; i++)
        pac_getTextureInfo(&tex[i], src, i);
    dst->texs = tex;
    dst->texCount = src->texCount;
}

/* the line-primitive counterpart; it writes the count into
   the line header's own halfword at +0xE */
static inline void pac_makeTextureTableLine(MatLine *dst, PObjPart *src) /* derived name */
{
    PObjTexInfo *tex;
    unsigned int i;

    tex = mallocseki(src->texCount * 80);
    for (i = 0; i < src->texCount; i++)
        pac_getTextureInfo(&tex[i], src, i);
    dst->texs = tex;
    dst->texCount = src->texCount;
}

/* prev builds the strip chain and then walks it for the clone, j counts the
   materials, m the texture slots, and j then the line records; out is the packet address pac_makeStrip
   returns. */
INCLUDE_ASM(pac_makePacket);

INCLUDE_ASM(pac_MakePacket);

inline void pac_Init(void)
{
    pacUnusedWord = 0;
}
