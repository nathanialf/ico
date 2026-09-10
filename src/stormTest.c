#include "common.h"
#include "sugiCommon.h"

/* header prototypes (order fixes the inline tail) */
extern char D_00620FA0[];
extern int D_0063A438;
/* prototypes: their order is the inline tail's emission order */
int *InitStormTestGeo(int a0, int *a1);
extern int iosMallocDebug(int t, int sz, const char *file, int line);
extern char D_0028FEF0[];
extern char D_004ED0F0[];
extern void *memset(void *s, int c, int n);
extern void gif_StartPacketPri(int pri);
extern void gif_SetZTest(int on);
extern void gif_SetZWrite(int on);
extern void gif_SetAlpha(int a, int b, int c);
extern void gif_EndPacket(void);
extern void Draw2DLineSeg_Start(void);
extern void Draw2DLineSeg_Loop(void *a, void *b, void *c);
extern float GetDistanceFromPlane(void *plane, void *pos);
extern float sceVu0InnerProduct(void *a, void *b);
extern float FSqrt(float x);
extern void sceVu0ClampVector(void *dst, void *src, float lo, float hi);
extern void sceVu0FTOI0Vector(void *dst, void *src);
extern void CopyIVector(void *dst, void *src);
extern char *matrixptr;
extern const float D_006396B0;
extern const float D_006396B4;
extern const float D_006396B8;
extern const float D_006396BC;
extern float D_006396C0;
extern void sceVu0ScaleVectorXYZ(void *dst, void *src, float s);
extern void *MatrixDrive_GetMatrix(void);
extern void MatrixDrive_SetTransposeMatrix(void *dst, void *src);
extern void MatrixDrive_TransMatrix(float f12, float f13, float f14);
extern void CopyVector(void *dst, void *src);
extern void sceVu0SubVector(void *dst, void *a, void *b);
extern void sceVu0ApplyMatrix(void *dst, void *m, void *v);
extern void sceVu0ScaleVector(void *dst, void *src, float s);

typedef struct StormPackage {
    /* 0x00 */ int mode;
    /* 0x04 */ int num;
    /* 0x08 */ float (*pos)[4];
    /* 0x0C */ float (*vel)[4];
    /* 0x10 */ int (*disp)[4];
    /* 0x14 */ float *rate;
    /* 0x18 */ int unk18;
} StormPackage;

/* stormTest.c lines 28-31 */
static __inline__ void StormStoreI4(void *dst, void *src)
{
    VU0_LSV_R(lqc2, 4, 0x0, src);
    VU0_V2OP(vftoi4.xyzw, 5, 4);
    VU0_LSV_R(sqc2, 5, 0x0, dst);
}

/* stormTest.c lines 38-44 */
static __inline__ void StormPerspective(void *dst, void *src)
{
    float t[4];

    sceVu0ApplyMatrix(t, matrixptr + 0xC0, src);
    sceVu0ScaleVector(t, t, 1.0f / t[3]);
    StormStoreI4(dst, t);
}

/* stormTest.c lines 48-55 */
static __inline__ float StormScreen(void *dst, void *src)
{
    float t[4];
    float w;

    sceVu0ApplyMatrix(t, matrixptr + 0x100, src);
    w = 1.0f / t[3];
    sceVu0ScaleVector(t, t, w);
    StormStoreI4(dst, t);
    return w;
}

/* stormTest.c lines 100-107 */
static __inline__ void StormProject(void *dst, void *src)
{
    float t[4];

    sceVu0ApplyMatrix(t, matrixptr + 0x80, src);
    StormPerspective(dst, t);
}

extern StormPackage *InitStormPackage(int mode, int num, int flag);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", InitStormPackage);

void ClipStormByVolume(StormPackage *pkg)
{
    int i;
    int clipped;

    for (i = 0; i < pkg->num; i++) {
        float *p = pkg->pos[i];

        clipped = 0;
        if (0.0f < p[1]) {
            p[1] -= 400.0f;
            clipped = 1;
        }
        if (p[1] < -400.0f) {
            p[1] += 400.0f;
            clipped = 1;
        }
        if (p[0] > D_006396C0) {
            p[0] -= 2000.0f;
            clipped = 1;
        }
        if (p[0] < -500.0f) {
            p[0] += 2000.0f;
            clipped = 1;
        }
        if (1000.0f < p[2]) {
            p[2] -= 2000.0f;
            clipped = 1;
        }
        if (p[2] < -1000.0f) {
            p[2] += 2000.0f;
            clipped = 1;
        }
        if (clipped) {
            StormProject(pkg->disp[i], p);
        }
    }
}

