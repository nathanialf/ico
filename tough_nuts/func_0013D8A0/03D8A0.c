extern int *D_006A6F30[];
extern int func_00100410(void);

int func_0013D8A0(int *a0) {
    if (a0 == 0) {
        int idx = func_00100410();
        a0 = D_006A6F30[idx];
    }
    return a0[0x18/4];
}
