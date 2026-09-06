#include "common.h"

#include "vu0.h"

#include "ico/types.h"

/* prototypes: their order is the inline tail's emission order */
int *GetCurrentQuaternion(void);
int *GetLastQuaternion(void);
void PushQuaternionWithNoCopy(void);
void PopQuaternion(void);
void SetQuaternionByAxisRotate(int *self, short a1, float x, float y, float z);
void SetQuaternionByAxisRotateWithNoRegularize(int *self, int a1, float x, float y, float z);
void SetQuaternionByAxisRotateEAngle(float *out, float *in, float x, float y, float z);
void SetQuaternionByAxisRotateV(int *self, short a1, int *src);
void SetQuaternionByAxisRotateVWithNoRegularize(int *self, short a1, void *src);
void MultiQuaternion(void *p0, void *p1, void *p2);
void DivQuaternion(int self, int a1, int a2);
void GetMatrixFromQuaternionRotElem(char *a0, char *a1);
void GetMatrixFromQuaternionPos(char *a0, char *a1, char *a2);
void MultiMatrixByQuaternion(void *src);
void GetMirrorQuaternion(float *dst, float *src, int mode);
void RotQuaternionX(void *self, int a1);
void RotQuaternionY(void *self, int a1);
void RotQuaternionZ(void *self, int a1);
void RotQuaternionEAX(void *self, float *in);
void RotQuaternionEAZ(void *self, float *in);
void GetXUnitVectorOfQuaternion(float *out, float *q);
void GetYUnitVectorOfQuaternion(float *out, float *q);
void GetZUnitVectorOfQuaternion(float *out, float *q);
void GetDifferencialQuaternionWithNoRegularize(void *out, void *a, void *b);
float GetQuaternionMagnitude(void *a0);
void SetQuaternionByCosineAxisRotateVWithNoRegularize(void *a0, void *a1, float angle);
void SetQuaternionByCosineAxisRotateV(void *a0, void *a1, float angle);
void SetQuaternionByAxisRotateVEAngle(void *a0, float *a1, void *a2);
float GetQuaternionCosRadian(void *p0, void *p1);

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

void RotCurrentQuaternionX(short a0)
{
    RotQuaternionX(&D_00669640[D_00639F3C * 4], a0);
}

void RotCurrentQuaternionY(short a0)
{
    RotQuaternionY(&D_00669640[D_00639F3C * 4], a0);
}

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
void CopyQuaternion(void *a0, void *a1) {
    CopyVector(a0, a1);
}
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
inline float GetQuaternionCosRadian(void *p0, void *p1)
{
    float r;
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0(%1)\n"
        "lqc2 $vf15, 0x0(%2)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni $2, $vf15\n"
        "mtc1 $2, %0\n"
        ".set reorder\n"
        : "=f"(r) : "r"(p0), "r"(p1) : "$2");
    return r;
}
extern void CopyQuaternion(void *a0, void *a1);
extern void _ScaleVector(void *a, void *b, float c);
extern int GetTableArcCos(float c);
extern float GetTableSin(int x);
extern void _InterVector(void *out, void *a, void *b, float t);
extern void _AddVector(void *out, void *a, void *b);
extern float D_00638BB8;

void GetSlerpQuaternionNoRegularize(void *out, void *qa, void *qb, float t)
{
    float tmp[4];
    float tq[4];
    float c;
    int ang;
    float s;
    float inv;
    float sa, sb;

    CopyQuaternion(tmp, qb);
    c = GetQuaternionCosRadian(qa, tmp);
    if (c < 0.0f) {
        _ScaleVector(tmp, tmp, -1.0f);
        c = GetQuaternionCosRadian(qa, tmp);
    }
    ang = GetTableArcCos(c);
    s = GetTableSin(ang);
    if (s < D_00638BB8) {
        _InterVector(out, qa, tmp, t);
        return;
    }
    inv = 1.0f / s;
    sa = GetTableSin((short)((float)ang * t)) * inv;
    sb = GetTableSin((short)((float)ang * (1.0f - t))) * inv;
    _ScaleVector(out, qa, sa);
    _ScaleVector(tq, tmp, sb);
    _AddVector(out, out, tq);
}
extern void GetSlerpQuaternionNoRegularize();

void GetSlerpQuaternion(int a0)
{
    GetSlerpQuaternionNoRegularize(a0);
    RegularizeQuaternion(a0);
}
inline int *GetCurrentQuaternion(void)
{
    return &D_00669640[D_00639F3C * 4];
}
extern int D_00669630[];

inline int *GetLastQuaternion(void)
{
    return &D_00669630[D_00639F3C * 4];
}
extern void debug_StdPrintfDummy__pn() __asm__("debug_StdPrintfDummy");

inline void PushQuaternionWithNoCopy(void)
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

inline void PopQuaternion(void)
{
    D_00639F3C -= 1;
    if (D_00639F3C < 0) {
        debug_StdPrintfDummy__pn(D_0054DAC8);
        D_00639F3C = 0;
    }
}
extern void _NormalizeVector(void *out, int *p);
extern float GetTableCos(int x);
extern float GetTableSin(int x);

inline void SetQuaternionByAxisRotateVWithNoRegularize(int *self, short a1, void *src)
{
    int half = a1 >> 1;
    float f;
    f = GetTableSin(half);
    _ScaleVector(self, src, f);
    *(float *)((char *)self + 0xC) = GetTableCos(half);
}
inline void SetQuaternionByAxisRotateV(int *self, short a1, int *src)
{
    char buf[0x10];
    _NormalizeVector(buf, src);
    SetQuaternionByAxisRotateVWithNoRegularize(self, a1, buf);
}
inline void SetQuaternionByAxisRotate(int *self, short a1, float x, float y, float z)
{
    float v[4] = { x, y, z, 0.0f };
    SetQuaternionByAxisRotateV(self, a1, (int *)v);
}
extern float GetTableCos(int x);
extern float GetTableSin(int x);
extern float _ScaleVector__pn(int *self, void *p, float arg) __asm__("_ScaleVector");

