#include "common.h"

#include "ico/types.h"
#include "vu0.h"


extern int D_0065F940[];
extern void MatrixDrive_TransMatrix();
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern void func_002438E8();
extern char D_00275890[];
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern void sceVu0ApplyMatrix(int *buf, char *p, int x);
extern void func_002438E8(char *dst, char *src, int m);
extern void sceVu0Normalize(char *a0, char *a1);

void GetRootOrient(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_002438E8(buf, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xC0);
    sceVu0ApplyMatrix((int *)a0, buf, (int)D_00275890);
    *(int *)(a0 + 4) = 0;
    sceVu0Normalize(a0, a0);
}

INCLUDE_ASM("asm/nonmatchings/src/keyInput", LimitExistGeometry);

void GetRootMatrixTransOffsetByDObj(char *dst, char *src)
{
    char tmp[0x40];
    MatrixDrive_TransMatrix(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    MatrixDrive_TurnObjectMatrix((int)dst, (int)(tmp + 0x30));
}

void GetRootMatrixTransOffset(char *dst, char *src)
{
    char tmp[0x40];
    char *p = *(char **)(src + 0x15C);
    MatrixDrive_TransMatrix(tmp, p + 0x20);
    func_002438E8(tmp, tmp, *(int *)(p + 0xC));
    MatrixDrive_TurnObjectMatrix((int)dst, (int)(tmp + 0x30));
}

extern void getQuaternionFromMatrix(int dst, int src);

void GetRootMotionOrient(char *a0, char *a1)
{
    char m[0x40];
    char buf[0x40];
    char *b = buf;
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(b, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_002438E8(b, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)b);
        }
    }
    *(float *)(b + 0x34) = *(float *)(b + 0x34) + *(float *)(p + 0xC0);
    getQuaternionFromMatrix((int)m, (int)(*(char **)(a1 + 0x15C) + 0xE0));
    func_002438E8(m, b, (int)m);
    sceVu0ApplyMatrix((int *)a0, m, (int)D_00275890);
}

void GetRootMotionMatrix(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    GetMatrixFromQuaternionPos(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_002438E8(buf, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xC0);
    getQuaternionFromMatrix((int)a0, (int)(*(char **)(a1 + 0x15C) + 0xE0));
    func_002438E8(a0, buf, (int)a0);
}

extern void _ScaleVectorXYZ(void *a0, void *a1, float f);
extern void AddVectorXYZ(void *a0, void *a1, void *a2);

void GetProjectionPosOfPlane(void *a0, void *a1, void *a2)
{
    float buf[4];
    float dot;
    int v0;
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV_R(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(v0));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(dot) : "r"(v0));
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
    int v0;
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV_R(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(v0));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(dot) : "r"(v0));
    _ScaleVectorXYZ(buf, a1, -dot + f);
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}

float GetProjectionOfPlaneWithKeepAway(void *a0, void *a1, void *a2, float f)
{
    float buf[4];
    float dot;
    int v0;
    VU0_LSV_R(lqc2, 1, 0x0, a2);
    VU0_LSV_R(lqc2, 2, 0x0, a1);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(v0));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(dot) : "r"(v0));
    _ScaleVectorXYZ(buf, a1, -dot + f);
    _AddVectorXYZ(a0, a2, buf);
    return dot;
}

int *func_00104A38(void) {
    return D_0065F940;
}

extern void CopyMatrix(void *dst, void *src);
extern void func_00104F20(void);
extern void func_001052A8(char *a0);
extern void MultiMatrixByQuaternion(void *a0);
extern void *func_00105278(void);
extern void MatrixDrive_PopMatrix(void);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", getInitialInverseMatrix);


INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104AF0);


extern void debug_StdPrintfDummy();
extern void iosPadDevReadFunc(void *a0);
extern void SignalSema();
extern char D_00553B78[];
extern char D_00553B90[];
extern char D_00553BA0[];
extern char D_00553BB8[];
extern char D_00275830[];
extern char D_00275250[];
extern int D_00631AA0;

