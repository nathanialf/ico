#include "common.h"





extern char D_0055A568[];
extern void debug_assertMessage();
extern void func_001918A8(void);
extern int D_0028A890[];
extern void saveEditedData();
extern int D_0028A894[];
extern int D_00632600;
INCLUDE_ASM("asm/nonmatchings/src/attackhit", MakeAttackPack_Actor);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00180A78);

void AttackCheckSameGroup(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackMail);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00180BC0);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCheckHit);

void AttackGenerate(void) {
    D_00632600 = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/attackhit", EnemyAttackCenter);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", BoyAttackCenter);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", CommonAttackCenter);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCenter);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", AttackCenter_WithDir);

void func_00181BB8(void) {}

void func_00181BC0(void) {}

extern void EnemyAttackCenter(void *pack, void *self, int a2);
extern void AttackCenter_WithDir(void *pack);

void func_00181BC8(void *self) {
    char pack[0x70];
    EnemyAttackCenter(pack, self, *(int *)(*(int *)((char *)self + 0x164) + 0x140));
    AttackCenter_WithDir(pack);
}

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00181BF8);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00181D88);

void func_00181F38(void)
{
    if (D_0028A894[0] != 0) {
        saveEditedData(D_0028A894[0]);
    }
}

void func_00181F58(void)
{
    char *new_var;
    char *p = D_0028A890;
    char *q;
    int i = 0x13;
    *((int *) (p + 0)) = 0;
    *((int *) (p + 0x4)) = 0;
    new_var = p;
    q = new_var + 0x23C;
    *((int *) (p + 0xC)) = 0;
    *((int *) (p + 0x10)) = 0;
    do {
        *((int *) q) = 0;
        i--;
        q -= 0x1C;
    } while (i >= 0);
    *((int *) (new_var + 0x8)) = 0;
    *((int *) (new_var + 0x14)) = 0;
    *((short *) (new_var + 0x1C)) = 0;
    *((short *) (new_var + 0x24)) = (short) (-1);
    func_001918A8();
}

void func_00181FB0(char *self, int key, float f12, float f13, float f14)
{
    int i = 0;
    int *p = (int *)(self + 0x28);
    do {
        if (*p == key) {
            char *slot = self + (i * 0x1C + 0x28);
            *(float *)(slot + 0x8) = f12;
            *(float *)(slot + 0xC) = f14;
            *(float *)(slot + 0x10) = f13;
            *(int *)(slot + 0x4) = 0;
            return;
        }
        i++;
        p = (int *)((char *)p + 0x1C);
    } while (i < 0x14);
    return debug_assertMessage(D_0055A568);
}

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00182000);

INCLUDE_ASM("asm/nonmatchings/src/attackhit", func_00182158);

