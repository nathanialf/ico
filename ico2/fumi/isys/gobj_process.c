#include "common.h"
#include "debug.h"
#include "memory.h"
#include "typedef.h"

/* one process node: 0x4 owner GObj, 0x8 prev, 0xC next; the owner keeps the
   list head at +0x2C and the tail at +0x30 */
typedef struct GProc {
    struct GProc *self;    /* 0x00, the node itself while the entry is in use, 0 when free */
    char *owner;           /* 0x04 */
    struct GProc *prev;    /* 0x08 */
    struct GProc *next;    /* 0x0C */
    int noThread;          /* 0x10, set when the process runs inline instead of on a thread */
    unsigned int priority; /* 0x14, the list is kept in ascending priority order */
    int active;            /* 0x18 */
    int func;              /* 0x1C, the body of an inline process */
    char _p20[0x4];
    char thread[0x70]; /* 0x24, the IOSThread a threaded process runs on */
} GProc;

extern void cut_gobj_process_link(GProc *p);
extern int D_0063A430;

/* .sbss, owned by gobj_process.o and reached only from this file (MAIN.MAP
   names no symbol in the run), in the ROM's run order: the process pool and
   how many 0x94-byte entries it holds. */
static char *procPool;

static int procMax;

#include "gobj_process.h"
#include "thread.h"

void isysGObjProcessInit(unsigned int a0)
{
    isysGObjProcessAlloc(a0);
}

inline void isysGObjProcessAlloc(unsigned int a0)
{
    int ret = iosMallocDebug(D_0063A430, a0 * 0x94, "isys/gobj_process.c", 73);
    unsigned int i;
    procMax = a0;
    procPool = (char *)ret;
    for (i = 0; i < a0; i++) {
        ((GProc *)(procPool + i * 0x94))->self = 0;
    }
}

static inline GProc *alloc_gobj_process(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < procMax; i++) {
        if (((GProc *)(procPool + i * 0x94))->self == 0) {
            break;
        }
    }
    if (i == procMax) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        for (j = 0; j < procMax; j++) {
            debug_StdPrintfDummy("id %d %x %x \n", ((GProc *)(procPool + j * 0x94))->self,
                                 ((GProc *)(procPool + j * 0x94))->func,
                                 *(int *)(procPool + j * 0x94 + 0x5C));
        }
        return 0;
    }
    return (GProc *)(procPool + i * 0x94);
}

int isysGObjProcAdd_(int a0, int a1, int a2, unsigned char a3, int a4, int a5)
{
    GProc *p;
    GProc *h;
    GProc *t;

    if (a2 == 0) {
        return 0;
    }
    p = alloc_gobj_process();
    if (p == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObjProcess\n");
        return 0;
    }
    p->self = p;
    if (a3 == 0) {
        iosThreadCreateS(p->thread, 1, a2, a1 ? a1 : (int)p, D_0063A430, a5, a4);
        iosThreadStart(p->thread);
        p->func = 0;
    } else {
        p->func = a2;
    }
    p->noThread = a3;
    p->owner = (char *)a0;
    p->active = 1;
    p->priority = a4;
    h = ((GObj *)a0)->procHead;
    if (h == 0) {
        p->next = 0;
        p->prev = 0;
        ((GObj *)a0)->procHead = p;
        ((GObj *)a0)->procTail = p;
    } else if ((unsigned int)a4 < h->priority) {
        p->next = 0;
        p->prev = ((GObj *)a0)->procHead;
        p->prev->next = p;
        ((GObj *)a0)->procHead = p;
    } else {
        t = ((GObj *)a0)->procTail;
        if (!((unsigned int)a4 < t->priority)) {
            p->next = t;
            p->prev = 0;
            t->prev = p;
            ((GObj *)a0)->procTail = p;
        } else {
            while (!((unsigned int)a4 < h->prev->priority)) {
                h = h->prev;
            }
            p->next = h;
            p->prev = h->prev;
            h->prev = p;
            p->prev->next = p;
        }
    }
    return (int)p;
}

inline int isysGObjProcAddGOppArg(int a0, int a1, int a2, int a3)
{
    return isysGObjProcAdd_(a0, 0, a1, a2 & 0xFF, a3, 0x1800);
}

inline int isysGObjProcAdd(int a0, int a1, int a2, int a3)
{
    return isysGObjProcAdd_(a0, a0, a1, a2 & 0xFF, a3, 0x1800);
}

inline int isysGObjProcAddS(int a0, int a1, int a2, int a3, int a4)
{
    return isysGObjProcAdd_(a0, a0, a1, a2 & 0xFF, a3, a4);
}

inline int isysGObjProcAddSGOppArg(int a, int b, int c, int d, int e)
{
    return isysGObjProcAdd_(a, 0, b, c & 0xFF, d, e);
}

inline void isysGObjProcPause(char *self)
{
    ((GProc *)self)->active = 0;
}

inline void isysGObjProcPauseAll(int *p)
{
    GProc *cur = ((GObj *)p)->procHead;
    if (cur != 0) {
        do {
            cur->active = 0;
            cur = cur->prev;
        } while (cur != 0);
    }
}

inline void isysGObjProcPausePtr(void *a0, int a1)
{
    GProc *p = ((GObj *)a0)->procHead;
    while (p != 0) {
        if (p->func == a1) {
            p->active = 0;
        }
        p = p->prev;
    }
}

inline void isysGObjProcActive(char *self)
{
    ((GProc *)self)->active = 1;
}

inline void isysGObjProcActiveAll(void *a0)
{
    GProc *p = ((GObj *)a0)->procHead;
    while (p != 0) {
        p->active = 1;
        p = p->prev;
    }
}

inline void isysGObjProcActivePtr(void *a0, int a1)
{
    GProc *p = ((GObj *)a0)->procHead;
    while (p != 0) {
        if (p->func == a1) {
            p->active = 1;
        }
        p = p->prev;
    }
}

inline void free_gobj_process_resource(char *self)
{
    ((GProc *)self)->self = 0;
}

void cut_gobj_process_link(GProc *p)
{
    if (p == 0) {
        debug_StdPrintfDummy("isys:null GObjProcess\n");
        return;
    }
    if (p->next == 0 && p->prev == 0) {
        /* not linked into a list */
    } else {
        if (p->next != 0) {
            p->next->prev = p->prev;
        }
        if (p->prev != 0) {
            p->prev->next = p->next;
        }
    }
    if (p == ((GObj *)p->owner)->procHead) {
        ((GObj *)p->owner)->procHead = p->prev;
    }
    if (p == ((GObj *)p->owner)->procTail) {
        ((GObj *)p->owner)->procTail = p->next;
    }
}

void isysGObjProcRemove(int *a0)
{
    int v0;
    cut_gobj_process_link((int)a0);
    v0 = a0[4];
    a0[0] = 0;
    if (v0 != 0) {
        return;
    }
    return iosThreadDestroy((int)a0 + 0x24);
}

inline void isysGObjProcRemoveAll(void *a0)
{
    GProc *p = ((GObj *)a0)->procHead;
    while (p != 0) {
        isysGObjProcRemove((int *)p);
        p = p->prev;
    }
}

inline void isysGObjProcThreadSleep(int a0)
{
    while (a0 != 0) {
        iosThreadStop(0);
        a0--;
    }
}
