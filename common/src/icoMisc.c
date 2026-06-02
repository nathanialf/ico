#include "common.h"

extern void func_00102828(int a0);
extern void func_0010F048(int a0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", disp_memory_partition_bar);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", disp_memory_partition);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", ExecIcoMisc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", InitIcoMisc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", DispIcoMisc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", ExitIcoMisc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ABE38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ABE88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ABEE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ABF40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ABF88);

void func_001ABFE8(int a0) {
    func_00102828(a0);
}

void func_001ABFF0(int a0) {
    func_0010F048(a0);
}

int func_001ABFF8(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001AC000);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001AC5E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001AC728);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/icoMisc", func_001ACA38);
