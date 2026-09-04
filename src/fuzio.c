#include "common.h"





typedef int (*FcFunc)(void *a0, int a1);
extern FcFunc D_006323F0;
extern FcFunc D_006323F4;
extern void sceVu0CopyVector(void *dst, void *src);
extern void ClipWall();
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
extern void DrawCollisionRay(char *a0);
extern void MakeExitAttributeIndex(void *a0);
extern void func_00169F80(void *a0);
extern void func_0016A058(void *a0);

int fzShowV(int a0)
{
    D_006323F0 = (FcFunc) DrawCollisionRay;
    D_006323F4 = (FcFunc) MakeExitAttributeIndex;
    if (a0 != 0) {
        D_006323F0 = (FcFunc) func_00169F80;
        D_006323F4 = (FcFunc) func_0016A058;
    }
    return 0;
}

extern int func_0010F5B8(int a0, int a1, int a2);

void LoadCollision(int *self, int a1)
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

extern float sceVu0InnerProduct(int a0, int a1);

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

extern char D_00559368[];
extern char D_00559398[];
extern void debug_StdPrintfDummy();
extern float GetTableCos(short a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *buf);
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
        debug_StdPrintfDummy(D_00559368);
    } else {
        var_19 = (int *)1;
        buf[0] = -p2o_SetDefaultEnviroment((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[1] = 0.0f;
        buf[2] = GetTableCos((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[3] = 1.0f;
    }
    if (var_19 == 0) {
        MatrixDrive_TurnObjectMatrix((void *)a0, (void *)buf);
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
            MatrixDrive_TurnObjectMatrix((void *)a0, (void *)buf);
            return;
        }
        debug_StdPrintfDummy(D_00559398);
    }
}

void SetSimplePlane(float *self, float a, float b, float c, float d) {
    self[0] = a; self[1] = b; self[2] = c; self[3] = d;
}

int GetWallAttribute(int a0) {
    if (*(int *)(a0 + 0x88) == 0) return 0;
    return *(int *)(a0 + 0x98);
}

int GetFloorAttribute(int a0) {
    if (*(int *)(a0 + 0x94) == 0) return 0;
    return *(int *)(a0 + 0x98);
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

INCLUDE_ASM("asm/nonmatchings/src/fuzio", GetWallGlobalInfo);

float GetDistanceFromPlane(int a0, int a1)
{
    return sceVu0InnerProduct(a0, a1) + *(float *)(a0 + 0xC);
}

float GetYDistanceFromPlane(float *a0, float *a1) {
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}

float GetYProjectionOfPlane(float *a0, float *a1) {
    return -(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1];
}

void ResetCollisionPC(void) {
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

int PositionOfExit(int a0, int a1) {
    int v = D_006AB100[a1 & 0xF];
    if (v != 0) { MatrixDrive_TurnObjectMatrix(a0, v); return 0; }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/fuzio", GetGlobalWallPlane);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWDebug);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipW);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWE);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWEField);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWR);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWField);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWDitchHangWalkStop);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWWaveForce);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWBoxStop);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipWAdjustPos);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipF);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipFE);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipFIH);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", _clipFR);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_00169F80);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_0016A058);

void ClipWallRD(void) {
    D_006323BC = 1;
    /* Cast away the (int) prototype so gcc doesn't emit `daddu $a0,$0,$0`
     * to set up an arg the original call didn't pass. The implementation
     * happens to read $a0 but the original cross-TU caller didn't bother
     * to clear it. */
    ((void (*)(void))ClipWall)();
    D_006323BC = 0;
}

int ClipWallVector(int *a0, int *a1) {
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    sceVu0CopyVector(buf, a0);
    sceVu0CopyVector(buf + 4, a1);
    D_006323F0(buf, 1);
    return buf[34];
}

void MapCollisionData(int *self) {
    int v0 = self[4];
    int v1 = self[5];
    self[4] = (int)((char *)self + v0);
    self[5] = (int)((char *)self + v1);
}

INCLUDE_ASM("asm/nonmatchings/src/fuzio", func_0016A1D8);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzShowM);

extern float FSqrt(float a0);

float func_0016A2A0(float x, float z)
{
    return FSqrt(x * x + z * z);
}

float func_0016A2C8(float x, float y, float z)
{
    return FSqrt(x * x + y * y + z * z);
}

float func_0016A2F8(int v)
{
    return FSqrt(sceVu0InnerProduct(v, v));
}

INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzMagnitude2fv);

INCLUDE_ASM("asm/nonmatchings/src/fuzio", fzMagnitudeByLine);

