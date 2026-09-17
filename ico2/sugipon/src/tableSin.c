#include "common.h"
#include <math.h>

/* tableSin.h is not included here: it declares GetTableArcTan2 as returning
   short, which is what every caller's bytes need, while this definition returns
   int, which is what this TU's own bytes need; the 2001 source can only have
   carried both if the definition never saw that prototype. The declarations
   below repeat the header's order, which is load-bearing: gcc 2.9 emits the
   deferred out-of-line copies of plain-inline functions in first-declaration
   order. */
float GetTableSin(short a0);
float GetTableCos(short a0);
void InitTableSin(void);
int GetTableArcSin(float x);
int GetTableArcCos(float x);
int GetTableArcTan2(float f12, float f13);

/* .bss, owned by tableSin.o and reached only from this file (MAIN.MAP names no
   symbol in the run; its tableSin.o .bss size 0x12012 is exactly these two
   tables), in the ROM's run order: a quarter-turn of sine at 16385 steps, then
   the arc-sine table at 4097 steps.  The ROM puts the arc-sine table 0x10010
   bytes on and MAIN.MAP sizes tableSin.o's .bss at 0x12012, which is that
   0x10010 plus the arc-sine table's own 0x2002; gcc's own padding after a
   0x4001-entry table only reaches 0x10008, so the sine table's DECLARED bound
   is 0x4004 even though the loop below fills 0x4001 entries.  The bound is
   inferred from those two sizes, not read off any ROM byte. */
static float sinTable[16388];

static unsigned short arcSinTable[4097];

extern int D_00639F40;

static inline void makeSinTable(void)
{
    int i;
    float m = 1.5707964f;
    float d = 16385.0f;
    for (i = 0; i < 16385; i++) {
        sinTable[i] = sinf((float)i * m / d);
    }
}

static inline void makeArcSinTable(void)
{
    int i;
    float k = 0.000244140625f;
    float s = 10430.378f;
    for (i = 0; i < 4097; i++) {
        arcSinTable[i] = (int)(asinf((float)i * k) * s);
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
    if (1.0f < *x) {
        *x = 1.0f;
    }
    if (*x < -1.0f) {
        *x = -1.0f;
    }
    if (*x < 0.0f) {
        *neg = 1;
        *x = -*x;
    } else {
        *neg = 0;
    }
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
    hi = ((short *)arcSinTable)[(int)(x * 4096.0f)];
    return (short)(neg ? -hi : hi);
}

inline int GetTableArcCos(float x)
{
    int neg;
    int hi;

    arcClamp(&x, &neg);
    hi = (short)(arcSinTable[(int)(x * 4096.0f)] + 0x4000);
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
    s = (unsigned int)a0 >> 31;
    if (idx >= 0x4000) {
        idx = 0x8000 - idx;
    }
    v = sinTable[idx];
    if (s == 0)
        goto done;
    v = -v;
done:
    return v;
}

inline float GetTableCos(short a0)
{
    short t = a0;
    return GetTableSin(t + 0x4000);
}
