/* src/DmaPacket.c
 *
 * The `extern int D_00632014;` precedes the typed-attribute
 * definition below so ee-gcc 2.9's small-data heuristic emits %gp_rel
 * for references in the function. The compiler reads the first
 * declaration to decide gp_rel eligibility, not the section
 * attribute on the later definition. Typed `.sdata.0xVMA` /
 * `.rodata.0xVMA` attrs keep the linker's SORT_BY_NAME placement
 * VMA-correct until Phase 3e retires SORT_BY_NAME in favor of
 * slinky's per-`.o` ordered emission.
 */

extern int D_00632014;
extern int D_004C7710[];
extern int func_0013A0F8(int handle, int size, char *file, int line);

__attribute__((section(".sdata.0x00632014"))) int D_00632014 = 0;
__attribute__((section(".rodata.0x0061AC60"))) const char D_0061AC60[16] = "src/DmaPacket.c";

void func_001FBB48(void)
{
    D_004C7710[0] = 0;
    D_004C7710[1] = func_0013A0F8(D_00632014, 0x80000, D_0061AC60, 0x86) | 0x30000000;
    D_004C7710[2] = func_0013A0F8(D_00632014, 0x80000, D_0061AC60, 0x87) | 0x30000000;
    D_004C7710[4] = (D_004C7710 + D_004C7710[0])[1];
}
