#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", GetDitchPosition);

int DebugActOrientFlag(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x2C);
    p += a1;
    return *(short *)((char *)p + 0x3C);
}

int ACTGetEnvironment(char *a0) {
    char *p = *(char **)(a0 + 0x2C);
    return *(short *)(p + 0x3C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", ACTSetEnvAllmighty);

void GetSofaPosition(void) {
}

void GetCollisCenterPositionSimple(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", CheckWallAttributeEdegWall);

void func_001FA070(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA078);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA130);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FA3D0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE0A8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE250);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-env", func_001FE2F8);
