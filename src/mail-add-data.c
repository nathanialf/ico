/* src/mail-add-data.c — __FILE__ anchor at .rodata 0x0055AF08 */

const char D_0055AF08[24] = "src/mail-add-data.c";

const char D_0055AF20[16] = "GOBJ_VAL(gop)";
const char D_0055AF30[48] = "mad_all->current_count<MAIL_ADDITIONAL_DATA_MAX";
const char D_0055AF60[16] = "STOP TGT";
const char D_0055AF70[16] = "STOP FIN";
const char D_0055AF80[24] = "STOP NO FIN %d,%1.1f";

/* String rodata migrated from mail-add-data_data.c */
const char D_0055AF98[24] = "bird reset\n";

#include "matching.h"
/* Inlined data (Phase 3e) — migrated from mail-add-data_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* strings */
unsigned int D_006327B0[2] = { 0x7F7FFFFF, 0x00000000 };
const char D_006327B8[8] = "EAT";
const char D_006327C0[8] = "STEP";
const char D_006327C8[8] = "GROOM";
const char D_006327D0[8] = "FLY S";
const char D_006327D8[8] = "FLY";
const char D_006327E0[8] = "FLY E1";
const char D_006327E8[8] = "FLY E2";

/* Inlined data (Phase 3e) — migrated from mail-add-data_data.c.
 * Plain typed defs; ee-gcc -fdata-sections + slinky place each
 * at its original VMA. See tools/inline_tu_data.py. */

/* scalars */
float D_00630FC4 = 0.1f;
float D_00630FC8 = 0.008726646f;
float D_00630FCC = 3.1415927f;
float D_00630FD0 = 3.1415927f;
float D_00630FD4 = 3.1415927f;
float D_00630FD8 = 10430.378f;
float D_00630FDC = 0.7f;
float D_00630FE0 = 6.2831855f;
float D_00630FE4 = 0.08726647f;
float D_00630FE8 = 6.2831855f;
float D_00630FEC = 0.28f;
float D_00630FF0 = 0.28f;
float D_00630FF4 = 0.4f;
float D_00630FF8 = 0.7f;
float D_00630FFC = 6.2831855f;
float D_00631000 = 6.2831855f;
float D_00631004 = 0.2f;
float D_00631008 = 6.2831855f;
float D_0063100C = 0.016666668f;
float D_00631010 = 6.2831855f;
float D_00631014 = 6.2831855f;
float D_00631018 = 0.034906585f;
float D_0063101C = -0.034906585f;
float D_00631020 = 0.6f;
float D_00631024 = -1.3f;
float D_00631028 = 0.6f;
float D_0063102C = 0.14285715f;
float D_00631030 = 0.2f;
float D_00631034 = 0.001f;
float D_00631038 = 6.2831855f;

#include "include_asm.h"

extern float D_006D35C0[];
extern void func_001951A0(char *a0);

extern void func_00243AE8(void *dst, int a0, int a1);
extern void func_00243978(void *dst, void *src);
extern int func_00194508(void *buf, int a2);
int func_00194840(int a0, int a1, int a2, int a3)
{
    int *p;
    int buf[8];
    register int sa2 = a2;
    register int sa3 = a3;
    int r;
    p = &buf[4];
    func_00243AE8(p, a0, a1);
    p = &buf[0];
    buf[5] = 0;
    func_00243978(p, &buf[4]);
    r = func_00194508(p, sa2);
    return __builtin_abs(r) < sa3;
}

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

extern float func_0010E9A0(int x);
extern unsigned int D_006327B0_far[] __asm__("D_006327B0");
float func_001948F0(int a0, float a1)
{
    float r = func_0010E9A0((short)((a0 << 15) / 0xB4));
    if (r == 0.0f)
        return *(float *)D_006327B0_far;
    return a1 / r;
}
int func_00194960(int a0)
{
    if (a0 > 0) {
        a0 = a0 % 360;
    } else {
        int a = a0 < 0 ? -a0 : a0;
        a0 = (a / 360 + 1) * 360 + a0;
    }
    return (a0 < 181) ? a0 : a0 - 360;
}
int func_001949B8(int a0)
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
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194A08);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194BD8);
extern int D_00274EC0[];
extern float D_00633DC0;

void func_00194DC0(void)
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

void func_00194FE8(int a0, int a1)
{
    *(int *)(*(int *)(a0 + 0x164) + 0x674) = a1;
    func_001951A0(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194FF4);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_00194FF8);
INCLUDE_ASM("asm/nonmatchings/src/mail-add-data", func_001950F8);
extern void func_001AD768(const char *, int);
extern void func_00263FF0(const char *, int, const char *);

void func_001951A0(char *self)
{
    char *sub_a = *(char **)(self + 0x164);
    int *sub_b;
    if (sub_a == 0) {
        func_001AD768(D_0055AF08, 0x47);
        func_00263FF0(D_0055AF08, 0x47, D_0055AF20);
        sub_a = *(char **)(self + 0x164);
    }
    sub_b = *(int **)(sub_a + 0x674);
    *sub_b = 0;
}
