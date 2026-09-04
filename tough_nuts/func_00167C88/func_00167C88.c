#include "common.h"

/* near-gp function-pointer table slots (splat named them jtbl_*); set by
 * fzShowV, called indirectly by ClipWallVector — not a switch jump table. */
extern void (*jtbl_0062A6D0)(int, int);
extern void (*D_0062A6D4)(int, int);

extern void DrawCollisionRay(int *a0);
extern void MakeExitAttributeIndex(int *a0);
extern void func_00167DB0(int *a0);
extern void func_00167E88(int *a0);

int fzShowV(int a0)
{
    *(int *)&jtbl_0062A6D0 = (int)&DrawCollisionRay;
    *(int *)&D_0062A6D4 = (int)&MakeExitAttributeIndex;
    if (a0 != 0) {
        *(int *)&jtbl_0062A6D0 = (int)&func_00167DB0;
        *(int *)&D_0062A6D4 = (int)&func_00167E88;
    }
    return 0;
}

extern void (*D_006323F0)(int a0, int a1);
extern void (*D_006323F4)(int, int);
extern volatile int func_0010F958(int a0, int a1, int a2);

void fzShowM(int *self, int a1)
{
    int new_var;
    int *p;
    func_0010F958((int) self, a1, 0);
    p = (int *) self[0];
    new_var = 0x14 / 4;
    p[0x10 / 4] = (int) (((char *) p) + p[0x10 / 4]);
    p[0x14 / 4] = (int) (((char *) p) + p[new_var]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzMagnitude2f);

extern float sceVu0InnerProduct(int a0, int a1);
extern void sceVu0CopyVector(int *dst, int *src);

int fzMagnitude3f(int a0) {
    float *p = (float *)a0;
    char *q = (char *)(a0 + 0xA0);
    float t0, t1, d;

    sceVu0CopyVector((int *)(a0 + 0x20), (int *)(a0 + 0x10));
    t0 = sceVu0InnerProduct((int)q, a0 + 0x10) + *(float *)(q + 0xC);
    if (t0 >= 0.0f) {
        return 0;
    }
    t1 = sceVu0InnerProduct((int)q, a0) + *(float *)(q + 0xC);
    if (t1 < 0.0f) {
        if (t0 < 0.0f) {
            return 0;
        }
    }
    d = t1 - t0;
    p[8] = (p[4] * t1 - p[0] * t0) / d;
    p[9] = (p[5] * t1 - p[1] * t0) / d;
    p[10] = (p[6] * t1 - p[2] * t0) / d;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzMagnitudefv);

void SetSimplePlane(float *a0, float a1, float a2, float a3, float a4) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a3;
    a0[3] = a4;
}

int GetWallAttribute(void *a0) {
    if (*(int *)((char *)a0 + 0x88) == 0) return 0;
    return *(int *)((char *)a0 + 0x98);
}

int GetFloorAttribute(void *a0) {
    if (*(int *)((char *)a0 + 0x94) == 0) return 0;
    return *(int *)((char *)a0 + 0x98);
}

int CompareAttribute(unsigned int a, unsigned int b)
{
    int i;
    if ((a & b) == 0) return 0;
    for (i = 0; i < 8; i++) {
        unsigned int da = (a >> (i * 4)) & 0xF;
        unsigned int db = (b >> (i * 4)) & 0xF;
        if (da != 0 && db != 0 && da == db) return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", GetWallGlobalInfo);

extern float sceVu0InnerProduct(int a0, int a1);

float GetDistanceFromPlane(int a0, int a1) {
    return sceVu0InnerProduct(a0, a1) + *(float *)(a0 + 0xC);
}

float GetYDistanceFromPlane(float *a0, float *a1) {
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}

float GetYProjectionOfPlane(float *a0, float *a1) {
    return -(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1];
}

extern int D_0062BFF8;
extern int D_0062BFFC;
extern int D_0062C000;
extern int D_0062C004;
extern int D_0062C008;
extern int D_0062C00C;
extern int D_0062C010;
extern int D_0062C014;
extern int D_0062C018;

void ResetCollisionPC(void) {
    D_0062BFF8 = 0;
    D_0062BFFC = 0;
    D_0062C008 = *(volatile int *)0x10000000;
    D_0062C000 = 0;
    D_0062C004 = 0;
    D_0062C00C = 0;
    D_0062C010 = 0;
    D_0062C014 = 0;
    D_0062C018 = 0;
}

extern int D_006A4BC0[];
extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);

int PositionOfExit(int a0, int a1) {
    int v = D_006A4BC0[a1 & 0xF];
    if (v != 0) { MatrixDrive_TurnObjectMatrix(a0, v); return 0; }
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", GetGlobalWallPlane);

/* _clipWDebug */
typedef struct {
    char _0[0x10];
    int unk10;
    int unk14;
    short **unk18;
    short **unk1C;
} FuzioCtx;
extern int D_0062C01C;
extern FuzioCtx *D_0062C020;
extern short D_006A4B40[];
extern int __ClipFloor(void *a0, int a1, int a2, int a3);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWDebug);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipW);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWE);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWEField);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWR);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWField);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWDitchHangWalkStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWWaveForce);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWBoxStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipWAdjustPos);

