#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", InitKeyInput);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", ExecKeyInput);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104498);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_001044F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104548);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104618);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_001046C8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104740);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_001047C0);

extern int D_006594C0[];

void *func_00104838(void) {
    return D_006594C0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104848);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_001048F0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104998);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104A80);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104CF0);

extern int D_00629E40;
extern unsigned char D_006595C0[];
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);

void func_00104D20(void) {
    int n = ++D_00629E40;
    MatrixDrive_TurnXObjectMatrixYZ(&D_006595C0[n * 64], &D_006595C0[n * 64 - 0x40]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104D48);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104DC0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104E38);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104EB0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00104EE0);

extern int D_00629E40;

void func_00105058(void) {
    D_00629E40++;
}

void func_00105068(void) {
    D_00629E40--;
}

extern unsigned char D_006595C0[];

void *func_00105078(void) {
    return &D_006595C0[D_00629E40 * 64];
}

extern unsigned char D_00659580[];

void *func_00105090(void) {
    return &D_00659580[D_00629E40 * 64];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_001050A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/keyInput", func_00105108);
