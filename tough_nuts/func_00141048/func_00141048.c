/* func_00141048 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself. */

int func_00141048(int *a0, int *a1)
{
    int *p = (int *)a1[0xB];
    int cur, delta, v2;
    register int v3 REG("$3");
    cur = SgStAdpcmIopReadAddr(p[2]);
    if (cur == p[4]) { goto end; }
    delta = cur - p[4];
    if (p[4] >= cur) { delta = p[7] - p[4]; }
    if (0x1EAAA < delta) { goto call1; }
    if (cur >= p[4]) goto cz;
call1:
    func_00132DC0((int)a0, p[6] + p[4], delta);
    v3 = a0[0x44];
    goto cont;
cz:
    delta = 0;
    ANCHOR(delta);
    v3 = a0[0x44];
cont:
    {
        register int t9 REG("$5") = p[9];
        if (v3 < t9) { v2 = p[4]; }
        else { t9 = v3 - t9; func_00133500((int)a0, p[8] + t9); v2 = p[4]; }
    }
    v3 = p[7];
    v2 = v2 + delta;
    p[4] = v2;
    if (v2 >= v3) { p[4] = 0; }
end:
    return 0;
}
