extern void func_00263520(float *a, int *b);
extern int func_00263410(int *buf);

void func_00263F48(float f12) {
    int buf[8];
    *(float *)((char *)buf + 0x10) = f12;
    func_00263520((float *)((char *)buf + 0x10), buf);
    buf[1] = (buf[1] == 0) ? 1 : 0;
    func_00263410(buf);
}
