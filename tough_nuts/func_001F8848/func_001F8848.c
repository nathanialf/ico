/* seki/src/DmaPacket.c — func_001F8848 parked seed (rc2 on aug6, Fire 7 permuter).
   BREAKTHROUGH over the old rc4 floor: a SHORT-narrowed array index plus a
   base-alias. `(short)idx` forces the index through a 16-bit pseudo, which (a)
   makes gcc fold the `+1` into the LOAD DISPLACEMENT (lw 4) instead of scaling
   (idx+1)*4, and (b) keeps idx + the scaled value in SEPARATE registers (4 regs),
   which lands %hi(D_004C3850)->a0 — the correct coloring the bare-array form had
   but the pointer/struct forms (rc11) flipped. The `(p = D_004C3850)[...]`
   base-alias shaves the last reg detail (rc3->rc2).
   RESIDUAL (rc2, 2 insns): the short cast emits `sll v0,v1,0x10; sra v0,v0,0xe`
   (sign-extend-and-*4) where ROM has a plain `sll v0,v1,0x2`. Every narrowing
   (short/ushort/mask 0x7FFF/0xFFFF) that triggers the disp-fold ALSO emits the
   ext; every int form that avoids the ext either scales (idx+1)*4 (array, rc4) or
   flips %hi->v1 (pointer, rc11). Coloring(needs 4-reg pseudo) and no-ext(needs
   int) appear mutually exclusive in hand C — permuter-class.
   Apply, then match_loop.py reset func_001F8848. */
extern int D_004C3850[];

void func_001F8848(void) {
    int *p;
    int idx = D_004C3850[0] ^ 1;
    D_004C3850[0] = idx;
    D_004C3850[4] = (p = D_004C3850)[(short)idx + 1];
    idx = 0;
    D_004C3850[5] = idx;
    D_004C3850[6] = idx;
    D_004C3850[7] = idx;
}
