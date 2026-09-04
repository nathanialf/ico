#include "common.h"

#include "ico/types.h"

typedef struct { unsigned int lo; unsigned char m[3]; unsigned char hi; } FcBlk8;

typedef int (*FcFunc)(void *a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", MakeCollisionDependGObjList);
extern void CopyVector(void *a0, void *a1);
extern float GetDistanceFromPlane(void *a0, void *a1);
extern float GetPointDistance(void *a0, void *a1);
extern void sceVu0AddVector(void *a0, void *a1, void *a2);
extern void sceVu0ScaleVector(void *a0, void *a1, float a2);
extern void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);

void GetReflectionElement(char *a0, float arg0, float arg1) {
    float buf0[4];
    float L10[4];
    float L20[4];
    float z;

    CopyVector(L10, a0 + 0xA0);
    *(int *) &L10[3] = 0;
    sceVu0SubVector(buf0, a0 + 0x10, a0);
    sceVu0ScaleVector(a0 + 0x30, L10, -GetDistanceFromPlane(L10, buf0));
    sceVu0AddVector(a0 + 0x40, buf0, a0 + 0x30);
    sceVu0ScaleVectorXYZ(a0 + 0x30, a0 + 0x30, arg1);
    sceVu0ScaleVectorXYZ(a0 + 0x40, a0 + 0x40, arg0);
    sceVu0AddVector(a0 + 0x60, a0 + 0x40, a0 + 0x30);
    {
        float *p20 = L20;
        z = GetPointDistance(a0 + 0x20, a0 + 0x10);
        sceVu0ScaleVector(p20, a0 + 0x60, z / GetPointDistance(a0, a0 + 0x10));
        sceVu0AddVector(a0 + 0x50, a0 + 0x20, p20);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", clip_wall_1);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", clip_floor_1);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DispCollisionPC);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", makeCollisionBlockTable);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _Clip);
extern FcBlk8 D_0063A810;
extern int _Clip(void *a0);

void __ClipWall(char *a0) {
    *(int *)(a0 + 0xB0) = 0;
    *(int *)(a0 + 0x94) = 0;
    *(int *)(a0 + 0x88) = 0;
    *(FcBlk8 *)(a0 + 0x80) = D_0063A810;
    _Clip(a0);
}
void __ClipFloor(void *a0) {
    *(int *)((char *)a0 + 0x94) = 0;
    *(FcBlk8 *)((char *)a0 + 0x8C) = D_0063A810;
    _Clip(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawGObjWallCollision);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawGObjFloorCollision);
extern char D_00553830[];
extern void debug_StdPrintfDummy();
extern int fptodp(float f);

void DBG_VECTOR(float *vec)
{
    return debug_StdPrintfDummy(D_00553830, fptodp(vec[0]),
                         fptodp(vec[1]), fptodp(vec[2]));
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetEdgeOfFloor);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawCollisionRay);
extern char D_00553960[];
extern char D_00553980[];
extern int D_00639CE0;
extern int D_0063A818;
extern int D_0063C20C;
extern int D_0063C240;
extern void *D_006C0CC0[];
extern void *D_006C1140[];

