#include "common.h"
#include "debug.h"
#include "memory.h"

struct GObj__p4 {
    int unk0;
    int unk4;
    int unk8;
    char pad[0x150];
    int unk15C;
    char pad2[0x14];
};

/* .bss, owned by gobj.o and reached only from this file (MAIN.MAP names no
   symbol in the run): the head of the free list for each of the 70 object
   kinds. */
static char *gobjKindHead[70];

/* Deferred-`inline` tail: ee-gcc 2.9 emits a plain-`inline` function's
   out-of-line copy at the END of the object in PROTOTYPE order while its
   string literals are emitted where it is DEFINED.  That is what puts the
   __FILE__ string, first used by isysGObjAlloc, at the head of this TU's
   .rodata run even though its code sits in the object's tail. */
struct GObj__p4;

inline void isysGObjAlloc(int n);
inline void isysGObjRemove(char *g);
inline void isysGObjKindTableAdd(char *g, int kind);
inline void isysGObjKindTableRemove(char *g);
inline void isysGObjMoveAfterGObj(char *self, char *other);
inline void isysGObjMoveBeforeGObj(int self, int other);
inline char *isysGObjAdd(char *owner, int a1, int a2);
inline char *isysGObjAddHead(char *owner, int a1, int a2);
inline void *isysGObjSearchFromObjLayoutID(int a0);
inline void *isysGObjSearchFromObjKindID_begin(int kind);
inline void *isysGObjSearchFromObjKindID_next(char *g);
inline void *isysGObjSearchFromLabelTypeID(int a0);
inline struct GObj__p4 *isysGObjGetExist_begin(void);
inline struct GObj__p4 *isysGObjGetExist_next(struct GObj__p4 *start);
inline void isysGObjActiveLink(int bit, int set);
inline void isysGObjActiveDlLink(int a0, int a1);

void isysGObjKindTableInit(void)
{
    memset(gobjKindHead, 0, sizeof(gobjKindHead));
}

extern char D_0029C4F0[];
extern char *D_0029C510[];
extern int D_0063A60C;
extern unsigned int D_0063A610;
/* kept local: this TU's uses of isysGObjAlloc do not fit the prototype in gobj.h */
extern void isysGObjAlloc(int n);

void isysGObjInit(int n)
{
    int i;

    for (i = 0; i < 8; i++) {
        *(int *)(D_0029C4F0 + i * 4) = 0;
        D_0029C510[i] = 0;
    }
    isysGObjAlloc(n);
    D_0063A60C = 0;
    D_0063A610 = 0;
    isysGObjKindTableInit();
}

extern int D_0063A430;

/* .sbss, owned by gobj.o and reached only from this file (MAIN.MAP names no
   symbol in the run), in the ROM's run order: the object table and how many
   0x174-byte entries isysGObjAlloc gave it. */
static struct GObj__pn *gobjTable;

static unsigned int gobjMax;

inline void isysGObjAlloc(int n)
{
    struct GObj__p4 *tbl;
    unsigned int i;

    gobjTable = iosMallocDebug(D_0063A430, n * sizeof(struct GObj__p4), __FILE__, 174);
    gobjMax = n;
    tbl = (struct GObj__p4 *)gobjTable;
    for (i = 0; i < n; i++) {
        tbl[i].unk0 = 0;
        tbl[i].unk15C = 0;
        tbl[i].unk8 = -1;
        tbl[i].unk4 = -1;
    }
}

typedef struct GLNode {
    char _p0[0x10];
    struct GLNode *next;
    struct GLNode *prev;
    unsigned char id;
    char _p1[0x3];
    int key;
} GLNode;

void cut_gobj_link(int a0)
{
    GLNode *p = (GLNode *)a0;

    if (p == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return;
    }

    if (p->prev == 0 && p->next == 0) {
        /* not linked into a list */
    } else {
        if (p->prev != 0)
            p->prev->next = p->next;

        if (p->next != 0) {
            p->next->prev = p->prev;
        }
    }

    if (p == ((GLNode **)D_0029C4F0)[p->id]) {
        ((GLNode **)D_0029C4F0)[p->id] = p->next;
    }
    if (p == ((GLNode **)D_0029C510)[p->id]) {
        ((GLNode **)D_0029C510)[p->id] = p->prev;
    }
}

