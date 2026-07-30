#include "common.h"







extern void func_0010DEC0();
extern void func_002438E8();
extern void MatrixDrive_TransMatrix();
extern void func_002438B8();
extern void MatrixDrive_TurnObjectMatrix();
extern void func_00243978();
extern int * func_00105278();
extern void func_00104F20();
extern void func_0010DF70();
extern void func_00105268();
extern void MatrixDrive_TurnXObjectMatrixYZ();
extern void func_0010DDB8();
extern void RegularizeQuaternion();
#include "ico/types.h"
extern void MatrixDrive_TurnXObjectMatrixYZ__p4(void *dst, void *src) __asm__("MatrixDrive_TurnXObjectMatrixYZ");
extern int func_00104F20__p4(void) __asm__("func_00104F20");
extern int *func_00105268__p4(void) __asm__("func_00105268");
extern void func_00105308(float a, float b, float c);

void GetRootQuaternionByDObj(void *a0)
{
    register float rf12 __asm__("$f12");
    register float rf13 __asm__("$f13");
    register float rf14 __asm__("$f14");
    float a = rf12;
    float b = rf13;
    float c = rf14;
    func_00104F20__p4();
    MatrixDrive_TurnXObjectMatrixYZ__p4(func_00105278(), (void *)((char *)a0 + 0x20));
    func_00105308(a, b, c);
    MatrixDrive_TurnXObjectMatrixYZ__p4((void *)*(int *)((char *)a0 + 0xC), func_00105278());
    func_00105268__p4();
}

void UpdateRootMatrixByDObj(int a0)
{
    GetRootQuaternionByDObj((int)((GObj *)(a0))->p_15C);
}

void GetRootQuaternion(int a0, int a1)
{
    RegularizeQuaternion(a0, a1 + 0x60);
    func_0010DDB8(a0, a0, *(int *)(a1 + 0x10));
}

void UpdateRootMatrix(void *a0, int a1) {
    GetRootQuaternion(a0, *(void **)(a1 + 0x15C));
}

void SetRootBaseQuaternion(int *self, int *other)
{
    func_00104F20();
    MatrixDrive_TurnXObjectMatrixYZ(func_00105278(), (char *)self + 0x20);
    func_0010DF70(other);
    MatrixDrive_TurnXObjectMatrixYZ((void *)self[0xC/4], func_00105278());
    func_00105268();
    func_0010DDB8((void *)self[0x10/4], (char *)self + 0x60, other);
}

extern void SetRootBaseQuaternion__p4(void *a0, void *a1) __asm__("SetRootBaseQuaternion");

void SetRootQuaternion(int a0, void *a1) {
    SetRootBaseQuaternion__p4(*(void **)(a0 + 0x15C), a1);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetRootMatrixWithTransOffsetByDObj);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", func_00102C10);

extern void SetMotionBlendlessNode(void *a0);
extern void SetRootMatrixWithTransOffsetByDObj(void *a0);

void SetRootMatrixWithTransOffset(void *a0) {
    SetRootMatrixWithTransOffsetByDObj(a0);
    SetMotionBlendlessNode(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetRootMatrixRotOffsetByDObj);

void GetRootMatrixRotOffset(int *self, int *other, char *p)
{
    MatrixDrive_TurnObjectMatrix((int)self, (int)p);
    {
        char *sub = ((GObj *)((char *)other))->p_15C;
        char *a = *(char **)sub;
        if (a != 0) {
            char *inner_struct = ((GObj *)(a))->p_15C;
            int inner_field = *(int *)(inner_struct + 0xC);
            int idx = *(int *)(sub + 0x4);
            func_002438B8(self, inner_field + (idx << 6), p);
        }
    }
    *(int *)((char *)self + 0x4) = 0;
    func_00243978(self, self);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetRootMatrixRotOffsetByDObj);

void SetRootMatrixRotOffset(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, (int)((GObj *)(a1))->p_15C + 0x130);
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPositionNoFittingWithNodePoint);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPositionWithNodePoint);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", LocalizeGeometry);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetGlobalDirectionOrient);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GlobalizeGeometry);

void GetRootVelocity(int *self, int *a1)
{
    int buf[16];
    char *obj = (char *)a1[0];
    char *ctx = ((GObj *)(obj))->p_15C;
    MatrixDrive_TurnXObjectMatrixYZ(buf, (void *)(*(int *)(ctx + 0xC) + (a1[1] << 6)));
    MatrixDrive_TransMatrix((char *)buf, (char *)buf);
    func_002438B8((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520), (int)buf,
                  (char *)((GObj *)((char *)self))->p_15C + 0x520);
    func_00243978((int *)((char *)((GObj *)((char *)self))->p_15C + 0x520),
                  (int *)((char *)((GObj *)((char *)self))->p_15C + 0x520));
    ((GObj *)((char *)self))->p_15C->f_52C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialInverseMatrixByDObj);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialInverseMatrix);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialSkeltonMatrixByDObj);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", MakeCharGObjList);

void cylinderCollisionCheck(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    func_0010DEC0(a0, src + 0xD0, p);
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

void LocalizeDirectionOrient(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    func_0010DEC0(a0, src + 0xD0, p);
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

void GetCylinderCollision(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        func_002438B8((int *)a0,
                      *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
                      (char *)p);
    } else {
        MatrixDrive_TurnObjectMatrix((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetCylinderCollisionWithExceptOwnCollision);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", CylinderCollision);

INCLUDE_ASM("asm/nonmatchings/src/geometryManager", CylinderCollisionWithControlDynamics);

void GetRootMatrixByDObj(void *a0, char *outer)
{
    char *src = ((GObj *)(outer))->p_15C;
    float *p = (float *)(src + 0xA0);
    float f0;
    int *g = *(int **)src;
    if (g) {
        func_002438B8((int *)a0,
                      *(int *)((int)((GObj *)((char *)g))->p_15C + 0xC) + (*(int *)(src + 4) << 6),
                      (char *)p);
    } else {
        MatrixDrive_TurnObjectMatrix((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}

