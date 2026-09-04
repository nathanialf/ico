#include "common.h"




extern void ExecFrameDependSequence(int a0);
extern void ExecuteSEPackage(int a0, int a1);
extern void func_001F08D8();
extern int D_00633720;
extern int D_00633724;
extern void iosMallocCheckLeak2();
extern int D_00633728;
typedef struct { char _0[0x14]; int f_14; } SugiLeaf;
extern SugiLeaf D_0070D4D8[];

void SugiLeafGeo2(int i, int v) {
    D_0070D4D8[i].f_14 = v;
}

void FreeStreamMotionBuffer(void)
{
    if (D_00633720 != 0) {
        iosMallocCheckLeak2(D_00633720);
        iosMallocCheckLeak2(D_00633728);
        D_00633728 = 0;
        D_00633720 = 0;
        D_00633724 = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", SugiLeafDL2);

int InitSugiLeafGeo(void) {
    func_001F08D8();
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", _handler);

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", InitSugiLeafGeo2);

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F1508);

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F16A0);

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F16F8);

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F17B0);

void func_001F1838(int a0)
{
    ExecFrameDependSequence(a0);
    ExecuteSEPackage(a0, 0x41);
}

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F1868);

INCLUDE_ASM("asm/nonmatchings/src/sugiTree", func_001F19F0);

