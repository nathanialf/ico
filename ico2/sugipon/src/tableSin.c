#include <math.h>

/* tableSin.h is not included here: it declares GetTableArcTan2 as returning
   short, while this definition returns int.  The declarations below repeat
   the header's order, which is load-bearing: gcc 2.9 emits the deferred
   out-of-line copies of plain-inline functions in first-declaration order. */
float GetTableSin(short angle);
float GetTableCos(short angle);
void InitTableSin(void);
short GetTableArcSin(float x);
short GetTableArcCos(float x);
int GetTableArcTan2(float y, float x);

/* the two lookup tables: a quarter-turn of sine at 16385 steps, then the
   arc-sine table at 4097 steps.  The sine table is declared 16388 long; the
   loop below fills 16385 entries. */
static float sinTable[16388]; /* derived name */

static unsigned short arcSinTable[4097]; /* derived name */

/* set once InitTableSin has built the two tables */
static int tableSinReady = 0; /* derived name */

static inline void makeSinTable(void) /* derived name */
{
    int i;
    float m = 1.5707964f;
    float d = 16385.0f;
    for (i = 0; i < 16385; i++) {
        sinTable[i] = sinf((float)i * m / d);
    }
}

static inline void makeArcSinTable(void) /* derived name */
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
    if (tableSinReady != 0) {
        return;
    }
    makeSinTable();
    makeArcSinTable();
    tableSinReady = 1;
}

/* shared by GetTableArcSin and GetTableArcCos: clamp the cosine/sine
   argument to [-1, 1] and split off its sign */
static inline void arcClamp(float *x, int *neg) /* derived name */
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

inline int GetTableArcTan2(float y, float x)
{
    return y < 0.0f ? (short)-GetTableArcCos(x) : GetTableArcCos(x);
}

inline short GetTableArcSin(float x)
{
    int neg;
    int hi;

    arcClamp(&x, &neg);
    hi = ((short *)arcSinTable)[(int)(x * 4096.0f)];
    return (short)(neg ? -hi : hi);
}

inline short GetTableArcCos(float x)
{
    int neg;
    int hi;

    arcClamp(&x, &neg);
    hi = (short)(arcSinTable[(int)(x * 4096.0f)] + 16384);
    if (neg == 0) {
        return (short)(32768 - hi);
    }
    return hi;
}

inline float GetTableSin(short angle)
{
    int idx = __builtin_abs(angle);
    int s;
    float v;
    s = (unsigned int)angle >> 31;
    if (idx >= 16384) {
        idx = 32768 - idx;
    }
    v = sinTable[idx];
    if (s == 0)
        goto done;
    v = -v;
done:
    return v;
}

inline float GetTableCos(short angle)
{
    short t = angle;
    return GetTableSin(t + 16384);
}
