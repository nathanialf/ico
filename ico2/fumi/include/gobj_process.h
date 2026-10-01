/*
 * ico2/fumi/include/gobj_process.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gobj_process.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GOBJ_PROCESS_H
#define GOBJ_PROCESS_H

#include "typedef.h"
#include "thread.h"

/* one process node of a game object (0x94 bytes): 0x4 owner GObj, 0x8 prev,
   0xC next; the owner keeps the list head at +0x2C and the tail at +0x30 */
typedef struct GProc {     /* field names derived */
    struct GProc *self;    /* 0x00, the node itself while the entry is in use, 0 when free */
    GObj *owner;           /* 0x04 */
    struct GProc *prev;    /* 0x08 */
    struct GProc *next;    /* 0x0C */
    int noThread;          /* 0x10, set when the process runs inline instead of on a thread */
    unsigned int priority; /* 0x14, the list is kept in ascending priority order */
    int active;            /* 0x18 */
    void (*func)();        /* 0x1C, the body of an inline process */
    char pad20[4];
    IOSThread thread; /* 0x24, the thread a threaded process runs on */
} GProc;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order gobj_process.c's inline tail has. */
void isysGObjProcessAlloc(unsigned int a0);
GProc *isysGObjProcAdd(GObj *g, void (*fn)(), int noThread, int pri);
GProc *isysGObjProcAddS(GObj *g, void (*fn)(), int noThread, int pri, long stack);
GProc *isysGObjProcAddGOppArg(GObj *g, void (*fn)(), int noThread, int pri);
void isysGObjProcPause(char *self);
void isysGObjProcPauseAll(int *p);
void isysGObjProcPausePtr(void *a0, int a1);
void isysGObjProcActive(char *self);
void isysGObjProcActiveAll(void *a0);
void isysGObjProcRemoveAll(void *a0);
void isysGObjProcThreadSleep(int a0);
GProc *isysGObjProcAddSGOppArg(GObj *g, void (*fn)(), int noThread, int pri, int stack);
void isysGObjProcActivePtr(void *a0, int a1);
void free_gobj_process_resource(char *self);

GProc *isysGObjProcAdd_(GObj *g, GObj *arg, void (*fn)(), unsigned char noThread, int pri,
                        long stack);

void isysGObjProcRemove(GProc *p);
void isysGObjProcessInit(unsigned int a0);

#endif /* GOBJ_PROCESS_H */
