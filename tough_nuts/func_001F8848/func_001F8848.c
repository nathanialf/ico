/* seki/src/DmaPacket.c — func_001F8848 parked seed (rc4, best of 30-stall).
   Apply into seki/src/DmaPacket.c, then match_loop.py reset func_001F8848. */
extern int D_004C3850[];

void func_001F8848(void) {
    int idx = D_004C3850[0] ^ 1;
    D_004C3850[0] = idx;
    D_004C3850[4] = D_004C3850[idx + 1];
    D_004C3850[5] = 0;
    D_004C3850[6] = 0;
    D_004C3850[7] = 0;
}
