#include "common.h"
#include "ico/types.h"

extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void func_0023FFF0(void *a0, void *a1, void *a2);

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
    func_0023FFF0(s0 + 0xD0, s0 + 0xD0, buf);
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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", BoyDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/boy", SelectBoyCrown);

void LightLineGeo(void *a0, int a1) {
    GOBJ_SUB(a0)->p_7F0->p_0 = (void *)a1;
}
