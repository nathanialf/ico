#include "common.h"
#include "sugiCommon.h"

extern void ExecuteSEPackage(int a0, int a1);

void torchOnOfWeaponSE(int a0)
{
    ExecuteSEPackage(a0, 0x42);
}

extern void StopSEPackage(int a0);

void torchOffOfWeaponSE(int a0)
{
    StopSEPackage(a0);
    ExecuteSEPackage(a0, 0x43);
}

extern void ExecuteSEPackage(int a0, int a1);

void weaponHitReactionSE(int a0, int a1, int a2, int a3)
{
    ExecuteSEPackage(a0, 0x44);
}

extern void ExecuteSEPackage(int a0, int a1);

void weaponFumbleSE(int a0)
{
    ExecuteSEPackage(a0, 0x5C);
}

void weaponStickSE(int a0)
{
    ExecuteSEPackage(a0, 0x5D);
}

extern int D_0028F4C0[];
extern void CopyVector(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern void GetRootPosition(void *out, void *obj);

/* INTERIM NAME, chosen and not recovered: the PAL listing carries this
   file-static helper at weapon.c:262-265 and inlines it here, so it has no
   census row and no name of its own in any map. */
static inline void releaseWeaponHolder(char *w)
{
    if (*(char **)(w + 0x8) != 0) {
        *(int *)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(w + 0xC) = -1;
}

void ReleaseWeaponWithFumbleTargetPos(char *g, void *pos, void *quat, void *rot, float t)
{
    char *p = *(char **)(g + 0x15C);
    char *w = *(char **)(p + 0x830);

    releaseWeaponHolder(w);
    *(int *)(w + 0x4) = 2;
    *(int *)(w + 0x8) = 0;
    if (rot != 0) {
        CopyQuaternion(p + 0x150, rot);
    }
    *(int *)(w + 0x60) = (int)((float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]) * t);
    *(int *)(w + 0x64) = 0;
    GetRootPosition(w + 0x70, g);
    CopyVector(w + 0x80, pos);
    CopyQuaternion(w + 0x90, quat);
    *(float *)(w + 0x68) = (*(float *)(w + 0x84) - *(float *)(w + 0x74)) / t - t * 490.0f;
    weaponFumbleSE((int)g);
}

/* ReleaseWeaponWithFumbleSequential is still asm: its one .lit4 word, the
   first of this TU's pool run. */
ASM_LIT4_SLOT(D_006396D8, 182.04445f);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/weapon", ReleaseWeaponWithFumbleSequential);

typedef struct {
    int kind;  /* 0x00 */
    float f04; /* 0x04 */
    int w[7];  /* 0x08 */
} WeaponDef;

extern WeaponDef D_00318EB8[];
extern float D_004ED2D0[];
extern float D_004ED2E0[];
extern char D_0028FEF0[];
extern void GetMatrixFromQuaternion(void *dst, void *q);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern void _AddVectorXYZ(void *dst, void *a, void *b);
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void CopyVector(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern void UpdateRootMatrix(char *g);

/* INTERIM NAMES, chosen and not recovered: the PAL listing carries these two
   file-static helpers at weapon.c:362-373 and 375-385 and inlines them here,
   so neither has a census row or a name in any map. */
static inline void addWeaponPathOffset(char *p, char *rp, float d)
{
    float m[16];
    float v[4];
    char *q = p + 0xD0;

    GetMatrixFromQuaternion(m, q);
    D_004ED2D0[2] = d;
    _ApplyMatrix(v, m, D_004ED2D0);
    _AddVectorXYZ(rp, rp, v);
}

static inline void subWeaponPathOffset(char *p, char *rp, float d)
{
    float m[16];
    float v[4];
    char *q = p + 0xD0;

    GetMatrixFromQuaternion(m, q);
    D_004ED2E0[2] = -d;
    _ApplyMatrix(v, m, D_004ED2E0);
    _AddVectorXYZ(rp, rp, v);
}

int calcDynamicPathGeometry(char *g)
{
    char *p = *(char **)(g + 0x15C);
    char *w = *(char **)(p + 0x830);
    float d = D_00318EB8[*(int *)w].f04;
    char *rp = p + 0xA0;
    float a;
    float b;
    float t;

    addWeaponPathOffset(p, rp, d);
    a = (float)*(int *)(w + 0x64);
    b = (float)*(int *)(w + 0x60);
    t = a / (float)((60 - D_0028F4C0[0] * 10) / D_0028F4C0[1]);
    _InterVectorXYZ(rp, w + 128, w + 112, a / b);
    *(float *)(rp + 4) = *(float *)(w + 0x74) + *(float *)(w + 0x68) * t + t * 490.0f * t;
    MultiQuaternion(p + 0xD0, p + 0xD0, p + 0x150);
    subWeaponPathOffset(p, rp, d);
    *(int *)(w + 0x64) = *(int *)(w + 0x64) + 1;
    if (*(int *)(w + 0x64) >= *(int *)(w + 0x60)) {
        *(int *)(w + 0x4) = 0;
        CopyVector(rp, w + 128);
        CopyVector(p + 0x130, D_0028FEF0);
        CopyQuaternion(p + 0xD0, w + 144);
        UpdateRootMatrix(g);
        weaponStickSE((int)g);
        return 1;
    }
    UpdateRootMatrix(g);
    return 0;
}

/* calcDynamicGeometry is still asm: its three .lit4 words, in its own order. */
ASM_LIT4_SLOT(D_006396DC, 0.7f);
ASM_LIT4_SLOT(D_006396E0, 0.7f);
ASM_LIT4_SLOT(D_006396E4, 0.9f);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/weapon", calcDynamicGeometry);

extern void CopyMatrix(void *dst, void *src);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void CopyVector(void *dst, void *src);
extern void CopyQuaternion(void *dst, void *src);
extern void RotQuaternionY(void *q, int ang);
extern void sceVu0SubVector(void *out, void *a, void *b);
extern void DivQuaternion(void *out, void *a, void *b);
extern void UpdateRootMatrix(char *g);
extern void calcDynamicGeometry(char *g);

/* INTERIM: a stand-in for SetWeaponOffsetMode, which the PAL listing inlines
   here (its rows at weapon.c:197 appear inside getGeometry) while keeping its
   own out-of-line copy at its ROM slot further down this file. */
static inline void setWeaponOffsetMode(char *g, int v)
{
    *(int *)(*(char **)(*(char **)(g + 0x15C) + 0x830) + 0xC0) = v;
}

void getGeometry(char *g)
{
    float pos[4];
    float quat[4];
    char *p = *(char **)(g + 0x15C);
    char *w = *(char **)(p + 0x830);
    char *rp = p + 0xA0;

    if (*(char **)(w + 0x8) != 0) {
        char *d = *(char **)(*(char **)(w + 0x8) + 0x15C);
        int n = *(int *)(w + 0xC);

        CopyMatrix(MatrixDrive_GetMatrix(), *(char **)(d + 0xC) + n * 0x40);
        MatrixDrive_TransMatrix(7.0f, -3.0f, 0.0f);
        CopyVector(pos, (char *)MatrixDrive_GetMatrix() + 0x30);
        CopyQuaternion(quat, *(char **)(d + 0x10) + n * 0x10);
        if (((int *)(*(char **)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x8C) + n * 0x40))[1] ==
            22) {
            RotQuaternionY(quat, -32768);
        }
        sceVu0SubVector(p + 0x130, pos, rp);
        {
            char *rq = p + 0xD0;

            DivQuaternion(p + 0x150, quat, rq);
            CopyVector(rp, pos);
            CopyQuaternion(rq, quat);
        }
        UpdateRootMatrix(g);
        setWeaponOffsetMode(g, 0);
    } else {
        switch (*(int *)(w + 0x4)) {
        default:
            break;
        case 1:
            calcDynamicGeometry(g);
            break;
        case 2:
            calcDynamicPathGeometry(g);
            break;
        }
    }
}

void WeaponCurPos(char *a0, void *a1, void *a2, void *a3)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    CopyVector(a1, p + 0x20);
    CopyVector(a2, p + 0x30);
    CopyVector(a3, p + 0x40);
}

