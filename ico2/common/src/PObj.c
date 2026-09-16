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
    float f84;           /* 0x84 */
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
    long long _0[0x12];
    Vec *f90;         /* 0x90 */
    unsigned int f94; /* 0x94 */
    long long _98[(0x180 - 0x98) / 8];
} PObjSub;

typedef struct PObj {
    char _0[0x24];
    int f24;              /* 0x24 */
    PObjPkt *pkt;         /* 0x28 */
    short f2C;            /* 0x2C */
    char f2E;             /* 0x2E */
    unsigned int f2F : 8; /* 0x2F; a bitfield, not a char: the ROM lets the
                             D_004FBA80 float load hoist past this store, which
                             a character type's alias set 0 would forbid */

    union {
        long long ll;

        struct {
            short nloop; /* 0x30 */
            short _32;
            float f34; /* 0x34 */
        } v;
    } tag; /* 0x30 */

    float f38;     /* 0x38 */
    float f3C;     /* 0x3C */
    PObjSub *sub;  /* 0x40 */
    Vec (*f44)[8]; /* 0x44 */
    char _48[8];
    Vec bb[8]; /* 0x50 */
} PObj;

extern char D_0063C0D8[]; /* the %s format, .sdata */
extern int sprintf(char *buf, const char *fmt, ...);

/* The file's own name tidier: rows 26 to 39 sit inside AllocPObj's span and the
   census lists no out-of-line copy, so it is defined here and inlined once. */
static __inline__ void TidyPObjName(char *name)
{
    char buf[256];
    int i;
    int top;

    top = 0;
    for (i = 0;; i++) {
        if (name[i] == 0)
            break;
        if (name[i] == '/')
            top = i + 1;
    }
    sprintf(buf, D_0063C0D8, &name[top]);
    sprintf(name, D_0063C0D8, buf);
    for (i = 0; name[i] != 0; i++) {
        if (name[i] == '.') {
            name[i] = 0;
            break;
        }
    }
}

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

extern char D_00635FE0[];
extern char D_00636018[];
extern char D_00636038[];
extern char D_00636060[];
extern char D_00636088[];
extern char D_006360A8[];
extern char D_006360C8[];
extern char D_0063C0E0[];
extern char D_0063C0E8[];
extern char D_0063C0F0[];
extern void MakeBoundingBox(PObj *p);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

typedef struct ObjHdr { /* the loaded model file image */
    char _0[4];
    int f4;           /* 0x4  object table, file offset then pointer */
    unsigned int f8;  /* 0x8  objnum */
    unsigned int fC;  /* 0xC  clstnum */
    int f10;          /* 0x10 texture table, file offset then pointer */
    unsigned int f14; /* 0x14 */
} ObjHdr;

typedef struct ObjEnt { /* the 0x10 stride records the 0xF0 table holds */
    void *p;            /* 0x0 */
    char _4[0xC];
} ObjEnt;

typedef struct ObjRec {
    char _0[0x80];
    int f80; /* 0x80 */
    char _84[0xC];
    char *f90; /* 0x90 */
    char _94[0xC];
    char *fA0; /* 0xA0 */
    char _A4[0xC];
    char *fB0; /* 0xB0 */
    char _B4[0xC];
    char *fC0; /* 0xC0 */
    char _C4[0xC];
    char *fD0; /* 0xD0 */
    char _D4[0xC];
    char *fE0; /* 0xE0 */
    char _E4[0xC];
    char *fF0;        /* 0xF0 */
    unsigned int fF4; /* 0xF4 */
    char _F8[8];
    char *f100;        /* 0x100 */
    unsigned int f104; /* 0x104 */
    char _108[8];
    char *f110; /* 0x110 */
    char _114[0xC];
    char *f120;        /* 0x120 */
    unsigned int f124; /* 0x124 */
} ObjRec;

/* Rows 123 to 126: the sub-record table allocate and copy, inlined once. */
static __inline__ void AllocPObjSubs(PObj *p, int *list)
{
    int i;

    p->sub = (PObjSub *)mallocseki(p->f2E * sizeof(PObjSub));

    for (i = 0; i < p->f2E; i++)
        p->sub[i] = *(PObjSub *)list[i];
}

/* Rows 138 to 146: the header fields of a freshly allocated PObj. */
static __inline__ void InitPObjHeader(PObj *p, ObjHdr *h, int n)
{
    p->f24 = (int)h;
    p->pkt = 0;
    p->f2C = 0;
    p->f2E = h->f8;
    p->f2F = h->fC;
    p->tag.ll &= ~0x30000LL;
    p->tag.ll &= ~0x4000000LL;
    p->f3C = D_004FBA80[n].f84;
}

PObj *AllocPObj(ObjHdr *h, char *name, int n)
{
    PObj *p;
    int *tex;
    int *list;
    ObjRec *o;
    unsigned int i;
    unsigned int j;

    h->f4 += (int)h;

    if (h->f10 != 0)
        h->f10 += (int)h;
    tex = (int *)h->f10;

    list = (int *)h->f4;

    debug_StdPrintfDummy(D_00635FE0, h, h->f8, h->fC);

    p = (PObj *)mallocseki(0xD0);
    sprintf((char *)p, D_0063C0D8, name);
    TidyPObjName((char *)p);

    debug_StdPrintfDummy(D_00636018, (char *)p);
    debug_StdPrintfDummy(D_00636038, list);
    if (tex != 0)
        debug_StdPrintfDummy(D_00636060, tex);
    else
        debug_StdPrintfDummy(D_0063C0E0);

    if (tex != 0) {
        for (i = 0; i < h->f14; i++)
            tex[i] += (int)h;
    }

    debug_StdPrintfDummy(D_00636088, list);

    for (i = 0; i < h->f8; i++) {
        list[i] += (int)h;
        o = (ObjRec *)list[i];

        if (o->f80 != *(int *)D_0063C0E8) {
            debug_StdPrintfDummy(D_006360A8);
            debug_assert(D_006360C8, 249);
            __assert(D_006360C8, 249, D_0063C0F0);
        }

        o->f90 += (int)h;
        o->fA0 += (int)h;
        o->fB0 += (int)h;
        o->fC0 += (int)h;
        o->fD0 += (int)h;
        o->fE0 += (int)h;
        o->fF0 += (int)h;
        for (j = 0; j < o->fF4; j++)
            ((ObjEnt *)o->fF0)[j].p = (void *)((int)((ObjEnt *)o->fF0)[j].p + (int)h);
        o->f100 += (int)h;
        for (j = 0; j < o->f104; j++)
            ((void **)o->f100)[j] = (void *)((int)((void **)o->f100)[j] + (int)h);
        o->f110 += (int)h;
        o->f120 += (int)h;
        for (j = 0; j < o->f124; j++) {
            if (((void **)o->f120)[j] != 0)
                ((void **)o->f120)[j] = (void *)((int)((void **)o->f120)[j] + (int)h);
        }
    }

    InitPObjHeader(p, h, n);
    AllocPObjSubs(p, list);

    MakeBoundingBox(p);

    return p;
}

extern void _AddVector(Vec d, Vec a, Vec b);

PObj *InitPObj(int a0, int a1, int n)
{
    PObj *p;
    Vec v;
    int num;
    int i;
    int j;

    p = AllocPObj((ObjHdr *)a0, (char *)a1, n);
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
