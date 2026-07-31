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

extern int D_00631B40;
extern char D_0065FA40[];
extern void func_00243BD8(void *a0);
extern void func_0010E9F8(void);
extern void SetIdentityQuaternion(void);

void func_00104EF0(void)
{
    D_00631B40 = 0;
    func_00243BD8(D_0065FA40);
    func_0010E9F8();
    SetIdentityQuaternion();
}

extern int D_00631B40;
extern char D_0065FA40[];
extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);

void func_00104F20(void)
{
    D_00631B40 += 1;
    MatrixDrive_TurnXObjectMatrixYZ(&D_0065FA40[D_00631B40 * 0x40],
                                    &D_0065FA40[D_00631B40 * 0x40 - 0x40]);
}

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104F48);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00104FC0);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105038);

extern float D_002759A0[];

void func_001050B0(float x, float y, float z)
{
    D_002759A0[0] = x;
    D_002759A0[5] = y;
    D_002759A0[10] = z;
    func_002438E8__p4(&D_0065FA40[D_00631B40 * 0x40], &D_0065FA40[D_00631B40 * 0x40],
                      (int)D_002759A0);
}

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001050E0);

extern int D_00631B40;

void func_00105258(void)
{
    D_00631B40 += 1;
}

void func_00105268(void)
{
    D_00631B40 -= 1;
}

extern char D_0065FA40[];

void *func_00105278(void) {
    return &D_0065FA40[D_00631B40 * 0x40];
}

extern char D_0065FA00[];

void *func_00105290(void) {
    return &D_0065FA00[D_00631B40 * 0x40];
}

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_001052A8);

INCLUDE_ASM("asm/nonmatchings/src/keyInput", func_00105308);