extern void CheckEnemyHit(void *a0, void *a1, void *a2, void *a3);

void WeaponHitEffect(char *a0, void *a1)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    CheckEnemyHit(a1, p + 0x20, p + 0x30, p + 0x40);
}

extern void weaponHitReactionSE();

void ExecWeaponHitReaction(int a0, int a1, int a2, int a3)
{
    weaponHitReactionSE(a0, a1, a2, a3);
}

extern char D_004ED300[];
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PushMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern void MatrixDrive_TransMatrixV(char *v);
extern void GetMatrixFromQuaternionPos(void *m, void *q, void *pos);
extern void GetInverseQuaternion(void *dst, void *src);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void SubVectorXYZ(void *dst, void *a, void *b);

void checkHit(char *g)
{
    float pos[4];
    float quat[4];
    float v0[4];
    float v1[4];
    char *p = *(char **)(g + 0x15C);
    char *w = *(char **)(p + 0x830);

    if (*(char **)(w + 0x8) == 0) {
        return;
    }
    MatrixDrive_PushMatrix();
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), p + 0xD0, p + 0xA0);
    MatrixDrive_TransMatrixV(D_004ED300);
    CopyVector(v0, (char *)MatrixDrive_GetMatrix() + 0x30);
    GetInverseQuaternion(quat, p + 0x150);
    MultiQuaternion(quat, p + 0xD0, quat);
    SubVectorXYZ(pos, p + 0xA0, p + 0x130);
    GetMatrixFromQuaternionPos(MatrixDrive_GetMatrix(), quat, pos);
    MatrixDrive_TransMatrixV(D_004ED300);
    CopyVector(v1, (char *)MatrixDrive_GetMatrix() + 0x30);
    MatrixDrive_PopMatrix();
    CopyVector(w + 0x20, v0);
    CopyVector(w + 0x30, v1);
    CopyVector(w + 0x40, p + 0xA0);
}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/weapon", initializeQueenzSword);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/weapon", InitWeaponGeo);

extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_TransMatrix(float x, float y, float z);
extern void MatrixDrive_ScaleMatrix(float x, float y, float z);
extern void p2o_DispVU1DObj(void *d);
extern void p2o_DispVU1(char *g);

void dispLaserSword(char *g, float t)
{
    char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);

    p2o_DispVU1(g);
    if (1.0f < t) {
        CopyMatrix(MatrixDrive_GetMatrix(), *(void **)(*(char **)(g + 0x15C) + 0xC));
        MatrixDrive_TransMatrix(0.0f, 0.0f, 7.5f);
        MatrixDrive_ScaleMatrix(1.0f, 1.0f, t / 100.0f);
        CopyMatrix(*(void **)(*(char **)(w + 0xB4) + 0xC), MatrixDrive_GetMatrix());
        p2o_DispVU1DObj(*(void **)(w + 0xB4));
        MatrixDrive_TransMatrix(*(float *)(*(char **)(w + 0xB0) + 0x0) * 0.1f,
                                *(float *)(*(char **)(w + 0xB0) + 0x4) * 0.1f, 0.0f);
        CopyMatrix(*(void **)(*(char **)(w + 0xB8) + 0xC), MatrixDrive_GetMatrix());
        p2o_DispVU1DObj(*(void **)(w + 0xB8));
    }
}

extern char D_004ED320[];
extern char D_004ED330[];
extern char D_004ED340[];
extern float GetTableCos(short a);
extern float GetTableSin(short a);
extern void DrawLineG(void *p0, void *c0, void *p1, void *c1, int f);