/* _clipF */
extern int clip_floor_1(void *a0, int a1, int a2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipF);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipFE);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipFIH);

/* _clipFR */
int _clipFR(void *a0, int a1, int a2) {
    int found = 0;
    int i = 0;
    if (D_0062C01C > 0) {
        do {
            FuzioCtx *t5 = D_0062C020;
            short *p = t5->unk1C[D_006A4B40[i]];
            if (p != 0 && *p >= 0) {
                do {
                    int addr = t5->unk14 + (int) *p * 0x70;
                    if (clip_floor_1(a0, addr, 1) != 0) {
                        *(int *)((char *)a0 + 0x94) = addr;
                        found = 1;
                        *(int *)((char *)a0 + 0x8C) = a1;
                        *(int *)((char *)a0 + 0x90) = a2;
                        *(int *)((char *)a0 + 0x88) = 0;
                    }
                    p++;
                    t5 = D_0062C020;
                } while (*p >= 0);
            }
            i++;
        } while (i < D_0062C01C);
    }
    return found;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167E88);

extern int D_0062A69C;
extern void ClipWallBoxStop(void);

void ClipWallRD(void) {
    D_0062A69C = 1;
    ClipWallBoxStop();
    D_0062A69C = 0;
}

extern void sceVu0CopyVector(int *dst, int *src);

int ClipWallVector(int *a0, int *a1) {
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    sceVu0CopyVector(buf, a0);
    sceVu0CopyVector(buf + 4, a1);
    ((int (*)(int *, int))jtbl_0062A6D0)(buf, 1);
    return buf[34];
}

void MapCollisionData(void *a0) {
    int *p = (int *)a0;
    p[4] = (int)a0 + p[4];
    p[5] = (int)a0 + p[5];
}

extern char D_0062C578[];
extern char D_0062C580[];
extern int fptodp(float f);

void func_00168008(float *p)
{
    int i = 3;
    do {
        int s = fptodp(*p);
        debug_StdPrintfDummy(D_0062C578, s);
        p++;
        i--;
    } while (i >= 0);
    debug_StdPrintfDummy(D_0062C580);
}

extern char D_0062C588[];

void func_00168070(int *p) {
    int i = 0;
    do {
        debug_StdPrintfDummy(D_0062C588, i);
        i++;
        func_00168008(p);
        p = (int *)((char *)p + 0x10);
    } while (i < 4);
}

extern float FSqrt(float a0);

float func_001680D0(float a0, float a1) {
    return FSqrt(a0 * a0 + a1 * a1);
}

float func_001680F8(float a0, float a1, float a2) {
    return FSqrt(a0 * a0 + a1 * a1 + a2 * a2);
}

extern float sceVu0InnerProduct(int a0, int a1);

float func_00168128(int a0) {
    return FSqrt(sceVu0InnerProduct(a0, a0));
}

struct vec4_0016A320 { float x, y, z, w; } __attribute__((aligned(8)));

float fzMagnitude2fv(float *a, float *b)
{
    struct vec4_0016A320 v;
    struct vec4_0016A320 diff;
    memset((int *)&diff, 0, 0x10);
    diff.x = b[0] - a[0];
    diff.y = b[1] - a[1];
    diff.z = b[2] - a[2];
    v = diff;
    return FSqrt(sceVu0InnerProduct((int)&v, (int)&v));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", fzMagnitudeByLine);


/* recovered struct shapes */
typedef struct {
    short              f_0;  /* 0x00 */
} S_006A4B40;  /* stride 0x2 */

/* end struct shapes */
