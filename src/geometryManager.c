#include "common.h"

#include "ico/types.h"

#include "vu0.h"

#include "sugiCommon.h"

void GetRootQuaternionByDObj(int a0, int *a1)
{
    int *p;
    int *q;
    int idx;
    p = (int *)a1[0];
    if (p == 0) goto null_path;
    q = (int *)p[0x57];
    idx = a1[1];
    MultiQuaternion(a0, q[0x4] + (idx << 4), (int)a1 + 0xD0);
    return;
null_path:
    CopyQuaternion(a0, (int)a1 + 0xD0);
}
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern void func_0025D440(void *a0, void *a1, void *a2);
void UpdateRootMatrixByDObj(char *a0) {
    char *p = a0 + 0xA0;
    char *fobj = *(char **)(a0 + 0xC);
    GetMatrixFromQuaternionPos(fobj, a0 + 0xD0, p);
    {
        char *q = *(char **)a0;
        if (q != 0) {
            func_0025D440(fobj, *(char **)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(a0 + 0x4) << 6), fobj);
        }
    }
    *(float *)(fobj + 0x34) = *(float *)(fobj + 0x34) + *(float *)(p + 0xC0);
    GetRootQuaternionByDObj(*(void **)(a0 + 0x10), a0);
}
extern void GetRootQuaternionByDObj(int a0, int *a1);

void GetRootQuaternion(int a0, int a1)
{
    GetRootQuaternionByDObj(a0, (int)((GObj *)(a1))->p_15C);
}
extern void UpdateRootMatrixByDObj();

void UpdateRootMatrix(int a0)
{
    UpdateRootMatrixByDObj((int)((GObj *)(a0))->p_15C);
}
extern void CopyQuaternion();

void SetRootBaseQuaternion(int a0)
{
    CopyQuaternion((int)((GObj *)(a0))->p_15C + 0xC0);
}
extern void CopyQuaternion__pn(void *a0, void *a1) __asm__("CopyQuaternion");
extern void DivQuaternion(void *a0, void *a1, int a2);

void SetRootQuaternion(char *a0, void *a1) {
    char *q = *(char **)(a0 + 0x15C) + 0xD0;
    char *p;
    CopyQuaternion__pn(q, a1);
    p = *(char **)(a0 + 0x15C);
    if (*(int *)p != 0) {
        char *m = *(char **)(*(int *)p + 0x15C);
        DivQuaternion(q, a1, *(int *)(m + 0x10) + (*(int *)(p + 4) << 4));
    }
}
extern void CopyMatrix();
extern int * MatrixDrive_GetMatrix();
extern void MatrixDrive_PopMatrix();
extern void MatrixDrive_PushMatrix();
extern void MatrixDrive_TransMatrix(float a, float b, float c);

void SetRootMatrixWithTransOffsetByDObj(void *a0)
{
    register float rf12 __asm__("$f12");
    register float rf13 __asm__("$f13");
    register float rf14 __asm__("$f14");
    float a = rf12;
    float b = rf13;
    float c = rf14;
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), (void *)((char *)a0 + 0x20));
    MatrixDrive_TransMatrix(a, b, c);
    CopyMatrix((void *)*(int *)((char *)a0 + 0xC), MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
}
void SetRootMatrixWithTransOffset(int a0)
{
    SetRootMatrixWithTransOffsetByDObj((int)((GObj *)(a0))->p_15C);
}
extern void GetInverseQuaternion();
extern void MultiQuaternion();

void GetRootMatrixRotOffsetByDObj(int a0, int a1)
{
    GetInverseQuaternion(a0, a1 + 0x60);
    MultiQuaternion(a0, a0, *(int *)(a1 + 0x10));
}
void GetRootMatrixRotOffset(void *a0, int a1) {
    GetRootMatrixRotOffsetByDObj(a0, *(void **)(a1 + 0x15C));
}
extern void MultiMatrixByQuaternion();

void SetRootMatrixRotOffsetByDObj(int *self, int *other)
{
    MatrixDrive_PushMatrix();
    CopyMatrix(MatrixDrive_GetMatrix(), (char *)self + 0x20);
    MultiMatrixByQuaternion(other);
    CopyMatrix((void *)self[0xC/4], MatrixDrive_GetMatrix());
    MatrixDrive_PopMatrix();
    MultiQuaternion((void *)self[0x10/4], (char *)self + 0x60, other);
}
void SetRootMatrixRotOffset(int a0, void *a1) {
    SetRootMatrixRotOffsetByDObj(*(void **)(a0 + 0x15C), a1);
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPositionNoFittingWithNodePoint);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", SetDirectRootPositionNoFittingWithNodePointXZ);
extern void AdjustMotionHeightToNearestField(void *a0);
extern void SetDirectRootPositionNoFittingWithNodePoint(void *a0);

