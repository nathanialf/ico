#include "common.h"



extern int D_0065F940[];
extern void MatrixDrive_TransMatrix();
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern void func_002438E8();
INCLUDE_ASM("asm/nonmatchings/src/keyInput", InitKeyInput);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", ExecKeyInput);

void func_00104698(char *dst, char *src)
{
    char tmp[0x40];
    MatrixDrive_TransMatrix(tmp, src + 0x20);
    func_002438E8(tmp, tmp, *(int *)(src + 0xC));
    MatrixDrive_TurnObjectMatrix((int)dst, (int)(tmp + 0x30));
}

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001046F0);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104748);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104818);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001048C8);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104940);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001049C0);

int *func_00104A38(void) {
    return D_0065F940;
}

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104A48);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104AF0);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104B98);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104C80);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104EF0);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104F20);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104F48);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104FC0);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105038);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001050B0);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001050E0);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105258);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105268);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105278);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105290);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001052A8);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105308);

