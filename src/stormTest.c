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

INCLUDE_ASM("asm/nonmatchings/src/stormTest", StormTestGeo);

void StormTestDL(void) {
    D_0063363C = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/stormTest", InitStormTestGeo);

void func_001EFA58(void) {}

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFA60);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFD18);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001EFEE0);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0098);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0260);

INCLUDE_ASM("asm/nonmatchings/src/stormTest", func_001F0540);

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

