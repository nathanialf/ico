#include "debug.h"
#include "memory.h"
#include "ios.h"
#include "typedef.h"
#include "isys.h"
#include "gobj.h"

/* the head of the free list for each of the 70 object kinds */
static GObj *gobjKindHead[70]; /* derived name */

/* Deferred-`inline` tail: ee-gcc 2.9 emits a plain-`inline` function's
   out-of-line copy at the END of the object in PROTOTYPE order while its
   string literals are emitted where it is DEFINED.  That is what puts the
   __FILE__ string, first used by isysGObjAlloc, at the head of this TU's
   .rodata run even though its code sits in the object's tail. */
inline void isysGObjAlloc(int n);
inline void isysGObjRemove(GObj *g);
inline void isysGObjKindTableAdd(GObj *g, int kind);
inline void isysGObjKindTableRemove(GObj *g);
inline void isysGObjMoveAfterGObj(GObj *self, GObj *other);
inline void isysGObjMoveBeforeGObj(GObj *self, GObj *other);
inline void *isysGObjAdd(void (*fn)(GObj *), int a1, int a2);
inline void *isysGObjAddHead(void (*fn)(GObj *), int a1, int a2);
inline void *isysGObjSearchFromObjLayoutID(int a0);
inline void *isysGObjSearchFromObjKindID_begin(int kind);
inline void *isysGObjSearchFromObjKindID_next(GObj *g);
inline void *isysGObjSearchFromLabelTypeID(int a0);
inline void *isysGObjGetExist_begin(void);
inline void *isysGObjGetExist_next(GObj *start);
inline void isysGObjActiveLink(int bit, int set);
inline void isysGObjActiveDlLink(int a0, int a1);

void isysGObjKindTableInit(void)
{
    memset(gobjKindHead, 0, sizeof(gobjKindHead));
}

void isysGObjInit(int n)
{
    int i;

    for (i = 0; i < 8; i++) {
        gobj_link_head[i] = 0;
        gobj_link_tail[i] = 0;
    }
    isysGObjAlloc(n);
    active_gobj_link = 0;
    active_gobj_dl_link = 0;
    isysGObjKindTableInit();
}

/* the object table and how many 0x174-byte entries isysGObjAlloc gave it */
static GObj *gobjTable; /* derived name */

static unsigned int gobjMax; /* derived name */

inline void isysGObjAlloc(int n)
{
    GObj *tbl;
    unsigned int i;

    gobjTable = iosMallocDebug(ios_partition_isys, n * sizeof(GObj), __FILE__, 174);
    gobjMax = n;
    tbl = gobjTable;
    for (i = 0; i < n; i++) {
        tbl[i].self = 0;
        tbl[i].dobj = 0;
        tbl[i].labelId = -1;
        tbl[i].labelType = -1;
    }
}

int debugKindOld = 0;

void cut_gobj_link(GObj *p)
{
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

    if (p == gobj_link_head[p->linkId]) {
        gobj_link_head[p->linkId] = p->next;
    }
    if (p == gobj_link_tail[p->linkId]) {
        gobj_link_tail[p->linkId] = p->prev;
    }
}

/* the kind-table unlink, which isysGObjKindTableRemove and the object
 * removal inline */
static __inline__ void kindTableRemove(GObj *g) /* derived name */
{
    int kind = g->kind;
    GObj *p;
    if ((unsigned int)(kind - 1) < 69) {
        p = gobjKindHead[kind];
        if (p == g) {
            gobjKindHead[kind] = g->kindNext;
            return;
        }
        if (p == 0)
            return;
        while (p->kindNext != g) {
            if (p == 0) {
                debug_assert(__FILE__, 146);
                __assert(__FILE__, 146, "0");
            }
            p = p->kindNext;
        }
        p->next = g->kindNext;
    }
}

/* the object removal, which isysGObjRemove and isysGObjRemoveAll inline */
static __inline__ void removeGObjEntry(GObj *g) /* derived name */
{
    struct GProc *proc = g->procHead;

    kindTableRemove(g);
    cut_gobj_link(g);
    g->self = 0;
    while (proc != 0) {
        isysGObjProcRemove(proc);
        proc = g->procHead;
    }
}

void isysGObjRemoveAll(void)
{
    unsigned int i;

    for (i = 0; i < gobjMax; i++) {
        if (gobjTable[i].self != 0)
            removeGObjEntry(&gobjTable[i]);
    }
    isysGObjKindTableInit();
}

