/* src/DmaPacket.c
 *
 * The `extern int D_00632014;` precedes the plain definition below
 * so ee-gcc 2.9's small-data heuristic emits %gp_rel for references
 * in the function. The compiler reads the first declaration to
 * decide gp_rel eligibility.
 *
 * Phase 3d pilot: this TU's `.rodata` and `.sdata` defs are in plain
 * form (no `__attribute__((section()))` wrappers); slinky places the
 * .o's per-section content via per-TU explicit slots in
 * ico.us.slinky.ld (see tools/postprocess_slinky_ld.py).
 */

extern int D_00632014;
extern int D_004C7710[];
extern int func_0013A0F8(int handle, int size, char *file, int line);

int D_00632014 = 0;
const char D_0061AC60[16] = "src/DmaPacket.c";

void func_001FBB48(void)
{
    D_004C7710[0] = 0;
    D_004C7710[1] = func_0013A0F8(D_00632014, 0x80000, D_0061AC60, 0x86) | 0x30000000;
    D_004C7710[2] = func_0013A0F8(D_00632014, 0x80000, D_0061AC60, 0x87) | 0x30000000;
    D_004C7710[4] = (D_004C7710 + D_004C7710[0])[1];
}
