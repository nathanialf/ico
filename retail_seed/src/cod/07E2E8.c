extern int func_00203AA0(int a0);

void func_0017E2E8(int *self) {
    int *p = (int *)self[0x164/4];
    while ((((int *)p[0x120/4])[0x5C/4] & 1) == 0) {
        func_00203AA0(1);
    }
}
