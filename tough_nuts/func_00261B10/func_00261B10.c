/* func_00261B10 — parked near-miss (rc17). strstr-like (find a1 in a0).
 * No externs needed. Residual rc17 = char signedness (lb vs lbu) + the early
 * empty-string guard structure + goto-CFG don't match the ROM's lowering; the
 * recovered goto shape below is only an approximation, re-derive from the asm. */
char *func_00261B10(char *a0, char *a1) {
    char c0;
    int j;
    c0 = *a0;
    if (!c0) {
        return *a1 ? (char*)0 : a0;
    }
    if (!*a1) {
        return a0;
    }
    j = 0;
    while (*a0) {
        char h0 = a0[0];
        if (a1[j] != h0) {
            a0++;
            goto outer;
        }
        j++;
    inner:
        {
            char hj = a1[j];
            char nj;
            if (!hj) return a0;
            nj = a0[j];
            if (hj == nj) {
                j++;
                goto inner;
            }
        }
        a0++;
    outer:
        c0 = *a0;
    }
    return (char*)0;
}