typedef struct {
    float f[4];
} __attribute__((aligned(16))) NetVec;

void dispInsectNet(char *g)
{
    int i;

    CopyMatrix(MatrixDrive_GetMatrix(), *(void **)(*(char **)(g + 0x15C) + 0xC));
    gif_StartPacketPri(11);
    gif_SetZTest(1);
    gif_SetZWrite(1);
    gif_SetAlpha(1, 7, 128);
    DrawLineG(D_004ED330, D_004ED320, D_004ED340, D_004ED320, 0);
    for (i = 0; i <= 0xFFFF; i += 4096) {
        NetVec p = {
            {GetTableCos((short)i) * 30.0f, 0.0f, GetTableSin((short)i) * 30.0f + 130.0f, 1.0f}};
        NetVec q = {{GetTableCos((short)(i + 4096)) * 30.0f, 0.0f,
                     GetTableSin((short)(i + 4096)) * 30.0f + 130.0f, 1.0f}};

        DrawLineG(&p, D_004ED320, &q, D_004ED320, 0);
    }
    gif_EndPacket();
}

extern char *matrixptr;
extern void _SetCurrentMatrix(void *p);
extern void _UnitMatrix(void *m);
extern void gif_StartPacketPri(int pri);
extern void gif_EndPacket(void);
extern void gif_SetAlpha(int a0, int a1, int a2);
extern void gif_SetZTest(int a0);
extern void gif_SetZWrite(int a0);

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} GifColor;

extern void gif_DrawStripF(void *p, GifColor c, int n, int f);

void dispBlur(char *g)
{
    char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);

    if (D_00318EB8[*(int *)w].w[3] != -1) {
        char *e = (char *)D_00318EB8 + *(int *)w * 36;
        void *s = *(void **)(w + 0x58);
        GifColor c = {e[0x18], e[0x19], e[0x1A], e[0x1B]};

        _SetCurrentMatrix(matrixptr + 0x100);
        gif_StartPacketPri(2);
        switch (*(int *)(e + 0x14)) {
        case 0:
        default:
            gif_SetAlpha(1, 7, 128);
            break;
        case 1:
            gif_SetAlpha(1, 5, 128);
            break;
        case 2:
            gif_SetAlpha(1, 6, 128);
            break;
        }
        gif_SetZTest(1);
        gif_SetZWrite(1);
        gif_DrawStripF(s, c, 22, 1);
        gif_EndPacket();
    }
    if (*(int *)w == 8) {
        if (12.0f < *(float *)(w + 0xA8)) {
            _UnitMatrix(MatrixDrive_GetMatrix());
            gif_StartPacketPri(2);
            gif_SetAlpha(1, 5, 128);
        }
        gif_EndPacket();
    }
}

extern void GetInverseQuaternion(void *dst, void *src);
extern void MultiQuaternion(void *dst, void *a, void *b);
extern void SubVectorXYZ(void *dst, void *a, void *b);
extern void GetMatrixFromQuaternion(void *dst, void *q);
extern void GetMatrixFromQuaternionPos(void *dst, void *q, void *pos);
extern void _ApplyMatrix(void *dst, void *m, void *src);
extern void _OuterProduct(void *dst, void *a, void *b);
extern void _NormalizeVector(void *dst, void *src);
extern float _InnerProduct(void *a, void *b);
extern void _ScaleVectorXYZ(void *dst, void *src, float s);
extern void _ScaleVector(void *dst, void *src, float s);
extern void _InterVector(void *dst, void *a, void *b, float t);
extern void _SubVector(void *dst, void *a, void *b);
extern float acosf(float x);
extern void SetQuaternionByAxisRotateVWithNoRegularize(void *q, short ang, void *axis);
extern void sceVu0InterVector(void *dst, void *a, void *b, float t);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *src);
extern void sceVu0CopyVector(void *dst, void *src);
extern void CopyVector(void *dst, void *src);
extern int SetParticleEffect(int id, void *pos, void *a2);
extern char *GetParticleEffectData(int h);
extern void ExecParticleEffect(int h);
extern float D_0028FF30[];
extern int D_002907E0[];

