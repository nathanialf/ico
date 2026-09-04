#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/stormTest", InitStormPackage);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", ClipStormByVolume);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", ClipStormByCamera);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", UpdateStormPackage);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", DispStormPackage);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", StormTestGeo);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", StormTestDL);
extern char D_00620FA0[];
extern int D_0063A438;
extern int InitStormPackage(int a, int b, int c);
extern int iosMallocDebug(int t, int sz, const char *file, int line);

int *InitStormTestGeo(int a0, int *a1)
{
    int *obj = (int *)iosMallocDebug(D_0063A438, 0x30, D_00620FA0, 0x11B);
    register int v = *(int *)((char *)a1 + 0x30);
    register int flag = 1;
    *obj = v;
    if (!(0.0f < *(float *)a1)) flag = 0;
    *(int *)((char *)obj + 0x20) = InitStormPackage(1, v, flag);
    *(float *)((char *)obj + 0x10) = *(float *)((char *)a1 + 0x20);
    *(float *)((char *)obj + 0x14) = *(float *)((char *)a1 + 0x24);
    *(float *)((char *)obj + 0x18) = *(float *)((char *)a1 + 0x28);
    *(float *)((char *)obj + 0x1C) = 128.0f;
    return obj;
}
