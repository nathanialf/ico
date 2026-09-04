#include "common.h"

typedef struct DLN {
    char _p0[0x34];
    struct DLN *next;
    struct DLN *prev;
    char _p1[0x4];
    unsigned char id;
    char _p2[0x3];
    int key;
} DLN;

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", cut_gobj_dl_link);
extern void cut_gobj_dl_link(int *self);

void isysGObjRemoveObjDL(int *self) {
    cut_gobj_dl_link(self);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", func_00141248);
extern int D_0029C530[];
extern int D_0029C550[];

void func_001413B8(int a0, int a1, int a2)
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
extern void func_00141248(int a0, int a1, int a2);

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
    return func_001413B8(a0, s1, new_var);
}
INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjLinkObjDL);
void isysGObjLinkObjDLHead(void *a0, void *a1, unsigned char a2, void *a3, void *a4) {
    if (a1 != 0) {
        *(void **)((char *)a0 + 0x48) = a1;
        *(void **)((char *)a0 + 0x50) = a4;
        func_001413B8(a0, a2, a3);
    }
}
extern char D_00551F78[];
extern void debug_StdPrintfDummy();

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
INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjDlInit);
extern void cut_gobj_dl_link(int *self);

void isysGObjMoveObjDLAfterGObj(DLN *self, DLN *obj) {
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
void isysGObjMoveObjDLBeforeGObj(DLN *self, DLN *obj) {
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
