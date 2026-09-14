#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void ClearHandCameraCorrect(void);
void InitHandCameraCorrect(void);
void SetLimitHandCameraCorrect(float a0, float a1);
extern int D_0028F4C0[];
extern float D_0063C2E0;
extern float D_006E9990[];
extern unsigned char D_0063C2E4;
extern float FSqrt(float a0);
extern float atan2f(float y, float x);
extern void *memset(void *dst, int c, int n);
extern void _ApplyRyGV(float *v, float ang);
extern float _ACTGame_GetParamF(int idx);

void RotateAccordingToStick_PatternThree(float *a, float *b, float x, float y)
{
    float *p = D_006E9990;
    float len = FSqrt(x * x + y * y);
    float ang = atan2f(y, x);
    float v[4] = {len, 0.0f, 0.0f, 0.0f};
    float spd;
    float da;
    float db;
    float t;
    float d;

    _ApplyRyGV(v, -ang);
    x = v[0];
    y = v[2];

    if (len < 0.1f) {
        if (D_0063C2E4 == 0)
            spd = D_0063C2E0 * 0.008726646f * _ACTGame_GetParamF(16);
        else
            spd = D_0063C2E0 * 0.008726646f * _ACTGame_GetParamF(18);
    } else if (D_0063C2E4 == 0)
        spd = D_0063C2E0 * 0.008726646f * _ACTGame_GetParamF(15);
    else
        spd = D_0063C2E0 * 0.008726646f * _ACTGame_GetParamF(17);

    db = x * (p[5] * 3.1415927f / 180.0f) - *b;

    if (y > 0.0f) {
        t = p[2];
    } else {
        t = p[3];
        if (t < 0.0f)
            t = -t;
    }
    da = y * t - *a;

    d = FSqrt(da * da + db * db);

    if (d < spd * 10.0f) {
        da = da / 10.0f;
        db = db / 10.0f;
    } else if (spd < d) {
        da = da * spd / d;
        db = db * spd / d;
    }
    *a += da;
    *b += db;
}

extern void sceVu0SubVector(void *dst, void *a, void *b);
extern float _RotGVF(float *a0, float *a1);

void SetCurrentInfo(void *a0, void *a1)
{
    float *p = D_006E9990;
    float v[4];
    float w[4];
    float ang;
    float t;
    float mx;
    float mn;

    sceVu0SubVector(v, a1, a0);
    w[0] = v[0];
    w[1] = 0.0f;
    w[2] = v[2];
    ang = _RotGVF(w, v);
    p[4] = ang;
    if (v[1] > 0.0f)
        p[4] = -ang;

    if (D_0063C2E4 == 0) {
        t = p[6] * 3.1415927f / 180.0f;
        mx = (t < p[4]) ? p[4] : t;
        p[2] = mx - p[4];
        mn = (p[4] < -t) ? p[4] : -t;
        p[3] = mn - p[4];
    } else {
        mx = p[4] + p[6] * 3.1415927f / 180.0f;
        mx = (mx < -1.4835298f) ? -1.4835298f : ((1.4835298f < mx) ? 1.4835298f : mx);
        p[2] = mx - p[4];
        mn = p[4] - p[6] * 3.1415927f / 180.0f;
        mn = (mn < -1.4835298f) ? -1.4835298f : ((1.4835298f < mn) ? 1.4835298f : mn);
        p[3] = mn - p[4];
    }
}

extern void SetIdentityQuaternion(void *q);
extern void SetQuaternionByAxisRotate(void *q, short ang, float x, float y, float z);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
extern void sceVu0OuterProduct(void *dst, void *a, void *b);
extern void sceVu0Normalize(void *dst, void *src);
extern void sceVu0ScaleVector(void *dst, void *src, float s);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void sceVu0AddVector(void *dst, void *a, void *b);

void HandyCamera_TargetMoveType(void *a0, void *a1)
{
    float *p = D_006E9990;
    float q[4];
    float d[4];
    float m[16];
    float q2[4];
    float v0[4];
    float v1[4];
    float n[4];
    float q3[4];

    sceVu0SubVector(d, a1, a0);

    SetIdentityQuaternion(q);

    SetIdentityQuaternion(q2);
    SetQuaternionByAxisRotate(q2, -(p[1] * 32768.0f / 3.1415927f), 0.0f, 1.0f, 0.0f);
    MultiQuaternion(q, q, q2);

    v0[0] = d[0];
    v0[1] = d[1];
    v0[2] = d[2];
    v1[0] = d[0];
    v1[1] = 0.0f;
    v1[2] = d[2];
    sceVu0OuterProduct(n, v0, v1);
    sceVu0Normalize(n, n);
    if (v0[1] < 0.0f)
        sceVu0ScaleVector(n, n, -1.0f);

    SetIdentityQuaternion(q3);
    SetQuaternionByAxisRotate(q3, -(p[0] * 32768.0f / 3.1415927f), n[0], n[1], n[2]);
    MultiQuaternion(q, q, q3);

    GetMatrixFromQuaternionPos(m, q, a0);

    d[3] = 0.0f;
    sceVu0ApplyMatrix(d, m, d);
    sceVu0AddVector(a1, a0, d);
}

inline void ClearHandCameraCorrect(void)
{
    int a = D_0028F4C0[0];
    int b = D_0028F4C0[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006E9990[0] = 0;
    *(int *)&D_006E9990[1] = 0;
    q = diff / b;
    D_0063C2E0 = 60.0f / (float)q;
}

inline void InitHandCameraCorrect(void)
{
    int a = D_0028F4C0[0];
    int b = D_0028F4C0[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006E9990[0] = 0;
    *(int *)&D_006E9990[1] = 0;
    q = diff / b;
    D_006E9990[5] = 120.0f;
    D_006E9990[6] = 80.0f;
    D_0063C2E0 = 60.0f / (float)q;
}

inline void SetLimitHandCameraCorrect(float a0, float a1)
{
    D_006E9990[5] = a0;
    D_006E9990[6] = a1;
}

extern void SetCurrentInfo(void *a0, void *a1);
extern void RotateAccordingToStick_PatternThree(float *a, float *b, float rot, float y);
extern void HandyCamera_TargetMoveType(void *a0, void *a1);

void HandCameraCorrect(void *a0, void *a1, int a2, float f12, float f13, float f14)
{
    float *p = D_006E9990;

    D_0063C2E0 = f14;
    D_0063C2E4 = a2;

    SetCurrentInfo(a0, a1);

    RotateAccordingToStick_PatternThree(p, p + 1, f12, -f13);

    HandyCamera_TargetMoveType(a0, a1);
}
