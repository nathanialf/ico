#include "common.h"
#include "ico/types.h"

extern int func_00104D20(void);
extern int *func_00105078(void);
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern void func_00105108(float a, float b, float c);
extern int *func_00105068(void);

void GetRootQuaternionByDObj(void *a0)
{
    register float rf12 __asm__("$f12");
    register float rf13 __asm__("$f13");
    register float rf14 __asm__("$f14");
    float a = rf12;
    float b = rf13;
    float c = rf14;
    func_00104D20();
    MatrixDrive_TurnXObjectMatrixYZ(func_00105078(), (void *)((char *)a0 + 0x20));
    func_00105108(a, b, c);
    MatrixDrive_TurnXObjectMatrixYZ((void *)*(int *)((char *)a0 + 0xC), func_00105078());
    func_00105068();
}

extern void GetRootQuaternionByDObj(void *a0);

void UpdateRootMatrixByDObj(int a0) {
    GetRootQuaternionByDObj(*(void **)(a0 + 0x15C));
}

extern void RegularizeQuaternion(int a0, int a1);
extern void func_0010E148(int a0, int a1, int a2);

void GetRootQuaternion(int a0, int a1)
{
    RegularizeQuaternion(a0, a1 + 0x60);
    func_0010E148(a0, a0, *(int *)(a1 + 0x10));
}


void UpdateRootMatrix(void *a0, int a1) {
    GetRootQuaternion(a0, *(void **)(a1 + 0x15C));
}

extern int func_00104D20(void);
extern int *func_00105078(void);
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern void func_0010E300(void *p);
extern int *func_00105068(void);

extern void func_0010E148(int a0, int a1, int a2);

void SetRootBaseQuaternion(void *a0, void *a1) {
    func_00104D20();
    MatrixDrive_TurnXObjectMatrixYZ(func_00105078(), (void *)((char *)a0 + 0x20));
    func_0010E300(a1);
    MatrixDrive_TurnXObjectMatrixYZ((void *)*(int *)((char *)a0 + 0xC), func_00105078());
    func_00105068();
    func_0010E148(*(int *)((char *)a0 + 0x10), (int)((char *)a0 + 0x60), (int)a1);
}


void SetRootQuaternion(int a0, void *a1) {
    SetRootBaseQuaternion(*(void **)(a0 + 0x15C), a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetRootMatrixWithTransOffsetByDObj);

extern void SetRootMatrixWithTransOffsetByDObj(void *a0);
extern void SetMotionBlendlessNode(void *a0);

void SetRootMatrixWithTransOffset(void *a0) {
    SetRootMatrixWithTransOffsetByDObj(a0);
    SetMotionBlendlessNode(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetRootMatrixRotOffsetByDObj);

extern void func_0023FDD8(int *self, int v, char *p);
extern void func_0023FE98(int *out, int *src);
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

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
            func_0023FDD8(self, inner_field + (idx << 6), p);
        }
    }
    *(int *)((char *)self + 0x4) = 0;
    func_0023FE98(self, self);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetRootMatrixRotOffsetByDObj);


void SetRootMatrixRotOffset(int a0, char *a1) {
    MatrixDrive_TurnObjectMatrix(a0, *(char **)(a1 + 0x15C) + 0x120);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetDirectRootPositionNoFittingWithNodePoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", SetDirectRootPositionWithNodePoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", LocalizeGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetGlobalDirectionOrient);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GlobalizeGeometry);

extern void MatrixDrive_TransMatrix(void *out, void *src);

void GetRootVelocity(char *a0, int *a1) {
    char buf[0x40];
    char *m = *(char **)(a1[0] + 0x15C);
    MatrixDrive_TurnXObjectMatrixYZ(buf, (void *)(*(int *)(m + 0xC) + a1[1] * 0x40));
    MatrixDrive_TransMatrix(buf, buf);
    func_0023FDD8((int *)(*(char **)(a0 + 0x15C) + 0x510), (int)buf, (char *)(*(char **)(a0 + 0x15C) + 0x510));
    func_0023FE98((int *)(*(char **)(a0 + 0x15C) + 0x510), (int *)(*(char **)(a0 + 0x15C) + 0x510));
    *(int *)(*(char **)(a0 + 0x15C) + 0x51C) = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetInitialInverseMatrixByDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetInitialInverseMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetInitialSkeltonMatrixByDObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", MakeCharGObjList);

void cylinderCollisionCheck(char *a0, char *a1) {
    char *sub = a1;
    char *p = sub + 0xA0;
    func_0010E250(a0, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0023FE08(a0, *(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 0x4) << 6), a0);
        }
    }
    *(float *)(a0 + 0x34) = *(float *)(a0 + 0x34) + *(float *)(p + 0xB0);
}

extern void func_0010E250();
extern void func_0023FE08();

void LocalizeDirectionOrient(char *a0, char *a1) {
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    func_0010E250(a0, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0023FE08(a0, *(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 0x4) << 6), a0);
        }
    }
    *(float *)(a0 + 0x34) = *(float *)(a0 + 0x34) + *(float *)(p + 0xB0);
}

void GetCylinderCollision(char *a0, char *a1) {
    char *sub = a1;
    char *p = sub + 0xA0;
    char *a = *(char **)sub;
    if (a != 0) {
        char *inner_struct = *(char **)(a + 0x15C);
        int inner_field = *(int *)(inner_struct + 0xC);
        int idx = *(int *)(sub + 0x4);
        func_0023FDD8((int *)a0, inner_field + (idx << 6), p);
    } else {
        MatrixDrive_TurnObjectMatrix((int)a0, (int)p);
    }
    {
        float sum = *(float *)(a0 + 0x4) + *(float *)(p + 0xB0);
        *(float *)(a0 + 0xC) = 1.0f;
        *(float *)(a0 + 0x4) = sum;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", GetCylinderCollisionWithExceptOwnCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", CylinderCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/geometryManager", CylinderCollisionWithControlDynamics);

void GetRootMatrixByDObj(char *a0, char *a1) {
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    char *a = *(char **)sub;
    if (a != 0) {
        char *inner_struct = *(char **)(a + 0x15C);
        int inner_field = *(int *)(inner_struct + 0xC);
        int idx = *(int *)(sub + 0x4);
        func_0023FDD8((int *)a0, inner_field + (idx << 6), p);
    } else {
        MatrixDrive_TurnObjectMatrix((int)a0, (int)p);
    }
    {
        float sum = *(float *)(a0 + 0x4) + *(float *)(p + 0xB0);
        *(float *)(a0 + 0xC) = 1.0f;
        *(float *)(a0 + 0x4) = sum;
    }
}