void MakeExitAttributeIndex(void) {
    int i;
    char *entry;
    int j;
    int n;
    int *p70;
    void *obj;
    int slot;

    debug_StdPrintfDummy(D_00553960, D_00639CE0);
    D_0063C240 = 0;
    i = 0xF;
    do {
        D_006C1140[i] = 0;
        i--;
    } while (i >= 0);
    D_0063C20C = 0;
    obj = D_006C0CC0[0];
    if (D_0063A818 > 0) {
        do {
            p70 = (int *)GOBJ_SUB(obj)->f_70;
            for (j = 0; j < p70[0xC / 4]; j++) {
                entry = (char *)p70[0x14 / 4] + j * 0x70;
                slot = *(int *)(entry + 0x60) & 0xF;
                if (slot != 0) {
                    if (D_006C1140[slot] == 0) {
                        debug_StdPrintfDummy(D_00553980, slot);
                        D_0063C240 = D_0063C240 + 1;
                        D_006C1140[slot] = entry;
                    }
                }
            }
            D_0063C20C = D_0063C20C + 1;
            obj = D_006C0CC0[D_0063C20C];
        } while (D_0063C20C < D_0063A818);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ClipFloorByGObj);
extern int (*D_0063A840)(void *a0, int a1);

int ClipWallDebug(void *a0) {
    return D_0063A840(a0, 0);
}
int ClipWall(void *a0) {
    return D_0063A840(a0, 0x1);
}
int ClipWallR(void *a0) {
    return D_0063A840(a0, 0x2);
}
int ClipWallWaveForce(void *a0) {
    return D_0063A840(a0, 0x6);
}
int ClipWallFuchiHangWalkStop(void *a0) {
    return D_0063A840(a0, 0x7);
}
int ClipWallField(void *a0) {
    return D_0063A840(a0, 0x3);
}
int ClipWallEField(void *a0) {
    return D_0063A840(a0, 0x5);
}
int ClipWallBoxStop(void *a0) {
    return D_0063A840(a0, 0xA);
}
int ClipWallAdjustPos(void *a0) {
    return D_0063A840(a0, 0xB);
}
int ClipWallE(void *a0) {
    return D_0063A840(a0, 0x4);
}
extern int D_0063C23C;

void ClipWallCheckCB(void *a0, int a1) {
    D_0063C23C = a1;
    D_0063A840(a0, 8);
}
void ClipWallFieldCheckCB(void *a0, int a1) {
    D_0063C23C = a1;
    D_0063A840(a0, 9);
}
extern int (*D_0063A844)(void *a0, int a1);

int ClipFloor(void *a0) {
    return D_0063A844(a0, 0xC);
}
int ClipFloorE(void *a0) {
    return D_0063A844(a0, 0xD);
}
int ClipFloorR(void *a0) {
    return D_0063A844(a0, 0xE);
}
int ClipFloorIH(void *a0) {
    return D_0063A844(a0, 0xF);
}
void ClipFloorCheckCB(void *a0, int a1) {
    D_0063C23C = a1;
    D_0063A844(a0, 0x10);
}
extern void sceVu0CopyVector(int *dst, int *src);

void ClipCollision(int *self)
{
    int buf[4];
    int *p10 = self + 4;
    sceVu0CopyVector(buf, p10);
    D_0063A840((int)self, 1);
    sceVu0CopyVector(p10, self + 8);
    D_0063A844((int)self, 0xC);
    sceVu0CopyVector(p10, buf);
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", ChangeFieldCollisionDebugMode);
extern int file_LoadFile(int a0, int a1, int a2);

void LoadCollision(int *self, int a1)
{
    int new_var;
    int *p;
    file_LoadFile((int) self, a1, 0);
    p = (int *) self[0];
    new_var = 0x14 / 4;
    p[0x10 / 4] = (int) (((char *) p) + p[0x10 / 4]);
    p[0x14 / 4] = (int) (((char *) p) + p[new_var]);
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", DrawCollision);
extern void sceVu0CopyVector__pn(void *dst, void *src) __asm__("sceVu0CopyVector");
extern float sceVu0InnerProduct(int a0, int a1);

int ClipPlane(int a0) {
    float *p = (float *)a0;
    char *q = (char *)(a0 + 0xA0);
    float t0, t1, d;

    sceVu0CopyVector__pn((int *)(a0 + 0x20), (int *)(a0 + 0x10));
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
extern char D_005538C8[];
extern char D_005538F8[];
extern float GetTableCos(short a0);
extern float GetTableSin(short a0);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *buf);

void GetOrientOfWall(void *a0, void *a1, int *a2)
{
    float buf[4];
    int *var_19;
    void *obj = (void *)a2[0];

    if (a1 == 0) {
        buf[1] = 0.0f;
        buf[2] = 1.0f;
        var_19 = 0;
        buf[0] = 0.0f;
        debug_StdPrintfDummy(D_005538C8);
    } else {
        var_19 = (int *)1;
        buf[0] = -GetTableSin((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[1] = 0.0f;
        buf[2] = GetTableCos((short)-*(unsigned short *)((char *)a1 + 0x44));
        buf[3] = 1.0f;
    }
    if (var_19 == 0) {
        CopyVector((void *)a0, (void *)buf);
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
            CopyVector((void *)a0, (void *)buf);
            return;
        }
        debug_StdPrintfDummy(D_005538F8);
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
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetWallGlobalInfo);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetDistanceFromPlane);
float GetYDistanceFromPlane(float *a0, float *a1) {
    return a1[1] - (-(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1]);
}
float GetYProjectionOfPlane(float *a0, float *a1) {
    return -(a0[0] * a1[0] + a0[2] * a1[2] + a0[3]) / a0[1];
}
extern int D_0063C210;
extern int D_0063C214;
extern int D_0063C218;
extern int D_0063C21C;
extern int D_0063C220;
extern int D_0063C224;
extern int D_0063C228;
extern int D_0063C22C;
extern int D_0063C230;

void ResetCollisionPC(void) {
    int tmp;
    D_0063C210 = 0;
    tmp = *(volatile int *)0x10000000;
    D_0063C214 = 0;
    D_0063C220 = tmp;

    D_0063C218 = 0;
    D_0063C21C = 0;
    D_0063C224 = 0;
    D_0063C228 = 0;
    D_0063C22C = 0;
    D_0063C230 = 0;
}
extern int D_006C1140__pn[] __asm__("D_006C1140");

int PositionOfExit(int a0, int a1) {
    int v = D_006C1140__pn[a1 & 0xF];
    if (v != 0) { CopyVector(a0, v); return 0; }
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", GetGlobalWallPlane);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWDebug);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipW);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWE);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWEField);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWR);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWField);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWDitchHangWalkStop);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWWaveForce);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWBoxStop);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipWAdjustPos);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipF);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipFE);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipFIH);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", _clipFR);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", __ClipWallWithDrawRay);
INCLUDE_ASM("asm/nonmatchings/src/fieldCollision", __ClipFloorWithDrawRay);
extern void ClipWall__pn() __asm__("ClipWall");
extern int D_0063A80C;

void ClipWallRD(void) {
    D_0063A80C = 1;
    /* Cast away the (int) prototype so gcc doesn't emit `daddu $a0,$0,$0`
     * to set up an arg the original call didn't pass. The implementation
     * happens to read $a0 but the original cross-TU caller didn't bother
     * to clear it. */
    ((void (*)(void))ClipWall__pn)();
    D_0063A80C = 0;
}
extern FcFunc D_0063A840__pn __asm__("D_0063A840");

int ClipWallVector(int *a0, int *a1) {
    int buf[48];
    *(float *)&buf[28] = 50.0f;
    sceVu0CopyVector__pn(buf, a0);
    sceVu0CopyVector__pn(buf + 4, a1);
    D_0063A840__pn(buf, 1);
    return buf[34];
}
void MapCollisionData(int *self) {
    int v0 = self[4];
    int v1 = self[5];
    self[4] = (int)((char *)self + v0);
    self[5] = (int)((char *)self + v1);
}
