/* func_001F4250 - parked seed: single function extracted from its coalesced
 * TU snapshot (the full-TU seed exceeded the check_no_rom 256KiB cap).
 * Externs/typedefs for permuter context live in the TU itself. */

void func_001F4250(int *self, int arg1, int a2)
{
    register int a2_check REG("$5");
    int *s0;
    int *p;
    int v;
    int *s1;
    a2_check = a2;
    s0 = (int *)((GObj *)(self))->p_15C;
    p = (int *)((Sub15C *)(s0))->p_800;
    v = p[0x8 / 4];
    s1 = s0 + 0xA0 / 4;
    if (v != 0) {
        int *r = (int *) ((int *)v)[0x15C / 4];
        r[0x630 / 4] = 0;
    }
    {
        int neg1 = -1;
        int one = 1;
        p[0x4 / 4] = one;
        p[0xC / 4] = neg1;
    }
    p[0x8 / 4] = 0;
    if (a2_check != 0) {
        func_0010D830(s0 + 0x150 / 4);
    }
    func_00105F00(s0 + 0x130 / 4, arg1);
    s1[0x9C / 4] = 0;
}
