#include "common.h"

#include "vu0.h"
#include "ico/types.h"

/* tableSin.h prototypes: their order is the inline tail's emission order */
float GetTableSin(short a0);
float GetTableCos(short a0);
void InitTableSin(void);
int GetTableArcSin(float x);
int GetTableArcCos(float x);
int GetTableArcTan2(float f12, float f13);

extern float D_00669A40[];
extern unsigned short D_00679A50[];
extern float D_00638BBC;
extern float D_00638BC0;
extern float D_00638BC4;
extern int D_00639F40;
extern float asinf(float);
extern float sinf(float);

static inline void makeSinTable(void)
{
    int i;
    float m = D_00638BBC;
    float d = D_00638BC0;
    for (i = 0; i < 0x4001; i++) {
        D_00669A40[i] = sinf((float)i * m / d);
    }
}

static inline void makeArcSinTable(void)
{
    int i;
    float k = 0.000244140625f;
    float s = D_00638BC4;
    for (i = 0; i < 0x1001; i++) {
        D_00679A50[i] = (int)(asinf((float)i * k) * s);
    }
}

inline void InitTableSin(void)
{
    if (D_00639F40 != 0) {
        return;
    }
    makeSinTable();
    makeArcSinTable();
    D_00639F40 = 1;
}

/* Shared by GetTableArcSin and GetTableArcCos (listing lines 63-69):
   clamp the cosine/sine argument to [-1, 1] and split off its sign. */
static inline void arcClamp(float *x, int *neg)
{
    if (1.0f < *x) { *x = 1.0f; }
    if (*x < -1.0f) { *x = -1.0f; }
    if (*x < 0.0f) { *neg = 1;
        *x = -*x;
    } else { *neg = 0; }
}

inline int GetTableArcTan2(float f12, float f13)
{
    return f12 < 0.0f ? (short)-GetTableArcCos(f13) : GetTableArcCos(f13);
}

inline int GetTableArcSin(float x)
{
    int neg;
    int hi;

    arcClamp(&x, &neg);
    hi = ((short *)D_00679A50)[(int)(x * 4096.0f)];
    return (short)(neg ? -hi : hi);
}

inline int GetTableArcCos(float x)
{
    int neg;
    int hi;

    arcClamp(&x, &neg);
    hi = (short)(D_00679A50[(int)(x * 4096.0f)] + 0x4000);
    if (neg == 0) {
        return (short)(0x8000 - hi);
    }
    return hi;
}

inline float GetTableSin(short a0)
{
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

inline float GetTableCos(short a0)
{
    short t = a0;
    return GetTableSin(t + 0x4000);
}
