#include "common.h"
#include "debug.h"
#include "motionFileManager.h"
#include <eekernel.h>

/* .sbss, owned by motionFileManager.o and reached only from this file
   (MAIN.MAP names no symbol in the run), in the ROM's run order: the two
   running totals AddMotionMemorySize keeps, one per motion class (its second
   argument picks the class; the second total is the one the node_id 4 reset
   clears). */
static int motionMemorySize;

static int motionMemorySizeStatic2;

typedef struct {
    char pad[0x134];
    int node_id;
    char pad2[0x194 - 0x138];
} MotFileRec;

extern MotFileRec D_0055FE58[];
extern int D_004EB758[];

inline void ResetDynamicMotionManager(void)
{
    int i;
    for (i = 0; i <= 1146; i++) {
        if (D_0055FE58[i].node_id == 4) {
            D_004EB758[i] = 0;
        }
    }
    motionMemorySizeStatic2 = 0;
}

inline void ResetStatic2MotionManager(int a0)
{
    int i;
    for (i = 0; i <= 1146; i++) {
        if (D_0055FE58[i].node_id == a0) {
            D_004EB758[i] = 0;
        }
    }
}

/* This TU's own .sdata word (MAIN.MAP line 7327, 4 bytes, no symbol named in
   the run; ROM value 0): the top of the motion file InitMotionFile relocates,
   the base every stored offset in it is added to.  In the source it is an
   initialised static; it stays a placeholder extern here because a named
   initialised small object lands in .sdata.<name> under -fdata-sections,
   which the period assembler does not address gp-relative.  The ROM pins its
   type only through alias sets (see relocMotionFile): the set of the header's
   first pointer field, not int's and not the facial table's void * entries;
   char * is our choice within that. */
extern char *D_0063B8F0;
extern char D_0061FB60[];
extern char D_0061FB80[];

typedef struct {
    int f0; /* 0x00 */
    int f4; /* 0x04 */
} NodeRec;

/* listing rows sugipon/src/motionFileManager.c:32-86 */
void pursueNodeList(void **node, unsigned char *type)
{
    int i;
    int ofs;

    i = 0;
    while (*node != 0) {
        ofs = (int)*node;
        switch (type[i]) {
        default:
            debug_StdPrintfDummy(D_0061FB60, type[i]);
            debug_StdPrintfDummy(D_0061FB80);
            break;
        case 1:
        case 4:
            *node = (void *)(D_0063B8F0 + ofs);
            break;
        case 2:
        case 5: {
            int *q = (int *)(D_0063B8F0 + ofs);
            int r = (int)(D_0063B8F0 + *q);
            *node = (void *)q;
            *q = r;
        } break;
        case 3:
        case 6: {
            NodeRec *q = (NodeRec *)(D_0063B8F0 + ofs);
            q->f0 = (int)(D_0063B8F0 + q->f0);
            q->f4 = (int)(D_0063B8F0 + q->f4);
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

/* The optional facial block (reconstruction; names ours): a count and the
   table of per-entry offsets, relocated in place like the header. */
typedef struct {
    int count;  /* 0x0 */
    void **tbl; /* 0x4 */
} FacialRec;

/* The motion file header as InitMotionFile leaves it, every offset turned
   into a pointer (reconstruction; field names ours, from their users here:
   pursueNodeList walks nodeList against typeList, the facial block exists
   when typeList does not start right after the 16-byte header). */
typedef struct {
    int f0;                  /* 0x00 */
    char *f4;                /* 0x04 */
    unsigned char *typeList; /* 0x08 */
    void **nodeList;         /* 0x0C */
    FacialRec *facial;       /* 0x10 */
} MotFileHdr;

/* listing rows sugipon/src/motionFileManager.c:93-105, inlined into
 * InitMotionFile and nowhere else. */
static inline void relocFacialTable(FacialRec *p)
{
    int i;

    if (p->tbl != 0) {
        p->tbl = (void **)(D_0063B8F0 + (int)p->tbl);
        for (i = 0; i < p->count; i++) {
            if (p->tbl[i] != 0) {
                p->tbl[i] = (void *)(D_0063B8F0 + (int)p->tbl[i]);
            }
        }
    }
}

/* listing rows sugipon/src/motionFileManager.c:125-142, inlined into
 * InitMotionFile and nowhere else.  Each offset is read through the file's
 * word view (the one CheckMotionIncludeFacialData reads) and the pointer
 * written through the typed header.  The bytes pin that split, not its
 * spelling: the loads must sit in another alias set from D_0063B8F0 so
 * sched2 can issue the top's store ahead of them, while the f4 store must
 * share its set so sched1 keeps the store ahead of it (the order local-alloc
 * reads to give f4 $a1), and the facial load and store must differ so the
 * top's load is issued first; one type for a field's load and store reaches
 * none of the three.  The int return is not pinned either: a void helper ends
 * in a tail call, calls.c emits a sibcall placeholder and integrate.c then
 * declines to inline the body the listing places inside InitMotionFile. */
static inline int relocMotionFile(MotFileHdr *self)
{
    self->f4 = (char *)self + ((unsigned int *)self)[1];
    self->typeList = (unsigned char *)self + ((unsigned int *)self)[2];
    self->nodeList = (void **)((char *)self + ((unsigned int *)self)[3]);
    FlushCache(0);
    if (CheckMotionIncludeFacialData((unsigned int *)self) == 0) {
        self->facial = (FacialRec *)(D_0063B8F0 + ((unsigned int *)self)[4]);
        relocFacialTable(self->facial);
    }
    pursueNodeList(self->nodeList, self->typeList);
    return 0;
}

/* listing rows sugipon/src/motionFileManager.c:147-148 */
void InitMotionFile(void *buf, int a1)
{
    D_0063B8F0 = (char *)buf;
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
