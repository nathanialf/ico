#include "common.h"

#include "vu0.h"






extern void _MulMatrix();
extern void getQuaternionFromMatrix();
extern int * func_00105278();
extern void RegularizeQuaternion();
extern int D_00553E48[];
extern void SetIdentityQuaternion();
extern char D_00553E00[];
extern void debug_StdPrintfDummy();
extern char D_00553E28[];
extern int D_00660A30[];
extern int D_00631B7C;
int *GetTableSin(void)
{
    return &D_00660A30[D_00631B7C * 4];
}

void PushQuaternionWithNoCopy(void)
{
    int v = D_00631B7C;
    if (v < 0) {
        debug_StdPrintfDummy(D_00553E00);
        SetIdentityQuaternion();
        v = D_00631B7C;
    }
    v++;
    D_00631B7C = v;
    if (v >= 0x40) {
        debug_StdPrintfDummy(D_00553E28);
        v = 0x3F;
        D_00631B7C = v;
    }
}

void PopQuaternion(void)
{
    D_00631B7C -= 1;
    if (D_00631B7C < 0) {
        debug_StdPrintfDummy(D_00553E48);
        D_00631B7C = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", SetQuaternionByAxisRotate);

extern float _ScaleVector(int *self, void *p, float arg);
extern float GetTableCos(int x);
extern float p2o_SetDefaultEnviroment(int x);

void SetQuaternionByAxisRotateWithNoRegularize(int *self, int a1, float x, float y, float z) {
    char buf[0x10];
    int half = (a1 << 16) >> 17;
    float f;
    *(float *)(buf + 0) = x;
    *(float *)(buf + 4) = y;
    *(float *)(buf + 8) = z;
    *(int *)(buf + 0xC) = 0;
    f = p2o_SetDefaultEnviroment(half);
    _ScaleVector(self, buf, f);
    *(float *)((char *)self + 0xC) = GetTableCos(half);
}

extern void _NormalizeVector(void *out, int *p);
extern float _Sqrt(float t);

void SetQuaternionByAxisRotateEAngle(float *out, float *in, float x, float y, float z) {
    float v[4];
    float r[4];
    float s1, s2;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
    s1 = _Sqrt((in[0] + 1.0f) * 0.5f);
    s2 = _Sqrt((1.0f - in[0]) * 0.5f);
    _NormalizeVector(r, (int *)v);
    out[0] = r[0] * s2;
    out[1] = r[1] * s2;
    out[2] = r[2] * s2;
    out[3] = s1;
}

void SetQuaternionByAxisRotateV(int *self, short a1, int *src)
{
    char buf[0x10];
    int half;
    float f;
    _NormalizeVector(buf, src);
    half = a1 >> 1;
    f = p2o_SetDefaultEnviroment(half);
    _ScaleVector(self, buf, f);
    *(float *)((char *)self + 0xC) = GetTableCos(half);
}

void SetQuaternionByAxisRotateVWithNoRegularize(int *self, int a1, void *src)
{
    int half = (a1 << 16) >> 17;
    float f;
    f = p2o_SetDefaultEnviroment(half);
    _ScaleVector(self, src, f);
    *(float *)((char *)self + 0xC) = GetTableCos(half);
}

void MultiQuaternion(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 11, 0x0, a1);
    VU0_LSV(lqc2, 12, 0x0, a2);
    VU0_V3OP(vmul.xyzw, 13, 11, 12);
    VU0_V3OP_BC(vaddy.x, 13, 13, 13, y);
    VU0_V3OP_BC(vaddz.x, 13, 13, 13, z);
    VU0_V3OP_BC(vsubx.w, 13, 13, 13, x);
    VU0_V3OP_BC(vmulw.xyz, 14, 12, 11, w);
    VU0_V3OP_BC(vmulw.xyz, 15, 11, 12, w);
    VU0_V3OP_ACC(vopmula.xyz, 12, 11);
    VU0_V3OP(vopmsub.xyz, 16, 11, 12);
    VU0_V3OP(vadd.xyz, 13, 14, 15);
    VU0_V3OP(vadd.xyz, 13, 13, 16);
    VU0_LSV(sqc2, 13, 0x0, a0);
    VU0_NOP();
}

void DivQuaternion(int self, int a1, int a2)
{
    int buf[4];
    RegularizeQuaternion(buf, a2);
    MultiQuaternion(self, buf, a1);
}

extern char D_00276150[];

void GetMatrixFromQuaternionRotElem(char *a0, char *a1)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf11, 0x0($5)\n"
        "lqc2 $vf12, 0x0(%0)\n"
        "vmr32.w $vf14, $vf0\n"
        "vmr32.w $vf15, $vf0\n"
        "vmr32.w $vf16, $vf0\n"
        "vopmula.xyz ACC, $vf11, $vf12\n"
        "vmadd.xyz $vf11, $vf0, $vf0\n"
        "vmulw.xyzw $vf11, $vf11, $vf12w\n"
        "vmul.xyz $vf13, $vf11, $vf11\n"
        "vopmula.xyz ACC, $vf11, $vf11\n"
        "vmaddw.xyz $vf15, $vf11, $vf11w\n"
        "vmsubw.xyz $vf16, $vf11, $vf11w\n"
        "vopmula.xyz ACC, $vf13, $vf12\n"
        "vmadd.xyz $vf17, $vf13, $vf12\n"
        "vopmula.xyz ACC, $vf15, $vf12\n"
        "vmadd.xyz $vf15, $vf0, $vf0\n"
        "vsub.xyz $vf14, $vf12, $vf17\n"
        "vmove.y $vf17, $vf14\n"
        "vmove.y $vf14, $vf16\n"
        "vmove.y $vf16, $vf15\n"
        "vmove.y $vf15, $vf17\n"
        "vmove.z $vf17, $vf14\n"
        "vmove.z $vf14, $vf15\n"
        "vmove.z $vf15, $vf16\n"
        "vmove.z $vf16, $vf17\n"
        "sqc2 $vf14, 0x0($4)\n"
        "sqc2 $vf15, 0x10($4)\n"
        "sqc2 $vf16, 0x20($4)\n"
        ".set reorder\n"
        : : "r"(D_00276150) : "memory");
}

