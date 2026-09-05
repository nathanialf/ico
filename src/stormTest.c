#include "common.h"

/* header prototypes (order fixes the inline tail) */
extern void UpdateStormPackage(int a0);
extern void DispStormPackage(int a0, void *a1);
extern char D_00620FA0[];
extern int D_0063A438;
/* prototypes: their order is the inline tail's emission order */
int *InitStormTestGeo(int a0, int *a1);
extern int InitStormPackage(int a, int b, int c);
extern int iosMallocDebug(int t, int sz, const char *file, int line);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", InitStormPackage);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", ClipStormByVolume);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", ClipStormByCamera);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", UpdateStormPackage);
INCLUDE_ASM("asm/nonmatchings/src/stormTest", DispStormPackage);
inline int *InitStormTestGeo(int a0, int *a1)
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
void StormTestGeo(char *a0) {
    UpdateStormPackage(*(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x20));
}
void StormTestDL(char *a0) {
    char *p = *(char **)(*(char **)(a0 + 0x15C) + 0x830);
    DispStormPackage(*(int *)(p + 0x20), p + 0x10);
}
