extern void func_00241838(void *a0, int a1, int a2);

void func_002416F0(int *a0, int a1) {
    int *ptr;
    func_00241838(a0, 2, 3);
    ptr = (int *)a0[0];
    a0[0] = (int)(ptr + 1);
    a0[3] = (int)ptr;
    *ptr = a1 ? 0xD0000000 : 0x50000000;
}
