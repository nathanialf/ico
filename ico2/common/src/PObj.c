#include "debug.h"
#include "Basic.h"
#include "DisplayP2O.h"
#include <stdio.h>
#include "debug_exception.h"
#include "Matrix.h"
#include "charFileManager.h"
#include <assert.h>
#include "include_asm.h"

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
    void *nodes;      /* 0x870, one 80-byte node record a part */
    PktHdr *lightMtx; /* 0x874, the light matrices (Light.h), their mode at 0xF0 */
} PObjPkt;            /* derived name */

typedef struct PObjSub { /* field names derived */ /* 0x180 stride, hung off the PObj at 0x40 */
    long long pad0[18];
    Vec *vtx;              /* 0x90 */
    unsigned int vtxCount; /* 0x94 */
    long long pad98[(0x180 - 0x98) / 8];
} PObjSub; /* derived name */

typedef struct PObj { /* field names derived */
    char pad0[36];
    int image;    /* 0x24, the model file image (ObjHdr) */
    PObjPkt *pkt; /* 0x28 */
    short pad2C;  /* 0x2C */
    /* 0x2E and 0x2F, the part count and the cluster count (the file's objnum
       and clstnum), as one short's two bitfields */
    short partCount : 8;        /* 0x2E */
    unsigned short clstNum : 8; /* 0x2F */

    union {
        long long ll;

        struct {
            short nloop; /* 0x30 */
            short bits;  /* 0x32, the display type, shade and level-of-detail bits tag.ll sets */
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
   allocates at boxes, plus the whole object's box in self->bb. */
INCLUDE_ASM(MakeBoundingBox);

INCLUDE_ASM(MakePacket);

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
static __inline__ void InitPObjHeader(PObj *p, ObjHdr *h, int n) /* derived name */
{
    p->image = (int)h;
    p->pkt = 0;
    p->pad2C = 0;
    p->partCount = h->objNum;
    p->clstNum = h->clstNum;
    p->tag.ll &= ~0x30000LL;
    p->tag.ll &= ~0x4000000LL;
    p->shadowLength = modelData[n].shadowLength;
}

INCLUDE_ASM(AllocPObj);

INCLUDE_ASM(InitPObj);

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

/* .sdata: a short string and a word pointing at it, which no code of the
   demo reads (the stub-owned row D_0067B4E8) */
INCLUDE_ASM(D_0067B4E8);
