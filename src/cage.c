#include "common.h"


extern void SetMotionBlendlessNode();
INCLUDE_ASM("asm/nonmatchings/src/cage", CageRideFunc);
ASM_LIT4_SLOT(D_006311D8, 0.01f);
ASM_LIT4_SLOT(D_006311DC, 0.001f);

void SetCageFixGeometry(int *self)
{
    int *p;
    p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    SetMotionBlendlessNode(self);
    p[0x14 / 4] = 0;
    p[0x10 / 4] = 1;
    ((int *)self[0x15C / 4])[0x62C / 4] = 0;
}

extern float MatrixDrive_GetTurnYAngleXZ(float f12);
extern float MatrixDrive_GetTurnYEAngleXZ(void *a0);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern void func_00243978(void *a0, void *a1);
extern void func_00243AD0(void *a0, void *a1, void *a2);
extern void func_00243AE8(void *a0, void *a1, void *a2);
extern void func_00243B18(void *a0, void *a1, float f12);

int InitCageGeo(int a0, int a1) {
    char buf[0x20];
    char *m1 = *(char **)a0;
    char *sub5 = *(char **)(a1 + 0x15C);
    char *sub = *(char **)(*(char **)(m1 + 0x15C) + 0x800);
    float x, z, ang, f20, f1;

    MatrixDrive_TurnObjectMatrix((int)buf, (int)(sub5 + 0xA0));
    *(float *)(buf + 0x4) = *(float *)(buf + 0x4) - 250.0f;
    func_00243978(buf + 0x10, buf);
    x = *(float *)(buf + 0x10);
    z = *(float *)(buf + 0x18);
    ang = MatrixDrive_GetTurnYAngleXZ(x * x + z * z);
    f20 = ang * 50.0f;
    f1 = MatrixDrive_GetTurnYEAngleXZ(buf) * f20 / 250.0f;
    if (f1 < 0.0f) f1 = -f1;
    *(float *)(buf + 0x4) = 0.0f;
    func_00243B18(buf, buf, f1 * 0.06f / *(float *)(sub + 0x38));
    func_00243AD0((void *)(*(int *)(sub + 0x24) * 0x50 + *(int *)(*(char **)(sub + 0x20) + 8) + 0x40),
                  (void *)(*(int *)(sub + 0x24) * 0x50 + *(int *)(*(char **)(sub + 0x20) + 8) + 0x40), buf);
    func_00243AE8((void *)(*(int *)(sub + 0x28) * 0x50 + *(int *)(*(char **)(sub + 0x20) + 8) + 0x40),
                  (void *)(*(int *)(sub + 0x28) * 0x50 + *(int *)(*(char **)(sub + 0x20) + 8) + 0x40), buf);
    return 1;
}

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

void HotInitCageGeo(int a0, int a1, int a2)
{
    int q = *(int *)(*(int *)(a0 + 0x15C) + 0x800);
    int node = *(int *)(q + 0x20);
    MatrixDrive_TurnObjectMatrix(*(int *)node + 0x20, a1);
    MatrixDrive_TurnObjectMatrix(q + 0x10, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/cage", CageGeo);
ASM_LIT4_SLOT(D_006311E4, 0.995f);
ASM_LIT4_SLOT(D_006311E8, 10430.3779f);

extern char D_00275850[];

void CageDL(int a0)
{
    int g = *(int *)(*(int *)(a0 + 0x15C) + 0x800);
    float f2;

    MatrixDrive_TurnObjectMatrix(*(int *)(g + 0x24) * 0x50 + *(int *)(*(int *)(g + 0x20) + 8) + 0x40, (int)D_00275850);
    MatrixDrive_TurnObjectMatrix(*(int *)(g + 0x28) * 0x50 + *(int *)(*(int *)(g + 0x20) + 8) + 0x40, (int)D_00275850);
    MatrixDrive_TurnObjectMatrix(*(int *)(g + 0x24) * 0x50 + *(int *)(*(int *)(g + 0x20) + 8) + 0x30, *(int *)(*(int *)(g + 0x20)) + 0x20);
    MatrixDrive_TurnObjectMatrix(*(int *)(g + 0x28) * 0x50 + *(int *)(*(int *)(g + 0x20) + 8) + 0x30, *(int *)(*(int *)(g + 0x20)) + 0x20);
    MatrixDrive_TurnObjectMatrix(*(int *)(*(int *)(*(int *)(g + 0x20) + 8)), *(int *)(*(int *)(g + 0x20)) + 0x20);
    MatrixDrive_TurnObjectMatrix(*(int *)(*(int *)(*(int *)(g + 0x20) + 8)) + 0x10, *(int *)(*(int *)(g + 0x20)) + 0x20);

    f2 = (float)*(int *)(g + 0x2C);
    *(float *)(*(int *)(*(int *)(*(int *)(g + 0x20) + 8)) + 0x14) += *(float *)(g + 0x30) * f2;
    *(float *)(*(int *)(g + 0x24) * 0x50 + *(int *)(*(int *)(g + 0x20) + 8) + 0x34) += *(float *)(g + 0x30) * f2;
    *(float *)(*(int *)(g + 0x28) * 0x50 + *(int *)(*(int *)(g + 0x20) + 8) + 0x34) += *(float *)(g + 0x30) * f2 + 500.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/cage", GetCageChainPoint);
ASM_LIT4_SLOT(D_006311EC, 2730.0f);
ASM_LIT4_SLOT(D_006311F0, 10430.3779f);