extern char D_0063A608[];

/* INTERIM: the listing inlines isysGObjRemove here (its own lines 225-231 and,
 * through it, isysGObjKindTableRemove's 138-147, appear inside this function's
 * span).  isysGObjRemove is a MAIN.MAP symbol with its own ROM slot AFTER this
 * one, so it cannot carry `inline` without moving to gcc's inline tail; the
 * caller gets this stand-in instead.  Keep the two bodies identical. */
static __inline__ void removeGObjEntry(char *g)
{
    int kind = *(int *)(g + 0xC);
    char *proc = *(char **)(g + 0x2C);
    char *p;
    if ((unsigned int)(kind - 1) < 0x45) {
        p = gobjKindHead[kind];
        if (p == g) {
            gobjKindHead[kind] = *(char **)(g + 0x3C);
        } else if (p != 0) {
            while (*(char **)(p + 0x3C) != g) {
                if (p == 0) {
                    debug_assert(__FILE__, 0x92);
                    __assert(__FILE__, 0x92, D_0063A608);
                }
                p = *(char **)(p + 0x3C);
            }
            *(char **)(p + 0x10) = *(char **)(g + 0x3C);
        }
    }
    cut_gobj_link((int)g);
    *(int *)g = 0;
    while (proc != 0) {
        isysGObjProcRemove(proc);
        proc = *(char **)(g + 0x2C);
    }
}

void isysGObjRemoveAll(void)
{
    unsigned int i;

    for (i = 0; i < gobjMax; i++) {
        if (*(int *)((char *)gobjTable + i * 0x174) != 0)
            removeGObjEntry((char *)gobjTable + i * 0x174);
    }
    isysGObjKindTableInit();
}

extern char D_0029C4F0[];
extern char *D_0029C510[];

void add_gobj_to_tail(int a0, int a1, int a2)
{
    char *g = (char *)a0;
    unsigned char kind = a1;
    unsigned int val = a2;
    char *head;
    char *tail;
    char *p;
    g[0x18] = kind;
    *(unsigned int *)(g + 0x1C) = val;
    head = *(char **)(D_0029C4F0 + kind * 4);
    if (head == 0) {
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        return;
    }
    if (val < *(unsigned int *)(head + 0x1C)) {
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = head;
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(head + 0x14) = g;
        return;
    }
    tail = D_0029C510[kind];
    if (!(val < *(unsigned int *)(tail + 0x1C))) {
        *(char **)(g + 0x14) = tail;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        *(char **)(tail + 0x10) = g;
        return;
    }
    p = head;
    while (!(val < *(unsigned int *)(*(char **)(p + 0x10) + 0x1C))) {
        p = *(char **)(p + 0x10);
    }
    *(char **)(g + 0x14) = p;
    *(char **)(g + 0x10) = *(char **)(p + 0x10);
    *(char **)(p + 0x10) = g;
    *(char **)(*(char **)(g + 0x10) + 0x14) = g;
}

void add_gobj_to_head(char *g, int a1, int a2)
{
    unsigned char kind = a1;
    unsigned int val = a2;
    char *head;
    char *tail;
    char *p;
    g[0x18] = kind;
    *(unsigned int *)(g + 0x1C) = val;
    head = *(char **)(D_0029C4F0 + kind * 4);
    if (head == 0) {
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        return;
    }
    if (!(*(unsigned int *)(head + 0x1C) < val)) {
        *(char **)(g + 0x14) = 0;
        *(char **)(g + 0x10) = head;
        *(char **)(D_0029C4F0 + kind * 4) = g;
        *(char **)(head + 0x14) = g;
        return;
    }
    tail = D_0029C510[kind];
    if (*(unsigned int *)(tail + 0x1C) < val) {
        *(char **)(g + 0x14) = tail;
        *(char **)(g + 0x10) = 0;
        D_0029C510[kind] = g;
        *(char **)(tail + 0x10) = g;
        return;
    }
    p = head;
    while (*(unsigned int *)(*(char **)(p + 0x10) + 0x1C) < val) {
        p = *(char **)(p + 0x10);
    }
    *(char **)(g + 0x14) = p;
    *(char **)(g + 0x10) = *(char **)(p + 0x10);
    *(char **)(p + 0x10) = g;
    *(char **)(*(char **)(g + 0x10) + 0x14) = g;
}

