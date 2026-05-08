int func_001653A0(int *self) {
    int *p = (int *)self[0x164/4];
    int *q = (int *)p[0x670/4];
    if (q[0x1E0/4] == 0 && p[0x30/4] == 0x10) {
        return q[0x218/4];
    }
    return 0;
}
