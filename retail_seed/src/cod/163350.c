extern void func_00262848(int *a, int *b);
extern void func_00262718(int *a);

void func_00263350(long long a0) {
    int buf[12];
    *(long long *)(buf + 8) = a0;
    func_00262848(buf + 8, buf);
    buf[1] = (buf[1] == 0) ? 1 : 0;
    func_00262718(buf);
}
