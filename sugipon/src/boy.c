#include "common.h"
#include "ico/types.h"

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);

int dispClothes(int *a0, char *a1) {
    char *obj = (char *)*a0;
    char *p15c = *(char **)(obj + 0x15C);
    char *s0 = *(char **)(p15c + 0x7F0);
    char buf[0x20];
    if (*(int *)(s0 + 0x20) != 5) {
        return 0;
    }
    *(float *)(p15c + 0x124) += 0.5f;
    GetRootMatrixByDObj(buf + 0x10, obj);
    MatrixDrive_TurnObjectMatrix(buf, *(char **)(a1 + 0x15C) + 0xA0);
    *(int *)(buf + 4) = 0;
    sceVu0AddVector(s0 + 0xD0, s0 + 0xD0, buf);
    return 1;
}

extern void GetClothAnimation(int a0, int a1, int a2);

void execClothes(char *a0) {
    char *cloth = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    int x;
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    GetClothAnimation(*(int *)(cloth + 0x18), x + 0x40, x);
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    GetClothAnimation(*(int *)(cloth + 0x1C), x + 0x40, x);
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    GetClothAnimation(*(int *)(cloth + 0x24), x + 0x40, x);
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    GetClothAnimation(*(int *)(cloth + 0x20), x + 0x40, x);
    x = *(int *)(*(char **)(a0 + 0x15C) + 0x834);
    GetClothAnimation(*(int *)(cloth + 0x28), x + 0x40, x);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", InitLightLineGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", LightLineDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", InitBoyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", BoyGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", dispCrown);

extern int DebugDisp1CollisionWithColor(void *a0, int code);
extern int func_00105078(void);
extern void CopyMatrix(int a0, int a1);
extern void MatrixDrive_RotMatrixX(int a0);
extern void shadow_EntryClusterShadow(void *a0, void *a1);

void BoyDL(void *a0) {
    char *s0 = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x7F0);
    int s2 = DebugDisp1CollisionWithColor(a0, 0x23);
    switch (*(int *)s0) {
    case 1:
        s0 = *(char **)(s0 + 0x8);
        break;
    case 2:
        s0 = *(char **)(s0 + 0xC);
        break;
    default:
        s0 = *(char **)(s0 + 0x4);
        break;
    }
    CopyMatrix(func_00105078(), *(int *)(*(char **)((char *)a0 + 0x15C) + 0xC) + s2 * 0x40);
    MatrixDrive_RotMatrixX(-0x8000);
    CopyMatrix(*(int *)(s0 + 0xC), func_00105078());
    shadow_EntryClusterShadow(s0, *(char **)((char *)a0 + 0x15C));
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", SelectBoyCrown);

void LightLineGeo(void *a0, int a1) {
    GOBJ_SUB(a0)->p_7F0->p_0 = (void *)a1;
}
