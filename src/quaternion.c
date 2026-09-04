#include "common.h"

#include "vu0.h"

#include "ico/types.h"

extern int D_00639F3C;
extern int D_00669640[];
void MultiCurrentQuaternion(void *a0) {
    int *q = &D_00669640[D_00639F3C * 4];
    MultiQuaternion(q, q, a0);
}
extern int D_00639F3C;
extern int D_00669640[];
extern void GetInverseQuaternion();

void InvertCurrentQuaternion(void)
{
    int *p = &D_00669640[D_00639F3C * 4];
    GetInverseQuaternion(p, p);
}
extern void CopyQuaternion();

void SetCurrentQuaternion(int a0)
{
    CopyQuaternion(&D_00669640[D_00639F3C * 4], a0);
}
extern void RotQuaternionX();

void RotCurrentQuaternionX(short a0)
{
    RotQuaternionX(&D_00669640[D_00639F3C * 4], a0);
}
extern void RotQuaternionY();

void RotCurrentQuaternionY(short a0)
{
    RotQuaternionY(&D_00669640[D_00639F3C * 4], a0);
}
extern void RotQuaternionZ();

void RotCurrentQuaternionZ(short a0)
{
    RotQuaternionZ(&D_00669640[D_00639F3C * 4], a0);
}
extern char D_0054DA80[];
extern char D_0054DAA8[];
extern void InitQuaternionDrive(void);
extern void debug_StdPrintfDummy(char *p);

void PushQuaternion(void) {
    int v = D_00639F3C;
    if (v < 0) {
        debug_StdPrintfDummy(D_0054DA80);
        InitQuaternionDrive();
        v = D_00639F3C;
    }
    v++;
    D_00639F3C = v;
    if (v >= 0x40) {
        debug_StdPrintfDummy(D_0054DAA8);
        v = 0x3F;
        D_00639F3C = v;
    }
    {
        int idx = *(volatile int *)&D_00639F3C;
        CopyQuaternion(&D_00669640[idx * 4], &D_00669640[idx * 4 - 4]);
    }
}
extern void SetIdentityQuaternion(void *a0);

void InitQuaternionDrive(void)
{
    D_00639F3C = 0;
    SetIdentityQuaternion(D_00669640);
}
extern void CopyQuaternion__pn(void *a0, void *a1) __asm__("CopyQuaternion");
extern int D_002907E0[];

void SetIdentityQuaternion(void *a0) {
    CopyQuaternion__pn(a0, D_002907E0);
}
extern void CopyVector();
extern char D_0028FF00[];
extern char D_002907F0[];

void GetMatrixFromQuaternion(char *a0, char *a1) {
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
        : : "r"(D_002907F0) : "memory");
    CopyVector(a0 + 0x30, D_0028FF00);
}
INCLUDE_ASM("asm/nonmatchings/src/quaternion", getQuaternionFromMatrix);
extern void _TransposeMatrix(void *a0, void *a1);
extern int getQuaternionFromMatrix();

void GetQuaternionFromMatrix(void *a0, void *a1) {
    auto void getQuaternionFromMatrix(void *a, void *b) __asm__("getQuaternionFromMatrix");
    char local[0x40];
    _TransposeMatrix(local, a1);
    getQuaternionFromMatrix(a0, local);
}
INCLUDE_ASM("asm/nonmatchings/src/quaternion", CopyQuaternion);
extern void _ScaleVectorXYZ(int a0, int a1, float f);

void GetInverseQuaternion(int a0, int a1)
{
    CopyQuaternion(a0, a1);
    _ScaleVectorXYZ(a0, a1, -1.0f);
}
extern void _ScaleVector(void *a, void *b, float c);
extern float _Sqrt(float);

void RegularizeQuaternion(void *a0) {
    register float d __asm__("$f12");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0(%1)\n"
        "lqc2 $vf15, 0x0(%1)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni $2, $vf15\n"
        "mtc1 $2, $f12\n"
        ".set reorder\n"
        : "=f"(d) : "r"(a0) : "$2");
    _ScaleVector(a0, a0, 1.0f / _Sqrt(d));
}
INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetSlerpQuaternionNoRegularize);
extern void GetSlerpQuaternionNoRegularize();