void SetDirectRootPositionWithNodePoint(void *a0) {
    SetDirectRootPositionNoFittingWithNodePoint(a0);
    AdjustMotionHeightToNearestField(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", LocalizeGeometry);
extern void CopyVector();
extern void sceVu0ApplyMatrix();
extern void sceVu0Normalize();

void GetGlobalDirectionOrient(int *self, int *other, char *p)
{
    CopyVector((int)self, (int)p);
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
    CopyVector(a0, (int)((GObj *)(a1))->p_15C + 0x130);
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialInverseMatrixByDObj);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialInverseMatrix);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", GetInitialSkeltonMatrixByDObj);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", MakeCharGObjList);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", cylinderCollisionCheck);
extern void MatrixDrive_SetTransposeMatrix();

void LocalizeDirectionOrient(int *self, int *a1)
{
    int buf[16];
    char *obj = (char *)a1[0];
    char *ctx = ((GObj *)(obj))->p_15C;
    CopyMatrix(buf, (void *)(*(int *)(ctx + 0xC) + (a1[1] << 6)));
    MatrixDrive_SetTransposeMatrix((char *)buf, (char *)buf);
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
extern void GetMatrixFromQuaternionPos();
extern void func_0025D440();

void GetRootMatrixByDObj(void *a0, char *src)
{
    float *p = (float *)(src + 0xA0);
    GetMatrixFromQuaternionPos(a0, src + 0xD0, p);
    {
        int *g = *(int **)src;
        if (g) {
            func_0025D440(a0,
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
            func_0025D440(a0,
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
        CopyVector((int)a0, (int)p);
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
        CopyVector((int)a0, (int)p);
    }
    f0 = p[0x30];
    *(float *)((char *)a0 + 0x4) += f0;
    *(float *)((char *)a0 + 0xC) = 1.0f;
}
extern char D_0028FF30[];
extern void GetMatrixFromQuaternionPos__pn(void *a0, void *a1, void *a2) __asm__("GetMatrixFromQuaternionPos");
extern void sceVu0ApplyMatrix__pn(int *buf, char *p, int x) __asm__("sceVu0ApplyMatrix");
extern void sceVu0Normalize__pn(char *a0, char *a1) __asm__("sceVu0Normalize");

void GetRootOrient(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos__pn(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0025D440(buf, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xC0);
    sceVu0ApplyMatrix__pn((int *)a0, buf, (int)D_0028FF30);
    *(int *)(a0 + 4) = 0;
    sceVu0Normalize__pn(a0, a0);
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", LimitExistGeometry);
extern void CopyVector__pn(void *dst, void *src) __asm__("CopyVector");

void GetRootMatrixTransOffsetByDObj(char *dst, char *src)
{
    char tmp[0x40];
    MatrixDrive_SetTransposeMatrix(tmp, src + 0x20);
    func_0025D440(tmp, tmp, *(int *)(src + 0xC));
    CopyVector__pn((int)dst, (int)(tmp + 0x30));
}
void GetRootMatrixTransOffset(char *dst, char *src)
{
    char tmp[0x40];
    char *p = *(char **)(src + 0x15C);
    MatrixDrive_SetTransposeMatrix(tmp, p + 0x20);
    func_0025D440(tmp, tmp, *(int *)(p + 0xC));
    CopyVector__pn((int)dst, (int)(tmp + 0x30));
}
extern void GetMatrixFromQuaternion(int dst, int src);

void GetRootMotionOrient(char *a0, char *a1)
{
    char m[0x40];
    char buf[0x40];
    char *b = buf;
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos__pn(b, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0025D440(b, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)b);
        }
    }
    *(float *)(b + 0x34) = *(float *)(b + 0x34) + *(float *)(p + 0xC0);
    GetMatrixFromQuaternion((int)m, (int)(*(char **)(a1 + 0x15C) + 0xE0));
    func_0025D440(m, b, (int)m);
    sceVu0ApplyMatrix__pn((int *)a0, m, (int)D_0028FF30);
}
void GetRootMotionMatrix(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos__pn(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_0025D440(buf, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xC0);
    GetMatrixFromQuaternion((int)a0, (int)(*(char **)(a1 + 0x15C) + 0xE0));
    func_0025D440(a0, buf, (int)a0);
}
extern void AddVectorXYZ(void *a0, void *a1, void *a2);
extern void _ScaleVectorXYZ(void *a0, void *a1, float f);

void GetProjectionPosOfPlane(void *a0, void *a1, void *a2)
{
    float buf[4];
    float dot;
    dot = plane_distance(a2, a1);
    _ScaleVectorXYZ(buf, a1, -dot);
    AddVectorXYZ(a0, a2, buf);
    *(float *)((char *)a0 + 0xC) = 1.0f;
}
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);

float GetProjectionOfPlane(void *a0, void *a1, void *a2)
{
    float buf[4];
    float f = 0.0f;
    float dot;
    dot = plane_distance(a2, a1);
    _ScaleVectorXYZ(buf, a1, -dot + f);
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}
float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float f)
{
    float buf[4];
    float dot;
    dot = plane_distance(a2, a1);
    _ScaleVectorXYZ(buf, a1, -dot + f);
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}
extern int D_00668540[];

int *GetCharGObjList(void) {
    return D_00668540;
}
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", getInitialInverseMatrix);
INCLUDE_ASM("asm/nonmatchings/src/geometryManager", getInitialMatrix);
