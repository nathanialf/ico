#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00101C80);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102310);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_001023E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102488);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_001024C8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102528);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_001025B8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102650);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102760);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102798);

extern void func_00102760(void *a0, void *a1);
extern void func_00102798(void *a0);

void func_00102820(void *a0, int a1) {
    func_00102760(a0, *(void **)(a1 + 0x15C));
}

void func_00102828(int a0) {
    func_00102798(*(void **)(a0 + 0x15C));
}

extern void GetInverseQuaternion(void *a0, void *a1);

void func_00102830(int **a0, void *a1) {
    GetInverseQuaternion((char *)a0[0x57] + 0xC0, a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102840);
