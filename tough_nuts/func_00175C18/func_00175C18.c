/* func_00175C18 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself.
 * Clean (no REG pin) rc9 seed — IMPROVED from rc11 by a 5-min permuter shot
 * (2026-05-31). The lever the permuter surfaced: an ASSIGNMENT-IN-CONDITION
 * that reuses `r` for D[0x5D] (`(r = D_002883D0[0x5D]) != 0`) plus an r/v
 * live-range swap (`r=v; …; v=r; return v;`). That cleanly fixes the const
 * -> $v1 allocation (the old rc11 had const stuck in $v0). The remaining
 * rc9 residual is the v-load -> $a0 vs $v0 coalesce tie (the load wants $a0
 * = the `register v asm("$4")` pin); no clean massage found — dummy param,
 * early-read, and the permuter's own 5-min randomization all plateau at rc9.
 * The two cleaned forms (without the r/v swap) regress to rc11, so keep the
 * swap verbatim. */

extern int D_00631AE8;
extern unsigned char D_002883D0[];

int func_00175C18(void)
{
    char *sub = *(char **)((char *)D_00631AE8 + 0x164);
    if (((*(unsigned long long *)(sub + 0x18) >> 36) & 1) == 0) {
        return 1;
    }
    {
        int v = *(int *)(sub + 0x30);
        int r = 0;
        r = v;
        if (r == 0x45 && (r = D_002883D0[0x5D]) != 0) {
            r = D_002883D0[0x58] == 0;
        }
        v = r;
        return v;
    }
}
