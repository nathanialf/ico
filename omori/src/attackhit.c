#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", MakeAttackPack_Actor);

void AttackCheckSameGroup(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackMail);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCheckHit);

extern int D_0062A8E0;

void AttackGenerate(void) {
    D_0062A8E0 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", EnemyAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", BoyAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", CommonAttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCenter);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", AttackCenter_WithDir);

void func_0017F0D0(void) {
}

void func_0017F0D8(void) {
}

extern void EnemyAttackCenter(void *a0, void *a1, int a2);
extern void AttackCenter_WithDir(void *a0);

void func_0017F0E0(void *a0) {
    char buf[0x70];
    int *p = *(int **)((char *)a0 + 0x164);
    EnemyAttackCenter(buf, a0, p[0x4C]);
    AttackCenter_WithDir(buf);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F110);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F2A0);

extern void *D_00286A94[];
extern void saveEditedData(void *a0);
void func_0017F450(void) {
    if (D_00286A94[0]) {
        saveEditedData(D_00286A94[0]);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F470);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F4C8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F518);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/attackhit", func_0017F670);