void GetSlerpQuaternion(int a0)
{
    GetSlerpQuaternionNoRegularize(a0);
    RegularizeQuaternion(a0);
}
int *GetCurrentQuaternion(void)
{
    return &D_00669640[D_00639F3C * 4];
}
extern int D_00669630[];

int *GetLastQuaternion(void)
{
    return &D_00669630[D_00639F3C * 4];
}
extern void debug_StdPrintfDummy__pn() __asm__("debug_StdPrintfDummy");

void PushQuaternionWithNoCopy(void)
{
    int v = D_00639F3C;
    if (v < 0) {
        debug_StdPrintfDummy__pn(D_0054DA80);
        InitQuaternionDrive();
        v = D_00639F3C;
    }
    v++;
    D_00639F3C = v;
    if (v >= 0x40) {
        debug_StdPrintfDummy__pn(D_0054DAA8);
        v = 0x3F;
        D_00639F3C = v;
    }
}
extern int D_0054DAC8[];

void PopQuaternion(void)
{
    D_00639F3C -= 1;
    if (D_00639F3C < 0) {
        debug_StdPrintfDummy__pn(D_0054DAC8);
        D_00639F3C = 0;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/quaternion", SetQuaternionByAxisRotate);
extern float GetTableCos(int x);
extern float GetTableSin(int x);
extern float _ScaleVector__pn(int *self, void *p, float arg) __asm__("_ScaleVector");

void SetQuaternionByAxisRotateWithNoRegularize(int *self, int a1, float x, float y, float z) {
    char buf[0x10];
    int half = (a1 << 16) >> 17;
    float f;
    *(float *)(buf + 0) = x;
    *(float *)(buf + 4) = y;
    *(float *)(buf + 8) = z;
    *(int *)(buf + 0xC) = 0;
    f = GetTableSin(half);
    _ScaleVector__pn(self, buf, f);
    *(float *)((char *)self + 0xC) = GetTableCos(half);
}
extern void _NormalizeVector(void *out, int *p);
extern float _Sqrt__pn(float t) __asm__("_Sqrt");

void SetQuaternionByAxisRotateEAngle(float *out, float *in, float x, float y, float z) {
    float v[4];
    float r[4];
    float s1, s2;
    v[0] = x;
    v[1] = y;
    v[2] = z;
    v[3] = 0.0f;
    s1 = _Sqrt__pn((in[0] + 1.0f) * 0.5f);
    s2 = _Sqrt__pn((1.0f - in[0]) * 0.5f);
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
    f = GetTableSin(half);
    _ScaleVector__pn(self, buf, f);
    *(float *)((char *)self + 0xC) = GetTableCos(half);
}
void SetQuaternionByAxisRotateVWithNoRegularize(int *self, int a1, void *src)
{
    int half = (a1 << 16) >> 17;
    float f;
    f = GetTableSin(half);
    _ScaleVector__pn(self, src, f);
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
extern void MultiQuaternion__pn(int dst, int a, int b) __asm__("MultiQuaternion");

void DivQuaternion(int self, int a1, int a2)
{
    int buf[4];
    GetInverseQuaternion(buf, a2);
    MultiQuaternion__pn(self, buf, a1);
}
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
        : : "r"(D_002907F0) : "memory");
}
extern void CopyVector__pn(char *a0, char *a1) __asm__("CopyVector");

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
        : : "r"(D_002907F0), "r"(a0), "r"(a1) : "memory");
    CopyVector__pn(a0 + 0x30, a2);
    *(float *)(a0 + 0x3C) = 1.0f;
}
extern void GetMatrixFromQuaternion__pn() __asm__("GetMatrixFromQuaternion");
extern int * MatrixDrive_GetMatrix();
extern void _MulMatrix();

void MultiMatrixByQuaternion(void *src)
{
    int local[16];
    void *r1, *r2;
    GetMatrixFromQuaternion__pn(local, src);
    r1 = MatrixDrive_GetMatrix();
    r2 = MatrixDrive_GetMatrix();
    _MulMatrix(r1, r2, local);
}
INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetMirrorQuaternion);
extern char D_0028FF10[];

