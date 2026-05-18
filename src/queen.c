/* queen.c -- typed sdata / lit4 definitions for this TU.
 *
 * Generated initially by tools/decode_sdata_lit4_typed.py
 * from baserom/baseelf.elf. Each line is a developer
 * reconstruction of one game variable or constant; the
 * file is tracked because the typed forms (named float
 * constants, string literals, single hex-word declarations)
 * are clean-room rather than raw byte arrays.
 *
 * As the TU gets fully decompiled, function definitions
 * land in this same file (per-TU layout); typed
 * data declarations stay here next to their references.
 *
 * Downstream tools (rewrite_data_named_sections.py,
 * migrate_data_per_tu.py _scan_existing_definitions) detect
 * the D_<VMA> name on each line and drop the corresponding
 * asm-generated and sidecar definitions.
 */


__attribute__((section(".rodata.0x0055C690"))) const char D_0055C690[16] = "src/queen.c";

__attribute__((section(".rodata.0x0055C620"))) const char D_0055C620[40] = "n_enemy_max:%d n_enemy:%d counter:%d";
__attribute__((section(".rodata.0x0055C658"))) const char D_0055C658[24] = "queen_ball_scr";
__attribute__((section(".rodata.0x0055C6C8"))) const char D_0055C6C8[16] = "damage:%d";
__attribute__((section(".rodata.0x0055CEB0"))) const char D_0055CEB0[32] = "../ito/include/mv_defs.h";
__attribute__((section(".rodata.0x0055CF10"))) const char D_0055CF10[32] = "../ito/include/mv_defs.h";
__attribute__((section(".rodata.0x0055CF30"))) const char D_0055CF30[16] = "p != NULL";
__attribute__((section(".rodata.0x0055CF70"))) const char D_0055CF70[40] = "sceMpegGetPicture() decode error";
__attribute__((section(".rodata.0x0055CFA8"))) const char D_0055CFA8[32] = "../ito/include/mv_defs.h";
__attribute__((section(".rodata.0x0055CFC8"))) const char D_0055CFC8[16] = "p != NULL";

/* String rodata migrated from queen_data.c */
__attribute__((section(".rodata.0x0055C5C0"))) const char D_0055C5C0[16] = "queen attacked\n";
__attribute__((section(".rodata.0x0055C5D0"))) const char D_0055C5D0[16] = "enemy dead %p\n";
__attribute__((section(".rodata.0x0055C648"))) const char D_0055C648[16] = "queen dead\n";
__attribute__((section(".rodata.0x0055C6A0"))) const char D_0055C6A0[24] = "queen barrier attacked\n";
__attribute__((section(".rodata.0x0055C6D8"))) const char D_0055C6D8[16] = "mail %d\n";
__attribute__((section(".rodata.0x0055C6E8"))) const char D_0055C6E8[24] = "queen ball attacked\n";
__attribute__((section(".rodata.0x0055C720"))) const char D_0055C720[32] = "queen barrier damaged\n";
__attribute__((section(".rodata.0x0055CD98"))) const char D_0055CD98[16] = "movie pause\n";
__attribute__((section(".rodata.0x0055CDA8"))) const char D_0055CDA8[16] = "D_CTRL %x\n";
__attribute__((section(".rodata.0x0055CDB8"))) const char D_0055CDB8[24] = "open movie file %s\n";
__attribute__((section(".rodata.0x0055CDD0"))) const char D_0055CDD0[32] = "create video decode thread\n";
__attribute__((section(".rodata.0x0055CDF0"))) const char D_0055CDF0[16] = "start thread\n";
__attribute__((section(".rodata.0x0055CE00"))) const char D_0055CE00[16] = "add intc\n";
__attribute__((section(".rodata.0x0055CE10"))) const char D_0055CE10[24] = "add intc failed\n";
__attribute__((section(".rodata.0x0055CE28"))) const char D_0055CE28[16] = "add dmac\n";
__attribute__((section(".rodata.0x0055CE38"))) const char D_0055CE38[24] = "add dmac failed\n";
__attribute__((section(".rodata.0x0055CE50"))) const char D_0055CE50[24] = "sceGsGetIMR() %lx\n";
__attribute__((section(".rodata.0x0055CE68"))) const char D_0055CE68[16] = "dmac %d %d\n";
__attribute__((section(".rodata.0x0055CE78"))) const char D_0055CE78[16] = "intc %d %d\n";
__attribute__((section(".rodata.0x0055CE88"))) const char D_0055CE88[24] = "movie init failed\n";
__attribute__((section(".rodata.0x0055CEA0"))) const char D_0055CEA0[16] = "movie end\n";
__attribute__((section(".rodata.0x0055CF40"))) const char D_0055CF40[24] = "pts buffer overflow\n";
__attribute__((section(".rodata.0x0055CF58"))) const char D_0055CF58[24] = "decode thread: aborted\n";
__attribute__((section(".rodata.0x0055CF98"))) const char D_0055CF98[16] = "movie %d x %d\n";

