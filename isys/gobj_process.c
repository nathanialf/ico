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

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcessInit);

extern int D_00281AD0[];
extern void isysGObjMoveObjDLHead(int *self);

void isysGObjProcAdd_(DLN *self, DLN *obj) {
    isysGObjMoveObjDLHead((int *)self);
    self->id = obj->id;
    self->prev = obj;
    self->next = obj->next;
    obj->next = self;
    self->key = obj->key;
    if (self->next == 0) {
        ((DLN **)D_00281AD0)[self->id] = self;
    }
}

extern int D_00281AB0[];

void cut_gobj_process_link(DLN *self, DLN *obj) {
    isysGObjMoveObjDLHead((int *)self);
    self->id = obj->id;
    self->prev = obj->prev;
    self->next = obj;
    obj->prev = self;
    self->key = obj->key;
    if (self->prev == 0) {
        ((DLN **)D_00281AB0)[self->id] = self;
    }
}

extern void isysGObjProcAddGOppArg(unsigned int a0);

void isysGObjProcRemove(unsigned int a0) {
    isysGObjProcAddGOppArg(a0);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcessAlloc);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcAdd);

extern int iosSemaDelete(int a0);
extern void isysGObjProcAdd(int a0);

void isysGObjProcAddS(int *a0)
{
    int v0;
    isysGObjProcAdd((int)a0);
    v0 = a0[4];
    a0[0] = 0;
    if (v0 != 0) {
        return;
    }
    return iosSemaDelete((int)a0 + 0x24);
}

extern char D_00557AD0[];
extern int D_00632008;
extern char *D_00633CA8;
extern int D_00633CAC;
extern int func_0013A0F8(int a0, int a1, const char *fmt, int line);

void isysGObjProcAddGOppArg(unsigned int a0) {
    int ret = func_0013A0F8(D_00632008, a0 * 0x94, D_00557AD0, 0x49);
    unsigned int i;
    D_00633CAC = a0;
    D_00633CA8 = (char *)ret;
    for (i = 0; i < a0; i++) {
        *(int *)(D_00633CA8 + i * 0x94) = 0;
    }
}

extern int isysGObjProcessAlloc(int a0, int a1, int a2, int a3, int a4, int a5);

int isysGObjProcPause(int a0, int a1, int a2, int a3) {
    return isysGObjProcessAlloc(a0, a0, a1, a2 & 0xFF, a3, 0x1800);
}

int isysGObjProcPauseAll(int a0, int a1, int a2, int a3, int a4) {
    return isysGObjProcessAlloc(a0, a0, a1, a2 & 0xFF, a3, a4);
}

int isysGObjProcPausePtr(int a0, int a1, int a2, int a3) {
    return isysGObjProcessAlloc(a0, 0, a1, a2 & 0xFF, a3, 0x1800);
}

void isysGObjProcActive(char *self) {
    *(int *)(self + 0x18) = 0;
}

void isysGObjProcActiveAll(int *p)
{
    int *cur = (int *)p[0x2C/4];
    if (cur != 0) {
        do {
            cur[0x18/4] = 0;
            cur = (int *)cur[0x8/4];
        } while (cur != 0);
    }
}

