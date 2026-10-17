#include "debug.h"
#include "memory.h"
#include "typedef.h"
#include "gobj_process.h"

/* the process pool and how many 0x94-byte entries it holds */
static char *procPool; /* derived name */

static int procMax; /* derived name */

#include "thread.h"
#include "ios.h"
#include "include_asm.h"

void isysGObjProcessInit(unsigned int max)
{
    isysGObjProcessAlloc(max);
}

INCLUDE_ASM_LIT(isysGObjProcessAlloc);

static inline GProc *alloc_gobj_process(void) /* derived name */
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

INCLUDE_ASM(isysGObjProcAdd_);

inline void isysGObjProcPause(char *self)
{
    ((GProc *)self)->active = 0;
}

inline void isysGObjProcPauseAll(GObj *p)
{
    GProc *cur = ((GObj *)p)->procHead;
    if (cur != 0) {
        do {
            cur->active = 0;
            cur = cur->prev;
        } while (cur != 0);
    }
}

inline void isysGObjProcPausePtr(void *gobj, void (*func)())
{
    GProc *p = ((GObj *)gobj)->procHead;
    while (p != 0) {
        if (p->func == func) {
            p->active = 0;
        }
        p = p->prev;
    }
}

inline void isysGObjProcActive(char *self)
{
    ((GProc *)self)->active = 1;
}

inline void isysGObjProcActiveAll(void *gobj)
{
    GProc *p = ((GObj *)gobj)->procHead;
    while (p != 0) {
        p->active = 1;
        p = p->prev;
    }
}

inline void isysGObjProcActivePtr(void *gobj, void (*func)())
{
    GProc *p = ((GObj *)gobj)->procHead;
    while (p != 0) {
        if (p->func == func) {
            p->active = 1;
        }
        p = p->prev;
    }
}

inline void free_gobj_process_resource(char *self)
{
    ((GProc *)self)->self = 0;
}

static void cut_gobj_process_link(GProc *p)
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
    if (p == p->owner->procHead) {
        p->owner->procHead = p->prev;
    }
    if (p == p->owner->procTail) {
        p->owner->procTail = p->next;
    }
}

void isysGObjProcRemove(GProc *p);

INCLUDE_ASM(isysGObjProcRemove);

inline void isysGObjProcRemoveAll(void *gobj)
{
    GProc *p = ((GObj *)gobj)->procHead;
    while (p != 0) {
        isysGObjProcRemove(p);
        p = p->prev;
    }
}

inline void isysGObjProcThreadSleep(int frames)
{
    while (frames != 0) {
        iosThreadStop(0);
        frames--;
    }
}

INCLUDE_ASM(isysGObjProcessAlloc);

INCLUDE_ASM(isysGObjProcAdd);

INCLUDE_ASM(isysGObjProcAddS);
