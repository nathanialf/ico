#include "common.h"

typedef union { unsigned long ll; unsigned int i; } GVBits;
typedef struct { char _0[0x42]; short f42; unsigned short f44; unsigned int f48; } GVGeo2;

INCLUDE_ASM("asm/nonmatchings/src/generator", CheckGeneratorCollision);
INCLUDE_ASM("asm/nonmatchings/src/generator", GetGeneratorSafePosition);
INCLUDE_ASM("asm/nonmatchings/src/generator", switch_MainStatus);
INCLUDE_ASM("asm/nonmatchings/src/generator", endfunc_BGA);
INCLUDE_ASM("asm/nonmatchings/src/generator", IsNeedGeneratorHard);
INCLUDE_ASM("asm/nonmatchings/src/generator", CallEnemy);
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_QuickCall);
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_Delete);
INCLUDE_ASM("asm/nonmatchings/src/generator", GetMotherGenerator);
INCLUDE_ASM("asm/nonmatchings/src/generator", ReadGeneratorPacket);
INCLUDE_ASM("asm/nonmatchings/src/generator", MakeGeneratorPacket);
INCLUDE_ASM("asm/nonmatchings/src/generator", generatorBeforeFunc);
INCLUDE_ASM("asm/nonmatchings/src/generator", GeneratorGeo);
INCLUDE_ASM("asm/nonmatchings/src/generator", GeneratorDL);
INCLUDE_ASM("asm/nonmatchings/src/generator", InitGeneratorGeo);
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_Call);
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_ResetCount);
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_Mask);
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_MaskOff);
INCLUDE_ASM("asm/nonmatchings/src/generator", SetMotherGenerator);
INCLUDE_ASM("asm/nonmatchings/src/generator", Generator_Init);
extern int D_006E6D80[];

int *GetbufpGeneratorPacket(void) {
    return D_006E6D80;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", GetsizeGeneratorPacket);
int RestoreGeneratorGeo(float *dst, float *src) {
    dst[0] = src[4];
    dst[1] = src[5];
    dst[2] = src[6];
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", RestoreGeneratorExtGeo);
INCLUDE_ASM("asm/nonmatchings/src/generator", MemoryGenerator);
INCLUDE_ASM("asm/nonmatchings/src/generator", IsEnableCallEnemy);
INCLUDE_ASM("asm/nonmatchings/src/generator", DirectCallEnemy);
extern char D_00555688[];
extern void debug_StdPrintfDummy(char *fmt, ...);

void LockEnemyGenerate(int *self)
{
    int *p;
    p = (int *)self[0x164 / 4];
    debug_StdPrintfDummy(D_00555688, self[0x8 / 4]);
    *(long long *)((char *)p + 0x18) = *(long long *)((char *)p + 0x18) | 0x400000000LL;
}
extern GVGeo2 D_002C2DC8[];
extern char D_00555698[];

void UnlockEnemyGenerate(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    GVGeo2 *g = &D_002C2DC8[*(int *)((char *)a0 + 0x8)];
    debug_StdPrintfDummy(D_00555698, *(int *)((char *)a0 + 0x8));
    ((GVBits *)((char *)p + 0x18))->ll &= ~((unsigned long)0x8000 << 19);
    g->f48 = (g->f48 | 0x200000) & 0xFFFBFFFF;
}
INCLUDE_ASM("asm/nonmatchings/src/generator", RestoreReviveCount);
void ReturnEnemyToGenerator(int a0) {
    GVGeo2 *g = &D_002C2DC8[a0];
    unsigned int x = g->f48 & 0xFFDFFFFF;
    unsigned int y = x & 0xFFFBFFFF;
    y |= ((x >> 19) & 1) << 18;
    g->f48 = y;
    if ((y >> 19) & 1) {
        unsigned int z = y | 0x40000;
        g->f48 = z;
        if ((int)((z >> 5) & 0x1F) != -1) {
            g->f42++;
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/generator", GeneratorWorkEnd);
INCLUDE_ASM("asm/nonmatchings/src/generator", SearchActiveGenerator);
void ResetReviveCountEnemy(int a0)
{
    int idx = *(int *)(a0 + 0x8);
    char *base = (char *)D_002C2DC8 + idx * 0x4C;
    *(short *)(base + 0x42) = 0;
}
void SetInfoSpKidnapGenerator(short *a0) {
    a0[0] = 1;
    a0[1] = 1;
}
extern char D_00308924[];

void SetInfoSpKidnapEnemy(void)
{
  int new_var;
  new_var = 0x42;
  *((short *) (D_00308924 + new_var)) = 0;
  *((int *) (D_00308924 + 0x48)) = ((*((int *) (D_00308924 + 0x48))) | 0x200000) & (~0x40000);
}
INCLUDE_ASM("asm/nonmatchings/src/generator", IsOpenGenerator);
int IsEnableCallEnemyByTargetGObj(void *a0) {
    GVGeo2 *g = &D_002C2DC8[*(int *)((char *)a0 + 0x8)];
    void *p = *(void **)((char *)a0 + 0x164);
    if (g->f44 != 0) {
        return 0;
    }
    if ((unsigned int)(*(unsigned long long *)((char *)p + 0x18) >> 34) & 1) {
        return 0;
    }
    if (((g->f48 >> 21) & 1) == 0 && (g->f42 == -1 || g->f42 > 0)) {
        return 1;
    }
    return 0;
}
