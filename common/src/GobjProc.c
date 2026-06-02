#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", ResetGObjProc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", GetMaxGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", GetGObjP);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", GetGObjId);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", PrintGObjID);

extern int D_00615180[];
extern void debug_assertMessage(void *a0, int a1);

void InitCameraGObjs(int a0) {
    debug_assertMessage(D_00615180, a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", CreateGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", CreateGObjByFuncSet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023BE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C040);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C1D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C2C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C310);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C5B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C738);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CB20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CB70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CCE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CE70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CF40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CF90);
