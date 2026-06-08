#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", ResetGObjProc);

void *GetMaxGObj(int *a0, int a1, int a2, int a3) {
    long long v = ((long long)a3 << 56) | ((long long)a2 << 48) | ((long long)a1 << 32);
    a0[1] = v >> 32;
    a0[2] = 0x50;
    a0[0] = 0;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

void *GetGObjP(int *a0, int a1, int a2, int a3) {
    long long v = ((long long)a1 << 59) | ((long long)a3 << 48) | ((long long)a2 << 32);
    a0[1] = v >> 32;
    a0[2] = 0x51;
    a0[0] = 0;
    a0[3] = 0;
    return (char *)a0 + 0x10;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", GetGObjId);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", PrintGObjID);

extern int D_00615180[];
extern void debug_assertMessage(void *a0, int a1);

void InitCameraGObjs(int a0) {
    debug_assertMessage(D_00615180, a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", CreateGObj);

extern void func_0023CE70(int a0);

void CreateGObjByFuncSet(int *a0) {
    func_0023CE70(a0[0]);
    func_0023CE70(a0[1]);
    func_0023CE70(a0[20]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023BE80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C040);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/GobjProc", func_0023C1D8);

extern unsigned char func_00100560(int x);
extern void func_00100540(int x);

void func_0023C2C0(int *self, int a1)
{
  func_00100560(self[0x40 / 4]);
  self[0x14 / 4] = self[0x14 / 4] + a1;
  *((long long *) (((char *) self) + 0x48)) = ((long long) a1) + (*((long long *) (((char *) self) + 0x48)));
  func_00100540(self[0x40 / 4]);
}

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
