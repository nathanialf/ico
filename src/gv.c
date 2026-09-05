#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/gv", _InterGV);
INCLUDE_ASM("asm/nonmatchings/src/gv", GetMatrixDirectionToZ);
extern int _RotyGV(float *a0, float *a1);
extern void _ApplyRyGV(float *a0, float a1);
extern float D_006391F0;
extern float D_006391F4;

int _InterRotGV(float *dst, float *cur, float *tgt, int step)
{
    float buf[4];
    int hit = 0;
    int d = _RotyGV(tgt, cur);

    if (__builtin_abs(d) < step) {
        hit = 1;
        buf[0] = cur[0]; buf[1] = cur[1]; buf[2] = cur[2];
    } else if (d > 0) {
        buf[0] = tgt[0]; buf[1] = tgt[1]; buf[2] = tgt[2];
        _ApplyRyGV(buf, -step * D_006391F0 / 180.0f);
    } else {
        buf[0] = tgt[0]; buf[1] = tgt[1]; buf[2] = tgt[2];
        _ApplyRyGV(buf, step * D_006391F4 / 180.0f);
    }
    dst[0] = buf[0]; dst[1] = buf[1]; dst[2] = buf[2];
    return hit;
}
extern float sceVu0InnerProduct(void *a0, void *a1);
extern void sceVu0SubVector();

void _DistxzSqGV(void *a0, void *a1) {
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

void _DistGV(void *a0, void *a1) {
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

float _MoveGV(float *a0, float *a1, float *a2, float a3)
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
extern float D_006391F8;

int _RotyGV(float *a0, float *a1)
{
    float a = atan2f(a0[0], a0[2]);
    float b = atan2f(a1[0], a1[2]);
    int d = (int)((a - b) * 180.0f / D_006391F8);

    if (d > 180) d -= 360;
    if (d <= -180) d += 360;
    return d;
}
int _AbsRotyGV(void *a0, void *a1)
{
    int d = _RotyGV(a0, a1);

    return (d < 0) ? -d : d;
}
extern void sceVu0RotMatrixY(float *dst, float *src, float a);
extern void sceVu0ApplyMatrix(float *dst, float *m, float *v);
extern void sceVu0UnitMatrix(float *m);

void _ApplyRyGV(float *a0, float a1)
{
    float m0[16];
    float m1[16];
    float v[4];
    sceVu0UnitMatrix(m0);
    sceVu0RotMatrixY(m1, m0, a1);
    sceVu0ApplyMatrix(v, m1, a0);
    a0[0] = v[0];
    a0[1] = v[1];
    a0[2] = v[2];
}
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

inline int _RotGV(float *a0, float *a1)
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
extern float D_006391FC;

inline float _RotGVF(float *a0, float *a1)
{
    return _RotGV(a0, a1) * D_006391FC / 180.0f;
}

inline void _OrientXZGV(int a0)
{
    int buf[4];
    sceVu0SubVector(buf);
    buf[1] = 0;
    sceVu0Normalize((void *)a0, buf);
}
inline void _OrientGV(int a0)
{
    int buf[4];
    sceVu0SubVector(buf);
    sceVu0Normalize((void *)a0, buf);
}

inline int _FrontGV(int a0, int a1, int a2, int a3)
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
    r = _RotyGV((float *)p, (float *)sa2);
    return __builtin_abs(r) < sa3;
}
inline void SwapGV(float *a, float *b)
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
}
extern unsigned int D_006327B0_far[] __asm__("D_0063AC18");
extern float GetTableCos(int x);

inline float GetCorrectDistance(int a0, float a1)
{
    float r = GetTableCos((short)((a0 << 15) / 0xB4));
    if (r == 0.0f)
        return *(float *)D_006327B0_far;
    return a1 / r;
}
inline int RoundDegGV(int a0)
{
    if (a0 > 0) {
        a0 = a0 % 360;
    } else {
        int a = a0 < 0 ? -a0 : a0;
        a0 = (a / 360 + 1) * 360 + a0;
    }
    return (a0 < 181) ? a0 : a0 - 360;
}
inline int AlignDegGV(int a0)
{
    if (a0 < -135) a0 = 180;
    else if (a0 < -45) a0 = -90;
    else if (a0 < 45) a0 = 0;
    else {
        int v = a0;
        a0 = 180;
        if (v <= 134) a0 = 90;
    }
    return a0;
}
