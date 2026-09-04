#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", RotQuaternionEAZ);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", GetXUnitVectorOfQuaternion);

extern void _ScaleVectorXYZ(void *a0, void *a1, float a2);

void GetYUnitVectorOfQuaternion(void *a0, float *a1) {
    float buf[4];
    float x = a1[0], y = a1[1], z = a1[2], w = a1[3];
    buf[0] = x * y + w * z;
    buf[2] = y * z - w * x;
    buf[1] = 0.0f - (x * x + z * z);
    *(int *)&buf[3] = 0;
    _ScaleVectorXYZ(a0, buf, 2.0f);
    *((float *)a0 + 1) += 1.0f;
}


INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", GetZUnitVectorOfQuaternion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/DisplayP2O", GetDifferencialQuaternionWithNoRegularize);

extern int _Sqrt(float arg);

int GetQuaternionMagnitude(void *a0) {
    register float arg __asm__("$f12");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0($4)\n"
        "lqc2 $vf15, 0x0($4)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni $2, $vf15\n"
        "mtc1 $2, $f12\n"
        ".set reorder\n"
        : "=f"(arg) :: "$2");
    return _Sqrt(arg);
}

extern void _ScaleVector(void *a0, void *a1, float a2);

void SetQuaternionByCosineAxisRotateVWithNoRegularize(void *a0, void *a1, float angle) {
    float first, second;
    first = ((float (*)(float))_Sqrt)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))_Sqrt)((1.0f - angle) * 0.5f);
    _ScaleVector(a0, a1, second);
    *(float *)((char *)a0 + 0xC) = first;
}

extern void _NormalizeVector(void *buf);
extern void _ScaleVector(void *a0, void *buf, float a2);

void SetQuaternionByCosineAxisRotateV(void *a0, float angle) {
    float buf[4];
    float first, second;
    _NormalizeVector(buf);
    first = ((float (*)(float))_Sqrt)((angle + 1.0f) * 0.5f);
    second = ((float (*)(float))_Sqrt)((1.0f - angle) * 0.5f);
    _ScaleVector(a0, buf, second);
    *(float *)((char *)a0 + 0xC) = first;
}

extern void _NormalizeVector(void *buf);

void SetQuaternionByAxisRotateVEAngle(void *a0, float *a1, void *a2) {
    float buf[4];
    float first, second;
    first = ((float (*)(float))_Sqrt)((a1[0] + 1.0f) * 0.5f);
    second = ((float (*)(float))_Sqrt)((1.0f - a1[0]) * 0.5f);
    ((void (*)(void *, void *))_NormalizeVector)(buf, a2);
    *(float *)((char *)a0 + 0xC) = first;
    *(float *)((char *)a0 + 0x0) = buf[0] * second;
    *(float *)((char *)a0 + 0x4) = buf[1] * second;
    *(float *)((char *)a0 + 0x8) = buf[2] * second;
}

float GetQuaternionCosRadian(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf14, 0x0($4)\n"
        "lqc2 $vf15, 0x0($5)\n"
        "vmul.xyzw $vf15, $vf14, $vf15\n"
        "vaddy.x $vf15, $vf15, $vf15y\n"
        "vaddz.x $vf15, $vf15, $vf15z\n"
        "vaddw.x $vf15, $vf15, $vf15w\n"
        "qmfc2.ni $2, $vf15\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

/* m2c scaffold from asm/aug6/nonmatchings/seki/src/DisplayP2O/p2o_SetDefaultEnviroment.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern float D_0065A9C0[];

float p2o_SetDefaultEnviroment(short a0) {
    int idx = __builtin_abs(a0);
    int s;
    float v;
    s = (unsigned int) a0 >> 0x1F;
    if (idx >= 0x4000) {
        idx = 0x8000 - idx;
    }
    v = D_0065A9C0[idx];
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
    v = D_0065A9C0[idx];
    if (s == 0) goto done;
    v = -v;
done:
    return v;
}


extern int D_00629E80;
extern float D_00628CBC;
extern float D_00628CC0;
extern float D_00628CC4;
extern unsigned short D_0066A9D0[];
extern float sinf(float);
extern float func_0025A868(float);

void InitTableSin(void) {
    int i;
    float m, d, s, k;
    if (D_00629E80 != 0) {
        return;
    }
    m = D_00628CBC;
    d = D_00628CC0;
    for (i = 0; i < 0x4001; i++) {
        D_0065A9C0[i] = sinf((float)i * m / d);
    }
    k = 0.000244140625f;
    s = D_00628CC4;
    for (i = 0; i < 0x1001; i++) {
        D_0066A9D0[i] = (int)(func_0025A868((float)i * k) * s);
    }
    D_00629E80 = 1;
}


extern unsigned short D_0066A9D0[];

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
    hi = ((short *)D_0066A9D0)[(int)(x * 4096.0f)];
    return (short)(neg ? -hi : hi);
}

int GetTableArcCos(float x) {
    int neg;
    int h;
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
    h = (short)(D_0066A9D0[(int)(x * 4096.0f)] + 0x4000);
    if (neg == 0) {
        return (short)(-0x8000 - h);
    }
    return h;
}

extern int GetTableArcCos(float x);

int GetTableArcTan2(float f12, float f13)
{
    if (f12 < 0.0f) {
        int r = GetTableArcCos(f13);
        return (short)(-r);
    }
    return GetTableArcCos(f13);
}

extern void func_0011C308(void *a0);

void func_0010EFE0(void *a0) {
    void *p = *(void **)((char *)a0 + 0x810);
    *(void **)((char *)p + 0x28) = a0;
    func_0011C308(a0);
}

extern void func_00123AA8(void *a0);

void func_0010EFF0(int a0) {
    func_00123AA8(*(void **)(a0 + 0x15C));
}

extern int D_0062AFA8;
extern int D_00629E84;
extern char D_0054E240[];
extern void debug_PrintFontWindow(int a0, void *a1, int a2);

void p2o_HideDispVU1(int a0) {
    D_00629E84 = a0;
    if (D_0062AFA8) {
        debug_PrintFontWindow(0xCCCCCC00, D_0054E240, a0);
    }
}


/* recovered struct shapes */
typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_0066A9D0;  /* stride 0x2 */

/* end struct shapes */