extern void MatrixDrive_TurnObjectMatrix(char *a0, char *a1);

void GetMatrixFromQuaternionPos(char *a0, char *a1, char *a2)
{
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf11, 0x0(%2)\n"
        "lqc2 $vf12, 0x0(%0)\n"
        "vmr32.w $vf14, $vf0\n"
        "vmr32.w $vf15, $vf0\n"
        "vmr32.w $vf16, $vf0\n"
        "vopmula.xyz ACC, $vf11, $vf12\n"
        "vmadd.xyz $vf11, $vf0, $vf0\n"
        "vmulw.xyzw $vf11, $vf11, $vf12w\n"
        "vmul.xyz $vf13, $vf11, $vf11\n"
        "vopmula.xyz ACC, $vf11, $vf11\n"
        "vmaddw.xyz $vf15, $vf11, $vf11w\n"
        "vmsubw.xyz $vf16, $vf11, $vf11w\n"
        "vopmula.xyz ACC, $vf13, $vf12\n"
        "vmadd.xyz $vf17, $vf13, $vf12\n"
        "vopmula.xyz ACC, $vf15, $vf12\n"
        "vmadd.xyz $vf15, $vf0, $vf0\n"
        "vsub.xyz $vf14, $vf12, $vf17\n"
        "vmove.y $vf17, $vf14\n"
        "vmove.y $vf14, $vf16\n"
        "vmove.y $vf16, $vf15\n"
        "vmove.y $vf15, $vf17\n"
        "vmove.z $vf17, $vf14\n"
        "vmove.z $vf14, $vf15\n"
        "vmove.z $vf15, $vf16\n"
        "vmove.z $vf16, $vf17\n"
        "sqc2 $vf14, 0x0(%1)\n"
        "sqc2 $vf15, 0x10(%1)\n"
        "sqc2 $vf16, 0x20(%1)\n"
        ".set reorder\n"
        : : "r"(D_00276150), "r"(a0), "r"(a1) : "memory");
    MatrixDrive_TurnObjectMatrix(a0 + 0x30, a2);
    *(float *)(a0 + 0x3C) = 1.0f;
}

void MultiMatrixByQuaternion(void *src)
{
    int local[16];
    void *r1, *r2;
    getQuaternionFromMatrix(local, src);
    r1 = func_00105278();
    r2 = func_00105278();
    _MulMatrix(r1, r2, local);
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetMirrorQuaternion);

extern char D_00275870[];

void func_0010E0B8(void *self, int a1)
{
    char buf[0x10];
    int half = (-(a1 << 16)) >> 17;
    char *axis = D_00275870;
    float f;
    f = p2o_SetDefaultEnviroment(half);
    _ScaleVector((int *)buf, axis, f);
    *(float *)(buf + 0xC) = GetTableCos(half);
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf11, 0x0(%0)\n"
        "lqc2 $vf12, %1\n"
        "vmul.xyzw $vf13, $vf11, $vf12\n"
        "vaddy.x $vf13, $vf13, $vf13y\n"
        "vaddz.x $vf13, $vf13, $vf13z\n"
        "vsubx.w $vf13, $vf13, $vf13x\n"
        "vmulw.xyz $vf14, $vf12, $vf11w\n"
        "vmulw.xyz $vf15, $vf11, $vf12w\n"
        "vopmula.xyz ACC, $vf12, $vf11\n"
        "vopmsub.xyz $vf16, $vf11, $vf12\n"
        "vadd.xyz $vf13, $vf14, $vf15\n"
        "vadd.xyz $vf13, $vf13, $vf16\n"
        "sqc2 $vf13, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(self), "m"(buf[0]) : "memory");
}

