#include "common.h"





extern void MatrixDrive_TurnXObjectMatrixYZ(void *dst, void *src);
extern int D_0028B100[];
extern void func_0010F630();
extern void gsb_SetFrame();
extern void gif_SpriteOffset();
extern float D_006D35C0[];
extern int D_00274EC0[];
extern float D_00633DC0;
int InitMailAdditionalData(int a0)
{
    if (a0 < -135) a0 = 180;
    else if (a0 < -45) a0 = -90;
    else if (a0 < 45) a0 = 0;
    else {
        int v = a0;
        a0 = 180;
        if (v <= 134) a0 = 90;
    }
    return a0;
}

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", ActSendMail_WithAdditionalData);

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", GetMailAdditionalData);

void ClearMailAdditionalData(void)
{
    int a = D_00274EC0[0];
    int b = D_00274EC0[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006D35C0[0] = 0;
    *(int *)&D_006D35C0[1] = 0;
    q = diff / b;
    D_00633DC0 = 60.0f / (float)q;
}

void func_00194E28(void)
{
    int a = D_00274EC0[0];
    int b = D_00274EC0[1];
    int t = a * 10;
    int diff = 0x3C - t;
    int q;
    *(int *)&D_006D35C0[0] = 0;
    *(int *)&D_006D35C0[1] = 0;
    q = diff / b;
    D_006D35C0[5] = 120.0f;
    D_006D35C0[6] = 80.0f;
    D_00633DC0 = 60.0f / (float)q;
}

void func_00194EA8(float a, float b)
{
    D_006D35C0[5] = a;
    D_006D35C0[6] = b;
}

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194EC0);

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194FE8);

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194FF8);

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_001950F8);

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_001951A0);

void func_00195208(void)
{
    gif_SpriteOffset(0xB);
    gsb_SetFrame(1, 2, 0x40);
}

void func_00195230(int a0, int a1, int a2, int a3)
{
    func_0010F630(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00195238);

void func_00195350(int a0)
{
    MatrixDrive_TurnXObjectMatrixYZ(D_0028B100, a0);
    gif_SpriteOffset(0xB);
}

