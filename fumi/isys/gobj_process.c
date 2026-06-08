#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcessInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcAdd_);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", cut_gobj_process_link);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcAddGOppArg);

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
