#include "common.h"
#include "ico/types.h"

void InitRopeGeo(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", SetRopeFixPoint);

extern void MatrixDrive_TurnObjectMatrix(int a0, void *a1);

void HoldRope(void *a0, void *a1) {
    Obj7F0 *q = GOBJ_SUB(a0)->p_7F0;
    int *r = *(int **)q;
    int *s = *(int **)r;
    MatrixDrive_TurnObjectMatrix((int)((char *)s + 0x20), a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", ropeGeo);

extern int func_00105078(void);
extern void func_002400F8(int a0);
extern void func_0023FE08(int a0, int a1, int a2);
extern void func_001C1560(int a0, int a1, int a2);

void RopeDL(char *a0)
{
    char *q = *(char **)(*(char **)(a0 + 0x15C) + 0x7F0);
    func_002400F8(func_00105078());
    {
        char *p = *(char **)(a0 + 0x15C);
        if (*(int *)p != 0) {
            int r1 = func_00105078();
            char *p2 = *(char **)(a0 + 0x15C);
            char *sub = *(char **)(*(int *)p2 + 0x15C);
            int addr = *(int *)(sub + 0xC) + *(int *)(p2 + 4) * 0x40;
            func_0023FE08(r1, addr, func_00105078());
        }
    }
    func_001C1560(*(int *)q, 0, func_00105078());
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/rope", CheckRopeUpperWallClimbable);

int ReleaseRope(int a0, void *a1) {
    return GOBJ_SUB(a1)->p_7F0->f_4;
}
