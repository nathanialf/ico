#include "common.h"






extern void func_001185D0();
extern void getQuaternionFromMatrix();
extern int * func_00105278();
extern void RegularizeQuaternion();
extern int D_00553E48[];
extern void SetIdentityQuaternion();
extern char D_00553E00[];
extern void debug_assertMessage();
extern char D_00553E28[];
extern int D_00660A30[];
extern int D_00631B7C;
int *GetTableSin(void)
{
    return &D_00660A30[D_00631B7C * 4];
}

void GetTableCos(void)
{
    int v = D_00631B7C;
    if (v < 0) {
        debug_assertMessage(D_00553E00);
        SetIdentityQuaternion();
        v = D_00631B7C;
    }
    v++;
    D_00631B7C = v;
    if (v >= 0x40) {
        debug_assertMessage(D_00553E28);
        v = 0x3F;
        D_00631B7C = v;
    }
}

void InitTableSin(void)
{
    D_00631B7C -= 1;
    if (D_00631B7C < 0) {
        debug_assertMessage(D_00553E48);
        D_00631B7C = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcSin);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcCos);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", GetTableArcTan2);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DCF8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DD58);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DDB8);

void func_0010DDF8(int self, int a1, int a2)
{
    int buf[4];
    RegularizeQuaternion(buf, a2);
    func_0010DDB8(self, buf, a1);
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DE40);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DEC0);

void func_0010DF70(void *src)
{
    int local[16];
    void *r1, *r2;
    getQuaternionFromMatrix(local, src);
    r1 = func_00105278();
    r2 = func_00105278();
    func_001185D0(r1, r2, local);
}

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010DFB8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E0B8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E158);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E1F8);

INCLUDE_ASM("asm/nonmatchings/src/tableSin", func_0010E298);

