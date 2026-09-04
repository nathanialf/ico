#include "common.h"

extern void sceVu0SubVector();
extern float sceVu0InnerProduct(void *a0, void *a1);

void RotateAccordingToStick_PatternThree(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    sceVu0InnerProduct(buf, buf);
}


void _DistSqGV(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    sceVu0InnerProduct(buf, buf);
}

extern float FSqrt(float a0);

void ClearHandCameraCorrect(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    FSqrt(sceVu0InnerProduct(buf, buf));
}

void _DistxzGV(void *a0, void *a1) {
    char buf[0x10];
    sceVu0SubVector(buf, a0, a1);
    *(int *)(buf + 4) = 0;
    FSqrt(sceVu0InnerProduct(buf, buf));
}

extern void _InterGV(float *a0, float *a1, float *a2, float a3, float a4);

float SetLimitHandCameraCorrect(float *a0, float *a1, float *a2, float a3)
{
    float buf[4];
    float ang;
    sceVu0SubVector(buf, a2, a1);
    ang = FSqrt(buf[0] * buf[0] + buf[1] * buf[1] + buf[2] * buf[2]);
    if (ang < a3) {
        a0[0] = a2[0];
        a0[1] = a2[1];
        a0[2] = a2[2];
    } else {
        _InterGV(a0, a1, a2, a3, ang - a3);
    }
    return ang;
}

extern float atan2f(float a0, float a1);
extern float D_006292B4;

int _RotyGV(a0, a1)
float *a0;
float *a1;
{
    float r1 = atan2f(a0[0], a0[2]);
    float r2 = atan2f(a1[0], a1[2]);
    int v = (int)((r1 - r2) * 180.0f / D_006292B4);
    if (v >= 181)
        v -= 360;
    if (v <= -180)
        v += 360;
    return v;
}

extern int _RotyGV();

int func_00191D90(void) {
    int r = _RotyGV();
    return r < 0 ? -r : r;
}

extern void sceVu0UnitMatrix(float *m);
extern void func_002402E8(float *dst, float *src, float a);
extern void sceVu0ApplyMatrix(float *dst, float *m, float *v);

void func_00191DB8(float *a0, float a1)
{
    float m0[16];
    float m1[16];
    float v[4];
    sceVu0UnitMatrix(m0);
    func_002402E8(m1, m0, a1);
    sceVu0ApplyMatrix(v, m1, a0);
    a0[0] = v[0];
    a0[1] = v[1];
    a0[2] = v[2];
}

extern float atan2f(float a0, float a1);
extern void sceVu0Normalize(void *dst, void *src);

float _GetDirection(float *a0)
{
    float buf[4];
    buf[1] = 0;
    buf[0] = a0[0];
    buf[2] = a0[2];
    sceVu0Normalize(buf, buf);
    return atan2f(buf[0], buf[2]);
}

extern int GetTableArcCos(float a0);

static inline int GetAngleBetweenVectorsXYZ(float *a0, float *a1)
{
    float v0[4];
    float v1[4];
    v0[0] = a0[0];
    v0[1] = a0[1];
    v0[2] = a0[2];
    v1[0] = a1[0];
    v1[1] = a1[1];
    v1[2] = a1[2];
    sceVu0Normalize(v0, v0);
    sceVu0Normalize(v1, v1);
    return GetTableArcCos(sceVu0InnerProduct(v0, v1)) * 180 / 32768;
}

int func_00191E78(float *a0, float *a1)
{
    float buf[4];
    float buf2[4];
    buf[0] = a0[0];
    buf[1] = a0[1];
    buf[2] = a0[2];
    buf2[0] = a1[0];
    buf2[1] = a1[1];
    buf2[2] = a1[2];
    sceVu0Normalize(buf, buf);
    sceVu0Normalize(buf2, buf2);
    return GetTableArcCos(sceVu0InnerProduct(buf, buf2)) * 180 / 32768;
}

extern float D_006292B8;

float _RotGVF(float *a0, float *a1)
{
    return (float)GetAngleBetweenVectorsXYZ(a0, a1) * D_006292B8 / 180.0f;
}

void _OrientXZGV(int a0)
{
    int buf[4];
    sceVu0SubVector(buf);
    buf[1] = 0;
    sceVu0Normalize(a0, buf);
}


void func_00192008(void *a0, void *a1, void *a2) {
    char buf[0x10];
    sceVu0SubVector(buf, a1, a2);
    sceVu0Normalize(a0, buf);
}

int func_00192040(int a0, int a1, int a2, int a3)
{
    int *p;
    int buf[8];
    register int sa2 = a2;
    register int sa3 = a3;
    int r;
    p = &buf[4];
    sceVu0SubVector(p, a0, a1);
    p = &buf[0];
    buf[5] = 0;
    sceVu0Normalize(p, &buf[4]);
    r = _RotyGV(p, sa2);
    return __builtin_abs(r) < sa3;
}

void SwapGV(float *a, float *b)
{
    float tmp[3];
    tmp[0] = a[0];
    tmp[1] = a[1];
    tmp[2] = a[2];
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    b[0] = tmp[0];
    b[1] = tmp[1];
    b[2] = tmp[2];
    __asm__ __volatile__("" : : "r"(tmp) : "memory");
}

extern float GetTableCos(int x);
extern unsigned int D_006327B0_far[] __asm__("D_0062C908");

float GetCorrectDistance(int a0, float a1)
{
    float r = GetTableCos((short)((a0 << 15) / 0xB4));
    if (r == 0.0f)
        return *(float *)D_006327B0_far;
    return a1 / r;
}

int RoundDegGV(int a0)
{
    if (a0 > 0) {
        a0 = a0 % 360;
    } else {
        int a = a0 < 0 ? -a0 : a0;
        a0 = (a / 360 + 1) * 360 + a0;
    }
    return (a0 < 181) ? a0 : a0 - 360;
}
