/* func_00175C18 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself. */

int func_00175C18(void)
{
    char *sub = *(char **)((char *)D_00631AE8 + 0x164);
    if (((*(unsigned long long *)(sub + 0x18) >> 36) & 1) == 0) {
        return 1;
    }
    {
        register int v = *(int *)(sub + 0x30);
        register int r REG("$2") = 0;
        if (v == 0x45 && D_002883D0[0x5D] != 0) {
            r = D_002883D0[0x58] == 0;
        }
        return r;
    }
}