/* kept local: this TU's uses of add_gobj_to_tail do not fit the prototype in gobj.h */
extern void add_gobj_to_tail(int a0, int a1, int a2);
/* kept local: this TU's uses of cut_gobj_link do not fit the prototype in gobj.h */
extern void cut_gobj_link(int a0);

void isysGObjMove(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    cut_gobj_link(a0);
    return add_gobj_to_tail(a0, s1, new_var);
}

/* kept local: this TU's uses of add_gobj_to_head do not fit the prototype in gobj.h */
extern void add_gobj_to_head(char *a0, int a1, int a2);

void isysGObjMoveHead(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    cut_gobj_link(a0);
    return add_gobj_to_head(a0, s1, new_var);
}

/* static helper the listing places at gobj.c lines 360-369; never emitted out
 * of line, so it has no MAIN.MAP symbol and this name is ours. */
static __inline__ void linkGObjAfter(GLNode *g, GLNode *other)
{
    g->id = other->id;
    g->key = other->key;
    g->prev = other;
    g->next = other->next;
    other->next = g;
    if (g->next == 0) {
        ((GLNode **)D_0029C510)[g->id] = g;
    }
}

/* static helper the listing places at gobj.c lines 453-467; never emitted out
 * of line, so it has no MAIN.MAP symbol and this name is ours. */
static __inline__ char *allocGObjEntry(void)
{
    unsigned int i;
    char *g;

    for (i = 0; i < gobjMax; i++) {
        if (*(int *)((char *)gobjTable + i * 0x174) == 0) {
            break;
        }
    }
    if (i == gobjMax) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    g = (char *)(i * 0x174 + (int)gobjTable);
    *(int *)(g + 0x164) = 0;
    *(int *)(g + 0x170) = 0;
    return g;
}

char *isysGObjAddAfterGObj(char *owner, char *other)
{
    char *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    if (other == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return 0;
    }
    *(int *)g = (int)g;
    *(char **)(g + 0x28) = owner;
    linkGObjAfter((GLNode *)g, (GLNode *)other);
    *(int *)(g + 0x15C) = 0;
    *(int *)(g + 0x8) = -1;
    *(int *)(g + 0x4) = -1;
    *(int *)(g + 0x2C) = 0;
    *(int *)(g + 0x30) = 0;
    *(int *)(g + 0x58) = 0;
    return g;
}

char *isysGObjAddBeforeGObj(char *owner, char *other)
{
    unsigned char t;
    int u;
    char *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    if (other == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return 0;
    }
    *(int *)g = (int)g;
    *(char **)(g + 0x28) = owner;
    t = *(unsigned char *)(other + 0x18);
    *(unsigned char *)(g + 0x18) = t;
    u = *(int *)(other + 0x14);
    *(int *)(g + 0x10) = (int)other;
    *(int *)(g + 0x14) = u;
    *(int *)(other + 0x14) = (int)g;
    *(int *)(g + 0x1C) = *(int *)(other + 0x1C);
    if (*(int *)(g + 0x14) == 0) {
        *(int *)(D_0029C4F0 + *(unsigned char *)(g + 0x18) * 4) = (int)g;
    }
    *(int *)(g + 0x15C) = 0;
    *(int *)(g + 0x8) = -1;
    *(int *)(g + 0x4) = -1;
    *(int *)(g + 0x2C) = 0;
    *(int *)(g + 0x30) = 0;
    *(int *)(g + 0x58) = 0;
    return g;
}

int isysGetNbAllocedGObjs(void)
{
    int result = 0;
    unsigned int i;
    for (i = 0; i < gobjMax; i++) {
        if (*(int *)((char *)gobjTable + i * 0x174) != 0) {
            result++;
        }
    }
    return result;
}

extern char D_0063A608[];

