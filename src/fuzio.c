#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzShowV);
INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzShowM);
extern float FSqrt(float a0);

float fzMagnitude2f(float x, float z)
{
    return FSqrt(x * x + z * z);
}
float fzMagnitude3f(float x, float y, float z)
{
    return FSqrt(x * x + y * y + z * z);
}
extern float sceVu0InnerProduct(int a0, int a1);

float fzMagnitudefv(int v)
{
    return FSqrt(sceVu0InnerProduct(v, v));
}
INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzMagnitude2fv);
INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzMagnitudeByLine);
extern float sceVu0InnerProduct__pn(void *a, void *b) __asm__("sceVu0InnerProduct");

float fzMagnitudeByLineSeg(float *p0, float *p1, float *p2) {
    float d1[4];
    float d2[4];
    float r1, r2;
    float a, b, c, mdret;
    int ci;

    d1[0] = p1[0] - p0[0];
    d1[2] = p1[2] - p0[2];
    d1[1] = 0.0f;
    d2[0] = p2[0] - p0[0];
    d2[2] = p2[2] - p0[2];
    d2[1] = 0.0f;
    r1 = sceVu0InnerProduct__pn(d1, d2);
    if (r1 < 0.0f) {
        return FSqrt(sceVu0InnerProduct__pn(d2, d2));
    }
    d2[0] = p2[0] - p1[0];
    d2[1] = 0.0f;
    d2[2] = p2[2] - p1[2];
    r2 = sceVu0InnerProduct__pn(d1, d2);
    if (-r2 < 0.0f) {
        return FSqrt(sceVu0InnerProduct__pn(d2, d2));
    }
    a = -(p1[0] - p0[0]);
    b = p1[2] - p0[2];
    c = p0[2] * p1[0] - p0[0] * p1[2];
    mdret = FSqrt(b * b + a * a);
    ci = (int)(b * p2[0] + a * p2[2] + c);
    ci = __builtin_abs(ci);
    return (float)ci / mdret;
}
