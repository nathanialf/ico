#include "common.h"
#include "ico/types.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/chandelier", ChandelierGeo);

extern int isysGObjSearchFromObjLayoutID();
extern int func_00105078();
extern void CopyMatrix();
extern void func_00105108(float, float, float);
extern void HoldRope();

void ChandelierDL(char *a0) {
    int obj = isysGObjSearchFromObjLayoutID(0x14);
    if (obj != 0) {
        CopyMatrix(func_00105078(), *(int *)(*(char **)(a0 + 0x15C) + 0xC));
        func_00105108(0.0f, 50.0f, 250.0f);
        HoldRope(obj, func_00105078() + 0x30, 0);
    }
}

extern int func_0010F068(int a0);
extern int file_LoadCDFile(int a0);

void InitChandelierGeo(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010F068(a0);
        return file_LoadCDFile((int)s0);
    }
}

int func_001C0728(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/chandelier", func_001C0730);

extern int func_0023D3C0(int a, int b, int c, int d, int e, int f, int g);
extern void actClipCollisionCore(void);
extern int D_0062B564;

int func_001C0950(void) {
    int v = func_0023D3C0(0, 0, 0, 0, (int)&actClipCollisionCore, 0, 0);
    D_0062B564 = v;
    return v;
}

extern void *actCreateSubThreadGOppArg(void *entry, int arg);
extern void func_001C0730(volatile unsigned int self);
/* func_001C0730 is an INCLUDE_ASM sibling in this TU; mark it weak so the %hi/%lo
   reference below emits an R_MIPS_HI16/LO16 against the SYMBOL (as the original
   object did) rather than a .text-section reloc gas would fold a strong in-TU def
   to. Binding is stripped from the .rom — verify_elf is byte-identical either way. */
__asm__(".weak func_001C0730");

void *func_001C0990(int *a0) {
    void *t = actCreateSubThreadGOppArg(func_001C0730, 0x15);
    *(int **)((char *)t + 0x20) = a0;
    a0[0] = 0;
    return t;
}
