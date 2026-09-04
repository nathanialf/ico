#include "common.h"

#include "vu0.h"
#include "ico/types.h"

extern float D_00669A40[];

float GetTableSin(short a0) {
    int idx = __builtin_abs(a0);
    int s;
    float v;
    s = (unsigned int) a0 >> 0x1F;
    if (idx >= 0x4000) {
        idx = 0x8000 - idx;
    }
    v = D_00669A40[idx];
    if (s == 0) goto done;
    v = -v;
done:
    return v;
}
float GetTableCos(short a0) {
    int t = (short)(a0 + 0x4000);
    int idx = __builtin_abs(t);
    int s;
    float v;
    s = (unsigned int) t >> 0x1F;
    if (idx >= 0x4000) {
        idx = 0x8000 - idx;
    }
    v = D_00669A40[idx];
    if (s == 0) goto done;
    v = -v;
done:
    return v;
}
extern float D_00638BBC;
extern float D_00638BC0;
extern float D_00638BC4;
extern int D_00639F40;
extern unsigned short D_00679A50[];
extern float asinf(float);
extern float sinf(float);

void InitTableSin(void) {
    int i;
    float m, d, s, k;
    if (D_00639F40 != 0) {
        return;
    }
    m = D_00638BBC;
    d = D_00638BC0;
    for (i = 0; i < 0x4001; i++) {
        D_00669A40[i] = sinf((float)i * m / d);
    }
    k = 0.000244140625f;
    s = D_00638BC4;
    for (i = 0; i < 0x1001; i++) {
        D_00679A50[i] = (int)(asinf((float)i * k) * s);
    }
    D_00639F40 = 1;
}
int GetTableArcSin(float x) {
    int neg;
    int hi;

    if (1.0f < x) {
        x = 1.0f;
    }
    if (x < -1.0f) {
        x = -1.0f;
    }
    if (x < 0.0f) {
        neg = 1;
        x = -x;
    } else {
        neg = 0;
    }
    hi = ((short *)D_00679A50)[(int)(x * 4096.0f)];
    return (short)(neg ? -hi : hi);
}
INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcCos);
extern short GetTableArcCos(float c);

extern int GetTableArcCos__pn(float x) __asm__("GetTableArcCos");

int GetTableArcTan2(float f12, float f13)
{
    if (f12 < 0.0f) {
        int r = GetTableArcCos__pn(f13);
        return (short)(-r);
    }
    return GetTableArcCos__pn(f13);
}
