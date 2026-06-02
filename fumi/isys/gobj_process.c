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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcAddS);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcAddGOppArg);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcPause);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcPauseAll);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcPausePtr);

void isysGObjProcActive(int *a0) {
    a0[6] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/isys/gobj_process", isysGObjProcActiveAll);
