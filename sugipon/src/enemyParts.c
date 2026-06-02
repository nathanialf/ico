#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", UpdatePointBlur);

void InitEnemyEye(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    q[0xE] = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", InitEnemyFootPrint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", ExecEnemyFootPrints);

int EntryEnemyFootPrint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[5];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", DispEnemyFootPrints);

void InitPointBlur(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    *(float *)((char *)q + 0x44) = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", DispPointBlur);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", UpdateEnemyEye);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", DispEnemyEye);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", ResetEnemyEye);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", moveDataElements);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC020);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC220);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC518);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC7D8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CC950);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CCA00);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CCA20);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CCB60);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/enemyParts", func_001CCBC0);