void calcBlur(char *g, float t)
{
    float q1[4];   /* 0x00 */
    float q2[4];   /* 0x10 */
    float d[4];    /* 0x20 */
    float p[4];    /* 0x30 */
    float m[4][4]; /* 0x40 */
    float n[4];    /* 0x80 */
    float a[4];    /* 0x90 */
    float b[4];    /* 0xA0 */
    float sub[4];  /* 0xB0 */
    float tmp[4];  /* 0xC0 */
    char *e = *(char **)(g + 0x15C);
    char *w = *(char **)(e + 0x830);
    char *base;
    char *vtx;
    char *q;
    char *dst1;
    char *dst2;
    char *pd;
    int h;
    int i;
    int j;
    int k;
    float ang;
    float r;

    GetInverseQuaternion(q1, e + 0x150);
    MultiQuaternion(q1, e + 0xD0, q1);
    SubVectorXYZ(d, e + 0xA0, e + 0x130);
    if (D_00318EB8[*(int *)w].w[3] == -1) {
        return;
    }
    base = *(char **)(w + 0x58);
    GetMatrixFromQuaternion(m, q1);
    _ApplyMatrix(a, m, D_0028FF30);
    GetMatrixFromQuaternion(m, e + 0xD0);
    _ApplyMatrix(b, m, D_0028FF30);
    _OuterProduct(n, b, a);
    _NormalizeVector(n, n);
    ang = acosf(_InnerProduct(a, b)) * 10430.378f;
    _ScaleVectorXYZ(a, a, t);
    a[3] = 1.0f;
    for (i = 0; i < 11; i++) {
        float rr = (float)i / 10.0f;

        SetQuaternionByAxisRotateVWithNoRegularize(q2, (short)(ang * (float)i / 10.0f), n);
        sceVu0InterVector(p, e + 0xA0, d, rr);
        GetMatrixFromQuaternionPos(m, q2, p);
        CopyVector(base + i * 32, (char *)m + 0x30);
        sceVu0ApplyMatrix(base + (i * 32 + 0x10), m, a);
    }
    if (*(int *)w >= 10) {
        return;
    }
    if (*(int *)w < 8) {
        return;
    }
    if (t > 12.0f) {
        h = SetParticleEffect(50, e + 0xA0, D_002907E0);
        if (h != -1) {
            pd = GetParticleEffectData(h);
            vtx = *(char **)(pd + 0x24);
            q = *(char **)(pd + 0x28);
            dst1 = *(char **)(q + 0x190);
            dst2 = *(char **)(q + 0x194);
            ExecParticleEffect(h);
            for (j = 0; j < *(int *)(pd + 0x30); j++) {
                k = j * 10 / *(int *)(pd + 0x30);
                r = random_unit();
                _InterVector(vtx + 0x10, base + (k + 1) * 32, base + ((k + 1) * 32 + 16), r);
                _InterVector(tmp, base + k * 32, base + (k * 32 + 16), r);
                _SubVector(sub, vtx + 0x10, tmp);
                _ScaleVector(
                    vtx + 0x20, sub,
                    *(float *)(*(char **)(pd + 0x20) + 0x10) *
                        (*(float *)(*(char **)(pd + 0x20) + 0x14) * random_signed() + 1.0f));
                sceVu0CopyVector(dst1, vtx + 0x10);
                dst1 += 0x20;
                sceVu0CopyVector(dst2, vtx + 0x10);
                dst2 += 0x20;
                vtx += 0x70;
            }
        }
    }
}

