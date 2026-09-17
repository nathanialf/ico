#include "common.h"
#include "sugiCommon.h"
#include "darkVolume.h"
#include "gobj.h"
#include "obj_manager.h"
#include "frameDependSequence.h"
#include "geometryManager.h"
#include "matrixDrive.h"
#include "tableSin.h"

extern int D_004E7470[];
extern float D_0063B7D4;
extern int D_004E7460[];
extern int D_00639EA8;
extern int D_0063B7BC;
extern float D_0063B7C0;
extern int D_0063B7C4;
extern int D_0063B7C8;
extern float D_0063B7CC;

/* The colour draw and drawHT take by value: four bytes in one register, which
   is why every call site masks the parameter home to 32 bits. */
typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} DVColor;

void draw(void *v, int n, DVColor col, int neg);
void drawHT(void *v, int n, DVColor col, int neg);

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/darkVolume", draw);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/darkVolume", drawHT);

/* .bss, owned by darkVolume.o (0x13A0, the run and MAIN.MAP's own size,
   tiled exactly by these six), in the ROM's run order: one 136-float hatch row,
   the eight rows the volume is built from, and the four cosine and sine tables
   the ring is stepped with. */
/* */
static float hatchRow[136];

static float hatchRows[8 * 136];

static float cosB[8];

static float cosA[8];

static float sinB[8];

static float sinA[8];

extern int D_0028FF00[];
extern char *matrixptr;
void _SetCurrentMatrix(void *m);
/* kept local: this TU's uses of _ApplyMatrix do not fit the prototype in Matrix.h */
extern void _ApplyMatrix(void *dst, void *m, void *src);
/* kept local: this TU's uses of _InterVectorXYZ do not fit the prototype in Matrix.h */
extern void _InterVectorXYZ(void *dst, void *a, void *b, float t);

/* listing lines 62-65: load the VU0 screen clamp limits vmaxx and vminix read
   out of vf13 and vf12 in the projection block at line 80. */
static __inline__ void setScreenClamp(float hi, float lo)
{
    __asm__ __volatile__("mfc1 $8, %0\n\t"
                         "qmtc2.ni $8, $vf12\n\t"
                         "mfc1 $8, %1\n\t"
                         "qmtc2.ni $8, $vf13"
                         :
                         : "f"(hi), "f"(lo)
                         : "$8");
}

/* listing line 117: dst = base + v * s over xyz, keeping base's w. */
static __inline__ void addScaledVectorXYZ(void *dst, const void *base, const void *v, float s)
{
    __asm__ __volatile__("lqc2 $vf14, 0x0(%1)\n\t"
                         "lqc2 $vf15, 0x0(%2)\n\t"
                         "mfc1 $8, %3\n\t"
                         "qmtc2.ni $8, $vf16\n\t"
                         "vmulx.xyz $vf15, $vf15, $vf16x\n\t"
                         "vadd.xyz $vf14, $vf14, $vf15\n\t"
                         "sqc2 $vf14, 0x0(%0)"
                         :
                         : "r"(dst), "r"(base), "r"(v), "f"(s)
                         : "$8");
}

/* listing lines 242-293: project the view-space sphere around pos, splitting each
   of the 8 rings at the near plane. The first arm's counter is not read in its
   body, so loop.c reverses that loop and the ROM counts it down with bgez; the
   second and third read n and stay ascending. */
void renderViewCoordZSphere(void *pos, DVColor col, int neg, float r)
{
    float v[4];
    int i;
    int n;
    float *p;
    float *q;

    _ApplyMatrix(v, matrixptr + 0x80, pos);
    if (v[2] + r * cosA[0] < 1.0f) {
        return;
    }
    _SetCurrentMatrix(matrixptr + 0xC0);
    setScreenClamp(4095.0f, 0.0f);
    for (i = 0; i < 8; i++) {
        float z0 = v[2] + r * cosB[i];
        float z1 = v[2] + r * cosA[i];

        p = &hatchRows[i * 136];
        q = hatchRow;
        if (1.0f < z0) {
            for (n = 0; n < 34; n++, p += 4, q += 4) {
                addScaledVectorXYZ(q, v, p, r);
            }
            drawHT(hatchRow, 34, col, neg);
        } else {
            float t = (z1 - 1.0f) / (z1 - z0);

            for (n = 0; n < 34; n++, p += 4, q += 4) {
                addScaledVectorXYZ(q, v, p, r);
                if (n & 1) {
                    _InterVectorXYZ(q, q, q - 4, t);
                }
            }
            drawHT(hatchRow, 34, col, neg);
            q = hatchRow;
            for (n = 0; n < 34; n++, q += 4) {
                if (n & 1) {
                    CopyVector(q - 4, q);
                    CopyVector(q, v);
                    hatchRow[n * 4 + 2] = 1.0f;
                }
            }
            draw(hatchRow, 34, col, neg);
            return;
        }
    }
}

inline void ExecGameOverEffect(void) {}

INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/darkVolume", sonic);
INCLUDE_ASM("asm/nonmatchings/ico2/sugipon/src/darkVolume", darkVolume);

/* listing lines 526-533: arm the game-over dark volume, shared by
   StartGameOverEffect and StartQueenAttackEffect */
