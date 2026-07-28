/* func_0016A5F0 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself. */

void func_0016A5F0(int *a0, int *a1)
{
    int idx = func_00109F10(a1, 0x23);
    int c = *(int *)((char *)a1 + 0xC);
    *(int *)a0 = 0;
    if (c == 4) {
        *(float *)((char *)a0 + 0x4) = -1.0f;
    } else {
        *(float *)((char *)a0 + 0x4) = 1.0f;
    }
    *(int *)((char *)a0 + 0x8) = 0;
    MEM_BARRIER();
    *(int *)((char *)a0 + 0xC) = 0;
    {
        register int base =
            *(int *)(*(int *)((char *)a1 + 0x15C) + 0xC);
        func_002438B8(a0, base + (idx << 6), (char *)a0);
    }
}
