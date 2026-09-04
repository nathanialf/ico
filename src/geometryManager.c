#include "common.h"







extern void GetMatrixFromQuaternionPos();
extern void func_002438E8();
extern void MatrixDrive_TransMatrix();
extern void sceVu0ApplyMatrix();
extern void MatrixDrive_TurnObjectMatrix();
extern void sceVu0Normalize();
extern int * func_00105278();
extern void func_00104F20();
extern void MultiMatrixByQuaternion();
extern void MatrixDrive_PopMatrix();
extern void CopyMatrix();
extern void MultiQuaternion();
extern void RegularizeQuaternion();
#include "ico/types.h"
extern void CopyMatrix(void *dst, void *src);
extern void func_00105308(float a, float b, float c);

void GetRootQuaternionByDObj(void *a0)
{
    register float rf12 __asm__("$f12");
    register float rf13 __asm__("$f13");
    register float rf14 __asm__("$f14");
    float a = rf12;
    float b = rf13;
    float c = rf14;
    func_00104F20();
    CopyMatrix(func_00105278(), (void *)((char *)a0 + 0x20));
    func_00105308(a, b, c);
    CopyMatrix((void *)*(int *)((char *)a0 + 0xC), func_00105278());
    MatrixDrive_PopMatrix();
}

void UpdateRootMatrixByDObj(int a0)
{
    GetRootQuaternionByDObj((int)((GObj *)(a0))->p_15C);
}

void GetRootMatrixRotOffsetByDObj(int a0, int a1)
{
    RegularizeQuaternion(a0, a1 + 0x60);
    MultiQuaternion(a0, a0, *(int *)(a1 + 0x10));
}

void UpdateRootMatrix(void *a0, int a1) {
    GetRootMatrixRotOffsetByDObj(a0, *(void **)(a1 + 0x15C));
}

void SetRootMatrixRotOffsetByDObj(int *self, int *other)
{
    func_00104F20();
    CopyMatrix(func_00105278(), (char *)self + 0x20);
    MultiMatrixByQuaternion(other);
    CopyMatrix((void *)self[0xC/4], func_00105278());
    MatrixDrive_PopMatrix();
    MultiQuaternion((void *)self[0x10/4], (char *)self + 0x60, other);
}


void SetRootQuaternion(int a0, void *a1) {
    SetRootMatrixRotOffsetByDObj(*(void **)(a0 + 0x15C), a1);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetRootMatrixWithTransOffsetByDObj);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPositionNoFittingWithNodePointXZ);

extern void SetMotionBlendlessNode(void *a0);
extern void SetRootMatrixWithTransOffsetByDObj(void *a0);

void SetRootMatrixWithTransOffset(void *a0) {
    SetRootMatrixWithTransOffsetByDObj(a0);
    SetMotionBlendlessNode(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", LocalizeGeometry);

void GetGlobalDirectionOrient(int *self, int *other, char *p)
{
    MatrixDrive_TurnObjectMatrix((int)self, (int)p);
    {
        char *sub = ((GObj *)((char *)other))->p_15C;
        char *a = *(char **)sub;
        if (a != 0) {
            char *inner_struct = ((GObj *)(a))->p_15C;
            int inner_field = *(int *)(inner_struct + 0xC);
            int idx = *(int *)(sub + 0x4);
            sceVu0ApplyMatrix(self, inner_field + (idx << 6), p);
        }
    }
    *(int *)((char *)self + 0x4) = 0;
    sceVu0Normalize(self, self);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GlobalizeGeometry);

void GetRootVelocity(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, (int)((GObj *)(a1))->p_15C + 0x130);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPositionNoFittingWithNodePoint);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialInverseMatrix);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialSkeltonMatrixByDObj);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", MakeCharGObjList);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", cylinderCollisionCheck);

void LocalizeDirectionOrient(int *self, int *a1)
{
    int buf[16];
    char *obj = (char *)a1[0];
    char *ctx = ((GObj *)(obj))->p_15C;
    CopyMatrix(buf, (void *)(*(int *)(ctx + 0xC) + (a1[1] << 6)));
    MatrixDrive_TransMatrix((char *)buf, (char *)buf);
    sceVu0ApplyMatrix((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520), (int)buf,
                  (char *)((GObj *)((char *)self))->p_15C + 0x520);
    sceVu0Normalize((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520),
                  (int *)((char *)((GObj *)((char *)self))->p_15C + 0x520));
    ((GObj *)((char *)self))->p_15C->f_52C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetCylinderCollision);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetCylinderCollisionWithExceptOwnCollision);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", CylinderCollision);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", CylinderCollisionWithControlDynamics);

void GetRootMatrixByDObj(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    GetMatrixFromQuaternionPos(a0, src + 0xD0, p);
    {
        int *g = *(int **)src;
        if (g) {
            func_002438E8(a0,
                          (char *)(*(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6)),
                          (int)a0);
        }
    }
    *(float *)((char *)a0 + 0x34) += p[0x30];
}

void GetRootMatrix(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    GetMatrixFromQuaternionPos(a0, src + 0xD0, p);
    {
        int *g = *(int **)src;
        if (g) {
            func_002438E8(a0,
                          (char *)(*(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6)),
                          (int)a0);
        }
    }
    *(float *)((char *)a0 + 0x34) += p[0x30];
}

void GetRootPositionByDObj(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix((int *)a0,
                      *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
                      (char *)p);
    } else {
        MatrixDrive_TurnObjectMatrix((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPosition);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPositionNoFitting);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetRootPosition);

void GetRootPosition(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        sceVu0ApplyMatrix((int *)a0,
                      *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
                      (char *)p);
    } else {
        MatrixDrive_TurnObjectMatrix((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

