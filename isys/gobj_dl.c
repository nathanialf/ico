#include "common.h"




extern int D_00281AD0[];
extern char D_00557A58[];
extern void debug_assertMessage();
extern int D_006321D0;
extern int D_006321CC;
INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", cut_gobj_dl_link);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjRemoveObjDL);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", func_0013ECF8);

void func_0013ED40(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321CC &= ~(1 << bit);
    return;
set_path:
    D_006321CC |= (1 << bit);
}

void isysGObjMoveObjDL(int bit, int set)
{
    if (set != 0) goto set_path;
    D_006321D0 &= ~(1 << bit);
    return;
set_path:
    D_006321D0 |= (1 << bit);
}

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjMoveObjDLHead);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjLinkObjDL);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjLinkObjDLHead);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjLinkObjDLAfterGObj);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjLinkObjDLBeforeGObj);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjDlInit);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjMoveObjDLAfterGObj);

INCLUDE_ASM("asm/nonmatchings/isys/gobj_dl", isysGObjMoveObjDLBeforeGObj);

void func_0013F1F8(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_assertMessage(D_00557A58);
        return;
    }
    t0[0x14] = a2;
    t0[0x12] = (int)a1;
    *((unsigned char *)t0 + 0x40) = *((unsigned char *)a3 + 0x40);
    t0[0xE] = (int)a3;
    v34 = a3[0xD];
    v44 = a3[0x11];
    t0[0xD] = v34;
    a3[0xD] = (int)t0;
    t0[0x11] = v44;
    if (t0[0xD] == 0) {
        D_00281AD0[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}

void func_0013F260(int *self, int *a1, int a2, int *a3)
{
    int *t0;
    int v34, v44;
    if (a1 == 0) return;
    t0 = self;
    if (a3 == 0) {
        debug_assertMessage(D_00557A58);
        return;
    }
    t0[0x14] = a2;
    t0[0x12] = (int)a1;
    *((unsigned char *)t0 + 0x40) = *((unsigned char *)a3 + 0x40);
    t0[0xE] = (int)a3;
    v34 = a3[0xD];
    v44 = a3[0x11];
    t0[0xD] = v34;
    a3[0xD] = (int)t0;
    t0[0x11] = v44;
    if (t0[0xD] == 0) {
        D_00281AD0[*((unsigned char *)t0 + 0x40)] = (int)t0;
    }
}

