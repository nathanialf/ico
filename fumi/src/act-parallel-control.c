#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_MakeTbl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_InitSystem);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_GetDefTbl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_StatusToFlag);

void ActPara_DebugOut(int **a0) {
    int *p = a0[0x59];
    p[0x15] = 0;
    p[0x16] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149C20);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149CA0);

void func_00149CC0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149CC8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149CD8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149D00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149D18);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149E70);