void ClipStormByCamera(StormPackage *pkg)
{
    float cam[4];
    float d[4];
    int i;
    int j;
    int clipped;

    MatrixDrive_SetTransposeMatrix(MatrixDrive_GetMatrix(), matrixptr + 0x80);
    MatrixDrive_TransMatrix(0.0f, 0.0f, 500.0f);
    CopyVector(cam, (char *)MatrixDrive_GetMatrix() + 0x30);
    for (i = 0; i < pkg->num; i++) {
        float *p = pkg->pos[i];

        clipped = 0;
        sceVu0SubVector(d, p, cam);
        for (j = 0; j < 3; j++) {
            if (500.0f < d[j]) {
                float t = d[j] - 500.0f;
                clipped = 1;
                p[j] = (cam[j] - 500.0f) + t;
            } else if (d[j] < -500.0f) {
                p[j] = (cam[j] + 500.0f) + (d[j] + 500.0f);
                clipped = 1;
            }
        }
        if (clipped) {
            StormProject(pkg->disp[i], p);
        }
    }
}

extern void UpdateStormPackage(StormPackage *pkg);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", UpdateStormPackage);

void DispStormPackage(StormPackage *pkg, void *color)
{
    int sv[4];
    int iv[4];
    float col[4] = {0.0f, 0.0f, 0.0f, 128.0f};
    float plane[4];
    int i;

    MatrixDrive_SetTransposeMatrix(MatrixDrive_GetMatrix(), matrixptr + 0x80);
    sceVu0ApplyMatrix(plane, MatrixDrive_GetMatrix(), D_004ED0F0);
    plane[3] = -sceVu0InnerProduct(plane, (char *)MatrixDrive_GetMatrix() + 0x30);
    gif_StartPacketPri(11);
    gif_SetZTest(1);
    gif_SetZWrite(0);
    gif_SetAlpha(1, 5, 128);
    Draw2DLineSeg_Start();
    for (i = 0; i < pkg->num; i++) {
        int *d = pkg->disp[i];

        if (GetDistanceFromPlane(plane, pkg->pos[i]) < 0.0f) {
            d[2] = -1;
        } else {
            float w = StormScreen(sv, pkg->pos[i]);

            if (d[2] >= 0 && (sv[0] >= 26368 && sv[0] <= 39168) &&
                (sv[1] >= 29568 && sv[1] <= 35968) && (d[0] >= 26368 && d[0] <= 39168) &&
                (d[1] >= 29568 && d[1] <= 35968)) {
                float dx;
                float dy;

                d[0] += 0x20;
                dx = (float)(sv[0] - d[0]);
                dy = (float)(sv[1] - d[1]);
                sceVu0ScaleVectorXYZ(col, color,
                                     80.0f / (FSqrt(dx * dx + dy * dy) + 30.0f) * w * 300.0f);
                sceVu0ClampVector(col, col, 0.0f, 255.0f);
                sceVu0FTOI0Vector(iv, col);
                Draw2DLineSeg_Loop(sv, d, iv);
            }
            CopyIVector(d, sv);
        }
    }
    gif_SetZWrite(1);
    gif_EndPacket();
}

inline int *InitStormTestGeo(int a0, int *a1)
{
    int *obj = (int *)iosMallocDebug(D_0063A438, 0x30, D_00620FA0, 0x11B);
    register int v = *(int *)((char *)a1 + 0x30);
    register int flag = 1;
    *obj = v;
    if (!(0.0f < *(float *)a1))
        flag = 0;
    *(int *)((char *)obj + 0x20) = (int)InitStormPackage(1, v, flag);
    *(float *)((char *)obj + 0x10) = *(float *)((char *)a1 + 0x20);
    *(float *)((char *)obj + 0x14) = *(float *)((char *)a1 + 0x24);
    *(float *)((char *)obj + 0x18) = *(float *)((char *)a1 + 0x28);
    *(float *)((char *)obj + 0x1C) = 128.0f;
    return obj;
}

void StormTestGeo(char *a0)
{
    UpdateStormPackage(*(StormPackage **)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20));
}

void StormTestDL(char *a0)
{
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    DispStormPackage(*(StormPackage **)(p + 0x20), p + 0x10);
}
