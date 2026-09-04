#include "common.h"

struct GObj { int unk0; int unk4; int unk8; char pad[0x168]; };
extern struct GObj *D_0062BFA8;
extern unsigned int D_0062BFAC;

const char D_00551E28[0x10] = "isys:null GObj\n";
const char D_00551E38[0x18] = "gobj dl added to tail\n";
const char D_00551E50[0x10] = "no_entry %p\n";
const char D_00551E60[0x10] = "add to head %p\n";
const char D_00551E70[0x10] = "add to tail %p\n";
const char D_00551E80[0x10] = "GObjLinkDL in\n";
const char D_00551E90[0x10] = "GObjLinkDL out\n";

struct GObj *isysGObjSearchFromLabelTypeID(int a0)
{
    unsigned int count = D_0062BFAC;
    unsigned int i = 0;
    if (count != 0) {
        do {
            struct GObj *e = &D_0062BFA8[i];
            if (e->unk0 != 0 && e->unk4 == a0) {
                return e;
            }
            i++;
        } while (i < count);
    }
    return 0;
}

struct GObj *isysGObjGetExist_begin(void)
{
    struct GObj *start = D_0062BFA8 - 1;
    struct GObj *end = (struct GObj *)((char *)D_0062BFA8 + (D_0062BFAC * 0x174 - 0x174));
    while (start != end) {
        start++;
        if (start->unk0 != 0) {
            return start;
        }
    }
    return 0;
}

struct GObj *isysGObjGetExist_next(struct GObj *start)
{
    struct GObj *end = (struct GObj *)((char *)D_0062BFA8 + (D_0062BFAC * 0x174 - 0x174));
    while (start != end) {
        start++;
        if (start->unk0 != 0) {
            return start;
        }
    }
    return 0;
}

extern unsigned int D_0062A4CC;

void func_0013E828(int a0, int a1) {
    if (a1 == 0) {
        D_0062A4CC &= ~(1 << a0);
    } else {
        D_0062A4CC |= (1 << a0);
    }
}

extern unsigned int D_0062A4D0;

void isysGObjMoveObjDL(int a0, int a1) {
    if (a1 == 0) {
        D_0062A4D0 &= ~(1 << a0);
    } else {
        D_0062A4D0 |= (1 << a0);
    }
}

extern void debug_StdPrintfDummy();
extern int D_0027DE30[];
extern int D_0027DE50[];

void cut_gobj_dl_link(int *self)
{
    if (self == 0) {
        debug_StdPrintfDummy(D_00551E28);
        return;
    }
    if (self[0xE] != 0) goto do_prev;
    if (self[0xD] == 0) goto head;
    goto merge;
do_prev:
    ((int *)self[0xE])[0xD] = self[0xD];
merge:
    if (self[0xD] != 0) {
        ((int *)self[0xD])[0xE] = self[0xE];
    }
head:
    if ((int)self == D_0027DE30[*((unsigned char *)self + 0x40)]) {
        D_0027DE30[*((unsigned char *)self + 0x40)] = self[0xD];
    }
    if ((int)self == D_0027DE50[*((unsigned char *)self + 0x40)]) {
        D_0027DE50[*((unsigned char *)self + 0x40)] = self[0xE];
    }
}

void isysGObjLinkObjDL(int *self) {
    cut_gobj_dl_link(self);
}

typedef struct DLN {
    char _p0[0x34];
    struct DLN *next;
    struct DLN *prev;
    char _p1[0x4];
    unsigned char id;
    char _p2[0x3];
    int key;
} DLN;