void add_gobj_to_tail(GObj *g, int a1, int a2)
{
    unsigned char kind = a1;
    unsigned int val = a2;
    GObj *head;
    GObj *tail;
    GObj *p;
    g->linkId = kind;
    g->key = val;
    head = gobj_link_head[kind];
    if (head == 0) {
        gobj_link_head[kind] = g;
        g->prev = 0;
        g->next = 0;
        gobj_link_tail[kind] = g;
        return;
    }
    if (val < head->key) {
        g->prev = 0;
        g->next = head;
        gobj_link_head[kind] = g;
        head->prev = g;
        return;
    }
    tail = gobj_link_tail[kind];
    if (!(val < tail->key)) {
        g->prev = tail;
        g->next = 0;
        gobj_link_tail[kind] = g;
        tail->next = g;
        return;
    }
    p = head;
    while (!(val < p->next->key)) {
        p = p->next;
    }
    g->prev = p;
    g->next = p->next;
    p->next = g;
    g->next->prev = g;
}

void add_gobj_to_head(GObj *g, int a1, int a2)
{
    unsigned char kind = a1;
    unsigned int val = a2;
    GObj *head;
    GObj *tail;
    GObj *p;
    g->linkId = kind;
    g->key = val;
    head = gobj_link_head[kind];
    if (head == 0) {
        gobj_link_head[kind] = g;
        g->prev = 0;
        g->next = 0;
        gobj_link_tail[kind] = g;
        return;
    }
    if (!(head->key < val)) {
        g->prev = 0;
        g->next = head;
        gobj_link_head[kind] = g;
        head->prev = g;
        return;
    }
    tail = gobj_link_tail[kind];
    if (tail->key < val) {
        g->prev = tail;
        g->next = 0;
        gobj_link_tail[kind] = g;
        tail->next = g;
        return;
    }
    p = head;
    while (p->next->key < val) {
        p = p->next;
    }
    g->prev = p;
    g->next = p->next;
    p->next = g;
    g->next->prev = g;
}

void isysGObjMove(GObj *g, unsigned char a1, int a2)
{
    cut_gobj_link(g);
    return add_gobj_to_tail(g, a1, a2);
}

void isysGObjMoveHead(GObj *g, unsigned char a1, int a2)
{
    cut_gobj_link(g);
    return add_gobj_to_head(g, a1, a2);
}

/* link g into other's list after other, taking its list and key */
static __inline__ void linkGObjAfter(GObj *g, GObj *other) /* derived name */
{
    g->linkId = other->linkId;
    g->key = other->key;
    g->prev = other;
    g->next = other->next;
    other->next = g;
    if (g->next == 0) {
        gobj_link_tail[g->linkId] = g;
    }
}

/* the first free entry of the object table, or 0 when the table is full */
static __inline__ GObj *allocGObjEntry(void) /* derived name */
{
    unsigned int i;
    GObj *g;

    for (i = 0; i < gobjMax; i++) {
        if (gobjTable[i].self == 0) {
            break;
        }
    }
    if (i == gobjMax) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    /* the entry's address from the table's address and the scaled index */
    g = (GObj *)(i * sizeof(GObj) + (int)gobjTable);
    g->act = 0;
    g->pauseExempt = 0;
    return g;
}

void *isysGObjAddAfterGObj(void (*fn)(GObj *), GObj *other)
{
    GObj *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    if (other == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return 0;
    }
    g->self = g;
    g->fn = fn;
    linkGObjAfter(g, other);
    g->dobj = 0;
    g->labelId = -1;
    g->labelType = -1;
    g->procHead = 0;
    g->procTail = 0;
    g->mailNum = 0;
    return g;
}

void *isysGObjAddBeforeGObj(void (*fn)(GObj *), GObj *other)
{
    unsigned char t;
    GObj *u;
    GObj *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    if (other == 0) {
        debug_StdPrintfDummy("isys:null GObj\n");
        return 0;
    }
    g->self = g;
    g->fn = fn;
    t = other->linkId;
    g->linkId = t;
    u = other->prev;
    g->next = other;
    g->prev = u;
    other->prev = g;
    g->key = other->key;
    if (g->prev == 0) {
        gobj_link_head[g->linkId] = g;
    }
    g->dobj = 0;
    g->labelId = -1;
    g->labelType = -1;
    g->procHead = 0;
    g->procTail = 0;
    g->mailNum = 0;
    return g;
}

int isysGetNbAllocedGObjs(void)
{
    int result = 0;
    unsigned int i;
    for (i = 0; i < gobjMax; i++) {
        if (gobjTable[i].self != 0) {
            result++;
        }
    }
    return result;
}

inline void isysGObjRemove(GObj *g)
{
    removeGObjEntry(g);
}

