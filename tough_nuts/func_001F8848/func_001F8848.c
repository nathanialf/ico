/* seki/src/DmaPacket.c — func_001F8848 parked seed (rc1, after 2 permuter passes).
   Residual: a single redundant `andi v0,v0,0xfc` mask after a CORRECT sll2
   (idx*4) — gcc inserts (idx*4)&252 that ROM lacks (§5.11-class canonicalization).
   The `idx=0; out[]=idx` zero-reuse store structure (permuter-found) is what
   collapsed rc4->rc1. No int/uint/long/char/short or store-order form removes
   the andi. Apply, then match_loop.py reset func_001F8848. */
extern int D_004C3850[];

void func_001F8848(void) {
    int idx = D_004C3850[0] ^ 1;
    D_004C3850[0] = idx;
    D_004C3850[4] = D_004C3850[idx + 1];
    idx = 0;
    D_004C3850[5] = idx;
    D_004C3850[6] = idx;
    D_004C3850[7] = idx;
}
