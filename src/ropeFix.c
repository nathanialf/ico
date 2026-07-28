#include "common.h"




extern void ExecFrameDependSequence(int a0);
extern void playSEConditionID(int a0, int a1);
extern void UnLockChainGeo(char *self, int val);
extern int isysGObjSearchFromObjLayoutID();
void RopeFixGeo(void) {}

struct vec4_rope { float x, y, z, w; } __attribute__((aligned(8)));

extern void RopeDL(void *o);
extern void GetRootMatrixByDObj(void *dst, void *src);
extern float MoveChainExtendedWeight(void *a0, void *a1, float w);
extern void *D_00631AE4;

void RopeFixDL(void *a0) {
    struct vec4_rope m;
    void **obj;
    void *g;
    float w;
    RopeDL(a0);
    g = D_00631AE4;
    obj = *(void ***)((char *)*(void **)((char *)a0 + 0x15C) + 0x800);
    GetRootMatrixByDObj(&m, g);
    w = MoveChainExtendedWeight(obj[0], &m, 200.0f);
    do {
        if (0.0f < w) {
            *(float *)((char *)*(void **)((char *)g + 0x15C) + 0x618) = w;
        }
    } while (0);
}

void InitRopeFixGeo(int a0)
{
    int v0 = isysGObjSearchFromObjLayoutID(0x15);
    if (v0 != 0) {
        return UnLockChainGeo(v0, a0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/ropeFix", func_001E98C8);

int func_001E9910(void)
{
    return 0;
}

void func_001E9918(int a0)
{
    playSEConditionID(a0, 0x33);
}

void func_001E9920(int a0)
{
    ExecFrameDependSequence(a0);
    playSEConditionID(a0, 0x38);
}

INCLUDE_ASM("asm/nonmatchings/src/ropeFix", func_001E9950);