extern void calcBlur(char *g, float t);
extern void *D_00639EA4;
extern int ACTGame_FLAG_TETSUNAGI_VISUAL(void);
extern void ExecuteDirectSE(char *g, int id);
extern void stage_SetLoopFlag(int key, int a1);
extern float stage_PlayBgAnimation(int key, float t, void *a, void *b);
extern int D_002907E0[];
extern int D_0028F4D4[];
extern void *MatrixDrive_GetMatrix(void);
extern void GetRootMatrix(void *m, char *g);
extern void CopyMatrix(void *dst, void *src);
extern void *memset(void *p, int c, int n);
extern void sceVu0ApplyMatrix(void *out, void *m, void *in);
extern float _Sqrt(float x);
extern float atan2f(float y, float x);

typedef struct {
    char pad00[0x190]; /* 0x000 */
    unsigned int f190; /* 0x190 */
} WeaponEnemyPara;     /* 0x194 */

extern WeaponEnemyPara D_0055FE58[];

/* The MatrixDrive matrix, viewed as the union of float and int arrays this
   codebase uses for VU0 data.  The union member reference is what puts the
   0x34 store in alias set 0, which is why the following gobj-extension load
   stays behind it instead of hoisting above the store (measured: 6 -> 3). */
typedef union {
    float f[4][4];
    int i[4][4];
} WeaponMatrix;

void WeaponGeo(char *g)
{
    char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);
    int kind;
    int i;
    int n;
    float t;
    float a;

    getGeometry(g);
    checkHit(g);

    kind = *(int *)w;
    *(int *)(w + 0xA4) = 0;
    if (*(int *)w >= 10 || kind < 8) {
        if (*(int *)(w + 0x4) == 1 ||
            (*(char **)(w + 0x8) != 0 &&
             ((((WeaponEnemyPara *)(*(int *)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x4A0) *
                                        0x194 +
                                    (char *)D_0055FE58))
                   ->f190 >>
               4) &
              1))) {
            calcBlur(g, *(float *)((char *)D_00318EB8 + kind * 36));
            *(int *)(w + 0xA4) = 1;
        }
    } else {
        *(float *)((char *)D_00318EB8 + kind * 36) = 40.0f;
        for (i = 0; i < 2; i++) {
            ((float *)*(char **)(w + 0xB0))[i] = random_signed_b();
        }
        if (*(char **)(w + 0x8) != 0) {
            if (*(char **)(w + 0x8) == D_00639EA4 && ACTGame_FLAG_TETSUNAGI_VISUAL()) {
                *(float *)((char *)D_00318EB8 + *(int *)w * 36) = 270.0f;
            }
            if (*(float *)(w + 0xAC) >= 30.0f) {
                *(float *)(w + 0xA8) +=
                    (*(float *)((char *)D_00318EB8 + *(int *)w * 36) - *(float *)(w + 0xA8)) * 0.4f;
            } else {
                *(float *)(w + 0xAC) = *(float *)(w + 0xAC) + 1.0f;
                if (*(float *)(w + 0xAC) == 29.0f) {
                    ExecuteDirectSE(g, 0x101E7);
                }
            }
        } else {
            *(float *)(w + 0xA8) += (0.0f - *(float *)(w + 0xA8)) * 0.1f;
            *(float *)(w + 0xAC) = 0.0f;
        }
        calcBlur(g, *(float *)(w + 0xA8));
        *(int *)(w + 0xA4) = 1;
        t = *(float *)(w + 0xA8);
        stage_SetLoopFlag(473, 1);
        if (t > 1.0f) {
            n = (int)stage_PlayBgAnimation(473, (float)*(int *)(w + 0xBC),
                                           *(char **)(*(char **)(g + 0x15C) + 0xC) + 0x30,
                                           D_002907E0);
            if (D_0028F4D4[0] == 0) {
                *(int *)(w + 0xBC) = n;
            }
        } else {
            stage_PlayBgAnimation(473, 0.0f, *(char **)(*(char **)(g + 0x15C) + 0xC) + 0x30,
                                  D_002907E0);
            *(int *)(w + 0xBC) = 0;
        }
        stage_SetLoopFlag(473, 0);
    }

    GetRootMatrix(MatrixDrive_GetMatrix(), g);
    CopyVector(w + 0xD0, (char *)MatrixDrive_GetMatrix() + 0x30);
    if (*(int *)(w + 0xC0) != 0) {
        float v[4] = {0.0f, 0.0f, 1.0f, 0.0f};

        v[3] = 0.0f;
        sceVu0ApplyMatrix(v, MatrixDrive_GetMatrix(), v);
        a = -atan2f(v[1], _Sqrt(1.0f - v[1] * v[1]));
        ((WeaponMatrix *)MatrixDrive_GetMatrix())->f[3][1] -=
            GetTableSin((short)(a * 10430.378f)) * 70.0f;
        CopyMatrix(*(char **)(*(char **)(g + 0x15C) + 0xC), MatrixDrive_GetMatrix());
    }
}