static inline void setGameOverEffect(int a0, float t)
{
    D_0063B7BC = 1;
    D_0063B7C0 = 0;
    D_0063B7C4 = 1;
    D_0063B7C8 = 0;
    CopyVector((int)D_004E7460, a0);
    D_0063B7CC = t;
}

inline void StartGameOverEffect(int a0, float t)
{
    if (D_00639EA8 != 0) {
        ExecuteSEPackage(D_00639EA8, 0x7A);
        ExecuteSEPackage(D_00639EA8, 0x7B);
        ExecuteSEPackage(D_00639EA8, 0x7C);
        ExecuteSEPackage(D_00639EA8, 0x7D);
        ExecuteSEPackage(D_00639EA8, 0x7E);
    }
    setGameOverEffect(a0, t);
}

inline void StartQueenAttackEffect(int a0, float t)
{
    setGameOverEffect(a0, t);
    D_0063B7C8 = 1;
    D_0063B7C4 = 0;
}

inline void ResetGameOverEffect(void)
{
    D_0063B7BC = 0;
    D_0063B7C4 = 0;
}

void SetDarkVolumeEffect(int a0, float a1)
{
    D_0063B7D4 = a1;
    CopyVector(D_004E7470, (void *)a0);
}

extern float D_0063B7D0;
extern int D_0028F4D4[];
extern int D_00639EA4;

/* listing lines 566-568: the per-object hit test, inlined at all three sites */
static inline void sendGameOverMail(void *gobj, float r2)
{
    float pos[4];

    GetRootPosition(pos, gobj);
    if (distance_squared(pos, D_004E7460) < r2) {
        iosOmSendMail(gobj, 0x22, gobj);
    }
}

void DispGameOverEffect(void)
{
    void *g;

    if (D_0063B7BC != 0) {
        sonic(D_004E7460, D_0063B7C0);
        darkVolume(D_004E7460, D_0063B7C0, 1.0f, 30.0f);
        if (D_0063B7C4 != 0) {
            float r2 = D_0063B7C0 * D_0063B7C0;

            g = (void *)D_00639EA4;
            if (g != 0) {
                sendGameOverMail(g, r2);
            }
            for (g = isysGObjSearchFromObjKindID_begin(4); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
                sendGameOverMail(g, r2);
            }
            for (g = isysGObjSearchFromObjKindID_begin(62); g != 0;
                 g = isysGObjSearchFromObjKindID_next(g)) {
                sendGameOverMail(g, r2);
            }
        }
        if (D_0063B7C0 < 50000.0f && D_0028F4D4[0] == 0) {
            D_0063B7C0 = D_0063B7C0 + D_0063B7CC;
        }
    } else {
        if (D_0063B7D4 < 0.001f && D_0063B7D0 < 1.0f) {
            return;
        }
        darkVolume(D_004E7470, D_0063B7D0, 0.96f, 0.0f);
        if (D_0028F4D4[0] != 0) {
            return;
        }
        D_0063B7D0 = D_0063B7D0 + (D_0063B7D4 - D_0063B7D0) * 0.3f;
        D_0063B7D4 = 0.0f;
    }
}

void GetGameOverEffectCenterPosition(int a0)
{
    CopyVector(a0, D_004E7460);
}

/* listing lines 647-676: build the 8 by 17 sphere vertex table renderViewCoordZSphere
   walks 34 vectors at a time, then reset the effect state. Each entry is the pair
   of vectors for ring i and ring i+1, so the row holds 17 pairs of 8 floats and the
   ring stride is 136 floats. Angles are the 16 bit binary turn the sin and cos
   tables take, 0x1000 per step. */
void InitGameOverEffect(void)
{
    int i;
    int j;
    float ca;
    float sa;
    float cb;
    float sb;

    for (i = 0; i < 8; i++) {
        short a = i * 0x1000;
        short b = (i + 1) * 0x1000;

        ca = GetTableCos(a);
        sa = GetTableSin(a);
        cb = GetTableCos(b);
        sb = GetTableSin(b);
        cosA[i] = ca;
        cosB[i] = cb;
        sinA[i] = sa;
        sinB[i] = sb;
        for (j = 0; j < 17; j++) {
            float *p = &hatchRows[i * 136 + j * 8];
            float *q = p + 4;
            short k = j * 0x1000;
            float s = GetTableSin(k);
            float c = GetTableCos(k);

            p[0] = sa * s;
            p[1] = sa * c;
            p[2] = ca;
            p[3] = 1.0f;
            q[0] = sb * s;
            q[1] = sb * c;
            q[2] = cb;
            q[3] = 1.0f;
        }
    }
    ResetGameOverEffect();
    D_0063B7D0 = 0;
    D_0063B7D4 = 0;
    CopyVector(D_004E7470, ZeroPoint);
}

inline int InitDarkVolumeGeo(char *a0)
{
    **(int **)(*(char **)(a0 + 0x15C) + 0xC) = 0;
    return 0;
}

void SetupDarkVolume(void *a0, float a1, float a2)
{
    darkVolume(a0, a1, 1.0f, a2);
}

void DarkVolumeGeo(char *a0)
{
    float *p;

    *(int *)(*(int *)(a0 + 0x15C) + 0x74) = 0;
    p = *(float **)(*(int *)(a0 + 0x15C) + 0xC);
    if (1e-05f < *p) {
        SetupDarkVolume((char *)p + 0x30, *p * 50.0f, 10.0f);
    }
}

inline void DarkVolumeDL(void) {}
