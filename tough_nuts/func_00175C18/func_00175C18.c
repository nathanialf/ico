/* func_00175C18 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself.
 * Clean (no REG pin) 11-diff seed; the retired REG("$2") form is gone. */

int func_00175C18(void)
{
    char *sub = *(char **)((char *)D_00631AE8 + 0x164);
    if (((*(unsigned long long *)(sub + 0x18) >> 36) & 1) == 0) {
        return 1;
    }
    {
        int v = *(int *)(sub + 0x30);
        int r = 0;
        if (v == 0x45 && D_002883D0[0x5D] != 0) {
            r = D_002883D0[0x58] == 0;
        }
        return r;
    }
}
