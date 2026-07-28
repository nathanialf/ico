/* func_001F40D8 — weapon.c — rc3 seed (full-TU seed exceeded check_no_rom 256KiB).
 * IDENTICAL to func_001F4150. Externs/typedefs (GObj, Sub15C, func_001F2388,
 * func_001F1868) live in the TU. */

void func_001F40D8(int *self)
{
    Sub15C *p = ((int *)((GObj *)(self))->p_15C)[0x800 / 4];
    int i;
    if (p->f_50 == 0) {
        return;
    }
    {
        int *arr = (int *)p->f_54;
        func_001F2388(arr[0]);
    }
    for (i = 0; i < p->f_50; i++) {
        int *arr = (int *)p->f_54;
        func_001F1868(arr[i]);
    }
}