inline void isysGObjKindTableAdd(GObj *g, int kind)
{
    GObj *p;

    if (debugKindOld != 0) {
        g->kind = kind;
        return;
    }
    for (p = isysGObjSearchFromObjKindID_begin(g->kind); p != 0;
         isysGObjSearchFromObjKindID_next(p)) {
        if (p == g) {
            isysGObjKindTableRemove(g);
            break;
        }
    }
    g->kind = kind;
    if ((unsigned int)kind < 70) {
        if (gobjKindHead[kind] == 0) {
            gobjKindHead[kind] = g;
        } else {
            p = gobjKindHead[kind];
            while (p->kindNext != 0) {
                p = p->kindNext;
            }
            p->kindNext = g;
        }
        g->kindNext = 0;
    }
}

inline void isysGObjKindTableRemove(GObj *g)
{
    kindTableRemove(g);
}

inline void isysGObjMoveAfterGObj(GObj *self, GObj *other)
{
    cut_gobj_link(self);
    self->linkId = other->linkId;
    self->prev = other;
    self->next = other->next;
    other->next = self;
    self->key = other->key;
    if (self->next == 0) {
        gobj_link_tail[self->linkId] = self;
    }
}

inline void isysGObjMoveBeforeGObj(GObj *self, GObj *other)
{
    unsigned char t;
    GObj *u;
    cut_gobj_link(self);
    t = other->linkId;
    self->linkId = t;
    u = other->prev;
    self->next = other;
    self->prev = u;
    other->prev = self;
    self->key = other->key;
    if (self->prev == 0) {
        gobj_link_head[self->linkId] = self;
    }
}

inline void *isysGObjAdd(void (*fn)(GObj *), int a1, int a2)
{
    int kind = a1 & 0xFF;
    int prio = a2;
    GObj *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    g->fn = fn;
    g->self = g;
    add_gobj_to_tail(g, kind, prio);
    g->dobj = 0;
    g->labelId = -1;
    g->labelType = -1;
    g->procHead = 0;
    g->procTail = 0;
    g->mailNum = 0;
    g->kind = 0;
    return g;
}

inline void *isysGObjAddHead(void (*fn)(GObj *), int a1, int a2)
{
    int kind = a1 & 0xFF;
    int prio = a2;
    GObj *g = allocGObjEntry();

    if (g == 0) {
        debug_StdPrintfDummy("isys:not enough memory for GObj\n");
        return 0;
    }
    g->fn = fn;
    g->self = g;
    add_gobj_to_head(g, kind, prio);
    g->dobj = 0;
    g->labelId = -1;
    g->labelType = -1;
    g->procHead = 0;
    g->procTail = 0;
    g->mailNum = 0;
    return g;
}

inline void *isysGObjSearchFromObjLayoutID(int a0)
{
    unsigned int i;
    for (i = 0; i < gobjMax; i++) {
        GObj *e = &gobjTable[i];
        if (e->self != 0 && e->labelType == 1 && e->labelId == a0)
            return e;
    }
    return 0;
}

/* the next live object after p of the given kind, or 0 */
static __inline__ GObj *searchGObjOfObjKind(GObj *p, int kind) /* derived name */
{
    GObj *end = &gobjTable[gobjMax - 1];

    while (p != end) {
        p++;
        if (p->labelType == 1 && p->kind == kind)
            return p;
    }
    return 0;
}

inline void *isysGObjSearchFromObjKindID_begin(int kind)
{
    if (debugKindOld != 0) {
        return searchGObjOfObjKind(gobjTable - 1, kind);
    }
    if ((unsigned int)(kind - 1) < 69) {
        return gobjKindHead[kind];
    }
    return 0;
}

inline void *isysGObjSearchFromObjKindID_next(GObj *g)
{
    if (debugKindOld != 0) {
        return searchGObjOfObjKind(g, g->kind);
    }
    return g->kindNext;
}

inline void *isysGObjSearchFromLabelTypeID(int a0)
{
    unsigned int i;
    for (i = 0; i < gobjMax; i++) {
        GObj *e = &gobjTable[i];
        if (e->self != 0 && e->labelType == a0)
            return e;
    }
    return 0;
}

inline void *isysGObjGetExist_begin(void)
{
    GObj *start = gobjTable - 1;
    GObj *end = &gobjTable[gobjMax - 1];
    while (start != end) {
        start++;
        if (start->self != 0) {
            return start;
        }
    }
    return 0;
}

inline void *isysGObjGetExist_next(GObj *start)
{
    GObj *end = &gobjTable[gobjMax - 1];
    while (start != end) {
        start++;
        if (start->self != 0) {
            return start;
        }
    }
    return 0;
}

inline void isysGObjActiveLink(int bit, int set)
{
    if (set != 0)
        goto set_path;
    active_gobj_link &= ~(1 << bit);
    return;
set_path:
    active_gobj_link |= (1 << bit);
}

inline void isysGObjActiveDlLink(int a0, int a1)
{
    if (a1 == 0) {
        active_gobj_dl_link &= ~(1 << a0);
    } else {
        active_gobj_dl_link |= (1 << a0);
    }
}
