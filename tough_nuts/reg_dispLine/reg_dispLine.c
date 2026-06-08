/* seki/src/RegistPacket.c — reg_dispLine parked seed (rc2, if-guard form).
   Pass-2 best: empty if(D){} materializes %hi(D) early (rc4->rc2). Residual rc2
   = a0=2/a2=4 gap-filler swap: ROM emits a2 into the lui/lo gap and defers a0=2
   to the jal delay; ee-gcc emits args left-to-right so a0 fills the gap and a2
   defers. Seed the permuter WITH this rc2 form (structurally closest). Apply in
   place of the INCLUDE_ASM stub (after reg_dispPoint, before reg_dispPointLineObj
   — do NOT delete siblings), then match_loop.py reset. */
extern void dpk_SwapBuffer(void);
extern void dpk_Init(int a0, void *a1, int a2);
extern int dl_GetPri(void);
extern int D_0054FBE0[];

void reg_dispLine(void) {
    if (D_0054FBE0) {
    }
    dpk_SwapBuffer();
    dpk_Init(2, D_0054FBE0, 4);
    return dl_GetPri();
}