INCLUDE_ASM("asm/nonmatchings/src/keyInput", InitKeyInput);


INCLUDE_ASM("asm/nonmatchings/src/keyInput", ExecKeyInput);


extern int D_00631B40;
extern char D_0065FA40[];
extern void sceVu0UnitMatrix(void *a0);
extern void InitTableSin(void);
extern void SetIdentityQuaternion(void);

void func_00104EF0(void)
{
    D_00631B40 = 0;
    sceVu0UnitMatrix(D_0065FA40);
    InitTableSin();
    SetIdentityQuaternion();
}


void func_00104F20(void)
{
    D_00631B40 += 1;
    CopyMatrix(&D_0065FA40[D_00631B40 * 0x40],
                                    &D_0065FA40[D_00631B40 * 0x40 - 0x40]);
}

extern float GetTableCos(short a0);
extern float p2o_SetDefaultEnviroment(short a0);
extern float D_002758E0[];

void MatrixDrive_RotMatrixX(short a0)
{
    float c = GetTableCos(a0);
    float s = p2o_SetDefaultEnviroment(a0);
    D_002758E0[10] = c;
    D_002758E0[9] = -s;
    D_002758E0[6] = s;
    D_002758E0[5] = c;
    func_002438E8(&D_0065FA40[D_00631B40 * 0x40], &D_0065FA40[D_00631B40 * 0x40],
                  (int)D_002758E0);
}

extern float D_00275920[];

void MatrixDrive_RotMatrixY(short a0)
{
    float c = GetTableCos(a0);
    float s = p2o_SetDefaultEnviroment(a0);
    D_00275920[10] = c;
    D_00275920[8] = s;
    D_00275920[2] = -s;
    D_00275920[0] = c;
    func_002438E8(&D_0065FA40[D_00631B40 * 0x40], &D_0065FA40[D_00631B40 * 0x40],
                  (int)D_00275920);
}

extern float D_00275960[];

void MatrixDrive_RotMatrixZ(short a0)
{
    float c = GetTableCos(a0);
    float s = p2o_SetDefaultEnviroment(a0);
    D_00275960[5] = c;
    D_00275960[4] = -s;
    D_00275960[1] = s;
    D_00275960[0] = c;
    func_002438E8(&D_0065FA40[D_00631B40 * 0x40], &D_0065FA40[D_00631B40 * 0x40],
                  (int)D_00275960);
}

extern float D_002759A0[];

void MatrixDrive_ScaleMatrix(float x, float y, float z)
{
    D_002759A0[0] = x;
    D_002759A0[5] = y;
    D_002759A0[10] = z;
    func_002438E8(&D_0065FA40[D_00631B40 * 0x40], &D_0065FA40[D_00631B40 * 0x40],
                      (int)D_002759A0);
}

extern void memset(void *a0, int a1, int a2);
extern float FSqrt(float f);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", MatrixDrive_TurnViewMatrix);


void MatrixDrive_PushMatrixWithNoCopy(void)
{
    D_00631B40 += 1;
}

void MatrixDrive_PopMatrix(void)
{
    D_00631B40 -= 1;
}


void *func_00105278(void) {
    return &D_0065FA40[D_00631B40 * 0x40];
}

extern char D_0065FA00[];

void *func_00105290(void) {
    return &D_0065FA00[D_00631B40 * 0x40];
}

void func_001052A8(char *a0)
{
    float buf[4];
    sceVu0ApplyMatrix((int *)buf, &D_0065FA40[D_00631B40 * 0x40], (int)a0);
    buf[3] = 1.0f;
    MatrixDrive_TurnObjectMatrix(&D_0065FA40[D_00631B40 * 0x40 + 0x30], buf);
}

void func_00105308(float x, float y, float z)
{
    float v[4];
    float buf[4];
    float *m = buf;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 1.0f;
    sceVu0ApplyMatrix((int *)m, &D_0065FA40[D_00631B40 * 0x40], (int)v);
    m[3] = 1.0f;
    MatrixDrive_TurnObjectMatrix(&D_0065FA40[D_00631B40 * 0x40 + 0x30], m);
}

