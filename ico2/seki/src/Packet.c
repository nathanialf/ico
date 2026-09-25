#include "common.h"
#include "debug.h"
#include "Basic.h"
#include "Matrix.h"
#include "Texture.h"

extern char D_0054F5C0[];
extern char D_0054F5D0[];

#include "Packet.h"
#include <stdio.h>

extern char D_0054F200[];
extern char D_0054F218[];
extern char D_0063A100[];
extern char D_0063A108[];
extern char D_0063A110[];
extern char D_0063A118[];

/* RECONSTRUCTION (name ours): the packet builder's work area, the TU's whole
 * .bss (MAIN.MAP Packet.o .bss 0x60, no symbol): the model name the error
 * messages print at 0, the open DMA tag, VIF code, GIF tag and write pointers
 * at 0x20..0x2C, the element count at 0x30, the state bits at 0x38, the
 * bounding box minimum at 0x40 and maximum at 0x50.  Every function reaches it
 * as raw storage through a char pointer, so it is kept as the byte array the
 * TU reads.  Not static: the assembled stubs still name it. */
static char pacWork
    [0x60]; /* static: the remaining stubs are assembled into this object and reach it as a local symbol */

void pac_DispQW(void *p, int size)
{
    int i;
    int j;
    int flag;

    flag = 0;
    switch (size) {
    case 0:
        flag = 1;
        size = 4;
        debug_StdPrintfDummy(D_0054F200, p);
        break;
    case 1:
    case 2:
    case 4:
    case 8:
    case 16:
        debug_StdPrintfDummy(D_0054F218, p, size);
        break;
    default:
        return;
    }
    for (i = 0; i < 16 / size; i++) {
        if (flag == 0) {
            for (j = 16 / (16 / size) - 1; j >= 0; j--)
                debug_StdPrintfDummy(D_0063A100, ((unsigned char *)p)[i * size + j]);
            debug_StdPrintfDummy(D_0063A108);
        } else {
            debug_StdPrintfDummy(D_0063A110, ((float *)p)[i]);
        }
    }
    debug_StdPrintfDummy(D_0063A118);
}