void RotQuaternionX(void *self, int a1)
{
    char buf[0x10];
    int half = (-(a1 << 16)) >> 17;
    char *axis = D_0028FF10;
    float f;
    f = GetTableSin(half);
    _ScaleVector__pn((int *)buf, axis, f);
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
extern char D_0028FF20[];

void RotQuaternionY(void *self, int a1)
{
    char buf[0x10];
    int half = (-(a1 << 16)) >> 17;
    char *axis = D_0028FF20;
    float f;
    f = GetTableSin(half);
    _ScaleVector__pn((int *)buf, axis, f);
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
extern char D_0028FF30[];

void RotQuaternionZ(void *self, int a1)
{
    char buf[0x10];
    int half = (-(a1 << 16)) >> 17;
    char *axis = D_0028FF30;
    float f;
    f = GetTableSin(half);
    _ScaleVector__pn((int *)buf, axis, f);
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
    s1 = _Sqrt__pn((in[0] + 1.0f) * 0.5f);
    s2 = _Sqrt__pn((1.0f - in[0]) * 0.5f);
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
INCLUDE_ASM("asm/nonmatchings/src/quaternion", RotQuaternionEAZ);
INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetXUnitVectorOfQuaternion);
INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetYUnitVectorOfQuaternion);
INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetZUnitVectorOfQuaternion);
INCLUDE_ASM("asm/nonmatchings/src/quaternion", GetDifferencialQuaternionWithNoRegularize);
float GetQuaternionMagnitude(void *a0) {
    float r;
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0(%1)\n"
        "lqc2 $vf15, 0x0(%1)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni %0, $vf15\n"
        ".set reorder\n"
        : "=r"(r) : "r"(a0));
    return _Sqrt(r);
}
void SetQuaternionByCosineAxisRotateVWithNoRegularize(void *a0, void *a1, float angle) {
    float first, second;
    first = ((float (*)(float))_Sqrt__pn)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))_Sqrt__pn)((1.0f - angle) * 0.5f);
    _ScaleVector(a0, a1, second);
    *(float *)((char *)a0 + 0xC) = first;
}
extern void _NormalizeVector__pn(void *buf) __asm__("_NormalizeVector");

void SetQuaternionByCosineAxisRotateV(void *a0, float angle) {
    float buf[4];
    float first, second;
    _NormalizeVector__pn(buf);
    first = ((float (*)(float))_Sqrt__pn)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))_Sqrt__pn)((1.0f - angle) * 0.5f);
    _ScaleVector(a0, buf, second);
    *(float *)((char *)a0 + 0xC) = first;
}
void SetQuaternionByAxisRotateVEAngle(void *a0, float *a1, void *a2) {
    float buf[4];
    float first, second;
    first = ((float (*)(float))_Sqrt__pn)((a1[0] + 1.0f) * 0.5f);
    second = ((float (*)(float))_Sqrt__pn)((1.0f - a1[0]) * 0.5f);
    ((void (*)(void *, void *))_NormalizeVector__pn)(buf, a2);
    *(float *)((char *)a0 + 0xC) = first;
    *(float *)((char *)a0 + 0x0) = buf[0] * second;
    *(float *)((char *)a0 + 0x4) = buf[1] * second;
    *(float *)((char *)a0 + 0x8) = buf[2] * second;
}
void GetQuaternionCosRadian(void *p0, void *p1, void *p2)
{
    VU0_LSV(lqc2, 14, 0x0, a0);
    VU0_LSV(lqc2, 15, 0x0, a1);
    VU0_V3OP(vmul.xyzw, 15, 14, 15);
    VU0_V3OP_BC(vaddy.x, 15, 15, 15, y);
    VU0_V3OP_BC(vaddz.x, 15, 15, 15, z);
    VU0_V3OP_BC(vaddw.x, 15, 15, 15, w);
    VU0_QMFC2_NI(v0, 15);
    VU0_MTC1(v0, 0);
    VU0_NOP();
}
