#include "common.h"







typedef struct AmbientVolume {
    char _pad0[0x90];
    int f_90;                   /* 0x90 */
    struct AmbientVolume *next; /* 0x94 */
    struct AmbientVolume *prev; /* 0x98 */
} AmbientVolume;
extern const char D_00554780[];
extern void debug_assertMessage();
extern int D_00631C18;
extern int func_00242640();
extern void gsb_SetBGColor();
#include "vu0.h"
extern char D_00631C70[8];
extern int D_00633C30;
extern int D_00633C34;
extern float D_00631BC8;
extern float D_00631BC0;
extern unsigned char D_00672E90[];
INCLUDE_ASM("asm/nonmatchings/src/Light", light_killLinkLight);

INCLUDE_ASM("asm/nonmatchings/src/Light", light_killLinkAmbient);

INCLUDE_ASM("asm/nonmatchings/src/Light", light_AddLight);

INCLUDE_ASM("asm/nonmatchings/src/Light", light_getNearLight);

void light_getAmbientLight(void *a0, int r, int g, int b) {
    unsigned long long bg = ((long long)b << 16) | ((long long)g << 8);
    unsigned long long v = r | 0x3F80000000000000ULL;
    v |= bg;
    *(int *)&D_00672E90[0] = r;
    v |= 0x80000000;
    *(int *)&D_00672E90[4] = g;
    *(int *)&D_00672E90[8] = b;
    *(int *)&D_00672E90[0xC] = 0x80;
    *(unsigned long long *)((char *)a0 + 0x1F0) = v;
    *(unsigned long long *)((char *)a0 + 0x100) = v;
}

void light_MakeLightMatrix(unsigned char *a0)
{
    a0[0] = D_00672E90[0];
    a0[1] = D_00672E90[4];
    a0[2] = D_00672E90[8];
    a0[3] = D_00672E90[0xC];
}

void light_DispVolume(float a, float b) {
    D_00631BC0 = a;
    D_00631BC8 = b;
}

int light_GetColorAnalog(void)
{
    int counter;
    if (func_00242640(1, 0) == 0) goto reset;
    counter = D_00631C18 + 1;
    D_00631C18 = counter;
    if (counter >= 0xB) {
        debug_assertMessage(D_00554780);
        gsb_SetBGColor();
        D_00631C18 = 0;
    }
    return 1;
reset:
    D_00631C18 = 0;
    return 0;
}

extern char D_00275120[];
extern char D_005547A0[];
extern char D_005547C0[];
extern char D_005547F0[];
extern char D_005F2FF8[];
extern int D_00631990;
extern int func_001AA4F0(void *a0, int a1);
extern void func_001AA550(int a0);
extern void func_002479C0(int a0, void *a1, int a2);
extern void func_00264DF8(void *a0, void *a1, void *a2);

int light_DrawCursor(void) {
    char buf[0x100];
    int s0;
    func_00264DF8(buf, D_005547A0, &D_005F2FF8[D_00631990 * 0x194]);
    s0 = func_001AA4F0(buf, 1);
    if (s0 < 0) {
        debug_assertMessage(D_005547C0);
    } else {
        debug_assertMessage(D_005547F0, buf);
        func_002479C0(s0, D_00275120, 0x130);
        func_001AA550(s0);
    }
    return -1;
}

extern char D_00554810[];
extern char D_00554840[];
extern void func_00247C30(int a0, void *a1, int a2);

int light_Tool(void) {
    char buf[0x100];
    int s0;
    func_00264DF8(buf, D_005547A0, &D_005F2FF8[D_00631990 * 0x194]);
    s0 = func_001AA4F0(buf, 0x602);
    if (s0 < 0) {
        debug_assertMessage(D_00554810);
    } else {
        func_00247C30(s0, D_00275120, 0x130);
        debug_assertMessage(D_00554840, buf);
        func_001AA550(s0);
    }
    return -1;
}

void light_InitLight(void) {
    volatile int local[96];
}

INCLUDE_ASM("asm/nonmatchings/src/Light", light_KillAllFixLight);

INCLUDE_ASM("asm/nonmatchings/src/Light", light_KillAllAmbient);

INCLUDE_ASM("asm/nonmatchings/src/Light", light_AddAmbientObject);

INCLUDE_ASM("asm/nonmatchings/src/Light", light_resetFlatLight);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115878);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115ED8);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00115FB8);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_001165A8);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00116888);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00116C08);

void func_00117750(void) {
    D_00633C30 = 0;
    D_00633C34 = 0;
    *(int *)D_00631C70 = 0;
}

void func_00117760(void) {}

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117768);

void func_001177C8(void)
{
    AmbientVolume *p = (AmbientVolume *)D_00633C34;
    while (p != 0) {
        int v = p->f_90;
        if (v < 3) {
            if (v >= 0) {
                AmbientVolume *node = p;
                p = p->prev;
                light_KillAllAmbient((char *)node);
                continue;
            }
        }
        p = p->prev;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117820);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117890);

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117950);

void func_00117C20(void *p0, void *p1, void *p2, void *p3, void *p4, void *p5)
{
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(a2, 12);
    VU0_QMTC2_NI(a2, 1);
    VU0_NOREORDER_END();
    VU0_WORD(0x4A0103BD);
    VU0_WAIT();
    VU0_NOREORDER_BEGIN();
    VU0_CFC2_NI(a3, 22);
    VU0_MTC1(a3, 0);
    VU0_NOREORDER_END();
}

void func_00117C40(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_V2OP(vmr32.xyzw, 6, 7);
    VU0_V2OP(vmr32.xyzw, 5, 6);
    VU0_V2OP(vmr32.xyzw, 4, 5);
    VU0_REG("viaddi $vi15, $vi0, 0x0");
    VU0_NOP();
}

void func_00117C60(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_V2OP(vmr32.xyzw, 6, 7);
    VU0_V2OP(vmr32.xyzw, 5, 6);
    VU0_V2OP(vmr32.xyzw, 4, 5);
    VU0_REG("viaddi $vi15, $vi0, 0x0");
    VU0_NOP();
}

void func_00117C80(void)
{
    VU0_REG("vsqi.xyzw $vf4, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf5, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf6, ($vi15++)");
    VU0_REG("vsqi.xyzw $vf7, ($vi15++)");
    VU0_NOP();
}

void func_00117C98(void)
{
    VU0_REG("vlqd.xyzw $vf7, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf6, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf5, (--$vi15)");
    VU0_REG("vlqd.xyzw $vf4, (--$vi15)");
    VU0_NOP();
}

void func_00117CB0(void *p0)
{
    VU0_LSV(lqc2, 8, 0x0, a0);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 7, 7, 8, w);
    VU0_NOP();
}

void func_00117CD0(void *p0)
{
    VU0_LSV(lqc2, 8, 0x0, a0);
    VU0_V2OP(vmove.xyzw, 7, 8);
    VU0_NOP();
}

void func_00117CE0(void)
{
    VU0_V2OP(vmove.xyzw, 7, 0);
    VU0_NOP();
}

INCLUDE_ASM("asm/nonmatchings/src/Light", func_00117CF0);

/* .rodata — carved VMA 0x554780..0x554790 (1 symbol), bytes verified against baserom/baseelf.rom */
const char D_00554780[16] = "reset gs\n";