extern void p2o_SetDefaultEnviroment(void);
extern void p2o_DispVU1(char *g);
extern void dispInsectNet(char *g);
extern void dispLaserSword(char *g, float f);
extern void dispBlur(char *g);

void WeaponDL(char *g)
{
    char *w = *(char **)(*(char **)(g + 0x15C) + 0x830);

    switch (*(int *)w) {
    default:
        p2o_SetDefaultEnviroment();
        p2o_DispVU1(g);
        break;
    case 7:
        dispInsectNet(g);
        break;
    case 8:
    case 9:
        dispLaserSword(g, *(float *)(w + 0xA8));
        break;
    case 0:
        break;
    }
    if (*(int *)(w + 0xA4) != 0) {
        dispBlur(g);
    }
}

extern int GetSkeltonFocusNode(char *obj, int kind);

void PickupWeapon(char *a0, char *a1, int a2)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);

    *(char **)(p + 0x8) = a1;
    *(int *)(p + 0xC) = GetSkeltonFocusNode(a1, a2);
    *(int *)(*(int *)(a1 + 0x15C) + 0x630) = (int)a0;
}

extern int stage_no;
extern void GetRootPosition(void *out, void *obj);
extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);

char *CheckSwapableWeapon(char *a0, float dist)
{
    char *found = 0;
    float best = dist * dist;
    char *g = (char *)isysGObjSearchFromObjKindID_begin(14);
    float pos[4];
    float d;

    GetRootPosition(pos, a0);

    for (; g != 0; g = (char *)isysGObjSearchFromObjKindID_next(g)) {
        char *w;
        char *wp;

        if (g == a0)
            continue;

        w = *(char **)(*(char **)(g + 0x15C) + 0x830);
        if (*(int *)w == 0)
            continue;

        if (*(int *)(w + 0x8) != 0)
            continue;

        if (*(int *)(g + 0x16C) == 0)
            continue;

        wp = w + 0xD0;
        if (stage_no == 4 && *(int *)(g + 0x8) != 0x80)
            continue;

        d = distance_squared(pos, wp);
        if (d < best) {
            found = g;
            best = d;
        }
    }
    return found;
}

void ReleaseWeapon(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(char **)(p + 0x8)) {
        *(int *)(*(char **)(*(char **)(p + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(p + 0x8) = 0;
    *(int *)(p + 0xC) = -1;
    *(int *)(p + 0x4) = 0;
}

int CheckWeaponKind(char *a0)
{
    return *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830));
}

extern void LightTorchOn(int torch);

void LightTorchOnOfWeapon(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int i;

    if (*(int *)(p + 0x50)) {
        torchOnOfWeaponSE(**(int **)(p + 0x54));
    }
    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOn(*(int *)(*(char **)(p + 0x54) + i * 4));
    }
}

void LightTorchOnOfWeaponWithNoSE(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int i;

    if (*(int *)(p + 0x50)) {
        torchOnOfWeaponSE(**(int **)(p + 0x54));
    }
    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOn(*(int *)(*(char **)(p + 0x54) + i * 4));
    }
}

