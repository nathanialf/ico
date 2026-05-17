/* s_init.c -- typed sdata / lit4 definitions for this TU.
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


__attribute__((section(".rodata.0x00557CC8"))) const char D_00557CC8[16] = "sound/s_init.c";
__attribute__((section(".rodata.0x00557D80"))) const char D_00557D80[16] = "center x";
__attribute__((section(".rodata.0x00557D90"))) const char D_00557D90[16] = "center y";
__attribute__((section(".rodata.0x00557DA0"))) const char D_00557DA0[16] = "volumeRate";
__attribute__((section(".rodata.0x00557DB0"))) const char D_00557DB0[24] = "max volume range";
__attribute__((section(".rodata.0x00557DC8"))) const char D_00557DC8[16] = "attenuator";
__attribute__((section(".rodata.0x00557DD8"))) const char D_00557DD8[16] = "volume length";
__attribute__((section(".rodata.0x00557DE8"))) const char D_00557DE8[16] = "max volume type";
__attribute__((section(".rodata.0x00557DF8"))) const char D_00557DF8[16] = "stereo rate";

/* String rodata migrated from s_init_data.c */
__attribute__((section(".rodata.0x00557C50"))) const char D_00557C50[24] = "Spu2DmaWriteEe2Iop\n";
__attribute__((section(".rodata.0x00557C68"))) const char D_00557C68[24] = "ee %x iop %x size %x\n";
__attribute__((section(".rodata.0x00557C80"))) const char D_00557C80[32] = "send SpuStEnv completed \n";
__attribute__((section(".rodata.0x00557CA0"))) const char D_00557CA0[16] = "SgInit()\n";
__attribute__((section(".rodata.0x00557CB0"))) const char D_00557CB0[24] = "SgSetTickMode()\n";
__attribute__((section(".rodata.0x00557CD8"))) const char D_00557CD8[24] = "\nCan't alloc heap \n";
__attribute__((section(".rodata.0x00557CF0"))) const char D_00557CF0[40] = "iop sound alloced 0x%x  size %d\n";
__attribute__((section(".rodata.0x00557D18"))) const char D_00557D18[16] = "se open\n";
__attribute__((section(".rodata.0x00557D28"))) const char D_00557D28[24] = "bgm request buff over\n";
__attribute__((section(".rodata.0x00557D40"))) const char D_00557D40[16] = "bgm not open\n";
__attribute__((section(".rodata.0x00557D50"))) const char D_00557D50[16] = "bgm play\n";
__attribute__((section(".rodata.0x00557D60"))) const char D_00557D60[32] = "soundBufAdpcmChAlloc over\n";
__attribute__((section(".rodata.0x00557E08"))) const char D_00557E08[24] = "req no %d %s %f\n";
__attribute__((section(".rodata.0x00557E20"))) const char D_00557E20[16] = "%s%8s = %d\n";
__attribute__((section(".rodata.0x00557E30"))) const char D_00557E30[16] = "%s%8s = %f\n";
__attribute__((section(".rodata.0x00557E50"))) const char D_00557E50[24] = "se request buff over\n";
__attribute__((section(".rodata.0x00557E68"))) const char D_00557E68[16] = "se not open\n";
__attribute__((section(".rodata.0x00557E78"))) const char D_00557E78[16] = "num %d %d\n";
__attribute__((section(".rodata.0x00557E88"))) const char D_00557E88[24] = "sound manager in\n";
__attribute__((section(".rodata.0x00557EA0"))) const char D_00557EA0[16] = "IosSndLock %d\n";
__attribute__((section(".rodata.0x00557EB0"))) const char D_00557EB0[32] = "SOUND MANAGER START\n";
__attribute__((section(".rodata.0x00557ED0"))) const char D_00557ED0[16] = "with mail\n";

#include "include_asm.h"
#include "matching.h"
#include "regpin.h"


extern int D_00632240;
extern int func_00135EB8(int x, char *p, int b);
extern void func_001A6E28();

void func_00141340(void) {
    int v = func_00135EB8(0x78000, D_00557CC8, 0xFE);
    D_00632240 = v;
    if (v < 0) {
        func_001A6E28(D_00557CD8);
    } else {
        func_001A6E28(D_00557CF0, v, 0x78000);
    }
}


INCLUDE_ASM_NOP_PAD(func_0014139C);


extern void func_0024A1E0(int a0);
void func_001413A0(void)
{
    func_0024A1E0(D_00632240);
}


INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_001413A8);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00141660);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00141868);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00141980);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00141C28);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00141D18);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00141E00);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00141F58);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00142008);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00142208);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00142890);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00142C60);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143138);


extern void func_00143138(int a0, int a1);
void func_00143240(int a0)
{
    func_00143138(a0, 0);
}



void func_00143248(int a0)
{
    func_00143138(a0, 1);
}



extern char D_006A98B0[];
extern int func_0025DA68(int a0);

void func_00143250(int a0)
{
    char *entry;
    short id;
    entry = &D_006A98B0[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry) return;
    func_0025DA68(id);
}


INCLUDE_ASM_NOP_PAD(func_0014328C);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143290);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_001434B0);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143948);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143AD0);


extern int D_00632214;

int func_00143B88(void) {
    return D_00632214;
}



extern int D_00632208;

int func_00143B90(void) {
    return D_00632208;
}


INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143B98);


extern long long D_00633CD8;

void func_00143CB0(char *self) {
    long long mask = ~*(long long *)(self + 0x18);
    D_00633CD8 &= mask;
    *(long long *)(self + 0x18) = 0;
}


INCLUDE_ASM_NOP_PAD(func_00143CCC);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143CD0);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143D18);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143E60);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", func_00143FC0);