inline void SetQuaternionByAxisRotateWithNoRegularize(int *self, int a1, float x, float y, float z) {
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

inline void SetQuaternionByAxisRotateVEAngle(void *a0, float *a1, void *a2) {
    float buf[4];
    float first, second;
    first = _Sqrt((a1[0] + 1.0f) * 0.5f);
    second = _Sqrt((1.0f - a1[0]) * 0.5f);
    _NormalizeVector(buf, a2);
    *(float *)((char *)a0 + 0xC) = first;
    *(float *)((char *)a0 + 0x0) = buf[0] * second;
    *(float *)((char *)a0 + 0x4) = buf[1] * second;
    *(float *)((char *)a0 + 0x8) = buf[2] * second;
}
inline void SetQuaternionByAxisRotateEAngle(float *out, float *in, float x, float y, float z) {
    float v[4] = { x, y, z, 0.0f };
    SetQuaternionByAxisRotateVEAngle(out, in, v);
}
inline void MultiQuaternion(void *p0, void *p1, void *p2)
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
}
extern void MultiQuaternion__pn(int dst, int a, int b) __asm__("MultiQuaternion");

inline void DivQuaternion(int self, int a1, int a2)
{
    int buf[4];
    GetInverseQuaternion(buf, a2);
    MultiQuaternion__pn(self, buf, a1);
}
inline void GetMatrixFromQuaternionRotElem(char *a0, char *a1)
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

inline void GetMatrixFromQuaternionPos(char *a0, char *a1, char *a2)
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

inline void MultiMatrixByQuaternion(void *src)
{
    int local[16];
    void *r1, *r2;
    GetMatrixFromQuaternion__pn(local, src);
    r1 = MatrixDrive_GetMatrix();
    r2 = MatrixDrive_GetMatrix();
    _MulMatrix(r1, r2, local);
}
inline void GetMirrorQuaternion(float *dst, float *src, int mode)
{
    CopyQuaternion(dst, src);
    switch (mode) {
    case 0:
        dst[0] = -dst[0];
        break;
    case 1:
        dst[1] = -dst[1];
        break;
    case 2:
        dst[2] = -dst[2];
        break;
    case 4:
        dst[0] = -dst[0];
        dst[1] = -dst[1];
        break;
    case 3:
        dst[0] = -dst[0];
        dst[2] = -dst[2];
        break;
    case 5:
        dst[1] = -dst[1];
        dst[2] = -dst[2];
        break;
    case 6:
    default:
        dst[0] = -dst[0];
        dst[1] = -dst[1];
        dst[2] = -dst[2];
        break;
    }
}
extern char D_0028FF10[];

inline void RotQuaternionX(void *self, int a1)
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

inline void RotQuaternionY(void *self, int a1)
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

inline void RotQuaternionZ(void *self, int a1)
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
inline void RotQuaternionEAX(void *self, float *in)
{
    float q[4];
    SetQuaternionByAxisRotateEAngle(q, in, 1.0f, 0.0f, 0.0f);
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
inline void RotQuaternionEAZ(void *self, float *in)
{
    float q[4];
    SetQuaternionByAxisRotateEAngle(q, in, 0.0f, 0.0f, 1.0f);
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
inline void GetXUnitVectorOfQuaternion(float *out, float *q)
{
    float w = q[3];
    float x = q[0];
    float y = q[1];
    float z = q[2];
    float v[4] = { -(y * y + z * z), x * y - w * z, x * z + w * y, 0.0f };
    _ScaleVectorXYZ((int)out, (int)v, 2.0f);
    out[0] = out[0] + 1.0f;
}
inline void GetYUnitVectorOfQuaternion(float *out, float *q)
{
    float w = q[3];
    float x = q[0];
    float y = q[1];
    float z = q[2];
    float v[4] = { x * y + w * z, -(x * x + z * z), y * z - w * x, 0.0f };
    _ScaleVectorXYZ((int)out, (int)v, 2.0f);
    out[1] = out[1] + 1.0f;
}
inline void GetZUnitVectorOfQuaternion(float *out, float *q)
{
    float w = q[3];
    float x = q[0];
    float y = q[1];
    float z = q[2];
    float v[4] = { x * z - w * y, y * z + w * x, -(x * x + y * y), 0.0f };
    _ScaleVectorXYZ((int)out, (int)v, 2.0f);
    out[2] = out[2] + 1.0f;
}
inline void SetQuaternionByCosineAxisRotateVWithNoRegularize(void *a0, void *a1, float angle) {
    float first, second;
    first = _Sqrt((angle + 1.0f) * 0.5f);
    second = _Sqrt((1.0f - angle) * 0.5f);
    _ScaleVector(a0, a1, second);
    *(float *)((char *)a0 + 0xC) = first;
}
inline void SetQuaternionByCosineAxisRotateV(void *a0, void *a1, float angle) {
    float buf[4];
    _NormalizeVector(buf, a1);
    SetQuaternionByCosineAxisRotateVWithNoRegularize(a0, buf, angle);
}
extern void _OuterProduct(void *out, void *a, void *b);
extern float _InnerProduct(void *a, void *b);

inline void GetDifferencialQuaternionWithNoRegularize(void *out, void *a, void *b)
{
    float v[4];
    float c;
    _OuterProduct(v, a, b);
    c = _InnerProduct(a, b);
    SetQuaternionByCosineAxisRotateV(out, v, c);
}
inline float GetQuaternionMagnitude(void *a0) {
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

