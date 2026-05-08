extern void func_00263520(float *a, int *b);
extern void func_00263388(int a0, int a1, int a2, long long a3);

void func_00263FB0(float f12) {
    int buf[8];
    *(float *)((char *)buf + 0x10) = f12;
    func_00263520((float *)((char *)buf + 0x10), buf);
    func_00263388(buf[0], buf[1], buf[2], (long long)((unsigned long long)(unsigned int)buf[3] << 30));
}