/* Float rodata migrated from queen_data.c */
__attribute__((section(".rodata.0x0055C2C0"))) const float D_0055C2C0[12] = { 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.0f };
__attribute__((section(".rodata.0x0055C2F0"))) const float D_0055C2F0[66] = { 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f };
__attribute__((section(".rodata.0x0055C3F8"))) const float D_0055C3F8[12] = { 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
__attribute__((section(".rodata.0x0055C428"))) const float D_0055C428[12] = { 3.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f };
__attribute__((section(".rodata.0x0055C458"))) const float D_0055C458[12] = { 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 4.0f, 0.0f };
__attribute__((section(".rodata.0x0055C488"))) const float D_0055C488[12] = { 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.6f, 0.0f };
__attribute__((section(".rodata.0x0055C4B8"))) const float D_0055C4B8[66] = { 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f, 0.0f, 0.0f, 0.001f, 0.01f, 0.99f, 0.99f };
__attribute__((section(".rodata.0x0055C700"))) const float D_0055C700[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
__attribute__((section(".rodata.0x0055C740"))) const float D_0055C740[4] = { 2.5e+02f, 1.5e+02f, 2e+02f, 0.0f };
__attribute__((section(".rodata.0x0055C750"))) const float D_0055C750[4] = { 1e+02f, 1.2e+02f, 115.0f, 0.0f };

/* String-pool rodata migrated from queen_data.c */
__attribute__((section(".rodata.0x0055CED0"))) const char D_0055CED0[64] = "p != NULL\000\000\000\000\000\000\000../ito/include/mv_defs.h\000\000\000\000\000\000\000\000p != NULL\000\000\000\000\000\000";

#include "include_asm.h"
#include "regpin.h"

extern int *func_0013EB50(int a0);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A7E8);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A8F0);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A9A0);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AA20);
extern void func_0019C280(float x);
void func_0019AE50(int *self)
{
    int *p = (int *)((int *)self[0x15C / 4])[0x800 / 4];
    if (*(signed char *)((char *)p + 0x12) == 0) return;
    {
        float f = (float)p[0x18 / 4];
        func_0019C280(1.0f - f / 5.0f);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AE98);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B660);
extern int *func_00202208(int *self);
extern void func_00203AA0(int x);
extern void func_00203B78(void *func, int id);
extern int func_001E29E8(int *self, int x, int *arg);
extern char D_00199F80[];
extern int func_0019BCE0(void);
extern int func_00199C30(void);
void func_0019B7F8(int *self)
{
    int *p = func_00202208(self);
    func_00202148(self);
    func_00203AA0(1);
    func_00203B78((void *)D_00199F80, 0x14);
    func_00203B78((void *)func_0019BCE0, 0x15);
    func_00203B78((void *)func_00199C30, 0x15);
    p[0x120 / 4] = func_001E29E8(self, 0xEE, p + 0x610 / 4);
    ((int *)self[0x15C / 4])[0x7C / 4] = 1;
}
extern int func_0013EBE0(int iter);
void func_0019B888(void)
{
    int *obj1 = func_0013EB50(0x2E);
    int *iter;
    *((char *)((int *)obj1[0x15C / 4])[0x800 / 4] + 1) = 1;
    iter = func_0013EB50(0x35);
    while (iter != 0) {
        *((char *)((int *)iter[0x15C / 4])[0x800 / 4] + 0x12) = 1;
        iter = (int *)func_0013EBE0((int)iter);
    }
}

int func_0019B8E8(void)
{
    int v0 = (int)func_0013EB50(0x2E);
    int v1 = *(int *)(v0 + 0x15C);
    int a0 = *(int *)(v1 + 0x800);
    return *(signed char *)(a0 + 0x3);
}

int func_0019B910(void)
{
    int v0 = (int)func_0013EB50(0x2E);
    int v1 = *(int *)(v0 + 0x15C);
    int a0 = *(int *)(v1 + 0x800);
    return *(int *)(a0 + 0x4);
}

float func_0019B938(char *self) {
    char *sub = *(char **)(self + 0x15C);
    char *p = *(char **)(sub + 0x800);
    return *(float *)(p + 0x14);
}

int func_0019B948(void)
{
    int *p;
    int ret = 0;
    p = (int *)((int *)func_0013EB50(0x2E)[0x15C / 4])[0x800 / 4];
    if (p[0x4 / 4] > 0 || p[0x8 / 4] > 0) {
        ret = 1;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B998);

int func_0019BA60(void)
{
    int ret = 0;
    int *p;
    int *q;
    int *r;
    p = func_0013EB50(0x35);
    if (p != 0) {
        q = (int *)p[0x15C / 4];
        r = (int *)q[0x800 / 4];
        ret = r[0x18 / 4] < 5;
    }
    return ret;
}

INCLUDE_ASM_NOP_PAD(func_0019BAA4);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BAA8);

float func_0019BB40(int a0)
{
    return *(float *)(*(int *)(*(int *)(a0 + 0x15C) + 0x800) + 0x14) * 100.0f;
}

INCLUDE_ASM_NOP_PAD(func_0019BB5C);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BB60);
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BC58);
