#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", ResetGObjProc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", GetMaxGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", GetGObjP);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", GetGObjId);

void *PrintGObjID(char *a0, long long a1) {
    unsigned long long t = (unsigned int)a1;
    *(int *)(a0 + 8) = 0x53;
    *(int *)(a0 + 0) = (int)t;
    *(int *)(a0 + 4) = 0;
    *(int *)(a0 + 0xC) = 0;
    return a0 + 0x10;
}

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

extern int iosMallocCheckLeak2(int a0);

void func_0023CE70(int a0) {
    iosMallocCheckLeak2(a0 & 0xFFFFFFF);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CF40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023CF90);
