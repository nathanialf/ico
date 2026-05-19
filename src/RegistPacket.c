/* src/RegistPacket.c — __FILE__ anchor at .rodata 0x00555650 */

#include "matching.h"
#include "include_asm.h"

__attribute__((section(".rodata.0x00555650"))) const char D_00555650[24] = "src/RegistPacket.c";

__attribute__((section(".rodata.0x00555A68"))) const char D_00555A68[24] = " Shadow Blend 1/64 ";
__attribute__((section(".rodata.0x00555A80"))) const char D_00555A80[24] = " Shadow Blend 1/16 ";
__attribute__((section(".rodata.0x00555A98"))) const char D_00555A98[24] = " Shadow Blend 1/4  ";
__attribute__((section(".rodata.0x00555AB0"))) const char D_00555AB0[24] = " Shadow Blend 1/1  ";
__attribute__((section(".rodata.0x00555AC8"))) const char D_00555AC8[24] = " Shadow Color B    ";
__attribute__((section(".rodata.0x00555AE0"))) const char D_00555AE0[24] = " Shadow Color G    ";
__attribute__((section(".rodata.0x00555AF8"))) const char D_00555AF8[24] = " Shadow Color R    ";
__attribute__((section(".rodata.0x00555B10"))) const char D_00555B10[24] = " Shadow Depth      ";
__attribute__((section(".rodata.0x00555B30"))) const char D_00555B30[16] = "Shadow Tool";

/* String rodata migrated from RegistPacket_data.c */
__attribute__((section(".rodata.0x00555620"))) const char D_00555620[48] = "reg_setShape:illegal vertex index. %d/%d\n";
__attribute__((section(".rodata.0x00555668"))) const char D_00555668[56] = "reg_setShape:illegal normal index. %d/%d\n";
__attribute__((section(".rodata.0x00555710"))) const char D_00555710[24] = "illegal clip type. %d\n";
__attribute__((section(".rodata.0x00555728"))) const char D_00555728[40] = "no light calc cluster model %s\n";
__attribute__((section(".rodata.0x00555920"))) const char D_00555920[24] = "shadow_Render called\n";
__attribute__((section(".rodata.0x00555B40"))) const char D_00555B40[24] = "Shadow %s => %s\n";
__attribute__((section(".rodata.0x00555B58"))) const char D_00555B58[24] = "Shadow %s => %d\n";

/* EUC-JP debug strings — re-derived from EE rodata bytes via
 * EUC-JP decoding. Octal escapes preserve byte-identical layout
 * without requiring source-encoding compiler flags. */
/* EUC-JP: "光源オフでリフレクションを表示.
" */
__attribute__((section(".rodata.0x00555800"))) const char D_00555800[48] = "\270\367\270\273\245\252\245\325\244\307\245\352\245\325\245\354\245\257\245\267\245\347\245\363\244\362\311\275\274\250.\n";

extern int D_00632028;
extern void func_0011D9A0(int a0, int a1, int a2, int a3, int a4);
extern void func_00118E88(int);
extern void func_00118C68(int a0, int a1, int a2, int a3, int a4);
extern int func_001FBAA8(int a0, int v, int n);
extern void func_001FB8B8(void);

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011DF18);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011E0B8);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011E220);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011E4F8);

void func_0011E708(int a0, int a1, int a2, int a3)
{
    func_0011D9A0(a0, a1, a2, a3, D_00632028);
    DEFEAT_TCO();
}

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011E728);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011EB50);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011ECE0);

void func_0011EDF8(char *a0)
{
    int *p820 = *(int **)(a0 + 0x820);
    if (*((signed char *)p820 + 0x2F) != 0) {
        return func_00118E88(3);
    }
    {
        int *p844 = *(int **)(a0 + 0x844);
        if (*(int *)((char *)p844 + 0xF0) == 0) {
            return func_00118E88(1);
        }
    }
    return func_00118E88(2);
}

INCLUDE_ASM_NOP_PAD(func_0011EE2C);
void func_0011EE30(char *self, int b, int c)
{
    long long v_ll = *(long long *)(self + 0x60);
    int v_int = *(int *)(self + 0x60);
    func_00118C68(v_int & 1, ((int)(v_ll >> 5)) & 3, 0, b, c);
}

void func_0011EE58(int a0, int a1, int a2)
{
    func_00118C68(a0, 1, 1, a1, a2);
}

INCLUDE_ASM_NOP_PAD(func_0011EE6C);

void func_0011EE70(int a0, int a1, int a2)
{
    func_00118C68(a0, 1, 2, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011EE84);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011EE88);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011EF70);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011F040);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011F248);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011F398);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011F468);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011F8E8);
INCLUDE_ASM("asm/nonmatchings/src/RegistPacket", func_0011FC28);

void func_0011FCD8(short *self, int *p)
{
    short idx = self[0x80/2];
    if (idx != -1) {
        int v = *p + idx * 0x70;
        func_001FBAA8(2, v, 6);
        func_001FB8B8();
    }
}
