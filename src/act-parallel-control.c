#include "common.h"



extern float D_002924B0[];

/* Intra-TU forward decls so calls type-check before the definitions
 * appear later in the file (and so the func_0014BD88(self) call site
 * in ActPara_InitSystem — original asm sets up $a0 with self — matches
 * even though func_0014BD88's body ignores its arg). */;
extern void func_00145638(int a0);
extern void func_0014BD88(int *unused);
extern void func_0014BC30();
int ActPara_MakeTbl(char *self, int a1, float *a2, int a3, int a4)
{
    char *sub = *(char **)(self + 0x164);
    int rv = 0;
    if (a3 == 6) {
        *(int *)(sub + 0x98) = 0;
        *(int *)(sub + 0xA0) = 0;
        *(int *)(sub + 0x9C) = 0;
        goto end;
    }
    if (a3 < *(int *)(sub + 0x9C))
        goto end;
    *(int *)(sub + 0x98) = a1;
    if (a2 != 0) {
        *(float *)(sub + 0xB0) = a2[0];
        *(float *)(sub + 0xB4) = a2[1];
        *(float *)(sub + 0xB8) = a2[2];
    }
    *(int *)(sub + 0xA0) = a4;
    *(int *)(sub + 0x9C) = a3;
    rv = 1;
end:
    return rv;
}

void ActPara_InitSystem(int *self)
{
    int *q = (int *)self[0x59];
    int *p;
    func_0014BD88(self);
    func_00145638(self);
    p = (int *)self[0x59];
    func_0014BC30((int *)p[0x19E], q[0x24], 0);
    q[0x25] = q[0x24];
}

void ActPara_GetDefTbl(char *self, int bit) {
    char *sub = *(char **)(self + 0x164);
    *(int *)(sub + 0x90) |= (1 << bit);
}

int ActPara_StatusToFlag(char *self, int bit) {
    char *sub = *(char **)(self + 0x164);
    return (*(int *)(sub + 0x90) >> bit) & 1;
}

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", ActPara_DebugOut);

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B270);

int func_0014B2F0(char *self, int a1)
{
    char *sub = *(char **)(self + 0x164);
    if (sub) {
        if ((1 << a1) & *(long long *)(sub + 0x58)) {
            return 1;
        }
    }
    return 0;
}

void func_0014B318(void) {}

void func_0014B320(char *self, float val) {
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x678);
    *(float *)(p + 0x334) = val;
}

void func_0014B330(char *self, unsigned int a1, float v)
{
    char *sub = *(char **)(self + 0x164);
    char *p = *(char **)(sub + 0x670);
    if (a1 < *(unsigned int *)(p + 0x54))
    {
        return;
    }
    *(float *)(p + 0x58) = v;
    *(unsigned int *)(p + 0x54) = a1;
}

float func_0014B358(int idx)
{
    return D_002924B0[idx];
}

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B370);

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B430);

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", func_0014B4C8);

