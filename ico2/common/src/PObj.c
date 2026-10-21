#include "debug.h"
#include "Basic.h"
#include "DisplayP2O.h"
#include <stdio.h>
#include "debug_exception.h"
#include "Matrix.h"
#include "charFileManager.h"
#include <assert.h>
#include <string.h>
#include "charFileName.h"

/* a 16-byte aligned float[4], the shape of libvu0's sceVu0FVECTOR */
typedef float Vec[4] __attribute__((aligned(16))); /* derived name */

typedef struct PktHdr { /* field names derived */
    char pad0[240];
    int kind; /* 0xF0 */
} PktHdr;     /* derived name */

/* the packet record, 0x820 bytes in this build */
typedef struct PObjPkt { /* field names derived */
    char pad0[2032];
    struct PObj *owner; /* 0x7F0 */
    char pad7F4[28];
    void *nodes;      /* 0x810, one 80-byte node record a part */
    PktHdr *lightMtx; /* 0x814, the light matrices (Light.h), their mode at 0xF0 */
} PObjPkt;            /* derived name */

typedef struct PObjSub { /* field names derived */ /* 0x180 stride, hung off the PObj at 0x40 */
    long long pad0[18];
    Vec *vtx;              /* 0x90 */
    unsigned int vtxCount; /* 0x94 */
    long long pad98[(0x180 - 0x98) / 8];
} PObjSub; /* derived name */

typedef struct PObj { /* field names derived */
    char pad0[36];
    int image;       /* 0x24, the model file image (ObjHdr) */
    PObjPkt *pkt;    /* 0x28 */
    short pad2C;     /* 0x2C */
    short partCount; /* 0x2E, the file's objnum */

    union {
        long long ll;

        struct {
            short clstNum; /* 0x30, the file's clstnum */
            short bits;    /* 0x32, the display type, shade and level-of-detail bits tag.ll sets */
            float lightScale; /* 0x34 */
        } v;
    } tag; /* 0x30 */

    float ambientScale; /* 0x38 */
    float shadowLength; /* 0x3C */
    PObjSub *sub;       /* 0x40 */
    Vec (*boxes)[8];    /* 0x44 */
    char pad48[8];
    Vec bb[8]; /* 0x50 */
} PObj;        /* derived name */

