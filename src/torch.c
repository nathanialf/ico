#include "common.h"

#include "ico/types.h"
#include "vu0.h"

extern char D_00276140[];
extern void ExecParticleEffects(int a0, void *a1, void *a2);

void torchOffSE(void *a0, void *a1) {
    char *s0 = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    if (*(int *)(s0 + 0x20) != -1) {
        ExecParticleEffects(*(int *)(s0 + 0x20), a1, D_00276140);
    }
    if (*(int *)(s0 + 0x1C) != -1) {
        ExecParticleEffects(*(int *)(s0 + 0x1C), a1, D_00276140);
    }
    if (*(int *)(s0 + 0x14) != -1) {
        ExecParticleEffects(*(int *)(s0 + 0x14), a1, D_00276140);
    }
    if (*(int *)(s0 + 0x18) != -1) {
        ExecParticleEffects(*(int *)(s0 + 0x18), a1, D_00276140);
    }
    if (*(int *)(s0 + 0x24) != -1) {
        ExecParticleEffects(*(int *)(s0 + 0x24), a1, D_00276140);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/torch", LightTorchOn);

INCLUDE_ASM("asm/nonmatchings/src/torch", LightTorchOff);

INCLUDE_ASM("asm/nonmatchings/src/torch", moveTorch);

void CheckTorchChainReactionReverse(void) {}

int TorchGeo(void *a0) {
    return ((Obj7F0 *)GOBJ_SUB(a0)->p_800)->f_4;
}

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void *isysGObjSearchFromObjKindID_begin(void *o);
extern void *isysGObjSearchFromObjLayoutID(int id);

void *InitTorchGeo(void *a0, float radius) {
    int buf0[4];
    int buf1[4];
    register float r2 __asm__("$f20") = radius * radius;
    GetRootMatrixByDObj(buf0, a0);
    {
        char *g = isysGObjSearchFromObjLayoutID(0xA);
        if (g != 0) {
            do {
                if (g != (char *)a0 &&
                    *(int *)(*(char **)(*(char **)(g + 0x15C) + 0x800) + 0x4) != 0 &&
                    *(int *)(g + 0x16C) != 0) {
                    register float d2 __asm__("$f0");
                    GetRootMatrixByDObj(buf1, g);
                    VU0_LSV_R(lqc2, 1, 0x0, buf1);
                    VU0_LSV_R(lqc2, 2, 0x0, buf0);
                    VU0_V3OP(vsub.xyzw, 3, 1, 2);
                    VU0_V3OP(vmul.xyz, 3, 3, 3);
                    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
                    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
                    VU0_QMFC2_NI(v0, 3);
                    VU0_MTC1(v0, 0);
                    if (d2 < r2) {
                        return g;
                    }
                }
                g = isysGObjSearchFromObjKindID_begin(g);
            } while (g != 0);
        }
    }
    return 0;
}

void TorchDL(void *a0, int a1) {
    ((Obj7F0 *)GOBJ_SUB(a0)->p_800)->f_C = a1;
}

void IsTorchLightOn(void *a0, int a1) {
    ((Obj7F0 *)GOBJ_SUB(a0)->p_800)->f_10 = a1;
}

