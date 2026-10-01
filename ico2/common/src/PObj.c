#include "debug.h"
#include "Basic.h"
#include "DisplayP2O.h"
#include <stdio.h>
#include "debug_exception.h"
#include "Matrix.h"
#include "charFileManager.h"
#include <assert.h>

/* a 16-byte aligned float[4], the shape of libvu0's sceVu0FVECTOR */
typedef float Vec[4] __attribute__((aligned(16))); /* derived name */

typedef struct PktHdr { /* field names derived */
    char pad0[240];
    int kind; /* 0xF0 */
} PktHdr;     /* derived name */

typedef struct PObjPkt { /* field names derived */
    char pad0[2132];
    struct PObj *owner; /* 0x854 */
    char pad858[24];
    void *f870;   /* 0x870 */
    PktHdr *f874; /* 0x874 */
} PObjPkt;        /* derived name */

typedef struct PObjSub { /* field names derived */ /* 0x180 stride, hung off the PObj at 0x40 */
    long long _0[18];
    Vec *f90;         /* 0x90 */
    unsigned int f94; /* 0x94 */
    long long _98[(0x180 - 0x98) / 8];
} PObjSub; /* derived name */

typedef struct PObj { /* field names derived */
    char pad0[36];
    int f24;      /* 0x24 */
    PObjPkt *pkt; /* 0x28 */
    short f2C;    /* 0x2C */
    /* 0x2E and 0x2F, the sub-object count and a second byte, as one short's
       two bitfields */
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
    char pad48[8];
    Vec bb[8]; /* 0x50 */
} PObj;        /* derived name */

/* the file's own name tidier, inlined once, into AllocPObj */
static __inline__ void TidyPObjName(char *name) /* derived name */
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
   allocates at 0x44, plus the whole object's box in self->bb. */
static void MakeBoundingBox(PObj *self)
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

static void MakePacket(PObj *p, int n)
{
    PObjPkt *q;

    p->tag.v.nloop = n;
    p->tag.ll = (p->tag.ll & ~0x3C0000LL) | ((long long)modelData[n].bits4 << 18);
    p->tag.ll = (p->tag.ll & ~0x3C00000LL) | ((long long)modelData[n].bits8 << 22);
    p->tag.v.f34 = modelData[n].float7C;
    p->f38 = modelData[n].float80;

    q = (PObjPkt *)mallocseki(0x880);
    p->pkt = q;
    q->f874 = (PktHdr *)mallocseki(0x100);
    q->f874->kind = modelData[n].pktKind;

    q->owner = p;
    q->f870 = mallocseki(p->f2E * 80);
    if (q->f874->kind != 4) {
        if (p->f24 != 0)
            p2o_MakePacket(q);
    }
    debug_StdPrintfDummy("end of packet making...\n");
}

/* the file's own vector setter, inlined into InitPObj */
static __inline__ void SetPObjVector(Vec v, float x, float y, float z) /* derived name */
{
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
}

typedef struct ObjHdr { /* field names derived */ /* the loaded model file image */
    char pad0[4];
    int f4;           /* 0x4  object table, file offset then pointer */
    unsigned int f8;  /* 0x8  objnum */
    unsigned int fC;  /* 0xC  clstnum */
    int f10;          /* 0x10 texture table, file offset then pointer */
    unsigned int f14; /* 0x14 */
} ObjHdr;             /* derived name */

typedef struct ObjEnt { /* field names derived */ /* the 0x10 stride records the 0xF0 table holds */
    void *p;                                      /* 0x0 */
    char pad4[12];
} ObjEnt; /* derived name */

typedef struct ObjRec { /* field names derived */
    char pad0[128];
    int f80; /* 0x80 */
    char pad84[12];
    char *f90; /* 0x90 */
    char pad94[12];
    char *fA0; /* 0xA0 */
    char padA4[12];
    char *fB0; /* 0xB0 */
    char padB4[12];
    char *fC0; /* 0xC0 */
    char padC4[12];
    char *fD0; /* 0xD0 */
    char padD4[12];
    char *fE0; /* 0xE0 */
    char padE4[12];
    char *fF0;        /* 0xF0 */
    unsigned int fF4; /* 0xF4 */
    char padF8[8];
    char *f100;        /* 0x100 */
    unsigned int f104; /* 0x104 */
    char pad108[8];
    char *f110; /* 0x110 */
    char pad114[12];
    char *f120;        /* 0x120 */
    unsigned int f124; /* 0x124 */
} ObjRec;              /* derived name */

/* the sub-record table allocate and copy, inlined once */
static __inline__ void AllocPObjSubs(PObj *p, int *list) /* derived name */
{
    int i;

    p->sub = (PObjSub *)mallocseki(p->f2E * sizeof(PObjSub));

    for (i = 0; i < p->f2E; i++)
        p->sub[i] = *(PObjSub *)list[i];
}

/* the header fields of a freshly allocated PObj */
static __inline__ void InitPObjHeader(PObj *p, ObjHdr *h, int n) /* derived name */
{
    p->f24 = (int)h;
    p->pkt = 0;
    p->f2C = 0;
    p->f2E = h->f8;
    p->f2F = h->fC;
    p->tag.ll &= ~0x30000LL;
    p->tag.ll &= ~0x4000000LL;
    p->f3C = modelData[n].float84;
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

PObj *InitPObj(int h, int name, int n)
{
    PObj *p;
    Vec v;
    int num;
    int i;
    int j;

    p = AllocPObj((ObjHdr *)h, (char *)name, n);
    SetPObjVector(v, modelData[n].offset[0], modelData[n].offset[1], modelData[n].offset[2]);
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

/* The DEBUG build's report of the model file image FreePObj releases, in
   AllocPObj's terms; built only under DEBUG (the text derived). */
static __inline__ void FreePObjDebugInfo(ObjHdr *h) /* derived name */
{
#ifdef DEBUG
    debug_StdPrintfDummy("            : adrs(%p)\n", h);
#endif
}

void FreePObj(PObj *p)
{
    debug_StdPrintfDummy("free object\n");
    FreePObjDebugInfo((ObjHdr *)p->f24);
}
