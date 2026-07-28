#include "common.h"





extern void Generator_Mask(char *self);
extern int *D_00631AE4;
extern float D_006CF940[];
extern int func_001BC870();
int warpGirlOutStage(void) {
    return func_001BC870() != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", warpGirlInStage);

void warpGirlInit(float *dst)
{
    dst[0] = D_006CF940[0];
    dst[1] = D_006CF940[1];
    dst[2] = D_006CF940[2];
}

void func_0017E9D8(void) {
    char *p = D_00631AE4;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        *(long long *)(sub + 0x20) &= ~0x1000LL;
    }
}

void func_0017EA00(void) {
    char *p = D_00631AE4;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        *(long long *)(sub + 0x20) |= 0x1000LL;
    }
}

void func_0017EA28(void) {
    char *p = D_00631AE4;
    if (p != 0) {
        char *sub = *(char **)(p + 0x164);
        *(long long *)(sub + 0x20) &= ~0x2000LL;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EA50);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EAD0);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EB50);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EBD0);

void func_0017EC50(void *a0, float f)
{
  long * volatile *pp = (long * volatile *) (((char *) a0) + 0x164);
  int new_var;
  long *p = *pp;
  char *new_var2;
  new_var2 = ((char *) p) + 0x20;
  new_var = 0x678;
  *((long *) new_var2) = (*((long *) new_var2)) | 0x100000;
 do { } while (0);
  {
    int **q = (int **) (*pp);
    int *r = *((int **) (((char *) q) + new_var));
    *((float *) (((char *) r) + 0x340)) = f;
  }
}

void func_0017EC78(char *self) {
    char *sub = *(char **)(self + 0x164);
    *(long long *)(sub + 0x20) &= ~0x100000LL;
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EC98);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017ED70);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EDA0);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017EF30);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017F028);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017F2E8);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017F810);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017FCF8);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_0017FF40);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_001803A8);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_00180550);

void func_00180580(volatile unsigned int a0)
{
    volatile int local;
    Generator_Mask(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_001805A8);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_00180628);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_001806B8);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_00180720);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_00180788);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_001807F0);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_00180830);

INCLUDE_ASM("asm/nonmatchings/src/warpGirl", func_00180898);

