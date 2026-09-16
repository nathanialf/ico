#include "common.h"

extern const char D_006360D8[];
extern void debug_StdPrintfDummy();

typedef float Vec[4];

typedef struct PObjMdl {
    char _0[0x70];
    float f70;           /* 0x70 */
    float f74;           /* 0x74 */
    float f78;           /* 0x78 */
    float f7C;           /* 0x7C */
    float f80;           /* 0x80 */
    char _84[4];         /* 0x84 */
    unsigned int b0 : 4; /* 0x88 */
    unsigned int b4 : 4;
    unsigned int b8 : 4;
    unsigned int b12 : 20;
} PObjMdl;

typedef struct PktHdr {
    char _0[0xF0];
    int kind; /* 0xF0 */
} PktHdr;

typedef struct PObjPkt {
    char _0[0x854];
    struct PObj *owner; /* 0x854 */
    char _858[0x18];
    void *f870;   /* 0x870 */
    PktHdr *f874; /* 0x874 */
} PObjPkt;

typedef struct PObjSub { /* 0x180 stride, hung off the PObj at 0x40 */
    char _0[0x90];
    Vec *f90;         /* 0x90 */
    unsigned int f94; /* 0x94 */
    char _98[0x180 - 0x98];
} PObjSub;

typedef struct PObj {
    char _0[0x24];
    int f24;      /* 0x24 */
    PObjPkt *pkt; /* 0x28 */
    char _2C[2];
    char f2E; /* 0x2E */
    char _2F[1];

    union {
        long long ll;

        struct {
            short nloop; /* 0x30 */
            short _32;
            float f34; /* 0x34 */
        } v;
    } tag; /* 0x30 */

    float f38; /* 0x38 */
    char _3C[4];
    PObjSub *sub;  /* 0x40 */
    Vec (*f44)[8]; /* 0x44 */
    char _48[8];
    Vec bb[8]; /* 0x50 */
} PObj;

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/PObj", MakeBoundingBox);

/* The 0x8C-stride model table this member shares with charFileManager: only
   the three columns MakePacket reads are spelled out here. */

extern PObjMdl D_004FBA80[];
extern char D_00635FC0[];
extern char *mallocseki(int size);
extern void p2o_MakePacket(PObjPkt *q);

void MakePacket(PObj *p, int n)
{
    PObjPkt *q;

    p->tag.v.nloop = n;
    p->tag.ll = (p->tag.ll & ~0x3C0000LL) | ((long long)D_004FBA80[n].b4 << 18);
    p->tag.ll = (p->tag.ll & ~0x3C00000LL) | ((long long)D_004FBA80[n].b8 << 22);
    p->tag.v.f34 = D_004FBA80[n].f7C;
    p->f38 = D_004FBA80[n].f80;

    q = (PObjPkt *)mallocseki(0x880);
    p->pkt = q;
    q->f874 = (PktHdr *)mallocseki(0x100);
    q->f874->kind = D_004FBA80[n].b0;

    q->owner = p;
    q->f870 = mallocseki(p->f2E * 80);
    if (q->f874->kind != 4) {
        if (p->f24 != 0)
            p2o_MakePacket(q);
    }
    debug_StdPrintfDummy(D_00635FC0);
}

/* The file's own vector setter, defined between MakePacket and AllocPObj and
   inlined into InitPObj (SRCFILE.TXT rows 181 and 183 inside InitPObj's span). */
static __inline__ void SetPObjVector(Vec v, float x, float y, float z)
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/ico2/common/src/PObj", AllocPObj);

extern void _AddVector(Vec d, Vec a, Vec b);
extern PObj *AllocPObj(int a0, int a1, int n);

PObj *InitPObj(int a0, int a1, int n)
{
    PObj *p;
    Vec v;
    int num;
    int i;
    int j;

    p = AllocPObj(a0, a1, n);
    SetPObjVector(v, D_004FBA80[n].f70, D_004FBA80[n].f74, D_004FBA80[n].f78);
    num = p->f2E;
    for (i = 0; i < num; i++) {
        PObjSub *g = &p->sub[i];
        int cnt = g->f94;

        for (j = 0; j < cnt; j++)
            _AddVector(g->f90[j], g->f90[j], v);
        for (j = 0; j < 8; j++)
            _AddVector(p->f44[i][j], p->f44[i][j], v);
    }
    MakePacket(p, n);
    return p;
}

void FreePObj(void)
{
    do {
        debug_StdPrintfDummy(D_006360D8);
    } while (0);
}