inline void isysGObjRemove(char *g)
{
    int kind = *(int *)(g + 0xC);
    char *proc = *(char **)(g + 0x2C);
    char *p;
    if ((unsigned int)(kind - 1) < 0x45) {
        p = gobjKindHead[kind];
        if (p == g) {
            gobjKindHead[kind] = *(char **)(g + 0x3C);
        } else if (p != 0) {
            while (*(char **)(p + 0x3C) != g) {
                if (p == 0) {
                    debug_assert(__FILE__, 0x92);
                    __assert(__FILE__, 0x92, D_0063A608);
                }
                p = *(char **)(p + 0x3C);
            }
            *(char **)(p + 0x10) = *(char **)(g + 0x3C);
        }
    }
    cut_gobj_link((int)g);
    *(int *)g = 0;
    while (proc != 0) {
        isysGObjProcRemove(proc);
        proc = *(char **)(g + 0x2C);
    }
}

extern int D_0063A600;
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_begin do not fit the prototype in gobj.h */
extern void *isysGObjSearchFromObjKindID_begin(int kind);
/* kept local: this TU's uses of isysGObjSearchFromObjKindID_next do not fit the prototype in gobj.h */
extern void *isysGObjSearchFromObjKindID_next(char *g);
/* kept local: this TU's uses of isysGObjKindTableRemove do not fit the prototype in gobj.h */
extern void isysGObjKindTableRemove(char *g);

inline void isysGObjKindTableAdd(char *g, int kind)
{
    char *p;

    if (D_0063A600 != 0) {
        *(int *)(g + 0xC) = kind;
        return;
    }
    for (p = isysGObjSearchFromObjKindID_begin(*(int *)(g + 0xC)); p != 0;
         isysGObjSearchFromObjKindID_next(p)) {
        if (p == g) {
            isysGObjKindTableRemove(g);
            break;
        }
    }
    *(int *)(g + 0xC) = kind;
    if ((unsigned int)kind < 0x46) {
        if (gobjKindHead[kind] == 0) {
            gobjKindHead[kind] = g;
        } else {
            p = gobjKindHead[kind];
            while (*(char **)(p + 0x3C) != 0) {
                p = *(char **)(p + 0x3C);
            }
            *(char **)(p + 0x3C) = g;
        }
        *(char **)(g + 0x3C) = 0;
    }
}

extern char D_0063A608[];

inline void isysGObjKindTableRemove(char *g)
{
    int kind = *(int *)(g + 0xC);
    char *p;
    if ((unsigned int)(kind - 1) < 0x45) {
        p = gobjKindHead[kind];
        if (p == g) {
            gobjKindHead[kind] = *(char **)(g + 0x3C);
            return;
        }
        if (p == 0)
            return;
        while (*(char **)(p + 0x3C) != g) {
            if (p == 0) {
                debug_assert(__FILE__, 0x92);
                __assert(__FILE__, 0x92, D_0063A608);
            }
            p = *(char **)(p + 0x3C);
        }
        *(char **)(p + 0x10) = *(char **)(g + 0x3C);
    }
}

/* kept local: this TU's uses of cut_gobj_link do not fit the prototype in gobj.h */
extern void cut_gobj_link(int a0);

inline void isysGObjMoveAfterGObj(char *self, char *other)
{
    cut_gobj_link((int)self);
    *(unsigned char *)(self + 0x18) = *(unsigned char *)(other + 0x18);
    *(char **)(self + 0x14) = other;
    *(char **)(self + 0x10) = *(char **)(other + 0x10);
    *(char **)(other + 0x10) = self;
    *(int *)(self + 0x1C) = *(int *)(other + 0x1C);
    if (*(char **)(self + 0x10) == 0) {
        D_0029C510[*(unsigned char *)(self + 0x18)] = self;
    }
}

extern char D_0029C4F0[];
/* kept local: this TU's uses of cut_gobj_link do not fit the prototype in gobj.h */
extern void cut_gobj_link(int a0);

inline void isysGObjMoveBeforeGObj(int self, int other)
{
    unsigned char t;
    int u;
    cut_gobj_link(self);
    t = *(unsigned char *)(other + 0x18);
    *(unsigned char *)(self + 0x18) = t;
    u = *(int *)(other + 0x14);
    *(int *)(self + 0x10) = other;
    *(int *)(self + 0x14) = u;
    *(int *)(other + 0x14) = self;
    *(int *)(self + 0x1C) = *(int *)(other + 0x1C);
    if (*(int *)(self + 0x14) == 0) {
        *(int *)(D_0029C4F0 + *(unsigned char *)(self + 0x18) * 4) = self;
    }
}

