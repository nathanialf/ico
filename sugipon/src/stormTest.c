#include "common.h"

void InitStormPackage(void) {
}

void ClipStormByVolume(void) {
}

extern int D_0062B98C;

void ClipStormByCamera(int a0) {
    D_0062B98C = a0;
}

extern int D_00271588[];

void UpdateStormPackage(int a0) {
    D_00271588[0] = a0;
}

extern int D_002714A0[];

void DispStormPackage(int a0, float a1, float a2) {
    D_002714A0[0x3B] = (int)a1;
    D_002714A0[0x3C] = (int)a2;
    D_002714A0[0x3E] = a0;
}

extern float D_0062B928;

void StormTestGeo(float a0) {
    D_0062B928 = a0;
}

extern int D_0062B91C;

void StormTestDL(void) {
    D_0062B91C = 0;
}

extern int D_00271BE0[];
extern int D_0062B914;
extern int D_0062B918;
extern int prim_DispFan2D(int a, float e, int *b, unsigned int c, int d);

void InitStormTestGeo(void)
{
    D_0062B914 = prim_DispFan2D(0x10, 80.0f, D_00271BE0, 0xFFFFFF80u, 0);
    D_0062B918 = prim_DispFan2D(0x10, 80.0f, D_00271BE0, 0xFFFFFF80u, 0);
}

void func_001ECC08(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ECC10);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ECEC8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ED090);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ED248);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ED410);

extern int func_001ED248(int a0);

void func_001ED6F0(void *a0) {
    void *p = *(void **)((char *)a0 + 0x15C);
    void *q = *(void **)((char *)p + 0x7F0);
    func_001ED248(*(int *)((char *)q + 0x20));
}

extern void func_001ED410(int a0, void *a1);

void func_001ED700(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    func_001ED410(q[8], (char *)q + 0x10);
}

extern int iosFree(int t, int sz, const char *file, int line);
extern int func_001ECC10(int a, int b, int c);
extern int D_0062A310;

extern char D_00612E60[];

int *func_001ED718(int a0, int *a1)
{
    int *obj = (int *)iosFree(D_0062A310, 0x30, D_00612E60, 0x11B);
    register int v = *(int *)((char *)a1 + 0x30);
    register int flag = 1;
    *obj = v;
    if (!(0.0f < *(float *)a1)) flag = 0;
    *(int *)((char *)obj + 0x20) = func_001ECC10(1, v, flag);
    *(float *)((char *)obj + 0x10) = *(float *)((char *)a1 + 0x20);
    *(float *)((char *)obj + 0x14) = *(float *)((char *)a1 + 0x24);
    *(float *)((char *)obj + 0x18) = *(float *)((char *)a1 + 0x28);
    *(float *)((char *)obj + 0x1C) = 128.0f;
    return obj;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ED7B8);

extern int D_0062B9F4;
extern int D_0062B9EC;
extern void *D_00612EF0[];
extern void debug_assertMessage(void *a0);
void func_001ED9E8(void) {
    if (D_0062B9F4 != 0) {
        D_0062B9EC = 1;
        return;
    }
    debug_assertMessage(D_00612EF0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001EDA08);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001EDA68);
