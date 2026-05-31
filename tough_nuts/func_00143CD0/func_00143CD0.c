/* func_00143CD0 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself. */

char *func_00143CD0(int *a0)
{
    int key = *a0;
    char *p = D_006A95B0;
    register char *end = p + 0x300;
    register char *r REG("$6") = D_006A95B0;
    do {
        char *tmp = r;
        if (*(int *)p == key) goto found;
        p += 0x30;
        r = tmp + 0x30;
    } while ((int)p < (int)end);
    return 0;
found:
    return r;
}