inline char *isysGObjAdd(char *owner, int a1, int a2)
{
    int kind = a1 & 0xFF;
    int prio = a2;
    char *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    *(char **)(g + 0x28) = owner;
    *(int *)g = (int)g;
    add_gobj_to_tail((int)g, kind, prio);
    *(int *)(g + 0x15C) = 0;
    *(int *)(g + 0x8) = -1;
    *(int *)(g + 0x4) = -1;
    *(int *)(g + 0x2C) = 0;
    *(int *)(g + 0x30) = 0;
    *(int *)(g + 0x58) = 0;
    *(int *)(g + 0xC) = 0;
    return g;
}

inline char *isysGObjAddHead(char *owner, int a1, int a2)
{
    int kind = a1 & 0xFF;
    int prio = a2;
    char *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    *(char **)(g + 0x28) = owner;
    *(int *)g = (int)g;
    add_gobj_to_head(g, kind, prio);
    *(int *)(g + 0x15C) = 0;
    *(int *)(g + 0x8) = -1;
    *(int *)(g + 0x4) = -1;
    *(int *)(g + 0x2C) = 0;
    *(int *)(g + 0x30) = 0;
    *(int *)(g + 0x58) = 0;
    return g;
}

inline void *isysGObjSearchFromObjLayoutID(int a0)
{
    unsigned int i;
    for (i = 0; i < gobjMax; i++) {
        char *e = (char *)gobjTable + i * 0x174;
        if (*(int *)e != 0 && *(int *)(e + 4) == 1 && *(int *)(e + 8) == a0)
            return e;
    }
    return 0;
}

/* static helper the listing places at gobj.c lines 657-667; never emitted out
 * of line, so it has no MAIN.MAP symbol and this name is ours. */
static __inline__ void *searchGObjOfObjKind(char *p, int kind)
{
    char *end = (char *)gobjTable + (gobjMax * 0x174 - 0x174);

    while (p != end) {
        p += 0x174;
        if (*(int *)(p + 4) == 1 && *(int *)(p + 0xC) == kind)
            return p;
    }
    return 0;
}

inline void *isysGObjSearchFromObjKindID_begin(int kind)
{
    if (D_0063A600 != 0) {
        return searchGObjOfObjKind((char *)gobjTable - 0x174, kind);
    }
    if ((unsigned int)(kind - 1) < 0x45) {
        return gobjKindHead[kind];
    }
    return 0;
}

inline void *isysGObjSearchFromObjKindID_next(char *g)
{
    if (D_0063A600 != 0) {
        return searchGObjOfObjKind(g, *(int *)(g + 0xC));
    }
    return *(char **)(g + 0x3C);
}

inline void *isysGObjSearchFromLabelTypeID(int a0)
{
    unsigned int i;
    for (i = 0; i < gobjMax; i++) {
        char *e = (char *)gobjTable + i * 0x174;
        if (*(int *)e != 0 && *(int *)(e + 4) == a0)
            return e;
    }
    return 0;
}

inline struct GObj__p4 *isysGObjGetExist_begin(void)
{
    struct GObj__p4 *start = (struct GObj__p4 *)gobjTable - 1;
    struct GObj__p4 *end = (struct GObj__p4 *)((char *)gobjTable + (gobjMax * 0x174 - 0x174));
    while (start != end) {
        start++;
        if (start->unk0 != 0) {
            return start;
        }
    }
    return 0;
}

inline struct GObj__p4 *isysGObjGetExist_next(struct GObj__p4 *start)
{
    struct GObj__p4 *end = (struct GObj__p4 *)((char *)gobjTable + (gobjMax * 0x174 - 0x174));
    while (start != end) {
        start++;
        if (start->unk0 != 0) {
            return start;
        }
    }
    return 0;
}

extern int D_0063A60C;

inline void isysGObjActiveLink(int bit, int set)
{
    if (set != 0)
        goto set_path;
    D_0063A60C &= ~(1 << bit);
    return;
set_path:
    D_0063A60C |= (1 << bit);
}

extern unsigned int D_0063A610;

inline void isysGObjActiveDlLink(int a0, int a1)
{
    if (a1 == 0) {
        D_0063A610 &= ~(1 << a0);
    } else {
        D_0063A610 |= (1 << a0);
    }
}
