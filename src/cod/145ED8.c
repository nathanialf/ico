extern int *func_00245EA8(int *a0);

int *func_00245ED8(int *a0, int a1) {
    if (a1 < 0 || a1 >= a0[0x20/4]) {
        return func_00245EA8(a0);
    }
    return (int *)(a0[0x1C/4] + (a1 << 6));
}
