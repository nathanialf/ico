/* girl_brain_main.c.inc — rodata + chunk-1 function fragments for the
 * girl_brain_main translation unit, inline-included from src/commonact.c.
 *
 * `__FILE__` anchor: `D_00559528 = "src/girl_brain_main.c.inc"`. Funcs
 * that load this anchor (per asm scan) sit at 0x16AE48 (chunk 1) and
 * 0x16E910 (chunk 2). Chunk 1 lives here; chunk 2 is inlined later in
 * commonact.c (between gba chunk 1 and gba chunk 2) with a `#line`
 * directive to keep its __FILE__ accurate.
 */

__attribute__((section(".rodata.0x00559528"))) const char D_00559528[32] = "src/girl_brain_main.c.inc";
__attribute__((section(".rodata.0x00559548"))) const char D_00559548[16] = "SAMEGROUP";
__attribute__((section(".rodata.0x00559558"))) const char D_00559558[24] = "OTHERGROUP";
/* EUC-JP: "敵の数が多すぎます" */
__attribute__((section(".rodata.0x00559510"))) const char D_00559510[24] = "\305\250\244\316\277\364\244\254\302\277\244\271\244\256\244\336\244\271";

/* ----- gbm chunk 1 functions (.text 0x16AE48..0x16D707) ----- */

INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016AE48);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016B3C0);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016B790);

extern void func_00104508(int *dst, int *src);
extern void func_0010A498(int *dst, int *src);
extern int *D_00631AE4;
extern int *D_00631AE8;
extern int D_002882D0[];

void func_0016BCA0(void)
{
    func_00104508(&D_002882D0[0], D_00631AE8);
    func_00104508(&D_002882D0[8], D_00631AE4);
    func_0010A498(&D_002882D0[4], D_00631AE8);
    func_0010A498(&D_002882D0[12], D_00631AE4);
}

extern int D_00282AC0[];
extern void func_002641D8(int *a0, int a1, int a2);

void func_0016BCF0(void)
{
    func_002641D8(D_00282AC0, 0, 0x5910);
}

/* func_0016BD04 is a 4-byte nop pad absorbed into func_0016BD08's .s. */
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016BD08);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016BDF8);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016D330);
INCLUDE_ASM("asm/nonmatchings/src/commonact", func_0016D488);
