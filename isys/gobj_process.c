#include "common.h"

/* one process node: 0x4 owner GObj, 0x8 prev, 0xC next; the owner keeps the
   list head at +0x2C and the tail at +0x30 */
typedef struct GProc {
    char _p0[0x4];
    char *owner;        /* 0x04 */
    struct GProc *prev; /* 0x08 */
    struct GProc *next; /* 0x0C */
} GProc;

extern void cut_gobj_process_link(GProc *p);
/* header prototypes (order fixes the inline tail) */
extern int iosThreadDestroy(int a0);
extern char D_00551FF0[];
extern int D_0063A430;
extern char *D_0063C1B0;
extern int D_0063C1B4;
extern int iosMallocDebug(int a0, int a1, const char *fmt, int line);
extern int isysGObjProcAdd_(int a0, int a1, int a2, unsigned char a3, int a4, int a5);
extern void iosThreadStop(int a0);
/* prototypes: their order is the inline tail's emission order */
void isysGObjProcessAlloc(unsigned int a0);
int isysGObjProcAdd(int a0, int a1, int a2, int a3);
int isysGObjProcAddS(int a0, int a1, int a2, int a3, int a4);
int isysGObjProcAddGOppArg(int a0, int a1, int a2, int a3);
void isysGObjProcPause(char *self);
void isysGObjProcPauseAll(int *p);
void isysGObjProcPausePtr(void *a0, int a1);
void isysGObjProcActive(char *self);
void isysGObjProcActiveAll(void *a0);
void isysGObjProcRemoveAll(void *a0);
void isysGObjProcThreadSleep(int a0);
int isysGObjProcAddSGOppArg(int a, int b, int c, int d, int e);
void isysGObjProcActivePtr(void *a0, int a1);
void free_gobj_process_resource(char *self);

void isysGObjProcessInit(unsigned int a0)
{
    isysGObjProcessAlloc(a0);
}

inline void isysGObjProcessAlloc(unsigned int a0)
{
    int ret = iosMallocDebug(D_0063A430, a0 * 0x94, D_00551FF0, 0x49);
    unsigned int i;
    D_0063C1B4 = a0;
    D_0063C1B0 = (char *)ret;
    for (i = 0; i < a0; i++) {
        *(int *)(D_0063C1B0 + i * 0x94) = 0;
    }
}

extern void debug_StdPrintfDummy();
extern char D_00552008[];
extern char D_00552030[];
extern char D_00552040[];
extern int iosThreadCreateS(void *th, int a1, int a2, int a3, int a4, int a5, int a6);
extern void iosThreadStart(void *th);

static inline GProc *alloc_gobj_process(void)
{
    unsigned int i;
    unsigned int j;

    for (i = 0; i < D_0063C1B4; i++) {
        if (*(int *)(D_0063C1B0 + i * 0x94) == 0) {
            break;
        }
    }
    if (i == D_0063C1B4) {
        debug_StdPrintfDummy(D_00552008);
        debug_StdPrintfDummy(D_00552008);
        for (j = 0; j < D_0063C1B4; j++) {
            debug_StdPrintfDummy(D_00552030, *(int *)(D_0063C1B0 + j * 0x94),
                                 *(int *)(D_0063C1B0 + j * 0x94 + 0x1C),
                                 *(int *)(D_0063C1B0 + j * 0x94 + 0x5C));
        }
        return 0;
    }
    return (GProc *)(D_0063C1B0 + i * 0x94);
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
        debug_StdPrintfDummy(D_00552040);
        return 0;
    }
    *(GProc **)p = p;
    if (a3 == 0) {
        iosThreadCreateS((char *)p + 0x24, 1, a2, a1 ? a1 : (int)p, D_0063A430, a5, a4);
        iosThreadStart((char *)p + 0x24);
        *(int *)((char *)p + 0x1C) = 0;
    } else {
        *(int *)((char *)p + 0x1C) = a2;
    }
    *(int *)((char *)p + 0x10) = a3;
    p->owner = (char *)a0;
    *(int *)((char *)p + 0x18) = 1;
    *(int *)((char *)p + 0x14) = a4;
    h = *(GProc **)((char *)a0 + 0x2C);
    if (h == 0) {
        *(GProc **)((char *)p + 0xC) = 0;
        *(GProc **)((char *)p + 0x8) = 0;
        *(GProc **)((char *)a0 + 0x2C) = p;
        *(GProc **)((char *)a0 + 0x30) = p;
    } else if ((unsigned int)a4 < *(unsigned int *)((char *)h + 0x14)) {
        *(GProc **)((char *)p + 0xC) = 0;
        *(GProc **)((char *)p + 0x8) = *(GProc **)((char *)a0 + 0x2C);
        p->prev->next = p;
        *(GProc **)((char *)a0 + 0x2C) = p;
    } else {
        t = *(GProc **)((char *)a0 + 0x30);
        if (!((unsigned int)a4 < *(unsigned int *)((char *)t + 0x14))) {
            p->next = t;
            p->prev = 0;
            t->prev = p;
            *(GProc **)((char *)a0 + 0x30) = p;
        } else {
            while (!((unsigned int)a4 < *(unsigned int *)((char *)h->prev + 0x14))) {
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
    *(int *)(self + 0x18) = 0;
}

inline void isysGObjProcPauseAll(int *p)
{
    int *cur = (int *)p[0x2C / 4];
    if (cur != 0) {
        do {
            cur[0x18 / 4] = 0;
            cur = (int *)cur[0x8 / 4];
        } while (cur != 0);
    }
}

inline void isysGObjProcPausePtr(void *a0, int a1)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        if (*(int *)((char *)p + 0x1C) == a1) {
            *(int *)((char *)p + 0x18) = 0;
        }
        p = *(int **)((char *)p + 0x8);
    }
}

inline void isysGObjProcActive(char *self)
{
    *(int *)(self + 0x18) = 1;
}

inline void isysGObjProcActiveAll(void *a0)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        *(int *)((char *)p + 0x18) = 1;
        p = *(int **)((char *)p + 0x8);
    }
}

inline void isysGObjProcActivePtr(void *a0, int a1)
{
    int *p = *(int **)((char *)a0 + 0x2C);
    while (p != 0) {
        if (*(int *)((char *)p + 0x1C) == a1) {
            *(int *)((char *)p + 0x18) = 1;
        }
        p = *(int **)((char *)p + 0x8);
    }
}

inline void free_gobj_process_resource(char *self)
{
    *(int *)(self + 0x0) = 0;
}

extern char D_00552068[];
extern void debug_StdPrintfDummy();

void cut_gobj_process_link(GProc *p)
{
    if (p == 0) {
        debug_StdPrintfDummy(D_00552068);
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
    if (p == *(GProc **)(p->owner + 0x2C)) {
        *(GProc **)(p->owner + 0x2C) = p->prev;
    }
    if (p == *(GProc **)(p->owner + 0x30)) {
        *(GProc **)(p->owner + 0x30) = p->next;
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
    void *p = *(void **)((char *)a0 + 0x2C);
    while (p != 0) {
        isysGObjProcRemove(p);
        p = *(void **)((char *)p + 0x8);
    }
}

inline void isysGObjProcThreadSleep(int a0)
{
    while (a0 != 0) {
        iosThreadStop(0);
        a0--;
    }
}
