#include "common.h"



extern int D_006333EC;
extern int checkHit(char *self);
extern void WeaponGeo(int *self);
extern int D_00631AEC;
extern void iosPadDevRead();
int func_001D1440(int a0)
{
    iosPadDevRead(D_00631AEC, a0);
    return 1;
}

int func_001D1468(void)
{
    int *p;
    int *q;
    p = (int *)((int *)D_006333EC)[0x15C/4];
    q = (int *)p[0x630/4];
    if (q != 0) {
        if (checkHit(q) == 1) {
            int *r = (int *)((int *)D_006333EC)[0x15C/4];
            WeaponGeo((int *)r[0x630/4]);
        }
    }
    return 1;
}

extern volatile float D_00631270;
extern volatile float D_00631274;
extern volatile float D_00631278;
extern volatile float D_0063127C;
extern void DispMeshWire(int a0, float f12, float f13);

void InitGirlGeo(void *a0) {
    char *s0 = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    if (*(int *)(s0 + 0xC) != 0) {
        if (*(int *)(s0 + 0x10) != 0) {
            DispMeshWire(*(int *)(s0 + 0x10), 4.0f, D_00631270);
        }
        if (*(int *)(s0 + 0x14) != 0) {
            DispMeshWire(*(int *)(s0 + 0x14), 4.0f, D_00631274);
        }
    }
    if (*(int *)(s0 + 0x4) != 0) {
        if (*(int *)(s0 + 0x8) != 0) {
            DispMeshWire(*(int *)(s0 + 0x8), 3.0f, D_00631278);
        }
    }
    if (*(int *)(s0 + 0x18) != 0) {
        if (*(int *)(s0 + 0x1C) != 0) {
            DispMeshWire(*(int *)(s0 + 0x1C), 4.0f, D_0063127C);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/girl", GirlGeo);

INCLUDE_ASM("asm/nonmatchings/src/girl", debugWireStringGirl);

INCLUDE_ASM("asm/nonmatchings/src/girl", GirlDL);

INCLUDE_ASM("asm/nonmatchings/src/girl", GirlAI);

extern int GirlAI(int a0);
extern void GirlGeo(int a0);
extern void func_0010ECB8(int a0);
extern void func_0010ECD8(int a0);

void SetGirlClothDispSwitch(int a0)
{
    func_0010ECD8(a0);
    func_0010ECB8(a0);
    GirlGeo(a0);
    return GirlAI(a0);
}

