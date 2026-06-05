#include "common.h"

extern void *D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void GetDataFileName(void) {
    if (D_00629DE8 == 0) {
        return;
    }
    if (func_00178DB0(0x31) != 0) {
        return;
    }
    func_00178DD8(0x165);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", GetDataFileName2);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_002361C0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236300);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236420);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_002365C0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236688);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236738);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_002367F8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236858);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_002368B8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236918);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236988);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_002369F0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236AA8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236B40);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236C20);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236C98);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236D28);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/access", func_00236DB8);
