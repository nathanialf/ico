#include "common.h"



extern void func_001E9920();
extern void func_001E9918();
extern void GetRootPosition(void *a0, void *a1);
extern void MatrixDrive_TransMatrix(void *a0, int a1);
extern void SlopeIKControl(void *a0, void *a1, void *a2, float a3);
extern void GetProjectionPosOfPlane(void *a0, void *a1, void *a2);
extern void GetGlobalWallPlane(void *a0, void *a1);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0Normalize(void *a0, void *a1);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);

void GetRotObjectHoldPoint(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x60];

    GetRootPosition(buf + 0x10, a3);
    GetGlobalWallPlane(buf, a2);
    sceVu0ScaleVectorXYZ(a1, buf, -1.0f);
    *(int *)((char *)a1 + 0xC) = 0;
    SlopeIKControl(a0, a2, buf + 0x10, 10.0f);
    GetProjectionPosOfPlane(a0, buf, a0);
    MatrixDrive_TransMatrix(buf + 0x20,
        *(int *)(*(char **)(*(int *)a2 + 0x15C) + 0xC) + (*(int *)((char *)a2 + 4) << 6));
    sceVu0ApplyMatrix(a0, buf + 0x20, a0);
    sceVu0ApplyMatrix(a1, buf + 0x20, a1);
    *(float *)((char *)a0 + 4) = -50.0f;
    sceVu0Normalize(a1, a1);
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

float func_001EA108(void *a0) {
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    return (float)*(int *)(p + 0x24) * (1.0f / 65536.0f);
}

INCLUDE_ASM("asm/nonmatchings/src/rotObject", func_001EA128);

int func_001EA220(void)
{
    return 1;
}

int func_001EA228(void *a0, void *a1)
{
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);

    *(short *)(p + 0x20) = *(unsigned short *)((char *)a1 + 0x30);
    *(int *)(p + 0x24) = *(short *)((char *)a1 + 0x32);
    return 1;
}

int func_001EA248(void *a0, void *a1)
{
    char *p = *(char **)(*(char **)((char *)a1 + 0x15C) + 0x800);

    *(short *)a0 = *(unsigned short *)(p + 0x20);
    *(short *)((char *)a0 + 2) = *(unsigned short *)(p + 0x24);
    return 1;
}

void func_001EA268(void *a0, int a1) {
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    *(int *)(p + 0x34) = a1;
}

