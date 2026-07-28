#include "common.h"



extern void func_001E9920();
extern void func_001E9918();
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void MatrixDrive_TransMatrix(void *a0, int a1);
extern void SlopeIKControl(void *a0, void *a1, void *a2, float a3);
extern void func_001048C8(void *a0, void *a1, void *a2);
extern void func_00168CC8(void *a0, void *a1);
extern void func_002438B8(void *a0, void *a1, void *a2);
extern void func_00243978(void *a0, void *a1);
extern void func_00244448(void *a0, void *a1, float a2);

void moveStartSE(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x60];

    GetRootMatrixByDObj(buf + 0x10, a3);
    func_00168CC8(buf, a2);
    func_00244448(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    SlopeIKControl(a0, a2, buf + 0x10, 10.0f);
    func_001048C8(a0, buf, a0);
    MatrixDrive_TransMatrix(buf + 0x20,
        *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) + (*(int *)((char *)a2 + 4) << 6));
    func_002438B8(a0, buf + 0x20, a0);
    func_002438B8(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    func_00243978(a1, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001E9A78);

void func_001E9DE8(int a0, int a1, int a2, int a3)
{
    func_001E9918(a0, a1, a2, a3);
}

void func_001E9DF0(int a0, int a1, int a2, int a3)
{
    func_001E9920(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001E9DF8);

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001E9F08);

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA030);

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA108);

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA128);

int func_001EA220(void)
{
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA228);

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA248);

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA268);

