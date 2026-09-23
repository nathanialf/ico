#include "common.h"
#include "debug.h"
#include "Basic.h"
#include "DisplayP2O.h"
#include <stdio.h>

/* RECONSTRUCTION, PUBLIC SDK NAMING RUNG for the shape (libvu0's
   sceVu0FVECTOR, a 16-byte aligned float[4]); the name is ours.  The ROM pins
   the alignment: MakeBoundingBox's bounds sit at 16-byte stack slots and its
   last loop writes self->bb through one pointer at +0x5C.  expand_expr builds
   an array element's address as base plus constant first only when the
   element's alignment is the float's own, which is the four-pointer loop a
   plain float[4] gives. */
typedef float Vec[4] __attribute__((aligned(16)));

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
    int f24;      /* 0x24 */
    PObjPkt *pkt; /* 0x28 */
    short f2C;    /* 0x2C */
    /* 0x2E and 0x2F, the sub-object count and a second byte, as one short's
       two bitfields rather than chars: a character type's alias set 0 would
       let every float store kill them, where the ROM keeps the count's lbu
       live across MakeBoundingBox's loops and lets the D_004FBA80 float
       load hoist past InitPObj's store to 0x2F */
    short f2E : 8;          /* 0x2E */
    unsigned short f2F : 8; /* 0x2F */

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
    sprintf(buf, "%s", &name[top]);
    sprintf(name, "%s", buf);
    for (i = 0; name[i] != 0; i++) {
        if (name[i] == '.') {
            name[i] = 0;
            break;
        }
    }
}

/* MakeBoundingBox: one axis-aligned box per sub-object into the block it
   allocates at 0x44, plus the whole object's box in self->bb.  The line map
   (SRCFILE.TXT rows 55 to 107) gives the statement boundaries used here. */
void MakeBoundingBox(PObj *self)
{
    Vec mn;
    Vec mx;
    Vec gmn;
    Vec gmx;
    Vec *out;
    float *p;
    PObjSub *sub;
    int i;
    unsigned int j;
    int l;

    self->f44 = (Vec(*)[8])mallocseki(self->f2E << 7);

    gmn[0] = gmn[1] = gmn[2] = 16777215.0f;
    gmx[0] = gmx[1] = gmx[2] = -16777215.0f;

    for (i = 0; i < self->f2E; i++) {
        sub = &self->sub[i];
        out = self->f44[i];

        mn[0] = mn[1] = mn[2] = 16777215.0f;
        mx[0] = mx[1] = mx[2] = -16777215.0f;

        for (j = 0; j < sub->f94; j++) {
            p = sub->f90[j];
            if (p[0] < mn[0])
                mn[0] = p[0];
            if (mx[0] < p[0])
                mx[0] = p[0];
            if (p[1] < mn[1])
                mn[1] = p[1];
            if (mx[1] < p[1])
                mx[1] = p[1];
            if (p[2] < mn[2])
                mn[2] = p[2];
            if (mx[2] < p[2])
                mx[2] = p[2];
            if (p[0] < gmn[0])
                gmn[0] = p[0];
            if (gmx[0] < p[0])
                gmx[0] = p[0];
            if (p[1] < gmn[1])
                gmn[1] = p[1];
            if (gmx[1] < p[1])
                gmx[1] = p[1];
            if (p[2] < gmn[2])
                gmn[2] = p[2];
            if (gmx[2] < p[2])
                gmx[2] = p[2];
        }

        for (l = 0; l < 8; l++) {
            if (l & 1)
                out[l][0] = mn[0];
            else
                out[l][0] = mx[0];
            if (l & 2)
                out[l][1] = mn[1];
            else
                out[l][1] = mx[1];
            if (l & 4)
                out[l][2] = mn[2];
            else
                out[l][2] = mx[2];
            out[l][3] = 1.0f;
        }
    }

    for (l = 0; l < 8; l++) {
        if (l & 1)
            self->bb[l][0] = gmn[0];
        else
            self->bb[l][0] = gmx[0];
        if (l & 2)
            self->bb[l][1] = gmn[1];
        else
            self->bb[l][1] = gmx[1];
        if (l & 4)
            self->bb[l][2] = gmn[2];
        else
            self->bb[l][2] = gmx[2];
        self->bb[l][3] = 1.0f;
    }
}

/* The 0x8C-stride model table this member shares with charFileManager: only
   the three columns MakePacket reads are spelled out here. */

extern PObjMdl D_004FBA80[];

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
    debug_StdPrintfDummy("end of packet making...\n");
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

    debug_StdPrintfDummy("\033[33mobject info : adrs(%p) objnum(%d) clstnum(%d)\n", h, h->f8,
                         h->fC);

    p = (PObj *)mallocseki(0xD0);
    sprintf((char *)p, "%s", name);
    TidyPObjName((char *)p);

    debug_StdPrintfDummy("            : object name (%s)\n", (char *)p);
    debug_StdPrintfDummy("            : object table (%p)\033\n", list);
    if (tex != 0)
        debug_StdPrintfDummy("            : texture table (%p)\033[m\n", tex);
    else
        debug_StdPrintfDummy("\033[m");

    if (tex != 0) {
        for (i = 0; i < h->f14; i++)
            tex[i] += (int)h;
    }

    debug_StdPrintfDummy("Solve object address. %p\n", list);

    for (i = 0; i < h->f8; i++) {
        list[i] += (int)h;
        o = (ObjRec *)list[i];

        if (o->f80 != *(int *)"OBJH") {
            debug_StdPrintfDummy("allocPObj:Invalid Object.\n");
            debug_assert(__FILE__, 249);
            __assert(__FILE__, 249, "FALSE");
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

/* kept local: this TU's uses of _AddVector do not fit the prototype in Matrix.h */
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
        debug_StdPrintfDummy("free object\n");
    } while (0);
}
