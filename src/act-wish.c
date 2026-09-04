#include "common.h"





extern int D_006AA968[];  /* array decl (not int*): keeps gcc on lui+addiu, not gp_rel — D_006AA968 lives at 0x006AA968, far outside the GP window */;
extern int D_002E4E00[];
extern int D_00631990;
extern int DispIcoMisc(int a0);
extern void queen_barrier_anim();
extern int D_006325B4;
extern void avoidInsideOfWall(void *self);
extern int InitMultiBgaManager(int a0);

void ACTGetWish_FromPad(int a0)
{
    int r = InitMultiBgaManager(1);
    int v = *(int *)(*(int *)(a0 + 0x164) + 0x670);
    *(int *)(v + 0x1B8) = r;
}

INCLUDE_ASM("asm/nonmatchings/src/act-wish", func_0014B5B8);

INCLUDE_ASM("asm/nonmatchings/src/act-wish", ActGame_GetOrientQ);

INCLUDE_ASM("asm/nonmatchings/src/act-wish", _GetRootObjectOrient);

void func_0014B768(int a0)
{
    int *s0 = *((int **)(((char *)a0) + 0x164));
    int *p = (int *)s0[0x170 / 4];
    if (p != 0) {
        avoidInsideOfWall((int)p);
        s0[0x174 / 4] = (s0[0x170 / 4] = 0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/act-wish", func_0014B7A8);

int func_0014B800(char *self)
{
    char *sub = *(char **)(self + 0x164);
    if (*(int *)(sub + 0x30) == 0x35) goto ret1;
    {
        char *other = *(char **)(sub + 0x678);
        if (*(int *)(other + 0x394) == 0) goto ret0;
        if (D_006325B4 == 0) goto ret0;
    }
ret1:
    return 1;
ret0:
    return 0;
}

int func_0014B840(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x30) == 0x6B;
}

int func_0014B858(char *self) {
    char *sub = *(char **)(self + 0x164);
    return *(int *)(sub + 0x30) == 0x64;
}

INCLUDE_ASM("asm/nonmatchings/src/act-wish", ACTCheckCollis_VIEW);

INCLUDE_ASM("asm/nonmatchings/src/act-wish", ACTCheckViewClDetail);

void func_0014BB00(int a0)
{
    int v = *(int *)(*(int *)(a0 + 0x164) + 0x670);
    *(float *)(v + 0x58) = 1.0f;
    *(int *)(v + 0x54) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/act-wish", func_0014BB20);

void GetGirlPositionAtThisStage(int a0)
{
    int buf[4];
    int v0 = DispIcoMisc(buf);
    queen_barrier_anim(a0, D_00631990, v0, buf);
}

INCLUDE_ASM("asm/nonmatchings/src/act-wish", func_0014BC30);

void func_0014BD88(int *unused)
{
    int *dst = D_006AA968;
    char *src = (char *)D_002E4E00;
    int i = 0x46;
    do {
        *dst = *(int *)src;
        i--;
        src += 0x94;
        dst++;
    } while (i >= 0);
}

int *func_0014BDC8(void) {
    return D_006AA968;
}

int func_0014BDD8(int a0, int a1)
{
    int v = a0 ? 9 : 1;
    return a1 ? (v | 4) : v;
}

