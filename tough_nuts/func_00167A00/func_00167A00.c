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

extern void MatrixDrive_TurnObjectMatrix(int a0, int a1);
extern void debug_StdPrintfDummy(void *msg, ...);
extern float GetTableCos(short a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *buf);
extern float p2o_SetDefaultEnviroment(short a0);
extern char D_00553658[];
extern char D_00553688[];

void fzMagnitudefv(void *a0, void *a1, int *a2)
{
    float buf[4];
    int *var_19;
    void *obj = (void *)a2[0];

    if (a1 == 0) {
        buf[1] = 0.0f;
        buf[2] = 1.0f;
        var_19 = 0;
        buf[0] = 0.0f;
        debug_StdPrintfDummy(D_00553658);
    } else {
        var_19 = (int *)1;
        buf[0] = -p2o_SetDefaultEnviroment((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[1] = 0.0f;
        buf[2] = GetTableCos((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[3] = 1.0f;
    }
    if (var_19 == 0) {
        MatrixDrive_TurnObjectMatrix((int)a0, (int)buf);
        *var_19 = 0;
        return;
    }
    *(int *)&buf[3] = 0;
    {
        int *temp_3 = (int *)*(int *)((char *)obj + 0x15C);
        if (temp_3 != 0 && *(int *)((char *)temp_3 + 0xC) != 0) {
            if (*(int *)((char *)temp_3 + 0x78) != 0) {
                int *p5 = (int *)a2[0];
                int idx = a2[1];
                int *o3 = (int *)*(int *)((char *)p5 + 0x15C);
                sceVu0ApplyMatrix(a0, (void *)(*(int *)((char *)o3 + 0xC) + (idx << 6)), buf);
                return;
            }
            MatrixDrive_TurnObjectMatrix((int)a0, (int)buf);
            return;
        }
        debug_StdPrintfDummy(D_00553688);
    }
}


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
    char _0[0x48];
    int unk48;
    char _4C[0x4];
} FzEntry;
typedef struct {
    char _0[0x10];
    FzEntry *unk10;
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


typedef struct {
    char pad74[0x74];
    int unk74;
    int unk78;
    int unk7C;
    char pad80[8];
    int unk88;
    int unk8C;
    int unk90;
    int unk94;
} St167A00;

int _clipFE(St167A00 *a0, int a1, int a2) {
    int i;
    int found = 0;

    for (i = 0; i < D_0062C01C; i++) {
        short *s1 = D_0062C020->unk1C[D_006A4B40[i]];
        unsigned short var_3;
        if (s1 == 0) continue;
        if (*s1 < 0) continue;
        var_3 = *s1;
        do {
            int s0 = D_0062C020->unk14 + (short) var_3 * 0x70;
            if (a1 == a0->unk74 && a2 == a0->unk78 && s0 == a0->unk7C) {
                /* skip */
            } else {
                if (clip_floor_1(a0, s0, 0)) {
                    a0->unk94 = s0;
                    found = 1;
                    a0->unk8C = a1;
                    a0->unk90 = a2;
                    a0->unk88 = 0;
                }
            }
            s1++;
            var_3 = *s1;
        } while (*(volatile short *) s1 >= 0);
    }
    return found;
}


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipFIH);


/* _clipFR */
INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", _clipFR);


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
