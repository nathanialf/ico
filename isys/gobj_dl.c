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

struct GObj__p4 { int unk0; int unk4; int unk8; char pad[0x168]; };




extern int D_00281AD0[];
extern char D_00557A58[];
extern void debug_assertMessage();
extern int D_006321D0;
extern int D_006321CC;
INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", cut_gobj_dl_link);

extern struct GObj__p4 *D_00633CA0;
extern unsigned int D_00633CA4;

struct GObj__p4 *isysGObjRemoveObjDL(void)
{
    struct GObj__p4 *start = D_00633CA0 - 1;
    struct GObj__p4 *end = (struct GObj__p4 *)((char *)D_00633CA0 + (D_00633CA4 * 0x174 - 0x174));
    while (start != end) {
        start++;
        if (start->unk0 != 0) {
            return start;
        }
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", func_0013ECF8);

void func_0013ED40(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321CC &= ~(1 << bit);
    return;
set_path:
    D_006321CC |= (1 << bit);
}

void isysGObjMoveObjDL(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321D0 &= ~(1 << bit);
    return;
set_path:
    D_006321D0 |= (1 << bit);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjMoveObjDLHead);

extern void isysGObjMoveObjDLHead(int *self);

void isysGObjLinkObjDL(int *self) {
    isysGObjMoveObjDLHead(self);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjLinkObjDLHead);

extern int D_00281AB0[];

void isysGObjLinkObjDLAfterGObj(int a0, int a1, int a2)
{
    DLN *self = (DLN *)a0;
    unsigned char idx = a1 & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;
    self->id = idx;
    self->key = a2;
    head = ((DLN **)D_00281AB0)[idx];
    if (head == 0) {
        ((DLN **)D_00281AB0)[idx] = self;
        self->prev = 0;
        self->next = 0;
        ((DLN **)D_00281AD0)[idx] = self;
        return;
    }
    if ((unsigned int)head->key >= (unsigned int)a2) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        ((DLN **)D_00281AB0)[idx] = self;
        return;
    }
    tail = ((DLN **)D_00281AD0)[idx];
    if ((unsigned int)tail->key < (unsigned int)a2) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        ((DLN **)D_00281AD0)[idx] = self;
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

extern void isysGObjLinkObjDLHead(int a0, int a1, int a2);

void isysGObjLinkObjDLBeforeGObj(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    isysGObjMoveObjDLHead(a0);
    return isysGObjLinkObjDLHead(a0, s1, new_var);
}

void isysGObjDlInit(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    isysGObjMoveObjDLHead(a0);
    return isysGObjLinkObjDLAfterGObj(a0, s1, new_var);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjMoveObjDLAfterGObj);

void isysGObjMoveObjDLBeforeGObj(void *a0, void *a1, unsigned char a2, void *a3, void *a4) {
    if (a1 != 0) {
        *(void **)((char *)a0 + 0x48) = a1;
        *(void **)((char *)a0 + 0x50) = a4;
        isysGObjLinkObjDLAfterGObj(a0, a2, a3);
    }
}

void func_0013F1F8(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_assertMessage(D_00557A58);
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
        D_00281AD0[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}

void func_0013F260(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_assertMessage(D_00557A58);
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
        D_00281AD0[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}

