#include "common.h"







extern unsigned int D_0063373C;
extern int D_0061A578[];
extern void debug_assertMessage();
extern int D_00633714;
extern int D_0063370C;
extern char D_0061A500[];
extern int D_0063363C;
struct D275 {
    char pad[0xEC];
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
};
extern struct D275 D_00275120;
extern int D_00275208[];
extern int D_006336AC;
void InitStormPackage(void) {}

void ClipStormByVolume(void) {}

void ClipStormByCamera(int val) {
    D_006336AC = val;
}

void UpdateStormPackage(int x) {
    D_00275208[0] = x;
}

void DispStormPackage(float f12, float f13, int a0)
{
    D_00275120.field_EC = (int)f12;
    D_00275120.field_F0 = (int)f13;
    D_00275120.field_F8 = a0;
}

extern float D_00633648;

void StormTestGeo(float a0) {
    D_00633648 = a0;
}

void StormTestDL(void) {
    D_0063363C = 0;
}

extern int D_00275860[];
extern int D_00633634;
extern int D_00633638;
extern int prim_DispFan2D(int a, float e, int *b, unsigned int c, int d);

void InitStormTestGeo(void)
{
    D_00633634 = prim_DispFan2D(0x10, 80.0f, D_00275860, 0xFFFFFF80u, 0);
    D_00633638 = prim_DispFan2D(0x10, 80.0f, D_00275860, 0xFFFFFF80u, 0);
}

void func_001EFA58(void) {}

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFA60);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFD18);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFEE0);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0098);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0260);

extern void func_001F0098(int a0);

void func_001F0540(void *a0) {
    char *p = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);
    func_001F0098(*(int *)(p + 0x20));
}

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0550);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0568);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0608);

void func_001F0858(void)
{
    if (D_00633714 == 0) {
        return debug_assertMessage(D_0061A500);
    }
    D_0063370C = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0878);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F08D8);

void func_001F0A28(void)
{
    D_0063373C = 0;
    debug_assertMessage(D_0061A578);
}