extern void LightTorchOff(char *torch);

void LightTorchOffOfWeapon(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    int i;

    for (i = 0; i < *(int *)(p + 0x50); i++) {
        LightTorchOff(*(char **)(*(char **)(p + 0x54) + i * 4));
    }
}

int GetTorchGObjOfWeapon(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    if (*(int *)(p + 0x50)) {
        return **(int **)(p + 0x54);
    }
    return 0;
}

extern void CopyQuaternion(void *dst, void *src);

/* INTERIM (see the iosThreadCreate note in ios/thread.c): the listing inlines
 * ReleaseWeapon's lines 262-265 here, so ReleaseWeapon is a public `inline` of
 * the deferred tail; its body is expanded in place until the tail's asm
 * members are C, when it collapses into a call.  LightTorchOnOfWeapon and
 * LightTorchOnOfWeaponWithNoSE are one source body (both symbols carry
 * weapon.c:173-177); their shared form is decided at layout. */
void ReleaseWeaponWithFumble(char *a0, void *a1, void *a2)
{
    char *e = *(char **)(a0 + 0x15C);
    char *w = *(char **)(e + 0x830);
    char *f = e + 0xA0;

    if (*(char **)(w + 0x8)) {
        *(int *)(*(char **)(*(char **)(w + 0x8) + 0x15C) + 0x630) = 0;
    }
    *(int *)(w + 0x8) = 0;
    *(int *)(w + 0xC) = -1;
    *(int *)(w + 0x4) = 1;

    if (a2) {
        CopyQuaternion(e + 0x150, a2);
    }
    CopyVector(e + 0x130, a1);
    *(int *)(f + 0x9C) = 0;
}

int InitWeaponFumbleSequence(char *a0)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xA0) = 0;
    return 1;
}

float GetWeaponWeight(char *a0)
{
    return (float)D_00318EB8[*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830))].w[1];
}

extern void *isysGObjSearchFromObjKindID_begin(int kind);
extern void *isysGObjSearchFromObjKindID_next(void *gobj);
extern void SetTorchChainReactionFlag(char *gobj, int flag);

void SetWeaponTorchChainReactionFlagAll(int a0)
{
    char *g;
    char *w;
    int i;

    for (g = isysGObjSearchFromObjKindID_begin(14); g; g = isysGObjSearchFromObjKindID_next(g)) {
        w = *(char **)(*(char **)(g + 0x15C) + 0x830);
        if (*(int *)w == 1) {
            for (i = 0; i < *(int *)(w + 0x50); i++) {
                SetTorchChainReactionFlag(*(char **)(*(char **)(w + 0x54) + i * 4), a0);
            }
        }
    }
}

typedef struct {
    double d[28];
} DemoQueenSwordWork;

extern int D_0063A438;
extern const char D_006214E0[];
extern DemoQueenSwordWork D_004ED1F0;
extern void *iosMallocDebug(int heap, int size, const char *file, int line);
extern void initializeQueenzSword(char *gobj, int index, void *a2);

void *InitDemoQueensSword(char *a0, void *a1)
{
    DemoQueenSwordWork *w;
    int i;

    w = (DemoQueenSwordWork *)iosMallocDebug(D_0063A438, 0xE0, D_006214E0, 802);
    *(DemoQueenSwordWork **)(*(char **)(a0 + 0x15C) + 0x830) = w;
    *w = D_004ED1F0;
    for (i = 0; i < *(int *)(*(char **)(a0 + 0x15C) + 0x8); i++) {
        initializeQueenzSword(a0, i, a1);
    }
    return w;
}

void ExecDemoQueensSword(char *a0)
{
    char *e = *(char **)(a0 + 0x15C);
    char *p = *(char **)(e + 0x830);
    *(int *)(*(char **)(p + 0x5C) + 0x16C) = *(int *)(e + 0x74);
}

void SetWeaponOffsetMode(char *a0, int a1)
{
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0xC0) = a1;
}
