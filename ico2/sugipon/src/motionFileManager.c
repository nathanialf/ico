#include "debug.h"
#include "motionFileManager.h"
#include "motionOrientManager.h"
#include <eekernel.h>

/* the two running totals AddMotionMemorySize keeps, one per motion class
   (its second argument picks the class; the node_id 4 reset clears the
   second) */
static int motionMemorySize; /* derived name */

static int motionMemorySizeStatic2; /* derived name */

/* declared here: motionOrientManager.h reaches ico2/fumi's files through
   typedef.h, and commonact.c declares the table char [] */
extern const MotionDef motionKind[];

/* every motion's loaded data, indexed by motion number; charFileManager
   fills the entries, the resets clear them */
int *motionTable[1150] = {0};

inline void ResetDynamicMotionManager(void)
{
    int i;
    for (i = 0; i <= 1146; i++) {
        if (motionKind[i].node_id == 4) {
            motionTable[i] = 0;
        }
    }
    motionMemorySizeStatic2 = 0;
}

inline void ResetStatic2MotionManager(int a0)
{
    int i;
    for (i = 0; i <= 1146; i++) {
        if (motionKind[i].node_id == a0) {
            motionTable[i] = 0;
        }
    }
}

/* the top of the motion file InitMotionFile relocates, the base every
   stored offset in it is added to */
static char *motionFileBase = 0; /* derived name */

/* a node of formats 3 and 6: the per-frame tables of its first and last
   element, which _getMotion indexes by frame */
typedef struct {   /* field names derived */
    int nTable;    /* 0x00 */
    int lastTable; /* 0x04 */
} NodeRec;         /* derived name */

void pursueNodeList(void **node, unsigned char *type)
{
    int i;
    int ofs;

    i = 0;
    while (*node != 0) {
        ofs = (int)*node;
        switch (type[i]) {
        default:
            debug_StdPrintfDummy("Invalid node formatID: (%d)\n", type[i]);
            /* "this MOB file is broken, or its version is old." */
            debug_StdPrintfDummy("このMOBファイルは壊れているか、バージョンが古いです。\n");
            break;
        case 1:
        case 4:
            *node = (void *)(motionFileBase + ofs);
            break;
        case 2:
        case 5: {
            int *q = (int *)(motionFileBase + ofs);
            int r = (int)(motionFileBase + *q);
            *node = (void *)q;
            *q = r;
        } break;
        case 3:
        case 6: {
            NodeRec *q = (NodeRec *)(motionFileBase + ofs);
            q->nTable = (int)(motionFileBase + q->nTable);
            q->lastTable = (int)(motionFileBase + q->lastTable);
            *node = (void *)q;
        } break;
        }
        node++;
        i++;
    }
}

inline int CheckMotionIncludeFacialData(unsigned int *self)
{
    int r;
    unsigned int p = (unsigned int)self + 16;
    if (p < self[2])
        r = 0;
    else
        r = -1;
    return r;
}

/* The optional facial block: a count and the table of per-entry offsets,
   relocated in place like the header. */
typedef struct { /* field names derived */
    int count;   /* 0x0 */
    void **tbl;  /* 0x4 */
} FacialRec;     /* derived name */

/* The motion file header as InitMotionFile leaves it, every offset turned
   into a pointer: pursueNodeList walks nodeList against typeList, and the
   facial block exists when typeList does not start right after the 16-byte
   header. */
typedef struct {             /* field names derived */
    int frames;              /* 0x00, the frame count */
    char *rootPos;           /* 0x04, three floats of root position a frame */
    unsigned char *typeList; /* 0x08 */
    void **nodeList;         /* 0x0C */
    FacialRec *facial;       /* 0x10 */
} MotFileHdr;                /* derived name */

/* relocate the facial table in place */
static inline void relocFacialTable(FacialRec *p) /* derived name */
{
    int i;

    if (p->tbl != 0) {
        p->tbl = (void **)(motionFileBase + (int)p->tbl);
        for (i = 0; i < p->count; i++) {
            if (p->tbl[i] != 0) {
                p->tbl[i] = (void *)(motionFileBase + (int)p->tbl[i]);
            }
        }
    }
}

/* Relocate the header in place.  Each offset is read through the file's
 * word view (the one CheckMotionIncludeFacialData reads) and the pointer
 * written through the typed header. */
static inline int relocMotionFile(MotFileHdr *self) /* derived name */
{
    self->rootPos = (char *)self + ((unsigned int *)self)[1];
    self->typeList = (unsigned char *)self + ((unsigned int *)self)[2];
    self->nodeList = (void **)((char *)self + ((unsigned int *)self)[3]);
    FlushCache(0);
    if (CheckMotionIncludeFacialData((unsigned int *)self) == 0) {
        self->facial = (FacialRec *)(motionFileBase + ((unsigned int *)self)[4]);
        relocFacialTable(self->facial);
    }
    pursueNodeList(self->nodeList, self->typeList);
    return 0;
}

void InitMotionFile(void *buf, int a1)
{
    motionFileBase = (char *)buf;
    relocMotionFile((MotFileHdr *)buf);
}

void InitMotionMemorySize(void)
{
    motionMemorySize = 0;
    motionMemorySizeStatic2 = 0;
}

int AddMotionMemorySize(int a0, int a1)
{
    int v0;
    if (a1 != 0) {
        v0 = motionMemorySizeStatic2 + a0;
        motionMemorySizeStatic2 = v0;
    } else {
        v0 = motionMemorySize + a0;
        motionMemorySize = v0;
    }
    return v0;
}

int GetMotionMemorySize(int a0)
{
    return a0 ? motionMemorySizeStatic2 : motionMemorySize;
}