void isysGObjLinkObjDLHead(int a0, int a1, int a2)
{
    DLN *self = (DLN *)a0;
    unsigned char idx = a1 & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;
    debug_StdPrintfDummy(D_00551E38);
    self->id = idx;
    self->key = a2;
    head = ((DLN **)D_0027DE30)[idx];
    if (head == 0) {
        self->prev = 0;
        self->next = 0;
        ((DLN **)D_0027DE30)[idx] = self;
        ((DLN **)D_0027DE50)[idx] = self;
        debug_StdPrintfDummy(D_00551E50, 0);
        return;
    }
    if ((unsigned int)a2 < (unsigned int)head->key) {
        self->next = head;
        self->prev = 0;
        head->prev = self;
        ((DLN **)D_0027DE30)[idx] = self;
        debug_StdPrintfDummy(D_00551E60, (int)self->next);
        return;
    }
    tail = ((DLN **)D_0027DE50)[idx];
    if ((unsigned int)a2 >= (unsigned int)tail->key) {
        self->next = 0;
        self->prev = tail;
        tail->next = self;
        ((DLN **)D_0027DE50)[idx] = self;
        debug_StdPrintfDummy(D_00551E70, (int)self->next);
        return;
    }
    cur = head;
    while ((unsigned int)a2 >= (unsigned int)cur->next->key) {
        cur = cur->next;
    }
    self->prev = cur;
    self->next = cur->next;
    cur->next = self;
    self->next->prev = self;
}

void isysGObjLinkObjDLAfterGObj(int a0, int a1, int a2)
{
    DLN *self = (DLN *)a0;
    unsigned char idx = a1 & 0xFF;
    DLN *head;
    DLN *tail;
    DLN *cur;
    self->id = idx;
    self->key = a2;
    head = ((DLN **)D_0027DE30)[idx];
    if (head == 0) {
        ((DLN **)D_0027DE30)[idx] = self;
        self->prev = 0;
        self->next = 0;
        ((DLN **)D_0027DE50)[idx] = self;
        return;
    }
    if ((unsigned int)head->key >= (unsigned int)a2) {
        self->prev = 0;
        self->next = head;
        head->prev = self;
        ((DLN **)D_0027DE30)[idx] = self;
        return;
    }
    tail = ((DLN **)D_0027DE50)[idx];
    if ((unsigned int)tail->key < (unsigned int)a2) {
        self->prev = tail;
        self->next = 0;
        tail->next = self;
        ((DLN **)D_0027DE50)[idx] = self;
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
    cut_gobj_dl_link(a0);
    return isysGObjLinkObjDLHead(a0, s1, new_var);
}

extern void isysGObjLinkObjDLAfterGObj(int a0, int a1, int a2);

void isysGObjDlInit(int a0, int a1, int a2)
{
    int s1 = a1 & 0xFF;
    int new_var;
    new_var = a2;
    cut_gobj_dl_link(a0);
    return isysGObjLinkObjDLAfterGObj(a0, s1, new_var);
}

extern void debug_StdPrintfDummy();

void isysGObjMoveObjDLAfterGObj(int *self, int *p, unsigned char q, int r, int t0)
{
  int new_var2;
  int new_var;
  int *new_var3;
  new_var = q & 0xFF;
  debug_StdPrintfDummy(D_00551E80);
  new_var3 = p;
  if (new_var3 != 0)
  {
    self[0x48 / 4] = (int) new_var3;
    new_var2 = 0x50;
    self[new_var2 / 4] = t0;
    isysGObjLinkObjDLHead(self, new_var, r);
    debug_StdPrintfDummy(D_00551E90);
  }
}


void isysGObjMoveObjDLBeforeGObj(void *a0, void *a1, unsigned char a2, void *a3, void *a4) {
    if (a1 != 0) {
        *(void **)((char *)a0 + 0x48) = a1;
        *(void **)((char *)a0 + 0x50) = a4;
        isysGObjLinkObjDLAfterGObj(a0, a2, a3);
    }
}

extern int D_0027DE50[];

void func_0013ECE0(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_StdPrintfDummy(D_00551E28);
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
        D_0027DE50[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}


void func_0013ED48(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_StdPrintfDummy(D_00551E28);
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
        D_0027DE50[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DE30;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0027DE50;  /* stride 0x4 */

/* end struct shapes */
