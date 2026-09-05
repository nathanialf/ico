#include "common.h"

static void add_gobj_to_head(int a0, int a1, int a2);
typedef struct DLN {
    char _p0[0x34];
    struct DLN *next;
    struct DLN *prev;
    char _p1[0x4];
    unsigned char id;
    char _p2[0x3];
    int key;
} DLN;
extern void cut_gobj_dl_link(int *self);
extern int D_0029C530[];
extern int D_0029C550[];
extern void func_00141248(int a0, int a1, int a2);
extern char D_00551F78[];
extern void debug_StdPrintfDummy();
/* prototypes: their order is the inline tail's emission order */
/* the listing's add_gobj_to_head; every gobj list TU has its own static copy, so the
   symbol-table name stays the placeholder (the other TU's copy owns the name) */
extern char D_00551FD0[];
extern char D_00551FE0[];
void isysGObjDlInit(void);
void isysGObjMoveObjDLAfterGObj(DLN *self, DLN *obj);
void isysGObjMoveObjDLBeforeGObj(DLN *self, DLN *obj);
inline void isysGObjDlInit(void) {
    int i;
    for (i = 0; i < 8; i++) {
        D_0029C530[i] = 0;
        D_0029C550[i] = 0;
    }
}
void cut_gobj_dl_link(int *self)
{
    DLN *p = (DLN *)self;

    if (p == 0) {
        debug_StdPrintfDummy(D_00551F78);
        return;
    }

    if (p->prev == 0 && p->next == 0) {
        /* not linked into a list */
    } else {
        if (p->prev != 0) p->prev->next = p->next;

        if (p->next != 0) {
            p->next->prev = p->prev;
        }
    }

    if (p == ((DLN **)D_0029C530)[p->id]) {
        ((DLN **)D_0029C530)[p->id] = p->next;
    }
    if (p == ((DLN **)D_0029C550)[p->id]) {
        ((DLN **)D_0029C550)[p->id] = p->prev;
    }
}
void isysGObjRemoveObjDL(int *self) {
    cut_gobj_dl_link(self);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", func_00141248);
static void add_gobj_to_head(int a0, int a1, int a2)
{
    DLN *self = (DLN *)a0;
    unsigned char idx = a1 & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;
    self->id = idx;
    self->key = a2;
    head = ((DLN **)D_0029C530)[idx];
    if (head == 0) {
        ((DLN **)D_0029C530)[idx] = self;
        self->prev = 0;
        self->next = 0;
        ((DLN **)D_0029C550)[idx] = self;
        return;
    }
    if ((unsigned int)head->key >= (unsigned int)a2) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        ((DLN **)D_0029C530)[idx] = self;
        return;
    }
    tail = ((DLN **)D_0029C550)[idx];
    if ((unsigned int)tail->key < (unsigned int)a2) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        ((DLN **)D_0029C550)[idx] = self;
        return;
    }
    cur = head;
    while ((unsigned int)cur->next->key < (unsigned int)a2) {
        cur = cur->next;
    }
    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}
void isysGObjMoveObjDL(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    cut_gobj_dl_link(a0);
    return func_00141248(a0, s1, new_var);
}
void isysGObjMoveObjDLHead(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    cut_gobj_dl_link(a0);
    return add_gobj_to_head(a0, s1, new_var);
}
inline void isysGObjMoveObjDLAfterGObj(DLN *self, DLN *obj) {
    cut_gobj_dl_link((int *)self);
    self->id = obj->id;
    self->prev = obj;
    self->next = obj->next;
    obj->next = self;
    self->key = obj->key;
    if (self->next == 0) {
        ((DLN **)D_0029C550)[self->id] = self;
    }
}
inline void isysGObjMoveObjDLBeforeGObj(DLN *self, DLN *obj) {
    cut_gobj_dl_link((int *)self);
    self->id = obj->id;
    self->prev = obj->prev;
    self->next = obj;
    obj->prev = self;
    self->key = obj->key;
    if (self->prev == 0) {
        ((DLN **)D_0029C530)[self->id] = self;
    }
}
void isysGObjLinkObjDL(void *a0, void *a1, unsigned char a2, void *a3, void *a4) {
    debug_StdPrintfDummy(D_00551FD0);
    if (a1 != 0) {
        *(void **)((char *)a0 + 0x48) = a1;
        *(void **)((char *)a0 + 0x50) = a4;
        func_00141248(a0, a2, a3);
        debug_StdPrintfDummy(D_00551FE0);
    }
}
void isysGObjLinkObjDLHead(void *a0, void *a1, unsigned char a2, void *a3, void *a4) {
    if (a1 != 0) {
        *(void **)((char *)a0 + 0x48) = a1;
        *(void **)((char *)a0 + 0x50) = a4;
        add_gobj_to_head(a0, a2, a3);
    }
}
void isysGObjLinkObjDLAfterGObj(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_StdPrintfDummy(D_00551F78);
        return;
    }
    t0[0x14] = a2;
    t0[0x12] = (int)a1;
    *((unsigned char *)t0 + 0x40) = *((unsigned char *)a3 + 0x40);
    t0[0xE] = (int)a3;
    v34 = a3[0xD];
    v44 = a3[0x11];
    t0[0xD] = v34;
    a3[0xD] = (int)t0;
    t0[0x11] = v44;
    if (t0[0xD] == 0) {
        D_0029C550[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}
void isysGObjLinkObjDLBeforeGObj(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_StdPrintfDummy(D_00551F78);
        return;
    }
    t0[0x14] = a2;
    t0[0x12] = (int)a1;
    *((unsigned char *)t0 + 0x40) = *((unsigned char *)a3 + 0x40);
    t0[0xE] = (int)a3;
    v34 = a3[0xD];
    v44 = a3[0x11];
    t0[0xD] = v34;
    a3[0xD] = (int)t0;
    t0[0x11] = v44;
    if (t0[0xD] == 0) {
        D_0029C550[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}
