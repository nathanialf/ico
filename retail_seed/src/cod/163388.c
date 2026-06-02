extern void func_00262718(int *buf);

void func_00263388(int a0, int a1, int a2, long long a3) {
    int buf[8];
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    *(long long *)(buf + 4) = a3;
    func_00262718(buf);
}
