#include "common.h"





extern unsigned int D_006323F0;
extern void func_00243B60(void *dst, void *src);
extern void ClipWallBoxStop();
extern int D_006323BC;
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern int D_006AB100[];
extern int D_00633D10;
extern int D_00633D28;
extern int D_00633D08;
extern int D_00633D24;
extern int D_00633D18;
extern int D_00633D14;
extern int D_00633D0C;
extern int D_00633D20;
extern int D_00633D1C;
INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzShowV);

extern volatile int func_0010F5B8(int a0, int a1, int a2);

void fzShowM(int *self, int a1)
{
    int new_var;
    int *p;
    func_0010F5B8((int) self, a1, 0);
    p = (int *) self[0];
    new_var = 0x14 / 4;
    p[0x10 / 4] = (int) (((char *) p) + p[0x10 / 4]);
    p[0x14 / 4] = (int) (((char *) p) + p[new_var]);
}

INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzMagnitude2f);

extern float func_00243950(int a0, int a1);
extern void func_00243B60__p4(int *dst, int *src) __asm__("func_00243B60");

int fzMagnitude3f(int a0) {
    float *p = (float *)a0;
    char *q = (char *)(a0 + 0xA0);
    float t0, t1, d;

    func_00243B60__p4((int *)(a0 + 0x20), (int *)(a0 + 0x10));
    t0 = func_00243950((int)q, a0 + 0x10) + *(float *)(q + 0xC);
    if (t0 >= 0.0f) {
        return 0;
    }
    t1 = func_00243950((int)q, a0) + *(float *)(q + 0xC);
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

extern char D_00559368[];
extern char D_00559398[];
extern void MatrixDrive_TurnObjectMatrix__p4(int a0, int a1) __asm__("MatrixDrive_TurnObjectMatrix");
extern void debug_assertMessage();
extern float func_0010E9A0(short a0);
extern void func_002438B8(void *a0, void *a1, void *buf);
extern float p2o_SetDefaultEnviroment(short a0);

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
        debug_assertMessage(D_00559368);
    } else {
        var_19 = (int *)1;
        buf[0] = -p2o_SetDefaultEnviroment((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[1] = 0.0f;
        buf[2] = func_0010E9A0((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[3] = 1.0f;
    }
    if (var_19 == 0) {
        MatrixDrive_TurnObjectMatrix__p4((int)a0, (int)buf);
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
                func_002438B8(a0, (void *)(*(int *)((char *)o3 + 0xC) + (idx << 6)), buf);
                return;
            }
            MatrixDrive_TurnObjectMatrix__p4((int)a0, (int)buf);
            return;
        }
        debug_assertMessage(D_00559398);
    }
}

void fzMagnitude2fv(float *self, float a, float b, float c, float d) {
    self[0] = a; self[1] = b; self[2] = c; self[3] = d;
}

int fzMagnitudeByLine(int a0) {
    if (*(int *)(a0 + 0x88) == 0) return 0;
    return *(int *)(a0 + 0x98);
}

int fzMagnitudeByLineSeg(int a0) {
    if (*(int *)(a0 + 0x94) == 0) return 0;
    return *(int *)(a0 + 0x98);
}

int func_00168A80(unsigned int a, unsigned int b)
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

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00168AE0);

float func_00168BA0(int a0, int a1)
{
    return func_00243950(a0, a1) + *(float *)(a0 + 0xC);
}

float func_00168BD0(float *a0, float *a1) {
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}

float func_00168C18(float *a0, float *a1) {
    return -(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1];
}

void func_00168C58(void) {
    int tmp;
    D_00633D08 = 0;
    tmp = *(volatile int *)0x10000000;
    D_00633D0C = 0;
    D_00633D18 = tmp;

    D_00633D10 = 0;
    D_00633D14 = 0;
    D_00633D1C = 0;
    D_00633D20 = 0;
    D_00633D24 = 0;
    D_00633D28 = 0;
}

int func_00168C88(int a0, int a1) {
    int v = D_006AB100[a1 & 0xF];
    if (v != 0) { MatrixDrive_TurnObjectMatrix(a0, v); return 0; }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00168CC8);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00168DA8);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00168ED0);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169020);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169190);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_001692F0);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169440);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169580);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_001696C0);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169800);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169968);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169AA8);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169BD0);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169D18);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169E58);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169F80);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_0016A058);

void func_0016A130(void) {
    D_006323BC = 1;
    /* Cast away the (int) prototype so gcc doesn't emit `daddu $a0,$0,$0`
     * to set up an arg the original call didn't pass. The implementation
     * happens to read $a0 but the original cross-TU caller didn't bother
     * to clear it. */
    ((void (*)(void))ClipWallBoxStop)();
    D_006323BC = 0;
}

int func_0016A158(int *a0, int *a1) {
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    func_00243B60(buf, a0);
    func_00243B60(buf + 4, a1);
    ((int (*)(int *, int))D_006323F0)(buf, 1);
    return buf[34];
}

void func_0016A1B8(int *self) {
    int v0 = self[4];
    int v1 = self[5];
    self[4] = (int)((char *)self + v0);
    self[5] = (int)((char *)self + v1);
}

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_0016A1D8);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_0016A240);

extern float MatrixDrive_GetTurnYAngleXZ(float a0);

float func_0016A2A0(float x, float z)
{
    return MatrixDrive_GetTurnYAngleXZ(x * x + z * z);
}

float func_0016A2C8(float x, float y, float z)
{
    return MatrixDrive_GetTurnYAngleXZ(x * x + y * y + z * z);
}

float func_0016A2F8(int v)
{
    return MatrixDrive_GetTurnYAngleXZ(func_00243950(v, v));
}

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_0016A320);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_0016A3B0);

