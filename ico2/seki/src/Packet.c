#include "common.h"
#include "debug.h"
#include "Basic.h"
#include "Texture.h"

extern char D_0054F5C0[];
extern char D_0067C010[];
extern char D_0054F5D0[];

#include "Packet.h"
#include <stdio.h>

extern int D_0063C154;
extern char D_0054F200[];
extern char D_0054F218[];
extern char D_0063A100[];
extern char D_0063A108[];
extern char D_0063A110[];
extern char D_0063A118[];
extern int fptodp(float v);

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
            debug_StdPrintfDummy(D_0063A110, fptodp(((float *)p)[i]));
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
                char *ctx = D_0067C010;
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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_makeBoundingBox);

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
        debug_Assert(D_0054F310, D_0067C010, name);
        break;
    case 1:
        debug_Assert(D_0054F340, D_0067C010, name);
        break;
    case 2:
        debug_Assert(D_0054F370, D_0067C010, name);
        break;
    case 3:
        debug_Assert(D_0054F3A0, D_0067C010, name);
        break;
    case 4:
        debug_Assert(D_0054F3D8, D_0067C010, name);
        break;
    }
    debug_assert(D_0054F400, 684);
    __assert(D_0054F400, 684, D_0063A120);
}

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_makeNormalStrip);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_getWeight);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_makeClusterStrip);

void pac_openDmaTag(int a0)
{
    register int mask = 0x0FFFFFFF;
    char *ctx = D_0067C010;
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
    char *ctx = D_0067C010;
    *(int *)(*(int *)(ctx + 0x24)) = 0;
    *(int *)(*(int *)(ctx + 0x24) + 4) = (a0 << 16) | 0x6C008000;
    debug_StdPrintfDummy(D_0054F5D0, *(int *)(*(int *)(ctx + 0x24)),
                         *(int *)(*(int *)(ctx + 0x24) + 4), *(int *)(ctx + 0x24), a0);
}

void pac_setVifEndCode(void)
{
    char *ctx = D_0067C010;
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
    ctx = D_0067C010;
    ((PacketWord *)(*(int *)(ctx + 0x28)))->ul =
        D_0054F5F0[tme].w0 |
        ((0xCULL | ((unsigned long long)tme << 4) | ((unsigned long long)abe << 6)) << 47) | nloop;
    ((PacketWord *)(*(int *)(ctx + 0x28) + 8))->ul = D_0054F5F0[tme].w1;
    debug_StdPrintfDummy(D_0054F610);
    debug_StdPrintfDummy(*(int *)(ctx + 0x28));
    debug_StdPrintfDummy(D_0063A128, nloop);
}

extern unsigned int D_0063C144;
extern unsigned int D_0063C14C;

/* listing rows 993/995: a static inline sitting between pac_openDmaTag and
   pac_setVifCode that zeroes the open DMA tag's two words. It reads the
   context pointer again for the second word because the first store aliases
   it. */
static inline void pac_closeDmaTag(void)
{
    ((unsigned int *)*(unsigned int *)(D_0067C010 + 0x20))[0] = 0;
    ((unsigned int *)*(unsigned int *)(D_0067C010 + 0x20))[1] = 0;
}

int pac_closeTag(char *shp, char *mat)
{
    char *ctx;
    unsigned int n;
    unsigned int qwc;

    ctx = D_0067C010;
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
    D_0063C144 += qwc * 16;
    D_0063C14C += 1;
    return qwc * 16;
}

extern char D_0054F620[];

/* listing rows 1043-1048: a static inline between pac_setVifEndCode and
   pac_closeTag that closes the VIF list and re-opens the DMA tag one qword
   further on. */
static inline void pac_continueDmaTag(void)
{
    char *ctx = D_0067C010;
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

    ctx = D_0067C010;
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
    D_0063C14C += 1;
}

extern char D_0054F648[];
extern char D_0054F670[];
extern char D_0054F688[];
extern char D_0054F698[];
extern char D_0054F6D0[];
extern unsigned int D_0063C148;
extern unsigned int D_0063C150;

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

    ctx = D_0067C010;
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
            D_0063C150);
        debug_StdPrintfDummy(D_0054F688);
        D_0063C150 = 0;
    } else if ((qwc - 1) / *(unsigned int *)(ctx + 0x30) * *(int *)(ctx + 0x34) + 1 +
                   *(int *)(ctx + 0x34) * num >
               limit) {
        debug_StdPrintfDummy(
            D_0054F698, qwc + *(int *)(ctx + 0x30) * num, limit, D_0063C148, *(int *)(ctx + 0x30),
            D_0063C150,
            qwc + ((qwc - 1) / *(unsigned int *)(ctx + 0x30) * *(int *)(ctx + 0x34) + 1));
        pac_continueTag(shp, mat);
        debug_StdPrintfDummy(
            D_0054F670,
            ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4,
            D_0063C150);
        debug_StdPrintfDummy(D_0054F688);
        D_0063C150 = 0;
    } else if (*(int *)(ctx + 0x30) * num >= 256) {
        debug_StdPrintfDummy(D_0054F6D0);
        pac_continueTag(shp, mat);
        debug_StdPrintfDummy(
            D_0054F670,
            ((*(unsigned int *)(ctx + 0x2C) & 0x0FFFFFFF) - *(unsigned int *)(ctx + 0x28)) >> 4,
            D_0063C150);
        debug_StdPrintfDummy(D_0054F688);
        D_0063C150 = 0;
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
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x30))->w[0] = 1;
        ((PacState *)(ctx + 0x38))->ul |= 1;
    }
    if (((int)(*(long long *)(shp + 0x60) >> 5) & 3) != 0 || ((ShpFlags *)(shp + 0x60))->b0 == 1 ||
        (mat != 0 && *(short *)(mat + 0x4C) >= 0)) {
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 2;
    } else {
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x38))->ul &= ~2;
    }
    if (((ShpFlags *)(shp + 0x60))->b0 == 1) {
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 4;
    } else {
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x38))->ul &= ~4;
    }
    if (((int)(*(long long *)(shp + 0x60) >> 7) & 1) != 0) {
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 8;
    } else {
        pac_error(D_0054F738, 5);
    }
    if (((int)(*(long long *)(shp + 0x60) >> 8) & 1) != 0) {
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul |= 0x10;
    } else {
        char *ctx = D_0067C010;
        ((PacState *)(ctx + 0x30))->w[0] += 1;
        ((PacState *)(ctx + 0x38))->ul &= ~0x10;
    }
    {
        char *ctx = D_0067C010;
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
    D_0063C150 = 0;
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
                    D_0063C148 += sz;
                    D_0063C150 += 1;
                }
            }
            p += n * 8;
            n = p[0];
        }
    }
    D_0063A3DC += debug_GetTimerSec() - t0;
    size = pac_closeTag(shp, mat);
    ctx = D_0067C010;
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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_setMaterialPacket);

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

INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_makeShapeTable);
INCLUDE_ASM("asm/nonmatchings/ico2/seki/src/Packet", pac_makePacket);

void pac_MakePacket(char *a0)
{
    char *p = *(char **)(a0 + 0x854);
    pac_makePacket(p, *(int *)(*(char **)(a0 + 0x874) + 0xF0), *(signed char *)(p + 0x2F) > 0);
}

inline void pac_Init(void)
{
    D_0063C154 = 0;
}
