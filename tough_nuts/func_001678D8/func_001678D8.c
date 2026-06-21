#include "common.h"

/* near-gp function-pointer table slots (splat named them jtbl_*); set by
 * fzShowV, called indirectly by func_00167F88 — not a switch jump table. */
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

extern float func_0023FE70(int a0, int a1);
extern void func_00240080(int *dst, int *src);

int fzMagnitude3f(int a0) {
    float *p = (float *)a0;
    char *q = (char *)(a0 + 0xA0);
    float t0, t1, d;

    func_00240080((int *)(a0 + 0x20), (int *)(a0 + 0x10));
    t0 = func_0023FE70((int)q, a0 + 0x10) + *(float *)(q + 0xC);
    if (t0 >= 0.0f) {
        return 0;
    }
    t1 = func_0023FE70((int)q, a0) + *(float *)(q + 0xC);
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

void fzMagnitude2fv(float *a0, float a1, float a2, float a3, float a4) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a3;
    a0[3] = a4;
}

int fzMagnitudeByLine(void *a0) {
    if (*(int *)((char *)a0 + 0x88) == 0) return 0;
    return *(int *)((char *)a0 + 0x98);
}

int fzMagnitudeByLineSeg(void *a0) {
    if (*(int *)((char *)a0 + 0x94) == 0) return 0;
    return *(int *)((char *)a0 + 0x98);
}

int func_001668B0(unsigned int a, unsigned int b)
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166910);

extern float func_0023FE70(int a0, int a1);

float func_001669D0(int a0, int a1) {
    return func_0023FE70(a0, a1) + *(float *)(a0 + 0xC);
}

float func_00166A00(float *a0, float *a1) {
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}

float func_00166A48(float *a0, float *a1) {
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

void func_00166A88(void) {
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

int func_00166AB8(int a0, int a1) {
    int v = D_006A4BC0[a1 & 0xF];
    if (v != 0) { MatrixDrive_TurnObjectMatrix(a0, v); return 0; }
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166AF8);

/* func_00166BD8 */
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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166BD8);


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166D00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166E50);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00166FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167120);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167270);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001673B0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001674F0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167630);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167798);

/* func_001678D8 */
extern int DrawGObjWallCollision(void *a0, int a1, int a2);

int func_001678D8(void *a0, int a1, int a2) {
    int found = 0;
    int i = 0;
    if (D_0062C01C > 0) {
        do {
            FuzioCtx *t5 = D_0062C020;
            short *p = t5->unk1C[D_006A4B40[i]];
            if (p != 0 && *p >= 0) {
                do {
                    int addr = t5->unk14 + (int) *p * 0x70;
                    if (DrawGObjWallCollision(a0, addr, 0) != 0) {
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


INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167A00);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167B48);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167C88);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_00167E88);

extern int D_0062A69C;
extern void ClipWallBoxStop(void);

void func_00167F60(void) {
    D_0062A69C = 1;
    ClipWallBoxStop();
    D_0062A69C = 0;
}

extern void func_00240080(int *dst, int *src);

int func_00167F88(int *a0, int *a1) {
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    func_00240080(buf, a0);
    func_00240080(buf + 4, a1);
    ((int (*)(int *, int))jtbl_0062A6D0)(buf, 1);
    return buf[34];
}

void func_00167FE8(void *a0) {
    int *p = (int *)a0;
    p[4] = (int)a0 + p[4];
    p[5] = (int)a0 + p[5];
}

extern char D_0062C578[];
extern char D_0062C580[];
extern int func_00260340(float f);

void func_00168008(float *p)
{
    int i = 3;
    do {
        int s = func_00260340(*p);
        debug_assertMessage(D_0062C578, s);
        p++;
        i--;
    } while (i >= 0);
    debug_assertMessage(D_0062C580);
}

extern char D_0062C588[];

void func_00168070(int *p) {
    int i = 0;
    do {
        debug_assertMessage(D_0062C588, i);
        i++;
        func_00168008(p);
        p = (int *)((char *)p + 0x10);
    } while (i < 4);
}

extern float MatrixDrive_GetTurnYAngleXZ(float a0);

float func_001680D0(float a0, float a1) {
    return MatrixDrive_GetTurnYAngleXZ(a0 * a0 + a1 * a1);
}

float func_001680F8(float a0, float a1, float a2) {
    return MatrixDrive_GetTurnYAngleXZ(a0 * a0 + a1 * a1 + a2 * a2);
}

extern float func_0023FE70(int a0, int a1);

float func_00168128(int a0) {
    return MatrixDrive_GetTurnYAngleXZ(func_0023FE70(a0, a0));
}

struct vec4_0016A320 { float x, y, z, w; } __attribute__((aligned(8)));

float func_00168150(float *a, float *b)
{
    struct vec4_0016A320 v;
    struct vec4_0016A320 diff;
    func_00260568((int *)&diff, 0, 0x10);
    diff.x = b[0] - a[0];
    diff.y = b[1] - a[1];
    diff.z = b[2] - a[2];
    v = diff;
    return MatrixDrive_GetTurnYAngleXZ(func_0023FE70((int)&v, (int)&v));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/fuzio", func_001681E0);


/* recovered struct shapes */
typedef struct {
    short              f_0;  /* 0x00 */
} S_006A4B40;  /* stride 0x2 */

/* end struct shapes */
