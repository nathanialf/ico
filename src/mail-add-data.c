/* src/mail-add-data.c — __FILE__ anchor at .rodata 0x0055AF08 */

__attribute__((section(".rodata.0x0055AF08"))) const char D_0055AF08[24] = "src/mail-add-data.c";

__attribute__((section(".rodata.0x0055AF20"))) const char D_0055AF20[16] = "GOBJ_VAL(gop)";
__attribute__((section(".rodata.0x0055AF30"))) const char D_0055AF30[48] = "mad_all->current_count<MAIL_ADDITIONAL_DATA_MAX";
__attribute__((section(".rodata.0x0055AF60"))) const char D_0055AF60[16] = "STOP TGT";
__attribute__((section(".rodata.0x0055AF70"))) const char D_0055AF70[16] = "STOP FIN";
__attribute__((section(".rodata.0x0055AF80"))) const char D_0055AF80[24] = "STOP NO FIN %d,%1.1f";

/* String rodata migrated from mail-add-data_data.c */
__attribute__((section(".rodata.0x0055AF98"))) const char D_0055AF98[24] = "bird reset\n";

#include "matching.h"
#include "include_asm.h"

extern float D_006D35C0[];
extern void func_001951A0(int a0);

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194840);

void func_001948A8(float *a, float *b)
{
    float tmp[3];
    tmp[0] = a[0];
    tmp[1] = a[1];
    tmp[2] = a[2];
    a[0] = b[0];
    a[1] = b[1];
    a[2] = b[2];
    b[0] = tmp[0];
    b[1] = tmp[1];
    b[2] = tmp[2];
    __asm__ __volatile__("" : : "r"(tmp) : "memory");
}

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_001948F0);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194960);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_001949B8);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194A08);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194BD8);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194DC0);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194E28);

void func_00194EA8(float a, float b)
{
    D_006D35C0[5] = a;
    D_006D35C0[6] = b;
}

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194EC0);

void func_00194FE8(int a0, int a1)
{
    *(int *)(*(int *)(a0 + 0x164) + 0x674) = a1;
    func_001951A0(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194FF4);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194FF8);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_001950F8);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_001951A0);
