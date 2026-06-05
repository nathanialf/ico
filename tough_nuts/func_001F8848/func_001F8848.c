/* seki/src/DmaPacket.c — func_001F8848 parked seed (rc2, post-permuter best).
   Residual: char sign-extension (sll24/sra22) vs ROM clean sll2; the sra is
   coupled to the correct a0/a1 coloring (int forms re-materialize/flip). */
extern int D_004C3850[];

void func_001F8848(void) {
    int idx = D_004C3850[0] ^ 1;
    char si = idx;
    D_004C3850[0] = idx;
    D_004C3850[4] = *(int *)((char *)D_004C3850 + si * 4 + 4);
    D_004C3850[5] = 0;
    D_004C3850[6] = 0;
    D_004C3850[7] = 0;
}
