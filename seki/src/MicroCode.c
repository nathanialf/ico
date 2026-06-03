#include "common.h"
#include "vu0.h"
#include "r5900.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", mc_setBaseOffset);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", mc_SetMicroCode);

void mc_TransMicroCode(void *a0, void *a1) {
    QCOPY16("$t0");
}

void mc_Reset(void *a0, void *a1) {
    QCOPY16("$t0");
}

void mc_Init(void *a0) {
    VU0_LSV_R(sqc2, 0, 0x0, a0);
    VU0_NOP();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001188B8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001188E0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118908);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118938);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118970);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001189A0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001189D0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_001189F8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118A70);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118AA0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118AC8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118AF0);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118B38);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118C40);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118D68);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118E38);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/MicroCode", func_00118E70);