/* the file's own name tidier, inlined once, into AllocPObj */
static __inline__ void TidyPObjName(char *name) /* derived name */
{
    char buf[64];
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
   allocates at boxes, plus the whole object's box in self->bb. */
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

    self->boxes = (Vec(*)[8])mallocseki(self->partCount << 7);

    gmn[0] = gmn[1] = gmn[2] = 16777215.0f;
    gmx[0] = gmx[1] = gmx[2] = -16777215.0f;

    for (i = 0; i < self->partCount; i++) {
        sub = &self->sub[i];
        out = self->boxes[i];

        mn[0] = mn[1] = mn[2] = 16777215.0f;
        mx[0] = mx[1] = mx[2] = -16777215.0f;

        for (j = 0; j < sub->vtxCount; j++) {
            p = sub->vtx[j];
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

static void MakePacket(PObj *p)
{
    char name[48];
    int n = -1;
    int i;
    PObjPkt *q;

    for (i = 0; i < ModelDataID_NUMBER; i++) {
        sprintf(name, "%s", modelData[i].modelPath);
        TidyPObjName(name);
        if (strncmp(name, (char *)p, strlen((char *)p)) == 0) {
            debug_StdPrintfDummy("search & found object [%d]%s clp:%d light:%d\n", i,
                                 modelData[i].modelPath, modelData[i].shade, modelData[i].pktKind);
            n = i;
            break;
        }
    }
    if (n == -1) {
        debug_assert(__FILE__, 217);
        __assert(__FILE__, 217, "0");
    }

    p->tag.ll = (p->tag.ll & ~0x3C0000LL) | ((long long)modelData[n].shade << 18);
    p->tag.ll = (p->tag.ll & ~0x3C00000LL) | ((long long)modelData[n].lod << 22);
    p->tag.v.lightScale = modelData[n].lightScale;
    p->ambientScale = modelData[n].ambientScale;
    p->shadowLength = modelData[n].shadowLength;

    q = (PObjPkt *)mallocseki(0x820);
    p->pkt = q;
    q->lightMtx = (PktHdr *)mallocseki(0x100);
    q->lightMtx->kind = modelData[n].pktKind;

    q->owner = p;
    q->nodes = mallocseki(p->partCount * 80);
    if (q->lightMtx->kind != 4) {
        if (p->image != 0)
            p2o_MakePacket((Sub15C *)q);
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
    int objTbl;           /* 0x4  object table, file offset then pointer */
    unsigned int objNum;  /* 0x8, the part count */
    unsigned int clstNum; /* 0xC, the cluster count */
    int texTbl;           /* 0x10 texture table, file offset then pointer */
    unsigned int texNum;  /* 0x14, the texture table's count */
} ObjHdr;                 /* derived name */

typedef struct ObjEnt { /* field names derived */ /* the 0x10 stride records the 0xF0 table holds */
    void *p;                                      /* 0x0 */
    char pad4[12];
} ObjEnt; /* derived name */

typedef struct ObjRec { /* field names derived */
    char pad0[128];
    int magic; /* 0x80, "OBJH" */
    char pad84[12];
    char *vtx; /* 0x90 */
    char pad94[12];
    char *nrm; /* 0xA0 */
    char padA4[12];
    char *uv; /* 0xB0 */
    char padB4[12];
    char *col; /* 0xC0 */
    char padC4[12];
    char *mats; /* 0xD0 */
    char padD4[12];
    char *texDefs; /* 0xE0 */
    char padE4[12];
    char *polys;            /* 0xF0 */
    unsigned int polyCount; /* 0xF4 */
    char padF8[8];
    char *strips;            /* 0x100 */
    unsigned int stripCount; /* 0x104 */
    char pad108[8];
    char *lines; /* 0x110 */
    char pad114[12];
    char *morphs;            /* 0x120 */
    unsigned int morphCount; /* 0x124 */
} ObjRec;                    /* derived name */

/* the sub-record table allocate and copy, inlined once */
static __inline__ void AllocPObjSubs(PObj *p, int *list) /* derived name */
{
    int i;

    p->sub = (PObjSub *)mallocseki(p->partCount * sizeof(PObjSub));

    for (i = 0; i < p->partCount; i++)
        p->sub[i] = *(PObjSub *)list[i];
}

/* the header fields of a freshly allocated PObj */
static __inline__ void InitPObjHeader(PObj *p, ObjHdr *h) /* derived name */
{
    p->image = (int)h;
    p->pkt = 0;
    p->pad2C = 0;
    p->partCount = h->objNum;
    p->tag.v.clstNum = h->clstNum;
    p->tag.ll &= ~0x30000LL;
}

PObj *AllocPObj(ObjHdr *h, char *name)
{
    PObj *p;
    int *tex;
    int *list;
    ObjRec *o;
    unsigned int i;
    unsigned int j;

    h->objTbl += (int)h;

    if (h->texTbl != 0)
        h->texTbl += (int)h;
    tex = (int *)h->texTbl;

    list = (int *)h->objTbl;

    debug_StdPrintfDummy("\033[33mobject info : adrs(%p) objnum(%d) clstnum(%d)\n", h, h->objNum,
                         h->clstNum);

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
        for (i = 0; i < h->texNum; i++)
            tex[i] += (int)h;
    }

    debug_StdPrintfDummy("Solve object address. %p\n", list);

    for (i = 0; i < h->objNum; i++) {
        list[i] += (int)h;
        o = (ObjRec *)list[i];

        if (o->magic != *(int *)"OBJH") {
            debug_StdPrintfDummy("allocPObj:Invalid Object.\n");
            debug_assert(__FILE__, 308);
            __assert(__FILE__, 308, "FALSE");
        }

        o->vtx += (int)h;
        o->nrm += (int)h;
        o->uv += (int)h;
        o->col += (int)h;
        o->mats += (int)h;
        o->texDefs += (int)h;
        o->polys += (int)h;
        for (j = 0; j < o->polyCount; j++)
            ((ObjEnt *)o->polys)[j].p = (void *)((int)((ObjEnt *)o->polys)[j].p + (int)h);
        o->strips += (int)h;
        for (j = 0; j < o->stripCount; j++)
            ((void **)o->strips)[j] = (void *)((int)((void **)o->strips)[j] + (int)h);
        o->lines += (int)h;
        o->morphs += (int)h;
        for (j = 0; j < o->morphCount; j++) {
            if (((void **)o->morphs)[j] != 0)
                ((void **)o->morphs)[j] = (void *)((int)((void **)o->morphs)[j] + (int)h);
        }
    }

    InitPObjHeader(p, h);
    AllocPObjSubs(p, list);

    MakeBoundingBox(p);

    return p;
}

PObj *InitPObj(int h, int name, float x, float y, float z)
{
    PObj *p;
    Vec v;
    int num;
    int i;
    int j;

    p = AllocPObj((ObjHdr *)h, (char *)name);
    SetPObjVector(v, x, y, z);
    num = p->partCount;
    for (i = 0; i < num; i++) {
        PObjSub *g = &p->sub[i];
        int cnt = g->vtxCount;

        for (j = 0; j < cnt; j++)
            _AddVector(g->vtx[j], g->vtx[j], v);
        for (j = 0; j < 8; j++)
            _AddVector(p->boxes[i][j], p->boxes[i][j], v);
    }
    MakePacket(p);
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
    FreePObjDebugInfo((ObjHdr *)p->image);
}

/* the file's version stamp: nothing reads it, so it stays in the member's
   .sdata after the strings of the functions above */
static char *version = "1.0p2"; /* derived name */
