#include "common.h"

extern int D_0027DE30[];
extern int D_0027DE50[];

void isysGObjProcessInit(void) {
    int i;
    for (i = 0; i < 8; i++) {
        D_0027DE30[i] = 0;
        D_0027DE50[i] = 0;
    }
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

extern void isysGObjMoveObjDLHead(int *self);

void isysGObjProcAdd_(DLN *self, DLN *obj) {
    isysGObjMoveObjDLHead((int *)self);
    self->id = obj->id;
    self->prev = obj;
    self->next = obj->next;
    obj->next = self;
    self->key = obj->key;
    if (self->next == 0) {
        ((DLN **)D_0027DE50)[self->id] = self;
    }
}

void cut_gobj_process_link(DLN *self, DLN *obj) {
    isysGObjMoveObjDLHead((int *)self);
    self->id = obj->id;
    self->prev = obj->prev;
    self->next = obj;
    obj->prev = self;
    self->key = obj->key;
    if (self->prev == 0) {
        ((DLN **)D_0027DE30)[self->id] = self;
    }
}

extern void isysGObjProcAddGOppArg(void);

void isysGObjProcRemove(void) {
    isysGObjProcAddGOppArg();
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcessAlloc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcAdd);

extern void isysGObjProcAdd(int a0);
extern int iosSemaDelete(int a0);

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

extern int iosFree(int a0, int a1, const char *fmt, int line);
extern int D_0062A308;
extern int D_0062BFB0;
extern int D_0062BFB4;
extern char D_00551EA0[];

void isysGObjProcAddGOppArg(unsigned int a0) {
    int ret = iosFree(D_0062A308, a0 * 0x94, D_00551EA0, 0x49);
    unsigned int i;
    D_0062BFB4 = a0;
    D_0062BFB0 = ret;
    for (i = 0; i < a0; i++) {
        *(int *)(ret + i * 0x94) = 0;
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

void isysGObjProcActive(int *a0) {
    a0[6] = 0;
}

void isysGObjProcActiveAll(int a0) {
    int p = *(int *)(a0 + 0x2C);
    while (p != 0) {
        *(int *)(p + 0x18) = 0;
        p = *(int *)(p + 0x8);
    }
}
