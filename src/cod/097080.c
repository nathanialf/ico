extern int D_00631990;
extern void func_0010ECC0(int *self);
extern int func_0012A7F8(int *p);
extern void func_001998C0(void);

void func_00197080(int *self)
{
    int *q;
    func_0010ECC0(self);
    q = (int *)((int *)self[0x15C/4])[0x800/4];
    if (q[0x30/4] != 0) {
        if (func_0012A7F8(q + 0x30/4) != 0) {
            q[0x30/4] = 0;
        }
    }
    if (D_00631990 == 0x52) {
        func_001998C0();
    }
}
