#include "common.h"

#include "ico/types.h"
#include "vu0.h"



extern int D_0065F940[];
extern void MatrixDrive_TransMatrix();
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern void func_002438E8();
extern char D_00275890[];
extern void func_0010DEC0(void *a0, void *a1, void *a2);
extern void func_002438B8(int *buf, char *p, int x);
extern void func_002438E8__p4(char *dst, char *src, int m) __asm__("func_002438E8");
extern void func_00243978(char *a0, char *a1);

void InitKeyInput(char *a0, char *a1)
{
    char buf[0x40];
    char *sub = *(char **)(a1 + 0x15C);
    char *p = sub + 0xA0;
    func_0010DEC0(buf, sub + 0xD0, p);
    {
        char *q = *(char **)sub;
        if (q != 0) {
            func_002438E8__p4(buf, (char *)(*(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)(sub + 4) << 6)), (int)buf);
        }
    }
    *(float *)(buf + 0x34) = *(float *)(buf + 0x34) + *(float *)(p + 0xC0);
    func_002438B8((int *)a0, buf, (int)D_00275890);
    *(int *)(a0 + 4) = 0;
    func_00243978(a0, a0);
}

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

