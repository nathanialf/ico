#include "common.h"

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcessInit);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcAdd_);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", cut_gobj_process_link);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcRemove);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcessAlloc);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcAdd);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcAddS);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcAddGOppArg);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcPause);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcPauseAll);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_process", isysGObjProcPausePtr);

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

