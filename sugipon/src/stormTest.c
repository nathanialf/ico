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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", DispStormPackage);

extern float D_0062B928;

void StormTestGeo(float a0) {
    D_0062B928 = a0;
}

extern int D_0062B91C;

void StormTestDL(void) {
    D_0062B91C = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", InitStormTestGeo);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ED718);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ED7B8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001ED9E8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001EDA08);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/stormTest", func_001EDA68);