inline void pac_Dump(int *a0, int size)
{
    int *p = a0;
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

extern char D_0054F278[];
extern char D_0054F290[];
extern char D_0054F2A8[];
extern char D_0054F2C8[];
extern char D_0054F2E8[];

void pac_DumpPac(char *pac)
{
    char *q;
    int i;
    int cnt;
    int n;

    while (pac != 0) {
        q = *(char **)(pac + 0x98);
        cnt = 0;
        for (i = 0; i < ((*(int *)(pac + 0x90) & 0xFFFFFF) >> 4); i++) {
            if (cnt == 0) {
                if (i == 0)
                    debug_StdPrintfDummy(D_0054F278);
                else if (i == ((*(int *)(pac + 0x90) & 0xFFFFFF) >> 4) - 1)
                    debug_StdPrintfDummy(D_0054F290);
                else
                    debug_StdPrintfDummy(D_0054F2A8);
                debug_StdPrintfDummy(q);
            } else if (cnt == -1) {
                char *ctx = pacWork;
                n = (*(int *)q & 0xFFF) * *(int *)(ctx + 0x30);
                cnt = n + 1;
                debug_StdPrintfDummy(D_0054F2C8, n, *(int *)(ctx + 0x30));
                debug_StdPrintfDummy(q);
                debug_StdPrintfDummy(D_0054F2E8, ctx);
            } else {
                debug_StdPrintfDummy(q);
            }
            q += 0x10;
            cnt--;
        }
        pac = *(char **)(pac + 0x94);
        debug_StdPrintfDummy(D_0063A118);
    }
}

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

/* A float word written through the union member: the store has alias set 0,
   so the bounding-box stores of pac_growBounds end what CSE knows about the
   strip entry and the strip builders re-read the vertex index after it, as the
   ROM does. */
typedef union {
    float f;
    unsigned int ui;
} PacketFloat;

/* RECONSTRUCTION (names ours): the work area's layout, as the TU's accesses
   read it. The strip builders reach the state and the write cursor as
   members: the ROM materialises the bare pacWork address at the first access
   of each region (listing 742 and 749, 911, 921, 933 and 944), which is what
   a member access of the whole object expands to, where a char offset from
   pacWork folds into one constant address. The cursor is a union of packet
   pointers: every access to it has alias set 0, so each typed word store
   keeps the cursor store before it alive while the int and float loads
   between them move as the ROM's do, and each word is one post-increment
   statement (the listing puts a word's value store and its cursor store on
   one line). The bytes cannot tell this cast view from a work area declared
   with the struct type. */
typedef union {
    int *i;
    float *f;
} PacCursor;

typedef struct {
    char name[0x20];
    int dmaTag;
    int vifCode;
    int gifTag;
    PacCursor cursor;
    int count;
    int gifCount;
    long long state;
    float boxMin[4];
    float boxMax[4];
} PacWork;

/* listing rows 607-613: grows the context's bounding box by one vertex (the
   strip builders inline it) */
static inline void pac_growBounds(char *ctx, char *vtx, int idx)
{
    if (*(float *)(ctx + 0x40) > *(float *)(vtx + idx * 16))
        ((PacketFloat *)(ctx + 0x40))->f = *(float *)(vtx + idx * 16);
    if (*(float *)(ctx + 0x50) < *(float *)(vtx + idx * 16))
        ((PacketFloat *)(ctx + 0x50))->f = *(float *)(vtx + idx * 16);
    if (*(float *)(ctx + 0x44) > *(float *)(vtx + idx * 16 + 4))
        ((PacketFloat *)(ctx + 0x44))->f = *(float *)(vtx + idx * 16 + 4);
    if (*(float *)(ctx + 0x54) < *(float *)(vtx + idx * 16 + 4))
        ((PacketFloat *)(ctx + 0x54))->f = *(float *)(vtx + idx * 16 + 4);
    if (*(float *)(ctx + 0x48) > *(float *)(vtx + idx * 16 + 8))
        ((PacketFloat *)(ctx + 0x48))->f = *(float *)(vtx + idx * 16 + 8);
    if (*(float *)(ctx + 0x58) < *(float *)(vtx + idx * 16 + 8))
        ((PacketFloat *)(ctx + 0x58))->f = *(float *)(vtx + idx * 16 + 8);
}

extern char D_0054F300[];

/* RECONSTRUCTION (name ours): a 16-byte vector copied as two doublewords,
   the ROM's ld/ld and sd/sd pair for the margin copy out of D_0054F300.
   pacWork + 0x40 is the 32-byte bounding box, minimum then maximum corner
   (the ROM reaches the maximum as %lo(pacWork + 0x50) and the minimum with
   -16). */
typedef struct {
    long long d[2];
} PacBoxVec;

void pac_makeBoundingBox(float (*box)[4], int flag)
{
    PacBoxVec sum;
    PacBoxVec mrg;
    char *ctx;
    int i;

    memset(&sum, 0, sizeof(sum));
    mrg = *(PacBoxVec *)D_0054F300;
    if (flag != 0) {
        _AddVectorXYZ(pacWork + 0x50, pacWork + 0x50, &mrg);
        _SubVectorXYZ(pacWork + 0x40, pacWork + 0x40, &mrg);
    }
    /* The eight corners are indexed off the box, not walked with a pointer:
       loop.c reduces the box[i] addresses to one pointer giv, and in that
       form sched1 schedules each block of the loop alone, the ROM's order; a
       pointer walk forms a ten-block interblock region and hoists the masks
       and the call's argument moves into the first block (measured). */
    for (ctx = pacWork, i = 0; i < 8; i++) {
        if (i & 1)
            box[i][0] = *(float *)(ctx + 0x50);
        else
            box[i][0] = *(float *)(ctx + 0x40);
        if (i & 2)
            box[i][1] = *(float *)(ctx + 0x54);
        else
            box[i][1] = *(float *)(ctx + 0x44);
        if (i & 4)
            box[i][2] = *(float *)(ctx + 0x58);
        else
            box[i][2] = *(float *)(ctx + 0x48);
        box[i][3] = 1.0f;
        _AddVectorXYZ(&sum, &sum, box[i]);
    }
}

extern char D_0054F310[];
extern char D_0054F340[];
extern char D_0054F370[];
extern char D_0054F3A0[];
extern char D_0054F3D8[];
extern char D_0054F400[];
extern char D_0063A120[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

void pac_error(char *name, int type)
{
    switch (type) {
    case 5:
        debug_Assert(D_0054F310, pacWork, name);
        break;
    case 1:
        debug_Assert(D_0054F340, pacWork, name);
        break;
    case 2:
        debug_Assert(D_0054F370, pacWork, name);
        break;
    case 3:
        debug_Assert(D_0054F3A0, pacWork, name);
        break;
    case 4:
        debug_Assert(D_0054F3D8, pacWork, name);
        break;
    }
    debug_assert(D_0054F400, 684);
    __assert(D_0054F400, 684, D_0063A120);
}

extern char D_0054F428[];
extern char D_0054F468[];

int pac_makeNormalStrip(char *obj, short *strip, int num)
{
    char buf[256];
    short *v;
    char *vtx;
    char *nrm;
    char *uv;
    char *ary;
    char *col;
    char *ctx;
    float f2;
    int i;

    vtx = *(char **)(obj + 0x90);
    nrm = *(char **)(obj + 0xA0);
    uv = *(char **)(obj + 0xB0);
    ary = *(char **)(obj + 0xE0);
    col = *(char **)(obj + 0xC0);
    ctx = pacWork;
    *(int *)(strip - 6) =
        (*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x20);
    for (i = 0, v = strip; i < num; i++, v += 8) {
        char *ctx = pacWork;

        pac_growBounds(ctx, vtx, v[2]);
        _CopyVector((*(PacBoxVec **)(ctx + 0x2C))++, vtx + v[2] * 16);
        if (*(float *)(vtx + v[2] * 16 + 12) != 1.0f) {
            sprintf(buf, D_0054F428, *(float *)(vtx + v[2] * 16), *(float *)(vtx + v[2] * 16 + 4),
                    *(float *)(vtx + v[2] * 16 + 8), *(float *)(vtx + v[2] * 16 + 12), v[2]);
            debug_StdPrintfDummy(buf);
        }
        if ((int)(*(long long *)(ctx + 0x38) >> 1) & 1)
            _CopyVector((*(PacBoxVec **)(ctx + 0x2C))++, nrm + v[3] * 16);
        if (((int)(*(long long *)(ctx + 0x38) >> 3) & 1) && v[4] != -1) {
            f2 = 1.0f;
            if (i == 0)
                f2 = 0.0f;
            *((PacWork *)ctx)->cursor.f++ =
                *(float *)(uv + v[4] * 16) * *(float *)(ary + v[7] * 144 + 0x84);
            *((PacWork *)ctx)->cursor.f++ =
                *(float *)(uv + v[4] * 16 + 4) * *(float *)(ary + v[7] * 144 + 0x88);
            *((PacWork *)ctx)->cursor.f++ = 1.0f;
            *((PacWork *)ctx)->cursor.f++ = f2;
        } else {
            pac_error(D_0054F468, 5);
        }
        if (((int)(((PacWork *)pacWork)->state >> 4) & 1) && v[5] != -1) {
            *((PacWork *)pacWork)->cursor.f++ = (float)(unsigned char)col[v[5] * 4];
            *((PacWork *)pacWork)->cursor.f++ = (float)(unsigned char)col[v[5] * 4 + 1];
            *((PacWork *)pacWork)->cursor.f++ = (float)(unsigned char)col[v[5] * 4 + 2];
            *((PacWork *)pacWork)->cursor.f++ = 127.0f;
        } else {
            *((PacWork *)pacWork)->cursor.f++ = 128.0f;
            *((PacWork *)pacWork)->cursor.f++ = 128.0f;
            *((PacWork *)pacWork)->cursor.f++ = 128.0f;
            *((PacWork *)pacWork)->cursor.f++ = 127.0f;
        }
    }
    return num - 2;
}

extern char D_0054F480[];
extern char D_0054F498[];
extern char D_0054F4B0[];
extern char D_0054F4C8[];
extern char D_0054F500[];

/* one entry of the four-entry cluster weight table pac_getWeight fills: the
 * cluster's bone number and its weight on the vertex */
typedef struct {
    int no;
    float weight;
} PacWeight;

/* clang-format off */
int pac_getWeight(PacWeight *w, char *obj, char *shp, int num)
{
    int ret = -1, n = 0, i = 0;
    int j, id;
    PacWeight tmp; char *bone; float sum;
    for (j = 0; j < 4; j++) { w[j].weight = 0.0f; w[j].no = 0; }

    for (j = 0; j < *(unsigned int *)(obj + 0xF4); j++) {
        bone = *(char **)(j * 16 + *(int *)(obj + 0xF0));

        for (; *(int *)(i * 16 + (int)bone) >= 0;) {
            if ((id = *(int *)(i * 16 + (int)bone)) == *(short *)(shp + 4)) {
                w[n].no = *(int *)(j * 16 + *(int *)(obj + 0xF0) + 4);
                w[n].weight = *(float *)(i * 16 + (int)bone + 4);
                if (n == 0) {
                    ret = id;
                    if ((unsigned int)ret >= *(unsigned int *)(obj + 0x94))
                        pac_error(D_0054F480, 2);
                }
                if (++n >= 4)
                    pac_error(D_0054F498, 3);
            }
            i++;
        }
        i = 0;
    }
    if (ret == -1)
        pac_error(D_0054F4B0, 4);
    if (n == 3) {

        debug_StdPrintfDummy(D_0054F4C8, w[0].no, w[0].weight, w[1].no, w[1].weight, w[2].no, w[2].weight);



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
        debug_StdPrintfDummy(D_0054F500, sum, ret);
    /* the listing has no rows for the 23 lines between the warning and the
     * return */





















    return ret;
}

/* clang-format on */
extern char D_0054F528[];
extern char D_0054F568[];
extern char D_0054F580[];
extern char D_0054F5A0[];

int pac_makeClusterStrip(char *obj, short *strip, int num)
{
    PacWeight w[4];
    char buf[256];
    int i;
    short *v;
    char *vtx;
    char *nrm;
    char *uv;
    char *col;
    char *ctx;

    vtx = *(char **)(obj + 0x90);
    nrm = *(char **)(obj + 0xA0);
    uv = *(char **)(obj + 0xB0);
    col = *(char **)(obj + 0xC0);
    ctx = pacWork;
    *(int *)(strip - 6) =
        (*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x20);
    for (i = 0, v = strip; i < num; i++, v += 8) {
        char *ctx;
        int idx;

        idx = pac_getWeight(w, obj, (char *)v, num);
        ctx = pacWork;
        pac_growBounds(ctx, vtx, idx);
        _CopyVector((*(PacBoxVec **)(ctx + 0x2C))++, vtx + v[2] * 16);
        if (*(float *)(vtx + v[2] * 16 + 12) != 1.0f) {
            sprintf(buf, D_0054F528, *(float *)(vtx + v[2] * 16), *(float *)(vtx + v[2] * 16 + 4),
                    *(float *)(vtx + v[2] * 16 + 8), *(float *)(vtx + v[2] * 16 + 12), v[2]);
            debug_StdPrintfDummy(buf);
        }
        if ((int)(*(long long *)(ctx + 0x38) >> 1) & 1)
            _CopyVector((*(PacBoxVec **)(ctx + 0x2C))++, nrm + v[3] * 16);
        else
            pac_error(D_0054F568, 1);
        *((PacWork *)pacWork)->cursor.i++ = w[0].no * 4 + 16;
        *((PacWork *)pacWork)->cursor.f++ = w[0].weight;
        *((PacWork *)pacWork)->cursor.i++ = w[1].no * 4 + 16;
        *((PacWork *)pacWork)->cursor.f++ = w[1].weight;
        if (w[0].no >= 60 || w[1].no >= 60) {
            debug_StdPrintfDummy(D_0054F580);
            debug_assert(D_0054F400, 917);
            __assert(D_0054F400, 917, D_0063A120);
        }
        if (((int)(((PacWork *)pacWork)->state >> 3) & 1) && v[4] != -1) {
            *((PacWork *)pacWork)->cursor.f++ =
                *(float *)(uv + v[4] * 16) * *(float *)(*(char **)(obj + 0xE0) + v[7] * 144 + 0x84);
            *((PacWork *)pacWork)->cursor.f++ =
                *(float *)(uv + v[4] * 16 + 4) *
                *(float *)(*(char **)(obj + 0xE0) + v[7] * 144 + 0x88);
            *((PacWork *)pacWork)->cursor.f++ = 1.0f;
            *((PacWork *)pacWork)->cursor.f++ = i == 0 ? 0.0f : 1.0f;
        } else {
            pac_error(D_0054F568, 5);
        }
        if (((int)(((PacWork *)pacWork)->state >> 4) & 1) && v[5] != -1) {
            if (col == 0) {
                debug_StdPrintfDummy(D_0054F5A0);
                debug_assert(D_0054F400, 936);
                __assert(D_0054F400, 936, D_0063A120);
            }
            *((PacWork *)pacWork)->cursor.f++ = (float)(unsigned char)col[v[5] * 4];
            *((PacWork *)pacWork)->cursor.f++ = (float)(unsigned char)col[v[5] * 4 + 1];
            *((PacWork *)pacWork)->cursor.f++ = (float)(unsigned char)col[v[5] * 4 + 2];
            *((PacWork *)pacWork)->cursor.f++ = 127.0f;
        } else {
            *((PacWork *)pacWork)->cursor.f++ = 128.0f;
            *((PacWork *)pacWork)->cursor.f++ = 128.0f;
            *((PacWork *)pacWork)->cursor.f++ = 128.0f;
            *((PacWork *)pacWork)->cursor.f++ = 127.0f;
        }
    }
    return num - 2;
}

void pac_openDmaTag(int a0)
{
    register int mask = 0x0FFFFFFF;
    char *ctx = pacWork;
    float f0 = 16777215.0f;
    float f1 = -16777215.0f;
    *(int *)(ctx + 0x20) = a0 & mask;
    *(int *)(ctx + 0x24) = (a0 + 0x8) & mask;
    *(int *)(ctx + 0x28) = (a0 + 0x10) & mask;
    *(int *)(ctx + 0x2C) = a0 + 0x20;
    *(float *)(ctx + 0x48) = f0;
    *(float *)(ctx + 0x44) = f0;
    *(float *)(ctx + 0x40) = f0;
    *(float *)(ctx + 0x58) = f1;
    *(float *)(ctx + 0x54) = f1;
    *(float *)(ctx + 0x50) = f1;
    debug_StdPrintfDummy(D_0054F5C0, a0 & mask);
}

void pac_setVifCode(int a0)
{
    char *ctx = pacWork;
    *(int *)(*(int *)(ctx + 0x24)) = 0;
    *(int *)(*(int *)(ctx + 0x24) + 4) = (a0 << 16) | 0x6C008000;
    debug_StdPrintfDummy(D_0054F5D0, *(int *)(*(int *)(ctx + 0x24)),
                         *(int *)(*(int *)(ctx + 0x24) + 4), *(int *)(ctx + 0x24), a0);
}

void pac_setVifEndCode(void)
{
    char *ctx = pacWork;
    int *p = (int *)*(int *)(ctx + 0x2C);
    *p++ = 0x17000000;
    *(int *)(ctx + 0x2C) = (int)p;
    p[0] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 1);
    p[1] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 2);
    p[2] = 0;
    *(int *)(ctx + 0x2C) = (int)(p + 3);
    debug_StdPrintfDummy(p + 3);
}

/* GIF tag template pair for the two texture-mapping modes, in the cod
   rodata pool: [0] is the tag's FLG/NREG half, [1] the REGS descriptor. */
typedef struct {
    unsigned long long w0;
    unsigned long long w1;
} GifTagTmpl;

/* One packet qword. The TU writes this memory both as 32-bit VIF codes
   (pac_setVifCode, pac_setVifEndCode) and as a 64-bit GIF tag, so the
   packet word is a union of the two views. */
typedef union {
    unsigned long long ul;
    unsigned int ui[2];
} PacketWord;

extern const GifTagTmpl D_0054F5F0[];
extern char D_0054F610[];
extern char D_0063A128[];

void pac_setGifTag(char *shp, char *mat, unsigned long long nloop)
{
    int abe;
    int tme;
    char *ctx;

    if (mat == 0)
        abe = ((int)(*(long long *)(shp + 0x60) >> 1) & 3) != 0;
    else if ((*(unsigned short *)(mat + 0x4E) & 6) == 0)
        abe = ((int)(*(long long *)(shp + 0x60) >> 1) & 3) != 0;
    else
        abe = 1;
    tme = *(unsigned short *)(mat + 0x4E) & 1;
    ctx = pacWork;
    ((PacketWord *)(*(int *)(ctx + 0x28)))->ul =
        D_0054F5F0[tme].w0 |
        ((0xCULL | ((unsigned long long)tme << 4) | ((unsigned long long)abe << 6)) << 47) | nloop;
    ((PacketWord *)(*(int *)(ctx + 0x28) + 8))->ul = D_0054F5F0[tme].w1;
    debug_StdPrintfDummy(D_0054F610);
    debug_StdPrintfDummy(*(int *)(ctx + 0x28));
    debug_StdPrintfDummy(D_0063A128, nloop);
}

/* .sbss, owned by Packet.o (MAIN.MAP Packet.o .sbss 0x14; it names no symbol
   in the run, so the names are ours), in the ROM's run order: the packet
   bytes pac_closeTag adds up, the polygons pac_makeStrip counts, the tags
   pac_closeTag and pac_continueTag open, the strips of the current chain
   (the "fchain" the divide messages print) and a word only pac_Init
   clears. pac_makePacket clears and reads the first three. */
static unsigned int pacPacketBytes;

static unsigned int pacPolyCount;

static unsigned int pacTagCount;

static unsigned int pacStripCount;

static int pacUnusedWord;

/* listing rows 993/995: a static inline sitting between pac_openDmaTag and
   pac_setVifCode that zeroes the open DMA tag's two words. It reads the
   context pointer again for the second word because the first store aliases
   it. */
static inline void pac_closeDmaTag(void)
{
    ((unsigned int *)*(unsigned int *)(pacWork + 0x20))[0] = 0;
    ((unsigned int *)*(unsigned int *)(pacWork + 0x20))[1] = 0;
}

int pac_closeTag(char *shp, char *mat)
{
    char *ctx;
    unsigned int n;
    unsigned int qwc;

    ctx = pacWork;
    n = ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4;
    if (n == 1) {
        *(unsigned int *)(ctx + 0x20) = 0;
        *(unsigned int *)(ctx + 0x24) = 0;
        *(unsigned int *)(ctx + 0x28) = 0;
        return 0;
    }
    pac_setVifCode(n);
    pac_setGifTag(
        shp, mat,
        (((((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4) -
          1) /
         *(unsigned int *)(ctx + 0x30)));
    pac_setVifEndCode();
    qwc = ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x20)) >> 4;
    pac_closeDmaTag();
    pacPacketBytes += qwc * 16;
    pacTagCount += 1;
    return qwc * 16;
}

extern char D_0054F620[];

/* listing rows 1043-1048: a static inline between pac_setVifEndCode and
   pac_closeTag that closes the VIF list and re-opens the DMA tag one qword
   further on. */
static inline void pac_continueDmaTag(void)
{
    char *ctx = pacWork;
    int *p = (int *)*(int *)(ctx + 0x2C);
    *p++ = 0x17000000;
    *(int *)(ctx + 0x2C) = (int)p;
    p[0] = 0;
    *(int *)(ctx + 0x24) = (int)(p + 1) & 0x0FFFFFFF;
    *(int *)(ctx + 0x28) = (int)(p + 3) & 0x0FFFFFFF;
    *(int *)(ctx + 0x2C) = (int)(p + 7);
}

void pac_continueTag(char *shp, char *mat)
{
    char *ctx;

    ctx = pacWork;
    if (((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4 == 1) {
        debug_StdPrintfDummy(D_0054F620, 0);
        debug_assert(D_0054F400, 1147);
        __assert(D_0054F400, 1147, D_0063A120);
    }
    pac_setVifCode(((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >>
                   4);
    pac_setGifTag(
        shp, mat,
        (((((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4) -
          1) /
         *(unsigned int *)(ctx + 0x30)));
    pac_continueDmaTag();
    pacTagCount += 1;
}

extern char D_0054F648[];
extern char D_0054F670[];
extern char D_0054F688[];
extern char D_0054F698[];
extern char D_0054F6D0[];

/* listing rows 1166-1194. 192 is the DMA chain's qword budget; the ROM's
   compare is against a register, so it is a local and not a literal.
   D_0054F698 is "gif over! cut! %d/%d polys:%d/%d fchain:%d vif+gif:%d":
   the last field is the qword count plus the gif tags the chain already
   holds plus the one about to be opened. */
void pac_checkDivide(int num, char *shp, char *mat)
{
    int limit = 192;
    char *ctx;
    unsigned int qwc;

    ctx = pacWork;
    if (*(int *)(ctx + 0x30) * num > limit) {
        debug_StdPrintfDummy(D_0054F648, *(int *)(ctx + 0x30) * num);
        debug_assert(D_0054F400, 1172);
        __assert(D_0054F400, 1172, D_0063A120);
    }
    qwc = ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4;
    if (qwc + *(int *)(ctx + 0x30) * num > limit) {
        pac_continueTag(shp, mat);
        debug_StdPrintfDummy(
            D_0054F670,
            ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4,
            pacStripCount);
        debug_StdPrintfDummy(D_0054F688);
        pacStripCount = 0;
    } else if ((qwc - 1) / *(unsigned int *)(ctx + 0x30) * *(int *)(ctx + 0x34) + 1 +
                   *(int *)(ctx + 0x34) * num >
               limit) {
        debug_StdPrintfDummy(
            D_0054F698, qwc + *(int *)(ctx + 0x30) * num, limit, pacPolyCount, *(int *)(ctx + 0x30),
            pacStripCount,
            qwc + ((qwc - 1) / *(unsigned int *)(ctx + 0x30) * *(int *)(ctx + 0x34) + 1));
        pac_continueTag(shp, mat);
        debug_StdPrintfDummy(
            D_0054F670,
            ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4,
            pacStripCount);
        debug_StdPrintfDummy(D_0054F688);
        pacStripCount = 0;
    } else if (*(int *)(ctx + 0x30) * num >= 256) {
        debug_StdPrintfDummy(D_0054F6D0);
        pac_continueTag(shp, mat);
        debug_StdPrintfDummy(
            D_0054F670,
            ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4,
            pacStripCount);
        debug_StdPrintfDummy(D_0054F688);
        pacStripCount = 0;
    }
}

extern char D_0054F738[];

typedef struct {
    unsigned int b0 : 1;
} ShpFlags;

/* The context's counter pair at +0x30 and the state word at +0x38 are one
   qword region that the TU reads both as 32-bit counters and as a 64-bit
   state mask. */
typedef union {
    unsigned long long ul;
    int w[2];
} PacState;

void pac_countOneVertexPacketSize(char *shp, char *mat)
{
    {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x30))->w[0] = 1;
        ((PacState *)(ctx + 0x38))->ul |= 1;
    }
    if (((int)(*(long long *)(shp + 0x60) >> 5) & 3) != 0 || ((ShpFlags *)(shp + 0x60))->b0 == 1 ||
        (mat != 0 && *(short *)(mat + 0x4C) >= 0)) {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 2;
    } else {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x38))->ul &= ~2;
    }
    if (((ShpFlags *)(shp + 0x60))->b0 == 1) {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 4;
    } else {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x38))->ul &= ~4;
    }
    if (((int)(*(long long *)(shp + 0x60) >> 7) & 1) != 0) {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 8;
    } else {
        pac_error(D_0054F738, 5);
    }
    if (((int)(*(long long *)(shp + 0x60) >> 8) & 1) != 0) {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 0x10;
    } else {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul &= ~0x10;
    }
    {
        char *ctx = pacWork;
        ((PacState *)(ctx + 0x30))->w[1] = 3;
    }
}

extern char D_0054F6E8[];
extern char D_0054F718[];
extern char D_0054F758[];
extern char D_0054F780[];
extern char D_0054F7A8[];
extern char D_0054F7C8[];
extern char D_0063A130[];
extern int D_0063A0F8;
extern float D_0063A3DC;
extern void malloc_MemCpy(int dst, int src, int n);
extern void iosFree(int p);
extern void debug_assertMessage(char *file, int line, char *msg);
extern void pac_countOneVertexPacketSize(char *shp, char *mat);
extern int pac_makeNormalStrip(char *obj, short *p, int n);
extern int pac_makeClusterStrip(char *obj, short *p, int n);

/* listing rows 1207-1219: a static inline above pac_makeStrip that copies a
   finished packet down into a fresh seki-heap block. */
static inline int pac_moveToSeki(int src, int size)
{
    int p;

    p = mallocseki(size);
    if (p == 0)
        debug_Assert(D_0054F6E8);
    debug_StdPrintfDummy(D_0054F718, src, p, size);
    if (src != p)
        malloc_MemCpy(p, src, size);
    return p;
}

int pac_makeStrip(int *out, char *obj, char **tbl, int shpno, int matno, int line)
{
    char buf[1024];
    int num;
    int dst;
    char *mat;
    char *shp;
    int pkt;
    short *p;
    int n;
    int i;
    int first;
    int size;
    int sz;
    int used;
    int packetSize;
    char *ctx;
    float t0;

    num = *(int *)(obj + 0x104);
    dst = 0;
    mat = 0;
    shp = tbl[0] + shpno * 0x70;
    pacStripCount = 0;
    if (matno != -1) {
        mat = tbl[1] + matno * 0x50;
    }
    pac_countOneVertexPacketSize(shp, mat);
    pkt = mallocsekistage(0x100000);
    if (pkt == 0)
        debug_Assert(D_0054F758);
    pac_openDmaTag(pkt);
    t0 = debug_GetTimerSec();
    for (i = 0; i < num; i++) {
        p = ((short **)*(int *)(obj + 0x100))[i];
        n = p[0];
        first = 0;
        while (n >= 3) {
            p += 8;
            if (p[7] == matno) {
                if (matno == -1)
                    debug_Assert(D_0054F780, line);
                if (p[6] == shpno) {
                    if (first != 0)
                        pac_checkDivide(n, shp, mat);
                    else
                        first = 1;
                    if ((*(int *)(shp + 0x60) & 1) == 0)
                        sz = pac_makeNormalStrip(obj, p, n);
                    else
                        sz = pac_makeClusterStrip(obj, p, n);
                    pacPolyCount += sz;
                    pacStripCount += 1;
                }
            }
            p += n * 8;
            n = p[0];
        }
    }
    D_0063A3DC += debug_GetTimerSec() - t0;
    size = pac_closeTag(shp, mat);
    ctx = pacWork;
    used = *(int *)(ctx + 0x2C) - pkt;
    if (D_0063A0F8 < used) {
        D_0063A0F8 = used;
        debug_StdPrintfDummy(D_0054F7A8, used);
    }
    /* D_0054F7C8 carries two conversions, "%s" for the object and "0x%x" for
       the size, so the recomputed size is sprintf's fourth argument. */
    packetSize = *(int *)(ctx + 0x2C) - pkt;
    if (0x100000 < packetSize) {
        sprintf(buf, D_0054F7C8, ctx, packetSize);
        debug_assertMessage(D_0054F400, 1362, buf);
        __assert(D_0054F400, 1362, D_0063A130);
    }
    if (size > 0) {
        if (malloc_GetPartition() == 0) {
            dst = pac_moveToSeki(pkt & 0x0FFFFFFF, size);
            iosFree(pkt & 0x0FFFFFFF);
        } else {
            dst = reallocseki(pkt & 0x0FFFFFFF, size);
        }
    } else {
        iosFree(pkt & 0x0FFFFFFF);
    }
    *out = dst;
    return size;
}

/* The material table entry's 64-bit mode word at +0x60: the same qword
   pac_setMaterialPacket reads back as its three mode selectors. */
typedef struct MatEnt {
    char pad0[0x60];
    unsigned long long b0 : 1;
    unsigned long long b1 : 2;
    unsigned long long b3 : 2;
    unsigned long long b5 : 2;
    unsigned long long b7 : 1;
    unsigned long long b8 : 1;
    unsigned long long b9 : 1;
    char pad1[8];
} MatEnt;

void pac_setMaterialPacket(MatEnt *ent)
{
    char *p;

    p = (char *)ent;
    *(int *)p = 0;
    p += 4;
    *(int *)p = 0;
    p += 4;
    *(int *)p = 0;
    p += 4;
    *(int *)p = 0x6C048000;
    p += 4;
    *(long long *)p = 0x1000000000008003LL;
    p += 8;
    *(long long *)p = 14;
    p += 8;
    switch ((int)(*(long long *)((char *)ent + 0x60) >> 1) & 3) {
    case 2:
        *(long long *)p = 0x8000000048LL;
        p += 8;
        break;
    case 3:
        *(long long *)p = 0x8000000042LL;
        p += 8;
        break;
    case 1:
        *(long long *)p = 0x8000000044LL;
        p += 8;
        break;
    default:
        *(long long *)p = 0x8000000044LL;
        p += 8;
        break;
    }
    *(long long *)p = 0x42;
    p += 8;
    switch ((int)(*(long long *)((char *)ent + 0x60) >> 3) & 3) {
    case 0:
        *(long long *)p = 5;
        p += 8;
        break;
    case 1:
        *(long long *)p = 4;
        p += 8;
        break;
    case 2:
        *(long long *)p = 1;
        p += 8;
        break;
    default:
        *(long long *)p = 0;
        p += 8;
        break;
    }
    *(long long *)p = 8;
    p += 8;
    *(long long *)p = (int)(*(long long *)((char *)ent + 0x60) >> 9) & 1;
    p += 8;
    *(long long *)p = 0x4A;
    p += 8;
    *(int *)p = 0x14000000;
    p += 4;
    *(int *)p = 0;
    p += 4;
    *(int *)p = 0;
    *(int *)(p + 4) = 0;
}

typedef struct MatSrc {
    char pad0[5];
    unsigned char f_5;
    unsigned char f_6;
    char pad1[5];
    float f_C;
} MatSrc;

typedef struct MatObj {
    char pad0[0xA0];
    int f_A0;
    char pad1[0xC];
    int f_B0;
    char pad2[0xC];
    int f_C0;
    char pad3[0xC];
    MatSrc *f_D0;
    unsigned int f_D4;
} MatObj;

extern void pac_setMaterialPacket(MatEnt *ent);

typedef struct MatTab {
    MatEnt *f_0;
    char pad0[0xC];
    short f_10;
} MatTab;

extern int D_0063B1A8;

void pac_makeMaterialTable(MatTab *out, MatObj *obj, int p2, int p3, unsigned int p4)
{
    MatEnt *tbl;
    MatEnt *ent;
    MatSrc *src;
    unsigned int i;
    unsigned int flag;
    int a;
    int x;

    tbl = (MatEnt *)mallocseki(obj->f_D4 * 0x70);
    for (i = 0; i < obj->f_D4; i++) {
        ent = &tbl[i];
        src = (MatSrc *)(i * 0x10 + (int)obj->f_D0);
        flag = src->f_C >= 0.501960814f;
        a = src->f_5;
        x = src->f_6 == 0;
        if (p4 != 0)
            x = D_0063B1A8 == 1;
        ent->b0 = p4;
        ent->b1 = flag * p3;
        ent->b3 = (a < 4) ? a : 3;
        ent->b9 = x;
        ent->b5 = obj->f_A0 ? p2 : 0;
        ent->b7 = obj->f_B0 != 0;
        ent->b8 = obj->f_C0 != 0;
        pac_setMaterialPacket(ent);
    }
    out->f_0 = tbl;
    out->f_10 = obj->f_D4;
}

typedef struct MatLine {
    MatEnt *f_0;
    char pad0[8];
    short f_C;
} MatLine;

void pac_makeMaterialTableLine(MatLine *out, MatObj *obj, int p2, int p3, unsigned int p4)
{
    MatEnt *tbl;
    MatEnt *ent;
    MatSrc *src;
    unsigned int i;
    unsigned int flag;
    short a;
    int x;

    tbl = (MatEnt *)mallocseki(obj->f_D4 * 0x70);
    for (i = 0; i < obj->f_D4; i++) {
        ent = &tbl[i];
        src = (MatSrc *)(i * 0x10 + (int)obj->f_D0);
        flag = src->f_C >= 0.501960814f;
        a = src->f_5;
        x = src->f_6 == 0;
        ent->b0 = p4;
        ent->b1 = flag * p3;
        if (a >= 4)
            a = 3;
        ent->b3 = a;
        ent->b9 = x;
        ent->b5 = obj->f_A0 ? p2 : 0;
        ent->b7 = obj->f_B0 != 0;
        ent->b8 = obj->f_C0 != 0;
        pac_setMaterialPacket(ent);
    }
    out->f_0 = tbl;
    out->f_C = obj->f_D4;
}

extern char D_0054F820[];
extern char D_0063A138[];
extern char D_0063A140[];
extern char D_0063A148[];

void pac_getTextureInfo(char *m, char *info, int idx)
{
    int n;

    if (idx != -1) {
        sprintf(m, D_0063A138, *(int *)(info + 0xE0) + idx * 0x90);
        *(short *)(m + 0x48) = tex_GetTextureNo(m);
        tex_GetTextureData(*(short *)(m + 0x48));
        if (*(short *)(m + 0x48) != -1) {
            *(unsigned short *)(m + 0x4E) |= 1;
            sprintf(m + 0x18, D_0063A140, m);
            n = tex_GetTextureNo(m + 0x18);
            if (n == -1) {
                *(short *)(m + 0x4A) = n;
                *(char *)(m + 0x18) = 0;
                *(unsigned short *)(m + 0x4E) &= 0xFFFD;
            } else {
                *(short *)(m + 0x4A) = tex_GetTextureNo(m + 0x18);
                *(unsigned short *)(m + 0x4E) |= 2;
            }
            sprintf(m + 0x30, D_0063A148, m);
            n = tex_GetTextureNo(m + 0x30);
            if (n == -1) {
                *(short *)(m + 0x4C) = n;
                *(unsigned short *)(m + 0x4E) &= 0xFFFB;
                *(char *)(m + 0x30) = 0;
            } else {
                *(short *)(m + 0x4C) = tex_GetTextureNo(m + 0x30);
                *(unsigned short *)(m + 0x4E) |= 4;
            }
        } else {
            debug_Assert(D_0054F820, m);
        }
    } else {
        *(unsigned short *)(m + 0x4E) |= 1;
    }
}

/* One 16-byte shape-table qword. Four ints, so 4-byte aligned: the ROM's
   copy of it comes out as ldl/ldr plus sdl/sdr. */
typedef struct {
    int _0[4];
} PacQw;

/* One 32-byte cluster node. 8-byte aligned (the ROM copies it with ld/sd),
   terminated by -1 in the word at +0x10. */
typedef struct {
    long long _0[2];
    int f10;
    int _14[3];
} PacNode;

void pac_makeShapeTable(int a0, char *obj)
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

    *(int *)(obj + 0x174) = mallocseki(*(int *)(obj + 0x94) * 16);
    for (i = 0; i < *(unsigned int *)(obj + 0x94); i++)
        _CopyVector(*(char **)(obj + 0x174) + i * 16, *(char **)(obj + 0x90) + i * 16);
    *(int *)(obj + 0x178) = mallocseki(*(int *)(obj + 0xA4) * 16);
    for (i = 0; i < *(unsigned int *)(obj + 0xA4); i++)
        _CopyVector(*(char **)(obj + 0x178) + i * 16, *(char **)(obj + 0xA0) + i * 16);
    *(int *)(obj + 0x90) = mallocseki(*(int *)(obj + 0x94) * 16);
    for (i = 0; i < *(unsigned int *)(obj + 0x94); i++)
        _CopyVector(*(char **)(obj + 0x90) + i * 16, *(char **)(obj + 0x174) + i * 16);
    *(int *)(obj + 0xA0) = mallocseki(*(int *)(obj + 0xA4) * 16);
    for (i = 0; i < *(unsigned int *)(obj + 0xA4); i++)
        _CopyVector(*(char **)(obj + 0xA0) + i * 16, *(char **)(obj + 0x178) + i * 16);
    tbl = (PacQw **)mallocseki(*(int *)(obj + 0x104) * 4);
    for (i = 0; i < *(unsigned int *)(obj + 0x104); i++) {
        p = ((short **)*(int *)(obj + 0x100))[i];
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
            tbl[i][k] = ((PacQw **)*(int *)(obj + 0x100))[i][k];
    }
    *(int *)(obj + 0x100) = (int)tbl;
    ntbl = (PacNode **)mallocseki(*(int *)(obj + 0x124) * 4);
    for (i = 0; i < *(unsigned int *)(obj + 0x124); i++) {
        ntbl[i] = 0;
        q = ((PacNode **)*(int *)(obj + 0x120))[i];
        if (q != 0) {
            r = q;
            for (m = 0; r->f10 != -1; r++)
                m++;
            m += 2;
            ntbl[i] = (PacNode *)mallocseki(m * 32);
            for (r = ((PacNode **)*(int *)(obj + 0x120))[i], dst = ntbl[i];; r++, dst++) {
                *dst = *r;
                if (r->f10 == -1)
                    break;
            }
        }
    }
    *(int *)(obj + 0x120) = (int)ntbl;
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_makePacket);

void pac_MakePacket(char *a0)
{
    char *p = *(char **)(a0 + 0x854);
    pac_makePacket(p, *(int *)(*(char **)(a0 + 0x874) + 0xF0), *(signed char *)(p + 0x2F) > 0);
}

inline void pac_Init(void)
{
    pacUnusedWord = 0;
}