extern char D_00275880[];

void func_0010E158(void *self, int a1)
{
    char buf[0x10];
    int half = (-(a1 << 16)) >> 17;
    char *axis = D_00275880;
    float f;
    f = p2o_SetDefaultEnviroment(half);
    _ScaleVector((int *)buf, axis, f);
    *(float *)(buf + 0xC) = GetTableCos(half);
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf11, 0x0(%0)\n"
        "lqc2 $vf12, %1\n"
        "vmul.xyzw $vf13, $vf11, $vf12\n"
        "vaddy.x $vf13, $vf13, $vf13y\n"
        "vaddz.x $vf13, $vf13, $vf13z\n"
        "vsubx.w $vf13, $vf13, $vf13x\n"
        "vmulw.xyz $vf14, $vf12, $vf11w\n"
        "vmulw.xyz $vf15, $vf11, $vf12w\n"
        "vopmula.xyz ACC, $vf12, $vf11\n"
        "vopmsub.xyz $vf16, $vf11, $vf12\n"
        "vadd.xyz $vf13, $vf14, $vf15\n"
        "vadd.xyz $vf13, $vf13, $vf16\n"
        "sqc2 $vf13, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(self), "m"(buf[0]) : "memory");
}

extern char D_00275890[];

void func_0010E1F8(void *self, int a1)
{
    char buf[0x10];
    int half = (-(a1 << 16)) >> 17;
    char *axis = D_00275890;
    float f;
    f = p2o_SetDefaultEnviroment(half);
    _ScaleVector((int *)buf, axis, f);
    *(float *)(buf + 0xC) = GetTableCos(half);
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf11, 0x0(%0)\n"
        "lqc2 $vf12, %1\n"
        "vmul.xyzw $vf13, $vf11, $vf12\n"
        "vaddy.x $vf13, $vf13, $vf13y\n"
        "vaddz.x $vf13, $vf13, $vf13z\n"
        "vsubx.w $vf13, $vf13, $vf13x\n"
        "vmulw.xyz $vf14, $vf12, $vf11w\n"
        "vmulw.xyz $vf15, $vf11, $vf12w\n"
        "vopmula.xyz ACC, $vf12, $vf11\n"
        "vopmsub.xyz $vf16, $vf11, $vf12\n"
        "vadd.xyz $vf13, $vf14, $vf15\n"
        "vadd.xyz $vf13, $vf13, $vf16\n"
        "sqc2 $vf13, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(self), "m"(buf[0]) : "memory");
}

void RotQuaternionEAX(void *self, float *in)
{
    float q[4];
    float v[4];
    float r[4];
    float s1, s2;
    float *axis = v;
    v[0] = 1.0f;
    v[1] = 0.0f;
    v[2] = 0.0f;
    v[3] = 0.0f;
    s1 = _Sqrt((in[0] + 1.0f) * 0.5f);
    s2 = _Sqrt((1.0f - in[0]) * 0.5f);
    _NormalizeVector(r, (int *)axis);
    q[0] = r[0] * s2;
    q[1] = r[1] * s2;
    q[2] = r[2] * s2;
    q[3] = s1;
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf11, 0x0(%0)\n"
        "lqc2 $vf12, %1\n"
        "vmul.xyzw $vf13, $vf11, $vf12\n"
        "vaddy.x $vf13, $vf13, $vf13y\n"
        "vaddz.x $vf13, $vf13, $vf13z\n"
        "vsubx.w $vf13, $vf13, $vf13x\n"
        "vmulw.xyz $vf14, $vf12, $vf11w\n"
        "vmulw.xyz $vf15, $vf11, $vf12w\n"
        "vopmula.xyz ACC, $vf12, $vf11\n"
        "vopmsub.xyz $vf16, $vf11, $vf12\n"
        "vadd.xyz $vf13, $vf14, $vf15\n"
        "vadd.xyz $vf13, $vf13, $vf16\n"
        "sqc2 $vf13, 0x0(%0)\n"
        ".set reorder\n"
        : : "r"(self), "m"(q[0]) : "memory");
}

