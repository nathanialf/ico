#include "common.h"

#include "ico/types.h"


extern int func_00240EA0();
extern int D_006332A4;
extern void actClipCollisionCore();
INCLUDE_ASM("asm/nonmatchings/src/chandelier", ChandelierGeo);

extern void HoldRope();
extern void CopyMatrix();
extern int func_00105278();
extern void func_00105308(float, float, float);
extern int isysGObjSearchFromObjLayoutID();

void ChandelierDL(char *a0) {
    int obj = isysGObjSearchFromObjLayoutID(0x14);
    if (obj != 0) {
        CopyMatrix(func_00105278(), *(int *)(*(char **)(a0 + 0x15C) + 0xC));
        func_00105308(0.0f, 50.0f, 250.0f);
        HoldRope(obj, func_00105278() + 0x30, 0);
    }
}

extern int file_LoadCDFile(int a0);
extern int func_0010ECD8(int a0);

void InitChandelierGeo(int a0)
{
    int *s0 = ((GObj *)((char *)a0))->p_15C;
    if (s0[0x74 / 4] != 0) {
        func_0010ECD8(a0);
        return file_LoadCDFile((int)s0);
    }
}

int func_001C34B8(void)
{
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/chandelier", func_001C34C0);

int func_001C36E0(void) {
    int v = func_00240EA0(0, 0, 0, 0, (int)&actClipCollisionCore, 0, 0);
    D_006332A4 = v;
    return v;
}

INCLUDE_ASM("asm/nonmatchings/src/chandelier", func_001C3720);

